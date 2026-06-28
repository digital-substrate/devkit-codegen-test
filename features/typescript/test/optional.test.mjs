import { test } from "node:test";
import { strict as assert } from "node:assert";
import dsviper from "@digitalsubstrate/dsviper";
import {
  Optional_uint8, Optional_int8, Optional_Test_StructureT,
  Test_StructureT,
} from "../features/dist/index.js";

// --- TestOptionalNil ---

test("default_is_nil", () => {
  const opt = new Optional_uint8();
  assert.ok(opt.isNil());
});

test("none_is_nil", () => {
  const opt = new Optional_uint8(null);
  assert.ok(opt.isNil());
});

test("bool_false_when_nil", () => {
  const opt = new Optional_uint8();
  assert.ok(!(!opt.isNil()));
});

// --- TestOptionalValue ---

test("wrap_value", () => {
  const opt = new Optional_uint8(42);
  assert.ok(!opt.isNil());
  assert.equal(opt.unwrap(), 42);
});

test("bool_true_when_has_value", () => {
  const opt = new Optional_uint8(42);
  assert.ok(!opt.isNil());
});

test("get_with_value", () => {
  const opt = new Optional_uint8(42);
  assert.equal(opt.get(), 42);
});

test("get_with_default_when_has_value", () => {
  const opt = new Optional_uint8(42);
  assert.equal(opt.get(99), 42);
});

test("get_with_default_when_nil", () => {
  const opt = new Optional_int8();
  assert.equal(opt.get(99), 99);
});

test("wrap_method", () => {
  const opt = new Optional_uint8();
  opt.wrap(123);
  assert.ok(!opt.isNil());
  assert.equal(opt.unwrap(), 123);
});

// --- TestOptionalStructure ---

test("optional_structure_nil", () => {
  const opt = new Optional_Test_StructureT();
  assert.ok(opt.isNil());
});

test("optional_structure_value", () => {
  const s = new Test_StructureT();
  s.field_string = "test";
  const opt = new Optional_Test_StructureT(s);
  assert.ok(!opt.isNil());
  const unwrapped = opt.unwrap();
  assert.equal(unwrapped.field_string, "test");
});

// --- TestOptionalCopy ---

test("copy_preserves_value", () => {
  const opt1 = new Optional_uint8(42);
  const opt2 = opt1.copy();
  assert.equal(opt2.unwrap(), 42);
});

test("copy_independent", () => {
  const opt1 = new Optional_uint8(42);
  const opt2 = opt1.copy();
  opt1.wrap(99);
  assert.equal(opt2.unwrap(), 42);
});

// --- TestOptionalSerialization ---

test("encode_decode_value", () => {
  const opt1 = new Optional_uint8(42);
  const blob = opt1.encode();
  const opt2 = Optional_uint8.decode(blob);
  assert.ok(!opt2.isNil());
  assert.equal(opt2.unwrap(), 42);
});

test("encode_decode_nil", () => {
  const opt1 = new Optional_uint8();
  const blob = opt1.encode();
  const opt2 = Optional_uint8.decode(blob);
  assert.ok(opt2.isNil());
});
