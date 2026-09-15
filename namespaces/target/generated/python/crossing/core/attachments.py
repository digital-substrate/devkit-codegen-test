# Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

"""Core — les attachments que ce namespace déclare."""

from __future__ import annotations

import dsviper

from .. import definitions
from .._attachment import Attachment
from .._proxy import AnyConceptKey
from .data import *


class Thing:
    """Les attachments portés par Core::ThingKey."""

    bag = Attachment(
        dsviper.ValueUUId.create("e8422ebb-3f90-3554-115a-308eca6b75d5"),
        definitions, ThingKey, Bag)


thing = Thing()

class Thing:
    """Les attachments portés par Core::ThingKey."""

    colour = Attachment(
        dsviper.ValueUUId.create("1c970e1f-b2a9-80d7-f588-02c610b5f114"),
        definitions, ThingKey, Colour)


thing = Thing()

class Thing:
    """Les attachments portés par Core::ThingKey."""

    history = Attachment(
        dsviper.ValueUUId.create("44dff56f-9628-52e8-8b6d-74fcebd89beb"),
        definitions, ThingKey, None)


thing = Thing()

class Thing:
    """Les attachments portés par Core::ThingKey."""

    palette = Attachment(
        dsviper.ValueUUId.create("07555083-c220-c293-7992-0b2d535a315e"),
        definitions, ThingKey, None)


thing = Thing()

class Thing:
    """Les attachments portés par Core::ThingKey."""

    related = Attachment(
        dsviper.ValueUUId.create("78dddddb-13c8-25ce-eb7a-83d42c72c86c"),
        definitions, ThingKey, None)


thing = Thing()

class Thing:
    """Les attachments portés par Core::ThingKey."""

    scalars = Attachment(
        dsviper.ValueUUId.create("11386338-c74c-53da-8472-413ecd1a0cce"),
        definitions, ThingKey, Scalars)


thing = Thing()