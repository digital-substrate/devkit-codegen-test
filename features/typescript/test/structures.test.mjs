// Tests for Kibo-generated structure proxy classes.
import { test } from "node:test";
import { strict as assert } from "node:assert";
import dsviper from "@digitalsubstrate/dsviper";
import {
  Test_StructureS, Test_StructureT, Test_StructureU, Test_StructureV,
  Test_EnumerationE, Vec_uint8_2, Mat_uint8_2_2, Mat_uint8_2_3,
  Tuple_uint8_string, Optional_uint8, Vector_uint8, Set_uint8,
  Map_uint8_to_string, XArray_uint8,
} from "../features/dist/index.js";

// --- StructureS construction and field access ---

test("StructureS: empty construction", () => {
  const s = new Test_StructureS();
  assert.ok(s instanceof Test_StructureS);
});

test("StructureS: dict construction", () => {
  const s = new Test_StructureS({ f_float: 3.14, f_string: "hello" });
  assert.ok(Math.abs(s.f_float - 3.14) < 1e-5);
  assert.equal(s.f_string, "hello");
});

test("StructureS: float field access", () => {
  const s = new Test_StructureS();
  s.f_float = 2.718;
  assert.ok(Math.abs(s.f_float - 2.718) < 1e-5);
});

test("StructureS: string field access", () => {
  const s = new Test_StructureS();
  s.f_string = "test";
  assert.equal(s.f_string, "test");
});

// --- StructureT with nested structure ---

test("StructureT: empty construction", () => {
  const t = new Test_StructureT();
  assert.ok(t instanceof Test_StructureT);
});

test("StructureT: string field access", () => {
  const t = new Test_StructureT();
  t.field_string = "nested";
  assert.equal(t.field_string, "nested");
});

test("StructureT: nested structure access", () => {
  const t = new Test_StructureT();
  const inner = new Test_StructureS({ f_float: 1.5, f_string: "inner" });
  t.field_structure_s = inner;
  const retrieved = t.field_structure_s;
  assert.ok(Math.abs(retrieved.f_float - 1.5) < 1e-5);
  assert.equal(retrieved.f_string, "inner");
});

// --- StructureU primitive field access ---

test("StructureU: bool field", () => {
  const u = new Test_StructureU();
  u.f_bool = true;
  assert.ok(u.f_bool);
  u.f_bool = false;
  assert.ok(!u.f_bool);
});

test("StructureU: uint8 field", () => {
  const u = new Test_StructureU();
  u.f_uint8 = 255;
  assert.equal(u.f_uint8, 255);
});

test("StructureU: uint16 field", () => {
  const u = new Test_StructureU();
  u.f_uint16 = 65535;
  assert.equal(u.f_uint16, 65535);
});

test("StructureU: uint32 field", () => {
  const u = new Test_StructureU();
  u.f_uint32 = 4294967295;
  assert.equal(u.f_uint32, 4294967295);
});

test("StructureU: uint64 field", () => {
  const u = new Test_StructureU();
  u.f_uint64 = 2n ** 63n;
  assert.equal(u.f_uint64, 2n ** 63n);
});

test("StructureU: int8 field", () => {
  const u = new Test_StructureU();
  u.f_int8 = -128;
  assert.equal(u.f_int8, -128);
  u.f_int8 = 127;
  assert.equal(u.f_int8, 127);
});

test("StructureU: int16 field", () => {
  const u = new Test_StructureU();
  u.f_int16 = -32768;
  assert.equal(u.f_int16, -32768);
});

test("StructureU: int32 field", () => {
  const u = new Test_StructureU();
  u.f_int32 = -2147483648;
  assert.equal(u.f_int32, -2147483648);
});

test("StructureU: int64 field", () => {
  const u = new Test_StructureU();
  u.f_int64 = -(2n ** 62n);
  assert.equal(u.f_int64, -(2n ** 62n));
});

test("StructureU: float field", () => {
  const u = new Test_StructureU();
  u.f_float = 3.14;
  assert.ok(Math.abs(u.f_float - 3.14) < 1e-5);
});

test("StructureU: double field", () => {
  const u = new Test_StructureU();
  u.f_double = 3.141592653589793;
  assert.ok(Math.abs(u.f_double - 3.141592653589793) < 1e-10);
});

test("StructureU: string field", () => {
  const u = new Test_StructureU();
  u.f_string = "hello world";
  assert.equal(u.f_string, "hello world");
});

// --- StructureU special type fields ---

test("StructureU: uuid field", () => {
  const u = new Test_StructureU();
  const uuid = dsviper.ValueUUId.create();
  u.f_uuid = uuid;
  assert.ok(u.f_uuid.equals(uuid));
});

