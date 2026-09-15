// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/service/Service.dsm.json by kibo-2.0.0.jar

/** PlayerModel — le pool, vu d'un client. */
import dsviper from "@digitalsubstrate/dsviper";

import { Mapping, Ordered, Sequence } from "../_codegen/container.js";
import { AnyConceptKey, unwrap, wrap } from "../_codegen/registry.js";
import * as demo from "../demo/data.js";

export const NAME = "PlayerModel";
export const UUID = dsviper.ValueUUId.create("d75a8a57-f0ad-4a44-84f7-1ea409d4bd36");

/** Le pool d'attachments, vu d'un client. */
export class Remote {
    private readonly service: dsviper.ServiceRemote;

    constructor(service: dsviper.ServiceRemote) {
        this.service = service;
    }

    isAvailable(): boolean {
        return this.service.attachmentFunctionPoolFuncs(NAME) !== undefined;
    }

    create(state: dsviper.AttachmentMutating, nickname: string, level: demo.Level): demo.PlayerKey {
        return wrap(this.service.attachmentFunctionPoolFunc(NAME, "create").call(state as unknown as dsviper.InputValue, unwrap(nickname), unwrap(level)));
    }

    hasPlayer(state: dsviper.AttachmentMutating, nickname: string): demo.PlayerKey | undefined {
        return wrap(this.service.attachmentFunctionPoolFunc(NAME, "has_player").call(state as unknown as dsviper.InputValue, unwrap(nickname)));
    }
}