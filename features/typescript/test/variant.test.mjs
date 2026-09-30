import { test } from "node:test";
import { strict as assert } from "node:assert";
import dsviper from "@digitalsubstrate/dsviper";
import { StructureS } from "../generated/dist/demo/data.js";
import { Variant_of_string_or_uint8_or_Demo_StructureS } from "../generated/dist/containers.js";

// --- TestVariant ---

test("variant_string", () => {
  const v = new Variant_of_string_or_uint8_or_Demo_StructureS();
  v.setString("hello");
  assert.ok(v.isString());
  assert.equal(v.getString(), "hello");
});

test("variant_uint8", () => {
  const v = new Variant_of_string_or_uint8_or_Demo_StructureS();
  v.setUint8(42);
  assert.ok(v.isUint8());
  assert.equal(v.getUint8(), 42);
});

test("variant_structure", () => {
  const s = new StructureS({ f_float: 1.5, f_string: "test" });
  const v = new Variant_of_string_or_uint8_or_Demo_StructureS();
  v.setDemo_StructureS(s);
  assert.ok(v.isDemo_StructureS());
  const unwrapped = v.getDemo_StructureS();
  assert.ok(Math.abs(unwrapped.f_float - 1.5) < 1e-5);
});

// --- TestVariantConstruction ---

test("construct_with_string", () => {
  const v = new Variant_of_string_or_uint8_or_Demo_StructureS("hello");
  assert.ok(v.isString());
  assert.equal(v.getString(), "hello");
});

test("construct_with_uint8", () => {
  const v = new Variant_of_string_or_uint8_or_Demo_StructureS(new dsviper.ValueUInt8(42));
  assert.ok(v.isUint8());
  assert.equal(v.getUint8(), 42);
});

test("construct_with_structure", () => {
  const s = new StructureS({ f_float: 2.5, f_string: "world" });
  const v = new Variant_of_string_or_uint8_or_Demo_StructureS(s);
  assert.ok(v.isDemo_StructureS());
});

// --- TestVariantTypeChecking ---

test("is_string_false", () => {
  const v = new Variant_of_string_or_uint8_or_Demo_StructureS();
  v.setUint8(42);
  assert.ok(!v.isString());
});

test("is_uint8_false", () => {
  const v = new Variant_of_string_or_uint8_or_Demo_StructureS();
  v.setString("hello");
  assert.ok(!v.isUint8());
});

test("is_structure_false", () => {
  const v = new Variant_of_string_or_uint8_or_Demo_StructureS();
  v.setString("hello");
  assert.ok(!v.isDemo_StructureS());
});

// --- TestVariantSwitch ---

test("switch_from_string_to_uint8", () => {
  const v = new Variant_of_string_or_uint8_or_Demo_StructureS();
  v.setString("hello");
  assert.ok(v.isString());
  v.setUint8(42);
  assert.ok(v.isUint8());
  assert.ok(!v.isString());
});

test("switch_from_uint8_to_structure", () => {
  const v = new Variant_of_string_or_uint8_or_Demo_StructureS();
  v.setUint8(42);
  const s = new StructureS({ f_float: 1.0, f_string: "test" });
  v.setDemo_StructureS(s);
  assert.ok(v.isDemo_StructureS());
  assert.ok(!v.isUint8());
});

// --- TestVariantCopy ---

test("copy_string_variant", () => {
  const v1 = new Variant_of_string_or_uint8_or_Demo_StructureS();
  v1.setString("hello");
  const v2 = v1.copy();
  assert.ok(v2.isString());
  assert.equal(v2.getString(), "hello");
});

test("copy_uint8_variant", () => {
  const v1 = new Variant_of_string_or_uint8_or_Demo_StructureS();
  v1.setUint8(42);
  const v2 = v1.copy();
  assert.ok(v2.isUint8());
  assert.equal(v2.getUint8(), 42);
});

test("copy_structure_variant", () => {
  const s = new StructureS({ f_float: 1.5, f_string: "test" });
  const v1 = new Variant_of_string_or_uint8_or_Demo_StructureS();
  v1.setDemo_StructureS(s);
  const v2 = v1.copy();
  assert.ok(v2.isDemo_StructureS());
  assert.ok(Math.abs(v2.getDemo_StructureS().f_float - 1.5) < 1e-5);
});

test("copy_independent", () => {
  const v1 = new Variant_of_string_or_uint8_or_Demo_StructureS();
  v1.setString("hello");
  const v2 = v1.copy();
  v1.setUint8(99);
  assert.ok(v2.isString());
  assert.equal(v2.getString(), "hello");
});

// --- TestVariantSerialization ---

test("encode_decode_string", () => {
  const v1 = new Variant_of_string_or_uint8_or_Demo_StructureS();
  v1.setString("hello");
  const blob = v1.encode();
  const v2 = Variant_of_string_or_uint8_or_Demo_StructureS.decode(blob);
  assert.ok(v2.isString());
  assert.equal(v2.getString(), "hello");
});

test("encode_decode_uint8", () => {
  const v1 = new Variant_of_string_or_uint8_or_Demo_StructureS();
  v1.setUint8(42);
  const blob = v1.encode();
  const v2 = Variant_of_string_or_uint8_or_Demo_StructureS.decode(blob);
  assert.ok(v2.isUint8());
  assert.equal(v2.getUint8(), 42);
});

test("encode_decode_structure", () => {
  const s = new StructureS({ f_float: 2.5, f_string: "world" });
  const v1 = new Variant_of_string_or_uint8_or_Demo_StructureS();
  v1.setDemo_StructureS(s);
  const blob = v1.encode();
  const v2 = Variant_of_string_or_uint8_or_Demo_StructureS.decode(blob);
  assert.ok(v2.isDemo_StructureS());
  assert.equal(v2.getDemo_StructureS().f_string, "world");
});
