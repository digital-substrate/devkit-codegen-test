import { AttachmentProxy } from "../_codegen/attachment.js";
import { Mapping, Ordered, Sequence } from "../_codegen/container.js";
import { ThingKey, Bag, Colour, Scalars } from "./data.js";
/** Les attachments portés par Core::ThingKey. */
export declare class Thing {
    static readonly bag: AttachmentProxy<ThingKey, Bag>;
    static readonly colour: AttachmentProxy<ThingKey, Colour>;
    static readonly history: AttachmentProxy<ThingKey, Ordered<Colour>>;
    static readonly palette: AttachmentProxy<ThingKey, Mapping<ThingKey, Colour>>;
    static readonly related: AttachmentProxy<ThingKey, Sequence<ThingKey>>;
    static readonly scalars: AttachmentProxy<ThingKey, Scalars>;
}
