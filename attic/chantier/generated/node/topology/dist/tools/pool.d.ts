/** Tools — le pool, vu d'un client. */
import dsviper from "@digitalsubstrate/dsviper";
export declare const NAME = "Tools";
export declare const UUID: dsviper.ValueUUId;
/** Le pool, vu d'un client. */
export declare class Remote {
    private readonly service;
    constructor(service: dsviper.ServiceRemote);
    isAvailable(): boolean;
    reset(): void;
    add(a: bigint, b: bigint): bigint;
}
