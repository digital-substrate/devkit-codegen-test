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

# The three models, and what each is for. None alone reaches everything.
#
#   Topology   the namespace topology -- every kind of edge between units
#   Crossing   the type system across it -- every shape, with elements from two units
#   Features   ONE namespace, and every shape of the type system inside it
#
# The last is the common case and the one most easily forgotten. A generator organised
# around namespaces has to degrade well when there is a single one, and nothing else here
# would have shown that it does.
MODELS = {
    "Topology": ROOT / "namespaces" / "Topology.dsm.json",
    "Crossing": ROOT / "crossing" / "Crossing.dsm.json",
    "Features": ROOT / "features" / "Features.dsm.json",
}

# Écrit à la main et non généré : les octets du modèle, qu'une vraie construction embarque
# depuis le `.dsm`, et les fichiers de contrôle qui compilent contre la sortie.
#
# LA RÉFÉRENCE D'UN MODÈLE SE COMPILE AVEC SON RENDU. Elle ne redéclare pas ce que le
# générateur produit déjà -- ce serait une seconde vérité à tenir -- donc elle est copiée
# dans l'arbre rendu et compilée là.
FROM_HAND = {
    "Topology": ["use.cpp", "bridge.cpp", "l4.cpp", "l5.cpp", "f.cpp", "json.cpp"],
}

HAND = {
    "Topology": ROOT / "namespaces/target/hand",
}

# LA RÉFÉRENCE DU MODÈLE CROISÉ EST PARTIELLE, ET DÉLIBÉRÉMENT. Elle ne couvre que les
# formes que le modèle topologique ne déclare pas -- un club, la clé non typée, les
# mutations d'agrégat -- et ses fichiers portent le nom des artefacts qu'ils reproduisent.
# Les copier dans l'arbre rendu masquerait donc ce qu'ils ne redisent pas : elle se compile
# chez elle, contre son propre jeu minimal.
STANDALONE = [ROOT / "crossing/target/hand"]


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

    for name in FROM_HAND.get(model, []):
        shutil.copy(HAND[model] / name, out / name)

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

for directory in STANDALONE:
    failed = []
    for source in sorted(directory.glob("*.cpp")):
        r = subprocess.run(["clang++", "-std=c++20", "-fsyntax-only", "-I", str(directory),
                            "-I", str(RUNTIME), str(source)],
                           capture_output=True, text=True)
        if r.returncode:
            failed.append(source.name)
            print(f"  !! {source.name}")
            for l in r.stderr.splitlines()[:4]:
                print(f"     {l}")
    print(f"  {directory.parent.parent.name + '/hand':10} "
          f"{len(list(directory.glob('*.cpp'))):3} .cpp"
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
