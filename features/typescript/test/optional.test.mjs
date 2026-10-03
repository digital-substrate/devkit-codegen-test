import { test } from "node:test";
import { strict as assert } from "node:assert";
import dsviper from "@digitalsubstrate/dsviper";
import { definitions } from "../generated/dist/index.js";
import { StructureT } from "../generated/dist/demo/data.js";
import { Optional_of_uint8, Optional_of_int8, Optional_of_Demo_StructureT } from "../generated/dist/containers.js";

// --- TestOptionalNil ---

test("default_is_nil", () => {
  const opt = new Optional_of_uint8();
  assert.ok(opt.isNil());
});

test("none_is_nil", () => {
  const opt = new Optional_of_uint8(null);
  assert.ok(opt.isNil());
});

test("bool_false_when_nil", () => {
  const opt = new Optional_of_uint8();
  assert.ok(!(!opt.isNil()));
});

// --- TestOptionalValue ---

test("wrap_value", () => {
  const opt = new Optional_of_uint8(42);
  assert.ok(!opt.isNil());
  assert.equal(opt.unwrap(), 42);
});

test("bool_true_when_has_value", () => {
  const opt = new Optional_of_uint8(42);
  assert.ok(!opt.isNil());
});

test("get_with_value", () => {
  const opt = new Optional_of_uint8(42);
  assert.equal(opt.get(), 42);
});

test("get_with_default_when_has_value", () => {
  const opt = new Optional_of_uint8(42);
  assert.equal(opt.get(99), 42);
});

test("get_with_default_when_nil", () => {
  const opt = new Optional_of_int8();
  assert.equal(opt.get(99), 99);
});

test("get_without_default_when_nil_throws", () => {
  assert.throws(() => new Optional_of_int8().get());
});

test("wrap_method", () => {
  const opt = new Optional_of_uint8();
  opt.wrap(123);
  assert.ok(!opt.isNil());
  assert.equal(opt.unwrap(), 123);
});

// --- TestOptionalStructure ---

test("optional_structure_nil", () => {
  const opt = new Optional_of_Demo_StructureT();
  assert.ok(opt.isNil());
});

test("optional_structure_value", () => {
  const s = new StructureT();
  s.field_string = "test";
  const opt = new Optional_of_Demo_StructureT(s);
  assert.ok(!opt.isNil());
  const unwrapped = opt.unwrap();
  assert.equal(unwrapped.field_string, "test");
});

// --- TestOptionalCopy ---

test("copy_preserves_value", () => {
  const opt1 = new Optional_of_uint8(42);
  const opt2 = opt1.copy();
  assert.equal(opt2.unwrap(), 42);
});

test("copy_independent", () => {
  const opt1 = new Optional_of_uint8(42);
  const opt2 = opt1.copy();
  opt1.wrap(99);
  assert.equal(opt2.unwrap(), 42);
});

// --- TestOptionalSerialization ---

test("encode_decode_value", () => {
  const opt1 = new Optional_of_uint8(42);
  const blob = dsviper.Value.encode(opt1.unwrapValue());
  const opt2 = new Optional_of_uint8(dsviper.Value.decode(blob, Optional_of_uint8.type(), definitions()));
  assert.ok(!opt2.isNil());
  assert.equal(opt2.unwrap(), 42);
});

test("encode_decode_nil", () => {
  const opt1 = new Optional_of_uint8();
  const blob = dsviper.Value.encode(opt1.unwrapValue());
  const opt2 = new Optional_of_uint8(dsviper.Value.decode(blob, Optional_of_uint8.type(), definitions()));
  assert.ok(opt2.isNil());
});
