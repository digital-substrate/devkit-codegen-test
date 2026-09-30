#!/usr/bin/env python3
"""Rendre le modèle figé, pour relire la base 1.2 avec ce que la génération produit aujourd'hui.

Seul le C++ est rendu pour l'instant ; -p et -t sont acceptés, pour que `check.py` passe le
même appel à tous les sites, et disent qu'il n'y a encore rien à rendre.
"""
import argparse, subprocess, sys
from pathlib import Path

from dsviper import DSMBuilder

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "tools"))
from models import MODELS
from render import jar, TEMPLATES

HERE = Path(__file__).resolve().parent
SPEC = MODELS["compat-1.2"]

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("-c", "--cpp", action="store_true", help="Generate C++")
parser.add_argument("-p", "--python", action="store_true", help="(pas encore)")
parser.add_argument("-t", "--typescript", action="store_true", help="(pas encore)")
arguments = parser.parse_args()

report, dsm, definitions = DSMBuilder.assemble(str(HERE / "definitions")).parse()
if report.has_error():
    for e in report.errors():
        print(repr(e))
    raise SystemExit(1)

DSM_PATH = HERE / f'{SPEC["namespace"]}.dsm.json'
DSM_PATH.write_text(dsm.json_encode())

sys.path.insert(0, str(TEMPLATES))
import resolve                                                          # noqa: E402

CPP_OUT = HERE / "cpp" / "generated"


def resources_hpp():
    """Le modèle, en octets, dans `<Namespace>_resources_definitions` -- ce que les templates attendent."""
    octets = bytes(definitions.encode().encoded())
    lignes = [", ".join(f"0x{b:02x}" for b in octets[i:i + 12]) for i in range(0, len(octets), 12)]
    ns = SPEC["namespace"]
    (CPP_OUT / f"{ns}_resources.hpp").write_text(
        f"#ifndef {ns}_resources_hpp\n#define {ns}_resources_hpp\n\n#include <cstddef>\n\n"
        f"inline constexpr unsigned char {ns}_resources_definitions[] = {{\n "
        + ",\n ".join(lignes) + f"\n}};\n\n#endif\n")


if arguments.cpp:
    print("** Render C++")
    JAR = jar()
    print(f"using kibo: {Path(JAR).name}")
    CPP_OUT.mkdir(parents=True, exist_ok=True)
    for stg in resolve.templates("cpp", SPEC["cpp"]):
        subprocess.run(["java", "-jar", JAR, "-c", "cpp", "-n", SPEC["namespace"],
                        "-d", str(DSM_PATH), "-t", str(stg), "-o", str(CPP_OUT)], check=True)
    resources_hpp()

for langage, voulu in (("python", arguments.python), ("typescript", arguments.typescript)):
    if voulu:
        print(f"** {langage} : pas encore -- la relecture commence par le C++")