test("StructureU: blob_id field", () => {
  const u = new Test_StructureU();
  const blobId = dsviper.ValueBlobId.INVALID;
  u.f_blob_id = blobId;
  assert.ok(u.f_blob_id.equals(blobId));
});

test("StructureU: commit_id field", () => {
  const u = new Test_StructureU();
  const commitId = dsviper.ValueCommitId.INVALID;
  u.f_commit_id = commitId;
  assert.ok(u.f_commit_id.equals(commitId));
});

test("StructureU: blob field", () => {
  const u = new Test_StructureU();
  const blob = new dsviper.ValueBlob("dGVzdCBkYXRh");
  u.f_blob = blob;
  assert.equal(u.f_blob.base64Encode(), new dsviper.ValueBlob("dGVzdCBkYXRh").base64Encode());
});

// --- StructureU container type fields ---

test("StructureU: vec field", () => {
  const u = new Test_StructureU();
  u.f_vec = new Vec_uint8_2([10, 20]);
  const retrieved = u.f_vec;
  assert.equal(retrieved.at(0), 10);
  assert.equal(retrieved.at(1), 20);
});

test("StructureU: mat field", () => {
  const u = new Test_StructureU();
  u.f_mat = new Mat_uint8_2_2([[1, 2], [3, 4]]);
  const retrieved = u.f_mat;
  assert.equal(retrieved.at(0, 0), 1);
  assert.equal(retrieved.at(1, 1), 4);
});

test("StructureU: tuple field", () => {
  const u = new Test_StructureU();
  u.f_tuple = new Tuple_uint8_string([42, "answer"]);
  const retrieved = u.f_tuple;
  assert.equal(retrieved.at(0), 42);
  assert.equal(retrieved.at(1), "answer");
});

test("StructureU: optional nil field", () => {
  const u = new Test_StructureU();
  u.f_optional = new Optional_uint8();
  const retrieved = u.f_optional;
  assert.ok(retrieved.isNil());
});

test("StructureU: optional value field", () => {
  const u = new Test_StructureU();
  u.f_optional = new Optional_uint8(42);
  const retrieved = u.f_optional;
  assert.ok(!retrieved.isNil());
  assert.equal(retrieved.unwrap(), 42);
});

test("StructureU: vector field", () => {
  const u = new Test_StructureU();
  u.f_vector = new Vector_uint8([1, 2, 3, 4, 5]);
  const retrieved = u.f_vector;
  assert.equal(retrieved.size, 5);
  assert.deepEqual([...retrieved], [1, 2, 3, 4, 5]);
});

test("StructureU: set field", () => {
  const u = new Test_StructureU();
  u.f_set = new Set_uint8([1, 2, 3]);
  const retrieved = u.f_set;
  assert.equal(retrieved.size, 3);
  assert.ok([...retrieved].includes(1));
});

test("StructureU: xarray field", () => {
  const u = new Test_StructureU();
  u.f_xarray = new XArray_uint8([10, 20, 30]);
  const retrieved = u.f_xarray;
  assert.equal(retrieved.size, 3);
});

// --- StructureU enumeration field ---

test("StructureU: enumeration field", () => {
  const u = new Test_StructureU();
  const e = Test_EnumerationE.A;
  u.f_E = e;
  const retrieved = u.f_E;
  assert.ok(retrieved.equals(e));
});

// --- StructureV construction ---

test("StructureV: empty construction", () => {
  const v = new Test_StructureV();
  assert.ok(v instanceof Test_StructureV);
});

test("StructureV: dict construction primitives", () => {
  const v = new Test_StructureV({
    f_bool: true,
    f_uint8: 42,
    f_int8: -10,
    f_float: 3.14,
    f_string: "hello",
  });
  assert.ok(v.f_bool);
  assert.equal(v.f_uint8, 42);
  assert.equal(v.f_int8, -10);
  assert.ok(Math.abs(v.f_float - 3.14) < 1e-5);
  assert.equal(v.f_string, "hello");
});

// --- StructureV primitive field access ---

test("StructureV: bool field", () => {
  const v = new Test_StructureV();
  v.f_bool = true;
  assert.ok(v.f_bool);
  v.f_bool = false;
  assert.ok(!v.f_bool);
});

test("StructureV: uint8 field", () => {
  const v = new Test_StructureV();
  v.f_uint8 = 255;
  assert.equal(v.f_uint8, 255);
});

test("StructureV: uint16 field", () => {
  const v = new Test_StructureV();
  v.f_uint16 = 65535;
  assert.equal(v.f_uint16, 65535);
});

test("StructureV: uint32 field", () => {
  const v = new Test_StructureV();
  v.f_uint32 = 4294967295;
  assert.equal(v.f_uint32, 4294967295);
});

test("StructureV: uint64 field", () => {
  const v = new Test_StructureV();
  v.f_uint64 = 2n ** 63n;
  assert.equal(v.f_uint64, 2n ** 63n);
});

