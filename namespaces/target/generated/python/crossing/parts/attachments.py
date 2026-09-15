# Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

"""Parts — les attachments que ce namespace déclare."""

from __future__ import annotations

import dsviper

from .. import definitions
from .._attachment import AttachmentProxy
from .._proxy import AnyConceptKey
from .data import *


class Thing:
    """Les attachments portés par Parts::ThingKey."""

    colour = AttachmentProxy(
        dsviper.ValueUUId.create("2db4209c-05b7-fed3-e045-08819f852028"),
        definitions, ThingKey, Colour)


thing = Thing()