#!/usr/bin/env python3
"""Render the namespace-based templates into `generated/`, and compile the result.

The output is versioned on purpose. A template is only as good as what it produces, and
what it produces has to be readable in a diff from one commit to the next -- otherwise a
change to a template is a change nobody can see.

    render.py            render both models and compile them
    render.py --check    render to a scratch tree and fail if it differs from `generated/`
"""
import argparse, shutil, subprocess, sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parent.parent
sys.path.insert(0, str(ROOT / "tools"))
from render import jar                                    # noqa: E402

TEMPLATES = HERE / "templated"
RUNTIME = ROOT / "runtime"

# The two models, and what each is for. Both are rendered because neither alone reaches
# everything: one carries the namespace topology, the other the type system across it.
MODELS = {
    "Topology": ROOT / "namespaces" / "Topology.dsm.json",
    "Crossing": ROOT / "crossing" / "Crossing.dsm.json",
}

# Hand-written and not generated: the model's own bytes, which a real build embeds from the
# .dsm, and the checkers that compile against the output.
FROM_HAND = ["Topology_Resources.hpp", "use.cpp", "bridge.cpp", "l4.cpp", "l5.cpp",
             "f.cpp", "json.cpp"]


def render(model, definitions, out):
    out.mkdir(parents=True, exist_ok=True)
    r = subprocess.run(["java", "-jar", jar(), "-c", "cpp", "-n", model,
                        "-d", str(definitions), "-t", str(TEMPLATES), "-o", str(out)],
                       capture_output=True, text=True)
    noise = [l for l in r.stderr.splitlines() if l.strip()]
    for l in noise[:8]:
        print(f"  !! {l}")
    return not (r.returncode or noise)


def compile_tree(model, out):
    resources = (ROOT / "namespaces/target/hand/Topology_Resources.hpp").read_text()
    (out / f"{model}_Resources.hpp").write_text(resources.replace("Topology", model))

    if model == "Topology":
        for name in FROM_HAND[1:]:
            shutil.copy(ROOT / "namespaces/target/hand" / name, out / name)

    failed = []
    for source in sorted(out.glob("*.cpp")):
        r = subprocess.run(["clang++", "-std=c++20", "-fsyntax-only", "-I", str(out),
                            "-I", str(RUNTIME), str(source)], capture_output=True, text=True)
        if r.returncode:
            failed.append(source.name)
            print(f"  !! {source.name}")
            for l in r.stderr.splitlines()[:4]:
                print(f"     {l}")
    return failed


parser = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
parser.add_argument("--check", action="store_true",
                    help="fail if `generated/` is not what the templates produce")
arguments = parser.parse_args()

target = HERE / (".check" if arguments.check else "generated")
if target.exists():
    shutil.rmtree(target)

status = 0
for model, definitions in MODELS.items():
    out = target / model
    if not render(model, definitions, out):
        status = 1
        continue

    failed = compile_tree(model, out)
    print(f"  {model:10} {len(list(out.glob('*.cpp'))):3} .cpp, "
          f"{len(list(out.glob('*.hpp'))):3} .hpp"
          + (f", {len(failed)} ne compilent pas" if failed else ", tout compile"))
    status |= bool(failed)

if arguments.check:
    same = subprocess.run(["diff", "-r", str(HERE / "generated"), str(target)],
                          capture_output=True, text=True)
    shutil.rmtree(target)
    if same.returncode:
        print(same.stdout[:2000])
        print("generated/ n'est pas ce que les templates produisent")
        status = 1
    else:
        print("generated/ est à jour")

raise SystemExit(status)
