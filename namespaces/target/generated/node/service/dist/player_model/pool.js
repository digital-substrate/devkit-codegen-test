// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/service/Service.dsm.json by kibo-2.0.0.jar
/** PlayerModel — le pool, vu d'un client. */
import dsviper from "@digitalsubstrate/dsviper";
import { unwrap, wrap } from "../_codegen/registry.js";
export const NAME = "PlayerModel";
export const UUID = dsviper.ValueUUId.create("d75a8a57-f0ad-4a44-84f7-1ea409d4bd36");
/** Le pool d'attachments, vu d'un client. */
export class Remote {
    service;
    constructor(service) {
        this.service = service;
    }
    isAvailable() {
        return this.service.attachmentFunctionPoolFuncs(NAME) !== undefined;
    }
    create(state, nickname, level) {
        return wrap(this.service.attachmentFunctionPoolFunc(NAME, "create").call(state, unwrap(nickname), unwrap(level)));
    }
    hasPlayer(state, nickname) {
        return wrap(this.service.attachmentFunctionPoolFunc(NAME, "has_player").call(state, unwrap(nickname)));
    }
}
