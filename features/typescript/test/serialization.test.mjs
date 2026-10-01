// Tests for Kibo-generated encode/decode serialization.
import { test } from "node:test";
import { strict as assert } from "node:assert";
import dsviper from "@digitalsubstrate/dsviper";
import { definitions } from "../generated/dist/index.js";
import { ConceptAKey, ConceptBKey, StructureS, StructureT, StructureV } from "../generated/dist/demo/data.js";
import { Optional_of_uint8, Vector_of_uint8, Set_of_uint8, Map_of_int8_to_string } from "../generated/dist/containers.js";
import { AnyConceptKey } from "../generated/dist/_codegen/registry.js";

// --- key encode/decode roundtrip ---

test("ConceptAKey: encode/decode roundtrip", () => {
  const key1 = ConceptAKey.create();
  const blob = dsviper.Value.encode(key1.vprValue);
  const key2 = ConceptAKey.wrap(dsviper.Value.decode(blob, ConceptAKey.type(), definitions()));
  assert.ok(key1.equals(key2));
});

test("ConceptBKey: encode/decode roundtrip", () => {
  const key1 = ConceptBKey.create();
  const blob = dsviper.Value.encode(key1.vprValue);
  const key2 = ConceptBKey.wrap(dsviper.Value.decode(blob, ConceptBKey.type(), definitions()));
  assert.ok(key1.equals(key2));
});

test("AnyConceptKey: encode/decode roundtrip", () => {
  const key = ConceptAKey.create();
  const anyKey1 = key.toAnyConceptKey();
  const blob = dsviper.Value.encode(anyKey1.vprValue);
  const anyKey2 = AnyConceptKey.wrap(dsviper.Value.decode(blob, AnyConceptKey.type(), definitions()));
  assert.ok(anyKey1.equals(anyKey2));
});

// --- structure encode/decode roundtrip ---

test("StructureS: encode/decode roundtrip", () => {
  const s1 = new StructureS({ f_float: 3.14, f_string: "hello" });
  const blob = dsviper.Value.encode(s1.vprValue);
  const s2 = StructureS.wrap(dsviper.Value.decode(blob, StructureS.type(), definitions()));
  assert.ok(Math.abs(s1.f_float - s2.f_float) < 1e-5);
  assert.equal(s1.f_string, s2.f_string);
});

test("StructureT: encode/decode roundtrip", () => {
  const inner = new StructureS({ f_float: 1.5, f_string: "inner" });
  const t1 = new StructureT();
  t1.field_string = "outer";
  t1.field_structure_s = inner;

  const blob = dsviper.Value.encode(t1.vprValue);
  const t2 = StructureT.wrap(dsviper.Value.decode(blob, StructureT.type(), definitions()));

  assert.equal(t1.field_string, t2.field_string);
  assert.ok(Math.abs(t1.field_structure_s.f_float - t2.field_structure_s.f_float) < 1e-5);
});

test("StructureV: encode/decode roundtrip", () => {
  const v1 = new StructureV();
  v1.f_bool = true;
  v1.f_uint8 = 255;
  v1.f_string = "test";

  const blob = dsviper.Value.encode(v1.vprValue);
  const v2 = StructureV.wrap(dsviper.Value.decode(blob, StructureV.type(), definitions()));

  assert.equal(v1.f_bool, v2.f_bool);
  assert.equal(v1.f_uint8, v2.f_uint8);
  assert.equal(v1.f_string, v2.f_string);
});

// --- container encode/decode roundtrip ---

test("Optional: nil roundtrip", () => {
  const opt1 = new Optional_of_uint8();
  const blob = dsviper.Value.encode(opt1.vprValue);
  const opt2 = new Optional_of_uint8(dsviper.Value.decode(blob, Optional_of_uint8.type(), definitions()));
  assert.ok(opt2.isNil());
});

test("Optional: value roundtrip", () => {
  const opt1 = new Optional_of_uint8(42);
  const blob = dsviper.Value.encode(opt1.vprValue);
  const opt2 = new Optional_of_uint8(dsviper.Value.decode(blob, Optional_of_uint8.type(), definitions()));
  assert.ok(!opt2.isNil());
  assert.equal(opt2.unwrap(), 42);
});

test("Vector: roundtrip", () => {
  const v1 = new Vector_of_uint8([1, 2, 3, 4, 5]);
  const blob = dsviper.Value.encode(v1.vprValue);
  const v2 = new Vector_of_uint8(dsviper.Value.decode(blob, Vector_of_uint8.type(), definitions()));
  assert.deepEqual([...v1], [...v2]);
});

