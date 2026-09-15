# runtime-proposed — ce que viper devrait porter, et ne porte pas encore

Les nouveaux idiomes s'appuient sur quelques choses que le runtime livré n'a pas. Elles sont
ici, et **seulement elles** : tout le reste vient des vrais en-têtes de `viper`, et la
référence se compile et se lie contre `libviper.a`.

C'était la limite principale du chantier, et elle est levée : une signature recopiée de
travers ne passe plus, parce que rien n'est recopié.

## Ce qu'il y a dedans

**`Viper_TypedCodec.hpp` — le codec typé.** `viper` a le codec *non typé* : une `Value` va
sur un flux (`ValueWriter`) et en revient (`ValueReader`). Ce qui manque est l'autre côté,
celui où une valeur C++ va sur le même flux — `Writer`, `Reader`, `tag<T>`, et les gabarits
génériques des conteneurs.

Le pack le génère aujourd'hui, par modèle, parce que ses méthodes portent un suffixe de type.
Rendues libres et trouvées par l'argument, il ne reste dans les classes rien qui connaisse un
modèle : leur place est le runtime.

**Et le format est un contrat, pas un choix.** Ce que ces gabarits posent sur le flux doit
être exactement ce que `Viper::ValueWriter` pose pour la Value correspondante — sans quoi le
pont statique/dynamique ne peut pas exister. Le format vient donc de `Viper_ValueWriter.cpp`,
et l'écrire une fois à côté de lui est plus sûr que le ré-émettre par forme et par modèle.

**`Viper_HashAccumulator.hpp` — le hachage sous la même forme.** `Viper::Hash` a
`combine_acc` ; ce qui manque est un accumulateur passé en premier argument. Ce n'est pas un
ornement : `hash(x)` sur un `std::uint8_t` ne peut pas marcher, un type fondamental n'ayant
aucun namespace associé, donc la recherche par argument ne mène nulle part. Un premier
argument porté par le runtime la rétablit pour tous les types.

**`Viper_Assert.hpp`, `Viper_Test.hpp`** — de quoi écrire une épreuve. Le pack les
reconstruit dans chaque modèle.

## Ce qui n'est pas ici, et pourquoi

`Viper::AnyConceptKey` reste généré par modèle. Elle devrait être du runtime — sept de ses
neuf membres ne nomment aucun concept — mais deux modèles liés dans un même programme en
définiraient chacun une, et le runtime livré n'en a pas à emprunter. Elle est écrite dans un
fichier sans dépendance, mot pour mot ce qu'elle serait là-bas, pour que le déplacement soit
une ligne le jour venu.

`Viper::Database` **n'est pas ici** : elle existe déjà dans le runtime, avec la surface qu'il
faut — `keys`, `has`, `get`, `set`, `del` sur un `Attachment` et une `ValueKey`. Le pack en
génère une copie par modèle qui ne fait que renvoyer vers `Databasing`. C'est ce que la
mesure disait, et le vrai en-tête le confirme.

## L'ordre des choses

1. le runtime gagne ces deux en-têtes ;
2. le générateur cesse de les émettre ;
3. les templates pleins-modèle cessent de déclarer leurs versions.

Rien avant l'étape 1 n'est sûr.
