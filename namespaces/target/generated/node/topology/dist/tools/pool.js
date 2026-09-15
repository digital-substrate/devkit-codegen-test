// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar
/** Tools — le pool, vu d'un client. */
import dsviper from "@digitalsubstrate/dsviper";
import { unwrap, wrap } from "../_codegen/registry.js";
export const NAME = "Tools";
export const UUID = dsviper.ValueUUId.create("17e63428-03e1-41d7-ad9d-60c5665bbd66");
/** Le pool, vu d'un client. */
export class Remote {
    service;
    constructor(service) {
        this.service = service;
    }
    isAvailable() {
        return this.service.functionPoolFuncs(NAME) !== undefined;
    }
    reset() {
        this.service.functionPoolFunc(NAME, "reset").call();
    }
    add(a, b) {
        return wrap(this.service.functionPoolFunc(NAME, "add").call(unwrap(a), unwrap(b)));
    }
}
