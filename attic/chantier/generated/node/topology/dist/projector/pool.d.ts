/** Projector — le pool, vu d'un client. */
import dsviper from "@digitalsubstrate/dsviper";
import * as model_a from "../model_a/data.js";
import * as model_b from "../model_b/data.js";
export declare const NAME = "Projector";
export declare const UUID: dsviper.ValueUUId;
/** Le pool, vu d'un client. */
export declare class Remote {
    private readonly service;
    constructor(service: dsviper.ServiceRemote);
    isAvailable(): boolean;
    link(a: model_a.MaterialKey, b: model_b.MaterialKey): void;
}
