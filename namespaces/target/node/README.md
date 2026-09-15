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

## Ce qui n'est pas encore écrit

Les conteneurs sont dans le socle — `Sequence`, `Mapping`, `Ordered`, génériques comme en
Python — mais aucune unité de la référence n'a de champ conteneur, donc ils ne sont pas encore
éprouvés ici. Et les templates ne sont pas écrites : c'est la référence qui vient d'abord.
