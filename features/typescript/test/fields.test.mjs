// A field's name and path, as constants (feature Fields): a constant completes and tsc checks it,
// where a string literal is neither. The name is the model's own; the path addresses that field,
// to read it or to write it alone.
import { test } from "node:test";
import { strict as assert } from "node:assert";
import dsviper from "@digitalsubstrate/dsviper";
import { definitions } from "../generated/dist/index.js";
import * as data from "../generated/dist/demo/data.js";
import * as fields from "../generated/dist/demo/fields.js";
import * as paths from "../generated/dist/demo/paths.js";
import * as ma from "../generated/dist/demo/attachments.js";

const constants = (cls) => Object.fromEntries(Object.keys(cls).map((k) => [k, cls[k]]));

test("every structure names every field as the model does", () => {
  for (const [name, cls] of Object.entries(fields)) {
    const declared = data[name].type().fields().map((f) => f.name()).sort();
    assert.deepEqual(Object.values(constants(cls)).sort(), declared, name);
  }
});

test("every path reads its field", () => {
  for (const [name, cls] of Object.entries(paths)) {
    const value = dsviper.Value.create(data[name].type());
    for (const [attribute, path] of Object.entries(constants(cls))) {
      const field = fields[name][attribute];
      assert.equal(String(path), String(dsviper.Path.fromField(field).const()), `${name}.${attribute}`);
      assert.ok(path.at(value, false).equals(value.at(field, false)), `${name}.${attribute}`);
    }
  }
});

test("a path reads a value it was not built from", () => {
  assert.equal(paths.StructureS.f_float.at(new data.StructureS({ f_float: 1.5 }).unwrapValue()), 1.5);
});

test("a path writes its field alone", () => {
  const mutable = new dsviper.CommitMutableState(new dsviper.CommitState(definitions()));
  const m = mutable.attachmentMutating();
  const key = data.ConceptAKey.create();
  ma.ConceptA.properties.set(m, key, new data.StructureV({ f_vector: [1] }));
  m.update(ma.ConceptA.properties.descriptor, key.unwrapValue(), paths.StructureV.f_vector, [7, 8]);
  const document = ma.ConceptA.properties.get(m, key).unwrap();
  assert.deepEqual([...document.f_vector], [7, 8]);
  assert.equal(document.f_bool, true);
});
