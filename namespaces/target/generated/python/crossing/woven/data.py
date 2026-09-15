# Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

"""Woven — les types que ce namespace déclare."""

from __future__ import annotations

import enum
import functools
import typing

import dsviper

from .. import definitions
from .._proxy import Proxy, register, unwrap, wrap
from .. import parts
from .. import core

# ── l'identité de cette unité dans le modèle ──
#
# LE MÊME ARTEFACT QU'EN C++, POUR LA MÊME RAISON : plusieurs couches en ont besoin et ce
# n'est pas de la sérialisation. Il tient ici en une constante par type, parce qu'il n'y a
# pas de tag à porter — l'appelant nomme la classe.

KNOT: dsviper.ValueUUId = dsviper.ValueUUId.create("f60cecc5-a96c-bab5-77f1-1130bc338fda")
DERIVED: dsviper.ValueUUId = dsviper.ValueUUId.create("d0d3c1b6-50b8-9684-bec1-3b9b3583e571")
WEAVE: dsviper.ValueUUId = dsviper.ValueUUId.create("356db13d-6594-8f58-4602-b13293f04281")
COMPOSITES: dsviper.ValueUUId = dsviper.ValueUUId.create("77ab62f8-cfe3-5a99-7af4-c2f2befc866a")
ENTITIES: dsviper.ValueUUId = dsviper.ValueUUId.create("e8bdbb4b-956b-a468-b60d-0dc796c6a949")
NESTED: dsviper.ValueUUId = dsviper.ValueUUId.create("3cfb3a88-6f75-c5d2-f501-5bb814a9c6f4")

class KnotKey(Proxy):
    """Une poignée sur une instance de Woven::Knot, pas la chose elle-même.

    Ce sur quoi les attachments de ce namespace sont accrochés.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def concept(cls):
        """Le descripteur, résolu une fois."""
        return definitions().check_concept(KNOT)

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
                raise TypeError("cette valeur n'est pas un Woven::KnotKey")
            super().__init__(identifier)
        else:
            super().__init__(dsviper.ValueKey.create(self.concept(), identifier))

    @classmethod
    def create(cls) -> KnotKey:
        """Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit."""
        return cls(dsviper.ValueUUId.create())

    @property
    def instance_id(self) -> dsviper.ValueUUId:
        return self.value.instance_id()

    def is_valid(self) -> bool:
        return self.instance_id.is_valid()

    def __repr__(self) -> str:
        return f"Woven::KnotKey({self.value.representation()})"


class DerivedKey(Proxy):
    """Une poignée sur une instance de Woven::Derived, pas la chose elle-même.

    Un concept dont le parent vit ailleurs.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def concept(cls):
        """Le descripteur, résolu une fois."""
        return definitions().check_concept(DERIVED)

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
                raise TypeError("cette valeur n'est pas un Woven::DerivedKey")
            super().__init__(identifier)
        else:
            super().__init__(dsviper.ValueKey.create(self.concept(), identifier))

    @classmethod
    def create(cls) -> DerivedKey:
        """Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit."""
        return cls(dsviper.ValueUUId.create())

    @property
    def instance_id(self) -> dsviper.ValueUUId:
        return self.value.instance_id()

    def is_valid(self) -> bool:
        return self.instance_id.is_valid()

    def __repr__(self) -> str:
        return f"Woven::DerivedKey({self.value.representation()})"

class WeaveKey(Proxy):
    """Une poignée sur une instance de Woven::Weave, pas la chose elle-même.

    Un club dont les membres viennent de deux fournisseurs ET PORTENT LE MÊME NOM : le nom
    du getter ne peut pas être `asThingKey` des deux côtés, et un nom de fonction ne peut pas
    contenir `::`. C'est le cas que Core::Klub ne montre pas, ses membres étant chez lui.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def concept(cls):
        """Le descripteur, résolu une fois."""
        return definitions().check_club(WEAVE)

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
                raise TypeError("cette valeur n'est pas un Woven::WeaveKey")
            super().__init__(identifier)
        else:
            super().__init__(dsviper.ValueKey.create(self.concept(), identifier))

    @classmethod
    def create(cls) -> WeaveKey:
        """Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit."""
        return cls(dsviper.ValueUUId.create())

    @property
    def instance_id(self) -> dsviper.ValueUUId:
        return self.value.instance_id()

    def is_valid(self) -> bool:
        return self.instance_id.is_valid()

    def __repr__(self) -> str:
        return f"Woven::WeaveKey({self.value.representation()})"

    def as_(self, cls):
        """La clé vue comme celle d'un membre, ou `None` si l'instance n'en est pas un."""
        return cls(self.value.to_member_key(cls.concept())) if self.value.is_member(cls.concept()) else None

