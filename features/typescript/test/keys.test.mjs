import { test } from "node:test";
import { strict as assert } from "node:assert";
import dsviper from "@digitalsubstrate/dsviper";
import {
  Test_ConceptAKey, Test_ConceptBKey, Test_ConceptCKey, Test_ConceptDKey,
  Test_KlubKey,
  definitions,
} from "../features/dist/index.js";

// --- TestKeyCreation ---

test("concept_a_key_create", () => {
  const key = Test_ConceptAKey.create();
  assert.ok(key instanceof Test_ConceptAKey);
  assert.ok(key.instanceId().isValid());
});

test("concept_b_key_create", () => {
  const key = Test_ConceptBKey.create();
  assert.ok(key instanceof Test_ConceptBKey);
  assert.ok(key.instanceId().isValid());
});

test("concept_c_key_create", () => {
  const key = Test_ConceptCKey.create();
  assert.ok(key instanceof Test_ConceptCKey);
  assert.ok(key.instanceId().isValid());
});

test("concept_d_key_create", () => {
  const key = Test_ConceptDKey.create();
  assert.ok(key instanceof Test_ConceptDKey);
  assert.ok(key.instanceId().isValid());
});

test("klub_key_from_concept_c", () => {
  // KlubKey is created from member concepts, not directly
  const keyC = Test_ConceptCKey.create();
  const klubKey = Test_KlubKey.fromConceptCKey(keyC);
  assert.ok(klubKey instanceof Test_KlubKey);
  assert.ok(klubKey.instanceId().isValid());
});

test("keys_are_unique", () => {
  const key1 = Test_ConceptAKey.create();
  const key2 = Test_ConceptAKey.create();
  assert.ok(!key1.equals(key2));
  assert.ok(!key1.instanceId().equals(key2.instanceId()));
});

// --- TestKeyFromString ---

test("concept_a_from_string", () => {
  const uuidStr = "12345678-1234-1234-1234-123456789abc";
  const key = new Test_ConceptAKey(uuidStr);
  assert.equal(key.instanceId().encoded(), uuidStr);
});

test("concept_b_from_string", () => {
  const uuidStr = "abcdef01-2345-6789-abcd-ef0123456789";
  const key = new Test_ConceptBKey(uuidStr);
  assert.equal(key.instanceId().encoded(), uuidStr);
});

// --- TestKeyFromUUID ---

test("concept_a_from_uuid", () => {
  const uuid = dsviper.ValueUUId.create();
  const key = new Test_ConceptAKey(uuid);
  assert.ok(key.instanceId().equals(uuid));
});

test("concept_b_from_uuid", () => {
  const uuid = dsviper.ValueUUId.create();
  const key = new Test_ConceptBKey(uuid);
  assert.ok(key.instanceId().equals(uuid));
});

// --- TestKeyRuntimeId ---

test("concept_a_runtime_id", () => {
  const key = Test_ConceptAKey.create();
  assert.ok(key.runtimeId().equals(definitions.RuntimeIds.Test_ConceptA));
});

test("concept_b_runtime_id", () => {
  const key = Test_ConceptBKey.create();
  assert.ok(key.runtimeId().equals(definitions.RuntimeIds.Test_ConceptB));
});

test("concept_c_runtime_id", () => {
  const key = Test_ConceptCKey.create();
  assert.ok(key.runtimeId().equals(definitions.RuntimeIds.Test_ConceptC));
});

test("concept_d_runtime_id", () => {
  const key = Test_ConceptDKey.create();
  assert.ok(key.runtimeId().equals(definitions.RuntimeIds.Test_ConceptD));
});

// --- TestKeyEquality ---

test("same_uuid_equal", () => {
  const uuidStr = "12345678-1234-1234-1234-123456789abc";
  const key1 = new Test_ConceptAKey(uuidStr);
  const key2 = new Test_ConceptAKey(uuidStr);
  assert.ok(key1.equals(key2));
});

test("different_uuid_not_equal", () => {
  const key1 = Test_ConceptAKey.create();
  const key2 = Test_ConceptAKey.create();
  assert.ok(!key1.equals(key2));
});

test("hash_consistency", () => {
  const uuidStr = "12345678-1234-1234-1234-123456789abc";
  const key1 = new Test_ConceptAKey(uuidStr);
  const key2 = new Test_ConceptAKey(uuidStr);
  assert.equal(key1.hexdigest(), key2.hexdigest());
});

test("keys_in_dict", () => {
  const key1 = Test_ConceptAKey.create();
  const key2 = Test_ConceptAKey.create();
  const d = new Map();
  d.set(key1.hexdigest(), "value1");
  d.set(key2.hexdigest(), "value2");
  assert.equal(d.get(key1.hexdigest()), "value1");
  assert.equal(d.get(key2.hexdigest()), "value2");
});

// --- TestKeyComparison ---

test("keys_orderable", () => {
  const key1 = Test_ConceptAKey.create();
  const key2 = Test_ConceptAKey.create();
  // Should not raise
  const c = key1.compareTo(key2);
  assert.ok(typeof c === "number");
});

test("keys_sortable", () => {
  const keys = Array.from({ length: 5 }, () => Test_ConceptAKey.create());
  // Should not raise
  const sortedKeys = [...keys].sort((a, b) => a.compareTo(b));
  assert.equal(sortedKeys.length, 5);
});

// --- TestKeyDescription ---

test("concept_a_description", () => {
  const key = Test_ConceptAKey.create();
  const desc = key.description();
  assert.ok(desc.includes("Test::ConceptAKey"));
  assert.ok(desc.includes(key.instanceId().encoded()));
});

test("concept_b_description", () => {
  const key = Test_ConceptBKey.create();
  const desc = key.description();
  assert.ok(desc.includes("Test::ConceptBKey"));
});

test("repr_matches_description", () => {
  const key = Test_ConceptAKey.create();
  assert.equal(key.toString(), key.description());
});

// --- TestKeyIsKnown ---

test("concept_a_is_known", () => {
  const key = Test_ConceptAKey.create();
  assert.ok(key.isKnown());
});

test("concept_b_is_known", () => {
  const key = Test_ConceptBKey.create();
  assert.ok(key.isKnown());
});

test("concept_c_is_known", () => {
  const key = Test_ConceptCKey.create();
  assert.ok(key.isKnown());
});

test("concept_d_is_known", () => {
  const key = Test_ConceptDKey.create();
  assert.ok(key.isKnown());
});

// --- TestKeyIsValid ---

test("created_key_is_valid", () => {
  const key = Test_ConceptAKey.create();
  assert.ok(key.isValid());
});

test("invalid_uuid_key", () => {
  const invalidUuid = dsviper.ValueUUId.INVALID;
  const key = new Test_ConceptAKey(invalidUuid);
  assert.ok(!key.isValid());
});

// --- TestKeyValidation ---

test("wrong_type_raises_type_error", () => {
  assert.throws(() => new Test_ConceptAKey(123)); // number is not valid
});

test("wrong_type_raises_type_error_for_list", () => {
  assert.throws(() => new Test_ConceptAKey([1, 2, 3]));
});

test("none_raises_type_error", () => {
  assert.throws(() => new Test_ConceptAKey(null));
});

// --- TestKeyVprValue ---

test("vpr_value_is_value_key", () => {
  const key = Test_ConceptAKey.create();
  assert.ok(key.vprValue instanceof dsviper.ValueKey);
});

test("vpr_value_roundtrip", () => {
  const key1 = Test_ConceptAKey.create();
  const vpr = key1.vprValue;
  const key2 = new Test_ConceptAKey(vpr);
  assert.ok(key1.equals(key2));
});
