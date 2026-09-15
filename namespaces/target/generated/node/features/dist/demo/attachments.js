// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/features/Features.dsm.json by kibo-2.0.0.jar
/** Demo — les attachments que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";
import { AttachmentProxy } from "../_codegen/attachment.js";
import { AnyConceptKey } from "../_codegen/registry.js";
import { definitions } from "../index.js";
import { ConceptAKey, ConceptBKey, ConceptCoverageKey, ConceptCKey, KlubKey, EnumerationE, StructureT, StructureU, StructureV, StructureW } from "./data.js";
/** Les attachments portés par ::Features::AnyConceptKey. */
export class AnyConcept {
    static propertiesAnyConceptAny = new AttachmentProxy(dsviper.ValueUUId.create("8de8e47b-58e8-5699-59a7-5a3193aef7f1"), definitions, AnyConceptKey, undefined);
}
/** Les attachments portés par Demo::ConceptAKey. */
export class ConceptA {
    static properties = new AttachmentProxy(dsviper.ValueUUId.create("3b79131f-a619-5b33-66ab-3b78ca749cd0"), definitions, ConceptAKey, StructureV);
    static propertiesInt8 = new AttachmentProxy(dsviper.ValueUUId.create("58ce283d-b8eb-1f01-3841-854fccd54fd7"), definitions, ConceptAKey, undefined);
    static propertiesMapInt8String = new AttachmentProxy(dsviper.ValueUUId.create("0eb140e3-5247-d7ad-649f-5fa124359ee2"), definitions, ConceptAKey, undefined);
    static propertiesSeInt8 = new AttachmentProxy(dsviper.ValueUUId.create("ad45f798-b25a-0421-c523-713ff624383e"), definitions, ConceptAKey, undefined);
    static propertiesXArray = new AttachmentProxy(dsviper.ValueUUId.create("ff9d7eda-5ad0-d217-d910-7d2adfad208f"), definitions, ConceptAKey, undefined);
}
/** Les attachments portés par Demo::ConceptBKey. */
export class ConceptB {
    static propertiesB = new AttachmentProxy(dsviper.ValueUUId.create("c117fd64-7b82-f4ab-164c-efb528a408bc"), definitions, ConceptBKey, StructureT);
}
/** Les attachments portés par Demo::ConceptCKey. */
export class ConceptC {
    static propertiesC = new AttachmentProxy(dsviper.ValueUUId.create("7f6d8d89-d32a-3214-ed11-3f23b7faaf1e"), definitions, ConceptCKey, StructureU);
}
/** Les attachments portés par Demo::ConceptCoverageKey. */
export class ConceptCoverage {
    static docAny = new AttachmentProxy(dsviper.ValueUUId.create("20a71745-30fb-4f1b-2245-d331c323bbba"), definitions, ConceptCoverageKey, undefined);
    static docAnyConceptKey = new AttachmentProxy(dsviper.ValueUUId.create("ab54b0a8-596a-40fc-6ef1-f1d2eba54f5c"), definitions, ConceptCoverageKey, undefined);
    static docBlob = new AttachmentProxy(dsviper.ValueUUId.create("e80aaf93-0656-f497-1372-20158ecea8fb"), definitions, ConceptCoverageKey, undefined);
    static docBlobId = new AttachmentProxy(dsviper.ValueUUId.create("8dce567e-111b-bddf-7448-1abc8261ac90"), definitions, ConceptCoverageKey, undefined);
    static docBool = new AttachmentProxy(dsviper.ValueUUId.create("de0efd5b-90bb-216f-03f8-cbf32245a423"), definitions, ConceptCoverageKey, undefined);
    static docClubKey = new AttachmentProxy(dsviper.ValueUUId.create("6c8c6c4a-f99b-1737-f3e9-b60da806f18b"), definitions, ConceptCoverageKey, KlubKey);
    static docCommitId = new AttachmentProxy(dsviper.ValueUUId.create("8bc4885f-0e59-2156-6534-f71674e16a62"), definitions, ConceptCoverageKey, undefined);
    static docConceptKey = new AttachmentProxy(dsviper.ValueUUId.create("e46092d8-19d2-786f-8ec2-ffe4eb96a2b0"), definitions, ConceptCoverageKey, ConceptAKey);
    static docConceptKeyB = new AttachmentProxy(dsviper.ValueUUId.create("72eb0057-8f6c-7e05-f68e-36ec9bbdc0e6"), definitions, ConceptCoverageKey, ConceptBKey);
    static docDouble = new AttachmentProxy(dsviper.ValueUUId.create("ddcc4ebf-809b-1186-a81d-e04887a55c28"), definitions, ConceptCoverageKey, undefined);
    static docEnumeration = new AttachmentProxy(dsviper.ValueUUId.create("297e6910-d347-da0c-3dd6-563406dc742f"), definitions, ConceptCoverageKey, EnumerationE);
    static docFloat = new AttachmentProxy(dsviper.ValueUUId.create("59dc723c-e718-31bd-93e1-fce13b975469"), definitions, ConceptCoverageKey, undefined);
    static docInt16 = new AttachmentProxy(dsviper.ValueUUId.create("138e62f6-c93a-11e6-8cbb-582c7de65a27"), definitions, ConceptCoverageKey, undefined);
    static docInt32 = new AttachmentProxy(dsviper.ValueUUId.create("83d4d1bf-497b-e2ad-4efc-09509903ef47"), definitions, ConceptCoverageKey, undefined);
    static docInt64 = new AttachmentProxy(dsviper.ValueUUId.create("bb3c8bde-0fd6-0535-4a63-361ba70dbe9c"), definitions, ConceptCoverageKey, undefined);
    static docInt8 = new AttachmentProxy(dsviper.ValueUUId.create("0eb18fdd-6c1b-1584-34c8-f8356d4bc05d"), definitions, ConceptCoverageKey, undefined);
    static docMap = new AttachmentProxy(dsviper.ValueUUId.create("d06b8489-8bd1-a8ff-4e64-d95c5771208f"), definitions, ConceptCoverageKey, undefined);
    static docMat = new AttachmentProxy(dsviper.ValueUUId.create("43e79483-eead-0925-cedd-78a45ce47d98"), definitions, ConceptCoverageKey, undefined);
    static docOptional = new AttachmentProxy(dsviper.ValueUUId.create("92e537a9-7a80-e98f-6e44-8a463cf9a970"), definitions, ConceptCoverageKey, undefined);
    static docSet = new AttachmentProxy(dsviper.ValueUUId.create("7793f2b3-58ab-a3a3-bd44-04cf41b58cdc"), definitions, ConceptCoverageKey, undefined);
    static docString = new AttachmentProxy(dsviper.ValueUUId.create("9403f10d-288e-00cc-1169-f9a544777dbc"), definitions, ConceptCoverageKey, undefined);
    static docStructureSingleField = new AttachmentProxy(dsviper.ValueUUId.create("19ebae3f-d189-04a2-dea3-deb80ece9ff8"), definitions, ConceptCoverageKey, StructureW);
    static docTuple = new AttachmentProxy(dsviper.ValueUUId.create("d51d4c9f-f9cd-fe62-4417-28021df7961c"), definitions, ConceptCoverageKey, undefined);
    static docUInt16 = new AttachmentProxy(dsviper.ValueUUId.create("3ae2904f-b0ed-d9e8-448a-fbd6d80be212"), definitions, ConceptCoverageKey, undefined);
    static docUInt32 = new AttachmentProxy(dsviper.ValueUUId.create("85ced0f5-1127-8750-a18e-3ecbfbe4813a"), definitions, ConceptCoverageKey, undefined);
    static docUInt64 = new AttachmentProxy(dsviper.ValueUUId.create("00a3fbe9-15b1-8e1f-fc42-c01d845ccc9a"), definitions, ConceptCoverageKey, undefined);
    static docUInt8 = new AttachmentProxy(dsviper.ValueUUId.create("5ac282e6-15c4-0a8c-bab9-b14ac6a7f9ed"), definitions, ConceptCoverageKey, undefined);
    static docUUId = new AttachmentProxy(dsviper.ValueUUId.create("a79058d8-5ee7-303d-1d19-50f01983a35b"), definitions, ConceptCoverageKey, undefined);
    static docVariant = new AttachmentProxy(dsviper.ValueUUId.create("b7a81faa-fea8-a2cb-760b-edf353f16c63"), definitions, ConceptCoverageKey, undefined);
    static docVec = new AttachmentProxy(dsviper.ValueUUId.create("73d224c0-d38f-4b5a-d225-bad481cec150"), definitions, ConceptCoverageKey, undefined);
    static docVector = new AttachmentProxy(dsviper.ValueUUId.create("ebb21187-7004-e7fa-23e6-690803352742"), definitions, ConceptCoverageKey, undefined);
    static docXArray = new AttachmentProxy(dsviper.ValueUUId.create("d45a1e55-9fc4-037e-5ce7-856093a638be"), definitions, ConceptCoverageKey, undefined);
}
/** Les attachments portés par Demo::KlubKey. */
export class Klub {
    static propertiesD = new AttachmentProxy(dsviper.ValueUUId.create("f7a9f794-cedc-a3ff-9530-63f86e932850"), definitions, KlubKey, StructureV);
}
