import { test } from "node:test";
import { strict as assert } from "node:assert";
import dsviper from "@digitalsubstrate/dsviper";
import {
  Vec_uint8_2,
  Mat_uint8_2_2, Mat_uint8_2_3,
  Tuple_uint8_string,
} from "../features/dist/index.js";

// =============================================================================
// Vec Tests
// =============================================================================

// --- TestVecConstruction ---

test("vec_default_construction", () => {
  const v = new Vec_uint8_2();
  assert.equal(v.size, 2);
});

test("vec_from_list", () => {
  const v = new Vec_uint8_2([10, 20]);
  assert.equal(v.size, 2);
  assert.equal(v.at(0), 10);
  assert.equal(v.at(1), 20);
});

test("vec_from_tuple", () => {
  const v = new Vec_uint8_2([5, 15]);
  assert.equal(v.at(0), 5);
  assert.equal(v.at(1), 15);
});

// --- TestVecAccess ---

test("vec_getitem", () => {
  const v = new Vec_uint8_2([10, 20]);
  assert.equal(v.at(0), 10);
  assert.equal(v.at(1), 20);
});

test("vec_setitem", () => {
  const v = new Vec_uint8_2([10, 20]);
  v.set(0, 99);
  assert.equal(v.at(0), 99);
  assert.equal(v.at(1), 20);
});

test("vec_setitem_all", () => {
  const v = new Vec_uint8_2([0, 0]);
  v.set(0, 100);
  v.set(1, 200);
  assert.equal(v.at(0), 100);
  assert.equal(v.at(1), 200);
});

// --- TestVecLen ---

test("vec_len_is_fixed", () => {
  const v = new Vec_uint8_2([10, 20]);
  assert.equal(v.size, 2);
});

test("vec_len_default", () => {
  const v = new Vec_uint8_2();
  assert.equal(v.size, 2);
});

// --- TestVecToTuple ---

test("vec_to_tuple", () => {
  const v = new Vec_uint8_2([10, 20]);
  const t = v.toTuple();
  assert.ok(Array.isArray(t));
  assert.deepEqual(t, [10, 20]);
});

test("vec_to_tuple_default_values", () => {
  const v = new Vec_uint8_2();
  const t = v.toTuple();
  assert.ok(Array.isArray(t));
  assert.equal(t.length, 2);
});

// --- TestVecCopy ---

test("vec_copy_creates_independent_vec", () => {
  const v1 = new Vec_uint8_2([10, 20]);
  const v2 = v1.copy();
  assert.equal(v2.at(0), 10);
  assert.equal(v2.at(1), 20);
  v2.set(0, 99);
  assert.equal(v1.at(0), 10);
  assert.equal(v2.at(0), 99);
});

test("vec_copy_preserves_values", () => {
  const v1 = new Vec_uint8_2([100, 200]);
  const v2 = v1.copy();
  assert.deepEqual(v2.toTuple(), [100, 200]);
});

// --- TestVecSerialization ---

test("vec_encode_decode_roundtrip", () => {
  const v1 = new Vec_uint8_2([10, 20]);
  const blob = v1.encode();
  const v2 = Vec_uint8_2.decode(blob);
  assert.equal(v2.at(0), 10);
  assert.equal(v2.at(1), 20);
});

test("vec_encode_decode_preserves_all", () => {
  const v1 = new Vec_uint8_2([255, 128]);
  const blob = v1.encode();
  const v2 = Vec_uint8_2.decode(blob);
  assert.deepEqual(v2.toTuple(), [255, 128]);
});

// =============================================================================
// Mat Tests
// =============================================================================

// --- TestMatConstruction ---

test("mat_default_construction_2x2", () => {
  const m = new Mat_uint8_2_2();
  // len returns total element count (2*2=4)
  assert.equal(m.size, 4);
});

test("mat_from_nested_list_2x2", () => {
  const m = new Mat_uint8_2_2([[1, 2], [3, 4]]);
  assert.equal(m.size, 4);
});

test("mat_default_construction_2x3", () => {
  const m = new Mat_uint8_2_3();
  // len returns total element count (2*3=6)
  assert.equal(m.size, 6);
});

test("mat_from_nested_list_2x3", () => {
  const m = new Mat_uint8_2_3([[1, 2, 3], [4, 5, 6]]);
  assert.equal(m.size, 6);
});

// --- TestMatAccessByRowIndex ---

test("mat_getitem_row_2x2", () => {
  const m = new Mat_uint8_2_2([[1, 2], [3, 4]]);
  const row0 = m.row(0);
  const row1 = m.row(1);
  assert.deepEqual(row0, [1, 2]);
  assert.deepEqual(row1, [3, 4]);
});

