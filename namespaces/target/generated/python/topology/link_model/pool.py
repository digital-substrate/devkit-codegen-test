# Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

"""LinkModel — le pool, et le même vu d'un client."""

from __future__ import annotations

import typing

import dsviper

from .._container import Mapping, Ordered, Sequence
from .._proxy import AnyConceptKey

from .. import projection

class Pool:
    """Le pool d'attachments, tenu en main."""

    __slots__ = ("_funcs",)

    NAME = "LinkModel"
    UUID = dsviper.ValueUUId.create("a51019a2-790e-49ac-a164-6b150e0976d6")

    def __init__(self, pool: dsviper.AttachmentFunctionPool):
        self._funcs = pool.funcs

    def clear(self, attachment_mutating: dsviper.AttachmentMutating, link_key: projection.LinkKey) -> None:
        self._funcs["clear"](attachment_mutating, link_key._unwrap())


class Remote:
    """Le même pool, vu d'un client."""

    __slots__ = ("_queried",)

    def __init__(self, service: dsviper.ServiceRemote):
        self._queried = service.attachment_function_pool_funcs(Pool.NAME)

    def is_available(self) -> bool:
        return self._queried is not None

    @property
    def _funcs(self):
        """Les fonctions, ou une erreur qui dit laquelle manque."""
        if self._queried is None:
            raise RuntimeError(f"le service ne porte pas le pool {Pool.NAME}")
        return self._queried

    def clear(self, attachment_mutating: dsviper.AttachmentMutating, link_key: projection.LinkKey) -> None:
        self._funcs["clear"](attachment_mutating, link_key._unwrap())