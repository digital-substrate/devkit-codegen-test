// Tests for Kibo-generated Enumeration proxy classes.

import { test } from "node:test";
import { strict as assert } from "node:assert";
import { EnumerationE } from "../generated/dist/demo/data.js";

// --- Cases ---

test("case_a", () => {
  const e = EnumerationE.A;
  assert.ok(Object.values(EnumerationE).includes(e));
});

test("case_b", () => {
  const e = EnumerationE.B;
  assert.ok(Object.values(EnumerationE).includes(e));
});

test("case_c", () => {
  const e = EnumerationE.C;
  assert.ok(Object.values(EnumerationE).includes(e));
});

test("cases_are_singletons", () => {
  const a1 = EnumerationE.A;
  const a2 = EnumerationE.A;
  assert.ok(a1 === a2);
});

// --- name() ---

test("name_a", () => {
  assert.equal(EnumerationE.name(EnumerationE.A), "a");
});

test("name_b", () => {
  assert.equal(EnumerationE.name(EnumerationE.B), "b");
});

test("name_c", () => {
  assert.equal(EnumerationE.name(EnumerationE.C), "c");
});

// --- fromStr() ---

test("from_str_a", () => {
  const e = EnumerationE.fromStr("a");
  assert.equal(EnumerationE.name(e), "a");
});

test("from_str_b", () => {
  const e = EnumerationE.fromStr("b");
  assert.equal(EnumerationE.name(e), "b");
});

test("from_str_c", () => {
  const e = EnumerationE.fromStr("c");
  assert.equal(EnumerationE.name(e), "c");
});

test("from_str_invalid", () => {
  assert.throws(() => EnumerationE.fromStr("invalid"));
});

test("from_str_type_error", () => {
  // A non-string / non-case argument is rejected.
  assert.throws(() => EnumerationE.fromStr(123));
});

// --- equality ---

test("same_case_equal", () => {
  assert.ok((EnumerationE.A === EnumerationE.A));
  assert.ok((EnumerationE.B === EnumerationE.B));
});

test("different_cases_not_equal", () => {
  assert.ok(!(EnumerationE.A === EnumerationE.B));
  assert.ok(!(EnumerationE.B === EnumerationE.C));
});

test("from_str_equals_direct", () => {
  assert.ok((EnumerationE.fromStr("a") === EnumerationE.A));
  assert.ok((EnumerationE.fromStr("b") === EnumerationE.B));
});

// --- hashing / use in JS collections (adapted from Python hash tests) ---

test("hashable", () => {
  // JS equivalent of a stable hash: the value hexdigest.
  const h = EnumerationE.hexdigest(EnumerationE.A);
  assert.equal(typeof h, "string");
});

test("same_case_same_hash", () => {
  assert.equal(EnumerationE.hexdigest(EnumerationE.A), EnumerationE.hexdigest(EnumerationE.A));
});

test("usable_in_set", () => {
  // Keyed by hexdigest, A appears once -> 2 distinct entries.
  const s = new Set([
    EnumerationE.hexdigest(EnumerationE.A),
    EnumerationE.hexdigest(EnumerationE.B),
    EnumerationE.hexdigest(EnumerationE.A),
  ]);
  assert.equal(s.size, 2);
});

test("usable_as_dict_key", () => {
  // Keyed by hexdigest, behaving as a dict key.
  const d = new Map([
    [EnumerationE.hexdigest(EnumerationE.A), "first"],
    [EnumerationE.hexdigest(EnumerationE.B), "second"],
  ]);
  assert.equal(d.get(EnumerationE.hexdigest(EnumerationE.A)), "first");
});

// --- serialization ---

test("encode_decode_a", () => {
  const e1 = EnumerationE.A;
  const blob = EnumerationE.encode(e1);
  const e2 = EnumerationE.decode(blob);
  assert.equal(EnumerationE.name(e2), "a");
});

test("encode_decode_b", () => {
  const e1 = EnumerationE.B;
  const blob = EnumerationE.encode(e1);
  const e2 = EnumerationE.decode(blob);
  assert.equal(EnumerationE.name(e2), "b");
});

test("encode_decode_c", () => {
  const e1 = EnumerationE.C;
  const blob = EnumerationE.encode(e1);
  const e2 = EnumerationE.decode(blob);
  assert.equal(EnumerationE.name(e2), "c");
});

// --- string representation ---

test("repr_contains_name", () => {
  const r = EnumerationE.A.toString();
  assert.ok(r.toLowerCase().includes("a"));
});
