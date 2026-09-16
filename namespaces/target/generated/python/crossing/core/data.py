# Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

"""Core — les types que ce namespace déclare."""

from __future__ import annotations

import enum
import functools
import typing

import dsviper

from .. import definitions
from .._codegen import (NEUF as _NEUF, AnyConceptKey, Mapping, Ordered, Proxy, Sequence,
                        is_known, register, unwrap, wrap)

# ── l'identité de cette unité dans le modèle ──
#
# LE MÊME ARTEFACT QU'EN C++, POUR LA MÊME RAISON : plusieurs couches en ont besoin et ce
# n'est pas de la sérialisation. Il tient ici en une constante par type, parce qu'il n'y a
# pas de tag à porter — l'appelant nomme la classe.

OTHER: dsviper.ValueUUId = dsviper.ValueUUId.create("fe5c9495-ee60-2c05-59a7-76a3acb2102c")
THING: dsviper.ValueUUId = dsviper.ValueUUId.create("43ac162e-d31b-650b-ff35-6e284bd06ea2")
SUB_THING: dsviper.ValueUUId = dsviper.ValueUUId.create("4953d146-1dcb-1d23-03b4-2d7e90cef4b2")
KLUB: dsviper.ValueUUId = dsviper.ValueUUId.create("f99852de-1837-1c8c-c831-4fc0ceee8688")
GRADE: dsviper.ValueUUId = dsviper.ValueUUId.create("fbfc67e2-b360-2377-80bf-d58461a34eb0")
BAG: dsviper.ValueUUId = dsviper.ValueUUId.create("2a160921-2e7a-0f1a-2800-10ef9b577166")
COLOUR: dsviper.ValueUUId = dsviper.ValueUUId.create("771d31fe-d3b9-603c-ca38-43a03717815e")
DEFAULTS: dsviper.ValueUUId = dsviper.ValueUUId.create("7da8213c-bddd-98ee-c3c1-c9b26e3e6ef5")
SCALARS: dsviper.ValueUUId = dsviper.ValueUUId.create("3e6c9792-57f3-e845-33fb-a29fdcb567f9")
SINGLE: dsviper.ValueUUId = dsviper.ValueUUId.create("52b43309-f09f-02d0-fe4e-6baf9f7adf49")

