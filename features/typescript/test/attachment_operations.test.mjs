// The operations generated for each attachment: one method per field, typed and completable.
import { test } from "node:test";
import { strict as assert } from "node:assert";
import dsviper from "@digitalsubstrate/dsviper";
import { ConceptAKey, ConceptCKey, StructureU, StructureV } from "../generated/dist/demo/data.js";
import { definitions } from "../generated/dist/index.js";
import * as ma from "../generated/dist/demo/attachments.js";

function mutating() {
  return new dsviper.CommitMutableState(new dsviper.CommitState(definitions())).attachmentMutating();
}

const asObject = (mapping) => Object.fromEntries(mapping.keys().map((k) => [k, mapping.at(k)]));
const sorted = (values) => [...values].sort((a, b) => a - b);

// --- on one field of a structure document ---

test("set field: union and subtract", () => {
  const m = mutating();
  const key = ConceptAKey.create();
  ma.ConceptA.properties.set(m, key, new StructureV());
  ma.ConceptA.properties.unionF_set(m, key, new Set([7, 8]));
  assert.deepEqual(sorted(ma.ConceptA.properties.get(m, key).unwrap().f_set), [1, 2, 3, 7, 8]);
  ma.ConceptA.properties.subtractF_set(m, key, [1, 7]);
  assert.deepEqual(sorted(ma.ConceptA.properties.get(m, key).unwrap().f_set), [2, 3, 8]);
});

test("map field: union, update and subtract", () => {
  const m = mutating();
  const key = ConceptAKey.create();
  ma.ConceptA.properties.set(m, key, new StructureV());
  ma.ConceptA.properties.unionF_map(m, key, new Map([[2, "Two"]]));
  ma.ConceptA.properties.updateF_map(m, key, new Map([[0, "zero"], [9, "Nine"]]));
  ma.ConceptA.properties.subtractF_map(m, key, [1]);
  assert.deepEqual(asObject(ma.ConceptA.properties.get(m, key).unwrap().f_map), { 0: "zero", 2: "Two" });
});

test("xarray field: insert, update and remove", () => {
  const m = mutating();
  const key = ConceptCKey.create();
  ma.ConceptC.propertiesC.set(m, key, new StructureU());
  const first = dsviper.ValueUUId.create();
  const second = dsviper.ValueUUId.create();
  ma.ConceptC.propertiesC.insertF_xarray(m, key, dsviper.ValueUUId.INVALID, first, 5);
  ma.ConceptC.propertiesC.insertF_xarray(m, key, dsviper.ValueUUId.INVALID, second, 6);
  ma.ConceptC.propertiesC.updateF_xarray(m, key, first, 50);
  ma.ConceptC.propertiesC.removeF_xarray(m, key, second);
  assert.deepEqual([...ma.ConceptC.propertiesC.get(m, key).unwrap().f_xarray], [50]);
});

test("scalar field: set", () => {
  const m = mutating();
  const key = ConceptAKey.create();
  ma.ConceptA.properties.set(m, key, new StructureV());
  ma.ConceptA.properties.setF_string(m, key, "written");
  assert.equal(ma.ConceptA.properties.get(m, key).unwrap().f_string, "written");
});

// --- when the document is itself the aggregate ---

test("set document: union and subtract", () => {
  const m = mutating();
  const key = ConceptAKey.create();
  ma.ConceptA.propertiesSeInt8.set(m, key, [1, 2]);
  ma.ConceptA.propertiesSeInt8.union(m, key, [3]);
  ma.ConceptA.propertiesSeInt8.subtract(m, key, new Set([1]));
  assert.deepEqual(sorted(ma.ConceptA.propertiesSeInt8.get(m, key).unwrap()), [2, 3]);
});

test("map document: union, update and subtract", () => {
  const m = mutating();
  const key = ConceptAKey.create();
  ma.ConceptA.propertiesMapInt8String.set(m, key, new Map([[1, "One"]]));
  ma.ConceptA.propertiesMapInt8String.union(m, key, new Map([[2, "Two"]]));
  ma.ConceptA.propertiesMapInt8String.update(m, key, new Map([[1, "one"], [3, "Three"]]));
  ma.ConceptA.propertiesMapInt8String.subtract(m, key, [2]);
  assert.deepEqual(asObject(ma.ConceptA.propertiesMapInt8String.get(m, key).unwrap()), { 1: "one" });
});

test("xarray document: insert, update and remove", () => {
  const m = mutating();
  const key = ConceptAKey.create();
  ma.ConceptA.propertiesXArray.set(m, key, new dsviper.ValueXArray(new dsviper.TypeXArray(dsviper.Type.INT8)));
  const position = dsviper.ValueUUId.create();
  ma.ConceptA.propertiesXArray.insert(m, key, dsviper.ValueUUId.INVALID, position, 4);
  ma.ConceptA.propertiesXArray.update(m, key, position, 40);
  assert.deepEqual([...ma.ConceptA.propertiesXArray.get(m, key).unwrap()], [40]);
  ma.ConceptA.propertiesXArray.remove(m, key, position);
  assert.deepEqual([...ma.ConceptA.propertiesXArray.get(m, key).unwrap()], []);
});

// --- an operation exists only where the document gives it a meaning ---

test("no aggregate operation on a scalar document, no lookup by name", () => {
  assert.equal(ma.ConceptA.propertiesInt8.union, undefined);
  assert.equal(ma.ConceptA.properties.unionF_sett, undefined);
  assert.equal(ma.ConceptA.properties.update, undefined);
});

test("an attachment names itself by its runtime id, a constant, and by its descriptor", () => {
  const attachment = definitions().checkAttachment(ma.ConceptA.properties.runtimeId);
  assert.ok(attachment.equals(ma.ConceptA.properties.descriptor));
  assert.ok(!ma.ConceptA.properties.runtimeId.equals(ma.ConceptA.propertiesInt8.runtimeId));
});
