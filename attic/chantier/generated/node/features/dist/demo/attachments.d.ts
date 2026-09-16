/** Demo — les attachments que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";
import { AttachmentProxy } from "../_codegen/attachment.js";
import { Mapping, Ordered, Sequence } from "../_codegen/container.js";
import { AnyConceptKey } from "../_codegen/registry.js";
import { ConceptAKey, ConceptBKey, ConceptCoverageKey, ConceptCKey, KlubKey, EnumerationE, StructureT, StructureU, StructureV, StructureW } from "./data.js";
/** Les attachments portés par ::Features::AnyConceptKey. */
export declare class AnyConcept {
    static readonly propertiesAnyConceptAny: AttachmentProxy<AnyConceptKey, unknown>;
}
/** Les attachments portés par Demo::ConceptAKey. */
export declare class ConceptA {
    static readonly properties: AttachmentProxy<ConceptAKey, StructureV>;
    static readonly propertiesInt8: AttachmentProxy<ConceptAKey, number>;
    static readonly propertiesMapInt8String: AttachmentProxy<ConceptAKey, Mapping<number, string>>;
    static readonly propertiesSeInt8: AttachmentProxy<ConceptAKey, Sequence<number>>;
    static readonly propertiesXArray: AttachmentProxy<ConceptAKey, Ordered<number>>;
}
/** Les attachments portés par Demo::ConceptBKey. */
export declare class ConceptB {
    static readonly propertiesB: AttachmentProxy<ConceptBKey, StructureT>;
}
/** Les attachments portés par Demo::ConceptCKey. */
export declare class ConceptC {
    static readonly propertiesC: AttachmentProxy<ConceptCKey, StructureU>;
}
/** Les attachments portés par Demo::ConceptCoverageKey. */
export declare class ConceptCoverage {
    static readonly docAny: AttachmentProxy<ConceptCoverageKey, unknown>;
    static readonly docAnyConceptKey: AttachmentProxy<ConceptCoverageKey, AnyConceptKey>;
    static readonly docBlob: AttachmentProxy<ConceptCoverageKey, dsviper.ValueBlob>;
    static readonly docBlobId: AttachmentProxy<ConceptCoverageKey, dsviper.ValueBlobId>;
    static readonly docBool: AttachmentProxy<ConceptCoverageKey, boolean>;
    static readonly docClubKey: AttachmentProxy<ConceptCoverageKey, KlubKey>;
    static readonly docCommitId: AttachmentProxy<ConceptCoverageKey, dsviper.ValueCommitId>;
    static readonly docConceptKey: AttachmentProxy<ConceptCoverageKey, ConceptAKey>;
    static readonly docConceptKeyB: AttachmentProxy<ConceptCoverageKey, ConceptBKey>;
    static readonly docDouble: AttachmentProxy<ConceptCoverageKey, number>;
    static readonly docEnumeration: AttachmentProxy<ConceptCoverageKey, EnumerationE>;
    static readonly docFloat: AttachmentProxy<ConceptCoverageKey, number>;
    static readonly docInt16: AttachmentProxy<ConceptCoverageKey, number>;
    static readonly docInt32: AttachmentProxy<ConceptCoverageKey, number>;
    static readonly docInt64: AttachmentProxy<ConceptCoverageKey, bigint>;
    static readonly docInt8: AttachmentProxy<ConceptCoverageKey, number>;
    static readonly docMap: AttachmentProxy<ConceptCoverageKey, Mapping<number, string>>;
    static readonly docMat: AttachmentProxy<ConceptCoverageKey, Sequence<Sequence<number>>>;
    static readonly docOptional: AttachmentProxy<ConceptCoverageKey, number | undefined>;
    static readonly docSet: AttachmentProxy<ConceptCoverageKey, Sequence<number>>;
    static readonly docString: AttachmentProxy<ConceptCoverageKey, string>;
    static readonly docStructureSingleField: AttachmentProxy<ConceptCoverageKey, StructureW>;
    static readonly docTuple: AttachmentProxy<ConceptCoverageKey, Sequence<string | number>>;
    static readonly docUInt16: AttachmentProxy<ConceptCoverageKey, number>;
    static readonly docUInt32: AttachmentProxy<ConceptCoverageKey, number>;
    static readonly docUInt64: AttachmentProxy<ConceptCoverageKey, bigint>;
    static readonly docUInt8: AttachmentProxy<ConceptCoverageKey, number>;
    static readonly docUUId: AttachmentProxy<ConceptCoverageKey, dsviper.ValueUUId>;
    static readonly docVariant: AttachmentProxy<ConceptCoverageKey, string | number>;
    static readonly docVec: AttachmentProxy<ConceptCoverageKey, Sequence<number>>;
    static readonly docVector: AttachmentProxy<ConceptCoverageKey, Sequence<number>>;
    static readonly docXArray: AttachmentProxy<ConceptCoverageKey, Ordered<number>>;
}
/** Les attachments portés par Demo::KlubKey. */
export declare class Klub {
    static readonly propertiesD: AttachmentProxy<KlubKey, StructureV>;
}