class OtherKey(Proxy):
    """Une poignée sur une instance de Core::Other, pas la chose elle-même.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def concept(cls):
        """Le descripteur, résolu une fois."""
        return definitions().check_concept(OTHER)

    @classmethod
    @functools.cache
    def type(cls) -> dsviper.Type:
        """Le descripteur du type de la clé.

        `classmethod` et non fonction libre : en C++ il fallait `type(tag<T>{})` pour que la
        recherche par argument trouve l'unité de T. Python n'a pas cette recherche et n'en a
        pas besoin — l'appelant écrit déjà le nom de la classe.
        """
        return dsviper.TypeKey(cls.concept())

    def __init__(self, identifier: typing.Any = _NEUF):
        # `None` EXPLICITE N'EST PAS L'ABSENCE D'ARGUMENT. `OtherKey()` demande une clé
        # neuve ; `OtherKey(None)` passe quelque chose, et ce quelque chose n'est pas un
        # identifiant. Un témoin distingue les deux là où `None` ne le peut pas.
        if identifier is _NEUF:
            identifier = None
        elif identifier is None:
            raise TypeError("None n'est pas un identifiant d'instance")

        if isinstance(identifier, dsviper.ValueKey):
            if not identifier.is_member(self.concept()):
                raise TypeError("cette valeur n'est pas un Core::OtherKey")
            super().__init__(identifier)
        elif identifier is None or isinstance(identifier, (dsviper.ValueUUId, str)):
            super().__init__(dsviper.ValueKey.create(self.concept(), identifier))
        else:
            # UN IDENTIFIANT EST UNE CHAÎNE OU UN UUId, ET RIEN D'AUTRE. Laisser passer un
            # entier ou une liste ferait lever le runtime -- ce qui est juste, mais par une
            # erreur qui parle de décodage plutôt que du type qu'on lui a donné.
            raise TypeError(f"{identifier!r} n'est pas un identifiant d'instance")

    @classmethod
    def decode(cls, blob, **kwargs) -> OtherKey:
        """Relire depuis des octets : la classe connaît son type."""
        return cls(dsviper.ValueKey.cast(
            dsviper.Value.decode(blob, cls.type(), definitions(), **kwargs)))

    @classmethod
    def create(cls) -> OtherKey:
        """Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit."""
        return cls(dsviper.ValueUUId.create())

    def instance_id(self) -> dsviper.ValueUUId:
        return self.value.instance_id()

    def runtime_id(self) -> dsviper.ValueUUId:
        return self.value.type_concept().runtime_id()

    def is_valid(self) -> bool:
        return self.value.instance_id().is_valid()

    # La clé, vue sans son type.
    def to_any_concept_key(self) -> AnyConceptKey:
        return AnyConceptKey(self.value.to_any_concept_key())

    @classmethod
    def from_any_concept_key(cls, key) -> OtherKey | None:
        """La clé non typée, retypée — ou `None` si elle ne désigne pas ce concept.

        LE CHEMIN DE RETOUR, ET IL PEUT ÉCHOUER. Élargir ne perd rien ; rétrécir pose une
        question dont la réponse est dans l'identifiant que la valeur porte.
        """
        value = key.value if isinstance(key, Proxy) else key
        return cls(value) if value.type_concept().runtime_id() == OTHER else None

    def description(self) -> str:
        """L'instance et son type, dits comme le modèle les nomme.

        `Value.description()` du runtime rend `key<Demo::ConceptA>` : la forme du *type*, qui
        est juste et n'est pas ce qu'un lecteur cherche. Ici c'est le nom de la classe qu'il
        tient, et `__repr__` rend la même chose — deux façons de demander, une réponse.
        """
        return f"{self.value.instance_id().encoded()}:Core::OtherKey"

    def is_known(self) -> bool:
        return is_known(self.value)

    def __repr__(self) -> str:
        return self.description()



class ThingKey(Proxy):
    """Une poignée sur une instance de Core::Thing, pas la chose elle-même.

    Ce sur quoi on accroche des choses.
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

    def __init__(self, identifier: typing.Any = _NEUF):
        # `None` EXPLICITE N'EST PAS L'ABSENCE D'ARGUMENT. `ThingKey()` demande une clé
        # neuve ; `ThingKey(None)` passe quelque chose, et ce quelque chose n'est pas un
        # identifiant. Un témoin distingue les deux là où `None` ne le peut pas.
        if identifier is _NEUF:
            identifier = None
        elif identifier is None:
            raise TypeError("None n'est pas un identifiant d'instance")

        if isinstance(identifier, dsviper.ValueKey):
            if not identifier.is_member(self.concept()):
                raise TypeError("cette valeur n'est pas un Core::ThingKey")
            super().__init__(identifier)
        elif identifier is None or isinstance(identifier, (dsviper.ValueUUId, str)):
            super().__init__(dsviper.ValueKey.create(self.concept(), identifier))
        else:
            # UN IDENTIFIANT EST UNE CHAÎNE OU UN UUId, ET RIEN D'AUTRE. Laisser passer un
            # entier ou une liste ferait lever le runtime -- ce qui est juste, mais par une
            # erreur qui parle de décodage plutôt que du type qu'on lui a donné.
            raise TypeError(f"{identifier!r} n'est pas un identifiant d'instance")

    @classmethod
    def decode(cls, blob, **kwargs) -> ThingKey:
        """Relire depuis des octets : la classe connaît son type."""
        return cls(dsviper.ValueKey.cast(
            dsviper.Value.decode(blob, cls.type(), definitions(), **kwargs)))

    @classmethod
    def create(cls) -> ThingKey:
        """Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit."""
        return cls(dsviper.ValueUUId.create())

    def instance_id(self) -> dsviper.ValueUUId:
        return self.value.instance_id()

    def runtime_id(self) -> dsviper.ValueUUId:
        return self.value.type_concept().runtime_id()

    def is_valid(self) -> bool:
        return self.value.instance_id().is_valid()

    # La clé, vue sans son type.
    def to_any_concept_key(self) -> AnyConceptKey:
        return AnyConceptKey(self.value.to_any_concept_key())

    @classmethod
    def from_any_concept_key(cls, key) -> ThingKey | None:
        """La clé non typée, retypée — ou `None` si elle ne désigne pas ce concept.

        LE CHEMIN DE RETOUR, ET IL PEUT ÉCHOUER. Élargir ne perd rien ; rétrécir pose une
        question dont la réponse est dans l'identifiant que la valeur porte.
        """
        value = key.value if isinstance(key, Proxy) else key
        return cls(value) if value.type_concept().runtime_id() == THING else None

    def description(self) -> str:
        """L'instance et son type, dits comme le modèle les nomme.

        `Value.description()` du runtime rend `key<Demo::ConceptA>` : la forme du *type*, qui
        est juste et n'est pas ce qu'un lecteur cherche. Ici c'est le nom de la classe qu'il
        tient, et `__repr__` rend la même chose — deux façons de demander, une réponse.
        """
        return f"{self.value.instance_id().encoded()}:Core::ThingKey"

    def is_known(self) -> bool:
        return is_known(self.value)

    def __repr__(self) -> str:
        return self.description()



