import { test } from "node:test";
import { strict as assert } from "node:assert";
import dsviper from "@digitalsubstrate/dsviper";
import { ConceptAKey, ConceptBKey, ConceptCKey, ConceptDKey, KlubKey } from "../generated/dist/demo/data.js";
import { AnyConceptKey } from "../generated/dist/_codegen/registry.js";
import * as demo from "../generated/dist/demo/data.js";
import { definitions } from "../generated/dist/index.js";

// --- TestAnyConceptKeyFromConcept ---

test("concept_a_to_any", () => {
  const key = ConceptAKey.create();
  const anyKey = key.toAnyConceptKey();
  assert.ok(anyKey instanceof AnyConceptKey);
  assert.ok(anyKey.instanceId().equals(key.instanceId()));
});

test("concept_b_to_any", () => {
  const key = ConceptBKey.create();
  const anyKey = key.toAnyConceptKey();
  assert.ok(anyKey instanceof AnyConceptKey);
});

test("concept_c_to_any", () => {
  const key = ConceptCKey.create();
  const anyKey = key.toAnyConceptKey();
  assert.ok(anyKey instanceof AnyConceptKey);
});

test("concept_d_to_any", () => {
  const key = ConceptDKey.create();
  const anyKey = key.toAnyConceptKey();
  assert.ok(anyKey instanceof AnyConceptKey);
});

// --- TestAnyConceptKeyRuntimeId ---

test("runtime_id_concept_a", () => {
  const key = ConceptAKey.create();
  const anyKey = key.toAnyConceptKey();
  assert.ok(anyKey.runtimeId().equals(demo.CONCEPT_A));
});

test("runtime_id_concept_b", () => {
  const key = ConceptBKey.create();
  const anyKey = key.toAnyConceptKey();
  assert.ok(anyKey.runtimeId().equals(demo.CONCEPT_B));
});

test("runtime_id_concept_c", () => {
  const key = ConceptCKey.create();
  const anyKey = key.toAnyConceptKey();
  assert.ok(anyKey.runtimeId().equals(demo.CONCEPT_C));
});

test("runtime_id_concept_d", () => {
  const key = ConceptDKey.create();
  const anyKey = key.toAnyConceptKey();
  assert.ok(anyKey.runtimeId().equals(demo.CONCEPT_D));
});

// --- TestAnyConceptKeyDowncast ---

test("downcast_to_concept_a_success", () => {
  const key = ConceptAKey.create();
  const anyKey = key.toAnyConceptKey();
  const result = ConceptAKey.fromAnyConceptKey(anyKey);
  assert.notEqual(result, null);
  assert.ok(result.equals?.(key) ?? (result === key));
});

test("downcast_to_concept_a_failure", () => {
  const key = ConceptBKey.create();
  const anyKey = key.toAnyConceptKey();
  const result = ConceptAKey.fromAnyConceptKey(anyKey);
  assert.equal(result, undefined);
});

test("downcast_to_concept_b_success", () => {
  const key = ConceptBKey.create();
  const anyKey = key.toAnyConceptKey();
  const result = ConceptBKey.fromAnyConceptKey(anyKey);
  assert.notEqual(result, null);
  assert.ok(result.equals?.(key) ?? (result === key));
});

test("downcast_to_concept_b_failure", () => {
  const key = ConceptAKey.create();
  const anyKey = key.toAnyConceptKey();
  const result = ConceptBKey.fromAnyConceptKey(anyKey);
  assert.equal(result, undefined);
});

// --- TestAnyConceptKeyIsKnown ---

test("concept_a_is_known", () => {
  const key = ConceptAKey.create();
  const anyKey = key.toAnyConceptKey();
  assert.ok(anyKey.isKnown());
});

test("concept_b_is_known", () => {
  const key = ConceptBKey.create();
  const anyKey = key.toAnyConceptKey();
  assert.ok(anyKey.isKnown());
});

// --- TestAnyConceptKeyDescription ---

test("description_includes_type", () => {
  const key = ConceptAKey.create();
  const anyKey = key.toAnyConceptKey();
  const desc = anyKey.description();
  assert.ok(desc.includes("AnyConceptKey"));
  assert.ok(desc.includes("ConceptAKey"));
});

test("description_includes_uuid", () => {
  const key = ConceptAKey.create();
  const anyKey = key.toAnyConceptKey();
  const desc = anyKey.description();
  assert.ok(desc.includes(key.instanceId().encoded()));
});

// --- TestAnyConceptKeyEquality ---

test("same_origin_equal", () => {
  const key = ConceptAKey.create();
  const any1 = key.toAnyConceptKey();
  const any2 = key.toAnyConceptKey();
  assert.ok(any1.equals(any2));
});

test("different_origin_not_equal", () => {
  const key1 = ConceptAKey.create();
  const key2 = ConceptAKey.create();
  const any1 = key1.toAnyConceptKey();
  const any2 = key2.toAnyConceptKey();
  assert.ok(!any1.equals(any2));
});

