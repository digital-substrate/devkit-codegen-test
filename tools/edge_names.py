#!/usr/bin/env python3
"""Edge names: what each target does with a name the DSM accepts.

The DSM is a description independent of any language; a name becomes a problem only once a
target spells it. Each case here is one small model built around one name -- a keyword of some
language, a name the pack's own code uses, a primitive's name, a documentation with quotes --
in one family of names (namespace, type, field, enumeration case, attachment, pool, function,
parameter). It is rendered through kibo-project on its own, and each target's output is
judged:

  ok        it generates, and nothing below objects
  explicit  refused, and said so: the C++ compiler, Python's import, tsc
  silent    accepted, and wrong: Python imports it, yet a field masks a method of the proxy,
            a constructor fails on its own names, or `mypy --strict` refuses it
  viper     the DSM itself refuses the name, so no target sees it
  kibo      the generation stops, saying which directive to write

A refused case is rendered again with the directive a project would write, the name spelled
otherwise for that target ([names.<target>.rename]), and judged again: `explicit>ok` is a
target that refuses the name and generates once told how to spell it.

The verdicts are compared with `edge_names.expected`. A change in either direction fails: a
fix is recorded on purpose (`--record`), so that the file always says what the pack does.

    edge_names.py                compare with the expected verdicts
    edge_names.py --record       measure and rewrite the expected verdicts
    edge_names.py --only field   the cases whose name contains this text
    edge_names.py --show         print each case's model and the reason of each verdict

About a hundred of the cases reach the targets, each rendered on its own: several minutes.
Needs dsviper, mypy and a C++ compiler, and the TypeScript tooling installed by a site's
`npm install` (`namespaces/typescript/node_modules`). Without one of them it says what it
skipped. Exit 0 when the verdicts match, 1 when they do not, 2 when nothing could run.
"""
from __future__ import annotations

import argparse
import concurrent.futures
import os
import shutil
import subprocess
import sys
import tempfile
import textwrap
import uuid
from dataclasses import dataclass, field
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from render import KIBO_PROJECT, ROOT                    # noqa: E402

EXPECTED = Path(__file__).resolve().parent / "edge_names.expected"
TARGETS = ("cpp", "python", "typescript")
INFRASTRUCTURE = "bench"
NODE_MODULES = ROOT / "namespaces" / "typescript" / "node_modules"
VIPER = Path(os.environ.get("REPO_VIPER") or ROOT.parent / "com.digitalsubstrate.viper")
FEATURES = {
    "cpp": ["Base", "Attachments", "Pool", "PoolRemote"],
    "python": ["Base", "Pool"],
    "typescript": ["Base", "Pool", "Package"],
}

# ── The cases ───────────────────────────────────────────────────────────────────────────────

KEYWORDS = {
    "a C++ keyword": ["union", "friend", "operator"],
    "a Python keyword": ["def", "lambda", "nonlocal", "async", "await"],
    "a TypeScript keyword": ["function", "let", "typeof"],
    "a keyword of several": ["class", "this", "import"],
}
PACK_PYTHON = ["wrap_value", "unwrap_value", "self", "super", "dict", "isinstance", "dsviper",
               "source", "typing"]
PACK_TYPESCRIPT = ["wrapValue", "unwrapValue", "equals", "compare", "hashKey", "toJSON",
                   "toString", "constructor"]
BINDING = ["type", "copy", "at", "set"]
MODULES = ["Containers", "Definitions", "Resources", "Pools", "Codec"]
PRIMITIVES = ["int64", "uuid", "string", "bool"]
UPPER = ["RGB", "E", "S"]
DOCUMENTATIONS = {
    "quotes": 'the "x" field',
    "backslash": "a path C:\\Users\\x",
    "ending-quote": 'ends with "',
    "comment-end": "a */ inside",
    "single-quotes": "a ''' inside",
}


