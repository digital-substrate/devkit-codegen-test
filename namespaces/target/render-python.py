#!/usr/bin/env python3
"""Rendre les quatre modèles en Python, et importer ce qui sort.

LE C++ EST VÉRIFIÉ PAR UN COMPILATEUR ; PYTHON N'EN A PAS. Ce qui en tient lieu est
l'import : un module qui s'importe a une syntaxe valable, ses dépendances résolues, ses
classes construites et ses descripteurs de type trouvés dans les définitions embarquées.
C'est moins qu'un compilateur et beaucoup plus qu'une lecture.

    render-python.py            rend, écrit dans generated/python/, importe tout
    render-python.py --check    échoue si generated/python/ n'est pas à jour
"""
import argparse
import shutil
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]

# IMPORTÉS PAR LEUR CHEMIN, ET NON PAR LEUR NOM. `tools/render.py` et le `render.py` d'à
# côté portent le même nom ; le répertoire du script passe en premier dans `sys.path`, donc
# `import render` prendrait le voisin et non celui qu'on veut.
import importlib.util                                              # noqa: E402


def _module(path, name):
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


sys.path.insert(0, str(ROOT / "tools"))
jar = _module(ROOT / "tools" / "render.py", "kibo_tools_render").jar
MODELS = _module(ROOT / "tools" / "models.py", "kibo_tools_models").MODELS

TEMPLATES = HERE / "python" / "templated"
RESOURCES = HERE / "link" / "resources"

# CE QUE `dsviper` NE PORTE PAS ENCORE, copié dans chaque paquet. Le pendant exact des deux
# en-têtes de `runtime-proposed/` du côté C++ : aucun ne nomme un type d'un modèle, aucun ne
# varie d'un modèle à l'autre, et le jour où la liaison les portera le code généré les
# importera au lieu de les recevoir.
PROPOSED = ROOT / "runtime-proposed" / "dsviper"

arguments = argparse.ArgumentParser(description=__doc__,
    formatter_class=argparse.RawDescriptionHelpFormatter)
arguments.add_argument("--check", action="store_true",
                       help="échouer si generated/python/ n'est pas à jour")
arguments = arguments.parse_args()

target = HERE / (".check-python" if arguments.check else "generated/python")
if target.exists():
    shutil.rmtree(target)

status = 0
for model, spec in MODELS.items():
    namespace = spec["namespace"]
    definitions = ROOT / model / f"{namespace}.dsm.json"
    package = target / namespace.lower()

    r = subprocess.run(["java", "-jar", jar(), "-c", "python", "-n", namespace,
                        "-d", str(definitions), "-t", str(TEMPLATES), "-o", str(package)],
                       capture_output=True, text=True)
    noise = [l for l in r.stderr.splitlines() if l.strip()]
    for line in noise[:8]:
        print(f"  !! {line}")
    if r.returncode or noise:
        status = 1
        continue

    # Ce qui ne sort pas des templates : les octets du modèle, et le runtime qui manque.
    shutil.copy(RESOURCES / f"{namespace}_resources.py", package / "resources.py")
    for proposed in PROPOSED.glob("_*.py"):
        shutil.copy(proposed, package)

    modules = sorted(p.relative_to(target).with_suffix("") for p in package.rglob("*.py"))
    names = [".".join(m.parts[:-1] if m.parts[-1] == "__init__" else m.parts) for m in modules]

    r = subprocess.run(
        [sys.executable, "-c",
         "import sys\n"
         "sys.path.insert(0, sys.argv[1])\n"
         "for name in sys.argv[2:]:\n"
         "    __import__(name)\n",
         str(target), *names],
        capture_output=True, text=True)

    ok = "tous les modules s'importent" if r.returncode == 0 else "L'IMPORT ÉCHOUE"
    print(f"  {namespace:11} {len(names):3} modules, {ok}")
    if r.returncode:
        status = 1
        for line in r.stderr.strip().splitlines()[-3:]:
            print(f"     {line}")

# ET LES MÊMES ASSERTIONS QUE LA RÉFÉRENCE ÉCRITE À LA MAIN. Un module qui s'importe n'est
# pas un module qui marche : l'import ne dit rien de ce qu'un attachment écrit ni de ce qu'une
# base relit. La référence dit ce qu'on veut, le rendu dit ce qu'on obtient, et c'est la même
# épreuve qui passe sur les deux ou ne référence rien.
if not arguments.check and status == 0:
    r = subprocess.run([sys.executable, str(HERE / "python" / "check.py"), str(target)],
                       capture_output=True, text=True)
    passed = sum(1 for line in r.stdout.splitlines() if line.startswith("  ok"))
    print(f"  {'épreuve':11} {passed:3} assertions sur le rendu, "
          + ("toutes passent" if r.returncode == 0 else "ÉCHEC"))
    if r.returncode:
        for line in r.stdout.splitlines():
            if "ÉCHEC" in line:
                print(f"     {line.strip()}")
        status = 1

if arguments.check:
    # LES BYTECODES NE SONT PAS DU RENDU. Importer un paquet en écrit un à côté de chaque
    # module ; les comparer ferait échouer la vérification sur la date de la dernière lecture.
    same = subprocess.run(["diff", "-r", "-x", "__pycache__",
                           str(HERE / "generated/python"), str(target)],
                          capture_output=True, text=True)
    print(same.stdout.strip() or "generated/python/ est à jour")
    shutil.rmtree(target)
    status |= 1 if same.returncode else 0

raise SystemExit(status)
