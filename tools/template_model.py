#!/usr/bin/env python3
"""Template Model 1 to 2: every value a Model 1 template reads, read again through Model 2.

kibo 2 renames the accessors that describe a type as the binding sees it, and changes some of
the values the model carries. A template pack migrating from kibo 1.2 needs both lists, and
the documentation gives them. This measures them, so the documentation cannot drift from kibo.

A probe template, `template_model/model1.stg`, prints every scalar accessor of every class of
Template Model 1, walking the whole model. It is rendered by a kibo 1.2 jar, then migrated by
the renames the documentation lists and rendered by kibo 2, on every model of this laboratory
and for the `python` and `cpp` targets. Each value that differs must be explained by one of
the changes the documentation lists, below in RULES; a value no rule explains fails, and so does
a list whose order changed when no rule says it does.

    template_model.py               measure, and fail on what the documentation does not list
    template_model.py --report      also print every change, grouped by rule
    template_model.py --regenerate  rewrite the probe from kibo 1.2's own Template Model

The kibo 1.2 jar is found as `crossversion.py` finds it; the kibo 2 jar is the newest
`kibo-2.*.jar` of `../kibo/target`. When either is missing this says which, and skips (exit 2).
"""
import argparse
import collections
import re
import subprocess
import tempfile
from pathlib import Path

from crossversion import SIBLINGS, jar as lts_jar, skip

ROOT = Path(__file__).resolve().parent.parent
PROBE = Path(__file__).resolve().parent / "template_model" / "model1.stg"
MODELS = [("features", "features/Features.dsm.json"), ("topology", "namespaces/topology.dsm.json"),
          ("crossing", "crossing/Crossing.dsm.json"), ("service", "service/Service.dsm.json")]
TARGETS = ["python", "cpp"]

# The renames, as the documentation lists them. Applied to the probe's accessor reads only:
# the labels it prints keep their Model 1 names, so the two renders compare line for line.
RENAMES = [("pythonElementType", "bindingElementType"), ("pythonKeyType", "bindingKeyType"),
           ("returnPythonType", "returnBindingType"), ("pythonTupleType", "bindingSequenceType"),
           ("pythonColumnType", "bindingColumnType"), ("pythonType", "bindingType")]
PYTHON_MEMBERS = ("<o.pythonMembers:T_TemplatePythonType()",
                  "<o.members:{x|<T_TemplatePythonType(x.bindingType)>}")

NATIVE = {"type", "typeInNamespace", "elementType", "keyType"}
IN_NAMESPACE = {"membersInNamespace", "strictDescendantsInNamespace"}
BINDING = ("pythonType", "pythonElementType", "pythonKeyType", "returnPythonType",
           "pythonTupleType", "pythonColumnType", "pythonMembers")
CONTAINER = re.compile(r"^(Vector|Set|Map|Optional|XArray|Variant|Tuple|Vec|Mat)\d*(x\d+)?_")


def migrate(text: str) -> str:
    text = text.replace(*PYTHON_MEMBERS)
    for old, new in RENAMES:
        text = re.sub(r"\bo\." + old + r"\b", "o." + new, text)
    return text


def snake(name: str) -> str:
    name = re.sub(r"([a-z0-9])([A-Z])", r"\1_\2", name)
    return re.sub(r"([A-Z]+)([A-Z][a-z])", r"\1_\2", name).lower()


def container_tokens(name: str) -> list[str]:
    tokens = []
    for token in name.split("_"):
        match = re.fullmatch(r"(Vec|Mat)(\d+)(?:x(\d+))?", token)
        if match:
            tokens += [g for g in match.groups() if g]
        elif token not in ("of", "and", "or"):
            tokens.append(token)
    return sorted(tokens)


def leaf(path: str) -> str:
    return path.rsplit(".", 1)[-1]


def binding(path: str) -> bool:
    return any(f".{segment}" in path for segment in BINDING)


def unqualified(representation: str) -> str:
    return re.sub(r"\b\w+::", "", representation)


def native_spelling(value: str, namespaces: set[str], infrastructure: str) -> str:
    for namespace in namespaces:
        value = re.sub(rf"(?<![\w:]){namespace}::", f"{snake(namespace)}::", value)
    return re.sub(r"(?<![\w:])AnyConceptKey", f"::{infrastructure}::AnyConceptKey", value)


