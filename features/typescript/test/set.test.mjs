import { test } from "node:test";
import { strict as assert } from "node:assert";
import dsviper from "@digitalsubstrate/dsviper";
import {
  Set_uint8, Set_Test_ConceptAKey, Test_ConceptAKey,
} from "../features/dist/index.js";

// --- TestSetConstruction ---

test("empty_set", () => {
  const s = new Set_uint8();
  assert.equal(s.size, 0);
});

test("set_from_list", () => {
  const s = new Set_uint8([1, 2, 3]);
  assert.equal(s.size, 3);
});

test("set_removes_duplicates", () => {
  const s = new Set_uint8([1, 1, 2, 2, 3]);
  assert.equal(s.size, 3);
});

// --- TestSetContains ---

test("contains_present", () => {
  const s = new Set_uint8([1, 2, 3]);
  assert.ok(s.contains(1));
});

test("contains_absent", () => {
  const s = new Set_uint8([1, 2, 3]);
  assert.ok(!s.contains(99));
});

// --- TestSetMutations ---

test("add", () => {
  const s = new Set_uint8([1, 2]);
  s.add(3);
  assert.equal(s.size, 3);
  assert.ok(s.contains(3));
});

test("add_duplicate", () => {
  const s = new Set_uint8([1, 2]);
  s.add(1);
  assert.equal(s.size, 2);
});

test("discard_present", () => {
  const s = new Set_uint8([1, 2, 3]);
  s.discard(2);
  assert.equal(s.size, 2);
  assert.ok(!s.contains(2));
});

test("discard_absent", () => {
  const s = new Set_uint8([1, 2, 3]);
  s.discard(99); // Should not raise
  assert.equal(s.size, 3);
});

test("remove_present", () => {
  const s = new Set_uint8([1, 2, 3]);
  s.remove(2);
  assert.equal(s.size, 2);
});

test("clear", () => {
  const s = new Set_uint8([1, 2, 3]);
  s.clear();
  assert.equal(s.size, 0);
});

test("pop", () => {
  const s = new Set_uint8([1, 2, 3]);
  const val = s.pop();
  assert.equal(s.size, 2);
  assert.ok([1, 2, 3].includes(val));
});

// --- TestSetOperations ---

test("union", () => {
  const s1 = new Set_uint8([1, 2]);
  const s2 = new Set_uint8([2, 3]);
  const result = s1.union(s2);
  assert.equal(result.size, 3);
});

test("union_operator", () => {
  const s1 = new Set_uint8([1, 2]);
  const s2 = new Set_uint8([2, 3]);
  const result = s1.union(s2);
  assert.equal(result.size, 3);
});

test("intersection", () => {
  const s1 = new Set_uint8([1, 2, 3]);
  const s2 = new Set_uint8([2, 3, 4]);
  const result = s1.intersection(s2);
  assert.equal(result.size, 2);
});

test("intersection_operator", () => {
  const s1 = new Set_uint8([1, 2, 3]);
  const s2 = new Set_uint8([2, 3, 4]);
  const result = s1.intersection(s2);
  assert.equal(result.size, 2);
});

test("difference", () => {
  const s1 = new Set_uint8([1, 2, 3]);
  const s2 = new Set_uint8([2, 3, 4]);
  const result = s1.difference(s2);
  assert.equal(result.size, 1);
  assert.ok(result.contains(1));
});

test("difference_operator", () => {
  const s1 = new Set_uint8([1, 2, 3]);
  const s2 = new Set_uint8([2, 3, 4]);
  const result = s1.difference(s2);
  assert.equal(result.size, 1);
});

test("symmetric_difference", () => {
  const s1 = new Set_uint8([1, 2, 3]);
  const s2 = new Set_uint8([2, 3, 4]);
  const result = s1.symmetricDifference(s2);
  assert.equal(result.size, 2);
});

test("issubset", () => {
  const s1 = new Set_uint8([1, 2]);
  const s2 = new Set_uint8([1, 2, 3]);
  assert.ok(s1.issubset(s2));
  assert.ok(!s2.issubset(s1));
});

test("issuperset", () => {
  const s1 = new Set_uint8([1, 2, 3]);
  const s2 = new Set_uint8([1, 2]);
  assert.ok(s1.issuperset(s2));
});

test("isdisjoint", () => {
  const s1 = new Set_uint8([1, 2]);
  const s2 = new Set_uint8([3, 4]);
  assert.ok(s1.isdisjoint(s2));
});

// --- TestSetWithKeys ---

test("set_of_keys", () => {
  const k1 = Test_ConceptAKey.create();
  const k2 = Test_ConceptAKey.create();
  const s = new Set_Test_ConceptAKey();
  s.add(k1);
  s.add(k2);
  assert.equal(s.size, 2);
  assert.ok(s.contains(k1));
});

// --- TestSetCopy ---

test("copy_creates_independent_set", () => {
  const s1 = new Set_uint8([1, 2, 3]);
  const s2 = s1.copy();
  assert.equal(s1.size, s2.size);
  s2.add(4);
  assert.equal(s1.size, 3);
  assert.equal(s2.size, 4);
});

