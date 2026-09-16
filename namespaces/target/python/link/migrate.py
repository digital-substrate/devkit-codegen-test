"""La suite d'épreuves existante, portée sur le rendu des nouveaux templates.

4 068 lignes et 474 tests écrits par le projet, contre le paquet de l'ancien pack. Ce fichier
ne contient que les renommages, chacun avec sa raison : sa longueur *est* le coût de
migration, et un portage à la main ne mesurerait rien.
"""
import re
import shutil
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
SOURCE = HERE.parents[3] / "features" / "python" / "tests"

RENAMES = [
    # LE NAMESPACE DE `all.dsm` S'APPELLE `Demo` DEPUIS QU'IL A CESSÉ DE S'APPELER `Test` : il
    # se confondait avec les artefacts d'épreuve que le générateur produit. La suite nomme les
    # types générés, donc elle suit — c'est la dette notée dans PLAN.md, payée ici.
    (re.compile(r"(?<![A-Za-z])Test_(\w+)"), r"Demo_\1"),
    (re.compile(r"\bfrom_test_(\w+)"), r"from_demo_\1"),

    # Une unité est un module, pas un préfixe : `Demo_ConceptAKey` devient `ConceptAKey` dans
    # `features.demo`. C'est ce que tout le chantier cherchait.
    #
    # SAUF AU MILIEU D'UN NOM DE CONTENEUR. `XArray_Demo_StructureS` nomme une forme et non un
    # type de l'unité : la forme appartient au modèle, qui n'a pas d'unité où ranger le nom.
    (re.compile(r"(?<![\w])Demo_(\w+)"), r"\1"),

    # Les classes vivent dans l'unité ; les conteneurs, qui n'appartiennent à aucune, vivent
    # au niveau du modèle.
    (re.compile(r"from features\.data import"), "from features.demo import"),
    (re.compile(r"from features import data\b"), "from features import demo as data"),

    # `definitions` est une fonction du paquet et non un module à lui.
    (re.compile(r"from features import definitions as md"), "from features import definitions"),
    (re.compile(r"\bmd\.definitions\(\)"), "definitions()"),

    # Les attachments sont par unité, et un attachment est un objet dont la portée est son
    # concept porteur.
    (re.compile(r"from features import attachments as ma"), "from features.demo import attachments as ma"),
    (re.compile(r"from features import database_attachments as db"),
     "from features.demo import attachments as db"),

    # La valeur enveloppée porte le nom que le langage donne à ce qu'on lit.
    (re.compile(r"\.vpr_value\b"), ".value"),

    # UNE ÉNUMÉRATION EST CELLE DE PYTHON, PAS UN PROXY. Le pack enveloppe une
    # `ValueEnumeration` et expose `name()` et `from_str()` ; `enum.Enum` a déjà `.name`, `.value`
    # et sa construction depuis la valeur. C'est le seul endroit où le portage change une forme
    # d'appel et non un nom, et c'est délibéré : la classe du pack ne faisait que redire ce que
    # le langage offre.
    (re.compile(r"\.name\(\)"), ".name"),
    (re.compile(r"(\w+)\.from_str\("), r"\1("),
]

# LES CONTENEURS SONT IMPORTÉS D'AILLEURS. Ils n'appartiennent à aucune unité -- un
# `vector<uint8>` n'est ni de `Demo` ni d'une autre -- donc le modèle les porte.
CONTAINERS = re.compile(r"\b(Vec|Mat|Tuple|Optional|Vector|Set|Map|XArray|Variant)_\w+")


# LA TABLE DES ATTACHMENTS SE LIT DANS LE PAQUET RENDU, elle ne se devine pas. Le pack écrit
# `demo_concept_a_properties_get` : un seul identifiant où le concept et l'attachment sont
# collés, et aucune règle de chaîne ne dit où l'un finit. Le rendu, lui, le sait — il a une
# classe par concept et une propriété par attachment. On le lui demande.
def attachment_table(package: Path) -> dict:
    sys.path.insert(0, str(package.parent))
    from features.demo import attachments                           # noqa: E402

    table = {}
    for scope in (n for n in dir(attachments) if n[0].isupper()):
        cls = getattr(attachments, scope)
        for name in (a for a in dir(cls) if not a.startswith("_")):
            flat = re.sub(r"(?<!^)(?=[A-Z])", "_", scope).lower() + "_" + name
            table[flat] = f"{scope}.{name}"
    return table


IMPORT = re.compile(r"from features\.demo import \(([^)]*)\)|from features\.demo import ([^\n(]+)")


def redistribute(text: str):
    """Tous les imports du fichier, redistribués en une passe.

    EN UNE PASSE ET NON EN BOUCLE : ce que la substitution écrit ressemble à ce qu'elle
    cherche, donc relancer la recherche sur son propre résultat ne s'arrête jamais.
    """
    count = 0

    def one(found):
        nonlocal count
        count += 1
        return _redistribute_names(found.group(1) or found.group(2))

    return IMPORT.sub(one, text), count


def _redistribute_names(raw: str) -> str:
    names = [n.strip().rstrip(",") for n in raw.replace("\n", " ").split(",")]
    names = [n for n in names if n]

    containers = [n for n in names if CONTAINERS.fullmatch(n)]
    untyped = [n for n in names if n == "AnyConceptKey"]
    unit = [n for n in names if n not in containers and n not in untyped]

    lines = []
    if unit:
        lines.append("from features.demo import " + ", ".join(unit))
    if containers:
        lines.append("from features.containers import " + ", ".join(containers))
    if untyped:
        lines.append("from features import AnyConceptKey")

    return "\n".join(lines)


TABLE: dict = {}


def migrate(into: Path, package: Path | None = None) -> dict:
    global TABLE
    if package is not None:
        TABLE = attachment_table(package)
    into.mkdir(parents=True, exist_ok=True)
    counts = {}
    for source in sorted(SOURCE.glob("*.py")):
        text = source.read_text()
        touched = 0
        for pattern, replacement in RENAMES:
            text, n = pattern.subn(replacement, text)
            touched += n

        # UN IMPORT SE REDISTRIBUE, IL NE SE RENOMME PAS. La suite importe tout depuis
        # `features.data` ; ici les types d'une unité viennent de l'unité, les conteneurs du
        # modèle -- ils n'appartiennent à aucune unité -- et la clé non typée du socle.
        text, n = redistribute(text)
        touched += n

        for flat, scoped in TABLE.items():
            # `test_` en minuscules aussi : le nom plat du pack porte le namespace en
            # minuscules, et le renommage du modèle n'a touché que la forme capitalisée.
            text, n = re.subn(rf"\b(ma|db)\.(?:test|demo)_{flat}_(\w+)\b", rf"\1.{scoped}.\2", text)
            touched += n

        (into / source.name).write_text(text)
        counts[source.name] = touched
    (into / "__init__.py").write_text("")
    return counts


if __name__ == "__main__":
    into = Path(sys.argv[1]) if len(sys.argv) > 1 else HERE / "tests"
    for name, n in migrate(into).items():
        print(f"  {name:32} {n:4} substitution(s)")
