// Tests for Kibo-generated XArray proxy classes.
//
// XArray is an extended array with stable position-based addressing using UUIDs.
// Elements can be accessed by index (int) or by position (UUID), and positions
// remain stable across insertions and deletions.

import { test } from "node:test";
import { strict as assert } from "node:assert";
import dsviper from "@digitalsubstrate/dsviper";
import { XArray_int8, XArray_uint8, Vector_int8, Vector_uint8 } from "../features/dist/index.js";

// --- Construction ---

test("empty_xarray", () => {
  const xa = new XArray_int8();
  assert.equal(xa.size, 0);
});

test("xarray_from_list", () => {
  const xa = new XArray_int8([1, 2, 3, 4, 5]);
  assert.equal(xa.size, 5);
});

test("xarray_from_empty_list", () => {
  const xa = new XArray_int8([]);
  assert.equal(xa.size, 0);
});

// --- Index access ---

test("getitem_by_index", () => {
  const xa = new XArray_int8([10, 20, 30]);
  assert.equal(xa.get(0), 10);
  assert.equal(xa.get(1), 20);
  assert.equal(xa.get(2), 30);
});

test("setitem_by_index", () => {
  const xa = new XArray_int8([10, 20, 30]);
  xa.set(1, 99);
  assert.equal(xa.get(1), 99);
});

test("negative_index_not_supported", () => {
  // XArray does not support negative indexing like Python lists.
  const xa = new XArray_int8([10, 20, 30]);
  // Negative indices return undefined in XArray.
  assert.equal(xa.get(-1), undefined);
});

// --- Position (UUID) access ---

test("getitem_by_position", () => {
  const xa = new XArray_int8([10, 20, 30]);
  const pos = xa.position(1);
  assert.notEqual(pos, undefined);
  assert.equal(xa.get(pos), 20);
});

test("setitem_by_position", () => {
  const xa = new XArray_int8([10, 20, 30]);
  const pos = xa.position(1);
  xa.set(pos, 99);
  assert.equal(xa.get(pos), 99);
  assert.equal(xa.get(1), 99);
});

// --- Contains ---

test("contains_present", () => {
  const xa = new XArray_int8([10, 20, 30]);
  assert.ok(xa.contains(20));
});

test("contains_absent", () => {
  const xa = new XArray_int8([10, 20, 30]);
  assert.ok(!xa.contains(99));
});

test("contains_empty", () => {
  const xa = new XArray_int8();
  assert.ok(!xa.contains(10));
});

// --- Positions ---

test("positions_returns_list", () => {
  const xa = new XArray_int8([10, 20, 30]);
  const positions = xa.positions();
  // XArray includes END position, so 3 elements = 4 positions.
  assert.equal(positions.length, 4);
  assert.ok(positions[0] instanceof dsviper.ValueUUId);
});

test("positions_empty_xarray", () => {
  const xa = new XArray_int8();
  const positions = xa.positions();
  // Even empty XArray has END position.
  assert.equal(positions.length, 1);
});

test("position_index_roundtrip", () => {
  const xa = new XArray_int8([10, 20, 30]);
  for (let i = 0; i < 3; i++) {
    const pos = xa.position(i);
    assert.notEqual(pos, undefined);
    const idx = xa.index(pos);
    assert.equal(idx, i);
  }
});

test("has_position_true", () => {
  const xa = new XArray_int8([10, 20, 30]);
  const pos = xa.position(1);
  assert.ok(xa.hasPosition(pos));
});

test("has_position_false", () => {
  const xa = new XArray_int8([10, 20, 30]);
  const newPos = XArray_int8.createPosition();
  assert.ok(!xa.hasPosition(newPos));
});

test("position_invalid_index", () => {
  const xa = new XArray_int8([10, 20, 30]);
  const pos = xa.position(99);
  assert.equal(pos, undefined);
});

// --- items() ---

test("items_returns_position_value_pairs", () => {
  const xa = new XArray_int8([10, 20, 30]);
  const items = xa.items();
  assert.equal(items.length, 3);
  for (const [pos] of items) {
    assert.ok(pos instanceof dsviper.ValueUUId);
  }
  const values = items.map(([, v]) => v);
  assert.deepEqual(values, [10, 20, 30]);
});

test("items_empty", () => {
  const xa = new XArray_int8();
  const items = xa.items();
  assert.equal(items.length, 0);
});

// --- at() ---

test("at_valid_position", () => {
  const xa = new XArray_int8([10, 20, 30]);
  const pos = xa.position(1);
  assert.equal(xa.at(pos), 20);
});

test("at_invalid_position_raises", () => {
  // Accessing a never-existed position throws ViperError.
  const xa = new XArray_int8([10, 20, 30]);
  const invalidPos = XArray_int8.createPosition();
  assert.throws(() => xa.at(invalidPos));
});

// --- set() by position ---