def _uuid(seed: str) -> str:
    return "{" + str(uuid.uuid5(uuid.NAMESPACE_URL, "edge-names/" + seed)) + "}"


def _namespace(body: str, name: str = "Model", seed: str = "") -> str:
    return f"namespace {name} {_uuid(seed + name)} {{\n{body}\n}};\n"


def _pool(name: str, function: str, parameter: str, seed: str) -> str:
    return (f'"""A pool."""\nfunction_pool {name} {_uuid(seed + name)} {{\n'
            f'"""A function."""\nint64 {function}(int64 {parameter});\n}};\n')


BASE = "concept Thing;\nstruct Item { int64 n; };"


def model(family: str, word: str) -> str:
    """The DSM of one case: the word in one family, and the least around it."""
    seed = f"{family}:{word}"
    if family == "namespace":
        return _namespace(BASE, word, seed)
    if family == "type":
        return _namespace(f"concept Thing;\nstruct {word} {{ int64 n; }};\nstruct Holder {{ {word} w; }};",
                          seed=seed)
    if family == "field":
        return _namespace(f"concept Thing;\nstruct Item {{ int64 {word}; }};", seed=seed)
    if family == "enumeration case":
        return _namespace(f"concept Thing;\nenum Mode {{ {word}, other }};\nstruct Item {{ Mode m; }};",
                          seed=seed)
    if family == "attachment":
        return _namespace(f"{BASE}\nattachment<Thing, Item> {word};", seed=seed)
    if family == "pool":
        return _namespace(BASE, seed=seed) + _pool(word, "f", "a", seed)
    if family == "function":
        return _namespace(BASE, seed=seed) + _pool("Tools", word, "a", seed)
    if family == "parameter":
        return _namespace(BASE, seed=seed) + _pool("Tools", "f", word, seed)
    if family == "documentation":
        text = DOCUMENTATIONS[word]
        return _namespace(f'concept Thing;\nstruct Item {{ """{text}""" int64 n; }};', seed=seed) + (
            f'"""{text}"""\nfunction_pool Tools {_uuid(seed + "Tools")} {{\n'
            f'"""{text}"""\nint64 f(int64 a);\n}};\n')
    if family == "no concept":
        return _namespace("struct Item { int64 n; };\nenum Mode { a, b };", seed=seed)
    raise ValueError(family)


def cases() -> list[tuple[str, str]]:
    families = ("namespace", "type", "field", "enumeration case", "attachment", "pool",
                "function", "parameter")
    out = [(f, w) for words in KEYWORDS.values() for w in words for f in families]
    out += [(f, w) for w in PACK_PYTHON for f in ("field", "enumeration case", "attachment",
                                                   "function", "parameter")]
    out += [(f, w) for w in PACK_TYPESCRIPT for f in ("field", "enumeration case", "attachment",
                                                       "function", "parameter")]
    out += [(f, w) for w in BINDING for f in ("field", "function", "parameter")]
    out += [(f, w) for w in MODULES for f in ("namespace", "pool")]
    out += [("type", w) for w in PRIMITIVES + UPPER]
    out += [("documentation", w) for w in DOCUMENTATIONS]
    out += [("no concept", "types and no concept")]
    return out


def key(family: str, word: str) -> str:
    return f"{family}:{word}"


# ── The judges ──────────────────────────────────────────────────────────────────────────────

@dataclass
class Verdict:
    outcome: str
    reason: str = ""


@dataclass
class Result:
    key: str
    dsm: str
    verdicts: dict[str, Verdict] = field(default_factory=dict)


def _run(command: list[str], cwd: Path, env: dict[str, str] | None = None,
         timeout: int = 300) -> tuple[int, str]:
    r = subprocess.run(command, cwd=cwd, capture_output=True, text=True, timeout=timeout,
                       env={**os.environ, **(env or {})})
    return r.returncode, (r.stdout + r.stderr).strip()


