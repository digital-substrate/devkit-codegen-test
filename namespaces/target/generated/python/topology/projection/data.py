# Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

"""Projection — les types que ce namespace déclare."""

from __future__ import annotations

import enum
import functools
import typing

import dsviper

from .. import definitions
from .._container import Mapping, Ordered, Sequence
from .._proxy import AnyConceptKey, Proxy, register, unwrap, wrap
from .. import model_b
from .. import model_a

# ── l'identité de cette unité dans le modèle ──
#
# LE MÊME ARTEFACT QU'EN C++, POUR LA MÊME RAISON : plusieurs couches en ont besoin et ce
# n'est pas de la sérialisation. Il tient ici en une constante par type, parce qu'il n'y a
# pas de tag à porter — l'appelant nomme la classe.

LINK: dsviper.ValueUUId = dsviper.ValueUUId.create("d4f2e968-390a-ad1f-83d4-00e72fd30a50")
DERIVED_MATERIAL: dsviper.ValueUUId = dsviper.ValueUUId.create("4d1e4a0c-e262-8449-d792-44ee5aa2bb3f")
PAIR: dsviper.ValueUUId = dsviper.ValueUUId.create("9b902df2-0abc-efa8-dc98-e9de83b1c7ab")

class LinkKey(Proxy):
    """Une poignée sur une instance de Projection::Link, pas la chose elle-même.

    What one link between two driver materials is.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def concept(cls):
        """Le descripteur, résolu une fois."""
        return definitions().check_concept(LINK)

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
                raise TypeError("cette valeur n'est pas un Projection::LinkKey")
            super().__init__(identifier)
        else:
            super().__init__(dsviper.ValueKey.create(self.concept(), identifier))

    @classmethod
    def create(cls) -> LinkKey:
        """Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit."""
        return cls(dsviper.ValueUUId.create())

    @property
    def instance_id(self) -> dsviper.ValueUUId:
        return self.value.instance_id()

    def is_valid(self) -> bool:
        return self.instance_id.is_valid()

    def __repr__(self) -> str:
        return f"Projection::LinkKey({self.value.representation()})"


class DerivedMaterialKey(Proxy):
    """Une poignée sur une instance de Projection::DerivedMaterial, pas la chose elle-même.

    A concept whose parent lives in another namespace.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def concept(cls):
        """Le descripteur, résolu une fois."""
        return definitions().check_concept(DERIVED_MATERIAL)

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
                raise TypeError("cette valeur n'est pas un Projection::DerivedMaterialKey")
            super().__init__(identifier)
        else:
            super().__init__(dsviper.ValueKey.create(self.concept(), identifier))

    @classmethod
    def create(cls) -> DerivedMaterialKey:
        """Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit."""
        return cls(dsviper.ValueUUId.create())

    @property
    def instance_id(self) -> dsviper.ValueUUId:
        return self.value.instance_id()

    def is_valid(self) -> bool:
        return self.instance_id.is_valid()

    def __repr__(self) -> str:
        return f"Projection::DerivedMaterialKey({self.value.representation()})"

class Pair(Proxy):
    """Projection::Pair.

    Two keys from two namespaces in one structure -- the key<NS::C> edge.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def type(cls) -> dsviper.TypeStructure:
        return definitions().check_structure(PAIR)

    def __init__(self, value: dsviper.ValueStructure | None = None, /, **fields):
        if value is None:
            value = dsviper.ValueStructure(self.type())
        elif value.type() != self.type():
            raise TypeError("cette valeur n'est pas un Projection::Pair")
        super().__init__(value)

        for name, field in fields.items():
            setattr(self, name, field)

    @property
    def a(self) -> model_a.MaterialKey:
        return wrap(self.value.at("a", encoded=False))

    @a.setter
    def a(self, value: model_a.MaterialKey) -> None:
        self.value.set("a", unwrap(value))

    @property
    def b(self) -> model_b.MaterialKey:
        return wrap(self.value.at("b", encoded=False))

    @b.setter
    def b(self, value: model_b.MaterialKey) -> None:
        self.value.set("b", unwrap(value))

    def __repr__(self) -> str:
        return f"Projection::Pair(a={self.a}, b={self.b})"


# Les classes de cette unité, par l'identifiant d'exécution de leur type : c'est ce qui
# permet à `wrap` de rendre un élément de conteneur avec son nom, sans qu'aucune classe de
# conteneur existe.
register({LINK: LinkKey, DERIVED_MATERIAL: DerivedMaterialKey, PAIR: Pair})

__all__ = ["LinkKey", "DerivedMaterialKey", "Pair"]