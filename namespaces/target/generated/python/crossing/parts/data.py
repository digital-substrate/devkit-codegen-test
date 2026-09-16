# Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

"""Parts — les types que ce namespace déclare."""

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
                raise TypeError("cette valeur n'est pas un Parts::ThingKey")
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
        return f"{self.value.instance_id().encoded()}:Parts::ThingKey"

    def is_known(self) -> bool:
        return is_known(self.value)

    def __repr__(self) -> str:
        return self.description()


class Grade(enum.Enum):
    """Parts::Grade.

    Le même nom que Core::Grade, des cases différentes.

    UNE ÉNUMÉRATION PYTHON, PAS UN PROXY. Le pack en fait une classe qui enveloppe une
    `ValueEnumeration` ; Python en a une, et le runtime sait convertir depuis le nom d'un
    cas. Envelopper n'apporterait que du poids — et `Finish.matte` se lit mieux que
    `Finish("matte")`.
    """

    SOFT = "soft"
    HARD = "hard"

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
    """Parts::Colour.

    Le même nom que Core::Colour, en virgule flottante.
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