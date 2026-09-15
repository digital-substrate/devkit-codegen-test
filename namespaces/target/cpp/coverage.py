#!/usr/bin/env python3
"""Ce que les anciens templates produisent et que les nouveaux ne produisent pas encore.

L'iso-fonctionnalité est le critère, et une affirmation ne vaut rien : ce script compare
les opérations déclarées dans les deux sorties pour le même modèle, et imprime ce qui
manque. La liste doit rétrécir jusqu'à zéro, et elle est la seule mesure d'avancement.

    coverage.py                 la liste de ce qui manque
    coverage.py --all           sans écarter ce qui est délibérément non généré

Un nom suffixé par un type -- `encode_Test_StructureS` -- est ramené à son opération
`encode` avant comparaison : une famille de fonctions par type est remplacée par une seule
fonction template, donc les compter ferait dire au décompte le contraire de ce qu'il mesure.
"""
import argparse, re, subprocess, sys
from pathlib import Path

HERE = Path(__file__).resolve().parent.parent
ROOT = HERE.parent.parent
sys.path.insert(0, str(ROOT / "tools"))
from render import jar, TEMPLATES                                    # noqa: E402
from models import MODELS                                           # noqa: E402

# TOUS LES MODÈLES, ET NON LE PLUS COMPLET. La mesure a tourné longtemps sur `features`
# seul -- « le modèle le plus complet : toutes les formes du langage » -- et annonçait zéro
# absente pendant que le `Remote` d'un pool d'attachments n'existait pas du tout. Features
# ne déclare aucun pool, donc pas une seule opération de pool n'entrait dans la comparaison :
# le décompte ne mesurait pas ce qu'il disait mesurer. Aucun modèle ne porte tout ; c'est
# leur réunion qui porte tout.
MODELS_MEASURED = ["features", "service", "crossing", "namespaces"]

GENERATED = {"features": "Features", "service": "Service",
             "crossing": "Crossing", "namespaces": "Topology"}

# LES UNITÉS SONT CELLES DES MODÈLES MESURÉS, LUES ET NON ÉCRITES. Une liste de namespaces
# tenue à la main se périme au premier modèle ajouté, et se périme en silence : le suffixe
# cesse d'être retiré, la famille par type réapparaît nom par nom, et le décompte se met à
# réclamer des fonctions qui n'ont jamais eu à exister.
UNITS = sorted({d.name.split("_")[0]
                for model in GENERATED.values()
                for d in (HERE / "generated/cpp" / model).glob("*_*.hpp")}
               | set(GENERATED.values()))

def descendant_getters():
    """Les `as<X>Key` que le pack pose sur l'ancêtre, un par concept qui descend d'un autre."""
    import json
    names = set()
    for model in MODELS_MEASURED:
        spec = MODELS[model]
        d = json.loads((ROOT / model / f'{spec["namespace"]}.dsm.json').read_text())
        for c in d.get("concepts", []):
            if not c.get("parent"):
                continue
            name, unit = c["name"], c["namespace_name"]
            names.add("as" + name[0].upper() + name[1:] + "Key")
            names.add("as" + unit[0].upper() + unit[1:] + name[0].upper() + name[1:] + "Key")
    return names


SUFFIX = re.compile(
    r"_(" + "|".join(UNITS) + r")_\w+$"
    r"|_(bool|uint8|uint16|uint32|uint64|int8|int16|int32|int64|float|double"
    r"|string|blob|blob_id|commit_id|uuid|any|Definitions|Types|AnyConceptKey)$"
    r"|_(vec|mat|tuple|optional|vector|set|map|xarray|variant)_?\w*$")

NOISE = {"if", "for", "while", "switch", "return", "sizeof", "static_cast", "throw",
         "catch", "operator", "make_shared", "move", "parse", "of"}

# Ce que les nouveaux templates n'émettent pas sous le même nom, et pourquoi. Deux sortes,
# et la distinction compte : un écart sans raison est un oubli qui a trouvé un abri.

