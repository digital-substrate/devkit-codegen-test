# node — la référence, écrite depuis le modèle et depuis TypeScript

Pas depuis le C++ ni depuis Python. Ce qui a tenu ailleurs tenait *parce que* C++ ou *parce
que* Python ; ce qui change ici n'est pas l'écriture mais la réponse.

```sh
namespaces/target/node/check.py     # compile en strict, puis exécute
```

**Deux épreuves et non une.** `tsc --strict` dit que les annotations tiennent ; il ne dit pas
qu'un attachment écrit ni qu'une base relit. Le C++ a un compilateur et un lien, Python a
l'import et pyright ; Node a les deux d'un coup, et il faut les deux.

## Ce que TypeScript décide autrement

**`instanceof` dit la vérité.** La liaison Node déclare une vraie hiérarchie et l'expose à
l'exécution — `value instanceof dsviper.Value` est vrai pour toute valeur concrète. La
liaison Python annonce `class ValueStructure(Value)` dans son `.pyi` et ne le tient pas. La
base commune n'existe donc ici que pour ne pas répéter, et non pour permettre de reconnaître.

**`Map` et `Set` indexent par identité**, et n'appellent aucune méthode. Une clé générée n'y
est pas utilisable telle quelle, et c'est vérifié :

```
  ok   une Map indexe par identité, donc une clé égale n'y est pas trouvée
  ok   le jeton du runtime, lui, indexe par valeur
```

Le runtime offre `hashKey()`, un bigint qui replie le type dans le hachage — et un bigint est
comparé par valeur. Ni le C++, où `operator<` suffit, ni Python, où `__hash__` et `__eq__`
font le travail, n'ont ce problème.

**Un entier 64 bits est un `bigint`.** Le modèle dit `int64` ; C++ lit `std::int64_t`, Python
lit `int`, et ici seul `bigint` porte la valeur sans perte.

**Et une portée de concept est une classe à membres statiques.** En C++ c'était un namespace,
en Python une classe instanciée une fois ; `Material.colour` dit la même chose sans qu'un
objet existe.

## Ce que la liaison Node n'a pas, et qui décide d'une fonctionnalité

**Il n'existe aucune classe `FunctionPool`.** Un pool n'est atteignable que par un
`ServiceRemote`, donc à travers un fil. C++ construit le pool et l'expose ; Python le tient en
main et l'appelle ; Node ne peut que l'appeler à distance.

C'est la même question posée à trois langages, et la troisième réponse est « rien à générer de
ce côté-là ». **Elle tranche aussi la découpe en fonctionnalités** : `Service` et
`ServiceClient` ne sont pas la même chose, puisqu'une cible n'a que la seconde — ce que le
pack savait déjà, puisque son dossier `typescript/` porte `function_pool_remotes.ts.stg` et
aucun `function_pools.ts.stg`.

## Ce que le vérificateur a trouvé pendant l'écriture

**Une base n'a ni `diff` ni `update`.** `dsviper.Database` porte `keys`, `has`, `get` et `set`
et s'arrête là : les deux autres demandent de connaître l'état courant pour en dériver une
mutation, ce qu'un état en mémoire a et qu'un enregistrement n'a pas. Trois interfaces donc,
et non deux — `Getting`, `Setting`, `Mutating`. En C++ la même chose avait demandé d'attendre
l'édition de liens.

**Et un import par défaut, pas un import de namespace.** La liaison est un module CommonJS ;
`import * as dsviper` rend un objet dont les classes sont absentes, et le programme meurt sur
`ValueUUId.create` à la première ligne. Le pack écrivait déjà `import dsviper from` — une
chose qu'il savait et que je ne savais pas.

## Les templates, et le rendu

Quatre templates — `index.ts.stg`, `data.ts.stg`, `attachments.ts.stg`, `pool.ts.stg` — rendent
un paquet par modèle dans `generated/node/<modèle>/src/`, et les quatre **compilent en strict
et s'importent** :

```
  Features      9 modules, compile et tout s'importe
  Service      13 modules, compile et tout s'importe
  Crossing     15 modules, compile et tout s'importe
  épreuve       9 assertions sur Crossing, toutes passent
  Topology     27 modules, compile et tout s'importe
```

### Les conteneurs, et ce que `tsc` en dit

Aucune unité de la référence n'a de champ conteneur, et lui en ajouter reviendrait à écrire à
la main ce que les templates produisent déjà. `Crossing` porte toutes les formes traversant
deux unités, et c'est là que l'épreuve se pose — `node/checks/crossing.mjs`.

Les annotations rendues :

```ts
get f_vector():   Sequence<parts.Colour>
get f_optional(): core.ThingKey | undefined
get f_map_enum(): Mapping<core.Grade, parts.Colour>
get f_xarray():   Ordered<core.Colour>
get f_variant():  core.Colour | parts.Colour | string
get f_tuple():    Sequence<core.Colour | parts.Colour>
```

Aucune classe de conteneur n'est générée : trois vues génériques, écrites une fois, et une
table qui dit quelle classe va avec quel identifiant d'exécution. Le pack en émet une par
combinaison rencontrée.

Et le cas fondateur tient jusqu'à travers un conteneur :

```
  ok   deux Colour homonymes ne se confondent pas dans un conteneur
```

### Deux différences de liaison trouvées en rendant

**Un variant ne s'écrit pas par son alternative.** La liaison Python accepte
`c.f_variant = Colour(...)` et construit le variant elle-même ; celle de Node refuse — *expected
Core::Colour|Parts::Colour|string, got Core::Colour* — et veut une `ValueVariant`. Le type du
champ dit dans lequel des deux cas on est, et la structure le porte : la construction est donc
dans le socle, une fois, plutôt que dans chaque accesseur généré. **Les deux liaisons devraient
répondre pareil à la même écriture.**

**Un état traverse `call`, que les déclarations typent trop étroit.** `call(...args:
InputValue[])` n'admet pas une `AttachmentMutating`, que le runtime accepte pourtant en premier
argument d'une fonction de pool d'attachments — c'est ce que le pack écrit déjà. La conversion
est explicite dans le template, et l'écart est à signaler au `.d.ts`.

### Et trois choses que TypeScript a imposées aux templates

- **une énumération est un type union et une valeur sous le même nom**, ce que ce langage
  permet : `Finish` annote, `Finish.matte` désigne, `Finish.wrap` convertit. Le pack en fait
  une classe qui enveloppe une `ValueEnumeration` ; une union de littéraux se vérifie mieux et
  ne coûte aucun objet ;
- **`register` est variadique**, parce qu'un tableau littéral de paires est inféré comme un
  tableau d'unions et non comme un tableau de tuples — il ne s'assigne alors à rien. Chaque
  argument d'une variadique est typé dans le contexte du paramètre ;
- **un champ `any` s'annote `unknown`** — le mot qui dit « je ne sais pas » sans ouvrir la
  porte à tout — et `unknown` ne s'assigne à rien sans être affirmé.
