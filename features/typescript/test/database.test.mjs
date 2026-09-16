import { test } from "node:test";
import { strict as assert } from "node:assert";
import dsviper from "@digitalsubstrate/dsviper";
import { ConceptAKey, ConceptBKey, ConceptCKey, StructureV, StructureT, StructureU } from "../generated/dist/demo/data.js";
import { Set_int8, Map_int8_to_string, XArray_int8 } from "../generated/dist/containers.js";
import { definitions } from "../generated/dist/index.js";
import * as db from "../generated/dist/demo/attachments.js";

function createDatabase() {
  const database = dsviper.Database.createInMemory();
  database.extendDefinitions(definitions());
  return database;
}

// TestAttachmentKeys
test("keys_empty_initially", () => {
  const database = createDatabase();
  const keys = db.ConceptA.properties.keys(database);
  assert.equal(keys.size, 0);
});

test("keys_after_set", () => {
  const database = createDatabase();
  const key = ConceptAKey.create();
  const value = new StructureV();

  database.beginTransaction();
  db.ConceptA.properties.set(database, key, value);
  database.commit();

  const keys = db.ConceptA.properties.keys(database);
  assert.equal(keys.size, 1);
  assert.ok(keys.contains(key));
});

// TestAttachmentHas
test("has_absent", () => {
  const database = createDatabase();
  const key = ConceptAKey.create();
  assert.ok(!db.ConceptA.properties.has(database, key));
});

test("has_present", () => {
  const database = createDatabase();
  const key = ConceptAKey.create();
  const value = new StructureV();

  database.beginTransaction();
  db.ConceptA.properties.set(database, key, value);
  database.commit();

  assert.ok(db.ConceptA.properties.has(database, key));
});

// TestAttachmentGetSet
test("get_absent_returns_nil", () => {
  const database = createDatabase();
  const key = ConceptAKey.create();
  const result = db.ConceptA.properties.get(database, key);
  assert.ok((result === undefined));
});

test("set_then_get", () => {
  const database = createDatabase();
  const key = ConceptAKey.create();
  const value = new StructureV();
  value.f_bool = true;
  value.f_string = "test value";

  database.beginTransaction();
  db.ConceptA.properties.set(database, key, value);
  database.commit();

  const result = db.ConceptA.properties.get(database, key);

  assert.ok(!(result === undefined));
  const retrieved = result;
  assert.ok(retrieved.f_bool);
  assert.equal(retrieved.f_string, "test value");
});

test("overwrite_value", () => {
  const database = createDatabase();
  const key = ConceptAKey.create();

  const value1 = new StructureV();
  value1.f_string = "first";
  database.beginTransaction();
  db.ConceptA.properties.set(database, key, value1);
  database.commit();

  const value2 = new StructureV();
  value2.f_string = "second";
  database.beginTransaction();
  db.ConceptA.properties.set(database, key, value2);
  database.commit();

  const result = db.ConceptA.properties.get(database, key);
  assert.equal(result.f_string, "second");
});

// TestAttachmentDelete
test("delete_removes_entry", () => {
  const database = createDatabase();
  const key = ConceptAKey.create();
  const value = new StructureV();

  database.beginTransaction();
  db.ConceptA.properties.set(database, key, value);
  database.commit();

  assert.ok(db.ConceptA.properties.has(database, key));

  database.beginTransaction();
  db.ConceptA.properties.delete(database, key);
  database.commit();

  assert.ok(!db.ConceptA.properties.has(database, key));
});

test("delete_absent_no_error", () => {
  const database = createDatabase();
  const key = ConceptAKey.create();
  // Should not raise
  database.beginTransaction();
  db.ConceptA.properties.delete(database, key);
  database.commit();
});

// TestAttachmentEnumerate
test("enumerate_empty", () => {
  const database = createDatabase();
  const items = [...db.ConceptA.properties.enumerate(database)];
  assert.equal(items.length, 0);
});

test("enumerate_entries", () => {
  const database = createDatabase();
  const key1 = ConceptAKey.create();
  const key2 = ConceptAKey.create();

  const value1 = new StructureV();
  value1.f_string = "value1";
  const value2 = new StructureV();
  value2.f_string = "value2";

  database.beginTransaction();
  db.ConceptA.properties.set(database, key1, value1);
  db.ConceptA.properties.set(database, key2, value2);
  database.commit();

  const items = [...db.ConceptA.properties.enumerate(database)];
  assert.equal(items.length, 2);

  const keys = items.map(([k]) => k);
  assert.ok(keys.some((k) => k.equals(key1)));
  assert.ok(keys.some((k) => k.equals(key2)));
});