test("Set: roundtrip", () => {
  const s1 = new Set_of_uint8([1, 2, 3]);
  const blob = dsviper.Value.encode(s1.vprValue);
  const s2 = new Set_of_uint8(dsviper.Value.decode(blob, Set_of_uint8.type(), definitions()));
  assert.equal(s1.size, s2.size);
  for (const x of s1) {
    assert.ok(s2.has(x));
  }
});

test("Map: roundtrip", () => {
  const m1 = new Map_of_int8_to_string([[1, "one"], [2, "two"], [3, "three"]]);
  const blob = dsviper.Value.encode(m1.vprValue);
  const m2 = new Map_of_int8_to_string(dsviper.Value.decode(blob, Map_of_int8_to_string.type(), definitions()));
  assert.equal(m1.at(1), m2.at(1));
  assert.equal(m1.at(2), m2.at(2));
  assert.equal(m1.at(3), m2.at(3));
});

// --- hexdigest for content hashing ---

test("Key: hexdigest is a non-empty string", () => {
  const key = ConceptAKey.create();
  const digest = dsviper.Value.hexdigest(key.vprValue);
  assert.equal(typeof digest, "string");
  assert.ok(digest.length > 0);
});

test("Key: same key same digest", () => {
  const uuidStr = "12345678-1234-1234-1234-123456789abc";
  const key1 = new ConceptAKey(uuidStr);
  const key2 = new ConceptAKey(uuidStr);
  assert.equal(dsviper.Value.hexdigest(key1.vprValue), dsviper.Value.hexdigest(key2.vprValue));
});

test("Key: different key different digest", () => {
  const key1 = ConceptAKey.create();
  const key2 = ConceptAKey.create();
  assert.notEqual(dsviper.Value.hexdigest(key1.vprValue), dsviper.Value.hexdigest(key2.vprValue));
});

test("Structure: hexdigest is a non-empty string", () => {
  const s = new StructureS({ f_float: 1.0, f_string: "test" });
  const digest = dsviper.Value.hexdigest(s.vprValue);
  assert.equal(typeof digest, "string");
  assert.ok(digest.length > 0);
});

test("Structure: same structure same digest", () => {
  const s1 = new StructureS({ f_float: 1.0, f_string: "test" });
  const s2 = new StructureS({ f_float: 1.0, f_string: "test" });
  assert.equal(dsviper.Value.hexdigest(s1.vprValue), dsviper.Value.hexdigest(s2.vprValue));
});

// --- stream codec instancing options ---

test("Codec: binary codec", () => {
  const s1 = new StructureS({ f_float: 1.5, f_string: "binary" });
  const blob = dsviper.Value.encode(s1.vprValue, dsviper.Codec.STREAM_BINARY);
  const s2 = StructureS.wrap(dsviper.Value.decode(blob, StructureS.type(), definitions(), dsviper.Codec.STREAM_BINARY));
  assert.equal(s1.f_string, s2.f_string);
});

test("Codec: raw codec", () => {
  const s1 = new StructureS({ f_float: 1.5, f_string: "raw" });
  const blob = dsviper.Value.encode(s1.vprValue, dsviper.Codec.STREAM_RAW);
  const s2 = StructureS.wrap(dsviper.Value.decode(blob, StructureS.type(), definitions(), dsviper.Codec.STREAM_RAW));
  assert.equal(s1.f_string, s2.f_string);
});

// --- pack_sized option for structures ---

test("Structure: pack sized decode", () => {
  const s1 = new StructureS({ f_float: 2.5, f_string: "pack" });
  const blob = dsviper.Value.encode(s1.vprValue);
  const s2 = StructureS.wrap(dsviper.Value.decode(blob, StructureS.type(), definitions()));
  assert.equal(s1.f_string, s2.f_string);
});

// --- vpr_value can be encoded directly ---

test("Key: vprValue encode", () => {
  const key = ConceptAKey.create();
  const vpr = key.vprValue;
  const blob = dsviper.Value.encode(vpr);
  assert.ok(blob instanceof dsviper.ValueBlob);
});

// --- blob content properties ---

test("Blob: is not empty", () => {
  const key = ConceptAKey.create();
  const blob = dsviper.Value.encode(key.vprValue);
  assert.ok(blob.size() > 0);
});

test("Blob: content differs by value", () => {
  const key1 = ConceptAKey.create();
  const key2 = ConceptAKey.create();
  const blob1 = dsviper.Value.encode(key1.vprValue);
  const blob2 = dsviper.Value.encode(key2.vprValue);
  assert.notEqual(blob1.base64Encode(), blob2.base64Encode());
});
