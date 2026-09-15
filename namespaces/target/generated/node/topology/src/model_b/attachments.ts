// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

/** ModelB — les attachments que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";

import { AttachmentProxy } from "../_codegen/attachment.js";
import { Mapping, Ordered, Sequence } from "../_codegen/container.js";
import { AnyConceptKey } from "../_codegen/registry.js";
import { definitions } from "../index.js";
import { MaterialKey, Colour } from "./data.js";

/** Les attachments portés par ModelB::MaterialKey. */
export class Material {
    static readonly colour = new AttachmentProxy<MaterialKey, Colour>(
        dsviper.ValueUUId.create("09eeb3f7-b0a6-9ad9-a80f-d2a85070ec08"),
        definitions, MaterialKey, Colour);
}