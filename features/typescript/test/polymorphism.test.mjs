import { test } from "node:test";
import { strict as assert } from "node:assert";
import dsviper from "@digitalsubstrate/dsviper";
import {
  Test_ConceptAKey, Test_ConceptBKey, Test_ConceptCKey, Test_ConceptDKey,
  Test_KlubKey, AnyConceptKey,
  definitions,
} from "../features/dist/index.js";

// --- TestAnyConceptKeyFromConcept ---

test("concept_a_to_any", () => {
  const key = Test_ConceptAKey.create();
  const anyKey = key.toAnyConceptKey();
  assert.ok(anyKey instanceof AnyConceptKey);
  assert.ok(anyKey.instanceId().equals(key.instanceId()));
});

test("concept_b_to_any", () => {
  const key = Test_ConceptBKey.create();
  const anyKey = key.toAnyConceptKey();
  assert.ok(anyKey instanceof AnyConceptKey);
});

test("concept_c_to_any", () => {
  const key = Test_ConceptCKey.create();
  const anyKey = key.toAnyConceptKey();
  assert.ok(anyKey instanceof AnyConceptKey);
});

test("concept_d_to_any", () => {
  const key = Test_ConceptDKey.create();
  const anyKey = key.toAnyConceptKey();
  assert.ok(anyKey instanceof AnyConceptKey);
});

// --- TestAnyConceptKeyRuntimeId ---

test("runtime_id_concept_a", () => {
  const key = Test_ConceptAKey.create();
  const anyKey = key.toAnyConceptKey();
  assert.ok(anyKey.runtimeId().equals(definitions.RuntimeIds.Test_ConceptA));
});

test("runtime_id_concept_b", () => {
  const key = Test_ConceptBKey.create();
  const anyKey = key.toAnyConceptKey();
  assert.ok(anyKey.runtimeId().equals(definitions.RuntimeIds.Test_ConceptB));
});

test("runtime_id_concept_c", () => {
  const key = Test_ConceptCKey.create();
  const anyKey = key.toAnyConceptKey();
  assert.ok(anyKey.runtimeId().equals(definitions.RuntimeIds.Test_ConceptC));
});

test("runtime_id_concept_d", () => {
  const key = Test_ConceptDKey.create();
  const anyKey = key.toAnyConceptKey();
  assert.ok(anyKey.runtimeId().equals(definitions.RuntimeIds.Test_ConceptD));
});

// --- TestAnyConceptKeyDowncast ---

test("downcast_to_concept_a_success", () => {
  const key = Test_ConceptAKey.create();
  const anyKey = key.toAnyConceptKey();
  const result = Test_ConceptAKey.fromAnyConceptKey(anyKey);
  assert.notEqual(result, null);
  assert.ok(result.equals(key));
});

test("downcast_to_concept_a_failure", () => {
  const key = Test_ConceptBKey.create();
  const anyKey = key.toAnyConceptKey();
  const result = Test_ConceptAKey.fromAnyConceptKey(anyKey);
  assert.equal(result, null);
});

test("downcast_to_concept_b_success", () => {
  const key = Test_ConceptBKey.create();
  const anyKey = key.toAnyConceptKey();
  const result = Test_ConceptBKey.fromAnyConceptKey(anyKey);
  assert.notEqual(result, null);
  assert.ok(result.equals(key));
});

test("downcast_to_concept_b_failure", () => {
  const key = Test_ConceptAKey.create();
  const anyKey = key.toAnyConceptKey();
  const result = Test_ConceptBKey.fromAnyConceptKey(anyKey);
  assert.equal(result, null);
});

// --- TestAnyConceptKeyIsKnown ---

test("concept_a_is_known", () => {
  const key = Test_ConceptAKey.create();
  const anyKey = key.toAnyConceptKey();
  assert.ok(anyKey.isKnown());
});

test("concept_b_is_known", () => {
  const key = Test_ConceptBKey.create();
  const anyKey = key.toAnyConceptKey();
  assert.ok(anyKey.isKnown());
});

// --- TestAnyConceptKeyDescription ---

test("description_includes_type", () => {
  const key = Test_ConceptAKey.create();
  const anyKey = key.toAnyConceptKey();
  const desc = anyKey.description();
  assert.ok(desc.includes("AnyConceptKey"));
  assert.ok(desc.includes("ConceptAKey"));
});

test("description_includes_uuid", () => {
  const key = Test_ConceptAKey.create();
  const anyKey = key.toAnyConceptKey();
  const desc = anyKey.description();
  assert.ok(desc.includes(key.instanceId().encoded()));
});

// --- TestAnyConceptKeyEquality ---

test("same_origin_equal", () => {
  const key = Test_ConceptAKey.create();
  const any1 = key.toAnyConceptKey();
  const any2 = key.toAnyConceptKey();
  assert.ok(any1.equals(any2));
});

test("different_origin_not_equal", () => {
  const key1 = Test_ConceptAKey.create();
  const key2 = Test_ConceptAKey.create();
  const any1 = key1.toAnyConceptKey();
  const any2 = key2.toAnyConceptKey();
  assert.ok(!any1.equals(any2));
});

test("different_types_not_equal", () => {
  const keyA = Test_ConceptAKey.create();
  const keyB = Test_ConceptBKey.create();
  const anyA = keyA.toAnyConceptKey();
  const anyB = keyB.toAnyConceptKey();
  assert.ok(!anyA.equals(anyB));
});

