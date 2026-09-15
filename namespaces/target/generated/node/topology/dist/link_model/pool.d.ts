/** LinkModel — le pool, vu d'un client. */
import dsviper from "@digitalsubstrate/dsviper";
import * as projection from "../projection/data.js";
export declare const NAME = "LinkModel";
export declare const UUID: dsviper.ValueUUId;
/** Le pool d'attachments, vu d'un client. */
export declare class Remote {
    private readonly service;
    constructor(service: dsviper.ServiceRemote);
    isAvailable(): boolean;
    clear(state: dsviper.AttachmentMutating, linkKey: projection.LinkKey): void;
}