def _first(text: str, *needles: str) -> str:
    """The first line of a tool's output that names the problem."""
    lines = [l.strip() for l in text.splitlines() if l.strip()]
    for needle in needles:
        for l in lines:
            if needle in l:
                return l[:200]
    return (lines[-1] if lines else "")[:200]


def viper_refusal(dsm: str) -> str:
    import dsviper
    builder = dsviper.DSMBuilder()
    builder.append("model.dsm", dsm)
    report = builder.parse()[0]
    return report.errors()[0].message() if report.has_error() else ""


def judge_cpp(out: Path) -> Verdict:
    sources = sorted(out.glob("*.cpp"))
    if not sources:
        return Verdict("ok", "nothing rendered")
    includes = [out, VIPER / "src" / "Viper"] + [VIPER / "third_parties" / d for d in
                                                 ("antlr4", "hash", "json", "xml/pugixml", "sqlite")]
    flags = ["-std=gnu++17", "-fsyntax-only", "-Wno-c++2b-extensions",
             "-Wno-deprecated-declarations", "-DANTLR4CPP_STATIC"]
    for source in sources:
        code, text = _run(["c++", *flags, *[f"-I{i}" for i in includes], str(source)], out)
        if code:
            return Verdict("explicit", f"{source.name}: {_first(text, 'error:')}")
    return Verdict("ok")


PYTHON_PROBE = textwrap.dedent("""
    import importlib, inspect, pkgutil, sys
    package = importlib.import_module(sys.argv[1])
    modules = [package] + [importlib.import_module(m.name)
                           for m in pkgutil.walk_packages(package.__path__, package.__name__ + ".")]
    problems = []
    for module in modules:
        for name, cls in vars(module).items():
            if not inspect.isclass(cls) or cls.__module__ != module.__name__:
                continue
            for base in cls.__mro__[1:]:
                if base is object:
                    continue
                for member, value in vars(cls).items():
                    if member.startswith("_") or member not in vars(base):
                        continue
                    if isinstance(value, property) and not isinstance(vars(base)[member], property):
                        problems.append(f"{cls.__name__}.{member} masks {base.__name__}.{member}")
            if "ValueStructure" in str(getattr(cls, "__orig_bases__", "")):
                try:
                    instance = cls()
                    for member, value in vars(cls).items():
                        if isinstance(value, property):
                            getattr(instance, member)
                except Exception as error:
                    problems.append(f"{cls.__name__}(): {type(error).__name__}: {error}")
    print("\\n".join(problems))
    sys.exit(1 if problems else 0)
""")


def judge_python(out: Path, work: Path) -> Verdict:
    package = out / INFRASTRUCTURE
    if not package.is_dir():
        return Verdict("ok", "nothing rendered")
    env = {"PYTHONPATH": str(out)}
    probe = work / "probe.py"
    probe.write_text(PYTHON_PROBE)
    code, text = _run([sys.executable, "-W", "error::SyntaxWarning", "-c",
                       f"import importlib, pkgutil, {INFRASTRUCTURE} as p\n"
                       "[importlib.import_module(m.name) for m in "
                       "pkgutil.walk_packages(p.__path__, p.__name__ + '.')]"], out, env)
    if code:
        return Verdict("explicit", _first(text, "Error", "Warning"))
    code, text = _run([sys.executable, str(probe), INFRASTRUCTURE], out, env)
    if code:
        return Verdict("silent", _first(text, "masks", "()"))
    code, text = _run([sys.executable, "-m", "mypy", "--strict", "--no-incremental",
                       "--cache-dir", os.devnull, INFRASTRUCTURE], out)
    if code:
        return Verdict("silent", "mypy: " + _first(text, "error:"))
    return Verdict("ok")


