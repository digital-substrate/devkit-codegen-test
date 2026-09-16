#!/usr/bin/env python3
"""Compiler et exécuter la référence Node.

DEUX ÉPREUVES ET NON UNE. `tsc --strict` dit que les annotations tiennent ; il ne dit pas
qu'un attachment écrit ni qu'une base relit. Le C++ a un compilateur et un lien, Python a
l'import et pyright ; Node a les deux d'un coup, et il faut les deux.
"""
import json
import shutil
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
TARGET = HERE.parent
ROOT = TARGET.parents[1]

# La liaison n'est pas publiée avec ce qui suit ; le paquet le reçoit comme en Python.
PROPOSED = TARGET / "runtime-proposed" / "node"

# LA BOÎTE À OUTILS EST CELLE D'UN PROJET EXISTANT. `tsc` et la liaison sont installés dans
# `features/typescript/node_modules` ; les réinstaller ici ne prouverait rien de plus et
# ajouterait un arbre de dépendances à tenir.
TOOLING = ROOT / "features" / "typescript" / "node_modules"
BINDING = ROOT.parent / "com.digitalsubstrate.viper" / "dsviper_node"


def prepare(package: Path) -> None:
    codegen = package / "src" / "_codegen"
    codegen.mkdir(parents=True, exist_ok=True)
    for module in PROPOSED.glob("*.ts"):
        shutil.copy(module, codegen)

    link = package / "node_modules" / "@digitalsubstrate"
    link.mkdir(parents=True, exist_ok=True)
    if not (link / "dsviper").exists():
        (link / "dsviper").symlink_to(BINDING)


def run(package: Path) -> int:
    prepare(package)
    tsc = TOOLING / ".bin" / "tsc"
    if not tsc.exists():
        print(f"  {'Node':11} tsc absent, non vérifié")
        return 0

    r = subprocess.run([str(tsc), "-p", "tsconfig.json"], cwd=package,
                       capture_output=True, text=True)
    errors = [l for l in (r.stdout + r.stderr).splitlines() if l.strip()]
    print(f"  {'types':11} {len(errors):3} erreur(s) de typage"
          + ("" if errors else " — les annotations tiennent"))
    for line in errors[:5]:
        print(f"     {line}")
    if errors:
        return 1

    r = subprocess.run(["node", "dist/check.js"], cwd=package, capture_output=True, text=True)
    passed = sum(1 for line in r.stdout.splitlines() if line.startswith("  ok"))
    print(f"  {'épreuve':11} {passed:3} assertions, "
          + ("toutes passent" if r.returncode == 0 else "ÉCHEC"))
    for line in r.stdout.splitlines():
        if "ÉCHEC" in line:
            print(f"     {line.strip()}")
    return r.returncode


raise SystemExit(run(Path(sys.argv[1]).resolve() if len(sys.argv) > 1 else HERE / "hand"))
