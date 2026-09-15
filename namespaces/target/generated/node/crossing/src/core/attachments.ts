// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

/** Core — les attachments que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";

import { AttachmentProxy } from "../_codegen/attachment.js";
import { Mapping, Ordered, Sequence } from "../_codegen/container.js";
import { AnyConceptKey } from "../_codegen/registry.js";
import { definitions } from "../index.js";
import { OtherKey, ThingKey, SubThingKey, KlubKey, Grade, Bag, Colour, Defaults, Scalars, Single } from "./data.js";

/** Les attachments portés par Core::ThingKey. */
export class Thing {
    static readonly bag = new AttachmentProxy<ThingKey, Bag>(
        dsviper.ValueUUId.create("e8422ebb-3f90-3554-115a-308eca6b75d5"),
        definitions, ThingKey, Bag);

    static readonly colour = new AttachmentProxy<ThingKey, Colour>(
        dsviper.ValueUUId.create("1c970e1f-b2a9-80d7-f588-02c610b5f114"),
        definitions, ThingKey, Colour);

    static readonly history = new AttachmentProxy<ThingKey, Ordered<Colour>>(
        dsviper.ValueUUId.create("44dff56f-9628-52e8-8b6d-74fcebd89beb"),
        definitions, ThingKey, undefined);

    static readonly palette = new AttachmentProxy<ThingKey, Mapping<ThingKey, Colour>>(
        dsviper.ValueUUId.create("07555083-c220-c293-7992-0b2d535a315e"),
        definitions, ThingKey, undefined);

    static readonly related = new AttachmentProxy<ThingKey, Sequence<ThingKey>>(
        dsviper.ValueUUId.create("78dddddb-13c8-25ce-eb7a-83d42c72c86c"),
        definitions, ThingKey, undefined);

    static readonly scalars = new AttachmentProxy<ThingKey, Scalars>(
        dsviper.ValueUUId.create("11386338-c74c-53da-8472-413ecd1a0cce"),
        definitions, ThingKey, Scalars);
}