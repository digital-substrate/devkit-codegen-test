# Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

"""Tools — le pool, et le même vu d'un client."""

from __future__ import annotations

import typing

import dsviper



class Pool:
    """Le pool, tenu en main — un `dsviper.FunctionPool` déjà obtenu."""

    __slots__ = ("_funcs",)

    NAME = "Tools"
    UUID = dsviper.ValueUUId.create("17e63428-03e1-41d7-ad9d-60c5665bbd66")

    def __init__(self, pool: dsviper.FunctionPool):
        self._funcs = pool.funcs

    def reset(self) -> None:
        self._funcs["reset"]()

    def add(self, a: int, b: int) -> int:
        return self._funcs["add"](a, b)


class Remote:
    """Le même pool, vu d'un client.

    LE SEUL ÉCART AVEC `Pool` EST L'OBTENTION DES FONCTIONS, et il tient en une ligne : d'un
    côté un pool qu'on a en main, de l'autre un service qu'on interroge par son nom. Les
    corps sont identiques -- ce qui traverse le fil est le format, pas l'appel.
    """

    __slots__ = ("_funcs",)

    def __init__(self, service: dsviper.ServiceRemote):
        self._funcs = service.function_pool_funcs(Pool.NAME)

    def is_available(self) -> bool:
        return self._funcs is not None

    def reset(self) -> None:
        self._funcs["reset"]()

    def add(self, a: int, b: int) -> int:
        return self._funcs["add"](a, b)