class SubThingKey(Proxy):
    """Une poignée sur une instance de Core::SubThing, pas la chose elle-même.

    Un dérivé, dans le même namespace : le cas facile de l'héritage.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def concept(cls):
        """Le descripteur, résolu une fois."""
        return definitions().check_concept(SUB_THING)

    @classmethod
    @functools.cache
    def type(cls) -> dsviper.Type:
        """Le descripteur du type de la clé.

        `classmethod` et non fonction libre : en C++ il fallait `type(tag<T>{})` pour que la
        recherche par argument trouve l'unité de T. Python n'a pas cette recherche et n'en a
        pas besoin — l'appelant écrit déjà le nom de la classe.
        """
        return dsviper.TypeKey(cls.concept())

    def __init__(self, identifier: typing.Any = _NEUF):
        # `None` EXPLICITE N'EST PAS L'ABSENCE D'ARGUMENT. `SubThingKey()` demande une clé
        # neuve ; `SubThingKey(None)` passe quelque chose, et ce quelque chose n'est pas un
        # identifiant. Un témoin distingue les deux là où `None` ne le peut pas.
        if identifier is _NEUF:
            identifier = None
        elif identifier is None:
            raise TypeError("None n'est pas un identifiant d'instance")

        if isinstance(identifier, dsviper.ValueKey):
            if not identifier.is_member(self.concept()):
                raise TypeError("cette valeur n'est pas un Core::SubThingKey")
            super().__init__(identifier)
        elif identifier is None or isinstance(identifier, (dsviper.ValueUUId, str)):
            super().__init__(dsviper.ValueKey.create(self.concept(), identifier))
        else:
            # UN IDENTIFIANT EST UNE CHAÎNE OU UN UUId, ET RIEN D'AUTRE. Laisser passer un
            # entier ou une liste ferait lever le runtime -- ce qui est juste, mais par une
            # erreur qui parle de décodage plutôt que du type qu'on lui a donné.
            raise TypeError(f"{identifier!r} n'est pas un identifiant d'instance")

    @classmethod
    def decode(cls, blob, **kwargs) -> SubThingKey:
        """Relire depuis des octets : la classe connaît son type."""
        return cls(dsviper.ValueKey.cast(
            dsviper.Value.decode(blob, cls.type(), definitions(), **kwargs)))

    @classmethod
    def create(cls) -> SubThingKey:
        """Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit."""
        return cls(dsviper.ValueUUId.create())

    def instance_id(self) -> dsviper.ValueUUId:
        return self.value.instance_id()

    def runtime_id(self) -> dsviper.ValueUUId:
        return self.value.type_concept().runtime_id()

    def is_valid(self) -> bool:
        return self.value.instance_id().is_valid()

    # La clé, vue sans son type.
    def to_any_concept_key(self) -> AnyConceptKey:
        return AnyConceptKey(self.value.to_any_concept_key())

    @classmethod
    def from_any_concept_key(cls, key) -> SubThingKey | None:
        """La clé non typée, retypée — ou `None` si elle ne désigne pas ce concept.

        LE CHEMIN DE RETOUR, ET IL PEUT ÉCHOUER. Élargir ne perd rien ; rétrécir pose une
        question dont la réponse est dans l'identifiant que la valeur porte.
        """
        value = key.value if isinstance(key, Proxy) else key
        return cls(value) if value.type_concept().runtime_id() == SUB_THING else None

    def description(self) -> str:
        """L'instance et son type, dits comme le modèle les nomme.

        `Value.description()` du runtime rend `key<Demo::ConceptA>` : la forme du *type*, qui
        est juste et n'est pas ce qu'un lecteur cherche. Ici c'est le nom de la classe qu'il
        tient, et `__repr__` rend la même chose — deux façons de demander, une réponse.
        """
        return f"{self.value.instance_id().encoded()}:Core::SubThingKey"

    def is_known(self) -> bool:
        return is_known(self.value)

    def __repr__(self) -> str:
        return self.description()

    def to_parent_key(self):
        """Élargir vers le parent.

        NE PERD RIEN ET NE PEUT PAS ÉCHOUER : l'identifiant d'exécution reste celui du concept
        réel, et c'est ce qui permet d'en revenir ensuite.
        """
        return ThingKey(self.value)


class KlubKey(Proxy):
    """Une poignée sur une instance d'un membre de Core::Klub.

    Un club, dont les membres vivent ici.

    ON N'Y CRÉE PAS D'INSTANCE : un club n'est pas un concept, rien n'est « un Klub ». On y
    entre depuis la clé d'un membre, et on en sort en demandant si c'en est un. Le pack
    donne à la clé de club un `create()` qui passe le descripteur du club là où le runtime
    attend celui d'un concept ; c'est un vérificateur de types qui l'a dit.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def club(cls) -> dsviper.TypeClub:
        """Le descripteur du club, résolu une fois."""
        return definitions().check_club(KLUB)

    @classmethod
    @functools.cache
    def type(cls) -> dsviper.Type:
        return dsviper.TypeKey(cls.club())

    def __init__(self, key):
        value = key.value if isinstance(key, Proxy) else key
        if not isinstance(value, dsviper.ValueKey):
            raise TypeError("cette valeur n'est pas une clé")
        if not self.club().is_member(value.type_concept()):
            raise TypeError("cette clé ne désigne pas un membre de Core::Klub")
        super().__init__(value.to_club_key(self.club()))

    def instance_id(self) -> dsviper.ValueUUId:
        return self.value.instance_id()

    def runtime_id(self) -> dsviper.ValueUUId:
        return self.value.type_concept().runtime_id()

    def is_valid(self) -> bool:
        return self.value.instance_id().is_valid()

    # La clé, vue sans son type.
    def to_any_concept_key(self) -> AnyConceptKey:
        return AnyConceptKey(self.value.to_any_concept_key())

    @classmethod
    def from_any_concept_key(cls, key) -> KlubKey | None:
        """La clé non typée, retypée — ou `None` si elle ne désigne pas ce concept.

        LE CHEMIN DE RETOUR, ET IL PEUT ÉCHOUER. Élargir ne perd rien ; rétrécir pose une
        question dont la réponse est dans l'identifiant que la valeur porte.
        """
        value = key.value if isinstance(key, Proxy) else key
        return cls(value) if value.type_concept().runtime_id() == KLUB else None

    def description(self) -> str:
        """L'instance et son type, dits comme le modèle les nomme.

        `Value.description()` du runtime rend `key<Demo::ConceptA>` : la forme du *type*, qui
        est juste et n'est pas ce qu'un lecteur cherche. Ici c'est le nom de la classe qu'il
        tient, et `__repr__` rend la même chose — deux façons de demander, une réponse.
        """
        return f"{self.value.instance_id().encoded()}:Core::KlubKey"

    def is_known(self) -> bool:
        return is_known(self.value)

    @classmethod
    def from_other_key(cls, key) -> KlubKey:
        """La clé d'un membre, vue comme celle du club."""
        return cls(key.value if isinstance(key, Proxy) else key)

    @classmethod
    def from_sub_thing_key(cls, key) -> KlubKey:
        """La clé d'un membre, vue comme celle du club."""
        return cls(key.value if isinstance(key, Proxy) else key)

    def to_other_key(self):
        """La clé vue comme celle de ce membre, ou `None` si l'instance n'en est pas un."""
        return self.as_(OtherKey)

    def to_sub_thing_key(self):
        """La clé vue comme celle de ce membre, ou `None` si l'instance n'en est pas un."""
        return self.as_(SubThingKey)

    def as_(self, cls):
        """La clé vue comme celle d'un membre, ou `None` si l'instance n'en est pas un."""
        concept = cls.concept()
        return cls(self.value.to_member_key(concept)) if self.value.is_member(concept) else None

    def __repr__(self) -> str:
        return self.description()

