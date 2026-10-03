// Fail-fast constructor contract (DESIGN.md §1), TypeScript mirror of
// python/tests/test_fail_fast.py. A proxy holds exactly one runtime value of
// exactly its own type; handing a constructor a runtime value of the WRONG type
// must throw at construction, not defer. Kept parallel with the Python suite
// per DESIGN.md §7.
import { test } from "node:test";
import { strict as assert } from "node:assert";
import { StructureS, StructureT, ConceptAKey, ConceptBKey, EnumerationE } from "../generated/dist/demo/data.js";
import { Set_of_uint8, Set_of_Demo_ConceptAKey, Vector_of_uint8, Vector_of_int8, Optional_of_Demo_ConceptAKey, Optional_of_Demo_ConceptBKey, Variant_of_string_or_uint8_or_Demo_StructureS } from "../generated/dist/containers.js";

// --- Constructor rejects a runtime value of another type ---

test("struct rejects other struct", () => {
  assert.throws(() => new StructureS(new StructureT().unwrapValue()), TypeError);
});

test("concept key rejects other concept", () => {
  assert.throws(() => new ConceptAKey(ConceptBKey.create().unwrapValue()), TypeError);
});

test("set rejects other element type", () => {
  assert.throws(() => new Set_of_uint8(new Set_of_Demo_ConceptAKey().unwrapValue()), TypeError);
});

test("vector rejects other element type", () => {
  assert.throws(() => new Vector_of_uint8(new Vector_of_int8([1]).unwrapValue()), TypeError);
});

test("native content that does not fit throws the runtime error", () => {
  // Not a value of another type, but content the conversion refuses: as an append does.
  assert.throws(() => new Vector_of_uint8([300]), { name: "ViperError", message: /range of 'uint8'/ });
});

test("optional rejects other element type", () => {
  assert.throws(() => new Optional_of_Demo_ConceptAKey(new Optional_of_Demo_ConceptBKey().unwrapValue()), TypeError);
});

test("enum rejects non-enum value", () => {
  assert.throws(() => new EnumerationE(new StructureS().unwrapValue()), TypeError);
});

// --- Constructor accepts a correctly-typed runtime value ---

test("struct accepts same type", () => {
  const s = new StructureS(new StructureS().unwrapValue());
  assert.ok(s instanceof StructureS);
});

test("set accepts same type", () => {
  const a = new Set_of_uint8(new Set_of_uint8([1, 2]).unwrapValue());
  assert.equal(a.size, 2);
});

// --- Variant arm getter precondition ---

test("variant get wrong arm throws", () => {
  const v = new Variant_of_string_or_uint8_or_Demo_StructureS("hello");
  assert.ok(v.isString());
  assert.throws(() => v.getUint8(), Error);
});

test("variant get right arm returns", () => {
  const v = new Variant_of_string_or_uint8_or_Demo_StructureS("hello");
  assert.equal(v.getString(), "hello");
});
