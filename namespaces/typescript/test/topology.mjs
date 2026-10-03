/** The topology, tested on the rendered output.
 *
 * This site proves one thing, and is the only one that can: two namespaces declare the same
 * name and neither of them moves. Where the pack wrote `ModelA_Colour` and `ModelB_Colour` --
 * a flattening that hides the clash by having already resolved it in the name -- here the path
 * *is* the namespace, and `Colour` stays `Colour`.
 */
import { test } from "node:test";
import { strict as assert } from "node:assert";

import * as modelA from "../generated/dist/model_a/data.js";
import * as modelB from "../generated/dist/model_b/data.js";
import * as projection from "../generated/dist/projection/data.js";

test("two namespaces declare Colour, and they are two types", () => {
    assert.ok(modelA.Colour, "ModelA::Colour");
    assert.ok(modelB.Colour, "ModelB::Colour");
    assert.notEqual(modelA.Colour, modelB.Colour);
    assert.equal(modelA.Colour.name, "Colour");
    assert.equal(modelB.Colour.name, "Colour");
});

test("and Material too -- a concept, hence its key", () => {
    assert.ok(modelA.MaterialKey);
    assert.ok(modelB.MaterialKey);
    assert.notEqual(modelA.MaterialKey, modelB.MaterialKey);
    assert.equal(modelA.MaterialKey.name, "MaterialKey");
    assert.equal(modelB.MaterialKey.name, "MaterialKey");
});

test("a unit declaring no homonym imports like the others", () => {
    assert.ok(projection.LinkKey, "Projection::Link");
    assert.ok(projection.Pair, "Projection::Pair");
});

test("a value of one namespace is not accepted by the other", () => {
    const a = new modelA.Colour();
    assert.throws(() => new modelB.Colour(a.unwrapValue()), TypeError);
});
