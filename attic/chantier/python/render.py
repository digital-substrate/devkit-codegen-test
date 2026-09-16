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
import json
import os
import shutil
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent.parent
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

resolve = _module(ROOT / "templates" / "resolve.py", "kibo_templates_resolve")
# LA SÉLECTION EST UNE FEATURE, PAS UN DOSSIER. `features.json` dit quels `.stg` une
# feature demande et ce qu'elle entraîne ; `kibo -t` prend un fichier aussi bien qu'un
# dossier, donc les templates restent à plat.
TEMPLATES = resolve.templates("python", ["Base", "Pool"])
# LA ROUE EST RENDUE À PART, parce qu'elle n'atterrit pas au même endroit : `py.typed` va
# dans le paquet, `pyproject.toml` un cran au-dessus, à la racine du projet. Quatre modèles
# donnent quatre projets ; un `pyproject.toml` commun les écraserait l'un l'autre.
WHEEL = [s for s in resolve.templates("python", ["Wheel"]) if s not in TEMPLATES]
RESOURCES = HERE / "cpp" / "link" / "resources"

# CE QUE LA LIAISON DEVRAIT PORTER ET NE PORTE PAS. Aucun de ces modules ne nomme un type
# d'un modèle et aucun ne varie d'un modèle à l'autre : leur place est dans `dsviper`, sous
# `dsviper.codegen`. En attendant, ils sont déposés dans chaque paquet rendu sous `_codegen`,
# et le code généré écrit `from .._codegen import …`. Le jour où la liaison les portera, ce
# sera `from dsviper.codegen import …` : une ligne dans chacun des trois templates.
PROPOSED = HERE / "runtime-proposed" / "python"

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
    project = target / namespace.lower()          # ce que `pip install` reçoit
    package = project / namespace.lower()         # ce que `import` trouve

    noise = []
    echec = False
    for stg in TEMPLATES:
        r = subprocess.run(["java", "-jar", jar(), "-c", "python", "-n", namespace,
                            "-d", str(definitions), "-t", str(stg), "-o", str(package)],
                           capture_output=True, text=True)
        noise += [l for l in r.stderr.splitlines() if l.strip()]
        echec = echec or bool(r.returncode)
    for stg in WHEEL:
        sortie = package if stg.name.startswith("py.typed") else project
        r = subprocess.run(["java", "-jar", jar(), "-c", "python", "-n", namespace,
                            "-d", str(definitions), "-t", str(stg), "-o", str(sortie)],
                           capture_output=True, text=True)
        noise += [l for l in r.stderr.splitlines() if l.strip()]
        echec = echec or bool(r.returncode)
    for line in noise[:8]:
        print(f"  !! {line}")
    if echec or noise:
        status = 1
        continue

    # Ce qui ne sort pas des templates : les octets du modèle, et le paquet que la liaison
    # devrait porter.
    shutil.copy(RESOURCES / f"{namespace}_resources.py", package / "resources.py")
    shutil.copytree(PROPOSED, package / "_codegen",
                    ignore=shutil.ignore_patterns("__pycache__", "README.md"))

    modules = sorted(p.relative_to(project).with_suffix("") for p in package.rglob("*.py"))
    names = [".".join(m.parts[:-1] if m.parts[-1] == "__init__" else m.parts) for m in modules]

    r = subprocess.run(
        [sys.executable, "-c",
         "import sys\n"
         "sys.path.insert(0, sys.argv[1])\n"
         "for name in sys.argv[2:]:\n"
         "    __import__(name)\n",
         str(project), *names],
        capture_output=True, text=True)

    ok = "tous les modules s'importent" if r.returncode == 0 else "L'IMPORT ÉCHOUE"
    print(f"  {namespace:11} {len(names):3} modules, {ok}")
    if r.returncode:
        status = 1
        for line in r.stderr.strip().splitlines()[-3:]:
            print(f"     {line}")

