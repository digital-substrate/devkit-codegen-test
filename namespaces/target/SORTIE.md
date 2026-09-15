# Sortir du mode exploratoire

Ce document dit **à quelles conditions** le chantier cesse d'être une exploration, et **ce
qu'il faut faire alors**. Il ne dit pas quand : les conditions le diront.

Tant qu'elles ne sont pas réunies, tout reste ici, sous `namespaces/target/`, et c'est
délibéré — un dépôt publié ne doit pas porter le va-et-vient d'une exploration.

## Les conditions

Cinq, et chacune se mesure. Aucune n'est une opinion.

| condition | comment on la constate | où on en est |
|---|---|---|
| **1. Tout passe, sur toutes les cibles** | `namespaces/target/check.py --check` sort zéro | C++ ✅ Python ✅ Node ❌ (n'existe pas) |
| **2. Chaque cible a passé une épreuve écrite par quelqu'un d'autre** | un consommateur existant tourne contre le rendu, porté par renommages seulement | C++ ✅ (`ServiceClient`/`ServiceServer`, 18 substitutions) · Python ❌ (`features/python/tests`, 474 tests) · Node ❌ |
| **3. Le Template Model a cessé de grossir** | la dernière cible ajoutée n'a réclamé aucun champ nouveau à kibo | ❌ — Python en a réclamé cinq (portée de layout, `typeInNamespace` de liaison, `isNamed`, `annotation`, `attachmentScopes`). **Node est l'épreuve de cette condition** |
| **4. Ce qui manque aux runtimes est figé** | `runtime-proposed/` inchangé sur un tour complet des quatre modèles et des trois cibles | ❌ — `dsviper_codegen` a gagné `container.py` cette semaine |
| **5. Chaque cible a une mesure de couverture** | un décompte opération par opération contre le pack existant, sur tous les modèles | C++ ✅ (162 opérations, 0 absente) · Python ❌ · Node ❌ |

**La condition 3 est la vraie.** Les quatre autres se rattrapent ; celle-là dit si le contrat
que kibo offre aux templates est stable. Une cible de plus qui ne demande rien de neuf est la
seule preuve possible qu'il l'est — et c'est pourquoi Node se fait avant le rangement, pas
après.

## Axe 1 — les templates dans `kibo-template-viper`

Le pack y est déjà rangé par langage, et par dossier de fonctionnalité pour le C++ : 17
dossiers, 73 `.stg`, 8 737 lignes. **Cette forme est la bonne et il faut la garder** : un
dossier est l'unité que `-t` désigne, donc c'est l'unité qu'un projet choisit. Toutes les
templates ne sont pas obligatoires, et c'est le dossier qui le permet.

Ce que les nouveaux templates deviennent — 20 `.stg` C++ aujourd'hui à plat, 4 en Python :

### C++ — six dossiers au lieu de dix-sept

| dossier | ce qu'il contient | rend | obligatoire |
|---|---|---|---|
| `Model` | `Data`, `Fields`, `Model` | les types d'une unité, ses champs, son identité dans le modèle | **oui** — tout en dépend |
| `Codec` | `Codec`, `AnyConcept` | le passage valeur ↔ flux, la clé non typée | oui dès qu'on sérialise |
| `Attachments` | `Attachments`, `AttachmentPool` | les attachments d'une unité, et le pool dynamique du modèle | non |
| `Database` | `Db` | les deux opérations qu'une base ajoute — `set`, `del` | non ; réclame `Attachments` |
| `Service` | `Pool` | un pool, son pont dynamique et son `Remote` | non |
| `Test` | `Test`, `TestApp` | l'épreuve par unité et le programme qui l'appelle | non |

Dix-sept dossiers deviennent six parce que onze d'entre eux n'avaient rien à générer :
mesuré, 11 des 13 templates de `Database` sortaient identiques pour deux modèles sans
rapport — 1 607 lignes, zéro différence. C'était du runtime déguisé en template.

### Python — trois dossiers, et deux qui n'existent pas

| dossier | ce qu'il contient | obligatoire |
|---|---|---|
| `Model` | `__init__.py`, `data.py` | **oui** |
| `Attachments` | `attachments.py` | non |
| `Service` | `pool.py` | non |

**Il n'y a ni `Codec` ni `Database`, et c'est un résultat, pas un oubli.** Une valeur générée
*est* une `Value` du runtime, donc il n'y a pas de passage à écrire ; et `Database` porte les
mêmes `keys`, `has`, `get`, `set` qu'un état en mémoire, donc rien à générer non plus. Que la
forme du pack le montre est exactement ce qu'on veut d'un rangement.

### Comment le déplacement se fait

- **une branche du pack, puis une version MAJEURE.** Le rendu change entièrement de forme,
  donc ce n'est pas une évolution ; `kibo` 2.0 en est le plancher ;
- **les anciens dossiers restent** tant qu'un projet consommateur ne les a pas quittés. Les
  deux jeux coexistent sans effort puisque `-t` désigne un dossier ;
- **chaque dossier documente ses dépendances** — `Database` réclame `Attachments`, qui
  réclame `Model`. Une sélection incohérente échoue à la compilation, ce qui est tard ; le
  dire dans le README du dossier est ce qui coûte le moins et suffit.

## Axe 2 — `generate.py` et la sélection

**Aucune modification de kibo n'est nécessaire**, et c'est le point à vérifier avant tout le
reste : `-t` prend un chemin, `generate.py` boucle sur une liste de noms de dossiers, un
appel par dossier. Le mécanisme de sélection existe déjà et il est le bon.

```python
# aujourd'hui, dans features/generate.py
templates = ['Model', 'Data', 'Stream', 'Json', 'Database',
             'Attachments', 'AttachmentFunctionPool_Attachments',
             'ValueType', 'ValueCodec', 'ValueHasher', 'Test']
```

Ce qui change :

1. **la liste se raccourcit** et devient lisible — `['Model', 'Codec', 'Attachments',
   'Database', 'Test']` — parce qu'elle nomme des fonctionnalités et non des artefacts ;
2. **une liste par langage**, puisque les fonctionnalités ne se recouvrent pas d'un langage
   à l'autre ;
3. **la sélection appartient au projet et doit y rester.** Kibo ne voit jamais un pack, seulement
   ce que `-t` désigne : il n'y a donc pas de manifeste à consulter et rien à tenir en phase.
   C'est une propriété à préserver, pas une limite à contourner ;
4. **`generate.py` dépose aussi ce qui ne sort pas des templates** : les octets du modèle
   (`resources`), et — tant que les runtimes ne les portent pas — le contenu de
   `runtime-proposed/`. Ce dépôt disparaît quand la condition 4 est remplie.

## Axe 3 — les épreuves en face des dossiers générés

C'est la forme qu'un projet fini a déjà, et qu'il suffit de suivre :

```
features/
├── all.dsm                    les définitions
├── generate.py                le pilote du projet
├── Features/                  le rendu C++
├── Features_Test_*.cpp        l'épreuve C++, écrite à la main
├── python/{features,tests}/   le rendu Python, et son épreuve
└── typescript/{features,test}/
```

**Un rendu par cible, et en face de chacun son épreuve.** La règle à tenir :

- **l'épreuve est écrite à la main et ne se réécrit pas.** `features/python/tests` fait
  4 068 lignes et 474 tests ; `Features_Test_*.cpp` et le service en font autant côté C++.
  Ce sont eux qui disent ce qu'un consommateur attend, précisément parce que personne ici ne
  les a écrits ;
- **elle se porte une fois, par un script qui est la mesure du coût.**
  `cpp/link/service/migrate.py` en est le modèle : il ne contient que des renommages, chacun
  avec sa raison, et sa longueur *est* le coût de migration — 18 substitutions sur quatre
  fichiers. Un portage à la main ne mesure rien ;
- **le code d'épreuve généré ne remplace pas celui qui est écrit.** Le `Test` par unité
  vérifie que chaque type se sérialise ; il ne vérifie pas qu'une API est agréable ni qu'un
  appel réel marche. Les deux servent.

### La dette ouverte

Le renommage `Test` → `Demo` dans `all.dsm` a cassé `features/python/tests` : 474 tests
passaient, 69 s'exécutent encore. Un remplacement mécanique laisse 3 échecs et 35 erreurs,
donc d'autres formes de noms portent le namespace ; la suite TypeScript n'a pas été mesurée.

**Elle se répare au moment du portage, pas avant.** Ces tests éprouvent le paquet de l'ancien
pack ; les réparer aujourd'hui serait les porter deux fois.

## L'ordre

1. **Node**, dérivé de zéro comme Python l'a été — c'est l'épreuve de la condition 3 ;
2. **les runtimes** : `viper` puis `dsviper` reçoivent ce que `runtime-proposed/` contient.
   Rien ne part tant que les trois cibles ne sont pas d'accord sur ce qu'il faut ;
3. **kibo** : la version qui porte le contrat définitif du Template Model ;
4. **le pack** : les dossiers ci-dessus, sur une branche, en version majeure ;
5. **les projets** : `generate.py` réécrit, les épreuves portées par un script qui mesure.

Chaque étape attend la précédente pour une raison : un pack publié contre un kibo qui bouge
encore oblige à republier le pack, et un projet porté contre un pack qui bouge oblige à
porter deux fois.