# ABSORBÉ : l'opération n'a pas de contrepartie, et c'est voulu. La raison est le nom du
# groupe, et elle doit tenir sans qu'on regarde ailleurs.
ABSORBED = {
    # Mesuré : ces artefacts sortent octet pour octet identiques pour deux modèles sans
    # rapport, donc ce sont du code de runtime enveloppé dans un namespace. Le nouveau
    # monde appelle Viper::Database, dont runtime/Viper_Database.hpp dit la surface.
    "le runtime, enveloppé dans un template": """beginTransaction commit rollback
        inTransaction close isClosed codecName dataVersion documentation path uuid
        databasing extendDefinitions definitionsHexDigest isCompatible createInMemory open
        connect databases getDatabase setDatabase make copy blob blobIds blobInfo blobInfos
        blobRead blobStatistics blobStreamAppend blobStreamClose blobStreamCreate
        blobStreamDelete blobStreamWrite createBlob createZeroBlob delBlob freezeBlob
        readBlob writeBlob streamCodecInstancing""",

    # Les entrées/sorties en vrac d'un flux, que le runtime porte déjà.
    "le flux, en vrac": """read_uint8s read_uint16s read_uint32s read_uint64s read_int8s
        read_int16s read_int32s read_int64s read_floats read_doubles write_uint8s
        write_uint16s write_uint32s write_uint64s write_int8s write_int16s write_int32s
        write_int64s write_floats write_doubles""",

    # Le nom d'un champ. Le pack en fait une fonction -- `Field::StructureU::f_A()` -- là où
    # ici c'est une constante `inline constexpr std::string_view`, utilisable en expression
    # constante. Présent, sous une forme qu'une comparaison de noms ne voit pas.
    "un nom de champ, devenu constante": """field_structure_s field""",

    # Le descripteur d'un type, que l'unité porte maintenant dans son identité de modèle, et
    # celui d'une primitive ou d'un conteneur, qui est du runtime.
    "un descripteur de type": "attachment type_void type_def_any_concept",

    # L'ANNUAIRE DE POOLS DU MODÈLE. Le pack déclare `Service::FunctionPools::tools()` :
    # le modèle tient la liste de ses pools et chacun s'y nomme. Ici un pool est une unité,
    # donc il se construit lui-même sous `Tools::pool()` et le modèle n'a rien à tenir.
    # La liste est calculée : chaque pool rendu porte le nom d'une entrée de l'annuaire.
    "l'annuaire de pools du modèle": " ".join(
        d.name.split("_")[0][0].lower() + d.name.split("_")[0][1:]
        for model in GENERATED.values()
        for d in (HERE / "generated/cpp" / model).glob("*_Pool.hpp")),

    # LE RÉTRÉCISSEMENT VERS UN DESCENDANT, POSÉ CHEZ L'ANCÊTRE. Le pack donne à
    # `Core::ThingKey` un `asWovenDerivedKey()` pour chaque concept qui en descend -- donc
    # `Core` nomme `Woven`, qui nomme `Core` : l'arête pointe dans les deux sens et un
    # modèle à plusieurs unités ne peut pas la fermer. Ici le rétrécissement est chez le
    # descendant, qui connaît son ancêtre de toute façon : `Woven::DerivedKey::from(
    # thing.toAny())` rend le même `optional`, et se dit là où le type se nomme déjà.
    "le rétrécissement, déplacé chez le descendant": " ".join(descendant_getters()),
}

# RENOMMÉ : l'opération est là, sous un autre mot. Chaque entrée dit lequel, et le script
# vérifie que ce mot est bien dans la sortie -- sans quoi l'écart serait un oubli déguisé.
RENAMED = {
    "toAnyConceptKey": "toAny",
    "type_check": "conceptType",
    "set_seed": "seed",
    "encode_dsm_definitions": "jsonDefinitions",
    "test_Metadata": "testMetadata",
    "test_Blob_Create": "testBlobCreate",
    "test_Blob_Stream": "testBlobStream",
    "test_Blob_IO": "testBlobIO",
    "test_Create_Blob": "withBlob",
    "test_Attachments": "testDatabase",
    "test_Attachments_get": "fuzzDatabase",
    "test_get": "fuzzDatabase",
}


def rendered_pack(out, model):
    spec = MODELS[model]
    definitions = ROOT / model / f'{spec["namespace"]}.dsm.json'
    out.mkdir(parents=True, exist_ok=True)
    for feature in spec["cpp"]:
        subprocess.run(["java", "-jar", jar(), "-c", "cpp", "-n", spec["namespace"],
                        "-d", str(definitions), "-t", str(TEMPLATES / "cpp" / feature),
                        "-o", str(out)], capture_output=True, text=True)
    return sorted(out.glob("*.hpp"))


# LE NOM D'UN CHAMP N'EST PAS UNE OPÉRATION, ET LE PACK LUI DONNE POURTANT LA FORME D'UNE.
# `Field::StructureU::f_A()` rend le nom du champ ; ici c'est une constante. Les écarter par
# le fichier qui les porte plutôt que par une liste de noms : la liste ne couvrait que les
# champs d'un seul modèle, et chaque modèle ajouté en inventait de nouveaux à y recopier.
FIELD_ARTEFACT = re.compile(r"_(Field|Path)\.hpp$")


def operations(paths):
    found = set()
    for p in paths:
        if FIELD_ARTEFACT.search(p.name):
            continue
        for line in p.read_text(errors="replace").splitlines():
            s = line.strip()
            if s.startswith(("//", "*", "/*", "#")):
                continue
            for m in re.finditer(r"\b([a-z]\w*)\s*\(", s):
                name, previous = m.group(1), None
                while name != previous:
                    previous, name = name, SUFFIX.sub("", name)
                found.add(name)
    return found - NOISE


arguments = argparse.ArgumentParser(description=__doc__,
    formatter_class=argparse.RawDescriptionHelpFormatter)
arguments.add_argument("--all", action="store_true",
                       help="sans écarter ce qui est délibérément non généré")
arguments = arguments.parse_args()

import tempfile
pack, mine = set(), set()
for model in MODELS_MEASURED:
    with tempfile.TemporaryDirectory() as scratch:
        pack |= operations(rendered_pack(Path(scratch) / model, model))
    mine |= operations(sorted((HERE / "generated/cpp" / GENERATED[model]).glob("*.hpp")))
missing = pack - mine

broken = []
if not arguments.all:
    for reason, names in ABSORBED.items():
        missing -= set(names.split())

    for old, new in RENAMED.items():
        if new in mine:
            missing.discard(old)
        else:
            broken.append(f"{old} -> {new}")

print(f"le pack déclare {len(pack)} opérations, les nouveaux templates {len(mine)}")
print(f"absentes : {len(missing)}")
print()
for name in sorted(missing):
    print("   ", name)

if broken:
    print()
    print("renommages annoncés dont le nouveau nom est absent de la sortie :")
    for line in broken:
        print("   ", line)

raise SystemExit(1 if missing or broken else 0)