class Grade(enum.Enum):
    """Core::Grade.

    Une énumération, que d'autres namespaces vont référencer.

    UNE ÉNUMÉRATION PYTHON, PAS UN PROXY. Le pack en fait une classe qui enveloppe une
    `ValueEnumeration` ; Python en a une, et le runtime sait convertir depuis le nom d'un
    cas. Envelopper n'apporterait que du poids — et `Finish.matte` se lit mieux que
    `Finish("matte")`.
    """

    LOW = "low"
    HIGH = "high"

    @classmethod
    @functools.cache
    def type(cls) -> dsviper.TypeEnumeration:
        return definitions().check_enumeration(GRADE)

    @classmethod
    def from_str(cls, name: str) -> Grade:
        """Depuis le nom d'un cas, et depuis rien d'autre.

        LE CONSTRUCTEUR EST PLUS LARGE : il prend aussi un rang, parce qu'un appel venu du
        dynamique en tient un. `from_str` dit ce qu'il attend, donc il refuse le reste par une
        erreur de type — ce sont deux portes, et elles n'ouvrent pas sur la même chose.
        """
        if not isinstance(name, str):
            raise TypeError(f"{name!r} n'est pas un nom de cas")
        return cls(name)

    @classmethod
    def _missing_(cls, value):
        """Se construire depuis un rang, comme le modèle les numérote.

        `enum.Enum` cherche par valeur ; le pack acceptait aussi l'index, et c'est ce qu'un
        appelant qui vient du dynamique tient. Les deux entrées, une seule classe.
        """
        # `in range(...)` plutôt qu'une double comparaison : un `<` dans un corps de
        # template ouvre une expression StringTemplate, et le fichier rendu s'arrête là.
        if isinstance(value, int) and not isinstance(value, bool):
            cases = list(cls)
            if value in range(len(cases)):
                return cases[value]
            return None
        if isinstance(value, str):
            return None          # un nom inconnu est une erreur de valeur
        # NI UN NOM NI UN RANG : c'est une erreur de type et non de valeur.
        raise TypeError(f"{value!r} n'est ni un cas de Grade ni un rang")

    def index(self) -> int:
        return list(type(self)).index(self)

    def encode(self, **kwargs) -> dsviper.ValueBlob:
        return dsviper.Value.encode(dsviper.ValueEnumeration(type(self).type(), self.value), **kwargs)

    @classmethod
    def decode(cls, blob, **kwargs) -> Grade:
        return cls._wrap(dsviper.Value.decode(blob, cls.type(), definitions(), **kwargs))

    @classmethod
    def _wrap(cls, value) -> Grade:
        return cls(dsviper.ValueEnumeration.cast(value).name())

    def _unwrap(self) -> str:
        return self.value

