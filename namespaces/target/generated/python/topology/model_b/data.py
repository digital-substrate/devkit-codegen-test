# Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

"""ModelB — les types que ce namespace déclare."""

from __future__ import annotations

import enum
import functools
import typing

import dsviper

from .. import definitions
from .._codegen import AnyConceptKey, Mapping, Ordered, Proxy, Sequence, register, unwrap, wrap

# ── l'identité de cette unité dans le modèle ──
#
# LE MÊME ARTEFACT QU'EN C++, POUR LA MÊME RAISON : plusieurs couches en ont besoin et ce
# n'est pas de la sérialisation. Il tient ici en une constante par type, parce qu'il n'y a
# pas de tag à porter — l'appelant nomme la classe.

MATERIAL: dsviper.ValueUUId = dsviper.ValueUUId.create("fcbafe56-84de-904a-574a-7013e31b8a53")
COLOUR: dsviper.ValueUUId = dsviper.ValueUUId.create("a75f5fbe-e310-cca6-ba0c-9c763942e461")

class MaterialKey(Proxy):
    """Une poignée sur une instance de ModelB::Material, pas la chose elle-même.

    A material, as ModelB understands one.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def concept(cls):
        """Le descripteur, résolu une fois."""
        return definitions().check_concept(MATERIAL)

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
                raise TypeError("cette valeur n'est pas un ModelB::MaterialKey")
            super().__init__(identifier)
        else:
            super().__init__(dsviper.ValueKey.create(self.concept(), identifier))

    @classmethod
    def create(cls) -> MaterialKey:
        """Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit."""
        return cls(dsviper.ValueUUId.create())

    @property
    def instance_id(self) -> dsviper.ValueUUId:
        return self.value.instance_id()

    def is_valid(self) -> bool:
        return self.instance_id.is_valid()

    def __repr__(self) -> str:
        return f"ModelB::MaterialKey({self.value.representation()})"

class Colour(Proxy):
    """ModelB::Colour.

    Colour in floating point -- the same name as ModelA::Colour, a different type.
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
        return f"ModelB::Colour(r={self.r}, g={self.g}, b={self.b})"


# Les classes de cette unité, par l'identifiant d'exécution de leur type : c'est ce qui
# permet à `wrap` de rendre un élément de conteneur avec son nom, sans qu'aucune classe de
# conteneur existe.
register({MATERIAL: MaterialKey, COLOUR: Colour})

__all__ = ["MaterialKey", "Colour"]