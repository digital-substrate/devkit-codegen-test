# python — la référence, écrite depuis le modèle et depuis Python

Pas depuis le C++. Les décisions qui ont tenu là-bas tenaient *parce que* C++ — l'ADL, les
templates, les namespaces imbriqués — et Python n'a rien de tout cela. Ce qui change n'est
pas l'écriture, c'est la réponse.

```sh
namespaces/target/python/hand/check.py
```

**Et elle tourne.** Le C++ était vérifié par un compilateur contre des stubs recopiés ; ici
`dsviper` est importable, donc la référence s'exécute contre le vrai runtime. Une assertion
qui passe vaut mieux qu'une signature qui compile.

## Ce que Python donne gratuitement

**Un namespace est un paquet.** Le pack met tout dans un module et aplatit en
`Test_StructureS` ; ici `ModelA::Colour` est `topology.modela.Colour` et `ModelB::Colour`
est `topology.modelb.Colour`. Les deux coexistent sans qu'un nom bouge — ce qui a déclenché
tout ce chantier coûte, en Python, une arborescence de fichiers.

**Il n'y a pas de couche codec, et pas parce qu'on l'a factorisée.** En C++, le socle portait
`encode`/`decode` parce qu'une valeur C++ et une `Value` du runtime sont deux objets qu'il
faut faire passer l'un dans l'autre. Ici une valeur générée **est** une `Value` : la classe
lui donne des noms, elle ne la copie pas. Il n'y a pas de passage, donc pas de couche pour
le faire.

**La couche 2 disparaît dans les propriétés.** En C++ il fallait `Fields::Colour::r` pour
nommer un champ et `rPath()` pour l'adresser, deux artefacts en bijection. `colour.r` est
déjà les deux.

**Et il n'y a pas de `tag<T>`.** `type()` est une `classmethod` parce que l'appelant écrit
déjà le nom de la classe. Le tag n'existait en C++ que pour donner à la recherche par
argument un namespace où aller ; sans cette recherche, il n'a pas de raison d'être.

## Ce qui reste, et qui ressemble au C++

Le socle, réduit à `definitions()`. L'identité de l'unité dans le modèle — ses identifiants
d'exécution et ses descripteurs de type — pour la même raison qu'en C++ : plusieurs choses en
ont besoin et ce n'est pas de la sérialisation.

C'est tout. Le reste de la décomposition C++ n'a pas de contrepartie ici, et c'était la
question posée en ouvrant ce dossier.

## Le périmètre, mesuré sur le pack existant

Ni plus ni moins que ce que le pack Python produit aujourd'hui. Il fait **2 200 lignes de
template** et rend **12 338 lignes** pour `features`. Voici chacun de ses artefacts, ce qu'il
devient quand le namespace est l'élément structurant, et pourquoi.

| artefact du pack | lignes de template | devient | pourquoi |
|---|---|---|---|
| `data.py` — proxies de conteneurs (`vec`, `mat`, `tuple`, `optional`, `vector`, `set`, `map`, `xarray`, `variant`) | ~700 | **rien de généré** | Un proxy de conteneur ne nomme son type qu'à un seul endroit : `mt.type<Suffixe>()`. `Optional_Colour` et `Optional_int32` sont la *même classe* avec un descripteur et un emballage d'élément différents. Une classe paramétrée, une fois, dans la couche runtime. |
| `data.py` — concepts, clubs, énumérations, structures | ~550 | **un module par unité** | C'est le seul contenu qui varie vraiment d'un modèle à l'autre, et c'est exactement le contenu d'un namespace. |
| `value_type.py` — descripteurs | 358 | **une table par unité** | Les types nommés sortent des définitions (`check_structure(runtime_id)`) ; seuls les identifiants varient. Les types de conteneurs se composent, donc un constructeur récursif suffit. |
| `path.py` — chemins de champ | 31 | **rien** | `dsviper.Path.from_field("r")` ne dépend que du nom du champ, que la propriété porte déjà. |
| `definitions.py` — `definitions()` et les identifiants | 56 | **le socle, plus une table par unité** | `definitions()` est du modèle entier ; les identifiants d'exécution appartiennent à l'unité qui les déclare. |
| `attachments.py` | 188 | **un module par unité** | Le pack écrit `modela_material_colour_get(...)` : le namespace, la clé et le document collés dans un nom parce qu'un module plat n'a pas d'autre moyen de les distinguer. |
| `database_attachments.py` | 75 | **fusionné avec le précédent** | `Database` **est** une `AttachmentGetting` en Python comme en C++. Ce qu'une base ajoute est d'écrire en rendant un statut. |
| `function_pools.py` / `..._remotes.py` | 104 | **un module par pool** | Un pool est une unité : il ne porte que des fonctions et son nom est déjà une portée. |
| `attachment_function_pools.py` / `..._remotes.py` | 111 | idem | |
| `__init__.py` | 18 | **le paquet** | |

