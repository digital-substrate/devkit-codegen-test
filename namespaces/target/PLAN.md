# Où en est le chantier

Le critère est **l'iso-fonctionnalité** : tout ce que les templates existants produisent doit
être produit, dans les idiomes proposés ici. Pas « l'essentiel », pas « les parties
intéressantes ».

Ce document dit ce qui manque, et il n'est pas tenu à la main :

```sh
namespaces/target/coverage.py       # ce que le pack déclare et que les nouveaux n'émettent pas
namespaces/target/render.py         # rend les trois modèles et compile chaque fichier
namespaces/target/render.py --check # échoue si generated/ n'est pas à jour
```

`coverage.py` rend le modèle le plus complet avec les deux jeux de templates, compare les
opérations déclarées, et sort non-zéro tant qu'il en manque. Un nom suffixé par un type —
`encode_Test_StructureS` — est ramené à `encode` avant comparaison, sans quoi le décompte
dirait le contraire de ce qu'il mesure : une famille par type remplacée par une fonction
template compterait comme une perte.

## L'état, au dernier passage

```
le pack déclare 141 opérations, les nouveaux templates 108
absentes : 9
```

Les 42 de différence ne sont pas des manques : ce sont les familles par type qui
s'effondrent en une fonction, plus ce que `coverage.py` écarte avec sa raison — le runtime
enveloppé dans un template, les entrées/sorties en vrac d'un flux, un nom de champ devenu
constante, un élargissement devenu conversion implicite.

**Ce qui manque vraiment tient en quatre familles.**

### 1. ~~Les mutations d'un champ agrégé~~ — fait

`unionF`, `subtractF`, `updateF`, `insertF`, `removeF`, `union_`, `subtract`, `update`

Un attachment dont le document est un agrégat, ou en contient un, reçoit des opérations qui
ne l'écrasent pas mais le modifient. `set` remplace le document, `update` remplace ce qui est
à une adresse ; celles-ci ajoutent, retirent ou déplacent à l'intérieur — et deux écritures
concurrentes sur le même ensemble se fondent là où deux remplacements s'écrasent.

Écrites aux deux niveaux : quand le document **est** l'agrégat, l'adresse est la racine ;
quand c'est un champ, l'adresse est celle du champ. Rien d'autre ne change, et les huit corps
sont identiques par ailleurs.

**Le fixture ne les couvrait pas** — aucun modèle ne déclarait d'attachment agrégé — donc
`crossing` gagne un ensemble, une map, un xarray et une structure qui contient les trois.

**Et le rendu a trouvé un troisième cas d'un défaut déjà vu deux fois** : les structures
étaient émises dans l'ordre de leurs noms et non de leurs dépendances, donc `Bag`, qui
contient une `Colour`, sortait avant elle. Le parent d'un concept, puis les membres d'un
club, maintenant les champs d'une structure — une unité émet dans un seul fichier, et l'ordre
de déclaration compte à chaque fois.

### 2. Les épreuves de base au-delà des attachments — 7 opérations

`test_Metadata`, `test_Blob_Create`, `test_Blob_Stream`, `test_Blob_IO`, `test_Create_Blob`,
`test_Attachments`, `test_Attachments_get`, `test_get`

L'aller-retour d'un attachment sur une base est écrit ; les épreuves des métadonnées et de
l'API blob ne le sont pas. Elles ne nomment aucun type du modèle, donc elles suivront la
forme du reste de la base de données — du code de runtime — mais cela reste à montrer plutôt
qu'à supposer.

### 3. Le JSON des définitions elles-mêmes — 1 opération

`encode_dsm_definitions`

Le modèle sait s'encoder en JSON. Une ligne, au-dessus de ce qui existe déjà.

### 4. Ce que le runtime livré ne porte pas

Hors décompte, parce que ce n'est pas un template à écrire. Les nouveaux idiomes s'appuient
sur des choses que `viper` 1.2 n'a pas sous cette forme :

| ce qui est supposé | où c'est écrit |
|---|---|
| `Viper::Codec::Writer` / `Reader` / `tag<T>` | `runtime/Viper_Codec.hpp` |
| `Viper::Hash::Accumulator` | `runtime/Viper_Hash.hpp` |
| `Viper::Database` avec les définitions en paramètre | `runtime/Viper_Database.hpp` |
| `Viper::AnyConceptKey` | généré par modèle, en attendant |

Chacun porte dans son fichier la raison de sa forme. **Rien de tout cela n'est lié ni
exécuté** : la vérification C++ est `-fsyntax-only` contre ces stubs, dont les signatures
sont recopiées du vrai runtime. C'est la limite principale de ce qui a été fait.

Le Python, lui, tourne contre le vrai `dsviper`.

## Où regarder

| pour voir | lire |
|---|---|
| ce qui est attendu | `hand/` — la référence C++, écrite depuis le modèle |
| ce qui produit | `templated/` — 18 templates |
| ce que ça donne | `generated/Topology/`, `generated/Crossing/`, `generated/Features/` |
| pourquoi chaque décision | `hand/README.md`, `templated/README.md` |
| ce qui manque | `coverage.py` |
| Python | `python/README.md`, `python/hand/check.py` |

Les trois modèles ne se recouvrent pas : `Topology` porte la topologie des namespaces,
`Crossing` le système de types qui la traverse, `Features` un seul namespace avec tout le
système de types dedans. Chacun a trouvé des défauts que les autres ne pouvaient pas voir.