# What the documentation lists as changed, one rule per entry. Each takes the path of a value,
# its Model 1 value, its Model 2 value and the render's context, and says whether it explains it.
RULES = {
    "a C++ type names its namespace in snake case, and the untyped key through the infrastructure":
        lambda p, b, a, c: leaf(p) in NATIVE | IN_NAMESPACE and not binding(p)
        and a == native_spelling(b, c["namespaces"], c["infrastructure"]),
    "a parent from another namespace is named with its namespace":
        lambda p, b, a, c: leaf(p) == "parentNameInNamespace"
        and any(a == f"{snake(n)}::{b}" for n in c["namespaces"]),
    "an attachment's representation names a type of another namespace with its namespace":
        lambda p, b, a, c: leaf(p) == "representation" and unqualified(a) == unqualified(b) and a != b
        and re.sub(r"\b\w+::(?=\w+[,>])", "", a) == b,
    "a container class is named after what it holds":
        lambda p, b, a, c: binding(p) and leaf(p) in ("proxy", "type") and bool(CONTAINER.match(b))
        and "_of_" in a and container_tokens(b) == container_tokens(a),
    "a concept's or a club's binding type is its key class":
        lambda p, b, a, c: re.match(r"ns\.(concepts|clubs)\[[^]]*\]\.pythonType\.type$", p) is not None
        and a == b + "Key",
    "an any is a proxy":
        lambda p, b, a, c: binding(p) and ((leaf(p) == "type" and (b, a) == ("dsviper.ValueAny", "Any"))
                                           or (leaf(p) == "useProxy" and (b, a) == ("false", "true")
                                               and c["before"].get(p[:-len("useProxy")] + "type") == "dsviper.ValueAny")),
    "the set of a concept's keys is set<key<Concept>>":
        lambda p, b, a, c: leaf(p) == "dsmType" and re.fullmatch(r"set<(.+)>", b) is not None
        and a == "set<key<" + b[4:-1] + ">>",
    "a C++ set or map whose element or key holds a floating-point value takes Viper::StaticLess":
        lambda p, b, a, c: leaf(p) in NATIVE and not binding(p) and ", Viper::StaticLess" in a
        and a.replace(", Viper::StaticLess", "") in (b, native_spelling(b, c["namespaces"], c["infrastructure"])),
    "a native target has no binding spelling":
        lambda p, b, a, c: c["target"] == "cpp" and binding(p) and a == "",
}

# Lists whose order the documentation says changed. Each takes the list's path, its keys in
# Model 2 order and the Model 2 values, and says whether the new order is the documented one.
def parents_first(path, keys, values):
    def qualified(k):
        return f"{snake(values[f'{path}[{k}].namespace'])}::{values[f'{path}[{k}].name']}"

    def parent(k):
        name = values.get(f"{path}[{k}].parentNameInNamespace", "")
        if not name or "::" in name:
            return name
        return f"{snake(values[f'{path}[{k}].namespace'])}::{name}"

    names = [qualified(k) for k in keys]
    return all(parent(k) not in names[i:] for i, k in enumerate(keys))


def by_native_type(path, keys, values):
    types = [values.get(f"{path}[{k}].type", "") for k in keys]
    return types == sorted(types)


ORDER_RULES = {
    "a namespace lists a parent concept before its children":
        lambda p, k, v: p == "ns.concepts" and parents_first(p, k, v),
    "the container functions are ordered by their C++ type, which names a namespace in snake case":
        lambda p, k, v: p.endswith("Functions") and by_native_type(p, k, v),
}


def parse(text: str) -> tuple[dict[str, str], dict[str, list[str]]]:
    """The probe's tree, flattened: a value per path, and the keys of each list in order."""
    lines = text.splitlines()
    values: dict[str, str] = {}
    orders: dict[str, list[str]] = {}

    def node(i):
        scalars, children = {}, []
        while lines[i] != "}":
            line = lines[i]
            if line.startswith("@"):
                if lines[i + 1].startswith("{"):
                    j, s, c = node(i + 2)
                    children.append((line[1:], (s, c)))
                    i = j
                else:
                    i += 1
                continue
            if line.startswith("["):
                i, items = sequence(i + 1)
                children.append((line[1:], items))
                continue
            if "=" in line:
                k, v = line.split("=", 1)
                scalars[k] = v
            i += 1
        return i + 1, scalars, children

    def sequence(i):
        items = []
        while lines[i] != "]":
            if lines[i].startswith("{"):
                i, s, c = node(i + 1)
                items.append((s, c))
            else:
                i += 1
        return i + 1, items

    def key(scalars, index):
        for k in ("identifier", "typeSuffix"):
            if scalars.get(k):
                return scalars[k]
        if scalars.get("name"):
            return f"{scalars.get('namespace', '')}::{scalars['name']}"
        return f"#{index}"

    def emit(path, scalars, children):
        for k, v in scalars.items():
            values[f"{path}.{k}"] = v
        for name, content in children:
            if isinstance(content, list):
                keys = [key(s, n) for n, (s, _) in enumerate(content)]
                orders[f"{path}.{name}"] = keys
                for k, (s, c) in zip(keys, content):
                    emit(f"{path}.{name}[{k}]", s, c)
            else:
                emit(f"{path}.{name}", *content)

    i = 0
    while i < len(lines):
        if lines[i].startswith("{"):
            i, s, c = node(i + 1)
            emit("m", s, c)
        elif lines[i].startswith("["):
            name = lines[i][1:]
            i, items = sequence(i + 1)
            keys = [key(s, n) for n, (s, _) in enumerate(items)]
            orders[name] = keys
            for k, (s, c) in zip(keys, items):
                emit(f"{name}[{k}]", s, c)
        else:
            i += 1
    return values, orders