**Une chose que le C++ a et que Python n'a pas :** il n'y a pas de pont statique à écrire.
`dsviper` expose `FunctionPool` en lecture — on interroge un pool, on appelle ses fonctions —
mais il n'offre pas de quoi en construire un depuis Python. Un pool, ici, se consomme ; il ne
se sert pas. Le pack ne produit donc que la moitié cliente, et c'est tout ce qu'il y a à
produire.

**Et une chose que Python a et que le C++ n'a pas :** `dsviper.Value.loads(objet, type,
définitions)` et `Value.dumps(valeur)` convertissent déjà entre objet Python et `Value`, en
se laissant guider par le descripteur de type. Toute la famille `encode_X` / `decode_X` du
monde C++ n'a pas de contrepartie à écrire : elle est dans le runtime, une fois.

## Les attachments, la base et un pool — écrits, et qui tournent

La question ouverte était : en C++ il fallait une portée par attachment parce qu'une
fonction ne peut pas être une valeur ; en Python elle peut. Écrit et exécuté, la réponse est
oui — **un attachment est un objet**, et `modela.attachments.material.colour.get(...)` se
lit dans les mêmes trois parties que `Attachments::Material::colour::get(...)`, sans qu'une
seule soit collée à une autre.

Et l'objet ne nomme aucun type du modèle. Il prend trois valeurs — l'identifiant de
l'attachment, la classe de la clé, celle du document — et tout le reste passe le descripteur
au runtime. Le pack écrit 188 lignes de template pour rendre 2 454 lignes de `features` ;
l'objet fait 110 lignes, une fois, et l'unité déclare cinq lignes par attachment.

```
  ok   un attachment neuf ne connaît pas la clé
  ok   après écriture, la clé est connue
  ok   et le document revient tel quel
  ok   les clés de l'attachment sont typées
  ok   un seul champ s'écrit par son nom
  ok   une clé absente rend None
  ok   l'écriture sur base rend un statut
  ok   et se relit par les mêmes appels
  ok   le retrait est la seule opération que la base ajoute
