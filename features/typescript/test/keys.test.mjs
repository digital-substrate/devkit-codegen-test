import { test } from "node:test";
import { strict as assert } from "node:assert";
import dsviper from "@digitalsubstrate/dsviper";
import { ConceptAKey, ConceptBKey, ConceptCKey, ConceptDKey, KlubKey } from "../generated/dist/demo/data.js";
import * as demo from "../generated/dist/demo/data.js";
import { definitions } from "../generated/dist/index.js";

// --- TestKeyCreation ---

test("concept_a_key_create", () => {
  const key = ConceptAKey.create();
  assert.ok(key instanceof ConceptAKey);
  assert.ok(key.instanceId().isValid());
});

test("concept_b_key_create", () => {
  const key = ConceptBKey.create();
  assert.ok(key instanceof ConceptBKey);
  assert.ok(key.instanceId().isValid());
});

test("concept_c_key_create", () => {
  const key = ConceptCKey.create();
  assert.ok(key instanceof ConceptCKey);
  assert.ok(key.instanceId().isValid());
});

test("concept_d_key_create", () => {
  const key = ConceptDKey.create();
  assert.ok(key instanceof ConceptDKey);
  assert.ok(key.instanceId().isValid());
});

test("klub_key_from_concept_c", () => {
  // KlubKey is created from member concepts, not directly
  const keyC = ConceptCKey.create();
  const klubKey = KlubKey.fromConceptCKey(keyC);
  assert.ok(klubKey instanceof KlubKey);
  assert.ok(klubKey.instanceId().isValid());
});

test("keys_are_unique", () => {
  const key1 = ConceptAKey.create();
  const key2 = ConceptAKey.create();
  assert.ok(!key1.equals(key2));
  assert.ok(!key1.instanceId().equals(key2.instanceId()));
});

// --- TestKeyFromString ---

test("concept_a_from_string", () => {
  const uuidStr = "12345678-1234-1234-1234-123456789abc";
  const key = new ConceptAKey(uuidStr);
  assert.equal(key.instanceId().encoded(), uuidStr);
});

test("concept_b_from_string", () => {
  const uuidStr = "abcdef01-2345-6789-abcd-ef0123456789";
  const key = new ConceptBKey(uuidStr);
  assert.equal(key.instanceId().encoded(), uuidStr);
});

// --- TestKeyFromUUID ---

test("concept_a_from_uuid", () => {
  const uuid = dsviper.ValueUUId.create();
  const key = new ConceptAKey(uuid);
  assert.ok(key.instanceId().equals(uuid));
});

test("concept_b_from_uuid", () => {
  const uuid = dsviper.ValueUUId.create();
  const key = new ConceptBKey(uuid);
  assert.ok(key.instanceId().equals(uuid));
});

// --- TestKeyRuntimeId ---

test("concept_a_runtime_id", () => {
  const key = ConceptAKey.create();
  assert.ok(key.runtimeId().equals(demo.CONCEPT_A));
});

test("concept_b_runtime_id", () => {
  const key = ConceptBKey.create();
  assert.ok(key.runtimeId().equals(demo.CONCEPT_B));
});

test("concept_c_runtime_id", () => {
  const key = ConceptCKey.create();
  assert.ok(key.runtimeId().equals(demo.CONCEPT_C));
});

test("concept_d_runtime_id", () => {
  const key = ConceptDKey.create();
  assert.ok(key.runtimeId().equals(demo.CONCEPT_D));
});

// --- TestKeyEquality ---

test("same_uuid_equal", () => {
  const uuidStr = "12345678-1234-1234-1234-123456789abc";
  const key1 = new ConceptAKey(uuidStr);
  const key2 = new ConceptAKey(uuidStr);
  assert.ok(key1.equals(key2));
});

test("different_uuid_not_equal", () => {
  const key1 = ConceptAKey.create();
  const key2 = ConceptAKey.create();
  assert.ok(!key1.equals(key2));
});

