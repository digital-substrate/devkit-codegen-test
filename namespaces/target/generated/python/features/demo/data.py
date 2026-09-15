# Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/features/Features.dsm.json by kibo-2.0.0.jar

"""Demo — les types que ce namespace déclare."""

from __future__ import annotations

import enum
import functools
import typing

import dsviper

from .. import definitions
from .._proxy import Proxy

# ── l'identité de cette unité dans le modèle ──
#
# LE MÊME ARTEFACT QU'EN C++, POUR LA MÊME RAISON : plusieurs couches en ont besoin et ce
# n'est pas de la sérialisation. Il tient ici en une constante par type, parce qu'il n'y a
# pas de tag à porter — l'appelant nomme la classe.

CONCEPT_A: dsviper.ValueUUId = dsviper.ValueUUId.create("bcc4e978-a438-ddba-66b9-d767b3b2649e")
CONCEPT_B: dsviper.ValueUUId = dsviper.ValueUUId.create("cdb6cd9f-f1b4-03b0-dff8-b8a2092ec01c")
CONCEPT_COVERAGE: dsviper.ValueUUId = dsviper.ValueUUId.create("28892760-a292-acbb-40ba-1aa63fc833e6")
CONCEPT_D: dsviper.ValueUUId = dsviper.ValueUUId.create("edc1351f-a74f-2036-f170-e1a67570b90a")
CONCEPT_C: dsviper.ValueUUId = dsviper.ValueUUId.create("ce7c9e3d-ae5f-2e57-c693-4b3e351d105b")
EMPTY_KLUB: dsviper.ValueUUId = dsviper.ValueUUId.create("f1a3dba5-200b-4fb9-e8e7-a5a62af2a843")
KLUB: dsviper.ValueUUId = dsviper.ValueUUId.create("0e64c619-6b27-330c-52ca-d2b0b6d88c0a")
ENUMERATION_E: dsviper.ValueUUId = dsviper.ValueUUId.create("57233334-ee71-b77f-d6a6-b4ff25bb2350")
STRUCTURE_S: dsviper.ValueUUId = dsviper.ValueUUId.create("c4f62cf6-2d27-05b0-018c-67d1b99df4a6")
STRUCTURE_T: dsviper.ValueUUId = dsviper.ValueUUId.create("773ad0a2-1c7b-302e-e1b5-314ab0edb74a")
STRUCTURE_U: dsviper.ValueUUId = dsviper.ValueUUId.create("019d066d-bd5a-19b7-4565-9c5a6f95c808")
STRUCTURE_V: dsviper.ValueUUId = dsviper.ValueUUId.create("8b5d06ab-5a9f-d427-23b8-7ec3611aabde")
STRUCTURE_W: dsviper.ValueUUId = dsviper.ValueUUId.create("df0e54fc-b3ac-a527-d8d7-678fc2d56d3f")

class ConceptAKey(Proxy):
    """Une poignée sur une instance de Demo::ConceptA, pas la chose elle-même.

    This is the documentation for the concept A
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def concept(cls):
        """Le descripteur, résolu une fois."""
        return definitions().check_concept(CONCEPT_A)

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
                raise TypeError("cette valeur n'est pas un Demo::ConceptAKey")
            super().__init__(identifier)
        else:
            super().__init__(dsviper.ValueKey.create(self.concept(), identifier))

    @classmethod
    def create(cls) -> ConceptAKey:
        """Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit."""
        return cls(dsviper.ValueUUId.create())

    @property
    def instance_id(self) -> dsviper.ValueUUId:
        return self.value.instance_id()

    def is_valid(self) -> bool:
        return self.instance_id.is_valid()

    def __repr__(self) -> str:
        return f"Demo::ConceptAKey({self.value.representation()})"


class ConceptBKey(Proxy):
    """Une poignée sur une instance de Demo::ConceptB, pas la chose elle-même.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def concept(cls):
        """Le descripteur, résolu une fois."""
        return definitions().check_concept(CONCEPT_B)

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
                raise TypeError("cette valeur n'est pas un Demo::ConceptBKey")
            super().__init__(identifier)
        else:
            super().__init__(dsviper.ValueKey.create(self.concept(), identifier))

    @classmethod
    def create(cls) -> ConceptBKey:
        """Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit."""
        return cls(dsviper.ValueUUId.create())

    @property
    def instance_id(self) -> dsviper.ValueUUId:
        return self.value.instance_id()

    def is_valid(self) -> bool:
        return self.instance_id.is_valid()

    def __repr__(self) -> str:
        return f"Demo::ConceptBKey({self.value.representation()})"