```

**La base ne demande pas un second module.** Les neuf lignes ci-dessus sont les mêmes appels,
sur `CommitMutableState` puis sur `Database.create_in_memory()`. Le pack écrit un
`database_attachments.py` entier — 1 616 lignes pour `features` — pour redire ce que la base
porte déjà sous les mêmes noms. Seul `delete` lui est propre.

**Un pool n'a qu'un bord à écrire.** `dsviper` expose de quoi interroger un pool et l'appeler,
mais rien pour en construire un ; il n'y a donc pas de pont statique comme en C++, et ce
n'est pas une omission du pack.

### Un écart entre le `.pyi` et le runtime

`dsviper/__init__.pyi` déclare `class ValueStructure(Value)`, et à l'exécution la hiérarchie
n'existe pas : `isinstance(v, dsviper.Value)` est faux pour toute valeur concrète, dont le
`__mro__` est `(ValueStructure, object)`. Rien ne permet donc de reconnaître une valeur du
runtime par son type — ce qui décide de la forme du code généré : il faut un ancêtre commun
à nos classes, seul test qui tienne. Le pack en a un (`Proxy`) ; la référence en a un pour
la même raison, découverte en écrivant.

À signaler à `viper`, avec le `XArray::operator!=` du C++.


## Le layout, et qui le fabrique

**Le générateur.** Pas `generate.py`, et l'argument est le même que celui qui a fait ce
chantier : en Python, le chemin d'un fichier *est* son namespace. Un module qui écrit
`from ..modelb import Colour` est correct à un endroit et faux partout ailleurs. Un
générateur qui rendrait des fichiers plats à charge pour un script de les déplacer ensuite
émettrait du texte faux là où il l'écrit, et juste seulement après qu'autre chose ait
tourné. Le chemin fait partie de ce qui est généré.

L'articulation existait déjà dans kibo : `TargetLayout` répond aux deux bouts de la même
question — où le rendu se pose, et par quel chemin un artefact en atteint un autre.
`PackageLayout` refusait de répondre au second (« la convention n'est pas arrêtée »). Elle
l'est maintenant :

| | C++ | paquet |
|---|---|---|
| une unité | un préfixe : `ModelA_Data.hpp` | un répertoire : `modela/data.py` |
| ce que le modèle porte | `Topology_Codec.hpp` | à la racine : `codec.py` |
| atteindre une autre unité | `#include "ModelB_Data.hpp"` | `modelb.data` |

Le nom du fichier reste celui du template : `Data.py.stg` rendu pour `ModelA` donne
`modela/data.py`. Rien n'est déduit du nom du template au-delà du retrait de l'extension —
une règle qui traduirait `Data` en `__init__.py` serait une convention cachée dans le
générateur, et un pack ne pourrait pas s'en défaire. Un pack qui veut un initialisateur
écrit un template appelé `__init__.py.stg`, et comme celui-ci déclare `unit(u)` *et*
`model(m)`, un seul fichier produit l'initialisateur de chaque unité et celui de la racine.

**Et les chemins rendus s'arrêtent à la racine du paquet**, sans les points de tête. La
profondeur d'un import relatif dépend d'où se trouve le fichier *importateur*, et c'est la
seule chose que le layout ne peut pas savoir : il est interrogé par l'artefact atteint, pas
par celui qui atteint. Un template, lui, connaît sa profondeur — il est écrit pour une unité
ou pour le modèle, jamais pour les deux. Donc la réponse est `modelb.data`, et le template
écrit `from ..<chemin> import` ou `from .<chemin> import` selon ce qu'il est. Relatif et non
absolu parce que le nom du paquet est le choix du projet, pas celui du modèle.

**Ce que `generate.py` garde**, et qui ne se déduit d'aucun modèle : où la racine du paquet
se trouve, les octets embarqués (`resources.py`), et les métadonnées de distribution
(`pyproject.toml`).

### Ce que ça donne, et ce qu'on écrit pour s'en servir

```
topology/
├── __init__.py          définitions du modèle          model(m)
├── modela/
│   ├── __init__.py      ce que l'unité expose          unit(u)
│   ├── data.py          concepts, structures, énums    unit(u)
│   └── attachments.py                                  unit(u)
├── modelb/              ... les mêmes noms, sans un renommage
└── tools/
    ├── __init__.py                                     pool(p)
    └── pool.py          le pool et son Remote          pool(p)
```

```python
from topology import definitions
from topology.modela import Colour, MaterialKey, attachments

key = MaterialKey.create()
attachments.material.colour.set(mutating, key, Colour(r=1, g=2, b=3))
attachments.material.colour.update(mutating, key, "r", 9)
attachments.material.colour.get(database, key)      # les mêmes appels sur une base
```

Et le cas qui a déclenché le chantier, écrit en entier :

```python
from topology.modela import attachments as a
from topology.modelb import attachments as b
# a.material.colour et b.material.colour : rien ne se touche.
```

Là où le pack écrit `modela_material_colour_get(...)` et `modelb_material_colour_get(...)` —
le namespace, le concept et l'attachment collés dans un identifiant parce qu'un module plat
n'a pas d'autre moyen de les distinguer.


## Les templates, et le rendu