test("set_value_at_position", () => {
  const xa = new XArray_int8([10, 20, 30]);
  const pos = xa.position(1);
  xa.set(pos, 99);
  assert.equal(xa.at(pos), 99);
  assert.equal(xa.get(1), 99);
});

// --- append() ---

test("append_to_empty", () => {
  const xa = new XArray_int8();
  xa.append(42);
  assert.equal(xa.size, 1);
  assert.equal(xa.get(0), 42);
});

test("append_multiple", () => {
  const xa = new XArray_int8();
  xa.append(1);
  xa.append(2);
  xa.append(3);
  assert.equal(xa.size, 3);
  assert.equal(xa.get(0), 1);
  assert.equal(xa.get(1), 2);
  assert.equal(xa.get(2), 3);
});

test("append_to_existing", () => {
  const xa = new XArray_int8([10, 20]);
  xa.append(30);
  assert.equal(xa.size, 3);
  assert.equal(xa.get(2), 30);
});

// --- insert() ---

test("insert_at_beginning", () => {
  const xa = new XArray_int8([20, 30]);
  const firstPos = xa.position(0);
  xa.insert(firstPos, 10);
  assert.equal(xa.size, 3);
  assert.equal(xa.get(0), 10);
  assert.equal(xa.get(1), 20);
  assert.equal(xa.get(2), 30);
});

test("insert_at_end", () => {
  const xa = new XArray_int8([10, 20]);
  const endPos = XArray_int8.end();
  xa.insert(endPos, 30);
  assert.equal(xa.size, 3);
  assert.equal(xa.get(2), 30);
});

test("insert_in_middle", () => {
  const xa = new XArray_int8([10, 30]);
  const pos30 = xa.position(1);
  xa.insert(pos30, 20);
  assert.equal(xa.size, 3);
  assert.equal(xa.get(0), 10);
  assert.equal(xa.get(1), 20);
  assert.equal(xa.get(2), 30);
});

test("insert_with_explicit_position", () => {
  const xa = new XArray_int8([10, 30]);
  const newPos = XArray_int8.createPosition();
  const pos30 = xa.position(1);
  xa.insert(pos30, 20, newPos);
  assert.equal(xa.size, 3);
  assert.ok(xa.hasPosition(newPos));
  assert.equal(xa.at(newPos), 20);
});

// --- remove() ---

test("remove_by_position", () => {
  const xa = new XArray_int8([10, 20, 30]);
  const pos = xa.position(1);
  xa.remove(pos);
  assert.equal(xa.size, 2);
  assert.equal(xa.get(0), 10);
  assert.equal(xa.get(1), 30);
});

test("remove_first", () => {
  const xa = new XArray_int8([10, 20, 30]);
  const pos = xa.position(0);
  xa.remove(pos);
  assert.equal(xa.size, 2);
  assert.equal(xa.get(0), 20);
});

test("remove_last", () => {
  const xa = new XArray_int8([10, 20, 30]);
  const pos = xa.position(2);
  xa.remove(pos);
  assert.equal(xa.size, 2);
  assert.equal(xa.get(1), 20);
});

test("removed_position_returns_none", () => {
  // After remove, position still exists but at() returns undefined.
  const xa = new XArray_int8([10, 20, 30]);
  const pos = xa.position(1);
  assert.notEqual(pos, undefined);
  xa.remove(pos);
  // Position still exists but value is undefined.
  assert.ok(xa.hasPosition(pos));
  assert.equal(xa.at(pos), undefined);
});

// --- positionOf() ---

test("position_of_existing", () => {
  const xa = new XArray_int8([10, 20, 30]);
  const pos = xa.positionOf(20);
  assert.notEqual(pos, undefined);
  assert.equal(xa.at(pos), 20);
});

test("position_of_first_occurrence", () => {
  const xa = new XArray_int8([10, 20, 20, 30]);
  const pos = xa.positionOf(20);
  assert.notEqual(pos, undefined);
  const idx = xa.index(pos);
  assert.equal(idx, 1);
});

test("position_of_absent", () => {
  const xa = new XArray_int8([10, 20, 30]);
  const pos = xa.positionOf(99);
  assert.equal(pos, undefined);
});

// --- insertPosition() ---

test("insert_position_then_set", () => {
  const xa = new XArray_int8([10, 30]);
  const newPos = XArray_int8.createPosition();
  const pos30 = xa.position(1);
  xa.insertPosition(pos30, newPos);
  assert.ok(xa.hasPosition(newPos));
  xa.set(newPos, 20);
  assert.equal(xa.at(newPos), 20);
});

// --- disablePosition() ---

test("disable_position_removes_value", () => {
  // disablePosition removes the value but keeps position valid.
  const xa = new XArray_int8([10, 20, 30]);
  const pos = xa.position(1);
  assert.notEqual(pos, undefined);
  xa.disablePosition(pos);
  // Position still exists but value is removed.
  assert.equal(xa.size, 2);
  // The values should now be [10, 30].
  assert.equal(xa.get(0), 10);
  assert.equal(xa.get(1), 30);
});