test("StructureV: int8 field", () => {
  const v = new Test_StructureV();
  v.f_int8 = -128;
  assert.equal(v.f_int8, -128);
  v.f_int8 = 127;
  assert.equal(v.f_int8, 127);
});

test("StructureV: int16 field", () => {
  const v = new Test_StructureV();
  v.f_int16 = -32768;
  assert.equal(v.f_int16, -32768);
});

test("StructureV: int32 field", () => {
  const v = new Test_StructureV();
  v.f_int32 = -2147483648;
  assert.equal(v.f_int32, -2147483648);
});

test("StructureV: int64 field", () => {
  const v = new Test_StructureV();
  v.f_int64 = -(2n ** 62n);
  assert.equal(v.f_int64, -(2n ** 62n));
});

test("StructureV: float field", () => {
  const v = new Test_StructureV();
  v.f_float = 3.14;
  assert.ok(Math.abs(v.f_float - 3.14) < 1e-5);
});

test("StructureV: double field", () => {
  const v = new Test_StructureV();
  v.f_double = 3.141592653589793;
  assert.ok(Math.abs(v.f_double - 3.141592653589793) < 1e-10);
});

test("StructureV: string field", () => {
  const v = new Test_StructureV();
  v.f_string = "hello world";
  assert.equal(v.f_string, "hello world");
});

// --- StructureV special type fields ---

test("StructureV: uuid field", () => {
  const v = new Test_StructureV();
  const uuid = dsviper.ValueUUId.create();
  v.f_uuid = uuid;
  assert.ok(v.f_uuid.equals(uuid));
});

// --- StructureV fixed-size container fields (Vec, Mat, Tuple) ---

test("StructureV: vec field", () => {
  const v = new Test_StructureV();
  v.f_vec = new Vec_uint8_2([10, 20]);
  const retrieved = v.f_vec;
  assert.equal(retrieved.at(0), 10);
  assert.equal(retrieved.at(1), 20);
});

test("StructureV: mat field", () => {
  const v = new Test_StructureV();
  // Mat_uint8_2_3 is 2 rows x 3 cols
  v.f_mat = new Mat_uint8_2_3([[1, 2, 3], [4, 5, 6]]);
  const retrieved = v.f_mat;
  assert.equal(retrieved.at(0, 0), 1);
  assert.equal(retrieved.at(0, 2), 3);
  assert.equal(retrieved.at(1, 1), 5);
});

test("StructureV: tuple field", () => {
  const v = new Test_StructureV();
  v.f_tuple = new Tuple_uint8_string([42, "answer"]);
  const retrieved = v.f_tuple;
  assert.equal(retrieved.at(0), 42);
  assert.equal(retrieved.at(1), "answer");
});

// --- StructureV dynamic container fields (Optional, Vector, Set, Map) ---

test("StructureV: optional nil field", () => {
  const v = new Test_StructureV();
  v.f_optional = new Optional_uint8();
  const retrieved = v.f_optional;
  assert.ok(retrieved.isNil());
});

test("StructureV: optional value field", () => {
  const v = new Test_StructureV();
  v.f_optional = new Optional_uint8(42);
  const retrieved = v.f_optional;
  assert.ok(!retrieved.isNil());
  assert.equal(retrieved.unwrap(), 42);
});

test("StructureV: vector field", () => {
  const v = new Test_StructureV();
  v.f_vector = new Vector_uint8([1, 2, 3, 4, 5]);
  const retrieved = v.f_vector;
  assert.equal(retrieved.size, 5);
  assert.deepEqual([...retrieved], [1, 2, 3, 4, 5]);
});

test("StructureV: set field", () => {
  const v = new Test_StructureV();
  v.f_set = new Set_uint8([1, 2, 3]);
  const retrieved = v.f_set;
  assert.equal(retrieved.size, 3);
  assert.ok(retrieved.contains(1));
  assert.ok(retrieved.contains(2));
  assert.ok(retrieved.contains(3));
});

test("StructureV: map field", () => {
  const v = new Test_StructureV();
  v.f_map = new Map_uint8_to_string([[1, "one"], [2, "two"]]);
  const retrieved = v.f_map;
  assert.equal(retrieved.size, 2);
  assert.equal(retrieved.at(1), "one");
  assert.equal(retrieved.at(2), "two");
});

// --- StructureV enumeration and nested structure fields ---

test("StructureV: enumeration field", () => {
  const v = new Test_StructureV();
  v.f_E = Test_EnumerationE.B;
  const retrieved = v.f_E;
  assert.ok(retrieved.equals(Test_EnumerationE.B));
  assert.equal(retrieved.name(), "b");
});

