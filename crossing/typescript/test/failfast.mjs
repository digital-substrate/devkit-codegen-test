/** Fail-fast, tested on the rendered package.
 *
 * A proxy holds nothing: it is an empty box around a `Value`, so every write reaches the
 * runtime, which raises its typed exception — fail-fast is inherited, not implemented. What
 * must be checked is that nothing in the generated layer intercepts or bypasses it.
 */
import dsviper from "@digitalsubstrate/dsviper";

import { definitions } from "../generated/dist/index.js";
import * as core from "../generated/dist/core/data.js";
import * as parts from "../generated/dist/parts/data.js";
import { Thing } from "../generated/dist/core/attachments.js";

let ok = true;
const mutating = new dsviper.CommitMutableState(new dsviper.CommitState(definitions())).attachmentMutating();

const refuses = (label, fn) => {
    try {
        fn();
        console.log(`  FAIL ${label} — passes without error`);
        ok = false;
    } catch {
        console.log(`  ok   ${label}`);
    }
};

refuses("a field rejects a string where a number is expected",
        () => { new core.Colour().r = "red"; });
refuses("a field rejects the Colour of another unit",
        () => { new core.Defaults().f_colour = new parts.Colour(); });
refuses("a container rejects an element of the wrong type",
        () => { new core.Bag().tints = [new parts.Colour()]; });
refuses("a key rejects the identifier of another concept",
        () => new core.ThingKey(core.OtherKey.create().unwrapValue()));
refuses("an attachment rejects a key of another concept",
        () => Thing.colour.set(mutating, core.OtherKey.create(), new core.Colour()));
refuses("an attachment rejects a document of the wrong type",
        () => Thing.colour.set(mutating, core.ThingKey.create(), new parts.Colour()));
refuses("wrapValue rejects a homonym structure of another namespace",
        () => core.Colour.wrapValue(new parts.Colour().unwrapValue()));
refuses("wrapValue rejects a homonym enumeration of another namespace",
        () => parts.Grade.wrapValue(core.Grade.unwrapValue(core.Grade.HIGH)));

process.exit(ok ? 0 : 1);
