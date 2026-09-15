# Où en est le chantier

Le critère est **l'iso-fonctionnalité** : tout ce que les templates existants produisent doit
être produit, dans les idiomes proposés ici. Pas « l'essentiel », pas « les parties
intéressantes ».

Ce document dit ce qui manque, et il n'est pas tenu à la main :

```sh
namespaces/target/coverage.py       # ce que le pack déclare et que les nouveaux n'émettent pas
namespaces/target/render.py         # rend les quatre modèles, compile, lie, exécute
namespaces/target/render.py --check # échoue si generated/ n'est pas à jour
```

`coverage.py` rend **les quatre modèles** avec les deux jeux de templates, compare les
opérations déclarées, et sort non-zéro tant qu'il en manque. Un nom suffixé par un type —
`encode_Test_StructureS` — est ramené à `encode` avant comparaison, sans quoi le décompte
dirait le contraire de ce qu'il mesure : une famille par type remplacée par une fonction
template compterait comme une perte.

## L'état, au dernier passage

```
le pack déclare 162 opérations, les nouveaux templates 178
absentes : 0
```

**Toute la surface du pack C++ est reproduite.** L'écart est fait des familles par type qui
s'effondrent en une fonction d'un côté, et des unités qui déclarent chacune ce qu'elle porte
de l'autre, plus ce que `coverage.py` écarte avec sa raison.

### Ce que la mesure ne mesurait pas

Elle a annoncé « absentes : 0 » pendant tout le temps où le `Remote` d'un pool d'attachments
n'existait pas du tout. La raison est bête et vaut d'être écrite : **elle ne tournait que
sur `features`, et `features` ne déclare aucun pool.** Pas une opération de pool n'entrait
dans la comparaison ; le décompte ne mesurait pas ce qu'il disait mesurer. Il tourne
maintenant sur les quatre modèles et prend leur réunion, parce qu'aucun ne porte tout.

Et il reste une chose qu'il ne peut pas voir : **il compare des noms, pas des portées.**
`description()` manquait sur les clés typées alors que `description(AnyConceptKey)` existait
au niveau du modèle — même mot, autre portée, écart invisible. C'est le consommateur, et non
la mesure, qui l'a trouvé.

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

Chacun porte dans son fichier la raison de sa forme.

Le Python, lui, tourne contre le vrai `dsviper` — et il est à peine commencé.

## Une dette ouverte, datée du 2026-09-15

**Le renommage du namespace de `all.dsm` (`Test` → `Demo`) a cassé la suite d'épreuves
Python du projet `features`.** Elle est écrite à la main — 16 fichiers, 4 068 lignes, 474
tests — et elle nomme les types générés : `Test_ConceptAKey` est devenu `Demo_ConceptAKey`.
Mesuré : 474 tests passaient, 69 s'exécutaient encore après régénération du paquet.

Un `Test_` → `Demo_` mécanique ne suffit pas : il en reste 3 échecs et 35 erreurs, donc
d'autres formes de noms portent le namespace. La suite TypeScript est probablement dans le
même cas ; elle n'a pas été mesurée.

**Reporté après Node, et délibérément.** Ces tests éprouvent le paquet de l'ancien pack ;
les porter maintenant serait les porter deux fois, puisque le vrai but est de les faire
tourner contre le rendu des nouveaux templates — et ça, c'est l'équivalent Python de ce que
`ServiceClient.cpp` a été pour le C++ : 4 068 lignes d'épreuves que personne ici n'a
écrites. Cette épreuve-là vaut, et elle vaudra mieux quand les quatre cibles auront une
forme arrêtée.

Rien dans le chantier ne dépend de cette suite : `check.py` ne la lance pas et n'en dit
rien. Elle est notée ici pour ne pas être oubliée, pas pour être contournée.

## Ce qui reste

1. **Les deux ajouts au runtime**, dans l'ordre : viper d'abord, kibo ensuite, le pack en
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
| ce que ça donne | `generated/Topology/`, `generated/Crossing/`, `generated/Features/`, `generated/Service/` |
| ce qu'un consommateur doit réécrire | `link/service/migrate.py` |
| pourquoi chaque décision | `hand/README.md`, `templated/README.md` |
| ce qui manque | `coverage.py` |
| Python | `python/README.md`, `python/hand/check.py` |

Les quatre modèles ne se recouvrent pas : `Topology` porte la topologie des namespaces,
`Crossing` le système de types qui la traverse, `Features` un seul namespace avec tout le
système de types dedans, `Service` les pools et le passage par un fil. Chacun a trouvé des
défauts que les autres ne pouvaient pas voir.

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
   ordre qui ne demande que `<` ne le rencontre pas ;
8. **la lecture d'un variant ignorait son index** et rendait toujours la première
   alternative -- ce qui passe tant qu'on n'éprouve que des variants dont la valeur est la
   première, et casse au premier autre ;