test("copy_preserves_elements", () => {
  const s1 = new Set_uint8([10, 20, 30]);
  const s2 = s1.copy();
  assert.ok(s2.contains(10));
  assert.ok(s2.contains(20));
  assert.ok(s2.contains(30));
});

// --- TestSetUpdateOperations ---

test("update", () => {
  const s1 = new Set_uint8([1, 2]);
  const s2 = new Set_uint8([2, 3]);
  s1.update(s2);
  assert.equal(s1.size, 3);
  assert.ok(s1.contains(3));
});

test("difference_update", () => {
  const s1 = new Set_uint8([1, 2, 3]);
  const s2 = new Set_uint8([2, 3, 4]);
  s1.differenceUpdate(s2);
  assert.equal(s1.size, 1);
  assert.ok(s1.contains(1));
  assert.ok(!s1.contains(2));
});

test("intersection_update", () => {
  const s1 = new Set_uint8([1, 2, 3]);
  const s2 = new Set_uint8([2, 3, 4]);
  s1.intersectionUpdate(s2);
  assert.equal(s1.size, 2);
  assert.ok(s1.contains(2));
  assert.ok(s1.contains(3));
  assert.ok(!s1.contains(1));
  assert.ok(!s1.contains(4));
});

test("symmetric_difference_update", () => {
  const s1 = new Set_uint8([1, 2, 3]);
  const s2 = new Set_uint8([2, 3, 4]);
  s1.symmetricDifferenceUpdate(s2);
  assert.equal(s1.size, 2);
  assert.ok(s1.contains(1));
  assert.ok(s1.contains(4));
  assert.ok(!s1.contains(2));
});

// --- TestSetMinMax ---

test("min", () => {
  const s = new Set_uint8([3, 1, 2]);
  assert.equal(s.min(), 1);
});

test("max", () => {
  const s = new Set_uint8([3, 1, 2]);
  assert.equal(s.max(), 3);
});

// --- TestSetIteration ---

test("iter", () => {
  const s = new Set_uint8([1, 2, 3]);
  const values = [...s];
  assert.deepEqual(values.sort((a, b) => a - b), [1, 2, 3]);
});

test("iter_empty", () => {
  const s = new Set_uint8();
  const values = [...s];
  assert.deepEqual(values, []);
});

test("iter_multiple_times", () => {
  const s = new Set_uint8([10, 20, 30]);
  const list1 = [...s].sort((a, b) => a - b);
  const list2 = [...s].sort((a, b) => a - b);
  assert.deepEqual(list1, list2);
});

// --- TestSetGetitem ---

test("getitem", () => {
  const s = new Set_uint8([10, 20, 30]);
  // Sets are ordered, so getitem returns element at index
  const values = [];
  for (let i = 0; i < s.size; i++) {
    values.push(s.at(i));
  }
  assert.deepEqual(values.sort((a, b) => a - b), [10, 20, 30]);
});

// --- TestSetInPlaceOperators ---

test("ior_operator", () => {
  const s1 = new Set_uint8([1, 2]);
  const s2 = new Set_uint8([2, 3]);
  s1.update(s2);
  assert.equal(s1.size, 3);
  assert.ok(s1.contains(1));
  assert.ok(s1.contains(2));
  assert.ok(s1.contains(3));
});

test("iand_operator", () => {
  const s1 = new Set_uint8([1, 2, 3]);
  const s2 = new Set_uint8([2, 3, 4]);
  s1.intersectionUpdate(s2);
  assert.equal(s1.size, 2);
  assert.ok(s1.contains(2));
  assert.ok(s1.contains(3));
  assert.ok(!s1.contains(1));
  assert.ok(!s1.contains(4));
});

test("isub_operator", () => {
  const s1 = new Set_uint8([1, 2, 3]);
  const s2 = new Set_uint8([2, 3, 4]);
  s1.differenceUpdate(s2);
  assert.equal(s1.size, 1);
  assert.ok(s1.contains(1));
  assert.ok(!s1.contains(2));
});

test("ixor_operator", () => {
  const s1 = new Set_uint8([1, 2, 3]);
  const s2 = new Set_uint8([2, 3, 4]);
  s1.symmetricDifferenceUpdate(s2);
  assert.equal(s1.size, 2);
  assert.ok(s1.contains(1));
  assert.ok(s1.contains(4));
  assert.ok(!s1.contains(2));
});

// --- TestSetSerialization ---

test("encode_decode_roundtrip", () => {
  const s1 = new Set_uint8([1, 2, 3]);
  const blob = s1.encode();
  const s2 = Set_uint8.decode(blob);
  assert.equal(s2.size, 3);
  assert.ok(s2.contains(1));
  assert.ok(s2.contains(2));
  assert.ok(s2.contains(3));
});

test("encode_decode_empty", () => {
  const s1 = new Set_uint8();
  const blob = s1.encode();
  const s2 = Set_uint8.decode(blob);
  assert.equal(s2.size, 0);
});
