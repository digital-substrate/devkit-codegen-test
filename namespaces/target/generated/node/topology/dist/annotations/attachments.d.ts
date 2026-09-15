import { AttachmentProxy } from "../_codegen/attachment.js";
import * as model_b from "../model_b/data.js";
import * as model_a from "../model_a/data.js";
/** Les attachments portés par ModelA::MaterialKey. */
export declare class ModelA_Material {
    static readonly note: AttachmentProxy<model_a.MaterialKey, string>;
}
/** Les attachments portés par ModelB::MaterialKey. */
export declare class ModelB_Material {
    static readonly note: AttachmentProxy<model_b.MaterialKey, string>;
}
