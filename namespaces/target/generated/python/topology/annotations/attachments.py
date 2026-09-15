# Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

"""Annotations — les attachments que ce namespace déclare."""

from __future__ import annotations

import dsviper

from .. import definitions
from .._codegen import AnyConceptKey, AttachmentProxy
from .. import model_b
from .. import model_a
from .data import *


class ModelA_Material:
    """Les attachments portés par ModelA::MaterialKey."""

    note = AttachmentProxy(
        dsviper.ValueUUId.create("a9fc61a4-cc9b-1867-2997-e3e58e3ee6c3"),
        definitions, model_a.MaterialKey, None)


model_a_material = ModelA_Material()

class ModelB_Material:
    """Les attachments portés par ModelB::MaterialKey."""

    note = AttachmentProxy(
        dsviper.ValueUUId.create("a032a823-77a9-3b78-6d34-c83670697fd9"),
        definitions, model_b.MaterialKey, None)


model_b_material = ModelB_Material()