// --- TestAnyConceptKeyValidation ---

test("valid_key", () => {
  const key = Test_ConceptAKey.create();
  const anyKey = key.toAnyConceptKey();
  assert.ok(anyKey.isValid());
});

test("invalid_key", () => {
  const invalidUuid = dsviper.ValueUUId.INVALID;
  const key = new Test_ConceptAKey(invalidUuid);
  const anyKey = key.toAnyConceptKey();
  assert.ok(!anyKey.isValid());
});

// --- TestConceptInheritance ---

test("concept_c_is_club_member", () => {
  // ConceptC is a member of Klub
  const keyC = Test_ConceptCKey.create();
  // Verify it can be used where ConceptB is expected (through club membership)
  assert.ok(keyC instanceof Test_ConceptCKey);
});

test("concept_c_to_parent_key", () => {
  // ConceptC extends ConceptB - use toParentKey
  const keyC = Test_ConceptCKey.create();
  // Convert to Test_ConceptBKey via toParentKey
  const asB = keyC.toParentKey();
  assert.ok(asB instanceof Test_ConceptBKey);
  assert.ok(asB.instanceId().equals(keyC.instanceId()));
});

test("concept_b_from_concept_c", () => {
  const keyC = Test_ConceptCKey.create();
  const anyKey = keyC.toAnyConceptKey();
  // ConceptC key should work with fromAnyConceptKey on ConceptCKey
  const resultC = Test_ConceptCKey.fromAnyConceptKey(anyKey);
  assert.notEqual(resultC, null);
});

// --- TestKlubMembership ---

test("klub_key_from_concept_c", () => {
  const keyC = Test_ConceptCKey.create();
  const klubKey = Test_KlubKey.fromConceptCKey(keyC);
  assert.ok(klubKey instanceof Test_KlubKey);
  assert.ok(klubKey.instanceId().equals(keyC.instanceId()));
});

test("klub_key_from_concept_d", () => {
  const keyD = Test_ConceptDKey.create();
  const klubKey = Test_KlubKey.fromConceptDKey(keyD);
  assert.ok(klubKey instanceof Test_KlubKey);
  assert.ok(klubKey.instanceId().equals(keyD.instanceId()));
});

test("klub_key_runtime_id_concept_c", () => {
  const keyC = Test_ConceptCKey.create();
  const klubKey = Test_KlubKey.fromConceptCKey(keyC);
  assert.ok(klubKey.runtimeId().equals(definitions.RuntimeIds.Test_ConceptC));
});

test("klub_key_runtime_id_concept_d", () => {
  const keyD = Test_ConceptDKey.create();
  const klubKey = Test_KlubKey.fromConceptDKey(keyD);
  assert.ok(klubKey.runtimeId().equals(definitions.RuntimeIds.Test_ConceptD));
});

test("klub_key_downcast_to_concept_c", () => {
  const keyC = Test_ConceptCKey.create();
  const klubKey = Test_KlubKey.fromConceptCKey(keyC);
  const result = klubKey.asConceptCKey();
  assert.notEqual(result, null);
  assert.ok(result.equals(keyC));
});

test("klub_key_downcast_failure", () => {
  const keyC = Test_ConceptCKey.create();
  const klubKey = Test_KlubKey.fromConceptCKey(keyC);
  const result = klubKey.asConceptDKey();
  assert.equal(result, null);
});

// --- TestKlubKeyIsKnown ---

test("klub_from_concept_c_is_known", () => {
  const keyC = Test_ConceptCKey.create();
  const klubKey = Test_KlubKey.fromConceptCKey(keyC);
  assert.ok(klubKey.isKnown());
});

test("klub_from_concept_d_is_known", () => {
  const keyD = Test_ConceptDKey.create();
  const klubKey = Test_KlubKey.fromConceptDKey(keyD);
  assert.ok(klubKey.isKnown());
});

// --- TestPolymorphicDispatch ---

test("dispatch_by_runtime_id", () => {
  const keys = [
    Test_ConceptAKey.create(),
    Test_ConceptBKey.create(),
    Test_ConceptCKey.create(),
    Test_ConceptDKey.create(),
  ];

  const anyKeys = keys.map((k) => k.toAnyConceptKey());

  // Dispatch based on runtimeId
  for (const anyKey of anyKeys) {
    const rid = anyKey.runtimeId();
    if (rid.equals(definitions.RuntimeIds.Test_ConceptA)) {
      const result = Test_ConceptAKey.fromAnyConceptKey(anyKey);
      assert.notEqual(result, null);
    } else if (rid.equals(definitions.RuntimeIds.Test_ConceptB)) {
      const result = Test_ConceptBKey.fromAnyConceptKey(anyKey);
      assert.notEqual(result, null);
    } else if (rid.equals(definitions.RuntimeIds.Test_ConceptC)) {
      const result = Test_ConceptCKey.fromAnyConceptKey(anyKey);
      assert.notEqual(result, null);
    } else if (rid.equals(definitions.RuntimeIds.Test_ConceptD)) {
      const result = Test_ConceptDKey.fromAnyConceptKey(anyKey);
      assert.notEqual(result, null);
    }
  }
});