class Entities(Proxy):
    """Woven::Entities.

    Les entités des deux fournisseurs, nues, comme champs.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def type(cls) -> dsviper.TypeStructure:
        return definitions().check_structure(ENTITIES)

    def __init__(self, value: dsviper.ValueStructure | None = None, /, **fields):
        if value is None:
            value = dsviper.ValueStructure(self.type())
        elif value.type() != self.type():
            raise TypeError("cette valeur n'est pas un Woven::Entities")
        super().__init__(value)

        for name, field in fields.items():
            setattr(self, name, field)

    @property
    def f_core_grade(self) -> core.Grade:
        return wrap(self.value.at("f_core_grade", encoded=False))

    @f_core_grade.setter
    def f_core_grade(self, value: core.Grade) -> None:
        self.value.set("f_core_grade", unwrap(value))

    @property
    def f_parts_grade(self) -> parts.Grade:
        return wrap(self.value.at("f_parts_grade", encoded=False))

    @f_parts_grade.setter
    def f_parts_grade(self, value: parts.Grade) -> None:
        self.value.set("f_parts_grade", unwrap(value))

    @property
    def f_core_colour(self) -> core.Colour:
        return wrap(self.value.at("f_core_colour", encoded=False))

    @f_core_colour.setter
    def f_core_colour(self, value: core.Colour) -> None:
        self.value.set("f_core_colour", unwrap(value))

    @property
    def f_parts_colour(self) -> parts.Colour:
        return wrap(self.value.at("f_parts_colour", encoded=False))

    @f_parts_colour.setter
    def f_parts_colour(self, value: parts.Colour) -> None:
        self.value.set("f_parts_colour", unwrap(value))

    @property
    def f_single(self) -> core.Single:
        return wrap(self.value.at("f_single", encoded=False))

    @f_single.setter
    def f_single(self, value: core.Single) -> None:
        self.value.set("f_single", unwrap(value))

    @property
    def f_thing(self) -> core.ThingKey:
        return wrap(self.value.at("f_thing", encoded=False))

    @f_thing.setter
    def f_thing(self, value: core.ThingKey) -> None:
        self.value.set("f_thing", unwrap(value))

    @property
    def f_sub_thing(self) -> core.SubThingKey:
        return wrap(self.value.at("f_sub_thing", encoded=False))

    @f_sub_thing.setter
    def f_sub_thing(self, value: core.SubThingKey) -> None:
        self.value.set("f_sub_thing", unwrap(value))

    @property
    def f_other_thing(self) -> parts.ThingKey:
        return wrap(self.value.at("f_other_thing", encoded=False))

    @f_other_thing.setter
    def f_other_thing(self, value: parts.ThingKey) -> None:
        self.value.set("f_other_thing", unwrap(value))

    @property
    def f_klub(self) -> core.KlubKey:
        return wrap(self.value.at("f_klub", encoded=False))

    @f_klub.setter
    def f_klub(self, value: core.KlubKey) -> None:
        self.value.set("f_klub", unwrap(value))

    @property
    def f_any_concept(self) -> typing.Any:
        return wrap(self.value.at("f_any_concept", encoded=False))

    @f_any_concept.setter
    def f_any_concept(self, value: typing.Any) -> None:
        self.value.set("f_any_concept", unwrap(value))

    def __repr__(self) -> str:
        return f"Woven::Entities(f_core_grade={self.f_core_grade}, f_parts_grade={self.f_parts_grade}, f_core_colour={self.f_core_colour}, f_parts_colour={self.f_parts_colour}, f_single={self.f_single}, f_thing={self.f_thing}, f_sub_thing={self.f_sub_thing}, f_other_thing={self.f_other_thing}, f_klub={self.f_klub}, f_any_concept={self.f_any_concept})"


class Composites(Proxy):
    """Woven::Composites.

    Chaque conteneur, avec des éléments des deux fournisseurs.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def type(cls) -> dsviper.TypeStructure:
        return definitions().check_structure(COMPOSITES)

    def __init__(self, value: dsviper.ValueStructure | None = None, /, **fields):
        if value is None:
            value = dsviper.ValueStructure(self.type())
        elif value.type() != self.type():
            raise TypeError("cette valeur n'est pas un Woven::Composites")
        super().__init__(value)

        for name, field in fields.items():
            setattr(self, name, field)

    @property
    def f_tuple(self) -> typing.Any:
        return wrap(self.value.at("f_tuple", encoded=False))

    @f_tuple.setter
    def f_tuple(self, value: typing.Any) -> None:
        self.value.set("f_tuple", unwrap(value))

    @property
    def f_optional(self) -> typing.Any:
        return wrap(self.value.at("f_optional", encoded=False))

    @f_optional.setter
    def f_optional(self, value: typing.Any) -> None:
        self.value.set("f_optional", unwrap(value))

    @property
    def f_vector(self) -> typing.Any:
        return wrap(self.value.at("f_vector", encoded=False))

    @f_vector.setter
    def f_vector(self, value: typing.Any) -> None:
        self.value.set("f_vector", unwrap(value))

    @property
    def f_set(self) -> typing.Any:
        return wrap(self.value.at("f_set", encoded=False))

    @f_set.setter
    def f_set(self, value: typing.Any) -> None:
        self.value.set("f_set", unwrap(value))

    @property
    def f_map_keys(self) -> typing.Any:
        return wrap(self.value.at("f_map_keys", encoded=False))

    @f_map_keys.setter
    def f_map_keys(self, value: typing.Any) -> None:
        self.value.set("f_map_keys", unwrap(value))

    @property
    def f_map_enum(self) -> typing.Any:
        return wrap(self.value.at("f_map_enum", encoded=False))

    @f_map_enum.setter
    def f_map_enum(self, value: typing.Any) -> None:
        self.value.set("f_map_enum", unwrap(value))

    @property
    def f_xarray(self) -> typing.Any:
        return wrap(self.value.at("f_xarray", encoded=False))

    @f_xarray.setter
    def f_xarray(self, value: typing.Any) -> None:
        self.value.set("f_xarray", unwrap(value))

    @property
    def f_variant(self) -> typing.Any:
        return wrap(self.value.at("f_variant", encoded=False))

    @f_variant.setter
    def f_variant(self, value: typing.Any) -> None:
        self.value.set("f_variant", unwrap(value))

    def __repr__(self) -> str:
        return f"Woven::Composites(f_tuple={self.f_tuple}, f_optional={self.f_optional}, f_vector={self.f_vector}, f_set={self.f_set}, f_map_keys={self.f_map_keys}, f_map_enum={self.f_map_enum}, f_xarray={self.f_xarray}, f_variant={self.f_variant})"


