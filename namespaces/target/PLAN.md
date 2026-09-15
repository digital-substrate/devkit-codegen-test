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
le pack déclare 141 opérations, les nouveaux templates 117
absentes : 0
```

**Toute la surface du pack C++ est reproduite.** Les 24 de différence sont les familles par
type qui s'effondrent en une fonction, plus ce que `coverage.py` écarte avec sa raison.

Deux sortes d'écart, et la distinction compte :

- **absorbé** — l'opération n'a pas de contrepartie et c'est voulu : le runtime enveloppé
  dans un template, les entrées/sorties en vrac d'un flux, un nom de champ devenu constante,
  un descripteur passé à l'unité ou au runtime. La raison est le nom du groupe.
- **renommé** — l'opération est là sous un autre mot, et **le script vérifie que ce mot est
  dans la sortie**. Un renommage annoncé dont le nouveau nom manque fait échouer l'outil,
  sans quoi l'écart serait un oubli déguisé.

C'est ce garde-fou qui a rattrapé la dernière affirmation faible : `toParentKey` était donné
pour « remplacé par une conversion implicite », ce que l'outil ne pouvait pas voir. Plutôt
que rendre l'exception invérifiable, l'opération a été écrite sous son nom — les deux formes
servent, l'implicite pour l'appelant qui passe la clé, la nommée pour l'expression où la
conversion ne se déclencherait pas.

## Ce que le runtime livré ne porte pas

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
sont recopiées du vrai runtime. C'est la limite principale de ce qui a été fait, et elle ne
se lèvera qu'en liant contre le vrai `viper`.

Le Python, lui, tourne contre le vrai `dsviper` — et il est à peine commencé.

## Ce qui reste

1. **Lier contre le vrai runtime.** Tant que c'est `-fsyntax-only`, une signature recopiée de
   travers passe inaperçue.
2. **Les quatre ajouts au runtime**, dans l'ordre : viper d'abord, kibo ensuite, le pack en
   dernier.
3. **Python**, dérivé du modèle et de Python. Les types et les namespaces sont écrits et
   tournent ; les attachments, les pools et la base ne le sont pas.
4. **Node, puis Swift** — dont les modules serviraient de point d'appui là où il n'y a pas
   de namespace.
5. **Puis seulement** une analyse de similarité, et les outils réutilisables qu'elle
   justifierait.

## Où regarder

| pour voir | lire |
|---|---|
| ce qui est attendu | `hand/` — la référence C++, écrite depuis le modèle |
| ce qui produit | `templated/` — les templates |
| ce que ça donne | `generated/Topology/`, `generated/Crossing/`, `generated/Features/` |
| pourquoi chaque décision | `hand/README.md`, `templated/README.md` |
| ce qui manque | `coverage.py` |
| Python | `python/README.md`, `python/hand/check.py` |

Les trois modèles ne se recouvrent pas : `Topology` porte la topologie des namespaces,
`Crossing` le système de types qui la traverse, `Features` un seul namespace avec tout le
système de types dedans. Chacun a trouvé des défauts que les autres ne pouvaient pas voir.

## Le lien contre le vrai runtime — fait

C'était la limite principale, et elle est levée. `render.py` compile les trois modèles
contre les **vrais en-têtes** de `viper`, lie le modèle topologique contre `libviper.a`, et
**exécute le programme d'épreuve** : cinq unités, trois codecs, tous les types déclarés, les
métadonnées, les trois épreuves de blob, l'aller-retour de chaque attachment sur une base
SQLite, et le fuzz.

```
  Topology    43 .cpp,  39 .hpp, tout compile
  Crossing    22 .cpp,  24 .hpp, tout compile
  Features    10 .cpp,  12 .hpp, tout compile
  crossing/hand   4 .cpp, tout compile
  lien       46 objets, et le programme tourne
```

**Les stubs ont disparu.** Il ne reste que deux fichiers dans `runtime-proposed/`, avec leur
implémentation, et ils sont ce que `viper` devrait porter :

| | pourquoi |
|---|---|
| `Viper_TypedCodec` | viper a le codec *non typé* — Value ↔ flux. Il manque l'autre côté. |
| `Viper_HashAccumulator` | `Hash::combine_acc` existe ; un accumulateur en premier argument manque |

Sur quatre ajouts annoncés, **deux existaient déjà** : `VIPER_ASSERT` est dans
`Viper_GeneralErrors.hpp`, avec une meilleure implémentation que la mienne, et le fuzz est
`Viper::Fuzzer`.

### Ce que seule l'exécution a montré

Sept défauts, dont aucun n'était visible en compilant contre des signatures recopiées :

1. **deux références à un temporaire mort** — `createDecoder` garde ce qu'on lui donne, et un
   blob non nommé meurt à la fin de l'expression. Le même défaut, à deux endroits, et le pack
   nomme le blob aux deux ;
2. **un `auto` qui créait une conversion** — `stream()` rendait une référence sur un
   temporaire, ce que le compilateur signale et que le stub ne pouvait pas produire ;
3. **un identifiant de blob inventé** — il se calcule depuis le contenu, il ne s'invente pas ;
4. **une transaction absente** — la base refuse d'écrire sans, et le pack l'ouvre ;
5. **le modèle jamais donné à la base** — `extendDefinitions` est le seul appel que la classe
   `Database` générée faisait de plus, et l'écrire ici lui retire sa dernière raison d'être ;
6. **`Viper::Database` est une `AttachmentGetting`** — la lecture d'une unité marche déjà sur
   une base, donc cinq gabarits deviennent deux ;
7. **un défaut dans le runtime** : `XArray::operator!=` s'écrit `!(this == other)` — un
   pointeur comparé à un objet. Il ne compile que tant que personne ne l'instancie, et un
   ordre qui ne demande que `<` ne le rencontre pas.

### Et la leçon de méthode

Chacune de ces corrections était **écrite dans les anciens templates**. `db->databasing()->readBlob`,
le blob nommé, la transaction, l'identifiant calculé : tout cela s'y trouve, en clair, depuis
des années. Je les avais lus pour ce qu'ils *produisent*, jamais pour ce qu'ils *appellent* —
et le stub que j'écrivais me donnait raison par construction.

Le stub était le mécanisme qui permettait de ne pas aller voir. Il n'y en a plus.
