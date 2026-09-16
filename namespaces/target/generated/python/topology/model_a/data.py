# Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

"""ModelA — les types que ce namespace déclare."""

from __future__ import annotations

import enum
import functools
import typing

import dsviper

from .. import definitions
from .._codegen import (AnyConceptKey, Mapping, Ordered, Proxy, Sequence, is_known,
                        register, unwrap, wrap)

# ── l'identité de cette unité dans le modèle ──
#
# LE MÊME ARTEFACT QU'EN C++, POUR LA MÊME RAISON : plusieurs couches en ont besoin et ce
# n'est pas de la sérialisation. Il tient ici en une constante par type, parce qu'il n'y a
# pas de tag à porter — l'appelant nomme la classe.

MATERIAL: dsviper.ValueUUId = dsviper.ValueUUId.create("de42abc9-3fd6-ac10-63ba-d0d6fba6cb9e")
FINISH: dsviper.ValueUUId = dsviper.ValueUUId.create("cc101b86-fc5f-855a-b0f6-59844b9f5e3e")
COLOUR: dsviper.ValueUUId = dsviper.ValueUUId.create("887a78c8-07ff-3c8a-8172-ff5ae381dfd9")

class MaterialKey(Proxy):
    """Une poignée sur une instance de ModelA::Material, pas la chose elle-même.

    A material, as ModelA understands one.
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
            if not identifier.is_member(self.concept()):
                raise TypeError("cette valeur n'est pas un ModelA::MaterialKey")
            super().__init__(identifier)
        else:
            super().__init__(dsviper.ValueKey.create(self.concept(), identifier))

    @classmethod
    def decode(cls, blob, **kwargs) -> MaterialKey:
        """Relire depuis des octets : la classe connaît son type."""
        return cls(dsviper.ValueKey.cast(
            dsviper.Value.decode(blob, cls.type(), definitions(), **kwargs)))

    @classmethod
    def create(cls) -> MaterialKey:
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
    def from_any_concept_key(cls, key) -> MaterialKey | None:
        """La clé non typée, retypée — ou `None` si elle ne désigne pas ce concept.

        LE CHEMIN DE RETOUR, ET IL PEUT ÉCHOUER. Élargir ne perd rien ; rétrécir pose une
        question dont la réponse est dans l'identifiant que la valeur porte.
        """
        value = key.value if isinstance(key, Proxy) else key
        return cls(value) if value.type_concept().runtime_id() == MATERIAL else None

    def description(self) -> str:
        return self.value.description()

    def is_known(self) -> bool:
        return is_known(self.value)

    def __repr__(self) -> str:
        return f"ModelA::MaterialKey({self.value.representation()})"

class Finish(enum.Enum):
    """ModelA::Finish.

    Un type énuméré, pour que les templates en rencontrent un. Aucun autre namespace
    n'en déclare, et c'est voulu : ce qui est testé ici est la topologie, pas le système de
    types -- mais une couche qui ne sait pas sérialiser une énumération est incomplète.

    UNE ÉNUMÉRATION PYTHON, PAS UN PROXY. Le pack en fait une classe qui enveloppe une
    `ValueEnumeration` ; Python en a une, et le runtime sait convertir depuis le nom d'un
    cas. Envelopper n'apporterait que du poids — et `Finish.matte` se lit mieux que
    `Finish("matte")`.
    """

    MATTE = "matte"
    GLOSS = "gloss"

    @classmethod
    @functools.cache
    def type(cls) -> dsviper.TypeEnumeration:
        return definitions().check_enumeration(FINISH)

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
        # NI UN NOM NI UN RANG : c'est une erreur de type et non de valeur, et le dire
        # autrement enverrait l'appelant chercher une faute là où il n'y en a pas.
        raise TypeError(f"{value!r} n'est ni un cas de Finish ni un rang")

    def index(self) -> int:
        return list(type(self)).index(self)

    def encode(self, **kwargs) -> dsviper.ValueBlob:
        return dsviper.Value.encode(dsviper.ValueEnumeration(type(self).type(), self.value), **kwargs)

    @classmethod
    def decode(cls, blob, **kwargs) -> Finish:
        return cls._wrap(dsviper.Value.decode(blob, cls.type(), definitions(), **kwargs))

    @classmethod
    def _wrap(cls, value) -> Finish:
        return cls(dsviper.ValueEnumeration.cast(value).name())

    def _unwrap(self) -> str:
        return self.value

class Colour(Proxy):
    """ModelA::Colour.

    Colour in 8-bit channels -- the same name as ModelB::Colour, a different type.
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
            raise TypeError("cette valeur n'est pas un ModelA::Colour")
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
        return f"ModelA::Colour(r={self.r}, g={self.g}, b={self.b})"


# Les classes de cette unité, par l'identifiant d'exécution de leur type : c'est ce qui
# permet à `wrap` de rendre un élément de conteneur avec son nom, sans qu'aucune classe de
# conteneur existe.
register({MATERIAL: MaterialKey, FINISH: Finish, COLOUR: Colour})

__all__ = ["MaterialKey", "Finish", "Colour"]