test("mat_getitem_row_2x3", () => {
  const m = new Mat_uint8_2_3([[1, 2, 3], [4, 5, 6]]);
  const row0 = m.row(0);
  const row1 = m.row(1);
  assert.deepEqual(row0, [1, 2, 3]);
  assert.deepEqual(row1, [4, 5, 6]);
});

// --- TestMatAccessByCoordinates ---

test("mat_getitem_coordinates_2x2", () => {
  const m = new Mat_uint8_2_2([[1, 2], [3, 4]]);
  assert.equal(m.at(0, 0), 1);
  assert.equal(m.at(0, 1), 2);
  assert.equal(m.at(1, 0), 3);
  assert.equal(m.at(1, 1), 4);
});

test("mat_getitem_coordinates_2x3", () => {
  const m = new Mat_uint8_2_3([[1, 2, 3], [4, 5, 6]]);
  assert.equal(m.at(0, 0), 1);
  assert.equal(m.at(0, 2), 3);
  assert.equal(m.at(1, 1), 5);
  assert.equal(m.at(1, 2), 6);
});

test("mat_setitem_coordinates_2x2", () => {
  const m = new Mat_uint8_2_2([[1, 2], [3, 4]]);
  m.set(0, 1, 99);
  assert.equal(m.at(0, 1), 99);
  assert.equal(m.at(0, 0), 1);
});

test("mat_setitem_coordinates_2x3", () => {
  const m = new Mat_uint8_2_3([[1, 2, 3], [4, 5, 6]]);
  m.set(1, 2, 99);
  assert.equal(m.at(1, 2), 99);
});

// --- TestMatSetRow ---

test("mat_setitem_row_2x2", () => {
  const m = new Mat_uint8_2_2([[1, 2], [3, 4]]);
  m.setRow(0, [10, 20]);
  assert.deepEqual(m.row(0), [10, 20]);
  assert.deepEqual(m.row(1), [3, 4]);
});

test("mat_setitem_row_2x3", () => {
  const m = new Mat_uint8_2_3([[1, 2, 3], [4, 5, 6]]);
  m.setRow(1, [40, 50, 60]);
  assert.deepEqual(m.row(1), [40, 50, 60]);
});

// --- TestMatLen ---

test("mat_len_2x2", () => {
  const m = new Mat_uint8_2_2();
  // 2x2 = 4 elements
  assert.equal(m.size, 4);
});

test("mat_len_2x3", () => {
  const m = new Mat_uint8_2_3();
  // 2x3 = 6 elements
  assert.equal(m.size, 6);
});

// --- TestMatToTuple ---

test("mat_to_tuple_2x2", () => {
  const m = new Mat_uint8_2_2([[1, 2], [3, 4]]);
  const t = m.toTuple();
  assert.ok(Array.isArray(t));
  assert.deepEqual(t, [[1, 2], [3, 4]]);
});

test("mat_to_tuple_2x3", () => {
  const m = new Mat_uint8_2_3([[1, 2, 3], [4, 5, 6]]);
  const t = m.toTuple();
  assert.deepEqual(t, [[1, 2, 3], [4, 5, 6]]);
});

// --- TestMatCopy ---

test("mat_copy_creates_independent_mat_2x2", () => {
  const m1 = new Mat_uint8_2_2([[1, 2], [3, 4]]);
  const m2 = m1.copy();
  m2.set(0, 0, 99);
  assert.equal(m1.at(0, 0), 1);
  assert.equal(m2.at(0, 0), 99);
});

test("mat_copy_preserves_values_2x3", () => {
  const m1 = new Mat_uint8_2_3([[1, 2, 3], [4, 5, 6]]);
  const m2 = m1.copy();
  assert.deepEqual(m2.toTuple(), [[1, 2, 3], [4, 5, 6]]);
});

// --- TestMatSerialization ---

test("mat_encode_decode_roundtrip_2x2", () => {
  const m1 = new Mat_uint8_2_2([[1, 2], [3, 4]]);
  const blob = m1.encode();
  const m2 = Mat_uint8_2_2.decode(blob);
  assert.deepEqual(m2.toTuple(), [[1, 2], [3, 4]]);
});

test("mat_encode_decode_roundtrip_2x3", () => {
  const m1 = new Mat_uint8_2_3([[10, 20, 30], [40, 50, 60]]);
  const blob = m1.encode();
  const m2 = Mat_uint8_2_3.decode(blob);
  assert.deepEqual(m2.toTuple(), [[10, 20, 30], [40, 50, 60]]);
});

// =============================================================================
// Tuple Tests
// =============================================================================

