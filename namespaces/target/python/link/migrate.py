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
    (re.compile(r"\.name\(\)"), ".value"),
    (re.compile(r"(\w+)\.from_str\("), r"\1("),

    # `.name()` rendait le nom déclaré par le modèle ; sur une `enum.Enum` c'est `.value`,
    # puisque le membre porte la majuscule et la valeur porte le nom du modèle.
    (re.compile(r"\.name\b(?!\()"), ".value"),

    # UN CONSTRUCTEUR DE CLUB EST NOMMÉ DEPUIS L'UNITÉ, donc sans elle. `from_demo_concept_c_key`
    # portait le namespace parce qu'un module plat n'avait pas d'autre moyen de distinguer deux
    # membres homonymes ; ici le module le fait.
    (re.compile(r"\.from_demo_(\w+)_key\b"), r".from_\1_key"),

    # UN CHAMP GARDE LE NOM DU MODÈLE. Le pack lui applique une casse qui coupe avant les
    # chiffres — `f_uint8` devient `f_uint_8` — et invente ainsi un nom que le modèle ne
    # contient pas. Le rendu garde celui qui est déclaré.
    (re.compile(r"(?<![A-Za-z])f_uint_(8|16|32|64)\b"), r"f_uint\1"),
    (re.compile(r"(?<![A-Za-z])f_int_(8|16|32|64)\b"), r"f_int\1"),
            (re.compile(r"\bf_s\b"), "f_S"),
    (re.compile(r"\bf_t\b"), "f_T"),

    # UN DOCUMENT ABSENT EST `None`, ET NON UN OPTIONAL ENVELOPPÉ. Python a `None` pour dire
    # l'absence ; une classe pour ça n'apporterait que du poids, et le typage l'exprime dans
    # le retour. C'est le seul endroit où le portage change la forme d'un test et non un nom.
    # SEULEMENT SUR LE RÉSULTAT D'UN `get`. Un optional construit par son nom garde son
    # `is_nil()` — la vue le porte ; c'est le document rendu par un attachment qui est `None`
    # plutôt qu'un optional enveloppé.
    (re.compile(r"self\.assertTrue\((result|retrieved|doc|document)\.is_nil\(\)\)"),
     r"self.assertIsNone(\1)"),
    (re.compile(r"self\.assertFalse\((result|retrieved|doc|document)\.is_nil\(\)\)"),
     r"self.assertIsNotNone(\1)"),

    # UN `get` REND LE DOCUMENT, PAS UN OPTIONAL. C'est le seul endroit où le portage change la
    # forme d'un appel et non un nom, et c'est délibéré : Python a `None` pour dire l'absence,
    # et le typage l'exprime dans le retour. Les tests déballaient le résultat d'un `get` ; ici
    # il n'y a rien à déballer.
    (re.compile(r"\.get\(([^()]*)\)\.unwrap\(\)"), r".get(\1)"),
    (re.compile(r"\b(result|retrieved|doc|document)\.unwrap\(\)"), r"\1"),

    # `md` était l'alias du module de définitions, qui n'existe plus comme module.
    (re.compile(r"\bmd\.definitions\b"), "definitions"),
    (re.compile(r"\bmd\.RuntimeIds\.[A-Za-z]+_(\w+)\b"), r"\1"),
    (re.compile(r"\bmd\.AttachmentRuntimeIds\.[A-Za-z]+_(\w+)\b"), r"\1"),
    (re.compile(r"(?m)^from features import definitions$"),
     "from features import definitions\nfrom features.demo import data as md"),
    # UN IDENTIFIANT D'EXÉCUTION EST UNE CONSTANTE, donc en majuscules — convention de Python
    # que le pack n'applique pas à ses `RuntimeIds`.
    (re.compile(r"\bmd\.(?:Attachment)?RuntimeIds\.(?:[A-Za-z]+_)?(\w+)\b"),
     lambda m: "md." + re.sub(r"(?<!^)(?=[A-Z])", "_", m.group(1)).upper()),

    # `f_e` : un champ dont le nom du modèle porte une capitale que la casse du pack efface.
    (re.compile(r"\bf_e\b"), "f_E"),
    (re.compile(r"\bf_v\b"), "f_V"),
    (re.compile(r"\bf_u\b"), "f_U"),
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
            table[_flat(scope) + "_" + _flat(name)] = f"{scope}.{name}"
    return table


def _flat(name: str) -> str:
    """Le nom tel que le pack l'aplatit : une coupure avant chaque capitale et chaque chiffre.

    `propertiesInt8` devient `properties_int_8`. C'est la casse que le pack applique et que le
    rendu n'applique pas — il garde le nom déclaré par le modèle — donc c'est ici que les deux
    se rencontrent.
    """
    return re.sub(r"(?<!^)(?=[A-Z])|(?<=[A-Za-z])(?=[0-9])", "_", name).lower()


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

        # `del` EST UN MOT-CLÉ, DONC L'OPÉRATION S'APPELLE `delete`. Le pack la nomme `_del`
        # dans un identifiant plat, où le mot n'a pas de sens syntaxique ; sur un objet il en a
        # un, et `x.del(...)` ne se compile pas. Un fichier entier — dix-neuf tests — mourait là.
        text, n = re.subn(r"\b(ma|db)\.((?:test|demo)_\w+)_del\b", r"\1.\2_delete", text)
        touched += n

        for flat, scoped in sorted(TABLE.items(), key=lambda kv: -len(kv[0])):
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
