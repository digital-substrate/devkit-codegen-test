"""La suite d'épreuves TypeScript du projet, portée sur le rendu.

15 fichiers, 4 000 lignes, 465 tests écrits contre le paquet de l'ancien pack. Ce fichier ne
contient que des renommages, chacun avec sa raison : sa longueur *est* le coût de migration.
"""
import re
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
SOURCE = HERE.parents[3] / "features" / "typescript" / "test"

CONTAINERS = re.compile(r"^(Vec|Mat|Tuple|Optional|Vector|Set|Map|XArray|Variant)_\w+$")

RENAMES = [
    # Le namespace de `all.dsm` s'appelle `Demo` depuis qu'il a cessé de s'appeler `Test` : il
    # se confondait avec les artefacts d'épreuve que le générateur produit. `\b` ne voit aucune
    # frontière entre deux caractères de mot, donc il ne sert à rien au milieu d'un identifiant.
    (re.compile(r"(?<![A-Za-z])Test_(\w+)"), r"Demo_\1"),
    (re.compile(r"\bTest::"), "Demo::"),
    # `md.definitions()` devient `definitions()` : le modèle offre la fonction, pas un module
    # qui la contiendrait.
    (re.compile(r"\b(md|definitions)\.definitions\(\)"), "definitions()"),
    # `Test_` au milieu d'un nom composé — `setTest_StructureS` — que le contrôle de frontière
    # ci-dessus écarte puisqu'une lettre le précède.
    (re.compile(r"\b(set|get|is)Test_(\w+)"), r"\1Demo_\2"),

    # Une unité est un module, pas un préfixe — sauf au milieu d'un nom de conteneur, où la
    # forme appartient au modèle et non à une unité.
    (re.compile(r"(?<![\w])Demo_(\w+)"), r"\1"),

    # UN CAS D'ÉNUMÉRATION EST UNE CHAÎNE, ET NON UN OBJET. Le pack en fait une classe qui
    # enveloppe une `ValueEnumeration` ; ici c'est une union de littéraux, qui se vérifie mieux
    # et ne coûte aucun objet — mais un littéral ne porte pas de méthode. Ce que le pack écrit
    # `e.hexdigest()` s'écrit donc `EnumerationE.hexdigest(e)`.
    # LE RÉCEPTEUR DOIT ÊTRE UNE ÉNUMÉRATION, ET RIEN D'AUTRE. `\w+\.encode()` attrape aussi
    # un vecteur et une structure, qui ont la méthode et n'ont rien à voir ; une règle de
    # portage qui déborde est pire que pas de règle, parce qu'elle casse ce qui marchait.
    (re.compile(r"\b(e\d?|enumValue|decoded)\.(hexdigest|encode|name)\(\)"),
     r"EnumerationE.\2(\1)"),
    (re.compile(r"\bEnumerationE\.([A-Z])\.(hexdigest|encode)\(\)"),
     r"EnumerationE.\2(EnumerationE.\1)"),

    # Et `instanceof` ne s'applique pas à une union de littéraux : le test est l'appartenance.
    (re.compile(r"assert\.ok\((\w+) instanceof EnumerationE\)"),
     r"assert.ok(Object.values(EnumerationE).includes(\1))"),
]

# LE PAQUET N'A PLUS DE TONNEAU UNIQUE. Le pack exporte tout depuis `dist/index.js` ; ici les
# types d'une unité viennent de l'unité, les conteneurs du modèle — ils n'appartiennent à
# aucune — et la clé non typée du socle.
IMPORT = re.compile(r'import\s*\{([^}]*)\}\s*from\s*"\.\./features/dist/index\.js";')


def redistribute(text: str):
    count = 0

    def one(found):
        nonlocal count
        count += 1
        names = [n.strip() for n in found.group(1).replace("\n", " ").split(",") if n.strip()]
        containers = [n for n in names if CONTAINERS.match(n)]
        untyped = [n for n in names if n == "AnyConceptKey"]
        # `definitions` et les identifiants d'exécution sont du modèle, pas d'une unité : ils
        # ne nomment aucun type, donc aucune unité ne peut les revendiquer.
        model = [n for n in names if n in ("definitions", "RuntimeIds", "AttachmentRuntimeIds")]
        attached = [n for n in names if n.startswith("attachments")]
        unit = [n for n in names if n not in containers and n not in untyped
                and n not in model and n not in attached]

        lines = []
        if unit:
            lines.append('import { ' + ", ".join(unit) + ' } from "../features/dist/demo/data.js";')
        if containers:
            lines.append('import { ' + ", ".join(containers)
                         + ' } from "../features/dist/containers.js";')
        if untyped:
            lines.append('import { AnyConceptKey } from "../features/dist/_codegen/registry.js";')
        if model:
            lines.append('import { ' + ", ".join(model) + ' } from "../features/dist/index.js";')
        if attached:
            lines.append('import * as ma from "../features/dist/demo/attachments.js";')
        return "\n".join(lines)

    return IMPORT.sub(one, text), count


TABLE: dict = {}


def attachment_table(package: Path) -> dict:
    """La table des attachments, lue dans le paquet rendu.

    Le pack écrit `conceptA_Properties` : un seul identifiant où le concept et l'attachment
    sont collés, et aucune règle de chaîne ne dit où l'un finit. Le rendu, lui, le sait.
    """
    import json
    import subprocess
    script = ("const m = await import('./dist/demo/attachments.js');"
              "const out = {};"
              "for (const [scope, cls] of Object.entries(m)) {"
              "  for (const name of Object.getOwnPropertyNames(cls)) {"
              "    if (['length', 'name', 'prototype'].includes(name)) continue;"
              "    out[scope.charAt(0).toLowerCase() + scope.slice(1) + '_'"
              "        + name.charAt(0).toUpperCase() + name.slice(1)] = scope + '.' + name;"
              "  } }"
              "console.log(JSON.stringify(out));")
    r = subprocess.run(["node", "--input-type=module", "-e", script],
                       cwd=package, capture_output=True, text=True)
    return json.loads(r.stdout) if r.returncode == 0 else {}


def migrate(into: Path, package: Path | None = None) -> dict:
    global TABLE
    if package is not None:
        TABLE = attachment_table(package)
    into.mkdir(parents=True, exist_ok=True)
    counts = {}
    for source in sorted(SOURCE.glob("*.mjs")):
        text = source.read_text()
        touched = 0
        for pattern, replacement in RENAMES:
            text, n = pattern.subn(replacement, text)
            touched += n
        text, n = redistribute(text)
        touched += n

        # LE NOM PLAT D'UN ATTACHMENT SE RESCOPE, et la table se lit dans le rendu plutôt que
        # de se deviner : `conceptA_Properties` ne dit pas où le concept finit.
        for flat, scoped in sorted(TABLE.items(), key=lambda kv: -len(kv[0])):
            text, n = re.subn(rf"\bma\.{flat}\b", f"ma.{scoped}", text)
            touched += n
        (into / source.name).write_text(text)
        counts[source.name] = touched
    return counts


if __name__ == "__main__":
    into = Path(sys.argv[1]) if len(sys.argv) > 1 else HERE / "test"
    for name, n in migrate(into).items():
        print(f"  {name:28} {n:4} substitution(s)")