9. **une mat n'est pas un vec de vec** : le runtime refuse un `TypeVec` dont l'élément n'est
   pas numérique, et il faut deux surcharges distinguées par la forme du type ;
10. **l'identifiant de blob du fuzzer n'était pas épinglé** : un document peut tenir un
    `blob_id`, et la base refuse une référence vers un blob absent. Le pack épingle le
    fuzzer sur le blob vide qu'il crée autour de l'épreuve -- une ligne que j'avais lue et
    pas reportée ;
11. **la clé non typée n'avait aucune implémentation** -- quatre fonctions déclarées et rien
    qui les définisse.

### Et la leçon de méthode

Chacune de ces corrections était **écrite dans les anciens templates**. `db->databasing()->readBlob`,
le blob nommé, la transaction, l'identifiant calculé : tout cela s'y trouve, en clair, depuis
des années. Je les avais lus pour ce qu'ils *produisent*, jamais pour ce qu'ils *appellent* —
et le stub que j'écrivais me donnait raison par construction.

Le stub était le mécanisme qui permettait de ne pas aller voir. Il n'y en a plus.


## L'épreuve du consommateur

C'est la seule que je n'ai pas écrite, et c'est pour ça qu'elle vaut. `service/` porte un
client et un serveur existants, plus les deux ponts que le développeur écrit à la main.
`link/service/migrate.py` les porte sur les nouveaux noms **et rien d'autre** — chaque ligne
du script est une chose que les nouveaux templates obligent un consommateur à réécrire, et
c'est la mesure du coût de migration :

| ce que le consommateur écrivait | ce qu'il écrit | pourquoi |
|---|---|---|
| `Tools_FunctionPoolBridges.hpp` + `…Remotes.hpp` | `Tools_Pool.hpp` | un pool est une unité, et les deux bords d'un pool sont le même pool |
| `Service_FunctionPools.hpp` | — | chaque pool se construit lui-même |
| `Service::FunctionPools::tools()` | `Tools::pool()` | le nom du pool dit déjà de quel pool il s'agit |
| `Service_Definitions.hpp` | `Service_Codec.hpp` | ce qui est du modèle entier tient dans une portée |
| `Service::definitions()` | `Service::Codec::definitions()` | idem |
| `namespace Service::Tools` | `namespace Tools` | une unité est un namespace de premier rang |
| `Demo::Attachments::Player_Property::` | `Demo::Attachments::Player::property::` | un attachment a une portée, au lieu d'un nom plat |

**18 substitutions sur quatre fichiers, toutes mécaniques.** Aucune ne demande de repenser
un appel : ni un argument de plus, ni un type qui change, ni une opération qui disparaît.

Le résultat tourne, et les deux binaires ne partagent que le format :

```
  Service lien      17 objets, et le programme tourne
  service      le client parle au serveur :
     add(32,10) -> 42
     add_vector(v1,v2) -> (11,22,33)
     key is 061adb2b-…:Demo::Player
     nickname=the shadow man, level=0
```

### Ce que le consommateur a trouvé et que la mesure ne voyait pas

1. **Le `Remote` d'un pool d'attachments n'existait pas.** Le pool ordinaire avait le sien ;
   celui-là n'avait que `pool()`. Un client ne pouvait appeler aucune fonction d'attachment
   à distance — c'est-à-dire la moitié de ce à quoi un service sert.
2. **`description()` et `isKnown()` manquaient sur les clés typées.** Le pack les pose sur
   chaque clé ; ici ils n'existaient qu'au niveau du modèle, sur la clé non typée. Ils sont
   revenus, et ils répondent mieux : la réponse vient des définitions embarquées, donc un
   descendant apparu après la génération est nommé au lieu d'être déclaré inconnu.
3. **Le constructeur depuis le seul identifiant d'instance manquait.** Il est revenu
   `explicit`, là où le pack le laissait implicite : toutes les clés du modèle ont la même
   forme, donc une conversion implicite depuis `UUId` fait de n'importe quel identifiant
   n'importe quelle clé. C'est le seul rétrécissement volontaire de la surface.
4. **Les attachments prenaient une référence** là où le runtime remet partout un
   `shared_ptr` — donc chaque appel d'un pont réel devait écrire `*mutating`. Alignés sur ce
   que le runtime remet.

### Et un écart assumé, mesuré sur `Crossing`

Le pack donne à `Core::ThingKey` un `asWovenDerivedKey()` pour chaque concept qui en
descend. Donc `Core` nomme `Woven`, qui nomme `Core` : l'arête pointe dans les deux sens, et
un modèle à plusieurs unités ne peut pas la fermer. Ici le rétrécissement est chez le
descendant, qui connaît son ancêtre de toute façon : `Woven::DerivedKey::from(thing.toAny())`
rend le même `optional`, et se dit là où le type se nomme déjà.