Écrits, rendus pour les quatre modèles, et éprouvés :

```
  Features      7 modules, tous les modules s'importent
  Service      11 modules, tous les modules s'importent
  Crossing     13 modules, tous les modules s'importent
  Topology     25 modules, tous les modules s'importent
  épreuve      19 assertions sur le rendu, toutes passent
```

**Le rendu est dans `namespaces/target/generated/python/<modèle>/`**, un paquet par modèle,
à côté de `generated/cpp/<Modèle>/`. Quatre templates le produisent :

| template | entrées déclarées | rend |
|---|---|---|
| `__init__.py.stg` | `model(m)`, `unit(u)`, `pool(p)`, `attachment_pool(p)` | l'initialisateur de chaque paquet |
| `data.py.stg` | `unit(u)` | `<unité>/data.py` — concepts, clubs, énumérations, structures |
| `attachments.py.stg` | `unit(u)` | `<unité>/attachments.py` |
| `pool.py.stg` | `pool(p)`, `attachment_pool(p)` | `<pool>/pool.py` — le pool et son `Remote` |

**Ce qui ne sort pas des templates** est déposé par `render-python.py` : `resources.py`, les
octets du modèle produits par `link/resources.py`. Et rien d'autre — ce qui ne varie d'aucun
modèle est maintenant dans la liaison, sous `dsviper.codegen`, et le code rendu l'importe :

```python
from dsviper.codegen import AnyConceptKey, AttachmentProxy, Mapping, Ordered, Proxy, Sequence
from dsviper.codegen import register, unwrap, wrap
```

Neuf noms, et ils sont tout ce que la génération suppose du côté Python. `Proxy` et les trois
vues portent ce qu'une classe générée a en commun avec toutes les autres ; `AttachmentProxy`
est l'accesseur typé d'un attachment ; `wrap`, `unwrap` et `register` sont le passage entre
une valeur du runtime et un nom du modèle.

**L'épreuve est la même pour la référence et pour le rendu.** `python/check.py` prend le
paquet à éprouver : sans argument la référence écrite à la main, avec `generated/python` le
rendu des templates. Les mêmes dix-neuf assertions passent sur les deux — sans quoi la
référence ne référencerait rien.

### Ce que le rendu a demandé au générateur

Trois choses, chacune parce que Python les impose :

1. **Le layout** — une unité est un répertoire. Déjà décrit plus haut.
2. **La seconde orthographe d'un proxy** — `Colour` dans son unité, `model_a.Colour` ailleurs,
   le pendant exact de `convertTypeInNamespace` du côté natif. Un pool n'appartenant à aucun
   namespace, tout type nommé lui est étranger et se qualifie : ce n'est pas un cas
   particulier mais la règle générale appliquée à une unité qui n'a pas de types à elle.
3. **Savoir si une unité déclare le type** — une structure, une énumération, une clé ont une
   classe ; un `map<…>` ou un `xarray<…>` n'en ont pas et n'en ont pas besoin. Le pack en
   génère un par forme, donc il pouvait les nommer ; ici l'annotation est `typing.Any` et le
   runtime rend l'objet Python qui correspond. Un nom ne permet pas de distinguer les deux,
   donc le modèle le dit.


## Le typage, mesuré

La question posée était : est-ce que la liaison Python fait perdre le typage ? La réponse
était oui, et elle est mesurée avant et après.

**Avant.** 74 annotations valaient `typing.Any` — tous les champs conteneurs — et un
vérificateur ne savait rien :

```
  Type of "c.f_vector"      is "Any"
  Type of "c.f_vector[0]"   is "Any"
  x: int = c.f_vector       (aucune erreur : Any s'affecte à tout)
```

**Après.** Les trois vues sont génériques et le modèle écrit la forme entière :

```
  Type of "c.f_vector"      is "Sequence[Colour]"
  Type of "c.f_vector[0]"   is "Colour"
  Type of "c.f_optional"    is "ThingKey | None"
  Type of "c.f_map_enum"    is "Mapping[Grade, Colour]"
  Type of "c.f_variant"     is "crossing.core.data.Colour | crossing.parts.data.Colour | str"

  error  Type "Sequence[Colour]" is not assignable to declared type "int"
  error  Cannot assign to attribute "f_vector" for class "Composites"
```

