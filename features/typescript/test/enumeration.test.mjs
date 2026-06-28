// Tests for Kibo-generated Enumeration proxy classes.

import { test } from "node:test";
import { strict as assert } from "node:assert";
import { Test_EnumerationE } from "../features/dist/index.js";

// --- Cases ---

test("case_a", () => {
  const e = Test_EnumerationE.A;
  assert.ok(e instanceof Test_EnumerationE);
});

test("case_b", () => {
  const e = Test_EnumerationE.B;
  assert.ok(e instanceof Test_EnumerationE);
});

test("case_c", () => {
  const e = Test_EnumerationE.C;
  assert.ok(e instanceof Test_EnumerationE);
});

test("cases_are_singletons", () => {
  const a1 = Test_EnumerationE.A;
  const a2 = Test_EnumerationE.A;
  assert.ok(a1 === a2);
});

// --- name() ---

test("name_a", () => {
  assert.equal(Test_EnumerationE.A.name(), "a");
});

test("name_b", () => {
  assert.equal(Test_EnumerationE.B.name(), "b");
});

test("name_c", () => {
  assert.equal(Test_EnumerationE.C.name(), "c");
});

// --- fromStr() ---

test("from_str_a", () => {
  const e = Test_EnumerationE.fromStr("a");
  assert.equal(e.name(), "a");
});

test("from_str_b", () => {
  const e = Test_EnumerationE.fromStr("b");
  assert.equal(e.name(), "b");
});

test("from_str_c", () => {
  const e = Test_EnumerationE.fromStr("c");
  assert.equal(e.name(), "c");
});

test("from_str_invalid", () => {
  assert.throws(() => Test_EnumerationE.fromStr("invalid"));
});

test("from_str_type_error", () => {
  // A non-string / non-case argument is rejected.
  assert.throws(() => Test_EnumerationE.fromStr(123));
});

// --- equality ---

test("same_case_equal", () => {
  assert.ok(Test_EnumerationE.A.equals(Test_EnumerationE.A));
  assert.ok(Test_EnumerationE.B.equals(Test_EnumerationE.B));
});

test("different_cases_not_equal", () => {
  assert.ok(!Test_EnumerationE.A.equals(Test_EnumerationE.B));
  assert.ok(!Test_EnumerationE.B.equals(Test_EnumerationE.C));
});

test("from_str_equals_direct", () => {
  assert.ok(Test_EnumerationE.fromStr("a").equals(Test_EnumerationE.A));
  assert.ok(Test_EnumerationE.fromStr("b").equals(Test_EnumerationE.B));
});

// --- hashing / use in JS collections (adapted from Python hash tests) ---

test("hashable", () => {
  // JS equivalent of a stable hash: the value hexdigest.
  const h = Test_EnumerationE.A.hexdigest();
  assert.equal(typeof h, "string");
});

test("same_case_same_hash", () => {
  assert.equal(Test_EnumerationE.A.hexdigest(), Test_EnumerationE.A.hexdigest());
});

test("usable_in_set", () => {
  // Keyed by hexdigest, A appears once -> 2 distinct entries.
  const s = new Set([
    Test_EnumerationE.A.hexdigest(),
    Test_EnumerationE.B.hexdigest(),
    Test_EnumerationE.A.hexdigest(),
  ]);
  assert.equal(s.size, 2);
});

test("usable_as_dict_key", () => {
  // Keyed by hexdigest, behaving as a dict key.
  const d = new Map([
    [Test_EnumerationE.A.hexdigest(), "first"],
    [Test_EnumerationE.B.hexdigest(), "second"],
  ]);
  assert.equal(d.get(Test_EnumerationE.A.hexdigest()), "first");
});

// --- serialization ---

test("encode_decode_a", () => {
  const e1 = Test_EnumerationE.A;
  const blob = e1.encode();
  const e2 = Test_EnumerationE.decode(blob);
  assert.equal(e2.name(), "a");
});

test("encode_decode_b", () => {
  const e1 = Test_EnumerationE.B;
  const blob = e1.encode();
  const e2 = Test_EnumerationE.decode(blob);
  assert.equal(e2.name(), "b");
});

test("encode_decode_c", () => {
  const e1 = Test_EnumerationE.C;
  const blob = e1.encode();
  const e2 = Test_EnumerationE.decode(blob);
  assert.equal(e2.name(), "c");
});

// --- string representation ---

test("repr_contains_name", () => {
  const r = Test_EnumerationE.A.toString();
  assert.ok(r.toLowerCase().includes("a"));
});
