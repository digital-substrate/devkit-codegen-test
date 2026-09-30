/** La topologie, éprouvée sur le rendu.
 *
 * CE SITE NE PROUVE QU'UNE CHOSE, mais il est le seul à pouvoir la prouver : deux namespaces
 * déclarent le même nom et aucun des deux ne bouge. Là où le pack écrivait `ModelA_Colour` et
 * `ModelB_Colour` -- un aplatissement qui rend le conflit invisible parce qu'il l'a déjà
 * résolu dans le nom -- ici le chemin *est* le namespace, et `Colour` reste `Colour`.
 */
import { test } from "node:test";
import { strict as assert } from "node:assert";

import * as modelA from "../generated/dist/model_a/data.js";
import * as modelB from "../generated/dist/model_b/data.js";
import * as projection from "../generated/dist/projection/data.js";

test("deux namespaces déclarent Colour, et ce sont deux types", () => {
    assert.ok(modelA.Colour, "ModelA::Colour");
    assert.ok(modelB.Colour, "ModelB::Colour");
    assert.notEqual(modelA.Colour, modelB.Colour);
    assert.equal(modelA.Colour.name, "Colour");
    assert.equal(modelB.Colour.name, "Colour");
});

test("et Material aussi -- un concept, donc sa clé", () => {
    assert.ok(modelA.MaterialKey);
    assert.ok(modelB.MaterialKey);
    assert.notEqual(modelA.MaterialKey, modelB.MaterialKey);
    assert.equal(modelA.MaterialKey.name, "MaterialKey");
    assert.equal(modelB.MaterialKey.name, "MaterialKey");
});

test("une unité qui n'en déclare aucun homonyme s'importe comme les autres", () => {
    assert.ok(projection.LinkKey, "Projection::Link");
    assert.ok(projection.Pair, "Projection::Pair");
});

test("une valeur d'un namespace n'est pas acceptée par l'autre", () => {
    const a = new modelA.Colour();
    assert.throws(() => new modelB.Colour(a.vprValue), TypeError);
});
