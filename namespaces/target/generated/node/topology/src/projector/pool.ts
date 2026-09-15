// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

/** Projector — le pool, vu d'un client. */
import dsviper from "@digitalsubstrate/dsviper";

import { Mapping, Ordered, Sequence } from "../_codegen/container.js";
import { AnyConceptKey, unwrap, wrap } from "../_codegen/registry.js";
import * as model_a from "../model_a/data.js";
import * as model_b from "../model_b/data.js";

export const NAME = "Projector";
export const UUID = dsviper.ValueUUId.create("3f513cf9-c9b9-4c57-8ace-ac9a644be74c");

/** Le pool, vu d'un client. */
export class Remote {
    private readonly service: dsviper.ServiceRemote;

    constructor(service: dsviper.ServiceRemote) {
        this.service = service;
    }

    isAvailable(): boolean {
        return this.service.functionPoolFuncs(NAME) !== undefined;
    }

    link(a: model_a.MaterialKey, b: model_b.MaterialKey): void {
        this.service.functionPoolFunc(NAME, "link").call(unwrap(a), unwrap(b));
    }
}