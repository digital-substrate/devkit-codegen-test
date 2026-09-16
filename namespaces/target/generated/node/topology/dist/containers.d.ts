/** Topology — les conteneurs que le modèle mentionne, nommés et constructibles. */
import dsviper from "@digitalsubstrate/dsviper";
export declare const Optional_AnyConceptKey: {
    new (value?: unknown): import("./_codegen/container.js").Optional<unknown>;
    type(): dsviper.Type;
    decode(blob: dsviper.ValueBlob): import("./_codegen/container.js").Optional<unknown>;
};
export declare const Optional_ModelA_Colour: {
    new (value?: unknown): import("./_codegen/container.js").Optional<unknown>;
    type(): dsviper.Type;
    decode(blob: dsviper.ValueBlob): import("./_codegen/container.js").Optional<unknown>;
};
export declare const Optional_ModelA_MaterialKey: {
    new (value?: unknown): import("./_codegen/container.js").Optional<unknown>;
    type(): dsviper.Type;
    decode(blob: dsviper.ValueBlob): import("./_codegen/container.js").Optional<unknown>;
};
export declare const Optional_ModelB_Colour: {
    new (value?: unknown): import("./_codegen/container.js").Optional<unknown>;
    type(): dsviper.Type;
    decode(blob: dsviper.ValueBlob): import("./_codegen/container.js").Optional<unknown>;
};
export declare const Optional_ModelB_MaterialKey: {
    new (value?: unknown): import("./_codegen/container.js").Optional<unknown>;
    type(): dsviper.Type;
    decode(blob: dsviper.ValueBlob): import("./_codegen/container.js").Optional<unknown>;
};
export declare const Optional_ModelC_MarkerKey: {
    new (value?: unknown): import("./_codegen/container.js").Optional<unknown>;
    type(): dsviper.Type;
    decode(blob: dsviper.ValueBlob): import("./_codegen/container.js").Optional<unknown>;
};
export declare const Optional_Projection_DerivedMaterialKey: {
    new (value?: unknown): import("./_codegen/container.js").Optional<unknown>;
    type(): dsviper.Type;
    decode(blob: dsviper.ValueBlob): import("./_codegen/container.js").Optional<unknown>;
};
export declare const Optional_Projection_LinkKey: {
    new (value?: unknown): import("./_codegen/container.js").Optional<unknown>;
    type(): dsviper.Type;
    decode(blob: dsviper.ValueBlob): import("./_codegen/container.js").Optional<unknown>;
};
export declare const Optional_Projection_Pair: {
    new (value?: unknown): import("./_codegen/container.js").Optional<unknown>;
    type(): dsviper.Type;
    decode(blob: dsviper.ValueBlob): import("./_codegen/container.js").Optional<unknown>;
};
export declare const Optional_Map_ModelA_MaterialKey_to_ModelB_MaterialKey: {
    new (value?: unknown): import("./_codegen/container.js").Optional<unknown>;
    type(): dsviper.Type;
    decode(blob: dsviper.ValueBlob): import("./_codegen/container.js").Optional<unknown>;
};
export declare const Optional_string: {
    new (value?: unknown): import("./_codegen/container.js").Optional<unknown>;
    type(): dsviper.Type;
    decode(blob: dsviper.ValueBlob): import("./_codegen/container.js").Optional<unknown>;
};
export declare const Set_ModelA_MaterialKey: {
    new (value?: unknown): import("./_codegen/container.js").Sequence<unknown>;
    type(): dsviper.Type;
    decode(blob: dsviper.ValueBlob): import("./_codegen/container.js").Sequence<unknown>;
};
export declare const Set_ModelB_MaterialKey: {
    new (value?: unknown): import("./_codegen/container.js").Sequence<unknown>;
    type(): dsviper.Type;
    decode(blob: dsviper.ValueBlob): import("./_codegen/container.js").Sequence<unknown>;
};
export declare const Set_Projection_LinkKey: {
    new (value?: unknown): import("./_codegen/container.js").Sequence<unknown>;
    type(): dsviper.Type;
    decode(blob: dsviper.ValueBlob): import("./_codegen/container.js").Sequence<unknown>;
};
export declare const Map_ModelA_MaterialKey_to_ModelB_MaterialKey: {
    new (value?: unknown): import("./_codegen/container.js").Mapping<unknown, unknown>;
    type(): dsviper.Type;
    decode(blob: dsviper.ValueBlob): import("./_codegen/container.js").Mapping<unknown, unknown>;
};
