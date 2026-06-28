import { test } from "node:test";
import { strict as assert } from "node:assert";
import dsviper from "@digitalsubstrate/dsviper";
import {
  Test_ConceptAKey, Test_ConceptBKey, Test_ConceptCKey,
  Test_StructureV, Test_StructureT, Test_StructureU,
  Set_int8, Map_int8_to_string, XArray_int8,
  definitions, databaseAttachments as db,
} from "../features/dist/index.js";

function createDatabase() {
  const database = dsviper.Database.createInMemory();
  database.extendDefinitions(definitions.definitions());
  return database;
}

// TestAttachmentKeys
test("keys_empty_initially", () => {
  const database = createDatabase();
  const keys = db.conceptA_Properties.keys(database);
  assert.equal(keys.size, 0);
});

test("keys_after_set", () => {
  const database = createDatabase();
  const key = Test_ConceptAKey.create();
  const value = new Test_StructureV();

  database.beginTransaction();
  db.conceptA_Properties.set(database, key, value);
  database.commit();

  const keys = db.conceptA_Properties.keys(database);
  assert.equal(keys.size, 1);
  assert.ok(keys.contains(key));
});

// TestAttachmentHas
test("has_absent", () => {
  const database = createDatabase();
  const key = Test_ConceptAKey.create();
  assert.ok(!db.conceptA_Properties.has(database, key));
});

test("has_present", () => {
  const database = createDatabase();
  const key = Test_ConceptAKey.create();
  const value = new Test_StructureV();

  database.beginTransaction();
  db.conceptA_Properties.set(database, key, value);
  database.commit();

  assert.ok(db.conceptA_Properties.has(database, key));
});

// TestAttachmentGetSet
test("get_absent_returns_nil", () => {
  const database = createDatabase();
  const key = Test_ConceptAKey.create();
  const result = db.conceptA_Properties.get(database, key);
  assert.ok(result.isNil());
});

test("set_then_get", () => {
  const database = createDatabase();
  const key = Test_ConceptAKey.create();
  const value = new Test_StructureV();
  value.f_bool = true;
  value.f_string = "test value";

  database.beginTransaction();
  db.conceptA_Properties.set(database, key, value);
  database.commit();

  const result = db.conceptA_Properties.get(database, key);

  assert.ok(!result.isNil());
  const retrieved = result.unwrap();
  assert.ok(retrieved.f_bool);
  assert.equal(retrieved.f_string, "test value");
});

test("overwrite_value", () => {
  const database = createDatabase();
  const key = Test_ConceptAKey.create();

  const value1 = new Test_StructureV();
  value1.f_string = "first";
  database.beginTransaction();
  db.conceptA_Properties.set(database, key, value1);
  database.commit();

  const value2 = new Test_StructureV();
  value2.f_string = "second";
  database.beginTransaction();
  db.conceptA_Properties.set(database, key, value2);
  database.commit();

  const result = db.conceptA_Properties.get(database, key);
  assert.equal(result.unwrap().f_string, "second");
});

// TestAttachmentDelete
test("delete_removes_entry", () => {
  const database = createDatabase();
  const key = Test_ConceptAKey.create();
  const value = new Test_StructureV();

  database.beginTransaction();
  db.conceptA_Properties.set(database, key, value);
  database.commit();

  assert.ok(db.conceptA_Properties.has(database, key));

  database.beginTransaction();
  db.conceptA_Properties.del(database, key);
  database.commit();

  assert.ok(!db.conceptA_Properties.has(database, key));
});

test("delete_absent_no_error", () => {
  const database = createDatabase();
  const key = Test_ConceptAKey.create();
  // Should not raise
  database.beginTransaction();
  db.conceptA_Properties.del(database, key);
  database.commit();
});

// TestAttachmentEnumerate
test("enumerate_empty", () => {
  const database = createDatabase();
  const items = [...db.conceptA_Properties.enumerate(database)];
  assert.equal(items.length, 0);
});

test("enumerate_entries", () => {
  const database = createDatabase();
  const key1 = Test_ConceptAKey.create();
  const key2 = Test_ConceptAKey.create();

  const value1 = new Test_StructureV();
  value1.f_string = "value1";
  const value2 = new Test_StructureV();
  value2.f_string = "value2";

  database.beginTransaction();
  db.conceptA_Properties.set(database, key1, value1);
  db.conceptA_Properties.set(database, key2, value2);
  database.commit();

  const items = [...db.conceptA_Properties.enumerate(database)];
  assert.equal(items.length, 2);

  const keys = items.map(([k]) => k);
  assert.ok(keys.some((k) => k.equals(key1)));
  assert.ok(keys.some((k) => k.equals(key2)));
});

