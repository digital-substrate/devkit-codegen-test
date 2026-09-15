# Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

"""ModelA — les attachments que ce namespace déclare."""

from __future__ import annotations

import dsviper

from .. import definitions
from .._codegen import AnyConceptKey, AttachmentProxy
from .data import *


class Material:
    """Les attachments portés par ModelA::MaterialKey."""

    colour = AttachmentProxy(
        dsviper.ValueUUId.create("faf658ea-5586-890a-0c4a-5cd2c9209b28"),
        definitions, MaterialKey, Colour)


material = Material()