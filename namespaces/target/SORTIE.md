# Sortir du mode exploratoire

Ce document dit **à quelles conditions** le chantier cesse d'être une exploration, et **ce
qu'il faut faire alors**. Il ne dit pas quand : les conditions le diront.

Tant qu'elles ne sont pas réunies, tout reste ici, sous `namespaces/target/` — un dépôt
publié ne doit pas porter le va-et-vient d'une exploration.

## Les conditions

Cinq, et chacune se mesure. Aucune n'est une opinion.

| condition | comment on la constate | où on en est |
|---|---|---|
| **1. Tout passe, sur toutes les cibles** | `check.py --check` sort zéro | C++ ✅ Python ✅ Node ❌ (n'existe pas) |
| **2. Chaque cible a passé une épreuve écrite par quelqu'un d'autre** | un consommateur existant tourne contre le rendu, porté par renommages seulement | C++ ✅ (`ServiceClient`/`ServiceServer`, 18 substitutions) · Python ❌ (`features/python/tests`, 474 tests) · Node ❌ |
| **3. Le Template Model a cessé de grossir** | la dernière cible ajoutée n'a réclamé aucun champ nouveau à kibo | ❌ — Python en a réclamé cinq. **Node est l'épreuve de cette condition** |
| **4. Ce qui manque aux runtimes est figé** | `runtime-proposed/` inchangé sur un tour complet des modèles et des cibles | ❌ — `container.py` vient d'y entrer |
| **5. Chaque cible a une mesure de couverture** | un décompte opération par opération contre le pack existant | C++ ✅ (162 opérations, 0 absente) · Python ❌ · Node ❌ |

**La condition 3 est la vraie.** Les autres se rattrapent ; celle-là dit si le contrat que
kibo offre aux templates est stable. Une cible de plus qui ne demande rien de neuf est la
seule preuve possible qu'il l'est — et c'est pourquoi Node se fait avant le rangement.

---

## Axe 1 — la fonctionnalité, et non le dossier

C'est le point de départ, parce qu'il change les trois autres.

### Ce que le pack fait aujourd'hui, et ce qui cloche

Le pack range ses templates **par dossier de fonctionnalité** — 17 dossiers C++ — et `-t`
désigne un dossier, donc le dossier *est* l'unité de sélection. Cela marche tant qu'une
template appartient à une fonctionnalité et à une seule.

Ce n'est pas vrai. `Codec` est réclamé par `Database`, par `Attachments` et par `Service` ;
un dossier l'oblige à choisir un foyer, et les autres à l'inclure par un chemin détourné.

### Ce qu'il faut à la place

**Les templates à plat, un dossier par langage, et la fonctionnalité déclarée au-dessus.**

```
kibo-template-viper/
├── cpp/                        toutes les templates C++, à plat
│   ├── Data.hpp.stg  Data.cpp.stg  Fields.hpp.stg  …
│   └── features.json           ← ce que chaque fonctionnalité réclame
├── python/
└── node/
```

```json
{
  "Model":       {"templates": ["Data", "Fields", "Model", "AnyConcept"]},
  "Codec":       {"templates": ["Codec"],       "requires": ["Model"]},
  "Json":        {"templates": ["Json"],        "requires": ["Codec"]},
  "Attachments": {"templates": ["Attachments", "AttachmentPool"], "requires": ["Codec"]},
  "Database":    {"templates": ["Db"],          "requires": ["Attachments"]},
  "Service":     {"templates": ["Pool"],        "requires": ["Codec"]},
  "ServiceClient": {"templates": ["PoolRemote"], "requires": ["Service"]},
  "Test":        {"templates": ["Test", "TestApp"], "requires": ["Attachments", "Database"]}
}
```

Ce que ça gagne, et qu'un dossier ne peut pas donner :

- **une template sert plusieurs fonctionnalités** sans être dupliquée ni déplacée ;
- **la fonctionnalité devient un mot que l'utilisateur prononce** — « je veux `Database` » —
  et le résolveur ferme le graphe : `Model`, `Codec`, `Attachments`, `Database` ;
- **le dossier redevient ce qu'il doit être** : un rangement pour qui lit, et non une
  contrainte pour qui choisit.

### La règle qui en découle, et que j'ai enfreinte

**Une template est le plus petit grain qu'on puisse ne pas vouloir.** Tout ce qu'un projet
peut refuser doit donc être un fichier `.stg` à lui.

J'ai fusionné trois frontières que le pack avait, et chacune est une chose qu'un projet
voudra refuser :

| ce que le pack sépare | ce que j'en ai fait | pourquoi c'est une perte |
|---|---|---|
| `FunctionPool` / `FunctionPoolRemote` | un seul `Pool.hpp/.cpp` | **la plupart des projets n'exposent pas leurs pools en service** et ne veulent pas du `Remote` |
| `AttachmentFunctionPool` / `…Remote` | idem | idem |
| `Json` | quelques fonctions dans `Codec.hpp` | un projet qui ne veut pas de JSON n'a pas de moyen de le dire |

Je les avais fusionnées avec un argument qui se lit bien — « les deux bords d'un pool sont le
même pool » — et qui ignore la seule question qui compte ici : **est-ce qu'un projet peut
vouloir l'un sans l'autre ?** Pour ces trois-là, oui.

**À faire** : scinder `Pool` en `Pool` + `PoolRemote`, et sortir `Json` de `Codec`.

---

## Axe 2 — `generate.py`, et une seule invocation

Aujourd'hui `generate.py` recopie une liste de noms de dossiers et appelle kibo une fois par
dossier. Demain il demande des fonctionnalités :

```python
features = ['Database', 'Test']          # ce que le projet veut
templates = resolve(features, 'cpp')     # ce que ça réclame, fermé et ordonné
```

**Une seule modification de kibo, et elle est petite** : `-t` doit pouvoir être répété.
Aujourd'hui c'est un `Path`, il faut une `List<Path>` — JCommander accumule les répétitions,
et `AppUtils.collectTemplates` sait déjà prendre un fichier comme un dossier. Un seul
démarrage de JVM au lieu d'un par fonctionnalité.

**Et kibo ne voit toujours pas de pack.** Il rend exactement ce qu'on lui désigne ; le
manifeste est lu par le pilote, pas par lui. Ce n'est pas une limite à contourner mais une
propriété à préserver : un projet peut écrire ses propres templates dans un répertoire et
kibo les rend, sans rien déclarer nulle part.

Le résolveur, lui, est livré avec le pack — `kibo-template-viper/tools/features.py` — parce
que le pack est la seule chose qui connaisse ses fonctionnalités.

`generate.py` dépose en plus ce qui ne sort pas des templates : les octets du modèle, et —
tant que les runtimes ne les portent pas — le contenu de `runtime-proposed/`.

---

## Axe 3 — le graphe, mesuré et vérifiable

### Il se lit dans ce qui est rendu

Mesuré sur `Topology`, en lisant les `#include` émis :

```
en-tête → en-tête (doit être acyclique)
   Attachments  → Model            Database → Codec
   Codec        → Model            Service  → Model
   Test         → Codec, Database
   cycles : aucun

implémentation → en-tête (peut ne pas l'être)
   Attachments  → Codec, Database, Model      Codec → Model
   Model        → Codec                       Service → Codec, Model
   Test         → Attachments, Codec, Model, Service
```

**Deux graphes et non un.** Un en-tête qui en inclut un autre crée une dépendance qui doit
être acyclique ; une implémentation qui inclut un en-tête n'en crée pas. `Model` et `Codec`
se référencent mutuellement en implémentation — `Data.cpp` demande au codec de décrire une
clé, `Codec.cpp` a besoin des types — et c'est sans conséquence.

**La première mesure a trouvé un cycle, et il venait de mon groupement.** `AnyConcept` était
rangé avec `Codec` ; or toute clé typée déclare `toAny()`, donc `Data.hpp` inclut
`AnyConcept.hpp` pendant que `Codec.hpp` inclut `Data.hpp`. La clé non typée est du système
de types, pas de la sérialisation : elle appartient à `Model`. Aucune lecture ne me l'avait
dit.

### La déclaration doit être confrontée à ce qui sort

Une dépendance déclarée qui se périme en silence est pire que pas de déclaration : la
sélection cesse d'être fermée, et l'erreur sort à la compilation d'un projet consommateur, à
l'autre bout de la chaîne.

**L'épreuve** : rendre une sélection, et vérifier que chaque `#include` émis nomme un fichier
que la sélection a produit, ou un en-tête du runtime. Si `Database` seule émet un
`#include "Topology_Codec.hpp"` alors que `Codec` n'est pas dans sa clôture, la déclaration
est fausse, et le script le dit là où c'est réparable.

### Ce qui reste ouvert

- **une fonctionnalité peut-elle dépendre d'une autre pour une partie seulement de ce qu'elle
  émet ?** `Attachments` ne réclame `Database` que pour deux surcharges — `set(db, …)` et
  `del(db, …)`. Un projet sans base veut les attachments sans elles. C'est une template de
  plus (`AttachmentsDb`) ou une option de rendu ; à trancher en mesurant ce que coûte chacune ;
- **le graphe n'est pas le même d'un langage à l'autre.** Python n'a ni `Codec` ni
  `Database` — une valeur générée *est* une `Value`, et une base porte les mêmes appels qu'un
  état en mémoire. Donc un manifeste par langage, et non un par fonctionnalité.

---

## Axe 4 — les épreuves en face des dossiers générés

C'est la forme qu'un projet fini a déjà :

```
features/
├── all.dsm                    les définitions
├── generate.py                le pilote du projet
├── Features/                  le rendu C++
├── Features_Test_*.cpp        l'épreuve C++, écrite à la main
├── python/{features,tests}/   le rendu Python, et son épreuve
└── typescript/{features,test}/
```

**Un rendu par cible, et en face de chacun son épreuve.** Trois règles :

- **l'épreuve écrite à la main ne se réécrit pas.** `features/python/tests` fait 4 068 lignes
  et 474 tests ; ils disent ce qu'un consommateur attend précisément parce que personne ici ne
  les a écrits ;
- **elle se porte une fois, par un script qui est la mesure du coût.**
  `cpp/link/service/migrate.py` en est le modèle : rien que des renommages, chacun avec sa
  raison, et sa longueur *est* le coût — 18 substitutions sur quatre fichiers. Un portage à la
  main ne mesure rien ;
- **le code d'épreuve généré ne remplace pas celui qui est écrit.** Le `Test` par unité
  vérifie que chaque type se sérialise ; il ne dit rien de ce qu'un appel réel fait.

### La dette ouverte

Le renommage `Test` → `Demo` dans `all.dsm` a cassé `features/python/tests` : 474 tests
passaient, 69 s'exécutent encore. Un remplacement mécanique laisse 3 échecs et 35 erreurs,
donc d'autres formes de noms portent le namespace ; la suite TypeScript n'a pas été mesurée.

**Elle se répare au moment du portage, pas avant** : ces tests éprouvent le paquet de l'ancien
pack, et les réparer aujourd'hui serait les porter deux fois.

---

## L'ordre

1. **Node**, dérivé de zéro comme Python l'a été — l'épreuve de la condition 3 ;
2. **les runtimes** : `viper` puis `dsviper` reçoivent ce que `runtime-proposed/` contient.
   Rien ne part tant que les trois cibles ne sont pas d'accord sur ce qu'il faut ;
3. **kibo** : le contrat définitif du Template Model, et `-t` répétable ;
4. **le pack** : les templates à plat par langage, le manifeste, le résolveur ;
5. **les projets** : `generate.py` demande des fonctionnalités, les épreuves sont portées par
   un script qui mesure.

Chaque étape attend la précédente pour une raison : un pack publié contre un kibo qui bouge
oblige à republier le pack, et un projet porté contre un pack qui bouge oblige à porter deux
fois.