class ConceptCoverageKey(Proxy):
    """Une poignée sur une instance de Demo::ConceptCoverage, pas la chose elle-même.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def concept(cls):
        """Le descripteur, résolu une fois."""
        return definitions().check_concept(CONCEPT_COVERAGE)

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
                raise TypeError("cette valeur n'est pas un Demo::ConceptCoverageKey")
            super().__init__(identifier)
        else:
            super().__init__(dsviper.ValueKey.create(self.concept(), identifier))

    @classmethod
    def create(cls) -> ConceptCoverageKey:
        """Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit."""
        return cls(dsviper.ValueUUId.create())

    @property
    def instance_id(self) -> dsviper.ValueUUId:
        return self.value.instance_id()

    def is_valid(self) -> bool:
        return self.instance_id.is_valid()

    def __repr__(self) -> str:
        return f"Demo::ConceptCoverageKey({self.value.representation()})"


class ConceptDKey(Proxy):
    """Une poignée sur une instance de Demo::ConceptD, pas la chose elle-même.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def concept(cls):
        """Le descripteur, résolu une fois."""
        return definitions().check_concept(CONCEPT_D)

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
                raise TypeError("cette valeur n'est pas un Demo::ConceptDKey")
            super().__init__(identifier)
        else:
            super().__init__(dsviper.ValueKey.create(self.concept(), identifier))

    @classmethod
    def create(cls) -> ConceptDKey:
        """Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit."""
        return cls(dsviper.ValueUUId.create())

    @property
    def instance_id(self) -> dsviper.ValueUUId:
        return self.value.instance_id()

    def is_valid(self) -> bool:
        return self.instance_id.is_valid()

    def __repr__(self) -> str:
        return f"Demo::ConceptDKey({self.value.representation()})"


class ConceptCKey(Proxy):
    """Une poignée sur une instance de Demo::ConceptC, pas la chose elle-même.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def concept(cls):
        """Le descripteur, résolu une fois."""
        return definitions().check_concept(CONCEPT_C)

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
                raise TypeError("cette valeur n'est pas un Demo::ConceptCKey")
            super().__init__(identifier)
        else:
            super().__init__(dsviper.ValueKey.create(self.concept(), identifier))

    @classmethod
    def create(cls) -> ConceptCKey:
        """Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit."""
        return cls(dsviper.ValueUUId.create())

    @property
    def instance_id(self) -> dsviper.ValueUUId:
        return self.value.instance_id()

    def is_valid(self) -> bool:
        return self.instance_id.is_valid()

    def __repr__(self) -> str:
        return f"Demo::ConceptCKey({self.value.representation()})"

class EmptyKlubKey(Proxy):
    """Une poignée sur une instance de Demo::EmptyKlub, pas la chose elle-même.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def concept(cls):
        """Le descripteur, résolu une fois."""
        return definitions().check_club(EMPTY_KLUB)

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
                raise TypeError("cette valeur n'est pas un Demo::EmptyKlubKey")
            super().__init__(identifier)
        else:
            super().__init__(dsviper.ValueKey.create(self.concept(), identifier))

    @classmethod
    def create(cls) -> EmptyKlubKey:
        """Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit."""
        return cls(dsviper.ValueUUId.create())

    @property
    def instance_id(self) -> dsviper.ValueUUId:
        return self.value.instance_id()

    def is_valid(self) -> bool:
        return self.instance_id.is_valid()

    def __repr__(self) -> str:
        return f"Demo::EmptyKlubKey({self.value.representation()})"

    def as_(self, cls):
        """La clé vue comme celle d'un membre, ou `None` si l'instance n'en est pas un."""
        return cls(self.value.to_member_key(cls.concept())) if self.value.is_member(cls.concept()) else None


