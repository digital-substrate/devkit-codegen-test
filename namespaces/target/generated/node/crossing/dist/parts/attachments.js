// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar
/** Parts — les attachments que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";
import { AttachmentProxy } from "../_codegen/attachment.js";
import { definitions } from "../index.js";
import { ThingKey, Colour } from "./data.js";
/** Les attachments portés par Parts::ThingKey. */
export class Thing {
    static colour = new AttachmentProxy(dsviper.ValueUUId.create("2db4209c-05b7-fed3-e045-08819f852028"), definitions, ThingKey, Colour);
}
