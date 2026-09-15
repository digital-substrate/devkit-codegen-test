"""ModelB — les types que ce namespace déclare.

Les mêmes noms que ModelA, et des types différents. C'est le cas qui a tout déclenché, et
en Python il ne coûte rien : `topology.modela.Colour` et `topology.modelb.Colour` sont deux
classes de deux modules, et aucune n'a besoin d'être renommée.

UNE CLASSE GÉNÉRÉE ENVELOPPE UNE `dsviper.Value`, ELLE NE LA COPIE PAS. C'est le choix du
runtime et non une transposition : la donnée vit dans la Value, la classe lui donne des noms.
Une conséquence est qu'il n'y a rien à sérialiser — la valeur est déjà ce que le runtime
écrit.
"""

from __future__ import annotations

import functools

import dsviper

from .. import definitions
from .._proxy import Proxy


# ── l'identité de cette unité dans le modèle ──
#
# Le même artefact qu'en C++, pour la même raison : deux couches en ont besoin, et ce n'est
# pas de la sérialisation. Ici il tient en trois fonctions parce qu'il n'y a pas de tag à
# porter — l'appelant nomme la classe.

MATERIAL = dsviper.ValueUUId.create("fcbafe56-84de-904a-574a-7013e31b8a53")
COLOUR = dsviper.ValueUUId.create("a75f5fbe-e310-cca6-ba0c-9c763942e461")


@functools.cache
def _concept_type() -> dsviper.TypeConcept:
    return definitions().check_concept(MATERIAL)


class MaterialKey(Proxy):
    """Une poignée sur une instance de Material, pas la chose elle-même."""

    __slots__ = ()

    @classmethod
    @functools.cache
    def type(cls) -> dsviper.Type:
        """Le descripteur du type, résolu une fois.

        `classmethod` et non fonction libre : en C++ il fallait `type(tag<T>{})` pour que la
        recherche par argument trouve l'unité de T. Python n'a pas cette recherche et n'en a
        pas besoin — l'appelant écrit déjà le nom de la classe.
        """
        return dsviper.ValueKey.create(_concept_type()).type()

    def __init__(self, identifier: dsviper.ValueKey | dsviper.ValueUUId | str | None = None):
        if identifier is None:
            identifier = dsviper.ValueUUId.INVALID
        if isinstance(identifier, dsviper.ValueKey):
            if identifier.type() != self.type():
                raise TypeError("cette valeur n'est pas un ModelB::MaterialKey")
            super().__init__(identifier)
        else:
            super().__init__(dsviper.ValueKey.create(_concept_type(), identifier))

    @classmethod
    def create(cls) -> MaterialKey:
        """Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit."""
        return cls(dsviper.ValueUUId.create())

    @property
    def instance_id(self) -> dsviper.ValueUUId:
        return self._value.instance_id

    def __hash__(self) -> float:
        return self._value.hash()

    def __repr__(self) -> str:
        return f"ModelB::MaterialKey({self._value.representation()})"


class Colour(Proxy):
    """Une couleur en virgule flottante.

    LES CHAMPS SONT DES PROPRIÉTÉS SUR LA VALUE, et c'est ce qui remplace toute la couche 2
    du C++. Là-bas il fallait un `Fields::Colour::r` pour nommer un champ et un
    `rPath()` pour l'adresser ; ici `colour.r` fait les deux, parce qu'une propriété est
    déjà un nom et un accès.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def type(cls) -> dsviper.TypeStructure:
        return definitions().check_structure(COLOUR)

    def __init__(self, value: dsviper.ValueStructure | None = None, /, **fields):
        if value is None:
            value = dsviper.ValueStructure(self.type())
        elif value.type() != self.type():
            raise TypeError("cette valeur n'est pas un ModelB::Colour")
        super().__init__(value)

        for name, field in fields.items():
            setattr(self, name, field)

    @property
    def r(self) -> float:
        return self._value.at("r")

    @r.setter
    def r(self, value: int) -> None:
        self._value.set("r", value)

    @property
    def g(self) -> float:
        return self._value.at("g")

    @g.setter
    def g(self, value: int) -> None:
        self._value.set("g", value)

    @property
    def b(self) -> float:
        return self._value.at("b")

    @b.setter
    def b(self, value: int) -> None:
        self._value.set("b", value)

    def __repr__(self) -> str:
        return f"ModelB::Colour(r={self.r}, g={self.g}, b={self.b})"
