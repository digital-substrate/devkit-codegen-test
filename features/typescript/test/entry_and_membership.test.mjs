// The package leads to every unit, its attachments imported by their path; membership is as strict as storing; a variant
// takes a native the runtime decodes into one of its alternatives.
import { test } from "node:test";
import { strict as assert } from "node:assert";
import * as f from "../generated/dist/index.js";
import * as ma from "../generated/dist/demo/attachments.js";

test("the package entry leads to each unit; its attachments are imported by their path", () => {
  assert.equal(typeof f.demo.StructureU, "function");
  assert.equal("attachments" in f.demo, false);
  assert.equal(typeof ma.ConceptA, "function");
  assert.equal(typeof f.AnyConceptKey, "function");
  assert.equal(typeof f.AnyValue, "function");
});

test("a key is found through another view", () => {
  const key = f.demo.ConceptCKey.create();
  const keys = new f.Set_of_AnyConceptKey([key.toAnyConceptKey()]);
  assert.ok(keys.has(key.toAnyConceptKey()));
  assert.ok(keys.has(key.toParentKey().toAnyConceptKey()));
  assert.ok(!keys.has(f.demo.ConceptCKey.create().toAnyConceptKey()));
});

test("another view is widened explicitly", () => {
  const key = f.demo.ConceptCKey.create();
  assert.throws(() => new f.Set_of_AnyConceptKey([key.toAnyConceptKey()]).has(key));
  assert.throws(() => new f.Set_of_Demo_ConceptBKey([key.toParentKey()]).has(key));
});

test("an element of the wrong type throws", () => {
  assert.throws(() => new f.Set_of_uint8([1]).has("x"));
  assert.throws(() => new f.Vector_of_uint8([1]).has(300));
});

test("a variant takes a number the runtime decodes into an alternative", () => {
  const u = new f.demo.StructureU();
  u.f_variant = 7;
  assert.ok(u.f_variant.isUint8());
  assert.throws(() => { u.f_variant = 7.5; });
  assert.ok(new f.Variant_of_string_or_uint8(7).isUint8());
});