class Nested(Proxy):
    """Woven::Nested.

    Une structure d'ici qui contient une structure d'ici : la profondeur reste locale.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def type(cls) -> dsviper.TypeStructure:
        return definitions().check_structure(NESTED)

    def __init__(self, value: dsviper.ValueStructure | None = None, /, **fields):
        if value is None:
            value = dsviper.ValueStructure(self.type())
        elif value.type() != self.type():
            raise TypeError("cette valeur n'est pas un Woven::Nested")
        super().__init__(value)

        for name, field in fields.items():
            setattr(self, name, field)

    @property
    def f_composites(self) -> Composites:
        return wrap(self.value.at("f_composites", encoded=False))

    @f_composites.setter
    def f_composites(self, value: Composites) -> None:
        self.value.set("f_composites", unwrap(value))

    @property
    def f_entities(self) -> Entities:
        return wrap(self.value.at("f_entities", encoded=False))

    @f_entities.setter
    def f_entities(self, value: Entities) -> None:
        self.value.set("f_entities", unwrap(value))

    def __repr__(self) -> str:
        return f"Woven::Nested(f_composites={self.f_composites}, f_entities={self.f_entities})"


# Les classes de cette unité, par l'identifiant d'exécution de leur type : c'est ce qui
# permet à `wrap` de rendre un élément de conteneur avec son nom, sans qu'aucune classe de
# conteneur existe.
register({KNOT: KnotKey, DERIVED: DerivedKey, WEAVE: WeaveKey, COMPOSITES: Composites, ENTITIES: Entities, NESTED: Nested})

__all__ = ["KnotKey", "DerivedKey", "WeaveKey", "Composites", "Entities", "Nested"]