import { test } from "node:test";
import { strict as assert } from "node:assert";
import dsviper from "@digitalsubstrate/dsviper";
import {
  Test_ConceptAKey, Test_StructureV,
  definitions, attachments as ma,
} from "../features/dist/index.js";

function createCommitState() {
  return new dsviper.CommitState(definitions.definitions());
}

// TestAttachmentGettingKeys
test("keys_empty_initially", () => {
  const state = createCommitState();
  const getting = state.attachmentGetting();
  const keys = ma.conceptA_Properties.keys(getting);
  assert.equal(keys.size, 0);
});

// TestAttachmentMutatingSetGet
test("set_then_get", () => {
  const state = createCommitState();
  const key = Test_ConceptAKey.create();
  const value = new Test_StructureV();
  value.f_string = "test";
  value.f_bool = true;

  // Mutate
  const mutable = new dsviper.CommitMutableState(state);
  const mutating = mutable.attachmentMutating();
  ma.conceptA_Properties.set(mutating, key, value);

  // Read back from mutable state (sees uncommitted changes)
  const getting = mutable.attachmentGetting();
  const result = ma.conceptA_Properties.get(getting, key);
  assert.ok(!result.isNil());
  const retrieved = result.unwrap();
  assert.equal(retrieved.f_string, "test");
  assert.ok(retrieved.f_bool);
});

test("uncommitted_changes_visible_in_mutable_state", () => {
  const state = createCommitState();
  const key = Test_ConceptAKey.create();
  const value = new Test_StructureV();
  value.f_string = "uncommitted";

  const mutable = new dsviper.CommitMutableState(state);
  const mutating = mutable.attachmentMutating();
  ma.conceptA_Properties.set(mutating, key, value);

  // Read within same mutable state (should see uncommitted changes)
  const getting = mutable.attachmentGetting();
  const result = ma.conceptA_Properties.get(getting, key);
  assert.ok(!result.isNil());
  assert.equal(result.unwrap().f_string, "uncommitted");
});

// TestCommitFieldUpdate
test("set_f_bool", () => {
  const state = createCommitState();
  const key = Test_ConceptAKey.create();
  const value = new Test_StructureV();
  value.f_bool = false;

  const mutable = new dsviper.CommitMutableState(state);
  const mutating = mutable.attachmentMutating();
  ma.conceptA_Properties.set(mutating, key, value);

  // Update single field
  ma.conceptA_Properties.setF_bool(mutating, key, true);

  const getting = mutable.attachmentGetting();
  const result = ma.conceptA_Properties.get(getting, key);
  assert.ok(result.unwrap().f_bool);
});

test("set_f_uint8", () => {
  const state = createCommitState();
  const key = Test_ConceptAKey.create();
  const value = new Test_StructureV();

  const mutable = new dsviper.CommitMutableState(state);
  const mutating = mutable.attachmentMutating();
  ma.conceptA_Properties.set(mutating, key, value);

  ma.conceptA_Properties.setF_uint8(mutating, key, 255);

  const getting = mutable.attachmentGetting();
  const result = ma.conceptA_Properties.get(getting, key);
  assert.equal(result.unwrap().f_uint8, 255);
});

test("set_f_string", () => {
  const state = createCommitState();
  const key = Test_ConceptAKey.create();
  const value = new Test_StructureV();
  value.f_string = "original";

  const mutable = new dsviper.CommitMutableState(state);
  const mutating = mutable.attachmentMutating();
  ma.conceptA_Properties.set(mutating, key, value);

  ma.conceptA_Properties.setF_string(mutating, key, "modified");

  const getting = mutable.attachmentGetting();
  const result = ma.conceptA_Properties.get(getting, key);
  assert.equal(result.unwrap().f_string, "modified");
});

// TestCommitDiffKeys
test("diff_keys_added", () => {
  const state = createCommitState();
  const key = Test_ConceptAKey.create();
  const value = new Test_StructureV();
  value.f_string = "test";

  // "before" state: empty
  const mutableBefore = new dsviper.CommitMutableState(state);
  const before = mutableBefore.attachmentGetting();

  // "after" state: with an added entry
  const mutableAfter = new dsviper.CommitMutableState(state);
  ma.conceptA_Properties.set(mutableAfter.attachmentMutating(), key, value);
  const after = mutableAfter.attachmentGetting();

  // diffKeys(current, other): added = keys in other but not current
  const [added, removed, different, same] = ma.conceptA_Properties.diffKeys(before, after);
  assert.equal(added.size, 1);
  assert.ok(added.contains(key));
  assert.equal(removed.size, 0);
  assert.equal(different.size, 0);
  assert.equal(same.size, 0);
});