// TestAttachmentInt8
test("set_get_int8", () => {
  const database = createDatabase();
  const key = ConceptAKey.create();

  database.beginTransaction();
  db.ConceptA.propertiesInt8.set(database, key, 42);
  database.commit();

  const result = db.ConceptA.propertiesInt8.get(database, key);
  assert.ok(!(result === undefined));
  assert.equal(result, 42);
});

test("negative_int8", () => {
  const database = createDatabase();
  const key = ConceptAKey.create();

  database.beginTransaction();
  db.ConceptA.propertiesInt8.set(database, key, -100);
  database.commit();

  const result = db.ConceptA.propertiesInt8.get(database, key);
  assert.equal(result, -100);
});

// TestAttachmentSetInt8
test("set_get_set_int8", () => {
  const database = createDatabase();
  const key = ConceptAKey.create();
  const value = new Set_int8([1, 2, 3]);

  database.beginTransaction();
  db.ConceptA.propertiesSeInt8.set(database, key, value);
  database.commit();

  const result = db.ConceptA.propertiesSeInt8.get(database, key);
  assert.ok(!(result === undefined));
  const retrieved = result;
  assert.equal(retrieved.size, 3);
});

// TestAttachmentMapInt8String
test("set_get_map", () => {
  const database = createDatabase();
  const key = ConceptAKey.create();
  const value = new Map_int8_to_string([[1, "one"], [2, "two"]]);

  database.beginTransaction();
  db.ConceptA.propertiesMapInt8String.set(database, key, value);
  database.commit();

  const result = db.ConceptA.propertiesMapInt8String.get(database, key);
  assert.ok(!(result === undefined));
  const retrieved = result;
  assert.equal(retrieved.at(1), "one");
  assert.equal(retrieved.at(2), "two");
});

// TestAttachmentXArray
test("set_get_xarray", () => {
  const database = createDatabase();
  const key = ConceptAKey.create();
  const value = new XArray_int8([10, 20, 30, 40]);

  database.beginTransaction();
  db.ConceptA.propertiesXArray.set(database, key, value);
  database.commit();

  const result = db.ConceptA.propertiesXArray.get(database, key);
  assert.ok(!(result === undefined));
  const retrieved = result;
  assert.equal(retrieved.size, 4);
});

// TestAttachmentConceptB
test("concept_b_attachment", () => {
  const database = createDatabase();
  const key = ConceptBKey.create();
  const value = new StructureT();
  value.field_string = "concept B value";

  database.beginTransaction();
  db.ConceptB.propertiesB.set(database, key, value);
  database.commit();

  const result = db.ConceptB.propertiesB.get(database, key);

  assert.ok(!(result === undefined));
  assert.equal(result.field_string, "concept B value");
});

// TestAttachmentConceptC
test("concept_c_attachment", () => {
  const database = createDatabase();
  const key = ConceptCKey.create();
  const value = new StructureU();
  value.f_uint8 = 255;
  value.f_string = "concept C value";

  database.beginTransaction();
  db.ConceptC.propertiesC.set(database, key, value);
  database.commit();

  const result = db.ConceptC.propertiesC.get(database, key);

  assert.ok(!(result === undefined));
  const retrieved = result;
  assert.equal(retrieved.f_uint8, 255);
  assert.equal(retrieved.f_string, "concept C value");
});

// TestMultipleAttachments
test("multiple_attachments_independent", () => {
  const database = createDatabase();
  const key = ConceptAKey.create();

  // Set properties attachment
  const props = new StructureV();
  props.f_string = "properties";
  database.beginTransaction();
  db.ConceptA.properties.set(database, key, props);
  database.commit();

  // Set propertiesInt8 attachment
  database.beginTransaction();
  db.ConceptA.propertiesInt8.set(database, key, 42);
  database.commit();

  // Verify both exist independently
  assert.ok(db.ConceptA.properties.has(database, key));
  assert.ok(db.ConceptA.propertiesInt8.has(database, key));

  // Delete one, other should remain
  database.beginTransaction();
  db.ConceptA.properties.delete(database, key);
  database.commit();

  assert.ok(!db.ConceptA.properties.has(database, key));
  assert.ok(db.ConceptA.propertiesInt8.has(database, key));
});
