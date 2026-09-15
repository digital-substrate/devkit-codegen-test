# Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/service/Service.dsm.json by kibo-2.0.0.jar

"""Demo — les attachments que ce namespace déclare."""

from __future__ import annotations

import dsviper

from .. import definitions
from .._attachment import Attachment
from .._proxy import AnyConceptKey
from .data import *


class Player:
    """Les attachments portés par Demo::PlayerKey."""

    property = Attachment(
        dsviper.ValueUUId.create("5f39a4c7-fa83-1290-432c-330fc392a39b"),
        definitions, PlayerKey, PlayerProperty)


player = Player()