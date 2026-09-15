// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/service/Service.dsm.json by kibo-2.0.0.jar
/** Demo — les attachments que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";
import { AttachmentProxy } from "../_codegen/attachment.js";
import { definitions } from "../index.js";
import { PlayerKey, PlayerProperty } from "./data.js";
/** Les attachments portés par Demo::PlayerKey. */
export class Player {
    static property = new AttachmentProxy(dsviper.ValueUUId.create("5f39a4c7-fa83-1290-432c-330fc392a39b"), definitions, PlayerKey, PlayerProperty);
}
