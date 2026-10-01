// Where the host's own collections enter: a field takes its declared class or, when nothing in
// it is generated, the host's collection; a declared container's constructor takes generated
// elements, each checked where the container is built.
import { test } from "node:test";
import { strict as assert } from "node:assert";
import * as c from "../generated/dist/containers.js";
import { StructureS, StructureU, StructureV } from "../generated/dist/demo/data.js";

const s1 = new StructureS({ f_float: 1 });
const s2 = new StructureS({ f_float: 2 });

test("a declared container takes its generated elements", () => {
  assert.equal(new c.Set_of_Demo_StructureS([s1, s2]).size, 2);
  assert.equal(new c.XArray_of_Demo_StructureS([s1, s2]).size, 2);
  assert.ok(new c.Map_of_string_to_Demo_StructureS(new Map([["k", s1]])).at("k").equals(s1));
});

test("a wrong element is refused where the container is built", () => {
  assert.throws(() => new c.Set_of_Demo_StructureS([s1, 3]), TypeError);
});

test("a field takes a host collection of primitives", () => {
  const u = new StructureU();
  u.f_vector = [1, 2, 3];
  u.f_set = new Set([4, 5]);
  assert.equal(u.f_vector.size, 3);
  assert.equal(new StructureV({ f_vector: [7], f_map: new Map([[1, "one"]]) }).f_vector.size, 1);
});

test("a field refuses a host collection of generated values", () => {
  const u = new StructureU();
  assert.throws(() => { u.f_set_s = [s1]; }, TypeError);
});
