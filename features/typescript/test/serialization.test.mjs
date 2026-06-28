// Tests for Kibo-generated encode/decode serialization.
import { test } from "node:test";
import { strict as assert } from "node:assert";
import dsviper from "@digitalsubstrate/dsviper";
import {
  Test_ConceptAKey, Test_ConceptBKey,
  Test_StructureS, Test_StructureT, Test_StructureV,
  Optional_uint8, Vector_uint8, Set_uint8, Map_int8_to_string,
  AnyConceptKey,
} from "../features/dist/index.js";

// --- key encode/decode roundtrip ---

test("ConceptAKey: encode/decode roundtrip", () => {
  const key1 = Test_ConceptAKey.create();
  const blob = key1.encode();
  const key2 = Test_ConceptAKey.decode(blob);
  assert.ok(key1.equals(key2));
});

test("ConceptBKey: encode/decode roundtrip", () => {
  const key1 = Test_ConceptBKey.create();
  const blob = key1.encode();
  const key2 = Test_ConceptBKey.decode(blob);
  assert.ok(key1.equals(key2));
});

test("AnyConceptKey: encode/decode roundtrip", () => {
  const key = Test_ConceptAKey.create();
  const anyKey1 = key.toAnyConceptKey();
  const blob = anyKey1.encode();
  const anyKey2 = AnyConceptKey.decode(blob);
  assert.ok(anyKey1.equals(anyKey2));
});

// --- structure encode/decode roundtrip ---

test("StructureS: encode/decode roundtrip", () => {
  const s1 = new Test_StructureS({ f_float: 3.14, f_string: "hello" });
  const blob = s1.encode();
  const s2 = Test_StructureS.decode(blob);
  assert.ok(Math.abs(s1.f_float - s2.f_float) < 1e-5);
  assert.equal(s1.f_string, s2.f_string);
});

test("StructureT: encode/decode roundtrip", () => {
  const inner = new Test_StructureS({ f_float: 1.5, f_string: "inner" });
  const t1 = new Test_StructureT();
  t1.field_string = "outer";
  t1.field_structure_s = inner;

  const blob = t1.encode();
  const t2 = Test_StructureT.decode(blob);

  assert.equal(t1.field_string, t2.field_string);
  assert.ok(Math.abs(t1.field_structure_s.f_float - t2.field_structure_s.f_float) < 1e-5);
});

test("StructureV: encode/decode roundtrip", () => {
  const v1 = new Test_StructureV();
  v1.f_bool = true;
  v1.f_uint8 = 255;
  v1.f_string = "test";

  const blob = v1.encode();
  const v2 = Test_StructureV.decode(blob);

  assert.equal(v1.f_bool, v2.f_bool);
  assert.equal(v1.f_uint8, v2.f_uint8);
  assert.equal(v1.f_string, v2.f_string);
});

// --- container encode/decode roundtrip ---

test("Optional: nil roundtrip", () => {
  const opt1 = new Optional_uint8();
  const blob = opt1.encode();
  const opt2 = Optional_uint8.decode(blob);
  assert.ok(opt2.isNil());
});

test("Optional: value roundtrip", () => {
  const opt1 = new Optional_uint8(42);
  const blob = opt1.encode();
  const opt2 = Optional_uint8.decode(blob);
  assert.ok(!opt2.isNil());
  assert.equal(opt2.unwrap(), 42);
});

test("Vector: roundtrip", () => {
  const v1 = new Vector_uint8([1, 2, 3, 4, 5]);
  const blob = v1.encode();
  const v2 = Vector_uint8.decode(blob);
  assert.deepEqual([...v1], [...v2]);
});

test("Set: roundtrip", () => {
  const s1 = new Set_uint8([1, 2, 3]);
  const blob = s1.encode();
  const s2 = Set_uint8.decode(blob);
  assert.equal(s1.size, s2.size);
  for (const x of s1) {
    assert.ok(s2.contains(x));
  }
});

test("Map: roundtrip", () => {
  const m1 = new Map_int8_to_string([[1, "one"], [2, "two"], [3, "three"]]);
  const blob = m1.encode();
  const m2 = Map_int8_to_string.decode(blob);
  assert.equal(m1.at(1), m2.at(1));
  assert.equal(m1.at(2), m2.at(2));
  assert.equal(m1.at(3), m2.at(3));
});

// --- hexdigest for content hashing ---

test("Key: hexdigest is a non-empty string", () => {
  const key = Test_ConceptAKey.create();
  const digest = key.hexdigest();
  assert.equal(typeof digest, "string");
  assert.ok(digest.length > 0);
});

test("Key: same key same digest", () => {
  const uuidStr = "12345678-1234-1234-1234-123456789abc";
  const key1 = new Test_ConceptAKey(uuidStr);
  const key2 = new Test_ConceptAKey(uuidStr);
  assert.equal(key1.hexdigest(), key2.hexdigest());
});

test("Key: different key different digest", () => {
  const key1 = Test_ConceptAKey.create();
  const key2 = Test_ConceptAKey.create();
  assert.notEqual(key1.hexdigest(), key2.hexdigest());
});

test("Structure: hexdigest is a non-empty string", () => {
  const s = new Test_StructureS({ f_float: 1.0, f_string: "test" });
  const digest = s.hexdigest();
  assert.equal(typeof digest, "string");
  assert.ok(digest.length > 0);
});

test("Structure: same structure same digest", () => {
  const s1 = new Test_StructureS({ f_float: 1.0, f_string: "test" });
  const s2 = new Test_StructureS({ f_float: 1.0, f_string: "test" });
  assert.equal(s1.hexdigest(), s2.hexdigest());
});

// --- stream codec instancing options ---

test("Codec: binary codec", () => {
  const s1 = new Test_StructureS({ f_float: 1.5, f_string: "binary" });
  const blob = s1.encode(dsviper.Codec.STREAM_BINARY);
  const s2 = Test_StructureS.decode(blob, dsviper.Codec.STREAM_BINARY);
  assert.equal(s1.f_string, s2.f_string);
});

test("Codec: raw codec", () => {
  const s1 = new Test_StructureS({ f_float: 1.5, f_string: "raw" });
  const blob = s1.encode(dsviper.Codec.STREAM_RAW);
  const s2 = Test_StructureS.decode(blob, dsviper.Codec.STREAM_RAW);
  assert.equal(s1.f_string, s2.f_string);
});

// --- pack_sized option for structures ---

test("Structure: pack sized decode", () => {
  const s1 = new Test_StructureS({ f_float: 2.5, f_string: "pack" });
  const blob = s1.encode();
  const s2 = Test_StructureS.decode(blob);
  assert.equal(s1.f_string, s2.f_string);
});

// --- vpr_value can be encoded directly ---

test("Key: vprValue encode", () => {
  const key = Test_ConceptAKey.create();
  const vpr = key.vprValue;
  const blob = dsviper.Value.encode(vpr);
  assert.ok(blob instanceof dsviper.ValueBlob);
});

// --- blob content properties ---

test("Blob: is not empty", () => {
  const key = Test_ConceptAKey.create();
  const blob = key.encode();
  assert.ok(blob.size() > 0);
});

test("Blob: content differs by value", () => {
  const key1 = Test_ConceptAKey.create();
  const key2 = Test_ConceptAKey.create();
  const blob1 = key1.encode();
  const blob2 = key2.encode();
  assert.notEqual(blob1.base64Encode(), blob2.base64Encode());
});
