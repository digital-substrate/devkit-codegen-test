"""L'accesseur typé d'un attachment — écrit une fois, pour tous.

CE FICHIER NE NOMME AUCUN TYPE DU MODÈLE, ET C'EST TOUT SON PROPOS. Le pack Python écrit
188 lignes de template qui rendent 2 454 lignes pour `features` : une famille de fonctions
par attachment, `modela_material_colour_get`, `..._set`, `..._keys`, `..._diff`. Pas une
seule ne fait autre chose que passer le descripteur de l'attachment à `AttachmentGetting` ou
`AttachmentMutating`. Ce qui varie d'un attachment à l'autre — son identifiant, la classe de
sa clé, la classe de son document — sont trois valeurs, pas trois cents lignes.

Donc c'est un objet paramétré par ces trois valeurs. Une unité en déclare un par attachment
qu'elle porte, et n'écrit rien d'autre. C'est l'équivalent Python du `Viper_TypedCodec`
du C++ : la place de ce fichier est dans le runtime, pas dans le code généré.
"""

from __future__ import annotations

import functools
from typing import Callable

import dsviper

from .proxy import unwrap as _unwrap, wrap as _wrap


class AttachmentProxy:
    """Un attachment du modèle, vu depuis l'unité qui le déclare.

    `AttachmentProxy` ET NON `Attachment`, PARCE QUE `dsviper.Attachment` EXISTE ET N'EST PAS
    ÇA. Le sien est le *descripteur* -- ce que les définitions portent : un identifiant, un
    type de clé, un type de document. Celui-ci est l'accesseur typé qui le résout et s'en
    sert, comme `Proxy` est l'accesseur typé d'une `Value`. Tant que les deux vivent dans
    des modules différents la confusion n'est que de lecture ; le jour où ceux-ci entrent
    dans `dsviper`, où ils ont vocation à aller, deux `Attachment` dans un même module
    s'écrasent -- et c'est le dernier des deux qui gagne, sans un mot.

    LA BASE N'A PRESQUE PAS DE MÉTHODES À ELLE. `dsviper.Database` n'hérite pas
    d'`AttachmentGetting` — la liaison Python ne les relie pas — mais elle porte les mêmes
    `keys`, `has`, `get` et `set`, et rien ici ne demande davantage : chaque méthode ne fait
    que passer le descripteur. Il ne reste en propre que `delete`, qu'un état en mémoire
    n'offre pas. C'est le même constat qu'en C++, où cinq gabarits étaient devenus deux.
    """

    # Pas de __slots__ : `cached_property` écrit son résultat dans l'instance.

    def __init__(self, runtime_id: dsviper.ValueUUId,
                 definitions: Callable[[], dsviper.DefinitionsConst],
                 key: type, document: type | None):
        self._runtime_id = runtime_id
        self._definitions = definitions

        # LES DEUX CLASSES NE SERVENT PAS À CONVERTIR — `wrap` le fait depuis le type que la
        # valeur porte. Elles sont retenues parce que les nommer dans l'unité **force leur
        # import**, et que c'est l'import qui remplit la table des classes. Sans elles la
        # conversion marcherait tant que quelqu'un d'autre a importé l'unité d'abord, ce qui
        # est la pire forme de correction : celle qui dépend de l'ordre.
        self._key = key
        self._document = document

    @functools.cached_property
    def descriptor(self) -> dsviper.Attachment:
        """Le descripteur que le runtime en tire, résolu une fois.

        PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE : les cinq opérations, l'épreuve sur base,
        le pont dynamique. Une identité, un endroit.
        """
        return self._definitions().check_attachment(self._runtime_id)

    # ── lire ──
    #
    # Le contexte est le premier paramètre, et il est le seul que l'appelant ne pourrait pas
    # deviner : c'est lui qui dit sur quoi l'appel porte — un état en mémoire, une base.

    def keys(self, getting: dsviper.AttachmentGetting) -> set:
        return {_wrap(key) for key in getting.keys(self.descriptor)}

    def has(self, getting: dsviper.AttachmentGetting, key) -> bool:
        return getting.has(self.descriptor, key.value)

    def get(self, getting: dsviper.AttachmentGetting, key):
        """Le document, ou `None` — et non un `Optional` enveloppé.

        LE PACK REND UN `Optional_Colour`, UN PROXY DE PLUS À NOMMER ET À GÉNÉRER. Python a
        déjà `None` et `if x is None`, qui disent la même chose sans qu'une classe existe
        pour ça. C'est l'écart le plus visible avec la sortie du pack, et il est délibéré.
        """
        document = getting.get(self.descriptor, key.value)
        return None if document.is_nil() else _wrap(document.unwrap())

    def diff_keys(self, current: dsviper.AttachmentGetting, other: dsviper.AttachmentGetting):
        added, removed, different, same = dsviper.AttachmentGetting.diff_keys(
            current, other, self.descriptor)
        return tuple({_wrap(key) for key in group}
                     for group in (added, removed, different, same))

    # ── écrire ──

    def set(self, mutating: dsviper.AttachmentMutating | dsviper.Database, key, value):
        """Poser le document.

        Rend ce que le contexte rend : rien pour un état en mémoire, un statut pour une
        base — un enregistrement peut échouer là où un changement en mémoire ne le peut pas.
        """
        return mutating.set(self.descriptor, key.value, _unwrap(value))

    def delete(self, database: dsviper.Database, key) -> bool:
        """Retirer le document. La seule opération qu'une base ajoute."""
        return database.delete(self.descriptor, key.value)

    def diff(self, mutating: dsviper.AttachmentMutating, key, value, *, recursive: bool = False) -> None:
        mutating.diff(self.descriptor, key.value, _unwrap(value), recursive=recursive)

    def update(self, mutating: dsviper.AttachmentMutating, key, field: str, value) -> None:
        """Écrire un seul champ.

        LE CHEMIN SE FAIT DEPUIS LE NOM DU CHAMP, ICI ET MAINTENANT. Le pack en fait un
        module entier — `Path_Colour.r`, une constante par champ de chaque structure du
        modèle — alors que `Path.from_field("r")` ne dépend que du nom, que l'appelant vient
        d'écrire. La mémoïsation rend le coût nul et la génération inutile.
        """
        mutating.update(self.descriptor, key.value, _path(field), _unwrap(value))

    def __getattr__(self, name: str):
        """`set_<champ>`, `union_<champ>`, `subtract_<champ>` — dérivés du type du document.

        LE PACK EN ÉMET UN PAR CHAMP DE CHAQUE DOCUMENT DE CHAQUE ATTACHMENT. Ici le document
        connaît ses champs : l'objet répond au nom qu'on lui demande s'il correspond à l'un
        d'eux, et lève sinon -- ce qui est le même fail-fast qu'un attribut absent, avec un
        message qui dit ce qui existe.
        """
        for prefix, operation in (("set_", "update"),
                                  ("union_", "union_in_set"),
                                  ("subtract_", "subtract_in_set")):
            if not name.startswith(prefix):
                continue
            field = name[len(prefix):]
            document = self.descriptor.document_type()
            query = getattr(document, "query", None)
            if query is None or query(field) is None:
                break

            def bound(mutating, key, value, _field=field, _operation=operation):
                getattr(mutating, _operation)(
                    self.descriptor, _unwrap(key), _path(_field), _unwrap(value))

            return bound

        raise AttributeError(
            f"{self.descriptor.representation()} n'a pas de champ pour '{name}'")

    def __repr__(self) -> str:
        return f"AttachmentProxy({self.descriptor.representation()})"


@functools.cache
def _path(field: str) -> dsviper.PathConst:
    return dsviper.Path.from_field(field).const()
