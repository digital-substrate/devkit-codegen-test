# Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

"""Parts — les types que ce namespace déclare."""

from __future__ import annotations

import enum
import functools
import typing

import dsviper

from .. import definitions
from .._proxy import Proxy, register, unwrap, wrap

# ── l'identité de cette unité dans le modèle ──
#
# LE MÊME ARTEFACT QU'EN C++, POUR LA MÊME RAISON : plusieurs couches en ont besoin et ce
# n'est pas de la sérialisation. Il tient ici en une constante par type, parce qu'il n'y a
# pas de tag à porter — l'appelant nomme la classe.

THING: dsviper.ValueUUId = dsviper.ValueUUId.create("12f4a98d-d084-f535-db87-e58f8757a553")
GRADE: dsviper.ValueUUId = dsviper.ValueUUId.create("b377e61b-49b9-6e92-5ccf-ea47d5bbfb30")
COLOUR: dsviper.ValueUUId = dsviper.ValueUUId.create("08261ca9-72d6-3df5-6608-c88279d35a48")

class ThingKey(Proxy):
    """Une poignée sur une instance de Parts::Thing, pas la chose elle-même.

    Le même nom que Core::Thing, et rien de commun.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def concept(cls):
        """Le descripteur, résolu une fois."""
        return definitions().check_concept(THING)

    @classmethod
    @functools.cache
    def type(cls) -> dsviper.Type:
        """Le descripteur du type de la clé.

        `classmethod` et non fonction libre : en C++ il fallait `type(tag<T>{})` pour que la
        recherche par argument trouve l'unité de T. Python n'a pas cette recherche et n'en a
        pas besoin — l'appelant écrit déjà le nom de la classe.
        """
        return dsviper.TypeKey(cls.concept())

    def __init__(self, identifier: dsviper.ValueKey | dsviper.ValueUUId | str | None = None):
        if isinstance(identifier, dsviper.ValueKey):
            if identifier.type() != self.type():
                raise TypeError("cette valeur n'est pas un Parts::ThingKey")
            super().__init__(identifier)
        else:
            super().__init__(dsviper.ValueKey.create(self.concept(), identifier))

    @classmethod
    def create(cls) -> ThingKey:
        """Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit."""
        return cls(dsviper.ValueUUId.create())

    @property
    def instance_id(self) -> dsviper.ValueUUId:
        return self.value.instance_id()

    def is_valid(self) -> bool:
        return self.instance_id.is_valid()

    def __repr__(self) -> str:
        return f"Parts::ThingKey({self.value.representation()})"

class Grade(enum.Enum):
    """Parts::Grade.

    Le même nom que Core::Grade, des cases différentes.

    UNE ÉNUMÉRATION PYTHON, PAS UN PROXY. Le pack en fait une classe qui enveloppe une
    `ValueEnumeration` ; Python en a une, et le runtime sait convertir depuis le nom d'un
    cas. Envelopper n'apporterait que du poids — et `Finish.matte` se lit mieux que
    `Finish("matte")`.
    """

    soft = "soft"
    hard = "hard"

    @classmethod
    @functools.cache
    def type(cls) -> dsviper.TypeEnumeration:
        return definitions().check_enumeration(GRADE)

    @classmethod
    def _wrap(cls, value) -> Grade:
        return cls(value.name())

    def _unwrap(self) -> str:
        return self.value

class Colour(Proxy):
    """Parts::Colour.

    Le même nom que Core::Colour, en virgule flottante.
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
            raise TypeError("cette valeur n'est pas un Parts::Colour")
        super().__init__(value)

        for name, field in fields.items():
            setattr(self, name, field)

    @property
    def r(self) -> float:
        return self.value.at("r")

    @r.setter
    def r(self, value: float) -> None:
        self.value.set("r", value)

    @property
    def g(self) -> float:
        return self.value.at("g")

    @g.setter
    def g(self, value: float) -> None:
        self.value.set("g", value)

    @property
    def b(self) -> float:
        return self.value.at("b")

    @b.setter
    def b(self, value: float) -> None:
        self.value.set("b", value)

    def __repr__(self) -> str:
        return f"Parts::Colour(r={self.r}, g={self.g}, b={self.b})"


# Les classes de cette unité, par l'identifiant d'exécution de leur type : c'est ce qui
# permet à `wrap` de rendre un élément de conteneur avec son nom, sans qu'aucune classe de
# conteneur existe.
register({THING: ThingKey, GRADE: Grade, COLOUR: Colour})

__all__ = ["ThingKey", "Grade", "Colour"]