class Colour(Proxy):
    """Core::Colour.

    Le même nom que Parts::Colour, un type différent -- la collision de re-export.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def type(cls) -> dsviper.TypeStructure:
        return definitions().check_structure(COLOUR)

    @classmethod
    def decode(cls, blob, **kwargs) -> Colour:
        """Relire depuis des octets : la classe connaît son type, donc elle peut le demander."""
        return cls(dsviper.ValueStructure.cast(
            dsviper.Value.decode(blob, cls.type(), definitions(), **kwargs)))

    def __init__(self, value: dsviper.ValueStructure | dict | None = None, /, **fields):
        if value is None:
            value = dsviper.ValueStructure(self.type())
        elif isinstance(value, dict):
            value = dsviper.ValueStructure(self.type(), value)
        elif value.type() != self.type():
            raise TypeError("cette valeur n'est pas un Core::Colour")
        super().__init__(value)

        for name, field in fields.items():
            setattr(self, name, field)

    @property
    def r(self) -> int:
        return self.value.at("r")

    @r.setter
    def r(self, value: int) -> None:
        self.value.set("r", value)

    @property
    def g(self) -> int:
        return self.value.at("g")

    @g.setter
    def g(self, value: int) -> None:
        self.value.set("g", value)

    @property
    def b(self) -> int:
        return self.value.at("b")

    @b.setter
    def b(self, value: int) -> None:
        self.value.set("b", value)

    def __repr__(self) -> str:
        return f"Core::Colour(r={self.r}, g={self.g}, b={self.b})"


class Scalars(Proxy):
    """Core::Scalars.

    Toutes les formes scalaires du langage, dans le namespace qui n'en référence aucun
    autre. Ce qui ne peut pas traverser une frontière est couvert ici, une fois.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def type(cls) -> dsviper.TypeStructure:
        return definitions().check_structure(SCALARS)

    @classmethod
    def decode(cls, blob, **kwargs) -> Scalars:
        """Relire depuis des octets : la classe connaît son type, donc elle peut le demander."""
        return cls(dsviper.ValueStructure.cast(
            dsviper.Value.decode(blob, cls.type(), definitions(), **kwargs)))

    def __init__(self, value: dsviper.ValueStructure | dict | None = None, /, **fields):
        if value is None:
            value = dsviper.ValueStructure(self.type())
        elif isinstance(value, dict):
            value = dsviper.ValueStructure(self.type(), value)
        elif value.type() != self.type():
            raise TypeError("cette valeur n'est pas un Core::Scalars")
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
    def f_any(self) -> typing.Any:
        return self.value.at("f_any")

    @f_any.setter
    def f_any(self, value: typing.Any) -> None:
        self.value.set("f_any", value)

    @property
    def f_vec(self) -> Sequence[int]:
        return wrap(self.value.at("f_vec", encoded=False))

    @f_vec.setter
    def f_vec(self, value: Sequence[int]) -> None:
        self.value.set("f_vec", unwrap(value))

    @property
    def f_mat(self) -> Sequence[Sequence[int]]:
        return wrap(self.value.at("f_mat", encoded=False))

    @f_mat.setter
    def f_mat(self, value: Sequence[Sequence[int]]) -> None:
        self.value.set("f_mat", unwrap(value))

    def __repr__(self) -> str:
        return f"Core::Scalars(f_bool={self.f_bool}, f_uint8={self.f_uint8}, f_uint16={self.f_uint16}, f_uint32={self.f_uint32}, f_uint64={self.f_uint64}, f_int8={self.f_int8}, f_int16={self.f_int16}, f_int32={self.f_int32}, f_int64={self.f_int64}, f_float={self.f_float}, f_double={self.f_double}, f_blob_id={self.f_blob_id}, f_commit_id={self.f_commit_id}, f_uuid={self.f_uuid}, f_string={self.f_string}, f_blob={self.f_blob}, f_any={self.f_any}, f_vec={self.f_vec}, f_mat={self.f_mat})"


