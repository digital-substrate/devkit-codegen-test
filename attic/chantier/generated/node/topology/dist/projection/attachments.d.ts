import { AttachmentProxy } from "../_codegen/attachment.js";
import { Mapping } from "../_codegen/container.js";
import * as model_b from "../model_b/data.js";
import * as model_c from "../model_c/data.js";
import * as model_a from "../model_a/data.js";
import { LinkKey, Pair } from "./data.js";
/** Les attachments portés par Projection::LinkKey. */
export declare class Link {
    static readonly mapping: AttachmentProxy<LinkKey, Mapping<model_a.MaterialKey, model_b.MaterialKey>>;
    static readonly marker: AttachmentProxy<LinkKey, model_c.MarkerKey>;
    static readonly pair: AttachmentProxy<LinkKey, Pair>;
}