def render(kibo: Path, target: str, infrastructure: str, model: Path, templates: Path, out: Path) -> str:
    run = subprocess.run(["java", "-jar", str(kibo), "-c", target, "-n", infrastructure, "-d", str(model),
                          "-t", str(templates), "-o", str(out)], capture_output=True, text=True)
    if run.returncode:
        raise RuntimeError(f"{kibo.name} -c {target} on {model.name}: {run.stderr.strip()}")
    return next(out.iterdir()).read_text()


def kibo2_jar() -> Path | None:
    found = sorted(SIBLINGS.joinpath("kibo", "target").glob("kibo-2.*.jar"))
    return found[-1] if found else None


def regenerate() -> int:
    """Write the probe from the getters of Template Model 1, read in kibo's LTS-1.2 branch."""
    kibo = SIBLINGS / "kibo"
    listing = subprocess.run(["git", "-C", str(kibo), "ls-tree", "-r", "--name-only", "LTS-1.2",
                              "src/main/java/com/digitalsubstrate/template"], capture_output=True, text=True, check=True)
    getters = collections.defaultdict(list)
    for file in listing.stdout.split():
        name = Path(file).stem
        if not re.fullmatch(r"Template[A-Za-z]+", name):
            continue
        source = subprocess.run(["git", "-C", str(kibo), "show", f"LTS-1.2:{file}"],
                                capture_output=True, text=True, check=True).stdout
        for kind, getter in re.findall(r"public ([A-Za-z<>?,. ]+?) ((?:get|is|has)[A-Z]\w*)\(\)", source):
            getters[name].append((getter, kind.strip()))

    def accessor(getter):
        rest = re.sub(r"^(get|is|has)", "", getter)
        return rest[0].lower() + rest[1:]

    scalar = {"String", "Boolean", "boolean"}
    by_name = {"TemplateConcept": "name", "TemplateStructure": "name", "TemplateAttachment": "identifier"}
    nl = "\\n"

    def entry(getter, kind):
        a = accessor(getter)
        if getter == "getPythonMembers":
            return f'[{a}\n<o.{a}:T_TemplatePythonType();separator="{nl}">\n]\n'
        if kind in scalar:
            return f"{a}=<o.{a}>\n"
        if kind.startswith("ArrayList<"):
            element = kind[len("ArrayList<"):-1]
            if element in by_name:
                return f'{a}=<o.{a}:{{x|<x.{by_name[element]}>}};separator=",">\n'
            if element == "TemplateConceptInNamespace":
                return (f'{a}=<o.{a}:{{x|<x.nameInNamespace>/<x.asNameInNamespace>/<x.concept.name>}};'
                        f'separator=",">\n')
            return f'[{a}\n<o.{a}:T_{element}();separator="{nl}">\n]\n'
        if kind in by_name:
            return f"{a}=<o.{a}.{by_name[kind]}>\n"
        return f"@{a}\n<T_{kind}(o.{a})>\n"

    blocks = []
    for name in sorted(getters):
        body = "".join(entry(g, k) for g, k in getters[name]
                       if "DSM" not in k and (name, g) != ("TemplateDefinitions", "getGenerated"))
        blocks.append(f"T_{name}(o) ::= <<\n{{{name}\n{body}}}\n>>\n")
    main = ["main(m) ::= <<", "<T_TemplateDefinitions(m)>"]
    for field, cls in [("concepts", "Concept"), ("clubs", "Club"), ("enumerations", "Enumeration"),
                       ("structures", "Structure"), ("attachments", "Attachment")]:
        main.append(f'[ns.{field}\n<m.nameSpaces:{{ns|<ns.{field}:T_Template{cls}();separator="{nl}">}};'
                    f'separator="{nl}">\n]')
    for field, cls in [("vec", "Vec"), ("mat", "Mat"), ("tuple", "Tuple"), ("optional", "Optional"),
                       ("vector", "Vector"), ("set", "Set"), ("map", "Map"), ("xarray", "XArray"),
                       ("variant", "Variant")]:
        main.append(f'[{field}Functions\n<m.{field}Functions:T_Template{cls}Function();separator="{nl}">\n]')
    main.append(f'[functionPools\n<m.functionPools:T_TemplateFunctionPool();separator="{nl}">\n]')
    main.append(f'[attachmentFunctionPools\n<m.attachmentFunctionPools:T_TemplateAttachmentFunctionPool();'
                f'separator="{nl}">\n]')
    main.append(">>")
    header = ("/* Generated by tools/template_model.py --regenerate from the getters of Template Model 1\n"
              " * (kibo, LTS-1.2). Every scalar accessor of every class, printed as a tree. */\n\n")
    PROBE.write_text(header + "\n".join(main) + "\n\n" + "\n".join(blocks))
    print(f"wrote {PROBE.relative_to(ROOT)}: {sum(map(len, getters.values()))} getters of {len(getters)} classes")
    return 0


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--report", action="store_true", help="print every change, grouped by rule")
    parser.add_argument("--regenerate", action="store_true", help="rewrite the probe from kibo 1.2")
    arguments = parser.parse_args()
    if arguments.regenerate:
        return regenerate()

    kibo1, kibo2 = lts_jar(), kibo2_jar()
    if not kibo1:
        return skip("no kibo 1.2 jar (set KIBO_LTS_JAR, or build kibo on LTS-1.2)")
    if not kibo2:
        return skip("no kibo 2 jar in ../kibo/target")

    probe = PROBE.read_text()
    failures = 0
    explained = collections.defaultdict(list)
    with tempfile.TemporaryDirectory() as scratch:
        work = Path(scratch)
        (work / "t1").mkdir()
        (work / "t2").mkdir()
        (work / "t1" / "probe.stg").write_text(probe)
        (work / "t2" / "probe.stg").write_text(migrate(probe))
        for infrastructure, model in MODELS:
            for target in TARGETS:
                label = f"{infrastructure} -c {target}"
                out = work / label.replace(" ", "_")
                before, before_orders = parse(render(kibo1, target, infrastructure, ROOT / model, work / "t1", out / "1"))
                after, after_orders = parse(render(kibo2, target, infrastructure, ROOT / model, work / "t2", out / "2"))
                context = {"target": target, "infrastructure": infrastructure, "before": before,
                           "namespaces": {v for k, v in before.items() if leaf(k) == "namespace" and v}}
                problems = []
                if set(before) != set(after):
                    for path in sorted(set(before) ^ set(after))[:10]:
                        problems.append(f"read by one kibo only: {path}")
                for path in sorted(set(before) & set(after)):
                    b, a = before[path], after[path]
                    if b == a:
                        continue
                    rule = next((name for name, test in RULES.items() if test(path, b, a, context)), None)
                    if rule:
                        explained[rule].append((label, path, b, a))
                    else:
                        problems.append(f"{path}: {b!r} -> {a!r}")
                for path in sorted(set(before_orders) & set(after_orders)):
                    if before_orders[path] != after_orders[path] and sorted(before_orders[path]) == sorted(after_orders[path]):
                        rule = next((name for name, test in ORDER_RULES.items()
                                     if test(path, after_orders[path], after)), None)
                        if rule:
                            explained[rule].append((label, path, "", ""))
                        else:
                            problems.append(f"order of {path}")
                if problems:
                    failures += 1
                    print(f"FAIL {label}: {len(problems)} change(s) the documentation does not list")
                    for problem in problems[:20]:
                        print(f"       {problem}")
                else:
                    print(f"ok   {label}: {len(before)} values, every change listed")

    if arguments.report:
        for rule, cases in explained.items():
            print(f"\n{len(cases):5}  {rule}")
            for label, path, b, a in cases[:3]:
                print(f"         {label}  {path}: {b!r} -> {a!r}")
    return 1 if failures else 0


if __name__ == "__main__":
    raise SystemExit(main())
