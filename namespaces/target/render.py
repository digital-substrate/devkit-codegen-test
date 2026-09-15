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
# LES VRAIS EN-TÊTES DU RUNTIME, et seulement ce qu'il ne porte pas encore à côté. Tant que
# la vérification se faisait contre des signatures recopiées, une recopie de travers passait
# inaperçue ; ici elles viennent de la source et le résultat se lie contre `libviper.a`.
VIPER = ROOT.parent / "com.digitalsubstrate.viper"
PROPOSED = ROOT / "runtime-proposed"

INCLUDES = ["-I", str(PROPOSED),
            "-I", str(VIPER / "src/Viper"),
            "-I", str(VIPER / "third_parties/hash"),
            "-I", str(VIPER / "third_parties/json"),
            "-I", str(VIPER / "third_parties/sqlite"),
            "-I", str(VIPER / "third_parties/cli11")]

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
        r = subprocess.run(["clang++", "-std=c++20", "-fsyntax-only", "-I", str(out), *INCLUDES, str(source)], capture_output=True, text=True)
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
        r = subprocess.run(["clang++", "-std=c++20", "-fsyntax-only", "-I", str(directory), *INCLUDES, str(source)],
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

# ── et l'épreuve qui compte : lier, et exécuter ──
#
# TANT QUE C'ÉTAIT `-fsyntax-only`, UNE SIGNATURE RECOPIÉE DE TRAVERS PASSAIT. Sept défauts
# ne se sont montrés qu'ici : deux références à un temporaire mort, un `auto` qui créait une
# conversion, un identifiant de blob inventé, une transaction absente, un modèle jamais
# donné à la base -- et un défaut dans le runtime lui-même.
if not arguments.check:
    link = target / "link"
    link.mkdir(parents=True, exist_ok=True)
    topology = target / "Topology"
    shutil.copy(HERE / "hand/Topology_Resources.hpp", topology)
    shutil.copy(HERE / "link/application.cpp", topology)

    objects, failed = [], []
    sources = sorted(topology.glob("*.cpp")) + sorted(PROPOSED.glob("*.cpp"))
    for source in sources:
        o = link / (source.stem + ".o")
        r = subprocess.run(["clang++", "-std=c++20", "-c", "-I", str(topology),
                            *INCLUDES, "-o", str(o), str(source)], capture_output=True, text=True)
        (objects if not r.returncode else failed).append(source.name)

    libs = [str(ROOT / "build" / f"lib{n}.a") for n in ("viper", "sqlite", "hash", "antlr4", "pugixml")]
    if failed or not all(Path(l).exists() for l in libs):
        print(f"  lien       ignoré ({len(failed)} objets manquants ou libviper.a absent)")
    else:
        binary = link / "testapp"
        r = subprocess.run(["clang++", "-std=c++20", "-o", str(binary),
                            *[str(link / (Path(n).stem + ".o")) for n in objects], *libs],
                           capture_output=True, text=True)
        if r.returncode:
            print("  lien       échoue")
            for l in r.stderr.splitlines()[:6]:
                print(f"     {l}")
            status = 1
        else:
            r = subprocess.run([str(binary)], capture_output=True, text=True)
            print(f"  lien       {len(objects)} objets, et le programme "
                  + ("tourne" if r.returncode == 0 else "ÉCHOUE"))
            if r.returncode:
                print("    " + r.stderr.strip().splitlines()[-1] if r.stderr.strip() else "")
                status = 1

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
