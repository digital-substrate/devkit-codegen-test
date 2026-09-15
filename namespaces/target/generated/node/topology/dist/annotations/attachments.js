// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar
/** Annotations — les attachments que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";
import { AttachmentProxy } from "../_codegen/attachment.js";
import { definitions } from "../index.js";
import * as model_b from "../model_b/data.js";
import * as model_a from "../model_a/data.js";
/** Les attachments portés par ModelA::MaterialKey. */
export class ModelA_Material {
    static note = new AttachmentProxy(dsviper.ValueUUId.create("a9fc61a4-cc9b-1867-2997-e3e58e3ee6c3"), definitions, model_a.MaterialKey, undefined);
}
/** Les attachments portés par ModelB::MaterialKey. */
export class ModelB_Material {
    static note = new AttachmentProxy(dsviper.ValueUUId.create("a032a823-77a9-3b78-6d34-c83670697fd9"), definitions, model_b.MaterialKey, undefined);
}