// --- TestTupleConstruction ---

test("tuple_default_construction", () => {
  const t = new Tuple_uint8_string();
  assert.equal(t.size, 2);
});

test("tuple_from_tuple", () => {
  const t = new Tuple_uint8_string([42, "hello"]);
  assert.equal(t.size, 2);
  assert.equal(t.at(0), 42);
  assert.equal(t.at(1), "hello");
});

test("tuple_from_list", () => {
  const t = new Tuple_uint8_string([100, "world"]);
  assert.equal(t.at(0), 100);
  assert.equal(t.at(1), "world");
});

// --- TestTupleLen ---

test("tuple_len_is_fixed", () => {
  const t = new Tuple_uint8_string([1, "a"]);
  assert.equal(t.size, 2);
});

// --- TestTupleGetitem ---

test("tuple_getitem_index_0", () => {
  const t = new Tuple_uint8_string([42, "hello"]);
  assert.equal(t.at(0), 42);
});

test("tuple_getitem_index_1", () => {
  const t = new Tuple_uint8_string([42, "hello"]);
  assert.equal(t.at(1), "hello");
});

test("tuple_getitem_out_of_range", () => {
  const t = new Tuple_uint8_string([42, "hello"]);
  assert.throws(() => {
    t.at(2);
  });
});

// --- TestTupleTypedGetters (no typed getters in TS; element access via at) ---

test("tuple_get_0", () => {
  const t = new Tuple_uint8_string([42, "hello"]);
  assert.equal(t.at(0), 42);
  assert.equal(typeof t.at(0), "number");
});

test("tuple_get_1", () => {
  const t = new Tuple_uint8_string([42, "hello"]);
  assert.equal(t.at(1), "hello");
  assert.equal(typeof t.at(1), "string");
});

// --- TestTupleIteration ---

test("tuple_iter", () => {
  const t = new Tuple_uint8_string([42, "hello"]);
  const values = [...t];
  assert.equal(values.length, 2);
  assert.equal(values[0], 42);
  assert.equal(values[1], "hello");
});

test("tuple_iter_unpacking", () => {
  const t = new Tuple_uint8_string([42, "hello"]);
  const [a, b] = t;
  assert.equal(a, 42);
  assert.equal(b, "hello");
});

test("tuple_iter_multiple_times", () => {
  const t = new Tuple_uint8_string([42, "hello"]);
  const list1 = [...t];
  const list2 = [...t];
  assert.deepEqual(list1, list2);
});

// --- TestTupleCopy ---

test("tuple_copy_creates_independent_tuple", () => {
  const t1 = new Tuple_uint8_string([42, "hello"]);
  const t2 = t1.copy();
  assert.equal(t2.at(0), 42);
  assert.equal(t2.at(1), "hello");
});

test("tuple_copy_preserves_values", () => {
  const t1 = new Tuple_uint8_string([255, "test"]);
  const t2 = t1.copy();
  assert.equal(t2.at(0), 255);
  assert.equal(t2.at(1), "test");
});

// --- TestTupleSerialization ---

test("tuple_encode_decode_roundtrip", () => {
  const t1 = new Tuple_uint8_string([42, "hello"]);
  const blob = t1.encode();
  const t2 = Tuple_uint8_string.decode(blob);
  assert.equal(t2.at(0), 42);
  assert.equal(t2.at(1), "hello");
});

test("tuple_encode_decode_special_chars", () => {
  const t1 = new Tuple_uint8_string([0, "héllo wörld"]);
  const blob = t1.encode();
  const t2 = Tuple_uint8_string.decode(blob);
  assert.equal(t2.at(1), "héllo wörld");
});

test("tuple_encode_decode_empty_string", () => {
  const t1 = new Tuple_uint8_string([128, ""]);
  const blob = t1.encode();
  const t2 = Tuple_uint8_string.decode(blob);
  assert.equal(t2.at(0), 128);
  assert.equal(t2.at(1), "");
});

// --- TestTupleComparison ---

test("tuple_equal_tuples", () => {
  const t1 = new Tuple_uint8_string([42, "hello"]);
  const t2 = new Tuple_uint8_string([42, "hello"]);
  assert.ok(t1.equals(t2));
});

test("tuple_not_equal_tuples", () => {
  const t1 = new Tuple_uint8_string([42, "hello"]);
  const t2 = new Tuple_uint8_string([42, "world"]);
  assert.ok(!t1.equals(t2));
});

test("tuple_not_equal_different_first", () => {
  const t1 = new Tuple_uint8_string([1, "hello"]);
  const t2 = new Tuple_uint8_string([2, "hello"]);
  assert.ok(!t1.equals(t2));
});