def judge_typescript(out: Path) -> Verdict:
    config = out / "tsconfig.json"
    if not config.is_file():
        return Verdict("ok", "nothing rendered")
    (out / "node_modules").symlink_to(NODE_MODULES)
    code, text = _run([str(NODE_MODULES / ".bin" / "tsc"), "-p", str(config)], out)
    if code:
        return Verdict("explicit", "tsc: " + _first(text, "error"))
    entries = sorted((out / "dist").rglob("*.js"))
    script = "".join(f"await import({str(p)!r});\n" for p in entries)
    code, text = _run(["node", "--input-type=module", "-e", script], out)
    if code:
        return Verdict("explicit", "node: " + _first(text, "Error"))
    return Verdict("ok")


JUDGES = {"cpp": lambda out, work: judge_cpp(out), "python": judge_python,
          "typescript": lambda out, work: judge_typescript(out)}


def render(dsm: str, target: str, keep: Path | None, rename: str | None = None) -> Verdict:
    """One target, rendered on its own -- a refusal for one does not hide the others -- and
    judged; with `rename`, the case's name is spelled otherwise for that target, as a project
    corrects what it is told."""
    work = Path(tempfile.mkdtemp(prefix=f"edge-{target}-", dir=keep)).resolve()
    try:
        (work / "definitions").mkdir()
        (work / "definitions" / "model.dsm").write_text(dsm)
        # The bench judges each target itself, so kibo-project's own validation is off.
        lines = ["[project]", 'definitions = "definitions"', f'infrastructure = "{INFRASTRUCTURE}"',
                 "[generator]", 'templates = "2"',
                 f"[target.{target}]", f"features = {FEATURES[target]!r}".replace("'", '"'),
                 f'output = "{target}"', "validate = false"]
        if rename:
            lines += [f"[names.{target}.rename]", f'"{rename}" = "{rename}X"']
        (work / "kibo.toml").write_text("\n".join(lines) + "\n")
        # A short-lived JVM, which these options keep from spending its time compiling itself.
        code, text = _run([sys.executable, str(KIBO_PROJECT), "generate"], work,
                          {"JAVA_TOOL_OPTIONS": "-XX:TieredStopAtLevel=1 -XX:+UseSerialGC"})
        verdict = Verdict("kibo", _first(text, "error", "Error", "written")) if code \
            else JUDGES[target](work / target, work)
        verdict.reason = verdict.reason.replace(str(work) + "/", "")
        return verdict
    finally:
        if keep is None:
            shutil.rmtree(work, ignore_errors=True)


def measure(family: str, word: str, keep: Path | None = None) -> Result:
    dsm = model(family, word)
    result = Result(key(family, word), dsm)
    refused = viper_refusal(dsm)
    if refused:
        result.verdicts = {t: Verdict("viper", refused) for t in TARGETS}
        return result
    for target in TARGETS:
        verdict = render(dsm, target, keep)
        # A refusal -- by a compiler, a validation or kibo -- is corrected by the project with a
        # directive; the case must then generate and pass. Recorded as `refused>adapted`.
        if verdict.outcome in ("explicit", "kibo", "silent") and family not in ("documentation", "no concept"):
            adapted = render(dsm, target, keep, rename=word)
            verdict = Verdict(f"{verdict.outcome}>{adapted.outcome}",
                              verdict.reason + (f" | adapted: {adapted.reason}" if adapted.reason else ""))
        result.verdicts[target] = verdict
    return result


# ── The expected verdicts ───────────────────────────────────────────────────────────────────

def read_expected() -> dict[str, dict[str, str]]:
    expected: dict[str, dict[str, str]] = {}
    if not EXPECTED.is_file():
        return expected
    for line in EXPECTED.read_text().splitlines():
        line = line.split("#", 1)[0].rstrip()
        if not line:
            continue
        name, _, rest = line.partition("  ")
        expected[name.strip()] = dict(part.split("=", 1) for part in rest.split())
    return expected