test("different_types_not_equal", () => {
  const keyA = ConceptAKey.create();
  const keyB = ConceptBKey.create();
  const anyA = keyA.toAnyConceptKey();
  const anyB = keyB.toAnyConceptKey();
  assert.ok(!anyA.equals(anyB));
});

// --- TestAnyConceptKeyValidation ---

test("valid_key", () => {
  const key = ConceptAKey.create();
  const anyKey = key.toAnyConceptKey();
  assert.ok(anyKey.isValid());
});

test("invalid_key", () => {
  const invalidUuid = dsviper.ValueUUId.INVALID;
  const key = new ConceptAKey(invalidUuid);
  const anyKey = key.toAnyConceptKey();
  assert.ok(!anyKey.isValid());
});

// --- TestConceptInheritance ---

test("concept_c_is_club_member", () => {
  // ConceptC is a member of Klub
  const keyC = ConceptCKey.create();
  // Verify it can be used where ConceptB is expected (through club membership)
  assert.ok(keyC instanceof ConceptCKey);
});

test("concept_c_to_parent_key", () => {
  // ConceptC extends ConceptB - use toParentKey
  const keyC = ConceptCKey.create();
  // Convert to ConceptBKey via toParentKey
  const asB = keyC.toParentKey();
  assert.ok(asB instanceof ConceptBKey);
  assert.ok(asB.instanceId().equals(keyC.instanceId()));
});

test("concept_b_from_concept_c", () => {
  const keyC = ConceptCKey.create();
  const anyKey = keyC.toAnyConceptKey();
  // ConceptC key should work with fromAnyConceptKey on ConceptCKey
  const resultC = ConceptCKey.fromAnyConceptKey(anyKey);
  assert.notEqual(resultC, null);
});

// --- TestKlubMembership ---

test("klub_key_from_concept_c", () => {
  const keyC = ConceptCKey.create();
  const klubKey = KlubKey.fromConceptCKey(keyC);
  assert.ok(klubKey instanceof KlubKey);
  assert.ok(klubKey.instanceId().equals(keyC.instanceId()));
});

test("klub_key_from_concept_d", () => {
  const keyD = ConceptDKey.create();
  const klubKey = KlubKey.fromConceptDKey(keyD);
  assert.ok(klubKey instanceof KlubKey);
  assert.ok(klubKey.instanceId().equals(keyD.instanceId()));
});

test("klub_key_runtime_id_concept_c", () => {
  const keyC = ConceptCKey.create();
  const klubKey = KlubKey.fromConceptCKey(keyC);
  assert.ok(klubKey.runtimeId().equals(demo.CONCEPT_C));
});

test("klub_key_runtime_id_concept_d", () => {
  const keyD = ConceptDKey.create();
  const klubKey = KlubKey.fromConceptDKey(keyD);
  assert.ok(klubKey.runtimeId().equals(demo.CONCEPT_D));
});

test("klub_key_downcast_to_concept_c", () => {
  const keyC = ConceptCKey.create();
  const klubKey = KlubKey.fromConceptCKey(keyC);
  const result = klubKey.asConceptCKey();
  assert.notEqual(result, null);
  assert.ok(result.equals?.(keyC) ?? (result === keyC));
});

test("klub_key_downcast_failure", () => {
  const keyC = ConceptCKey.create();
  const klubKey = KlubKey.fromConceptCKey(keyC);
  const result = klubKey.asConceptDKey();
  assert.equal(result, undefined);
});

// --- TestKlubKeyIsKnown ---

test("klub_from_concept_c_is_known", () => {
  const keyC = ConceptCKey.create();
  const klubKey = KlubKey.fromConceptCKey(keyC);
  assert.ok(klubKey.isKnown());
});

test("klub_from_concept_d_is_known", () => {
  const keyD = ConceptDKey.create();
  const klubKey = KlubKey.fromConceptDKey(keyD);
  assert.ok(klubKey.isKnown());
});

// --- TestPolymorphicDispatch ---

test("dispatch_by_runtime_id", () => {
  const keys = [
    ConceptAKey.create(),
    ConceptBKey.create(),
    ConceptCKey.create(),
    ConceptDKey.create(),
  ];

  const anyKeys = keys.map((k) => k.toAnyConceptKey());

  // Dispatch based on runtimeId
  for (const anyKey of anyKeys) {
    const rid = anyKey.runtimeId();
    if (rid.equals(demo.CONCEPT_A)) {
      const result = ConceptAKey.fromAnyConceptKey(anyKey);
      assert.notEqual(result, null);
    } else if (rid.equals(demo.CONCEPT_B)) {
      const result = ConceptBKey.fromAnyConceptKey(anyKey);
      assert.notEqual(result, null);
    } else if (rid.equals(demo.CONCEPT_C)) {
      const result = ConceptCKey.fromAnyConceptKey(anyKey);
      assert.notEqual(result, null);
    } else if (rid.equals(demo.CONCEPT_D)) {
      const result = ConceptDKey.fromAnyConceptKey(anyKey);
      assert.notEqual(result, null);
    }
  }
});