La seconde erreur est la meilleure : elle refuse un `Core::Colour` là où un `Parts::Colour`
est attendu. Deux types homonymes de deux unités, séparés par un vérificateur — ce qui était
le problème de départ de tout le chantier, tenu jusque dans l'outillage.

**Une seule concession, déclarée une fois.** `wrap()` rend `typing.Any`, parce que le type
réel dépend de ce que la valeur porte. Mais il est écrit à chaque endroit qui appelle, donc
le vérificateur y trouve un type exact : ce qui est concédé est un point de passage, pas un
`Any` répandu sur chaque champ.

**`render-python.py` le vérifie maintenant à chaque rendu** — 0 erreur sur les quatre
modèles — et s'annonce non vérifié si `pyright` n'est pas là.

### Trois défauts que le vérificateur a trouvés

1. **La clé d'un club avait un `create()`**, qui passait le descripteur du club là où le
   runtime attend celui d'un concept. On ne crée pas d'instance d'un club : rien n'est « un
   Klub ». On y entre depuis la clé d'un membre, et on en sort en demandant si c'en est un.
2. **Le `Remote` d'un pool indexait des fonctions qui pouvaient être absentes.** Un service
   peut ne pas porter le pool, `is_available()` est là pour le demander, et appeler sans
   avoir demandé donnait « NoneType n'est pas indexable » — qui ne nomme ni le pool ni le
   service. C'est maintenant une erreur qui les nomme.
3. **`unwrap` construisait un ensemble d'éléments non hachables** selon son type déclaré.


## L'épreuve du projet : 474 sur 474

La seule épreuve qui n'a pas été écrite ici. `features/python/tests` fait 4 068 lignes et
474 tests, écrits contre le paquet de l'ancien pack, et `python/link/migrate.py` les porte sur
le rendu — **1 091 substitutions, rien que des renommages.** Sa longueur est le coût de
migration ; un portage à la main ne mesurerait rien.

```
  la suite    474 / 474 tests du projet, 1091 substitutions de portage
```

Elle tourne à chaque rendu. Entre le premier portage et maintenant : **155 → 474.**

### Ce que la suite a trouvé, et que rien d'autre ne pouvait trouver

L'architecture n'a jamais été mise en cause — aucun des 319 échecs ne disait qu'elle était
fausse. Tous disaient qu'une surface manquait, et deux d'entre eux étaient des défauts :

- **une clé refusait celle d'un descendant.** Élargir ne perd rien : l'identifiant d'exécution
  reste celui du concept réel, et c'est ce qui permet d'en revenir. Comparer les types à
  l'identique interdisait tout polymorphisme — `test_polymorphism` passait de 1/33 à 29/33 ;
- **`isinstance(v, dsviper.Value)` est toujours faux**, la liaison ne tenant pas la hiérarchie
  que son `.pyi` déclare. Le contrôle de type d'une vue liée ne se déclenchait donc jamais :
  une valeur du mauvais type filait jusqu'au runtime, qui la refusait par une `ViperError` et
  non par le `TypeError` que le contrat annonce. **Le fail-fast était en place et désarmé.**

Et un point de conception que seule une assertion d'identité révèle : **une forme, une
classe**. Deux appels de la fabrique pour le même type rendaient deux classes distinctes, donc
`isinstance(v, Vector_int8)` était faux pour un vecteur pourtant construit par elle. La table
par représentation de type est ce qui fait de « la même forme » la même chose.

### Deux endroits où le rendu garde sa forme contre celle du pack

Absorbés par le portage plutôt que suivis, et c'est délibéré :

- **un champ garde le nom du modèle.** Le pack coupe avant les chiffres et invente `f_uint_8`
  là où le `.dsm` dit `f_uint8` ;
- **un document absent est `None`**, et non un optional enveloppé. Python a `None` pour dire
  l'absence, et le typage l'exprime dans le retour.
