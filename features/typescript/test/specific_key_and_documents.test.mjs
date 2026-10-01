// A key gives back its instance's own key; a document is written as a field is; AnyValue is built
// from a value.
import { test } from "node:test";
import { strict as assert } from "node:assert";
import dsviper from "@digitalsubstrate/dsviper";
import * as f from "../generated/dist/index.js";

test("any view gives back the instance key", () => {
  const key = f.demo.ConceptCKey.create();
  for (const view of [key.toAnyConceptKey(), key.toParentKey(), new f.demo.KlubKey(key)]) {
    const specific = view.toConceptKey();
    assert.ok(specific instanceof f.demo.ConceptCKey);
    assert.ok(specific.equals(key));
  }
});

test("a document takes what its field would", () => {
  const db = dsviper.Database.createInMemory();
  db.extendDefinitions(f.definitions());
  const key = f.demo.ConceptAKey.create();
  db.beginTransaction();
  f.demo.attachments.ConceptA.propertiesSeInt8.set(db, key, [1, 2]);
  db.commit();
  assert.deepEqual([...f.demo.attachments.ConceptA.propertiesSeInt8.get(db, key).unwrap()].sort(), [1, 2]);
});

test("an AnyValue is built from a value", () => {
  assert.equal(new f.AnyValue(42).unwrap(), 42);
  assert.ok(new f.AnyValue().isNil());
});

test("a club refuses a key that is not a member's", () => {
  assert.throws(() => new f.demo.KlubKey(f.demo.ConceptAKey.create()), TypeError);
});
