#!/usr/bin/env python3
"""Render the namespace-based templates into `generated/`, and compile the result.

The output is versioned on purpose. A template is only as good as what it produces, and
what it produces has to be readable in a diff from one commit to the next -- otherwise a
change to a template is a change nobody can see.

    render.py            render both models and compile them
    render.py --check    render to a scratch tree and fail if it differs from `generated/`
"""
import argparse, shutil, subprocess, sys, time
from pathlib import Path

HERE = Path(__file__).resolve().parent.parent
ROOT = HERE.parent.parent
sys.path.insert(0, str(ROOT / "tools"))
from render import jar                                    # noqa: E402

sys.path.insert(0, str(ROOT / "templates"))
import resolve                                            # noqa: E402

# TOUTES LES FEATURES, ICI, parce que le chantier éprouve la surface entière. Un vrai projet
# en nomme deux ou trois et `resolve` calcule le reste : `resolve.templates("cpp", ["Database"])`
# rend 9 `.stg` sans que le projet ait à savoir lesquels.
TEMPLATES = resolve.templates("cpp", ["TestApp", "AttachmentPool"])
# LES VRAIS EN-TÊTES DU RUNTIME, et seulement ce qu'il ne porte pas encore à côté. Tant que
# la vérification se faisait contre des signatures recopiées, une recopie de travers passait
# inaperçue ; ici elles viennent de la source et le résultat se lie contre `libviper.a`.
VIPER = ROOT.parent / "com.digitalsubstrate.viper"
PROPOSED = HERE / "runtime-proposed" / "cpp"

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
#   Service    des pools et un remote -- le seul qui exerce le pont statique/dynamique
#
# The last is the common case and the one most easily forgotten. A generator organised
# around namespaces has to degrade well when there is a single one, and nothing else here
# would have shown that it does.
MODELS = {
    "Topology": ROOT / "namespaces" / "Topology.dsm.json",
    "Crossing": ROOT / "crossing" / "Crossing.dsm.json",
    "Features": ROOT / "features" / "Features.dsm.json",
    "Service": ROOT / "service" / "Service.dsm.json",
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
    "Topology": HERE / "cpp/hand",
}

# LA RÉFÉRENCE DU MODÈLE CROISÉ EST PARTIELLE, ET DÉLIBÉRÉMENT. Elle ne couvre que les
# formes que le modèle topologique ne déclare pas -- un club, la clé non typée, les
# mutations d'agrégat -- et ses fichiers portent le nom des artefacts qu'ils reproduisent.
# Les copier dans l'arbre rendu masquerait donc ce qu'ils ne redisent pas : elle se compile
# chez elle, contre son propre jeu minimal.
STANDALONE = [ROOT / "crossing/target/hand"]


def render(model, definitions, out):
    out.mkdir(parents=True, exist_ok=True)
    noise, echec = [], False
    for stg in TEMPLATES:
        r = subprocess.run(["java", "-jar", jar(), "-c", "cpp", "-n", model,
                            "-d", str(definitions), "-t", str(stg), "-o", str(out)],
                           capture_output=True, text=True)
        noise += [l for l in r.stderr.splitlines() if l.strip()]
        echec = echec or bool(r.returncode)
    for l in noise[:8]:
        print(f"  !! {l}")
    return not (echec or noise)


def compile_tree(model, out):
    shutil.copy(HERE / "cpp/link/resources" / f"{model}_Resources.hpp", out)

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

target = HERE / (".check" if arguments.check else "generated/cpp")
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
# conversion, un identifiant de blob inventé, une transaction absente, un modèle jamais donné
# à la base -- et un défaut dans le runtime lui-même.
#
# Ce qu'un modèle apporte en plus du rendu : ses octets, et les fonctions de ses pools. Le
# premier est produit par `link/resources.py`, le second est ce qu'une application écrit.
APPLICATION = {"Topology": HERE / "cpp/link/application.cpp"}

# LE SERVICE EST LA SEULE ÉPREUVE QUE JE N'AI PAS ÉCRITE. Un client et un serveur existants,
# portés sur les nouveaux noms par `link/service/migrate.py` et pas autrement retouchés : ce
# qu'ils demandent est ce qu'un consommateur demande, et non ce que j'ai pensé à offrir.
CONSUMERS = {"Service": HERE / "cpp/link/service"}
LIBS = [ROOT / "build" / f"lib{n}.a" for n in ("viper", "sqlite", "hash", "antlr4", "pugixml")]


