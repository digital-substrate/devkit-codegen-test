// The bridge to the Viper value: wrapValue takes a value without copying it, unwrapValue gives
// it back, and a constructor builds a new value -- copying one it is given, as the runtime's own
// constructors do.
import { test } from "node:test";
import { strict as assert } from "node:assert";
import dsviper from "@digitalsubstrate/dsviper";
import * as f from "../generated/dist/index.js";

const { StructureS, StructureT, ConceptAKey, ConceptDKey, EnumerationE } = f.demo;

test("wrapValue takes the value itself", () => {
  const value = new StructureS({ f_string: "a" }).unwrapValue();
  const wrapped = StructureS.wrapValue(value);
  wrapped.f_string = "b";
  assert.equal(value.at("f_string"), "b");
  assert.ok(wrapped.unwrapValue().equals(value));

  const vector = new f.Vector_of_uint8([1]).unwrapValue();
  f.Vector_of_uint8.wrapValue(vector).append(2);
  assert.equal(vector.size(), 2);

  const any = new dsviper.ValueAny(1);
  f.AnyValue.wrapValue(any).wrap(2);
  assert.equal(any.unwrap(), 2);

  const key = ConceptAKey.create();
  assert.ok(ConceptAKey.wrapValue(key.unwrapValue()).equals(key));
  assert.equal(EnumerationE.wrapValue(EnumerationE.unwrapValue(EnumerationE.B)), EnumerationE.B);
});

test("wrapValue refuses a value of another type", () => {
  assert.throws(() => StructureS.wrapValue(new StructureT().unwrapValue()), TypeError);
  assert.throws(() => f.Vector_of_uint8.wrapValue(new f.Vector_of_int8([1]).unwrapValue()), TypeError);
  assert.throws(() => ConceptAKey.wrapValue(ConceptDKey.create().unwrapValue()), TypeError);
});

test("a constructor copies the value it is given", () => {
  const value = new StructureS({ f_string: "a" }).unwrapValue();
  new StructureS(value).f_string = "b";
  assert.equal(value.at("f_string"), "a");

  const source = new f.Vector_of_uint8([1]);
  new f.Vector_of_uint8(source).append(2);
  new f.Vector_of_uint8(source.unwrapValue()).append(3);
  assert.deepEqual([...source], [1]);

  const any = new dsviper.ValueAny(1);
  new f.AnyValue(any).wrap(2);
  assert.equal(any.unwrap(), 1);
});

test("a copy is shallow", () => {
  const source = new f.Vector_of_Demo_StructureS([new StructureS({ f_string: "a" })]);
  const built = new f.Vector_of_Demo_StructureS(source);
  built.at(0).f_string = "b";
  assert.equal(source.at(0).f_string, "b");
});
