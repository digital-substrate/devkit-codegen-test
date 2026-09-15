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

HERE = Path(__file__).resolve().parent
ROOT = HERE.parent.parent
sys.path.insert(0, str(ROOT / "tools"))
from render import jar, TEMPLATES                                    # noqa: E402
from models import MODELS                                           # noqa: E402

MODEL = "features"          # le modèle le plus complet : toutes les formes du langage

SUFFIX = re.compile(
    r"_(Test|Features)_\w+$"
    r"|_(bool|uint8|uint16|uint32|uint64|int8|int16|int32|int64|float|double"
    r"|string|blob|blob_id|commit_id|uuid|any|Definitions|Types|AnyConceptKey)$"
    r"|_(vec|mat|tuple|optional|vector|set|map|xarray|variant)_?\w*$")

NOISE = {"if", "for", "while", "switch", "return", "sizeof", "static_cast", "throw",
         "catch", "operator", "make_shared", "move", "parse", "of"}

# Ce que les nouveaux templates n'émettent pas, et ne doivent pas émettre. Chaque entrée
# porte la raison, parce qu'une exception sans raison est un oubli qui a trouvé un abri.
DELIBERATE = {
    # Mesuré : ces artefacts sortent octet pour octet identiques pour deux modèles sans
    # rapport, donc ce sont du code de runtime enveloppé dans un namespace.
    "database": """beginTransaction commit rollback inTransaction close isClosed codecName
        dataVersion documentation path uuid databasing extendDefinitions definitionsHexDigest
        isCompatible createInMemory open connect databases getDatabase setDatabase make copy
        blob blobIds blobInfo blobInfos blobRead blobStatistics blobStreamAppend
        blobStreamClose blobStreamCreate blobStreamDelete blobStreamWrite createBlob
        createZeroBlob delBlob freezeBlob readBlob writeBlob""",

    # Les entrées/sorties en vrac d'un flux, que le runtime porte déjà.
    "flux": """read_uint8s read_uint16s read_uint32s read_uint64s read_int8s read_int16s
        read_int32s read_int64s read_floats read_doubles write_uint8s write_uint16s
        write_uint32s write_uint64s write_int8s write_int16s write_int32s write_int64s
        write_floats write_doubles""",

    # Renommés, et le nouveau nom est dans la sortie : la comparaison les verrait comme
    # manquants alors qu'ils sont là sous un autre mot.
    "renommés": """toAnyConceptKey type_check set_seed attachment field type_void
        type_def_any_concept remove""",

    # Le nom d'un champ. Le pack en fait une fonction -- `Field::StructureU::f_A()` --
    # là où ici c'est une constante `inline constexpr std::string_view`, utilisable en
    # expression constante. Présent, sous une forme que la comparaison ne voit pas.
    "champs": """f_A f_B f_C f_D f_E f_Klub f_S f_T f_any_concept f_single
        field_structure_s""",

    # Remplacé par une conversion implicite vers la clé du parent : `is a` n'est pas une
    # demande, donc l'élargissement n'a pas à être appelé. L'opération est là, sans nom.
    "élargissement": "toParentKey",
}


def rendered_pack(out):
    spec = MODELS[MODEL]
    definitions = ROOT / MODEL / f'{spec["namespace"]}.dsm.json'
    out.mkdir(parents=True, exist_ok=True)
    for feature in spec["cpp"]:
        subprocess.run(["java", "-jar", jar(), "-c", "cpp", "-n", spec["namespace"],
                        "-d", str(definitions), "-t", str(TEMPLATES / "cpp" / feature),
                        "-o", str(out)], capture_output=True, text=True)
    return sorted(out.glob("*.hpp"))


def operations(paths):
    found = set()
    for p in paths:
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
with tempfile.TemporaryDirectory() as scratch:
    pack = operations(rendered_pack(Path(scratch)))

mine = operations(sorted((HERE / "generated" / "Features").glob("*.hpp")))
missing = pack - mine

if not arguments.all:
    for reason, names in DELIBERATE.items():
        missing -= set(names.split())

print(f"le pack déclare {len(pack)} opérations, les nouveaux templates {len(mine)}")
print(f"absentes : {len(missing)}")
print()
for name in sorted(missing):
    print("   ", name)

raise SystemExit(1 if missing else 0)