test("diff_keys_removed", () => {
  const state = createCommitState();
  const key = Test_ConceptAKey.create();
  const value = new Test_StructureV();
  value.f_string = "test";

  // "before" state: with entry
  const mutableBefore = new dsviper.CommitMutableState(state);
  ma.conceptA_Properties.set(mutableBefore.attachmentMutating(), key, value);
  const before = mutableBefore.attachmentGetting();

  // "after" state: empty
  const mutableAfter = new dsviper.CommitMutableState(state);
  const after = mutableAfter.attachmentGetting();

  // diffKeys(current, other): removed = keys in current but not other
  const [added, removed, different, same] = ma.conceptA_Properties.diffKeys(before, after);
  assert.equal(added.size, 0);
  assert.equal(removed.size, 1);
  assert.ok(removed.contains(key));
  assert.equal(different.size, 0);
  assert.equal(same.size, 0);
});

test("diff_keys_different", () => {
  const state = createCommitState();
  const key = Test_ConceptAKey.create();

  // "before" state: key -> "first"
  const mutableBefore = new dsviper.CommitMutableState(state);
  const value1 = new Test_StructureV();
  value1.f_string = "first";
  ma.conceptA_Properties.set(mutableBefore.attachmentMutating(), key, value1);
  const before = mutableBefore.attachmentGetting();

  // "after" state: key -> "second"
  const mutableAfter = new dsviper.CommitMutableState(state);
  const value2 = new Test_StructureV();
  value2.f_string = "second";
  ma.conceptA_Properties.set(mutableAfter.attachmentMutating(), key, value2);
  const after = mutableAfter.attachmentGetting();

  // diffKeys(current, other): different = keys in both with different values
  const [added, removed, different, same] = ma.conceptA_Properties.diffKeys(before, after);
  assert.equal(added.size, 0);
  assert.equal(removed.size, 0);
  assert.equal(different.size, 1);
  assert.ok(different.contains(key));
  assert.equal(same.size, 0);
});

test("diff_keys_same", () => {
  const state = createCommitState();
  const key = Test_ConceptAKey.create();
  const value = new Test_StructureV();
  value.f_string = "unchanged";

  // "before" state: key -> value
  const mutableBefore = new dsviper.CommitMutableState(state);
  ma.conceptA_Properties.set(mutableBefore.attachmentMutating(), key, value);
  const before = mutableBefore.attachmentGetting();

  // "after" state: key -> same value
  const mutableAfter = new dsviper.CommitMutableState(state);
  ma.conceptA_Properties.set(mutableAfter.attachmentMutating(), key, value);
  const after = mutableAfter.attachmentGetting();

  // diffKeys(current, other): same = keys in both with identical values
  const [added, removed, different, same] = ma.conceptA_Properties.diffKeys(before, after);
  assert.equal(added.size, 0);
  assert.equal(removed.size, 0);
  assert.equal(different.size, 0);
  assert.equal(same.size, 1);
  assert.ok(same.contains(key));
});

// TestCommitEnumerate
test("enumerate_entries", () => {
  const state = createCommitState();
  const key1 = Test_ConceptAKey.create();
  const key2 = Test_ConceptAKey.create();

  const value1 = new Test_StructureV();
  value1.f_string = "one";
  const value2 = new Test_StructureV();
  value2.f_string = "two";

  const mutable = new dsviper.CommitMutableState(state);
  const mutating = mutable.attachmentMutating();
  ma.conceptA_Properties.set(mutating, key1, value1);
  ma.conceptA_Properties.set(mutating, key2, value2);

  const getting = mutable.attachmentGetting();
  const items = [...ma.conceptA_Properties.enumerate(getting)];
  assert.equal(items.length, 2);

  const keys = items.map(([k]) => k);
  assert.ok(keys.some((k) => k.equals(key1)));
  assert.ok(keys.some((k) => k.equals(key2)));
});

// TestCommitHas
test("has_absent", () => {
  const state = createCommitState();
  const key = Test_ConceptAKey.create();
  const getting = state.attachmentGetting();
  assert.ok(!ma.conceptA_Properties.has(getting, key));
});

test("has_present", () => {
  const state = createCommitState();
  const key = Test_ConceptAKey.create();
  const value = new Test_StructureV();

  const mutable = new dsviper.CommitMutableState(state);
  const mutating = mutable.attachmentMutating();
  ma.conceptA_Properties.set(mutating, key, value);

  const getting = mutable.attachmentGetting();
  assert.ok(ma.conceptA_Properties.has(getting, key));
});

// TestCommitDiff
test("diff_updates_existing", () => {
  const state = createCommitState();
  const key = Test_ConceptAKey.create();

  const value1 = new Test_StructureV();
  value1.f_string = "original";
  value1.f_uint8 = 10;

  const mutable = new dsviper.CommitMutableState(state);
  const mutating = mutable.attachmentMutating();
  ma.conceptA_Properties.set(mutating, key, value1);

  // Use diff to update only changed fields
  const value2 = new Test_StructureV();
  value2.f_string = "modified";
  value2.f_uint8 = 10; // Same value

  ma.conceptA_Properties.diff(mutating, key, value2);

  const getting = mutable.attachmentGetting();
  const result = ma.conceptA_Properties.get(getting, key);
  assert.equal(result.unwrap().f_string, "modified");
});
