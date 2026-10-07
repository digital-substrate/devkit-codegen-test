// A field's name and path, as constants (feature Fields): a constant completes and tsc checks it,
// where a string literal is neither. The name is the model's own; the path reads that field.
import { test } from "node:test";
import { strict as assert } from "node:assert";
import { StructureS } from "../generated/dist/demo/data.js";
import * as fields from "../generated/dist/demo/fields.js";
import * as paths from "../generated/dist/demo/paths.js";

test("a field name is the model's name", () => {
  assert.equal(fields.StructureS.f_float, "f_float");
});

test("a path reads the field in a value", () => {
  const s = new StructureS({ f_float: 1.5 });
  assert.equal(paths.StructureS.f_float.at(s.unwrapValue()), 1.5);
});
