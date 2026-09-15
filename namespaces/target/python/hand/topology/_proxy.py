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


def unwrap(value):
    """La Value que le runtime attend, depuis ce que l'appelant a écrit.

    Ce qui n'est pas une de nos classes passe tel quel : `Value.loads` du runtime sait déjà
    convertir un objet Python depuis le descripteur de type, donc un `int`, un `str` ou un
    `dict` n'a besoin de rien ici.
    """
    return value.value if isinstance(value, Proxy) else value