class KlubKey(Proxy):
    """Une poignée sur une instance de Demo::Klub, pas la chose elle-même.

    This is the documentation for the concept D
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def concept(cls):
        """Le descripteur, résolu une fois."""
        return definitions().check_club(KLUB)

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
                raise TypeError("cette valeur n'est pas un Demo::KlubKey")
            super().__init__(identifier)
        else:
            super().__init__(dsviper.ValueKey.create(self.concept(), identifier))

    @classmethod
    def create(cls) -> KlubKey:
        """Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit."""
        return cls(dsviper.ValueUUId.create())

    @property
    def instance_id(self) -> dsviper.ValueUUId:
        return self.value.instance_id()

    def is_valid(self) -> bool:
        return self.instance_id.is_valid()

    def __repr__(self) -> str:
        return f"Demo::KlubKey({self.value.representation()})"

    def as_(self, cls):
        """La clé vue comme celle d'un membre, ou `None` si l'instance n'en est pas un."""
        return cls(self.value.to_member_key(cls.concept())) if self.value.is_member(cls.concept()) else None

class EnumerationE(enum.Enum):
    """Demo::EnumerationE.

    This is the documentation for enumeration E

    UNE ÉNUMÉRATION PYTHON, PAS UN PROXY. Le pack en fait une classe qui enveloppe une
    `ValueEnumeration` ; Python en a une, et le runtime sait convertir depuis le nom d'un
    cas. Envelopper n'apporterait que du poids — et `Finish.matte` se lit mieux que
    `Finish("matte")`.
    """

    a = "a"
    b = "b"
    c = "c"

    @classmethod
    @functools.cache
    def type(cls) -> dsviper.TypeEnumeration:
        return definitions().check_enumeration(ENUMERATION_E)

    @classmethod
    def _wrap(cls, value) -> EnumerationE:
        return cls(value.name())

    def _unwrap(self) -> str:
        return self.value

class StructureS(Proxy):
    """Demo::StructureS.

    This is the documentation for the struct S
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def type(cls) -> dsviper.TypeStructure:
        return definitions().check_structure(STRUCTURE_S)

    def __init__(self, value: dsviper.ValueStructure | None = None, /, **fields):
        if value is None:
            value = dsviper.ValueStructure(self.type())
        elif value.type() != self.type():
            raise TypeError("cette valeur n'est pas un Demo::StructureS")
        super().__init__(value)

        for name, field in fields.items():
            setattr(self, name, field)

    @property
    def f_float(self) -> float:
        return self.value.at("f_float")

    @f_float.setter
    def f_float(self, value: float) -> None:
        self.value.set("f_float", value)

    @property
    def f_string(self) -> str:
        return self.value.at("f_string")

    @f_string.setter
    def f_string(self, value: str) -> None:
        self.value.set("f_string", value)

    def __repr__(self) -> str:
        return f"Demo::StructureS(f_float={self.f_float}, f_string={self.f_string})"


class StructureW(Proxy):
    """Demo::StructureW.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def type(cls) -> dsviper.TypeStructure:
        return definitions().check_structure(STRUCTURE_W)

    def __init__(self, value: dsviper.ValueStructure | None = None, /, **fields):
        if value is None:
            value = dsviper.ValueStructure(self.type())
        elif value.type() != self.type():
            raise TypeError("cette valeur n'est pas un Demo::StructureW")
        super().__init__(value)

        for name, field in fields.items():
            setattr(self, name, field)

    @property
    def f_single(self) -> int:
        return self.value.at("f_single")

    @f_single.setter
    def f_single(self, value: int) -> None:
        self.value.set("f_single", value)

    def __repr__(self) -> str:
        return f"Demo::StructureW(f_single={self.f_single})"


