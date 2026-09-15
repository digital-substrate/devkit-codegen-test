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
