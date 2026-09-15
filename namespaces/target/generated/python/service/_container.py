"""Les conteneurs, rendus avec les noms du modèle — écrits une fois, pour tous.

CE QUE LE PACK GÉNÈRE ICI, ET POURQUOI IL N'Y A RIEN À GÉNÉRER. Le pack Python émet une
classe par forme de conteneur rencontrée : `Optional_Colour`, `Vector_Parts_Colour`,
`Map_Core_ThingKey_to_Parts_ThingKey`, une par combinaison, soit environ 700 des 1 259 lignes
de son `data.py.stg`. Or `Optional_Colour` et `Optional_int32` ne diffèrent que par deux
choses : le descripteur du type, et la classe qui enveloppe un élément.

Et ces deux choses, la valeur les porte déjà. Une `Value` connaît son type, et un type nommé
connaît son identifiant d'exécution ; il suffit donc d'une table qui dise quelle classe va
avec quel identifiant, et d'une vue qui enveloppe en lisant. C'est ce fichier. Une unité
enregistre ses classes en une ligne, et aucune combinaison n'a plus à être prévue — y compris
celles qu'un modèle ajoutera ensuite.

UNE VUE ET NON UNE COPIE. La donnée reste dans la Value : `c.f_vector[0]` construit un
`Colour` au moment où on le demande, et `c.f_vector.append(Colour(...))` écrit dans la Value.
Copier obligerait à réécrire le champ entier pour changer un élément, et à choisir quand
recopier -- deux questions qu'une vue ne pose pas.
"""

from __future__ import annotations

import dsviper

from ._proxy import unwrap, wrap


class Sequence:
    """Une suite du runtime — vector, set, vec, tuple — dont les éléments portent leurs noms."""

    __slots__ = ("_value",)

    def __init__(self, value):
        self._value = value

    @property
    def value(self):
        return self._value

    def _unwrap(self):
        return self._value

    def _unwrap(self):
        return self._value

    def _unwrap(self):
        return self._value

    def __len__(self) -> int:
        return len(self._value)

    def __iter__(self):
        return (wrap(element) for element in self._value)

    def __getitem__(self, index):
        return wrap(self._value[index])

    def __setitem__(self, index, element) -> None:
        self._value[index] = unwrap(element)

    def __contains__(self, element) -> bool:
        return unwrap(element) in self._value

    def __eq__(self, other) -> bool:
        return self._value == (other._value if isinstance(other, Sequence) else other)

    def append(self, element) -> None:
        self._value.append(unwrap(element))

    def remove(self, element) -> None:
        self._value.remove(unwrap(element))

    def clear(self) -> None:
        self._value.clear()

    def __repr__(self) -> str:
        return repr(list(self))


class Mapping:
    """Une map du runtime, dont les clés et les valeurs portent leurs noms."""

    __slots__ = ("_value",)

    def __init__(self, value):
        self._value = value

    @property
    def value(self):
        return self._value

    def __len__(self) -> int:
        return len(self._value)

    def __iter__(self):
        return (wrap(key) for key in self._value)

    def __getitem__(self, key):
        return wrap(self._value.at(unwrap(key)))

    def __setitem__(self, key, element) -> None:
        self._value.set(unwrap(key), unwrap(element))

    def __delitem__(self, key) -> None:
        del self._value[unwrap(key)]

    def __contains__(self, key) -> bool:
        return unwrap(key) in self._value

    def __eq__(self, other) -> bool:
        return self._value == (other._value if isinstance(other, Mapping) else other)

    def keys(self):
        return list(self)

    def items(self):
        return [(key, self[key]) for key in self]

    def values(self):
        return [self[key] for key in self]

    def __repr__(self) -> str:
        return repr(dict(self.items()))


class Ordered:
    """Un xarray du runtime : une suite dont chaque place a une identité stable.

    LA POSITION EST LA CLÉ, ET C'EST TOUT CE QUI LE DISTINGUE D'UN `vector`. Deux éditeurs
    qui insèrent au même endroit n'écrasent pas l'insertion l'un de l'autre, parce que
    chaque élément est désigné par un identifiant et non par un rang.
    """

    __slots__ = ("_value",)

    END = dsviper.ValueXArray.END

    def __init__(self, value):
        self._value = value

    @property
    def value(self):
        return self._value

    def __len__(self) -> int:
        return len(self._value)

    def __iter__(self):
        return (wrap(element) for element in self._value)

    def positions(self) -> list:
        return list(self._value.positions())

    def at(self, position):
        return wrap(self._value.at(position))

    def insert(self, before_position, new_position, element) -> None:
        self._value.insert(before_position, new_position, unwrap(element))

    def update(self, position, element) -> None:
        self._value.update(position, unwrap(element))

    def remove(self, position) -> None:
        self._value.remove(position)

    def __eq__(self, other) -> bool:
        return self._value == (other._value if isinstance(other, Ordered) else other)

    def __repr__(self) -> str:
        return repr(list(self))
