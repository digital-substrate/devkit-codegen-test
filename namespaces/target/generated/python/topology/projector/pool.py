# Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

"""Projector — le pool, et le même vu d'un client."""

from __future__ import annotations

import typing

import dsviper

from .._container import Mapping, Ordered, Sequence
from .._proxy import AnyConceptKey

from .. import model_a
from .. import model_b

class Pool:
    """Le pool, tenu en main — un `dsviper.FunctionPool` déjà obtenu."""

    __slots__ = ("_funcs",)

    NAME = "Projector"
    UUID = dsviper.ValueUUId.create("3f513cf9-c9b9-4c57-8ace-ac9a644be74c")

    def __init__(self, pool: dsviper.FunctionPool):
        self._funcs = pool.funcs

    def link(self, a: model_a.MaterialKey, b: model_b.MaterialKey) -> None:
        self._funcs["link"](a._unwrap(), b._unwrap())


class Remote:
    """Le même pool, vu d'un client.

    LE SEUL ÉCART AVEC `Pool` EST L'OBTENTION DES FONCTIONS, et il tient en une ligne : d'un
    côté un pool qu'on a en main, de l'autre un service qu'on interroge par son nom. Les
    corps sont identiques -- ce qui traverse le fil est le format, pas l'appel.
    """

    __slots__ = ("_queried",)

    def __init__(self, service: dsviper.ServiceRemote):
        self._queried = service.function_pool_funcs(Pool.NAME)

    def is_available(self) -> bool:
        return self._queried is not None

    @property
    def _funcs(self):
        """Les fonctions, ou une erreur qui dit laquelle manque.

        UN SERVICE PEUT NE PAS PORTER CE POOL, et `is_available()` est là pour le demander.
        Appeler sans avoir demandé donnait « NoneType n'est pas indexable », qui ne nomme ni
        le pool ni le service ; un vérificateur de types l'a signalé avant qu'un appelant ne
        le rencontre.
        """
        if self._queried is None:
            raise RuntimeError(f"le service ne porte pas le pool {Pool.NAME}")
        return self._queried

    def link(self, a: model_a.MaterialKey, b: model_b.MaterialKey) -> None:
        self._funcs["link"](a._unwrap(), b._unwrap())