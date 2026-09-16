# Le chantier : les namespaces comme élément structurant

**Tout se lance d'ici, par une seule commande.**

```sh
namespaces/target/check.py            # rend tout, compile, lie, exécute, éprouve, type
namespaces/target/check.py --check    # la même chose, et échoue si le rendu versionné est périmé
```

Elle enchaîne les quatre instruments et rend un verdict unique. Chacun reste lançable seul,
mais il n'y a plus à savoir lesquels ni dans quel ordre.

## Où est quoi

```
namespaces/target/
├── check.py                    LA porte : tout, en une commande
│
├── cpp/                        la cible C++
│   ├── templated/              ← LES TEMPLATES C++ (21 fichiers .stg)
│   ├── hand/                   la référence écrite à la main, avant tout template
│   ├── link/                   ce qui ne sort pas des templates : les octets du modèle,
│   │                           le code d'application, le portage du service existant
│   ├── render.py               rend, compile, lie contre libviper.a, exécute
│   └── coverage.py             compare aux 162 opérations du pack existant
│
├── python/                     la cible Python
│   ├── templated/              ← LES TEMPLATES PYTHON (4 fichiers .stg)
│   ├── hand/                   la référence écrite à la main
│   ├── render.py               rend, importe tout, éprouve, vérifie les types
│   └── check.py                les assertions ; tournent sur la référence ou sur le rendu
│
├── generated/                  LE RENDU, rangé par cible et par modèle
│   ├── cpp/{Topology,Crossing,Features,Service}/
│   └── python/{topology,crossing,features,service}/
│
├── runtime-proposed/           ce que le runtime devrait porter et ne porte pas
│   ├── cpp/                    Viper_TypedCodec, Viper_HashAccumulator
│   └── python/                 le paquet destiné à devenir `dsviper.codegen`
│
└── build/                      objets et binaires — jamais versionné
```

Un template C++ est dans `cpp/templated/`, un template Python dans `python/templated/`. Les
deux cibles ont la même forme : `templated/`, `hand/`, `render.py`. Ce qui diffère est ce que
la cible réclame en plus — `link/` et `coverage.py` pour le C++, rien pour Python.

## Comment tout ce qui est généré est vérifié

Chaque étape prouve une chose et pas la suivante ; c'est l'empilement qui vaut, et chacune
a trouvé des défauts qu'aucune autre ne pouvait voir.

| étape | ce qu'elle prouve | ce qu'elle ne prouve pas |
|---|---|---|
| rendu C++ | les templates produisent un fichier par unité, sans diagnostic | que ça compile |
| compilation | chaque fichier est du C++ valable contre les **vrais** en-têtes de viper | que ça se lie : une signature recopiée de travers passe |
| lien | chaque symbole appelé existe dans `libviper.a` | que ça marche |
| exécution | le programme d'épreuve tourne : tous les types, les métadonnées, les blobs, l'aller-retour de chaque attachment sur SQLite, le fuzz | |
| service | un client et un serveur **existants**, portés par renommage seulement, parlent par une socket | |
| couverture | les 162 opérations du pack sont émises, ou écartées avec une raison | elle ne voit que des **noms** : un déplacement de portée lui est invisible |
| rendu Python | un paquet par modèle, et **chaque module s'importe** — syntaxe, dépendances, classes construites, descripteurs trouvés | |
| assertions | les mêmes 23 sur la référence écrite à la main et sur le rendu | |
| types | `pyright` et `tsc --strict` ne trouvent aucune erreur : les annotations tiennent | |
| fail-fast | une valeur du mauvais type est rejetée **là où elle apparaît**, dans les trois cibles | |

**Sept défauts n'étaient visibles qu'au lien, et aucun avant.** Deux références à un
temporaire mort, un `auto` qui créait une conversion, un identifiant de blob inventé, une
transaction absente, le modèle jamais donné à la base, et un défaut dans viper lui-même.
C'est pourquoi `-fsyntax-only` ne suffit pas et pourquoi le lien est dans la chaîne.

## Le fail-fast, et pourquoi il est hérité

