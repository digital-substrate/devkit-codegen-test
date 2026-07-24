// Fail-fast constructor contract (DESIGN.md §1), TypeScript mirror of
// python/tests/test_fail_fast.py. A proxy holds exactly one runtime value of
// exactly its own type; handing a constructor a runtime value of the WRONG type
// must throw at construction, not defer. Kept parallel with the Python suite
// per DESIGN.md §7.
import { test } from "node:test";
import { strict as assert } from "node:assert";
import {
  Test_StructureS, Test_StructureT,
  Test_ConceptAKey, Test_ConceptBKey,
  Test_EnumerationE,
  Set_uint8, Set_Test_ConceptAKey,
  Vector_uint8, Vector_int8,
  Optional_Test_ConceptAKey, Optional_Test_ConceptBKey,
  Variant_string_uint8_Test_StructureS,
} from "../features/dist/index.js";

// --- Constructor rejects a runtime value of another type ---

test("struct rejects other struct", () => {
  assert.throws(() => new Test_StructureS(new Test_StructureT().vprValue), TypeError);
});

test("concept key rejects other concept", () => {
  assert.throws(() => new Test_ConceptAKey(Test_ConceptBKey.create().vprValue), TypeError);
});

test("set rejects other element type", () => {
  assert.throws(() => new Set_uint8(new Set_Test_ConceptAKey().vprValue), TypeError);
});

test("vector rejects other element type", () => {
  assert.throws(() => new Vector_uint8(new Vector_int8([1]).vprValue), TypeError);
});

test("optional rejects other element type", () => {
  assert.throws(() => new Optional_Test_ConceptAKey(new Optional_Test_ConceptBKey().vprValue), TypeError);
});

test("enum rejects non-enum value", () => {
  assert.throws(() => new Test_EnumerationE(new Test_StructureS().vprValue), TypeError);
});

// --- Constructor accepts a correctly-typed runtime value ---

test("struct accepts same type", () => {
  const s = new Test_StructureS(new Test_StructureS().vprValue);
  assert.ok(s instanceof Test_StructureS);
});

test("set accepts same type", () => {
  const a = new Set_uint8(new Set_uint8([1, 2]).vprValue);
  assert.equal(a.size, 2);
});

// --- Variant arm getter precondition ---

test("variant get wrong arm throws", () => {
  const v = new Variant_string_uint8_Test_StructureS("hello");
  assert.ok(v.isString());
  assert.throws(() => v.getUint8(), Error);
});

test("variant get right arm returns", () => {
  const v = new Variant_string_uint8_Test_StructureS("hello");
  assert.equal(v.getString(), "hello");
});
