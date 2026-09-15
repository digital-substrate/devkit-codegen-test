# Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/service/Service.dsm.json by kibo-2.0.0.jar

"""PlayerModel — le pool, et le même vu d'un client."""

from __future__ import annotations

import typing

import dsviper

from .. import demo

class Pool:
    """Le pool d'attachments, tenu en main."""

    __slots__ = ("_funcs",)

    NAME = "PlayerModel"
    UUID = dsviper.ValueUUId.create("d75a8a57-f0ad-4a44-84f7-1ea409d4bd36")

    def __init__(self, pool: dsviper.AttachmentFunctionPool):
        self._funcs = pool.funcs

    def create(self, attachment_mutating: dsviper.AttachmentMutating, nickname: str, level: demo.Level) -> demo.PlayerKey:
        return demo.PlayerKey._wrap(self._funcs["create"](attachment_mutating, nickname, level._unwrap()))

    def has_player(self, attachment_getting: dsviper.AttachmentGetting, nickname: str) -> typing.Any:
        return self._funcs["has_player"](attachment_getting, nickname)


class Remote:
    """Le même pool, vu d'un client."""

    __slots__ = ("_funcs",)

    def __init__(self, service: dsviper.ServiceRemote):
        self._funcs = service.attachment_function_pool_funcs(Pool.NAME)

    def is_available(self) -> bool:
        return self._funcs is not None

    def create(self, attachment_mutating: dsviper.AttachmentMutating, nickname: str, level: demo.Level) -> demo.PlayerKey:
        return demo.PlayerKey._wrap(self._funcs["create"](attachment_mutating, nickname, level._unwrap()))

    def has_player(self, attachment_getting: dsviper.AttachmentGetting, nickname: str) -> typing.Any:
        return self._funcs["has_player"](attachment_getting, nickname)