/** PlayerModel — le pool, vu d'un client. */
import dsviper from "@digitalsubstrate/dsviper";
import * as demo from "../demo/data.js";
export declare const NAME = "PlayerModel";
export declare const UUID: dsviper.ValueUUId;
/** Le pool d'attachments, vu d'un client. */
export declare class Remote {
    private readonly service;
    constructor(service: dsviper.ServiceRemote);
    isAvailable(): boolean;
    create(state: dsviper.AttachmentMutating, nickname: string, level: demo.Level): demo.PlayerKey;
    hasPlayer(state: dsviper.AttachmentMutating, nickname: string): demo.PlayerKey | undefined;
}
