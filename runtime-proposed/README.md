# runtime-proposed — ce que viper devrait porter, et ne porte pas encore

Les nouveaux idiomes s'appuient sur quelques choses que le runtime livré n'a pas. Elles sont
ici, et **seulement elles** : tout le reste vient des vrais en-têtes de `viper`, et la
référence se compile et se lie contre `libviper.a`.

C'était la limite principale du chantier, et elle est levée : une signature recopiée de
travers ne passe plus, parce que rien n'est recopié.

## Trois sociétés, et ce qui revient à chacune

Le critère qui place chaque pièce : **viper** complète *sa propre* dual-reality, quelle que
soit la façon de l'exposer ; **kibo** fournit ce dont n'importe quel template a besoin et que
StringTemplate ne sait pas calculer ; **le pack** construit *une* exposition parmi d'autres,
et a droit à ses propres outils pour cela.

« Une parmi d'autres » porte sur la **forme** des classes, pas sur leur **mise en page**. Deux
packs peuvent façonner différemment le côté statique ; ils ne peuvent pas le sérialiser
différemment, parce qu'il n'existe qu'une mise en page — celle que `ValueReader` relit.

## Le dépliage statique — déplacé dans viper

`Viper_TypedCodec` a quitté ce dossier le 2026-09-29. Il vit désormais sur la branche
`kibo-2-dev` de viper, à côté de ce qu'il déplie :

| viper | rôle |
|---|---|
| `Viper_StaticType.hpp` | `tag<T>` et la correspondance type C++ ↔ descripteur, partagée |
| `Viper_StaticWriter.hpp/.cpp` | le dépliage statique de `ValueWriter` |
| `Viper_StaticReader.hpp/.cpp` | le dépliage statique de `ValueReader` |
| `cpp-test-harness/Viper_StaticLayout_test.cpp` | le contrat |

Le nom dit ce que c'est : la moitié statique de `ValueWriter`/`ValueReader`, avec le mot que
la documentation emploie pour ce côté de la dual reality. `Viper::Codec` reste le registre des
codecs, qu'il ne fallait pas rouvrir.

**Le contrat se vérifie sur la suite des appels à `StreamWriting`**, enregistrée — pas sur des
octets. C'est ce qui le rend indépendant de l'encodage, et c'est ce qui a démasqué deux
défauts du code d'ici, invisibles à un aller-retour :

- un `vec` et un `mat` étaient écrits élément par élément, là où `ValueWriter` les écrit d'un
  seul appel par tableau. Sous `StreamBinary`, que le pont emploie, les octets coïncident ;
  sous `StreamTokenBinary`, non ;
- la correspondance de type d'un `mat` inversait colonnes et lignes. Un aller-retour par le
  même code la compense exactement ; seule une `ValueMat` bâtie case par case la voit.

Chacun a été réintroduit pour vérifier que le test le rattrape — il le fait, par le cas qui le
vise.

**Ce que ça impose ici** : la branche `kibo-2-dev` de ce dépôt se construit contre celle de
viper. `lib.cmake` le vérifie et échoue tôt sinon ; `REPO_VIPER` désigne le checkout, un
worktree gardant l'arbre voisin sur sa propre branche.

## `Viper_HashAccumulator.hpp` — ne revient pas à viper

Son unique raison d'être est un trou de la convention existante. Les types statiques de
viper se hachent déjà par un `hash()` membre, et souvent par `std::hash` :

| | `hash()` | `std::hash` |
|---|---|---|
| UUId, BlobId, CommitId | oui | oui |
| Blob, Any | oui | non |
| **Key, XArray** | **non** | **non** |

`ValueKey` et `ValueXArray` se hachent — `Value` impose `hash()` à tous ses dérivés. Leurs
jumeaux statiques, non. Ce fichier contourne ce trou en inventant une seconde convention.