class StructureT(Proxy):
    """Demo::StructureT.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def type(cls) -> dsviper.TypeStructure:
        return definitions().check_structure(STRUCTURE_T)

    def __init__(self, value: dsviper.ValueStructure | None = None, /, **fields):
        if value is None:
            value = dsviper.ValueStructure(self.type())
        elif value.type() != self.type():
            raise TypeError("cette valeur n'est pas un Demo::StructureT")
        super().__init__(value)

        for name, field in fields.items():
            setattr(self, name, field)

    @property
    def field_string(self) -> str:
        return self.value.at("field_string")

    @field_string.setter
    def field_string(self, value: str) -> None:
        self.value.set("field_string", value)

    @property
    def field_structure_s(self) -> StructureS:
        return StructureS._wrap(self.value.at("field_structure_s", encoded=False))

    @field_structure_s.setter
    def field_structure_s(self, value: StructureS) -> None:
        self.value.set("field_structure_s", value._unwrap())

    def __repr__(self) -> str:
        return f"Demo::StructureT(field_string={self.field_string}, field_structure_s={self.field_structure_s})"


class StructureV(Proxy):
    """Demo::StructureV.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def type(cls) -> dsviper.TypeStructure:
        return definitions().check_structure(STRUCTURE_V)

    def __init__(self, value: dsviper.ValueStructure | None = None, /, **fields):
        if value is None:
            value = dsviper.ValueStructure(self.type())
        elif value.type() != self.type():
            raise TypeError("cette valeur n'est pas un Demo::StructureV")
        super().__init__(value)

        for name, field in fields.items():
            setattr(self, name, field)

    @property
    def f_bool(self) -> bool:
        return self.value.at("f_bool")

    @f_bool.setter
    def f_bool(self, value: bool) -> None:
        self.value.set("f_bool", value)

    @property
    def f_uint8(self) -> int:
        return self.value.at("f_uint8")

    @f_uint8.setter
    def f_uint8(self, value: int) -> None:
        self.value.set("f_uint8", value)

    @property
    def f_uint16(self) -> int:
        return self.value.at("f_uint16")

    @f_uint16.setter
    def f_uint16(self, value: int) -> None:
        self.value.set("f_uint16", value)

    @property
    def f_uint32(self) -> int:
        return self.value.at("f_uint32")

    @f_uint32.setter
    def f_uint32(self, value: int) -> None:
        self.value.set("f_uint32", value)

    @property
    def f_uint64(self) -> int:
        return self.value.at("f_uint64")

    @f_uint64.setter
    def f_uint64(self, value: int) -> None:
        self.value.set("f_uint64", value)

    @property
    def f_int8(self) -> int:
        return self.value.at("f_int8")

    @f_int8.setter
    def f_int8(self, value: int) -> None:
        self.value.set("f_int8", value)

    @property
    def f_int16(self) -> int:
        return self.value.at("f_int16")

    @f_int16.setter
    def f_int16(self, value: int) -> None:
        self.value.set("f_int16", value)

    @property
    def f_int32(self) -> int:
        return self.value.at("f_int32")

    @f_int32.setter
    def f_int32(self, value: int) -> None:
        self.value.set("f_int32", value)

    @property
    def f_int64(self) -> int:
        return self.value.at("f_int64")

    @f_int64.setter
    def f_int64(self, value: int) -> None:
        self.value.set("f_int64", value)

    @property
    def f_float(self) -> float:
        return self.value.at("f_float")

    @f_float.setter
    def f_float(self, value: float) -> None:
        self.value.set("f_float", value)

    @property
    def f_double(self) -> float:
        return self.value.at("f_double")

    @f_double.setter
    def f_double(self, value: float) -> None:
        self.value.set("f_double", value)

    @property
    def f_uuid(self) -> dsviper.ValueUUId:
        return self.value.at("f_uuid")

    @f_uuid.setter
    def f_uuid(self, value: dsviper.ValueUUId) -> None:
        self.value.set("f_uuid", value)

    @property
    def f_string(self) -> str:
        return self.value.at("f_string")

    @f_string.setter
    def f_string(self, value: str) -> None:
        self.value.set("f_string", value)

    @property
    def f_vec(self) -> typing.Any:
        return self.value.at("f_vec")

    @f_vec.setter
    def f_vec(self, value: typing.Any) -> None:
        self.value.set("f_vec", value)

    @property
    def f_mat(self) -> typing.Any:
        return self.value.at("f_mat")

    @f_mat.setter
    def f_mat(self, value: typing.Any) -> None:
        self.value.set("f_mat", value)

    @property
    def f_tuple(self) -> typing.Any:
        return self.value.at("f_tuple")

    @f_tuple.setter
    def f_tuple(self, value: typing.Any) -> None:
        self.value.set("f_tuple", value)

    @property
    def f_optional(self) -> typing.Any:
        return self.value.at("f_optional")

    @f_optional.setter
    def f_optional(self, value: typing.Any) -> None:
        self.value.set("f_optional", value)

    @property
    def f_vector(self) -> typing.Any:
        return self.value.at("f_vector")

    @f_vector.setter
    def f_vector(self, value: typing.Any) -> None:
        self.value.set("f_vector", value)

    @property
    def f_set(self) -> typing.Any:
        return self.value.at("f_set")

    @f_set.setter
    def f_set(self, value: typing.Any) -> None:
        self.value.set("f_set", value)

    @property
    def f_map(self) -> typing.Any:
        return self.value.at("f_map")

    @f_map.setter
    def f_map(self, value: typing.Any) -> None:
        self.value.set("f_map", value)

    @property
    def f_E(self) -> EnumerationE:
        return EnumerationE._wrap(self.value.at("f_E", encoded=False))

    @f_E.setter
    def f_E(self, value: EnumerationE) -> None:
        self.value.set("f_E", value._unwrap())

    @property
    def f_S(self) -> StructureS:
        return StructureS._wrap(self.value.at("f_S", encoded=False))

    @f_S.setter
    def f_S(self, value: StructureS) -> None:
        self.value.set("f_S", value._unwrap())

    @property
    def f_T(self) -> StructureT:
        return StructureT._wrap(self.value.at("f_T", encoded=False))

    @f_T.setter
    def f_T(self, value: StructureT) -> None:
        self.value.set("f_T", value._unwrap())

    def __repr__(self) -> str:
        return f"Demo::StructureV(f_bool={self.f_bool}, f_uint8={self.f_uint8}, f_uint16={self.f_uint16}, f_uint32={self.f_uint32}, f_uint64={self.f_uint64}, f_int8={self.f_int8}, f_int16={self.f_int16}, f_int32={self.f_int32}, f_int64={self.f_int64}, f_float={self.f_float}, f_double={self.f_double}, f_uuid={self.f_uuid}, f_string={self.f_string}, f_vec={self.f_vec}, f_mat={self.f_mat}, f_tuple={self.f_tuple}, f_optional={self.f_optional}, f_vector={self.f_vector}, f_set={self.f_set}, f_map={self.f_map}, f_E={self.f_E}, f_S={self.f_S}, f_T={self.f_T})"


