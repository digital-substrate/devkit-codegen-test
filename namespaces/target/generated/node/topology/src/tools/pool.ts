// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

/** Tools — le pool, vu d'un client. */
import dsviper from "@digitalsubstrate/dsviper";

import { Mapping, Ordered, Sequence } from "../_codegen/container.js";
import { AnyConceptKey, unwrap, wrap } from "../_codegen/registry.js";

export const NAME = "Tools";
export const UUID = dsviper.ValueUUId.create("17e63428-03e1-41d7-ad9d-60c5665bbd66");

/** Le pool, vu d'un client. */
export class Remote {
    private readonly service: dsviper.ServiceRemote;

    constructor(service: dsviper.ServiceRemote) {
        this.service = service;
    }

    isAvailable(): boolean {
        return this.service.functionPoolFuncs(NAME) !== undefined;
    }

    reset(): void {
        this.service.functionPoolFunc(NAME, "reset").call();
    }

    add(a: bigint, b: bigint): bigint {
        return wrap(this.service.functionPoolFunc(NAME, "add").call(unwrap(a), unwrap(b)));
    }
}