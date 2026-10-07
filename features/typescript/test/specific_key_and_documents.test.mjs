// A key narrows back to its instance's own key; a document is written as a field is; AnyValue is built
// from a value.
import { test } from "node:test";
import { strict as assert } from "node:assert";
import dsviper from "@digitalsubstrate/dsviper";
import * as f from "../generated/dist/index.js";
import * as ma from "../generated/dist/demo/attachments.js";

test("any view narrows back to the instance key", () => {
  const key = f.demo.ConceptCKey.create();
  assert.ok(f.demo.ConceptCKey.fromAnyConceptKey(key.toAnyConceptKey()).equals(key));
  assert.ok(key.toParentKey().toConceptCKey() instanceof f.demo.ConceptCKey);
  assert.ok(key.toParentKey().toConceptCKey().equals(key));
  assert.ok(new f.demo.KlubKey(key).toConceptCKey().equals(key));
});

test("no argument gives the invalid key", () => {
  assert.ok(!new f.demo.ConceptBKey().isValid());
  assert.ok(f.demo.ConceptBKey.create().isValid());
});

test("a key from an instance id and a runtime id", () => {
  const c = f.demo.ConceptCKey.create();
  assert.ok(new f.demo.ConceptBKey(c.instanceId(), c.runtimeId()).equals(c.toParentKey()));
  assert.ok(new f.demo.ConceptBKey(c.instanceId(), c.runtimeId()).toConceptCKey().equals(c));
  assert.ok(new f.demo.KlubKey(c.instanceId(), c.runtimeId()).toConceptCKey().equals(c));
  assert.throws(() => new f.demo.ConceptDKey(c.instanceId(), c.runtimeId()), TypeError);
  assert.throws(() => new f.demo.KlubKey(c.instanceId()), TypeError);
});

test("a document takes what its field would", () => {
  const db = dsviper.Database.createInMemory();
  db.extendDefinitions(f.definitions());
  const key = f.demo.ConceptAKey.create();
  db.beginTransaction();
  ma.ConceptA.propertiesSeInt8.set(db, key, [1, 2]);
  db.commit();
  assert.deepEqual([...ma.ConceptA.propertiesSeInt8.get(db, key).unwrap()].sort(), [1, 2]);
});

test("an AnyValue is built from a value", () => {
  assert.equal(new f.AnyValue(42).unwrap(), 42);
  assert.ok(new f.AnyValue().isNil());
});

test("a club refuses a key that is not a member's", () => {
  assert.throws(() => new f.demo.KlubKey(f.demo.ConceptAKey.create()), TypeError);
});
