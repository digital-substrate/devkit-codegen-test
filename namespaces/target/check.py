#!/usr/bin/env python3
"""Tout vérifier, et dire ce que chaque épreuve prouve — et ce qu'elle ne prouve pas.

UNE SEULE PORTE, PARCE QU'UNE VÉRIFICATION QU'IL FAUT SAVOIR LANCER N'EN EST PAS UNE. Il y
avait quatre scripts et il fallait connaître les quatre ; il y en a toujours quatre, mais
celui-ci les enchaîne et rend un verdict unique.

    check.py            rend tout, compile, lie, exécute, éprouve, vérifie les types
    check.py --check    la même chose, mais échoue si le rendu versionné est périmé

CE QUE CHAQUE ÉTAPE PROUVE, ET CE QU'ELLE NE PROUVE PAS — c'est le tableau qui compte, plus
que le fait qu'elle passe :

  rendu C++        les templates produisent un fichier par unité, sans diagnostic
                   ne prouve pas que ça compile
  compilation      chaque fichier est du C++ valable contre les VRAIS en-têtes de viper
                   ne prouve pas que ça se lie : une signature recopiée de travers passe
  lien             chaque symbole appelé existe dans libviper.a
                   ne prouve pas que ça marche : sept défauts n'étaient visibles qu'après
  exécution        le programme d'épreuve tourne : tous les types, les métadonnées, les
                   blobs, l'aller-retour de chaque attachment sur SQLite, le fuzz
  service          un client et un serveur EXISTANTS, portés par renommage seulement,
                   parlent par une socket — la seule épreuve qui n'a pas été écrite ici
  couverture       les 162 opérations du pack sont toutes émises, ou écartées avec raison
                   ne voit que des NOMS : un déplacement de portée lui est invisible
  rendu Python     un paquet par modèle, et chaque module s'importe
                   l'import est ce qui tient lieu de compilateur : syntaxe, dépendances,
                   classes construites, descripteurs trouvés dans les définitions
  assertions       les mêmes 23 sur la référence écrite à la main et sur le rendu
  types            pyright ne trouve aucune erreur : les annotations tiennent
"""
import argparse
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent

arguments = argparse.ArgumentParser(description=__doc__,
    formatter_class=argparse.RawDescriptionHelpFormatter)
arguments.add_argument("--check", action="store_true",
                       help="échouer si le rendu versionné n'est pas à jour")
arguments = arguments.parse_args()
flags = ["--check"] if arguments.check else []

STAGES = [
    ("C++    — rend, compile, lie, exécute", HERE / "cpp/render.py", flags),
    ("C++    — couverture du pack existant", HERE / "cpp/coverage.py", []),
    ("Python — rend, importe, éprouve, type", HERE / "python/render.py", flags),
    ("Python — la référence écrite à la main", HERE / "python/check.py", []),
    ("Node   — compile en strict, et tourne", HERE / "node/check.py", []),
    ("Node   — rend, compile, importe, éprouve", HERE / "node/render.py", flags),
]

status = 0
for label, script, extra in STAGES:
    print(f"\n── {label}")
    r = subprocess.run([sys.executable, str(script), *extra], capture_output=True, text=True)
    for line in (r.stdout + r.stderr).strip().splitlines():
        print(f"   {line}")
    status |= r.returncode

print()
print("tout passe" if status == 0 else "QUELQUE CHOSE NE PASSE PAS")
raise SystemExit(status)
