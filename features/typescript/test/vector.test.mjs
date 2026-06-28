import { test } from "node:test";
import { strict as assert } from "node:assert";
import dsviper from "@digitalsubstrate/dsviper";
import {
  Vector_uint8, Vector_Test_StructureS, Test_StructureS,
} from "../features/dist/index.js";

// --- TestVectorConstruction ---

test("empty_vector", () => {
  const v = new Vector_uint8();
  assert.equal(v.size, 0);
});

test("vector_from_list", () => {
  const v = new Vector_uint8([1, 2, 3, 4, 5]);
  assert.equal(v.size, 5);
});

test("vector_iteration", () => {
  const v = new Vector_uint8([10, 20, 30]);
  const values = [...v];
  assert.deepEqual(values, [10, 20, 30]);
});

// --- TestVectorAccess ---

test("getitem", () => {
  const v = new Vector_uint8([1, 2, 3]);
  assert.equal(v.at(0), 1);
  assert.equal(v.at(1), 2);
  assert.equal(v.at(2), 3);
});

test("negative_index", () => {
  const v = new Vector_uint8([1, 2, 3]);
  assert.equal(v.at(v.size - 1), 3);
});

test("setitem", () => {
  const v = new Vector_uint8([1, 2, 3]);
  v.set(1, 99);
  assert.equal(v.at(1), 99);
});

// --- TestVectorMutations ---

test("append", () => {
  const v = new Vector_uint8([1, 2]);
  v.append(3);
  assert.equal(v.size, 3);
  assert.equal(v.at(2), 3);
});

test("clear", () => {
  const v = new Vector_uint8([1, 2, 3]);
  v.clear();
  assert.equal(v.size, 0);
});

test("pop", () => {
  const v = new Vector_uint8([1, 2, 3]);
  const val = v.pop();
  assert.equal(val, 3);
  assert.equal(v.size, 2);
});

test("pop_at_index", () => {
  const v = new Vector_uint8([1, 2, 3]);
  const val = v.pop(0);
  assert.equal(val, 1);
  assert.deepEqual([...v], [2, 3]);
});

test("insert", () => {
  const v = new Vector_uint8([1, 3]);
  v.insert(1, 2);
  assert.deepEqual([...v], [1, 2, 3]);
});

test("extend", () => {
  const v1 = new Vector_uint8([1, 2]);
  const v2 = new Vector_uint8([3, 4]);
  v1.extend(v2);
  assert.deepEqual([...v1], [1, 2, 3, 4]);
});

test("remove", () => {
  const v = new Vector_uint8([1, 2, 3, 2]);
  v.remove(2);
  assert.deepEqual([...v], [1, 3, 2]);
});

// --- TestVectorStructure ---

test("vector_of_structures", () => {
  const v = new Vector_Test_StructureS([
    { f_float: 1.0, f_string: "one" },
    { f_float: 2.0, f_string: "two" },
  ]);
  assert.equal(v.size, 2);
  assert.equal(v.at(0).f_string, "one");
  assert.equal(v.at(1).f_string, "two");
});

// --- TestVectorSearch ---

test("count", () => {
  const v = new Vector_uint8([1, 2, 3, 2, 1, 2]);
  assert.equal(v.count(2), 3);
  assert.equal(v.count(1), 2);
  assert.equal(v.count(99), 0);
});

test("index", () => {
  const v = new Vector_uint8([1, 2, 3, 2]);
  assert.equal(v.index(1), 0);
  assert.equal(v.index(2), 1);
  assert.equal(v.index(3), 2);
});

test("index_matches_python_list", () => {
  const data = [1, 2, 3, 2, 1];
  const p = [...data];
  const v = new Vector_uint8(data);
  assert.equal(p.indexOf(2), v.index(2));
  assert.equal(p.indexOf(3), v.index(3));
});

// --- TestVectorCopy ---

test("copy_creates_independent_vector", () => {
  const v1 = new Vector_uint8([1, 2, 3]);
  const v2 = v1.copy();
  assert.deepEqual([...v1], [...v2]);
  v2.append(4);
  assert.equal(v1.size, 3);
  assert.equal(v2.size, 4);
});

test("copy_preserves_values", () => {
  const v1 = new Vector_uint8([10, 20, 30]);
  const v2 = v1.copy();
  assert.deepEqual([...v2], [10, 20, 30]);
});

// --- TestVectorOperators ---

test("add_creates_new_vector", () => {
  const v1 = new Vector_uint8([1, 2]);
  const v2 = new Vector_uint8([3, 4]);
  const v3 = v1.concat(v2);
  assert.deepEqual([...v3], [1, 2, 3, 4]);
  assert.deepEqual([...v1], [1, 2]);
  assert.deepEqual([...v2], [3, 4]);
});

test("iadd_modifies_in_place", () => {
  const v1 = new Vector_uint8([1, 2]);
  const v2 = new Vector_uint8([3, 4]);
  v1.extend(v2);
  assert.deepEqual([...v1], [1, 2, 3, 4]);
});

test("contains", () => {
  const v = new Vector_uint8([1, 2, 3]);
  assert.ok(v.contains(2));
  assert.ok(!v.contains(99));
});

// --- TestVectorSerialization ---

test("encode_decode_roundtrip", () => {
  const v1 = new Vector_uint8([1, 2, 3, 4, 5]);
  const blob = v1.encode();
  const v2 = Vector_uint8.decode(blob);
  assert.deepEqual([...v2], [1, 2, 3, 4, 5]);
});

test("encode_decode_empty", () => {
  const v1 = new Vector_uint8();
  const blob = v1.encode();
  const v2 = Vector_uint8.decode(blob);
  assert.equal(v2.size, 0);
});
