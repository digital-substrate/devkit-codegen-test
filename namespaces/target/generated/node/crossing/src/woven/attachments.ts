// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

/** Woven — les attachments que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";

import { AttachmentProxy } from "../_codegen/attachment.js";
import { Mapping, Ordered, Sequence } from "../_codegen/container.js";
import { AnyConceptKey } from "../_codegen/registry.js";
import { definitions } from "../index.js";
import * as parts from "../parts/data.js";
import * as core from "../core/data.js";
import { KnotKey, DerivedKey, WeaveKey, Composites, Entities, Nested } from "./data.js";

/** Les attachments portés par Core::ThingKey. */
export class Core_Thing {
    static readonly mark = new AttachmentProxy<core.ThingKey, parts.Colour>(
        dsviper.ValueUUId.create("29b28189-1b55-86c3-5e2c-59344e124aa2"),
        definitions, core.ThingKey, parts.Colour);
}

/** Les attachments portés par Woven::KnotKey. */
export class Knot {
    static readonly docAnyConceptKey = new AttachmentProxy<KnotKey, AnyConceptKey>(
        dsviper.ValueUUId.create("4a9fcd14-9b14-51cd-1865-cb55edb9021e"),
        definitions, KnotKey, undefined);

    static readonly docColour = new AttachmentProxy<KnotKey, core.Colour>(
        dsviper.ValueUUId.create("b6352063-8d70-8a69-963c-d1441b676370"),
        definitions, KnotKey, core.Colour);

    static readonly docComposites = new AttachmentProxy<KnotKey, Composites>(
        dsviper.ValueUUId.create("d81beea7-b5ce-6808-94fb-4487e4ee79d6"),
        definitions, KnotKey, Composites);

    static readonly docGrade = new AttachmentProxy<KnotKey, core.Grade>(
        dsviper.ValueUUId.create("9ff5bafb-4555-2539-1cf8-28794071e3f9"),
        definitions, KnotKey, core.Grade);

    static readonly docKlubKey = new AttachmentProxy<KnotKey, core.KlubKey>(
        dsviper.ValueUUId.create("9e24eff7-c018-1b1f-df8a-ba06bf0393c7"),
        definitions, KnotKey, core.KlubKey);

    static readonly docMapEnum = new AttachmentProxy<KnotKey, Mapping<core.Grade, parts.Colour>>(
        dsviper.ValueUUId.create("bb379295-5f29-328c-7c5b-7c3073b675fb"),
        definitions, KnotKey, undefined);

    static readonly docMapKeys = new AttachmentProxy<KnotKey, Mapping<core.ThingKey, parts.ThingKey>>(
        dsviper.ValueUUId.create("ca705caa-f5bf-b94f-5f52-cf0745c338be"),
        definitions, KnotKey, undefined);

    static readonly docOptional = new AttachmentProxy<KnotKey, core.ThingKey | undefined>(
        dsviper.ValueUUId.create("7a6d4307-8841-d296-cbea-938d5bb346cd"),
        definitions, KnotKey, undefined);

    static readonly docOtherColour = new AttachmentProxy<KnotKey, parts.Colour>(
        dsviper.ValueUUId.create("791ea025-2d11-6f01-fc7d-749a85470a7c"),
        definitions, KnotKey, parts.Colour);

    static readonly docSet = new AttachmentProxy<KnotKey, Sequence<core.ThingKey>>(
        dsviper.ValueUUId.create("eb7bdd6d-a772-3d04-bc8c-077f3ed44532"),
        definitions, KnotKey, undefined);

    static readonly docThingKey = new AttachmentProxy<KnotKey, core.ThingKey>(
        dsviper.ValueUUId.create("831d85fc-bf2f-16af-4cd7-bd71cde7cf3c"),
        definitions, KnotKey, core.ThingKey);

    static readonly docTuple = new AttachmentProxy<KnotKey, Sequence<core.Colour | parts.Colour>>(
        dsviper.ValueUUId.create("80700838-18f7-ae9f-9f1c-2d232720258e"),
        definitions, KnotKey, undefined);

    static readonly docVariant = new AttachmentProxy<KnotKey, core.Colour | parts.Colour>(
        dsviper.ValueUUId.create("a30edeff-00f1-96fd-7ee4-8a4bb2e51849"),
        definitions, KnotKey, undefined);

    static readonly docVector = new AttachmentProxy<KnotKey, Sequence<parts.Colour>>(
        dsviper.ValueUUId.create("b139c73e-34f5-265b-1052-23a0685f66a9"),
        definitions, KnotKey, undefined);

    static readonly docXArray = new AttachmentProxy<KnotKey, Ordered<core.Colour>>(
        dsviper.ValueUUId.create("70c9c550-d044-dd9a-e924-f988a02bcb6a"),
        definitions, KnotKey, undefined);
}

/** Les attachments portés par Parts::ThingKey. */
export class Parts_Thing {
    static readonly mark = new AttachmentProxy<parts.ThingKey, core.Colour>(
        dsviper.ValueUUId.create("f3fbea66-985b-da2b-f523-016cf94b43cc"),
        definitions, parts.ThingKey, core.Colour);
}