HEADER = """\
# The verdict of each edge-names case, per target, as `tools/edge_names.py --record` measured
# it with the pack and the runtime at hand. Rewritten on purpose when a fix changes a verdict;
# a line's comment says which defect it is. Outcomes: ok, explicit, silent, viper, kibo.
"""


def write_expected(results: list[Result], notes: dict[str, str]) -> None:
    width = max(len(r.key) for r in results) + 2
    lines = [HEADER]
    for r in results:
        verdicts = "  ".join(f"{t}={r.verdicts[t].outcome:8}" for t in TARGETS).rstrip()
        note = f"  # {notes[r.key]}" if r.key in notes else ""
        lines.append(f"{r.key:{width}}{verdicts}{note}")
    EXPECTED.write_text("\n".join(lines) + "\n")


def read_notes() -> dict[str, str]:
    notes = {}
    if EXPECTED.is_file():
        for line in EXPECTED.read_text().splitlines():
            if "#" in line and not line.startswith("#"):
                name = line.split("  ", 1)[0].strip()
                notes[name] = line.split("#", 1)[1].strip()
    return notes


# ── Main ────────────────────────────────────────────────────────────────────────────────────

def missing_tools() -> list[str]:
    missing = []
    if shutil.which("c++") is None:
        missing.append("a C++ compiler")
    if not (VIPER / "src" / "Viper").is_dir():
        missing.append(f"viper's sources ({VIPER})")
    if not (NODE_MODULES / ".bin" / "tsc").exists():
        missing.append(f"tsc ({NODE_MODULES}: run npm install there)")
    if subprocess.run([sys.executable, "-m", "mypy", "--version"], capture_output=True).returncode:
        missing.append("mypy")
    try:
        import dsviper  # noqa: F401
    except ImportError:
        missing.append("dsviper")
    return missing


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--record", action="store_true", help="rewrite the expected verdicts")
    parser.add_argument("--only", help="the cases whose name contains this text")
    parser.add_argument("--show", action="store_true", help="each model, each reason")
    parser.add_argument("--keep", type=Path, help="keep each case's rendering under this directory")
    parser.add_argument("-j", "--jobs", type=int, default=os.cpu_count() or 4)
    arguments = parser.parse_args()

    missing = missing_tools()
    if missing:
        print(f"skipped: no {', no '.join(missing)}")
        return 2
    selected = [c for c in cases() if not arguments.only or arguments.only in key(*c)]
    if arguments.record and arguments.only:
        parser.error("--record measures every case")
    if arguments.keep:
        arguments.keep.mkdir(parents=True, exist_ok=True)

    with concurrent.futures.ThreadPoolExecutor(arguments.jobs) as pool:
        results = list(pool.map(lambda c: measure(*c, keep=arguments.keep), selected))

    if arguments.record:
        write_expected(results, read_notes())
        counts: dict[str, int] = {}
        for r in results:
            for v in r.verdicts.values():
                counts[v.outcome] = counts.get(v.outcome, 0) + 1
        print(f"recorded {len(results)} cases: " +
              ", ".join(f"{n} {o}" for o, n in sorted(counts.items())))
        return 0

    expected = read_expected()
    differences = 0
    for r in results:
        want = expected.get(r.key)
        got = {t: v.outcome for t, v in r.verdicts.items()}
        if want != got:
            differences += 1
            print(f"FAIL {r.key}: expected {want or 'nothing'}, measured {got}")
            for t, v in r.verdicts.items():
                if v.reason:
                    print(f"       {t}: {v.reason}")
        elif arguments.show:
            print(f"ok   {r.key}: {got}")
            for t, v in r.verdicts.items():
                if v.reason:
                    print(f"       {t}: {v.reason}")
        if arguments.show:
            print(textwrap.indent(r.dsm.rstrip(), "       | "))
    if differences:
        print(f"{differences} of {len(results)} cases differ from {EXPECTED.name}")
        return 1
    print(f"ok   {len(results)} edge-name cases, every verdict as expected")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
