/** Service — les conteneurs que le modèle mentionne, nommés et constructibles. */
import dsviper from "@digitalsubstrate/dsviper";
export declare const Optional_AnyConceptKey: {
    new (value?: unknown): import("./_codegen/container.js").Optional<unknown>;
    type(): dsviper.Type;
    decode(blob: dsviper.ValueBlob): import("./_codegen/container.js").Optional<unknown>;
};
export declare const Optional_Demo_PlayerKey: {
    new (value?: unknown): import("./_codegen/container.js").Optional<unknown>;
    type(): dsviper.Type;
    decode(blob: dsviper.ValueBlob): import("./_codegen/container.js").Optional<unknown>;
};
export declare const Optional_Demo_PlayerProperty: {
    new (value?: unknown): import("./_codegen/container.js").Optional<unknown>;
    type(): dsviper.Type;
    decode(blob: dsviper.ValueBlob): import("./_codegen/container.js").Optional<unknown>;
};
export declare const Set_Demo_PlayerKey: {
    new (value?: unknown): import("./_codegen/container.js").Sequence<unknown>;
    type(): dsviper.Type;
    decode(blob: dsviper.ValueBlob): import("./_codegen/container.js").Sequence<unknown>;
};