# ET CE QU'UN VÉRIFICATEUR DE TYPES EN DIT. C'est l'équivalent le plus proche du compilateur
# que le C++ a : il lit les annotations et refuse ce qui ne s'accorde pas. Sans lui, écrire
# `typing.Any` partout passerait pour du typage -- `Any` accepte toute affectation, donc un
# champ de couleurs prendrait un entier sans un mot, et rien ne le dirait.
def typecheck(package):
    if shutil.which("pyright") is None:
        print(f"  {'types':11} pyright absent, non vérifié")
        return 0

    configuration = package / "pyrightconfig.json"
    configuration.write_text(json.dumps({
        "include": ["."],
        "extraPaths": [*(str(p) for p in sorted(package.iterdir()) if p.is_dir()),
                       str(ROOT.parent / "com.digitalsubstrate.viper" / "dsviper_wheel")],
        "typeCheckingMode": "standard",
    }))
    r = subprocess.run(["pyright", "--outputjson"], cwd=package, capture_output=True, text=True)
    configuration.unlink()

    try:
        diagnostics = json.loads(r.stdout)["generalDiagnostics"]
    except (ValueError, KeyError):
        print(f"  {'types':11} pyright n'a rien rendu d'exploitable")
        return 1

    errors = [d for d in diagnostics if d["severity"] == "error"]
    print(f"  {'types':11} {len(errors):3} erreur(s) de typage"
          + ("" if errors else " — les annotations tiennent"))
    for d in errors[:5]:
        name = "/".join(d["file"].split("/")[-2:])
        print(f"     {name}:{d['range']['start']['line'] + 1}  {d['message'].splitlines()[0][:70]}")
    return 1 if errors else 0


# ET LA SUITE QUE LE PROJET A ÉCRITE, PORTÉE SUR LE RENDU. C'est la seule épreuve qui n'a pas
# été écrite ici : 474 tests, 4 068 lignes, contre le paquet de l'ancien pack.
# `python/link/migrate.py` ne contient que des renommages -- sa longueur est le coût de
# migration, et un portage à la main ne mesurerait rien.
def suite(package):
    if not (ROOT / "features" / "python" / "tests").exists():
        return 0

    sys.path.insert(0, str(HERE / "python" / "link"))
    import migrate
    scratch = HERE / "build" / "suite"
    shutil.rmtree(scratch, ignore_errors=True)
    (scratch / "features").parent.mkdir(parents=True, exist_ok=True)
    substitutions = sum(migrate.migrate(scratch / "tests", package / "features").values())
    (scratch / "features").symlink_to(package / "features")
    sys.path.pop(0)

    r = subprocess.run([sys.executable, "-m", "unittest", "discover", "tests"],
                       cwd=scratch, capture_output=True, text=True,
                       env={**os.environ, "PYTHONPATH": str(scratch)})
    ran = next((l for l in r.stderr.splitlines() if l.startswith("Ran ")), "")
    total = int(ran.split()[1]) if ran else 0
    failed = sum(1 for l in r.stderr.splitlines() if l.startswith(("ERROR:", "FAIL:")))
    print(f"  {'la suite':11} {total - failed:3} / {total} tests du projet, "
          + f"{substitutions} substitutions de portage")
    return 1 if failed else 0


# Et les épreuves qu'un modèle donné permet : le fail-fast demande des types qui se
# ressemblent dans deux unités, ce que seul `Crossing` porte.
# CHAQUE MODÈLE A SA RACINE DE PROJET, donc plus aucun dossier ne les contient toutes. Les
# contrôles reçoivent les quatre par PYTHONPATH ; `sys.argv[1]` reste pour ceux qui le lisent.
CHEMINS = os.pathsep.join(str(p) for p in sorted(target.iterdir()) if p.is_dir())
ENV = {**os.environ, "PYTHONPATH": CHEMINS}

if not arguments.check and status == 0:
    for assertions in sorted((HERE / "python" / "checks").glob("*.py")):
        r = subprocess.run([sys.executable, str(assertions), str(target)],
                           capture_output=True, text=True, env=ENV)
        passed = sum(1 for line in r.stdout.splitlines() if line.strip().startswith("ok"))
        print(f"  {'fail-fast':11} {passed:3} assertions, "
              + ("toutes passent" if r.returncode == 0 else "ÉCHEC"))
        if r.returncode:
            status = 1
            for line in (r.stdout + r.stderr).splitlines()[-4:]:
                print(f"     {line.strip()}")


# ET LES MÊMES ASSERTIONS QUE LA RÉFÉRENCE ÉCRITE À LA MAIN. Un module qui s'importe n'est
# pas un module qui marche : l'import ne dit rien de ce qu'un attachment écrit ni de ce qu'une
# base relit. La référence dit ce qu'on veut, le rendu dit ce qu'on obtient, et c'est la même
# épreuve qui passe sur les deux ou ne référence rien.
if not arguments.check and status == 0:
    r = subprocess.run([sys.executable, str(HERE / "python" / "check.py"), str(target)],
                       capture_output=True, text=True, env=ENV)
    passed = sum(1 for line in r.stdout.splitlines() if line.startswith("  ok"))
    print(f"  {'épreuve':11} {passed:3} assertions sur le rendu, "
          + ("toutes passent" if r.returncode == 0 else "ÉCHEC"))
    if r.returncode:
        for line in r.stdout.splitlines():
            if "ÉCHEC" in line:
                print(f"     {line.strip()}")
        status = 1

    status |= typecheck(target)
    status |= suite(target / "features")

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
