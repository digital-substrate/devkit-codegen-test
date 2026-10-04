// The bridge to the Viper value: a generated class is a box around one. wrapValue and a
// constructor given a value box it without copying, unwrapValue gives it back, and a copy is
// explicit.
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

test("wrapValue refuses a value of another kind", () => {
  const text = dsviper.Value.create(dsviper.Type.STRING, "a");
  for (const wrap of [StructureS.wrapValue, ConceptAKey.wrapValue, f.demo.KlubKey.wrapValue, EnumerationE.wrapValue,
                      f.AnyValue.wrapValue, f.AnyConceptKey.wrapValue, f.Vector_of_uint8.wrapValue]) {
    assert.throws(() => wrap(text), TypeError);
  }
});

test("a constructor boxes the value it is given", () => {
  const value = new StructureS({ f_string: "a" }).unwrapValue();
  new StructureS(value).f_string = "b";
  assert.equal(value.at("f_string"), "b");

  const source = new f.Vector_of_uint8([1]);
  new f.Vector_of_uint8(source).append(2);
  new f.Vector_of_uint8(source.unwrapValue()).append(3);
  assert.deepEqual([...source], [1, 2, 3]);

  const any = new dsviper.ValueAny(1);
  new f.AnyValue(any).wrap(2);
  assert.equal(any.unwrap(), 2);
});

test("a container built from elements keeps them, whatever its kind", () => {
  const built = [
    (s) => new f.Vector_of_Demo_StructureS([s]).at(0),
    (s) => new f.XArray_of_Demo_StructureS([s]).at(0),
    (s) => new f.Map_of_string_to_Demo_StructureS([["k", s]]).at("k"),
    (s) => new f.Map_of_string_to_Demo_StructureS(new Map([["k", s]])).at("k"),
    (s) => new f.Optional_of_Demo_StructureS(s).unwrap(),
  ];
  for (const read of built) {
    const s = new StructureS({ f_string: "a" });
    const held = read(s);
    s.f_string = "b";
    assert.equal(held.f_string, "b");
  }
});

test("a copy is explicit", () => {
  const value = new StructureS({ f_string: "a" }).unwrapValue();
  new StructureS(value.copy()).f_string = "b";
  assert.equal(value.at("f_string"), "a");
});

test("a proxy and a container sort by the runtime's order", () => {
  const xs = [3, 1, 2].map((x) => new StructureS({ f_float: x }));
  assert.deepEqual(xs.sort((a, b) => a.compare(b)).map((s) => s.f_float), [1, 2, 3]);
  assert.equal(new f.Vector_of_uint8([2]).compare(new f.Vector_of_uint8([1])), 1);
});
