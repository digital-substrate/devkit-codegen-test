// A variant and an any read as views: a variant field is its declared class, which tells,
// reads and writes each alternative by name, keys included; an any is a view whose content
// comes back as the generated class.
import { test } from "node:test";
import dsviper from "@digitalsubstrate/dsviper";
import { strict as assert } from "node:assert";
import * as c from "../generated/dist/containers.js";
import { AnyValue } from "../generated/dist/_codegen/registry.js";
import { ConceptAKey, ConceptDKey, StructureS, StructureU, StructureVariantKeys } from "../generated/dist/demo/data.js";

test("a variant field reads as its declared class", () => {
  const u = new StructureU({ f_variant: new StructureS({ f_float: 1 }) });
  assert.ok(u.f_variant instanceof c.Variant_of_string_or_uint8_or_Demo_StructureS);
  assert.ok(u.f_variant.isDemo_StructureS());
  assert.equal(u.f_variant.getDemo_StructureS().f_float, 1);
});

test("a variant changes in place", () => {
  const u = new StructureU({ f_variant: "x" });
  u.f_variant.setUint8(3);
  assert.ok(u.f_variant.isUint8());
  assert.equal(u.f_variant.unwrap(), 3);
  assert.throws(() => u.f_variant.getString(), RangeError);
});

test("key alternatives have their names", () => {
  const aKey = ConceptAKey.create();
  const v = new StructureVariantKeys({ f_target: aKey });
  assert.ok(v.f_target.isDemo_ConceptAKey());
  assert.ok(v.f_target.getDemo_ConceptAKey().equals(aKey));
  v.f_target.setDemo_ConceptDKey(ConceptDKey.create());
  assert.ok(v.f_target.getDemo_ConceptDKey() instanceof ConceptDKey);
});

test("an any reads as a view, takes a generated value and gives back the runtime value", () => {
  const u = new StructureU({ f_any: 42 });
  assert.ok(u.f_any instanceof AnyValue);
  assert.equal(u.f_any.unwrap(), 42);
  u.f_any = new StructureS({ f_string: "held" });
  assert.ok(u.f_any.unwrap() instanceof dsviper.ValueStructure);
  assert.equal(StructureS.wrapValue(u.f_any.unwrap()).f_string, "held");
  assert.ok(new StructureU().f_any.isNil());
});
