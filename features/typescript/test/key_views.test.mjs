// One instance, many views: a key's conversions keep its instance.
import { test } from "node:test";
import { strict as assert } from "node:assert";
import { AnyConceptKey } from "../generated/dist/_codegen/proxy.js";
import { ConceptAKey, ConceptBKey, ConceptCKey, ConceptDKey, KlubKey, StructureU } from "../generated/dist/demo/data.js";

const views = () => {
  const c = ConceptCKey.create();
  return { c, b: c.toParentKey(), a: c.toAnyConceptKey() };
};

test("a parent key has the parent static type, and a parent slot accepts it", () => {
  const { b } = views();
  assert.ok(b.vprValue.typeKey().equals(ConceptBKey.type()));
  const u = new StructureU({ f_B: b });
  assert.ok(u.f_B instanceof ConceptBKey && u.f_B.equals(b));
});

test("views of one instance are equal and hash alike", () => {
  const { a, b, c } = views();
  assert.ok(b.equals(c) && c.equals(a));
  assert.equal(b.hashKey(), c.hashKey());
  assert.equal(c.hashKey(), a.hashKey());
});

test("fromAnyConceptKey accepts a descendant", () => {
  const { a, b } = views();
  assert.ok(ConceptBKey.fromAnyConceptKey(a).equals(b));
  assert.equal(ConceptDKey.fromAnyConceptKey(a), undefined);
  assert.throws(() => new ConceptDKey(b.vprValue), TypeError);
});

test("narrowing and widening by name", () => {
  const { a, b, c } = views();
  assert.ok(b.toConceptCKey() instanceof ConceptCKey && b.toConceptCKey().equals(c));
  assert.equal(ConceptBKey.create().toConceptCKey(), undefined);
  assert.ok(ConceptBKey.fromConceptCKey(c).equals(b));
});

test("a club converts to and from its members", () => {
  const { a, c } = views();
  const k = KlubKey.fromConceptCKey(c);
  assert.ok(k.toConceptCKey().equals(c));
  assert.equal(k.toConceptDKey(), undefined);
  assert.ok(KlubKey.fromAnyConceptKey(a).equals(k));
});

test("a field reads the class of its static type", () => {
  const { a, c } = views();
  const u = new StructureU({ f_Klub: KlubKey.fromConceptCKey(c), f_any_concept: a });
  assert.ok(u.f_Klub instanceof KlubKey);
  assert.ok(u.f_any_concept instanceof AnyConceptKey);
  assert.ok(new StructureU().f_A instanceof ConceptAKey);
});

test("the constructor takes exactly its static type", () => {
  const { c } = views();
  assert.throws(() => new ConceptBKey(c.vprValue), TypeError);
  assert.ok(new AnyConceptKey(c).equals(c.toAnyConceptKey()));
});

test("a description names the instance concept when the view differs", () => {
  const { b, c } = views();
  const name = c.instanceId().encoded();
  assert.equal(`${c}`, `${name}:Demo::ConceptCKey`);
  assert.equal(`${b}`, `${name}:Demo::ConceptBKey(Demo::ConceptCKey)`);
  assert.equal(`${KlubKey.fromConceptCKey(c)}`, `${name}:Demo::KlubKey(Demo::ConceptCKey)`);
});