class Single(Proxy):
    """Core::Single.

    Une structure à un seul champ : le cas zéro/un que le générateur traite à part.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def type(cls) -> dsviper.TypeStructure:
        return definitions().check_structure(SINGLE)

    @classmethod
    def decode(cls, blob, **kwargs) -> Single:
        """Relire depuis des octets : la classe connaît son type, donc elle peut le demander."""
        return cls(dsviper.ValueStructure.cast(
            dsviper.Value.decode(blob, cls.type(), definitions(), **kwargs)))

    def __init__(self, value: dsviper.ValueStructure | dict | None = None, /, **fields):
        if value is None:
            value = dsviper.ValueStructure(self.type())
        elif isinstance(value, dict):
            value = dsviper.ValueStructure(self.type(), value)
        elif value.type() != self.type():
            raise TypeError("cette valeur n'est pas un Core::Single")
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
        return f"Core::Single(f_single={self.f_single})"


class Bag(Proxy):
    """Core::Bag.

    Et un document ordinaire dont un champ est un agrégat : les mêmes opérations, à une
    adresse au lieu de la racine.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def type(cls) -> dsviper.TypeStructure:
        return definitions().check_structure(BAG)

    @classmethod
    def decode(cls, blob, **kwargs) -> Bag:
        """Relire depuis des octets : la classe connaît son type, donc elle peut le demander."""
        return cls(dsviper.ValueStructure.cast(
            dsviper.Value.decode(blob, cls.type(), definitions(), **kwargs)))

    def __init__(self, value: dsviper.ValueStructure | dict | None = None, /, **fields):
        if value is None:
            value = dsviper.ValueStructure(self.type())
        elif isinstance(value, dict):
            value = dsviper.ValueStructure(self.type(), value)
        elif value.type() != self.type():
            raise TypeError("cette valeur n'est pas un Core::Bag")
        super().__init__(value)

        for name, field in fields.items():
            setattr(self, name, field)

    @property
    def members(self) -> Sequence[ThingKey]:
        return wrap(self.value.at("members", encoded=False))

    @members.setter
    def members(self, value: Sequence[ThingKey]) -> None:
        self.value.set("members", unwrap(value))

    @property
    def tints(self) -> Mapping[ThingKey, Colour]:
        return wrap(self.value.at("tints", encoded=False))

    @tints.setter
    def tints(self, value: Mapping[ThingKey, Colour]) -> None:
        self.value.set("tints", unwrap(value))

    @property
    def trail(self) -> Ordered[Colour]:
        return wrap(self.value.at("trail", encoded=False))

    @trail.setter
    def trail(self, value: Ordered[Colour]) -> None:
        self.value.set("trail", unwrap(value))

    def __repr__(self) -> str:
        return f"Core::Bag(members={self.members}, tints={self.tints}, trail={self.trail})"