test("StructureV: structure_s field", () => {
  const v = new Test_StructureV();
  v.f_S = new Test_StructureS({ f_float: 1.5, f_string: "nested" });
  const retrieved = v.f_S;
  assert.ok(Math.abs(retrieved.f_float - 1.5) < 1e-5);
  assert.equal(retrieved.f_string, "nested");
});

test("StructureV: structure_t field", () => {
  const v = new Test_StructureV();
  const t = new Test_StructureT();
  t.field_string = "level1";
  t.field_structure_s = new Test_StructureS({ f_float: 2.5, f_string: "level2" });
  v.f_T = t;
  const retrieved = v.f_T;
  assert.equal(retrieved.field_string, "level1");
  assert.ok(Math.abs(retrieved.field_structure_s.f_float - 2.5) < 1e-5);
});

// --- StructureV copy operation ---

test("StructureV: copy creates independent structure", () => {
  const v1 = new Test_StructureV();
  v1.f_string = "original";
  v1.f_uint8 = 100;
  const v2 = v1.copy();
  v2.f_string = "modified";
  v2.f_uint8 = 200;
  assert.equal(v1.f_string, "original");
  assert.equal(v1.f_uint8, 100);
  assert.equal(v2.f_string, "modified");
  assert.equal(v2.f_uint8, 200);
});

test("StructureV: copy preserves nested structures", () => {
  const v1 = new Test_StructureV();
  v1.f_S = new Test_StructureS({ f_float: 3.14, f_string: "pi" });
  const v2 = v1.copy();
  assert.ok(Math.abs(v2.f_S.f_float - 3.14) < 1e-5);
  assert.equal(v2.f_S.f_string, "pi");
});

// --- StructureV encode/decode serialization ---

test("StructureV: encode/decode roundtrip", () => {
  const v1 = new Test_StructureV();
  v1.f_bool = true;
  v1.f_uint8 = 42;
  v1.f_string = "test";
  const blob = v1.encode();
  const v2 = Test_StructureV.decode(blob);
  assert.ok(v2.f_bool);
  assert.equal(v2.f_uint8, 42);
  assert.equal(v2.f_string, "test");
});

test("StructureV: encode/decode with containers", () => {
  const v1 = new Test_StructureV();
  v1.f_vector = new Vector_uint8([10, 20, 30]);
  v1.f_set = new Set_uint8([1, 2, 3]);
  v1.f_map = new Map_uint8_to_string([[1, "a"], [2, "b"]]);
  const blob = v1.encode();
  const v2 = Test_StructureV.decode(blob);
  assert.deepEqual([...v2.f_vector], [10, 20, 30]);
  assert.equal(v2.f_set.size, 3);
  assert.equal(v2.f_map.at(1), "a");
});

test("StructureV: encode/decode with nested structures", () => {
  const v1 = new Test_StructureV();
  v1.f_S = new Test_StructureS({ f_float: 2.718, f_string: "euler" });
  v1.f_E = Test_EnumerationE.C;
  const blob = v1.encode();
  const v2 = Test_StructureV.decode(blob);
  assert.ok(Math.abs(v2.f_S.f_float - 2.718) < 1e-3);
  assert.equal(v2.f_S.f_string, "euler");
  assert.ok(v2.f_E.equals(Test_EnumerationE.C));
});

// --- structure copy operation ---

test("StructureS: copy", () => {
  const s1 = new Test_StructureS({ f_float: 1.5, f_string: "original" });
  const s2 = s1.copy();
  s2.f_string = "modified";
  assert.equal(s1.f_string, "original");
  assert.equal(s2.f_string, "modified");
});

test("StructureT: copy", () => {
  const t1 = new Test_StructureT();
  t1.field_string = "original";
  const t2 = t1.copy();
  t2.field_string = "modified";
  assert.equal(t1.field_string, "original");
  assert.equal(t2.field_string, "modified");
});

// --- structure equality comparison ---

test("Structure: equal structures", () => {
  const s1 = new Test_StructureS({ f_float: 1.0, f_string: "test" });
  const s2 = new Test_StructureS({ f_float: 1.0, f_string: "test" });
  assert.ok(s1.equals(s2));
});

test("Structure: unequal structures", () => {
  const s1 = new Test_StructureS({ f_float: 1.0, f_string: "test" });
  const s2 = new Test_StructureS({ f_float: 2.0, f_string: "test" });
  assert.ok(!s1.equals(s2));
});

// --- access to underlying Viper value ---

test("Structure: vprValue is ValueStructure", () => {
  const s = new Test_StructureS();
  assert.ok(s.vprValue instanceof dsviper.ValueStructure);
});

test("Structure: vprValue roundtrip", () => {
  const s1 = new Test_StructureS({ f_float: 2.5, f_string: "test" });
  const vpr = s1.vprValue;
  const s2 = new Test_StructureS(vpr);
  assert.equal(s1.f_float, s2.f_float);
  assert.equal(s1.f_string, s2.f_string);
});
