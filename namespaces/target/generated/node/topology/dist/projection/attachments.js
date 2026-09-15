// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar
/** Projection — les attachments que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";
import { AttachmentProxy } from "../_codegen/attachment.js";
import { definitions } from "../index.js";
import * as model_c from "../model_c/data.js";
import { LinkKey, Pair } from "./data.js";
/** Les attachments portés par Projection::LinkKey. */
export class Link {
    static mapping = new AttachmentProxy(dsviper.ValueUUId.create("e44613ce-ada0-c8a2-a9d1-20b04ae443c0"), definitions, LinkKey, undefined);
    static marker = new AttachmentProxy(dsviper.ValueUUId.create("5b7db20d-fe60-2c96-206c-ec6686b46822"), definitions, LinkKey, model_c.MarkerKey);
    static pair = new AttachmentProxy(dsviper.ValueUUId.create("2b04b57b-9677-e209-6000-91c489d81323"), definitions, LinkKey, Pair);
}
