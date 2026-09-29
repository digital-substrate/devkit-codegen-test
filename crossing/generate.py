#!/usr/bin/env python3
"""Render this model into the working tree, the way the other models' drivers do.

For comparing a change -- rendering before and after without touching the working
tree -- use `tools/render.py` instead.
"""
import argparse, base64, json, shutil, subprocess, sys, zlib
from pathlib import Path

from dsviper import DSMBuilder

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "tools"))
from models import MODELS
from render import jar, TEMPLATES

HERE = Path(__file__).resolve().parent
SPEC = MODELS["crossing"]

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("-c", "--cpp", action="store_true", help="Generate C++")
parser.add_argument("-p", "--python", action="store_true", help="Generate the Python package")
parser.add_argument("-t", "--typescript", action="store_true", help="Generate the TypeScript package")
arguments = parser.parse_args()

if not (arguments.cpp or arguments.python or arguments.typescript):
    parser.print_help()
    raise SystemExit(0)

report, dsm, definitions = DSMBuilder.assemble(str(HERE / "definitions")).parse()
if report.has_error():
    for e in report.errors():
        print(repr(e))
    raise SystemExit(1)

DSM_PATH = HERE / f'{SPEC["namespace"]}.dsm.json'
DSM_PATH.write_text(dsm.json_encode())

JAR = jar()
print(f"using kibo: {Path(JAR).name}")


# LA SÉLECTION EST UNE FEATURE, PAS UN DOSSIER. `templates/features.json` dit quels `.stg`
# chacune demande et ce qu'elle entraîne ; `resolve` calcule la clôture. `kibo -t` prend un
# `.stg` seul aussi bien qu'un dossier, donc les templates restent à plat.
sys.path.insert(0, str(TEMPLATES))
import resolve                                                          # noqa: E402

RUNTIME = HERE.parent / "runtime-proposed"
# Les typages Node vivent dans le node_modules du site : le paquet généré est compilé là
# où ses dépendances sont installées.
NODE_TYPES = HERE / "typescript" / "node_modules" / "@types"

TSCONFIG = {
    "compilerOptions": {
        "target": "ES2022", "module": "NodeNext", "moduleResolution": "NodeNext",
        "declaration": True, "strict": True, "esModuleInterop": True, "skipLibCheck": True,
        "outDir": "dist", "rootDir": "src",
        "typeRoots": [str(NODE_TYPES)], "types": ["node"],
    },
    "include": ["src/**/*.ts"],
}
CPP_OUT = HERE / "cpp" / "generated"
PY_PROJECT = HERE / "python" / "generated"          # ce que `pip install` reçoit
PY_PACKAGE = PY_PROJECT / SPEC["package"]           # ce que `import` trouve
TS_SOURCE = HERE / "typescript" / "generated" / "src"


def kibo(target, stgs, output):
    Path(output).mkdir(parents=True, exist_ok=True)
    for stg in stgs:
        subprocess.run(["java", "-jar", JAR, "-c", target,
                        "-n", SPEC["namespace"] if target == "cpp" else SPEC["package"],
                        "-d", str(DSM_PATH), "-t", str(stg), "-o", str(output)])


def resources_hpp():
    """Le modèle, en octets, dans `<Namespace>_Resources_definitions` -- ce que les templates attendent."""
    octets = bytes(definitions.encode().encoded())
    lignes = [", ".join(f"0x{b:02x}" for b in octets[i:i + 12]) for i in range(0, len(octets), 12)]
    ns = SPEC["namespace"]
    (CPP_OUT / f"{ns}_Resources.hpp").write_text(
        f"#ifndef {ns}_Resources_hpp\n#define {ns}_Resources_hpp\n\n#include <cstddef>\n\n"
        f"inline constexpr unsigned char {ns}_Resources_definitions[] = {{\n "
        + ",\n ".join(lignes) + f"\n}};\n\n#endif\n")


if arguments.cpp:
    print("** Render C++")
    kibo("cpp", resolve.templates("cpp", SPEC["cpp"]), CPP_OUT)
    resources_hpp()

if arguments.python:
    print("** Render Python Package")
    base = resolve.templates("python", ["Base", "Pool"])
    kibo("python", base, PY_PACKAGE)
    # La roue n'atterrit pas au même endroit : py.typed dans le paquet, pyproject.toml un cran
    # au-dessus. Sans py.typed, toutes les annotations sont invisibles au consommateur.
    for stg in resolve.templates("python", ["Wheel"]):
        if stg not in base:
            kibo("python", [stg], PY_PACKAGE if stg.name.startswith("py.typed") else PY_PROJECT)
    (PY_PACKAGE / "resources.py").write_text(
        f"B64_DEFINITIONS = {base64.b64encode(zlib.compress(definitions.encode()))}")
    shutil.rmtree(PY_PACKAGE / "_codegen", ignore_errors=True)
    shutil.copytree(RUNTIME / "python", PY_PACKAGE / "_codegen",
                    ignore=shutil.ignore_patterns("__pycache__", "*.md"))

if arguments.typescript:
    print("** Render TypeScript Package")
    kibo("typescript", resolve.templates("typescript", ["Base", "Pool"]), TS_SOURCE)
    (TS_SOURCE / "resources.ts").write_text(
        f'export const B64_DEFINITIONS = "{base64.b64encode(definitions.encode().encoded()).decode("ascii")}";\n')
    shutil.rmtree(TS_SOURCE / "_codegen", ignore_errors=True)
    shutil.copytree(RUNTIME / "node", TS_SOURCE / "_codegen", ignore=shutil.ignore_patterns("*.md"))
    # Le calage du projet. Pas de template pour ça : `templates/typescript` n'a pas de feature
    # `Project`, contrairement au pack. Écrit ici en attendant, et c'est une dette.
    (TS_SOURCE.parent / "package.json").write_text(json.dumps(
        {"name": SPEC["package"], "private": True, "type": "module"}, indent=4) + "\n")
    (TS_SOURCE.parent / "tsconfig.json").write_text(json.dumps(TSCONFIG, indent=4) + "\n")
