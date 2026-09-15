import { AttachmentProxy } from "../_codegen/attachment.js";
import { Mapping, Ordered, Sequence } from "../_codegen/container.js";
import { AnyConceptKey } from "../_codegen/registry.js";
import * as parts from "../parts/data.js";
import * as core from "../core/data.js";
import { KnotKey, Composites } from "./data.js";
/** Les attachments portés par Core::ThingKey. */
export declare class Core_Thing {
    static readonly mark: AttachmentProxy<core.ThingKey, parts.Colour>;
}
/** Les attachments portés par Woven::KnotKey. */
export declare class Knot {
    static readonly docAnyConceptKey: AttachmentProxy<KnotKey, AnyConceptKey>;
    static readonly docColour: AttachmentProxy<KnotKey, core.Colour>;
    static readonly docComposites: AttachmentProxy<KnotKey, Composites>;
    static readonly docGrade: AttachmentProxy<KnotKey, core.Grade>;
    static readonly docKlubKey: AttachmentProxy<KnotKey, core.KlubKey>;
    static readonly docMapEnum: AttachmentProxy<KnotKey, Mapping<core.Grade, parts.Colour>>;
    static readonly docMapKeys: AttachmentProxy<KnotKey, Mapping<core.ThingKey, parts.ThingKey>>;
    static readonly docOptional: AttachmentProxy<KnotKey, core.ThingKey | undefined>;
    static readonly docOtherColour: AttachmentProxy<KnotKey, parts.Colour>;
    static readonly docSet: AttachmentProxy<KnotKey, Sequence<core.ThingKey>>;
    static readonly docThingKey: AttachmentProxy<KnotKey, core.ThingKey>;
    static readonly docTuple: AttachmentProxy<KnotKey, Sequence<core.Colour | parts.Colour>>;
    static readonly docVariant: AttachmentProxy<KnotKey, core.Colour | parts.Colour>;
    static readonly docVector: AttachmentProxy<KnotKey, Sequence<parts.Colour>>;
    static readonly docXArray: AttachmentProxy<KnotKey, Ordered<core.Colour>>;
}
/** Les attachments portés par Parts::ThingKey. */
export declare class Parts_Thing {
    static readonly mark: AttachmentProxy<parts.ThingKey, core.Colour>;
}