// TestAttachmentInt8
test("set_get_int8", () => {
  const database = createDatabase();
  const key = Test_ConceptAKey.create();

  database.beginTransaction();
  db.conceptA_PropertiesInt8.set(database, key, 42);
  database.commit();

  const result = db.conceptA_PropertiesInt8.get(database, key);
  assert.ok(!result.isNil());
  assert.equal(result.unwrap(), 42);
});

test("negative_int8", () => {
  const database = createDatabase();
  const key = Test_ConceptAKey.create();

  database.beginTransaction();
  db.conceptA_PropertiesInt8.set(database, key, -100);
  database.commit();

  const result = db.conceptA_PropertiesInt8.get(database, key);
  assert.equal(result.unwrap(), -100);
});

// TestAttachmentSetInt8
test("set_get_set_int8", () => {
  const database = createDatabase();
  const key = Test_ConceptAKey.create();
  const value = new Set_int8([1, 2, 3]);

  database.beginTransaction();
  db.conceptA_PropertiesSeInt8.set(database, key, value);
  database.commit();

  const result = db.conceptA_PropertiesSeInt8.get(database, key);
  assert.ok(!result.isNil());
  const retrieved = result.unwrap();
  assert.equal(retrieved.size, 3);
});

// TestAttachmentMapInt8String
test("set_get_map", () => {
  const database = createDatabase();
  const key = Test_ConceptAKey.create();
  const value = new Map_int8_to_string([[1, "one"], [2, "two"]]);

  database.beginTransaction();
  db.conceptA_PropertiesMapInt8String.set(database, key, value);
  database.commit();

  const result = db.conceptA_PropertiesMapInt8String.get(database, key);
  assert.ok(!result.isNil());
  const retrieved = result.unwrap();
  assert.equal(retrieved.at(1), "one");
  assert.equal(retrieved.at(2), "two");
});

// TestAttachmentXArray
test("set_get_xarray", () => {
  const database = createDatabase();
  const key = Test_ConceptAKey.create();
  const value = new XArray_int8([10, 20, 30, 40]);

  database.beginTransaction();
  db.conceptA_PropertiesXArray.set(database, key, value);
  database.commit();

  const result = db.conceptA_PropertiesXArray.get(database, key);
  assert.ok(!result.isNil());
  const retrieved = result.unwrap();
  assert.equal(retrieved.size, 4);
});

// TestAttachmentConceptB
test("concept_b_attachment", () => {
  const database = createDatabase();
  const key = Test_ConceptBKey.create();
  const value = new Test_StructureT();
  value.field_string = "concept B value";

  database.beginTransaction();
  db.conceptB_PropertiesB.set(database, key, value);
  database.commit();

  const result = db.conceptB_PropertiesB.get(database, key);

  assert.ok(!result.isNil());
  assert.equal(result.unwrap().field_string, "concept B value");
});

// TestAttachmentConceptC
test("concept_c_attachment", () => {
  const database = createDatabase();
  const key = Test_ConceptCKey.create();
  const value = new Test_StructureU();
  value.f_uint8 = 255;
  value.f_string = "concept C value";

  database.beginTransaction();
  db.conceptC_PropertiesC.set(database, key, value);
  database.commit();

  const result = db.conceptC_PropertiesC.get(database, key);

  assert.ok(!result.isNil());
  const retrieved = result.unwrap();
  assert.equal(retrieved.f_uint8, 255);
  assert.equal(retrieved.f_string, "concept C value");
});

// TestMultipleAttachments
test("multiple_attachments_independent", () => {
  const database = createDatabase();
  const key = Test_ConceptAKey.create();

  // Set properties attachment
  const props = new Test_StructureV();
  props.f_string = "properties";
  database.beginTransaction();
  db.conceptA_Properties.set(database, key, props);
  database.commit();

  // Set propertiesInt8 attachment
  database.beginTransaction();
  db.conceptA_PropertiesInt8.set(database, key, 42);
  database.commit();

  // Verify both exist independently
  assert.ok(db.conceptA_Properties.has(database, key));
  assert.ok(db.conceptA_PropertiesInt8.has(database, key));

  // Delete one, other should remain
  database.beginTransaction();
  db.conceptA_Properties.del(database, key);
  database.commit();

  assert.ok(!db.conceptA_Properties.has(database, key));
  assert.ok(db.conceptA_PropertiesInt8.has(database, key));
});
