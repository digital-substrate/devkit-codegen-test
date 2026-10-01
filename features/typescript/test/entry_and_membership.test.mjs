// The package leads to every unit and its attachments; membership always answers; a variant
// takes a native the runtime decodes into one of its alternatives.
import { test } from "node:test";
import { strict as assert } from "node:assert";
import * as f from "../generated/dist/index.js";

test("the package entry leads to each unit and its attachments", () => {
  assert.equal(typeof f.demo.StructureU, "function");
  assert.equal(typeof f.demo.attachments.ConceptA, "function");
  assert.equal(typeof f.AnyConceptKey, "function");
  assert.equal(typeof f.AnyValue, "function");
});

test("a key is found through another view", () => {
  const key = f.demo.ConceptCKey.create();
  const keys = new f.Set_of_AnyConceptKey([key.toAnyConceptKey()]);
  assert.ok(keys.has(key));
  assert.ok(keys.has(key.toParentKey()));
  assert.ok(!keys.has(f.demo.ConceptCKey.create()));
});

test("an element of the wrong type is not there", () => {
  assert.ok(!new f.Set_of_uint8([1]).has("x"));
  assert.ok(!new f.Vector_of_uint8([1]).has(300));
});

test("a variant takes a number the runtime decodes into an alternative", () => {
  const u = new f.demo.StructureU();
  u.f_variant = 7;
  assert.ok(u.f_variant.isUint8());
  assert.throws(() => { u.f_variant = 7.5; });
  assert.ok(new f.Variant_of_string_or_uint8(7).isUint8());
});
