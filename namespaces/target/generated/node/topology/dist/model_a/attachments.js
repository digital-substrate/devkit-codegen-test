// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar
/** ModelA — les attachments que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";
import { AttachmentProxy } from "../_codegen/attachment.js";
import { definitions } from "../index.js";
import { MaterialKey, Colour } from "./data.js";
/** Les attachments portés par ModelA::MaterialKey. */
export class Material {
    static colour = new AttachmentProxy(dsviper.ValueUUId.create("faf658ea-5586-890a-0c4a-5cd2c9209b28"), definitions, MaterialKey, Colour);
}
