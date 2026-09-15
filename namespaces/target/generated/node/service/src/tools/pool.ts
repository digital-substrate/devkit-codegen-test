// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/service/Service.dsm.json by kibo-2.0.0.jar

/** Tools — le pool, vu d'un client. */
import dsviper from "@digitalsubstrate/dsviper";

import { Mapping, Ordered, Sequence } from "../_codegen/container.js";
import { AnyConceptKey, unwrap, wrap } from "../_codegen/registry.js";
import * as demo from "../demo/data.js";

export const NAME = "Tools";
export const UUID = dsviper.ValueUUId.create("7aa5aea2-c9de-4f91-8371-7995aca8c947");

/** Le pool, vu d'un client. */
export class Remote {
    private readonly service: dsviper.ServiceRemote;

    constructor(service: dsviper.ServiceRemote) {
        this.service = service;
    }

    isAvailable(): boolean {
        return this.service.functionPoolFuncs(NAME) !== undefined;
    }

    add(a: bigint, b: bigint): bigint {
        return wrap(this.service.functionPoolFunc(NAME, "add").call(unwrap(a), unwrap(b)));
    }

    addVector(a: demo.Vector3, b: demo.Vector3): demo.Vector3 {
        return wrap(this.service.functionPoolFunc(NAME, "add_vector").call(unwrap(a), unwrap(b)));
    }

    randomString(size: number): string {
        return wrap(this.service.functionPoolFunc(NAME, "random_string").call(unwrap(size)));
    }
}