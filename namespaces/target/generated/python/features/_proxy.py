"""Ce que toute classe générée a en commun — écrit une fois, pour tous.

UNE CLASSE GÉNÉRÉE ENVELOPPE UNE `dsviper.Value`, ELLE NE LA COPIE PAS. La donnée vit dans
la Value ; la classe lui donne des noms. Tout ce qui découle de ça — l'égalité, le hachage,
la lecture de la valeur enveloppée — ne dépend d'aucun type du modèle, donc rien de tout
cela n'a à être émis une fois par type.

ET IL FAUT UNE BASE COMMUNE, PAS SEULEMENT PARCE QUE C'EST PLUS COURT. La liaison Python ne
relie pas `dsviper.ValueStructure` à `dsviper.Value` à l'exécution : `isinstance(v,
dsviper.Value)` est faux pour toute valeur concrète, alors que le `.pyi` déclare
`class ValueStructure(Value)`. Il n'y a donc aucun moyen de reconnaître une valeur du
runtime par son type ; reconnaître *nos* classes est le seul test qui tienne, et il demande
qu'elles aient un ancêtre.
"""

from __future__ import annotations

import dsviper


class Proxy:
    """Une valeur du modèle, nommée.

    L'ÉGALITÉ PORTE SUR LA VALEUR ET SUR LA CLASSE. `ModelA::Colour` et `ModelB::Colour`
    enveloppent des Values de types différents, donc la comparaison de valeurs suffirait ;
    exiger la même classe le dit quand même, parce que c'est ce qui est voulu et non ce qui
    se trouve être vrai.
    """

    __slots__ = ("_value",)

    def __init__(self, value):
        self._value = value

    @property
    def value(self):
        """La valeur du runtime. C'est la donnée ; la classe n'en est que la lecture."""
        return self._value

    def __eq__(self, other) -> bool:
        return type(self) is type(other) and self._value == other._value

    def __hash__(self) -> int:
        return self._value.hash()

    def encode(self) -> dsviper.ValueBlob:
        return dsviper.Value.encode(self._value)

    def hexdigest(self) -> str:
        return dsviper.Value.hexdigest(self._value)

    # ── le passage, dans les deux sens ──
    #
    # UN SEUL COUPLE DE NOMS POUR TOUT CE QUI A UNE CLASSE. Une structure et une clé sont des
    # `Proxy` ; une énumération est une `enum.Enum` de Python et n'en est pas une. Sans un
    # protocole commun, le code généré devrait savoir laquelle des deux il tient — donc
    # porter dans le template une distinction que le modèle connaît déjà.

    @classmethod
    def _wrap(cls, value) -> "Proxy":
        return cls(value)

    def _unwrap(self):
        return self._value


def unwrap(value):
    """La Value que le runtime attend, depuis ce que l'appelant a écrit.

    Ce qui n'est pas une de nos classes passe tel quel : `Value.loads` du runtime sait déjà
    convertir un objet Python depuis le descripteur de type, donc un `int`, un `str` ou un
    `dict` n'a besoin de rien ici.
    """
    return value._unwrap() if hasattr(value, "_unwrap") else value


class AnyConceptKey(Proxy):
    """Une clé sur une instance de n'importe quel concept.

    LE C++ EN GÉNÈRE UNE PAR MODÈLE ; ICI IL N'EN FAUT AUCUNE. Elle ne nomme aucun type :
    elle enveloppe un `ValueKey` et pose ses questions au descripteur que la valeur porte
    déjà. Ce qu'une version générée y ajoutait — savoir nommer les concepts du modèle — est
    dans les définitions embarquées, lues à l'exécution, ce qui la rend juste aussi pour un
    descendant apparu après la génération.
    """

    __slots__ = ()

    def __init__(self, value: dsviper.ValueKey):
        if not isinstance(value, dsviper.ValueKey):
            raise TypeError("cette valeur n'est pas une clé")
        super().__init__(value)

    @property
    def instance_id(self) -> dsviper.ValueUUId:
        return self.value.instance_id()

    @property
    def runtime_id(self) -> dsviper.ValueUUId:
        return self.value.type_concept().runtime_id()

    def is_valid(self) -> bool:
        return self.instance_id.is_valid()

    def as_(self, cls):
        """La clé vue comme celle d'un concept donné, ou `None` si elle n'en est pas une."""
        return cls(self.value) if self.value.type() == cls.type() else None

    def __repr__(self) -> str:
        return f"AnyConceptKey({self.value.representation()})"