class Defaults(Proxy):
    """Core::Defaults.

    Les valeurs par défaut, qui sont un chemin de code à part.
    """

    __slots__ = ()

    @classmethod
    @functools.cache
    def type(cls) -> dsviper.TypeStructure:
        return definitions().check_structure(DEFAULTS)

    @classmethod
    def decode(cls, blob, **kwargs) -> Defaults:
        """Relire depuis des octets : la classe connaît son type, donc elle peut le demander."""
        return cls(dsviper.ValueStructure.cast(
            dsviper.Value.decode(blob, cls.type(), definitions(), **kwargs)))

    def __init__(self, value: dsviper.ValueStructure | dict | None = None, /, **fields):
        if value is None:
            value = dsviper.ValueStructure(self.type())
        elif isinstance(value, dict):
            value = dsviper.ValueStructure(self.type(), value)
        elif value.type() != self.type():
            raise TypeError("cette valeur n'est pas un Core::Defaults")
        super().__init__(value)

        for name, field in fields.items():
            setattr(self, name, field)

    @property
    def f_uint8(self) -> int:
        return self.value.at("f_uint8")

    @f_uint8.setter
    def f_uint8(self, value: int) -> None:
        self.value.set("f_uint8", value)

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

    @property
    def f_uuid(self) -> dsviper.ValueUUId:
        return self.value.at("f_uuid")

    @f_uuid.setter
    def f_uuid(self, value: dsviper.ValueUUId) -> None:
        self.value.set("f_uuid", value)

    @property
    def f_vec(self) -> Sequence[int]:
        return wrap(self.value.at("f_vec", encoded=False))

    @f_vec.setter
    def f_vec(self, value: Sequence[int]) -> None:
        self.value.set("f_vec", unwrap(value))

    @property
    def f_grade(self) -> Grade:
        return wrap(self.value.at("f_grade", encoded=False))

    @f_grade.setter
    def f_grade(self, value: Grade) -> None:
        self.value.set("f_grade", unwrap(value))

    @property
    def f_colour(self) -> Colour:
        return wrap(self.value.at("f_colour", encoded=False))

    @f_colour.setter
    def f_colour(self, value: Colour) -> None:
        self.value.set("f_colour", unwrap(value))

    def __repr__(self) -> str:
        return f"Core::Defaults(f_uint8={self.f_uint8}, f_float={self.f_float}, f_string={self.f_string}, f_uuid={self.f_uuid}, f_vec={self.f_vec}, f_grade={self.f_grade}, f_colour={self.f_colour})"


# Les classes de cette unité, par l'identifiant d'exécution de leur type : c'est ce qui
# permet à `wrap` de rendre un élément de conteneur avec son nom, sans qu'aucune classe de
# conteneur existe.
register({OTHER: OtherKey, THING: ThingKey, SUB_THING: SubThingKey, KLUB: KlubKey, GRADE: Grade, BAG: Bag, COLOUR: Colour, DEFAULTS: Defaults, SCALARS: Scalars, SINGLE: Single})

__all__ = ["OtherKey", "ThingKey", "SubThingKey", "KlubKey", "Grade", "Bag", "Colour", "Defaults", "Scalars", "Single"]