class StructureU(Proxy):
    """Demo::StructureU.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def type(cls) -> dsviper.TypeStructure:
        return definitions().check_structure(STRUCTURE_U)

    def __init__(self, value: dsviper.ValueStructure | None = None, /, **fields):
        if value is None:
            value = dsviper.ValueStructure(self.type())
        elif value.type() != self.type():
            raise TypeError("cette valeur n'est pas un Demo::StructureU")
        super().__init__(value)

        for name, field in fields.items():
            setattr(self, name, field)

    @property
    def f_bool(self) -> bool:
        return self.value.at("f_bool")

    @f_bool.setter
    def f_bool(self, value: bool) -> None:
        self.value.set("f_bool", value)

    @property
    def f_uint8(self) -> int:
        return self.value.at("f_uint8")

    @f_uint8.setter
    def f_uint8(self, value: int) -> None:
        self.value.set("f_uint8", value)

    @property
    def f_uint16(self) -> int:
        return self.value.at("f_uint16")

    @f_uint16.setter
    def f_uint16(self, value: int) -> None:
        self.value.set("f_uint16", value)

    @property
    def f_uint32(self) -> int:
        return self.value.at("f_uint32")

    @f_uint32.setter
    def f_uint32(self, value: int) -> None:
        self.value.set("f_uint32", value)

    @property
    def f_uint64(self) -> int:
        return self.value.at("f_uint64")

    @f_uint64.setter
    def f_uint64(self, value: int) -> None:
        self.value.set("f_uint64", value)

    @property
    def f_int8(self) -> int:
        return self.value.at("f_int8")

    @f_int8.setter
    def f_int8(self, value: int) -> None:
        self.value.set("f_int8", value)

    @property
    def f_int16(self) -> int:
        return self.value.at("f_int16")

    @f_int16.setter
    def f_int16(self, value: int) -> None:
        self.value.set("f_int16", value)

    @property
    def f_int32(self) -> int:
        return self.value.at("f_int32")

    @f_int32.setter
    def f_int32(self, value: int) -> None:
        self.value.set("f_int32", value)

    @property
    def f_int64(self) -> int:
        return self.value.at("f_int64")

    @f_int64.setter
    def f_int64(self, value: int) -> None:
        self.value.set("f_int64", value)

    @property
    def f_float(self) -> float:
        return self.value.at("f_float")

    @f_float.setter
    def f_float(self, value: float) -> None:
        self.value.set("f_float", value)

    @property
    def f_double(self) -> float:
        return self.value.at("f_double")

    @f_double.setter
    def f_double(self, value: float) -> None:
        self.value.set("f_double", value)

    @property
    def f_blob_id(self) -> dsviper.ValueBlobId:
        return self.value.at("f_blob_id")

    @f_blob_id.setter
    def f_blob_id(self, value: dsviper.ValueBlobId) -> None:
        self.value.set("f_blob_id", value)

    @property
    def f_commit_id(self) -> dsviper.ValueCommitId:
        return self.value.at("f_commit_id")

    @f_commit_id.setter
    def f_commit_id(self, value: dsviper.ValueCommitId) -> None:
        self.value.set("f_commit_id", value)

    @property
    def f_uuid(self) -> dsviper.ValueUUId:
        return self.value.at("f_uuid")

    @f_uuid.setter
    def f_uuid(self, value: dsviper.ValueUUId) -> None:
        self.value.set("f_uuid", value)

    @property
    def f_string(self) -> str:
        return self.value.at("f_string")

    @f_string.setter
    def f_string(self, value: str) -> None:
        self.value.set("f_string", value)

    @property
    def f_blob(self) -> dsviper.ValueBlob:
        return self.value.at("f_blob")

    @f_blob.setter
    def f_blob(self, value: dsviper.ValueBlob) -> None:
        self.value.set("f_blob", value)

    @property
    def f_vec(self) -> typing.Any:
        return self.value.at("f_vec")

    @f_vec.setter
    def f_vec(self, value: typing.Any) -> None:
        self.value.set("f_vec", value)

    @property
    def f_mat(self) -> typing.Any:
        return self.value.at("f_mat")

    @f_mat.setter
    def f_mat(self, value: typing.Any) -> None:
        self.value.set("f_mat", value)

    @property
    def f_tuple(self) -> typing.Any:
        return self.value.at("f_tuple")

    @f_tuple.setter
    def f_tuple(self, value: typing.Any) -> None:
        self.value.set("f_tuple", value)

    @property
    def f_optional(self) -> typing.Any:
        return self.value.at("f_optional")

    @f_optional.setter
    def f_optional(self, value: typing.Any) -> None:
        self.value.set("f_optional", value)

    @property
    def f_vector(self) -> typing.Any:
        return self.value.at("f_vector")

    @f_vector.setter
    def f_vector(self, value: typing.Any) -> None:
        self.value.set("f_vector", value)

    @property
    def f_set(self) -> typing.Any:
        return self.value.at("f_set")

    @f_set.setter
    def f_set(self, value: typing.Any) -> None:
        self.value.set("f_set", value)

    @property
    def f_set_s(self) -> typing.Any:
        return self.value.at("f_set_s")

    @f_set_s.setter
    def f_set_s(self, value: typing.Any) -> None:
        self.value.set("f_set_s", value)

    @property
    def f_map_s1(self) -> typing.Any:
        return self.value.at("f_map_s1")

    @f_map_s1.setter
    def f_map_s1(self, value: typing.Any) -> None:
        self.value.set("f_map_s1", value)

    @property
    def f_map_s2(self) -> typing.Any:
        return self.value.at("f_map_s2")

    @f_map_s2.setter
    def f_map_s2(self, value: typing.Any) -> None:
        self.value.set("f_map_s2", value)

    @property
    def f_xarray(self) -> typing.Any:
        return self.value.at("f_xarray")

    @f_xarray.setter
    def f_xarray(self, value: typing.Any) -> None:
        self.value.set("f_xarray", value)

    @property
    def f_xarray_s(self) -> typing.Any:
        return self.value.at("f_xarray_s")

    @f_xarray_s.setter
    def f_xarray_s(self, value: typing.Any) -> None:
        self.value.set("f_xarray_s", value)

    @property
    def f_map_vs(self) -> typing.Any:
        return self.value.at("f_map_vs")

    @f_map_vs.setter
    def f_map_vs(self, value: typing.Any) -> None:
        self.value.set("f_map_vs", value)

    @property
    def f_variant(self) -> typing.Any:
        return self.value.at("f_variant")

    @f_variant.setter
    def f_variant(self, value: typing.Any) -> None:
        self.value.set("f_variant", value)

    @property
    def f_any(self) -> dsviper.ValueAny:
        return self.value.at("f_any")

    @f_any.setter
    def f_any(self, value: dsviper.ValueAny) -> None:
        self.value.set("f_any", value)

    @property
    def f_E(self) -> EnumerationE:
        return EnumerationE._wrap(self.value.at("f_E", encoded=False))

    @f_E.setter
    def f_E(self, value: EnumerationE) -> None:
        self.value.set("f_E", value._unwrap())

    @property
    def f_S(self) -> StructureS:
        return StructureS._wrap(self.value.at("f_S", encoded=False))

    @f_S.setter
    def f_S(self, value: StructureS) -> None:
        self.value.set("f_S", value._unwrap())

    @property
    def f_T(self) -> StructureT:
        return StructureT._wrap(self.value.at("f_T", encoded=False))

    @f_T.setter
    def f_T(self, value: StructureT) -> None:
        self.value.set("f_T", value._unwrap())

    @property
    def f_A(self) -> ConceptAKey:
        return ConceptAKey._wrap(self.value.at("f_A", encoded=False))

    @f_A.setter
    def f_A(self, value: ConceptAKey) -> None:
        self.value.set("f_A", value._unwrap())

    @property
    def f_B(self) -> ConceptBKey:
        return ConceptBKey._wrap(self.value.at("f_B", encoded=False))

    @f_B.setter
    def f_B(self, value: ConceptBKey) -> None:
        self.value.set("f_B", value._unwrap())

    @property
    def f_C(self) -> ConceptCKey:
        return ConceptCKey._wrap(self.value.at("f_C", encoded=False))

    @f_C.setter
    def f_C(self, value: ConceptCKey) -> None:
        self.value.set("f_C", value._unwrap())

    @property
    def f_D(self) -> ConceptDKey:
        return ConceptDKey._wrap(self.value.at("f_D", encoded=False))

    @f_D.setter
    def f_D(self, value: ConceptDKey) -> None:
        self.value.set("f_D", value._unwrap())

    @property
    def f_Klub(self) -> KlubKey:
        return KlubKey._wrap(self.value.at("f_Klub", encoded=False))

    @f_Klub.setter
    def f_Klub(self, value: KlubKey) -> None:
        self.value.set("f_Klub", value._unwrap())

    @property
    def f_any_concept(self) -> typing.Any:
        return self.value.at("f_any_concept")

    @f_any_concept.setter
    def f_any_concept(self, value: typing.Any) -> None:
        self.value.set("f_any_concept", value)

    def __repr__(self) -> str:
        return f"Demo::StructureU(f_bool={self.f_bool}, f_uint8={self.f_uint8}, f_uint16={self.f_uint16}, f_uint32={self.f_uint32}, f_uint64={self.f_uint64}, f_int8={self.f_int8}, f_int16={self.f_int16}, f_int32={self.f_int32}, f_int64={self.f_int64}, f_float={self.f_float}, f_double={self.f_double}, f_blob_id={self.f_blob_id}, f_commit_id={self.f_commit_id}, f_uuid={self.f_uuid}, f_string={self.f_string}, f_blob={self.f_blob}, f_vec={self.f_vec}, f_mat={self.f_mat}, f_tuple={self.f_tuple}, f_optional={self.f_optional}, f_vector={self.f_vector}, f_set={self.f_set}, f_set_s={self.f_set_s}, f_map_s1={self.f_map_s1}, f_map_s2={self.f_map_s2}, f_xarray={self.f_xarray}, f_xarray_s={self.f_xarray_s}, f_map_vs={self.f_map_vs}, f_variant={self.f_variant}, f_any={self.f_any}, f_E={self.f_E}, f_S={self.f_S}, f_T={self.f_T}, f_A={self.f_A}, f_B={self.f_B}, f_C={self.f_C}, f_D={self.f_D}, f_Klub={self.f_Klub}, f_any_concept={self.f_any_concept})"


__all__ = ["ConceptAKey", "ConceptBKey", "ConceptCoverageKey", "ConceptDKey", "ConceptCKey", "EmptyKlubKey", "KlubKey", "EnumerationE", "StructureS", "StructureT", "StructureU", "StructureV", "StructureW"]