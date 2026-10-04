/** A club key designates a member, or an instance of a concept that descends from one.
 *
 * `Woven::Weave` declares `Core::Thing` as a member; `Core::SubThing` and `Woven::Derived`
 * descend from it. The runtime makes a club key from any of them, and the generated C++
 * accepts them through its member's key: the TypeScript key accepts them too.
 */
import * as core from "../generated/dist/core/data.js";
import * as woven from "../generated/dist/woven/data.js";

let ok = true;
const check = (label, condition) => {
    console.log(`  ${condition ? "ok  " : "FAIL "} ${label}`);
    ok &&= condition;
};
const same = (a, b) => a.instanceId().encoded() === b.instanceId().encoded();

const derived = woven.DerivedKey.create();
const weave = new woven.WeaveKey(derived.toParentKey());
check("a key of a descendant, held as its member's key, makes a club key", same(weave, derived));
check("which reads back as the member's key", weave.toCoreThingKey() !== undefined);
check("and not as the other member's", weave.toPartsThingKey() === undefined);

const sub = core.SubThingKey.create();
check("a key of a descendant itself makes a club key", same(new woven.WeaveKey(sub), sub));
check("fromAnyConceptKey accepts a descendant",
      woven.WeaveKey.fromAnyConceptKey(sub.toAnyConceptKey()) !== undefined);
check("fromAnyConceptKey still answers undefined outside the club",
      woven.WeaveKey.fromAnyConceptKey(core.OtherKey.create().toAnyConceptKey()) === undefined);

let refused = false;
try {
    new woven.WeaveKey(core.OtherKey.create());
} catch (error) {
    refused = error instanceof TypeError;
}
check("a key outside the club is refused", refused);

if (!ok) process.exit(1);
