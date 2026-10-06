// What console.log shows of a generated object: its class's name and what it holds, as Node
// shows an object, an array, a Set or a Map -- never the symbol that holds the Viper value.

import { test } from "node:test";
import { strict as assert } from "node:assert";
import { inspect } from "node:util";
import { AnyValue } from "../generated/dist/index.js";
import { ConceptAKey, ConceptCKey, StructureS, StructureT, StructureU, StructureV } from "../generated/dist/demo/data.js";

const shown = (value, options = {}) => inspect(value, { breakLength: Infinity, ...options });

test("a structure shows its class and its fields", () => {
  assert.equal(shown(new StructureS({ f_float: 1.5, f_string: "hi" })),
               "StructureS { f_float: 1.5, f_string: 'hi' }");
});

test("a nested structure shows its own class", () => {
  const t = new StructureT({ field_string: "outer", field_structure_s: new StructureS({ f_string: "in" }) });
  assert.equal(shown(t), "StructureT { field_string: 'outer', field_structure_s: StructureS { f_float: 0, f_string: 'in' } }");
});

test("the depth is Node's: a level past it shows the class in brackets", () => {
  assert.match(shown(new StructureV(), { depth: 0 }), /^StructureV \{ f_bool: true, .* f_S: \[StructureS\], f_T: \[StructureT\] \}$/);
});

test("a key shows its instance id, and the instance's concept when it is not the view's", () => {
  const c = ConceptCKey.create();
  const id = c.instanceId().encoded();
  assert.equal(shown(c), `ConceptCKey(${id})`);
  assert.equal(shown(c.toParentKey()), `ConceptBKey(${id}, Demo::ConceptC)`);
  assert.equal(shown(c.toAnyConceptKey()), `AnyConceptKey(${id}, Demo::ConceptC)`);
  assert.equal(shown(new ConceptAKey()), "ConceptAKey(00000000-0000-0000-0000-000000000000)");
});

test("a container shows its class, its size where it varies, and its elements", () => {
  const v = new StructureV();
  assert.equal(shown(v.f_vector), "Vector_of_uint8(3) [ 1, 2, 3 ]");
  assert.equal(shown(v.f_set), "Set_of_uint8(3) { 1, 2, 3 }");
  assert.equal(shown(v.f_map), "Map_of_uint8_to_string(2) { 0 => 'Zero', 1 => 'One' }");
  assert.equal(shown(v.f_vec), "Vec2_of_uint8 [ 2, 3 ]");
  assert.equal(shown(v.f_mat), "Mat2x3_of_uint8 [ [ 1, 2, 3 ], [ 4, 5, 6 ] ]");
  assert.equal(shown(v.f_tuple), "Tuple_of_uint8_and_string [ 0, '1' ]");
  assert.equal(shown(v.f_optional), "Optional_of_uint8(8)");
  const u = new StructureU();
  assert.equal(shown(u.f_optional), "Optional_of_uint8(nil)");
  assert.equal(shown(u.f_xarray), "XArray_of_uint8(0) []");
  assert.equal(shown(u.f_variant), "Variant_of_string_or_uint8_or_Demo_StructureS('')");
  assert.equal(shown(new AnyValue(42)), "AnyValue(42)");
});

test("String() and JSON keep the value's own text", () => {
  const s = new StructureS({ f_float: 1.5, f_string: "hi" });
  assert.equal(String(s), "{f_float=1.5, f_string='hi'}");
  assert.equal(JSON.stringify(s), '{"f_float":1.5,"f_string":"hi"}');
});
