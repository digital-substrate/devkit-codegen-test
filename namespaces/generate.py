#!/usr/bin/env python3
"""Render this model into the working tree, the way the other models' drivers do.

For comparing a change -- rendering before and after without touching the working
tree -- use `tools/render.py` instead.
"""
import argparse, subprocess, sys
from pathlib import Path

from dsviper import DSMBuilder

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "tools"))
from models import MODELS
from render import jar, TEMPLATES

HERE = Path(__file__).resolve().parent
SPEC = MODELS["namespaces"]

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("-c", "--cpp", action="store_true", help="Generate C++")
parser.add_argument("-p", "--python", action="store_true", help="Generate the Python package")
parser.add_argument("-t", "--typescript", action="store_true", help="Generate the TypeScript package")
arguments = parser.parse_args()

if not (arguments.cpp or arguments.python or arguments.typescript):
    parser.print_help()
    raise SystemExit(0)

report, dsm, _ = DSMBuilder.assemble(str(HERE / "definitions")).parse()
if report.has_error():
    for e in report.errors():
        print(repr(e))
    raise SystemExit(1)

DSM_PATH = HERE / f'{SPEC["namespace"]}.dsm.json'
DSM_PATH.write_text(dsm.json_encode())

JAR = jar()
print(f"using kibo: {Path(JAR).name}")


def kibo(target, template, output):
    Path(output).mkdir(parents=True, exist_ok=True)
    subprocess.run(["java", "-jar", JAR, "-c", target, "-n", SPEC["namespace"] if target == "cpp" else SPEC["package"],
                    "-d", str(DSM_PATH), "-t", str(template), "-o", str(output)])


if arguments.cpp:
    print("** Render C++")
    for feature in SPEC["cpp"]:
        kibo("cpp", TEMPLATES / "cpp" / feature, HERE / SPEC["namespace"])

if arguments.python:
    print("** Render Python Package")
    kibo("python", TEMPLATES / "python/package", HERE / "python" / SPEC["package"])

if arguments.typescript:
    print("** Render TypeScript Package")
    kibo("typescript", TEMPLATES / "typescript", HERE / "typescript" / SPEC["package"] / "src")
