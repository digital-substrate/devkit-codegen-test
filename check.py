#!/usr/bin/env python3
"""Une seule porte : les cinq sites, rendus et éprouvés.

UNE VÉRIFICATION QU'IL FAUT SAVOIR LANCER N'EN EST PAS UNE. Il y a douze `run_test.sh` et
cinq `generate.py` ; celui-ci les enchaîne et rend un verdict unique.

    check.py                rend les cinq sites et lance toutes les épreuves
    check.py features       un seul site
    check.py --no-render    éprouve ce qui est déjà rendu, sans regénérer

CE QUE CHAQUE SITE PROUVE, ET CE QU'IL NE PROUVE PAS -- c'est le tableau qui compte, plus que
le fait qu'il passe :

  features     tout le système de types dans un namespace, et les deux suites du projet
               474 tests Python, 465 TypeScript, écrits avant ce chantier et portés une fois
               ne prouve rien sur les pools : le modèle n'en déclare aucun
  service      deux pools, et un service qui tourne : un serveur C++, trois clients
               la seule épreuve où le code généré traverse un fil
               ne prouve rien sur les homonymes : un seul namespace utile
  namespaces   six namespaces et leurs arêtes ; deux déclarent le même nom
               la plus petite formulation de ce chantier
               ne prouve rien sur les composites : ses types ne se croisent pas
  crossing     la référence qui traverse un namespace À L'INTÉRIEUR d'un composite
               un `map<Core::Grade, Parts::Colour>`, un `variant<Core::Colour, ...>`
               ne prouve rien sur le service ni sur les suites

CE QU'AUCUN DES CINQ NE PROUVE : qu'un développeur de la population visée trouve la sortie
utilisable. `pip install` et `tsc --strict` chez un consommateur extérieur sont éprouvés à la
main pour l'instant, pas ici.
"""
import argparse
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent

# Le nom du site, et ce que son `generate.py` attend en plus des drapeaux. `features` prend
# son `.dsm` en positionnel ; les autres le lisent dans `definitions/`.
SITES = {
    "features": ["all.dsm"],
    "service": [],
    "namespaces": [],
    "crossing": [],
    "compat-1.2": [],
}
LANGAGES = ("cpp", "python", "typescript")

VERT, ROUGE, GRIS, NEUTRE = "\033[32m", "\033[31m", "\033[90m", "\033[0m"


def resultat(sortie: str) -> str:
    """Ce que l'épreuve a dit, en quelques mots.

    CHAQUE SUITE PARLE SA LANGUE, et deviner mal est pire que ne rien dire : un programme C++
    qui imprime `ok` une fois n'a pas passé « 1 assertion », il a compilé, lié et tourné.
    Les formes sont donc reconnues explicitement, et ce qui n'est reconnu par rien le dit.
    """
    lignes = [l.strip() for l in sortie.splitlines() if l.strip()]

    if any(l.startswith("add(32,10)") for l in lignes):
        return "client ↔ serveur"

    for ligne in lignes:
        if ligne.startswith("Ran ") and "test" in ligne:
            return f"{ligne.split()[1]} tests du projet"
        if ligne.startswith("ℹ pass "):
            return f"{ligne.split()[-1]} tests"

    if lignes and lignes[-1] == "ok":
        return "compile, lie, tourne"

    oks = sum(1 for l in lignes if l.startswith("ok"))
    if oks:
        return f"{oks} assertions"
    return f"passe, sans résumé reconnu ({lignes[-1][:28]})" if lignes else "silencieux"


def lancer(commande, dossier):
    r = subprocess.run(commande, cwd=dossier, capture_output=True, text=True)
    return r.returncode, r.stdout + r.stderr


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("site", nargs="?", choices=sorted(SITES), help="n'éprouver que celui-là")
    parser.add_argument("--no-render", action="store_true",
                        help="éprouver ce qui est déjà rendu")
    arguments = parser.parse_args()

    sites = [arguments.site] if arguments.site else list(SITES)
    echecs = []

    for site in sites:
        print(f"\n── {site}")
        dossier = HERE / site

        if not arguments.no_render:
            code, sortie = lancer([sys.executable, "generate.py", *SITES[site], "-c", "-p", "-t"],
                                  dossier)
            if code:
                print(f"   {ROUGE}rendu       échoue{NEUTRE}")
                for ligne in sortie.splitlines()[-6:]:
                    print(f"      {ligne}")
                echecs.append(f"{site}/rendu")
                continue

        for langage in LANGAGES:
            script = dossier / langage / "run_test.sh"
            if not script.exists():
                print(f"   {GRIS}{langage:11} pas d'épreuve{NEUTRE}")
                continue

            code, sortie = lancer(["./run_test.sh"], script.parent)
            if code:
                print(f"   {ROUGE}{langage:11} ÉCHEC{NEUTRE}")
                for ligne in sortie.splitlines()[-8:]:
                    print(f"      {ligne}")
                echecs.append(f"{site}/{langage}")
            else:
                print(f"   {VERT}{langage:11} {resultat(sortie)}{NEUTRE}")

    print()
    if echecs:
        print(f"{ROUGE}{len(echecs)} échec(s) : {', '.join(echecs)}{NEUTRE}")
        return 1
    print(f"{VERT}{'tout passe':>42}{NEUTRE}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