test("hash_consistency", () => {
  const uuidStr = "12345678-1234-1234-1234-123456789abc";
  const key1 = new ConceptAKey(uuidStr);
  const key2 = new ConceptAKey(uuidStr);
  assert.equal(dsviper.Value.hexdigest(key1.vprValue), dsviper.Value.hexdigest(key2.vprValue));
});

test("keys_in_dict", () => {
  const key1 = ConceptAKey.create();
  const key2 = ConceptAKey.create();
  const d = new Map();
  d.set(dsviper.Value.hexdigest(key1.vprValue), "value1");
  d.set(dsviper.Value.hexdigest(key2.vprValue), "value2");
  assert.equal(d.get(dsviper.Value.hexdigest(key1.vprValue)), "value1");
  assert.equal(d.get(dsviper.Value.hexdigest(key2.vprValue)), "value2");
});

// --- TestKeyComparison ---

test("keys_orderable", () => {
  const key1 = ConceptAKey.create();
  const key2 = ConceptAKey.create();
  // Should not raise
  const c = key1.vprValue.compare(key2.vprValue);
  assert.ok(typeof c === "number");
});

test("keys_sortable", () => {
  const keys = Array.from({ length: 5 }, () => ConceptAKey.create());
  // Should not raise
  const sortedKeys = [...keys].sort((a, b) => a.vprValue.compare(b.vprValue));
  assert.equal(sortedKeys.length, 5);
});

// --- TestKeyDescription ---

test("concept_a_description", () => {
  const key = ConceptAKey.create();
  const desc = key.description();
  assert.ok(desc.includes("Demo::ConceptAKey"));
  assert.ok(desc.includes(key.instanceId().encoded()));
});

test("concept_b_description", () => {
  const key = ConceptBKey.create();
  const desc = key.description();
  assert.ok(desc.includes("Demo::ConceptBKey"));
});

test("repr_matches_description", () => {
  const key = ConceptAKey.create();
  assert.equal(key.toString(), key.description());
});

// --- TestKeyIsKnown ---

test("concept_a_is_known", () => {
  const key = ConceptAKey.create();
  assert.ok(key.isKnown());
});

test("concept_b_is_known", () => {
  const key = ConceptBKey.create();
  assert.ok(key.isKnown());
});

test("concept_c_is_known", () => {
  const key = ConceptCKey.create();
  assert.ok(key.isKnown());
});

test("concept_d_is_known", () => {
  const key = ConceptDKey.create();
  assert.ok(key.isKnown());
});

// --- TestKeyIsValid ---

test("created_key_is_valid", () => {
  const key = ConceptAKey.create();
  assert.ok(key.isValid());
});

test("invalid_uuid_key", () => {
  const invalidUuid = dsviper.ValueUUId.INVALID;
  const key = new ConceptAKey(invalidUuid);
  assert.ok(!key.isValid());
});

// --- TestKeyValidation ---

test("wrong_type_raises_type_error", () => {
  assert.throws(() => new ConceptAKey(123)); // number is not valid
});

test("wrong_type_raises_type_error_for_list", () => {
  assert.throws(() => new ConceptAKey([1, 2, 3]));
});

test("none_raises_type_error", () => {
  assert.throws(() => new ConceptAKey(null));
});

// --- TestKeyVprValue ---

test("vpr_value_is_value_key", () => {
  const key = ConceptAKey.create();
  assert.ok(key.vprValue instanceof dsviper.ValueKey);
});

test("vpr_value_roundtrip", () => {
  const key1 = ConceptAKey.create();
  const vpr = key1.vprValue;
  const key2 = new ConceptAKey(vpr);
  assert.ok(key1.equals(key2));
});

test("a key is made from its instance id as a string", () => {
  const key = ConceptAKey.create();
  const again = new ConceptAKey(key.instanceId().encoded());
  assert.ok(again.equals(key));
});