// --- static methods ---

test("end_returns_uuid", () => {
  const endPos = XArray_int8.end();
  assert.ok(endPos instanceof dsviper.ValueUUId);
});

test("create_position_returns_uuid", () => {
  const pos = XArray_int8.createPosition();
  assert.ok(pos instanceof dsviper.ValueUUId);
});

test("create_position_unique", () => {
  const pos1 = XArray_int8.createPosition();
  const pos2 = XArray_int8.createPosition();
  assert.ok(!pos1.equals(pos2));
});

// --- copy ---

test("copy_creates_independent_xarray", () => {
  const xa1 = new XArray_int8([10, 20, 30]);
  const xa2 = xa1.copy();
  assert.equal(xa1.size, xa2.size);
  xa2.append(40);
  assert.equal(xa1.size, 3);
  assert.equal(xa2.size, 4);
});

test("copy_preserves_values", () => {
  const xa1 = new XArray_int8([10, 20, 30]);
  const xa2 = xa1.copy();
  assert.equal(xa2.get(0), 10);
  assert.equal(xa2.get(1), 20);
  assert.equal(xa2.get(2), 30);
});

test("copy_mutation_independent", () => {
  const xa1 = new XArray_int8([10, 20, 30]);
  const xa2 = xa1.copy();
  xa1.set(1, 99);
  assert.equal(xa1.get(1), 99);
  assert.equal(xa2.get(1), 20);
});

// --- toVector() ---

test("to_vector_preserves_values", () => {
  const xa = new XArray_int8([10, 20, 30]);
  const v = xa.toVector();
  assert.ok(v instanceof Vector_int8);
  assert.equal(v.size, 3);
  assert.deepEqual([...v], [10, 20, 30]);
});

test("to_vector_empty", () => {
  const xa = new XArray_int8();
  const v = xa.toVector();
  assert.equal(v.size, 0);
});

test("to_vector_uint8", () => {
  const xa = new XArray_uint8([1, 2, 3]);
  const v = xa.toVector();
  assert.ok(v instanceof Vector_uint8);
  assert.deepEqual([...v], [1, 2, 3]);
});

// --- position stability ---

test("position_stable_after_insert", () => {
  const xa = new XArray_int8([10, 30]);
  const pos30 = xa.position(1);
  const originalValue = xa.at(pos30);
  xa.insert(pos30, 20);
  assert.equal(xa.at(pos30), originalValue);
});

test("position_stable_after_append", () => {
  const xa = new XArray_int8([10, 20]);
  const pos20 = xa.position(1);
  xa.append(30);
  assert.equal(xa.at(pos20), 20);
});

test("position_stable_after_remove_other", () => {
  const xa = new XArray_int8([10, 20, 30]);
  const pos10 = xa.position(0);
  const pos30 = xa.position(2);
  xa.remove(xa.position(1));
  assert.equal(xa.at(pos10), 10);
  assert.equal(xa.at(pos30), 30);
});

// --- XArray_uint8 variant ---

test("uint8_construction", () => {
  const xa = new XArray_uint8([1, 2, 3]);
  assert.equal(xa.size, 3);
  assert.equal(xa.get(0), 1);
});

test("uint8_append", () => {
  const xa = new XArray_uint8();
  xa.append(255);
  assert.equal(xa.get(0), 255);
});

test("uint8_copy", () => {
  const xa1 = new XArray_uint8([100, 200]);
  const xa2 = xa1.copy();
  assert.equal(xa2.get(0), 100);
  assert.equal(xa2.get(1), 200);
});

// --- serialization ---

test("encode_decode_roundtrip", () => {
  const xa1 = new XArray_int8([10, 20, 30]);
  const blob = xa1.encode();
  const xa2 = XArray_int8.decode(blob);
  assert.equal(xa2.size, 3);
  assert.equal(xa2.get(0), 10);
  assert.equal(xa2.get(1), 20);
  assert.equal(xa2.get(2), 30);
});

test("encode_decode_empty", () => {
  const xa1 = new XArray_int8();
  const blob = xa1.encode();
  const xa2 = XArray_int8.decode(blob);
  assert.equal(xa2.size, 0);
});

test("encode_decode_uint8", () => {
  const xa1 = new XArray_uint8([1, 128, 255]);
  const blob = xa1.encode();
  const xa2 = XArray_uint8.decode(blob);
  assert.deepEqual([...xa2.toVector()], [1, 128, 255]);
});

test("encode_decode_preserves_positions", () => {
  const xa1 = new XArray_int8([10, 20, 30]);
  const pos1Original = xa1.positions();
  const blob = xa1.encode();
  const xa2 = XArray_int8.decode(blob);
  const pos2 = xa2.positions();
  assert.equal(pos1Original.length, pos2.length);
  for (let i = 0; i < pos1Original.length; i++) {
    assert.ok(pos1Original[i].equals(pos2[i]));
  }
});
