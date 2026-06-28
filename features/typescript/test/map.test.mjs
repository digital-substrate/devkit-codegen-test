import { test } from "node:test";
import { strict as assert } from "node:assert";
import dsviper from "@digitalsubstrate/dsviper";
import {
  Map_int8_to_string, Map_string_to_Test_StructureS, Map_Test_StructureS_to_string,
  Test_StructureS,
} from "../features/dist/index.js";

// --- TestMapConstruction ---

test("empty_map", () => {
  const m = new Map_int8_to_string();
  assert.equal(m.size, 0);
});

test("map_from_dict", () => {
  const m = new Map_int8_to_string([[1, "one"], [2, "two"]]);
  assert.equal(m.size, 2);
});

// --- TestMapAccess ---

test("getitem", () => {
  const m = new Map_int8_to_string([[1, "one"], [2, "two"]]);
  assert.equal(m.at(1), "one");
  assert.equal(m.at(2), "two");
});

test("setitem", () => {
  const m = new Map_int8_to_string();
  m.set(1, "one");
  assert.equal(m.at(1), "one");
});

test("contains", () => {
  const m = new Map_int8_to_string([[1, "one"]]);
  assert.ok(m.has(1));
  assert.ok(!m.has(99));
});

test("get_present", () => {
  const m = new Map_int8_to_string([[1, "one"]]);
  assert.equal(m.get(1), "one");
});

test("get_absent_default", () => {
  const m = new Map_int8_to_string([[1, "one"]]);
  assert.equal(m.get(99, "default"), "default");
});

// --- TestMapMutations ---

test("delete", () => {
  const m = new Map_int8_to_string([[1, "one"], [2, "two"]]);
  m.remove(1);
  assert.equal(m.size, 1);
  assert.ok(!m.has(1));
});

test("clear", () => {
  const m = new Map_int8_to_string([[1, "one"], [2, "two"]]);
  m.clear();
  assert.equal(m.size, 0);
});

test("pop", () => {
  const m = new Map_int8_to_string([[1, "one"], [2, "two"]]);
  const val = m.pop(1);
  assert.equal(val, "one");
  assert.equal(m.size, 1);
});

test("pop_with_default", () => {
  const m = new Map_int8_to_string([[1, "one"]]);
  const val = m.pop(99, "default");
  assert.equal(val, "default");
  assert.equal(m.size, 1); // Map unchanged
});

// --- TestMapIteration ---

test("keys", () => {
  const m = new Map_int8_to_string([[1, "one"], [2, "two"]]);
  const keys = [...m.keys()];
  assert.deepEqual(keys.sort((a, b) => a - b), [1, 2]);
});

test("values", () => {
  const m = new Map_int8_to_string([[1, "one"], [2, "two"]]);
  const values = [...m.values()];
  assert.deepEqual(values.sort(), ["one", "two"]);
});

test("items", () => {
  const m = new Map_int8_to_string([[1, "one"], [2, "two"]]);
  const items = m.items();
  assert.equal(items.length, 2);
});

// --- TestMapIterDunder ---

test("iter", () => {
  const m = new Map_int8_to_string([[1, "one"], [2, "two"], [3, "three"]]);
  const keys = [...m];
  assert.deepEqual(keys.sort((a, b) => a - b), [1, 2, 3]);
});

test("iter_empty", () => {
  const m = new Map_int8_to_string();
  const keys = [...m];
  assert.deepEqual(keys, []);
});

test("iter_multiple_times", () => {
  const m = new Map_int8_to_string([[1, "a"], [2, "b"]]);
  const list1 = [...m].sort((a, b) => a - b);
  const list2 = [...m].sort((a, b) => a - b);
  assert.deepEqual(list1, list2);
});

// --- TestMapWithStructures ---

test("map_string_to_structure", () => {
  // Map values need plain shapes or vpr_values, not proxy objects
  const m = new Map_string_to_Test_StructureS([["key", { f_float: 1.5, f_string: "test" }]]);
  const retrieved = m.at("key");
  assert.ok(Math.abs(retrieved.f_float - 1.5) < 1e-5);
});

test("map_structure_to_string", () => {
  const s = new Test_StructureS({ f_float: 1.5, f_string: "test" });
  const m = new Map_Test_StructureS_to_string();
  m.set(s, "value");
  assert.equal(m.at(s), "value");
});

// --- TestMapCopy ---

test("copy_creates_independent_map", () => {
  const m1 = new Map_int8_to_string([[1, "one"], [2, "two"]]);
  const m2 = m1.copy();
  assert.equal(m1.size, m2.size);
  m2.set(3, "three");
  assert.equal(m1.size, 2);
  assert.equal(m2.size, 3);
});

test("copy_preserves_entries", () => {
  const m1 = new Map_int8_to_string([[1, "one"], [2, "two"]]);
  const m2 = m1.copy();
  assert.equal(m2.at(1), "one");
  assert.equal(m2.at(2), "two");
});

// --- TestMapAdvancedOperations ---

test("popitem", () => {
  const m = new Map_int8_to_string([[1, "one"], [2, "two"]]);
  const [key, value] = m.popitem();
  assert.equal(m.size, 1);
  assert.ok([1, 2].includes(key));
  assert.ok(["one", "two"].includes(value));
});

test("setdefault_new_key", () => {
  const m = new Map_int8_to_string([[1, "one"]]);
  m.setdefault(2, "two");
  assert.equal(m.at(2), "two");
});

test("setdefault_existing_key", () => {
  const m = new Map_int8_to_string([[1, "one"]]);
  m.setdefault(1, "ONE");
  assert.equal(m.at(1), "one"); // Original value preserved
});

test("update", () => {
  const m1 = new Map_int8_to_string([[1, "one"]]);
  const m2 = new Map_int8_to_string([[2, "two"], [3, "three"]]);
  m1.update(m2);
  assert.equal(m1.size, 3);
  assert.equal(m1.at(2), "two");
  assert.equal(m1.at(3), "three");
});

test("update_overwrites_existing", () => {
  const m1 = new Map_int8_to_string([[1, "one"], [2, "two"]]);
  const m2 = new Map_int8_to_string([[2, "TWO"]]);
  m1.update(m2);
  assert.equal(m1.at(2), "TWO");
});

// --- TestMapSerialization ---

test("encode_decode_roundtrip", () => {
  const m1 = new Map_int8_to_string([[1, "one"], [2, "two"]]);
  const blob = m1.encode();
  const m2 = Map_int8_to_string.decode(blob);
  assert.equal(m2.size, 2);
  assert.equal(m2.at(1), "one");
  assert.equal(m2.at(2), "two");
});

test("encode_decode_empty", () => {
  const m1 = new Map_int8_to_string();
  const blob = m1.encode();
  const m2 = Map_int8_to_string.decode(blob);
  assert.equal(m2.size, 0);
});