**La correction est côté viper, et elle est dans l'esprit d'`XArray`** : donner un `hash()`
membre à `Viper_Key` et `Viper_XArray`, comme à leurs cinq voisins. Elle complète le côté
données de la dual-reality sans rien inventer, et rend ce fichier inutile.

Ne pas confondre avec le digest : `StreamHasher` produit une empreinte de contenu, pas le
`std::size_t` qu'attend une table de hachage. Deux usages, deux mécanismes.

## Et après : ce dossier se vide, pour le C++

Trois additions à viper, et il ne reste rien ici :

| addition viper | ce qu'elle retire |
|---|---|
| le contrat de mise en page statique — ce `TypedCodec`, avec son test aller-retour | la mise en page réénoncée par le pack |
| `hash()` sur `Key` et `XArray` | `HashAccumulator` |
| `hexdigest(value, hashing = SHA-1)` | la même composition, écrite dans P_Viper, N_Viper et notre `Codec` |

Mesuré : ce dossier contient ces quatre fichiers et rien d'autre, et le C++ généré n'inclut
que ces deux en-têtes — `TypedCodec` 28 fois, `HashAccumulator` 14. L'outillage d'épreuve
n'a jamais été au pack : `VIPER_ASSERT` vient de `Viper_GeneralErrors.hpp`, et les
`Viper_Assert.hpp`/`Viper_Test.hpp` qu'une version antérieure de ce fichier annonçait
n'existent pas.

**Le principe qui vide aussi le `Codec` généré :** le pack génère le pont C++ ⇄ `Value`, et
rien qui ne soit une composition de ce pont avec une transition du runtime. JSON et XML
s'obtiennent en une ligne sur `encode`/`decode`, qui sont publics ; `jsonEncode`,
`jsonDecode`, `jsonDefinitions`, `hexdigest` et `hexdigestValue` disparaissent.

**`runtime-proposed/python` et `runtime-proposed/node` se vident aussi — dans dsviper.** Une
version antérieure de ce fichier affirmait le contraire, au motif qu'en Python la classe
générée *est* une vue sur une `Value`, donc qu'il n'y aurait pas de dual-reality. C'était
confondre donnée et face : il n'y a pas de seconde donnée, mais il y a une seconde face. La
dual-reality est là, sur un autre modèle — par proxy au lieu de par copie :

| | C++ — par copie | Python / Node — par proxy |
|---|---|---|
| le pont | `encode`/`decode` | `wrap`/`unwrap` |
| le contrat du pont | la mise en page → viper | `Proxy`, `wrap`/`unwrap`, le registre → dsviper |
| le vocabulaire | `XArray<T>` → viper | `Sequence`, `Mapping`, `Ordered`, `Optional`, `Variant` → dsviper |
| les types du modèle | générés | générés |

Le proxy n'est pas un style parmi d'autres : une classe qui ne tient rien **hérite** du
fail-fast de dsviper au lieu de le réimplémenter. Un modèle par copie le perdrait. C'est ce qui
le fait revenir à dsviper plutôt qu'à un pack.

**Mais pas maintenant.** Les relecteurs à froid ont trouvé des défauts réels dans exactement
ces classes — `Mapping.items()` rend une liste, `Optional` masque `typing.Optional`, cinq
`__getattr__` non annotés, `Sequence<unknown>` en TypeScript. Les déplacer avant le polissage,
ce serait figer une API défectueuse sous les engagements du runtime.

**Et deux travaux de dsviper les attendent** : la vraie hiérarchie remplacera les trois
`hasattr(value, "type_code")` de `container.py` par des `isinstance` ; et `decode(…,
encoded=False)` devra remplacer la forme `ValueKey.cast(Value.decode(…))` de `data.py.stg`
avant qu'un `py.typed` soit livré.

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

1. viper gagne le contrat de mise en page statique, son test aller-retour, et `hash()` sur
   `Key` et `XArray` ;
2. le pack retire `TypedCodec` de ce dossier et `HashAccumulator` avec lui ;
3. les templates cessent de déclarer leurs versions.

Rien avant l'étape 1 n'est sûr.
