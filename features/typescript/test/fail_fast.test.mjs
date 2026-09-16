// Fail-fast constructor contract (DESIGN.md §1), TypeScript mirror of
// python/tests/test_fail_fast.py. A proxy holds exactly one runtime value of
// exactly its own type; handing a constructor a runtime value of the WRONG type
// must throw at construction, not defer. Kept parallel with the Python suite
// per DESIGN.md §7.
import { test } from "node:test";
import { strict as assert } from "node:assert";
import { StructureS, StructureT, ConceptAKey, ConceptBKey, EnumerationE } from "../generated/dist/demo/data.js";
import { Set_uint8, Set_Demo_ConceptAKey, Vector_uint8, Vector_int8, Optional_Demo_ConceptAKey, Optional_Demo_ConceptBKey, Variant_string_uint8_Demo_StructureS } from "../generated/dist/containers.js";

// --- Constructor rejects a runtime value of another type ---

test("struct rejects other struct", () => {
  assert.throws(() => new StructureS(new StructureT().value), TypeError);
});

test("concept key rejects other concept", () => {
  assert.throws(() => new ConceptAKey(ConceptBKey.create().value), TypeError);
});

test("set rejects other element type", () => {
  assert.throws(() => new Set_uint8(new Set_Demo_ConceptAKey().value), TypeError);
});

test("vector rejects other element type", () => {
  assert.throws(() => new Vector_uint8(new Vector_int8([1]).value), TypeError);
});

test("optional rejects other element type", () => {
  assert.throws(() => new Optional_Demo_ConceptAKey(new Optional_Demo_ConceptBKey().value), TypeError);
});

test("enum rejects non-enum value", () => {
  assert.throws(() => new EnumerationE(new StructureS().value), TypeError);
});

// --- Constructor accepts a correctly-typed runtime value ---

test("struct accepts same type", () => {
  const s = new StructureS(new StructureS().value);
  assert.ok(s instanceof StructureS);
});

test("set accepts same type", () => {
  const a = new Set_uint8(new Set_uint8([1, 2]).value);
  assert.equal(a.size, 2);
});

// --- Variant arm getter precondition ---

test("variant get wrong arm throws", () => {
  const v = new Variant_string_uint8_Demo_StructureS("hello");
  assert.ok(v.isString());
  assert.throws(() => v.getUint8(), Error);
});

test("variant get right arm returns", () => {
  const v = new Variant_string_uint8_Demo_StructureS("hello");
  assert.equal(v.getString(), "hello");
});
