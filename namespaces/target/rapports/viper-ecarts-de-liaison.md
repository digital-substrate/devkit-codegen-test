# Écarts de liaison — à signaler à viper

Cinq écarts trouvés en écrivant un générateur de code pour les trois cibles à partir du même
modèle. Chacun est **reproduit** ci-dessous, avec la commande exacte et sa sortie.

Ce qui les rend intéressants, c'est ce qui les a fait apparaître : rendre le *même* modèle
vers C++, Python et Node oblige à poser la même question aux trois liaisons, et trois réponses
différentes à une même question est une définition utilisable du mot « écart ».

Deux d'entre eux — 3 et 5 — sont des **divergences entre liaisons** : la même écriture est
acceptée d'un côté et refusée de l'autre. Ce sont les plus coûteux, parce qu'un code porté
d'un langage à l'autre change de comportement sans changer de forme.

---

## 1. `XArray::operator!=` compare un pointeur à un objet — C++

`src/Viper/Viper_XArray.hpp:215`

```cpp
bool operator!=(XArray const & other) const {
    return !(this == other);      // `this` est un pointeur
}
```

Ne compile que tant que personne ne l'instancie, ce qui est le cas aujourd'hui : un ordre qui
ne demande que `<` ne le rencontre jamais.

**Reproduction**

```cpp
#include "Viper_XArray.hpp"
int main() { Viper::XArray<int> a, b; return a != b; }
```

```
Viper_XArray.hpp:216:23: error: invalid operands to binary expression
  ('const Viper::XArray<int> *' and 'const XArray<int>')
  216 |         return !(this == other);
```

**Correctif** : `return !(*this == other);`

---

## 2. Le `.pyi` annonce une hiérarchie qui n'existe pas à l'exécution — Python

`dsviper/__init__.pyi` déclare `class ValueUUId(Value):`, et à l'exécution la relation n'est
pas là.

**Reproduction**

```python
import dsviper
v = dsviper.ValueUUId.create()
print([c.__name__ for c in type(v).__mro__])   # ['ValueUUId', 'object']
print(isinstance(v, dsviper.Value))            # False
```

**Conséquence** : aucune valeur du runtime n'est reconnaissable par son type. Un code
générique qui veut distinguer « une valeur du runtime » de « un objet Python » n'a aucun test
à sa disposition, et doit se rabattre sur la présence d'une méthode.

La liaison Node, elle, expose une vraie hiérarchie : `value instanceof dsviper.Value` y est
vrai. Les deux devraient se comporter pareil — ou le `.pyi` ne devrait pas déclarer ce que la
liaison ne tient pas.

---

## 3. Un variant s'écrit par son alternative en Python, pas en Node

Champ déclaré `variant<Core::Colour, Parts::Colour, string>`, écrit avec un `Core::Colour`.

**Reproduction**

```python
c.value.set("f_variant", core.Colour(r=1, g=1, b=1).value)
# accepté, relu comme Core::Colour|Parts::Colour|string
```

```js
c.value.set("f_variant", new core.Colour({r:1,g:1,b:1}).value);
// refusé : expected Core::Colour|Parts::Colour|string, got Core::Colour [set]
```

Python construit le variant lui-même ; Node exige une `ValueVariant` déjà formée. **La même
écriture devrait donner le même résultat.**

Contourné aujourd'hui en construisant le variant depuis le type du champ, que la structure
porte — mais c'est du code que la liaison Python rend inutile.

---

## 4. Le `.d.ts` interdit ce que le runtime accepte — Node

`ServiceRemoteAttachmentFunction.call(...args: InputValue[])` n'admet pas une
`AttachmentMutating`, que le runtime accepte pourtant comme premier argument — et que le pack
de templates écrit déjà.

**Reproduction** (avec `@types/node` présent ; sans lui `Buffer` s'effondre en `any` et
l'erreur disparaît, ce qui la rend intermittente selon la configuration du projet)

```ts
service.attachmentFunctionPoolFunc("LinkModel", "clear").call(state);
```

```
error TS2345: Argument of type 'AttachmentMutating' is not assignable to parameter of type 'InputValue'.
  Type 'AttachmentMutating' is not assignable to type 'Record<string, unknown>'.
    Index signature for type 'string' is missing in type 'AttachmentMutating'.
```

**Correctif** : déclarer la surcharge que le runtime implémente —
`call(state: AttachmentMutating, ...args: InputValue[]): OutputValue`.

---

## 5. Un document du mauvais type est accepté en Node, refusé en Python

Attachment déclaré `attachment<Thing, Colour> Core::colour`, document écrit : un
`Parts::Colour`.

**Reproduction**

```js
mutating.set(attachment, key, new parts.Colour({r:1,g:2,b:3}).value);
// accepté ; relu : Parts::Colour
```

```python
mutating.set(attachment, key, parts.Colour(r=1, g=2, b=3).value)
# refusé : expected Core::Colour, got Parts::Colour [checkValue]
```

**C'est le plus grave des cinq**, parce qu'il touche le fail-fast lui-même : une valeur du
mauvais type est stockée et se relit telle quelle, donc l'erreur ne se découvre qu'au prochain
lecteur — qui n'aura aucun moyen de savoir d'où elle vient. Toutes les autres écritures de la
liaison Node vérifient ; celle-ci est la seule qui ne le fait pas.

Contourné aujourd'hui par une comparaison de type dans la couche générée, **à retirer le jour
où la liaison vérifie**.

---

## Où ces reproductions tournent

Les cinq sont rejouables depuis `namespaces/target/` : les paquets rendus sont dans
`generated/{python,node}/crossing/`, et `check.py` les reconstruit. Les épreuves permanentes
qui pinnent les points 3 et 5 sont dans `python/checks/` et `node/checks/`.