def link_and_run(model, out):
    resource = HERE / "cpp/link/resources" / f"{model}_Resources.hpp"
    if not resource.exists() or not all(l.exists() for l in LIBS):
        print(f"  {model + ' lien':16} ignoré (ressource ou libviper.a absente)")
        return 0

    # LE RENDU RESTE LE RENDU. Les octets du modèle et le code d'application ne sortent pas
    # des templates ; les poser à côté du rendu ferait échouer `--check`, qui compare
    # `generated/` à un rendu neuf et compterait chaque intrus comme une différence.
    link = HERE / "build" / model
    if link.exists():
        shutil.rmtree(link)
    link.mkdir(parents=True)

    shutil.copy(resource, link)
    extra = []
    if model in APPLICATION:
        extra.append(Path(shutil.copy(APPLICATION[model], link)))

    consumers = []
    if model in CONSUMERS:
        sys.path.insert(0, str(CONSUMERS[model]))
        import migrate
        migrate.migrate(link / "consumer")
        sys.path.pop(0)
        consumers = sorted((link / "consumer").glob("*.cpp"))

    objects = []
    mains = {}
    for source in sorted(out.glob("*.cpp")) + sorted(PROPOSED.glob("*.cpp")) + extra + consumers:
        o = link / (source.stem + ".o")
        r = subprocess.run(["clang++", "-std=c++20", "-c", "-I", str(out), "-I", str(link),
                            *INCLUDES, "-o", str(o), str(source)], capture_output=True, text=True)
        if r.returncode:
            print(f"  !! {source.name}")
            for l in r.stderr.splitlines()[:4]:
                print(f"     {l}")
            return 1
        if source.stem in ("ServiceClient", "ServiceServer"):
            mains[source.stem] = str(o)
        else:
            objects.append(str(o))

    binary = link / "testapp"
    r = subprocess.run(["clang++", "-std=c++20", "-o", str(binary), *objects,
                        *[str(l) for l in LIBS]], capture_output=True, text=True)
    if r.returncode:
        print(f"  {model + ' lien':16} échoue")
        for l in r.stderr.splitlines()[:6]:
            print(f"     {l}")
        return 1

    r = subprocess.run([str(binary)], capture_output=True, text=True)
    print(f"  {model + ' lien':16} {len(objects):3} objets, et le programme "
          + ("tourne" if r.returncode == 0 else "ÉCHOUE"))
    if r.returncode and r.stderr.strip():
        print("     " + r.stderr.strip().splitlines()[-1])

    if mains:
        return r.returncode | round_trip(link, objects, mains)
    return r.returncode


# LE VRAI TEST D'UN POOL EST UN APPEL QUI TRAVERSE UN PROCESSUS. Un `call()` local passe par
# les mêmes `Value` mais reste du même côté du codec : rien ne vérifie que ce que le client
# pose sur le fil est ce que le serveur y lit. Ici le client et le serveur sont deux
# binaires, et le seul lien entre eux est le format.
def round_trip(link, objects, mains):
    shared = [o for o in objects if not o.endswith("Service_TestApp.o")]
    binaries = {}
    for name, obj in mains.items():
        binaries[name] = link / name
        r = subprocess.run(["clang++", "-std=c++20", "-o", str(binaries[name]), obj, *shared,
                            *[str(l) for l in LIBS]], capture_output=True, text=True)
        if r.returncode:
            print(f"  {name + ' lien':16} échoue")
            for l in r.stderr.splitlines()[:6]:
                print(f"     {l}")
            return 1

    socket = link / "service.sock"
    server = subprocess.Popen([str(binaries["ServiceServer"]), "-s", str(socket)],
                              stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    try:
        for _ in range(100):
            if socket.exists():
                break
            time.sleep(0.05)
        r = subprocess.run([str(binaries["ServiceClient"]), "-s", str(socket)],
                           capture_output=True, text=True, timeout=30)
    finally:
        server.terminate()
        server.wait(timeout=10)

    if r.returncode:
        print("  service      client ÉCHOUE")
        for l in (r.stdout + r.stderr).strip().splitlines()[-4:]:
            print(f"     {l}")
        return 1

    print("  service      le client parle au serveur :")
    for l in r.stdout.strip().splitlines():
        print(f"     {l}")
    return 0


if not arguments.check:
    for model in MODELS:
        status |= link_and_run(model, target / model)

if arguments.check:
    same = subprocess.run(["diff", "-r", str(HERE / "generated/cpp"), str(target)],
                          capture_output=True, text=True)
    shutil.rmtree(target)
    if same.returncode:
        print(same.stdout[:2000])
        print("generated/ n'est pas ce que les templates produisent")
        status = 1
    else:
        print("generated/ est à jour")

raise SystemExit(status)