**Un proxy ne détient rien.** C'est une boîte vide devant une `Value` : chaque écriture passe
par `value.set(...)`, donc atteint le runtime, qui lève son exception typée. Le fail-fast
n'est pas implémenté par le code généré, il en découle — à condition que rien dans la couche
générée ne l'intercepte ni ne le contourne. C'est ça qu'il faut vérifier, et c'est ce que
`checks/*failfast*` vérifie, sur le rendu et pas sur une référence.

Deux sortes d'erreur, et les deux comptent :

- **du runtime** — une valeur du mauvais type atteint `set`, et `ViperError` sort ;
- **du code généré** — un constructeur refuse une `Value` qui n'est pas la sienne, avant même
  qu'une écriture ait lieu. En Python ce sont des `raise` et non des `assert`, donc le contrat
  tient aussi sous `python -O` ; en C++ le rendu ne contient aucun `assert`.

**Deux endroits où il ne tenait pas, trouvés en le mesurant :**

1. **`wrap` rendait la valeur nue** quand un type n'avait pas de classe enregistrée, au lieu
   d'échouer. C'est le seul repli que j'avais introduit, et c'était un mensonge contre
   l'annotation — que le typage ne peut pas rattraper et qui se découvre bien plus loin, sur
   un attribut absent. Il échoue maintenant, en nommant le type et l'unité manquante.
2. **La liaison Node n'oppose rien à un document du mauvais type.** Mesuré au niveau du
   runtime, pas de ma couche : écrire un `Parts::Colour` dans un attachment déclaré
   `Core::Colour` est accepté et se relit tel quel. La liaison Python refuse la même écriture.
   La vérification est donc dans le socle Node, marquée comme un pis-aller, **à retirer le
   jour où la liaison vérifie** — et à signaler d'ici là.

**Et trois défauts n'étaient visibles que du consommateur** — le `Remote` d'un pool
d'attachments qui n'existait pas, `description()` et `isKnown()` disparus des clés typées —
alors que la couverture annonçait « absentes : 0 ». Elle ne tournait que sur un modèle sans
pool. C'est corrigé, et c'est la raison d'être de l'épreuve du service.

## Ce qui reste à ranger, et où ça ira

**Le plan de sortie est dans [`SORTIE.md`](SORTIE.md)** : les cinq conditions qui disent
quand l'exploration s'arrête, et les trois axes du rangement — les templates dans
`kibo-template-viper`, `generate.py` et sa sélection, les épreuves en face des dossiers
générés.

Tout vit sous `namespaces/`, qui est le nom d'un des quatre modèles. C'est un reste de la
phase exploratoire et ce n'est pas tenable : le chantier n'appartient pas à ce modèle-là.
**On reste ainsi pour l'instant**, le temps de voir à quoi le projet fini ressemble — il
reste Node, et une cible qui n'existe pas peut encore déplacer une décision.

Les trois destinations sont connues, et elles ne sont pas ici :

| ce qui est ici | où ça ira | pourquoi pas encore |
|---|---|---|
| `cpp/templated/`, `python/templated/` | **`kibo-template-viper`** — c'est le pack, et ces templates sont le pack de demain | ils changent encore à chaque défaut trouvé ; les déplacer maintenant ferait porter à un dépôt publié le va-et-vient d'une exploration |
| `generated/` | les répertoires de chaque projet, produits par son `generate.py` | le rendu est versionné ici parce que `--check` le compare à un rendu neuf : c'est ce qui rend une régression visible dans un diff. Ce rôle disparaît quand les templates sont figés |
| `cpp/hand/`, `python/hand/` | rien — ce sont des références, pas des livrables | elles restent tant qu'elles trouvent des défauts que le rendu ne trouve pas |
| `runtime-proposed/cpp`, `runtime-proposed/python` | **`viper`** et **`dsviper`** | l'ordre est viper d'abord, kibo ensuite, le pack en dernier ; rien ne part tant que les trois ne sont pas prêts ensemble |

Et le code d'épreuve devra être **généré en face** du code rendu, au lieu d'être écrit à
côté : un `Test` par unité existe déjà côté C++, mais l'application qui l'appelle et le
programme de service sont encore écrits à la main dans `cpp/link/`.
