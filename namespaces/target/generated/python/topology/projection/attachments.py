# Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

"""Projection — les attachments que ce namespace déclare."""

from __future__ import annotations

import dsviper

from .. import definitions
from .._codegen import AnyConceptKey, AttachmentProxy
from .. import model_b
from .. import model_c
from .. import model_a
from .data import *


class Link:
    """Les attachments portés par Projection::LinkKey."""

    mapping = AttachmentProxy(
        dsviper.ValueUUId.create("e44613ce-ada0-c8a2-a9d1-20b04ae443c0"),
        definitions, LinkKey, None)

    marker = AttachmentProxy(
        dsviper.ValueUUId.create("5b7db20d-fe60-2c96-206c-ec6686b46822"),
        definitions, LinkKey, model_c.MarkerKey)

    pair = AttachmentProxy(
        dsviper.ValueUUId.create("2b04b57b-9677-e209-6000-91c489d81323"),
        definitions, LinkKey, Pair)


link = Link()