/** Tools — le pool, vu d'un client. */
import dsviper from "@digitalsubstrate/dsviper";
import * as demo from "../demo/data.js";
export declare const NAME = "Tools";
export declare const UUID: dsviper.ValueUUId;
/** Le pool, vu d'un client. */
export declare class Remote {
    private readonly service;
    constructor(service: dsviper.ServiceRemote);
    isAvailable(): boolean;
    add(a: bigint, b: bigint): bigint;
    addVector(a: demo.Vector3, b: demo.Vector3): demo.Vector3;
    randomString(size: number): string;
}
