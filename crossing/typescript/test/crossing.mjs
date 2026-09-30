/** Containers, tested on the rendering of `Crossing`.
 *
 * No unit of the reference has a container field, and adding one would mean hand-writing
 * what the templates already produce. `Crossing` carries every shape of the type system
 * across two units, which is where the question really arises.
 */
import { Composites } from "../generated/dist/woven/data.js";
import * as core from "../generated/dist/core/data.js";
import * as parts from "../generated/dist/parts/data.js";

let ok = true;
const check = (label, condition) => {
    console.log(`  ${condition ? "ok  " : "FAIL "} ${label}`);
    ok &&= condition;
};

const c = new Composites();

c.f_vector = [new parts.Colour({ r: 1, g: 2, b: 3 }), new parts.Colour({ r: 4, g: 5, b: 6 })];
check("a vector yields a sequence", c.f_vector.length === 2);
check("and its elements carry their class",
      c.f_vector.at(0) instanceof parts.Colour && c.f_vector.at(0).r === 1);

c.f_optional = core.ThingKey.create();
check("an optional yields the value", c.f_optional instanceof core.ThingKey);

c.f_map_enum = [[core.Grade.LOW, new parts.Colour({ r: 7, g: 8, b: 9 })]];
// Iterating a map yields its keys, like a JavaScript `Map`; pairs are obtained through
// `entries()`, the same word the two sibling languages use.
const [key, value] = c.f_map_enum.entries()[0];
check("a map yields a mapping", c.f_map_enum.size === 1);
check("whose key is the model's enumeration", key === "low");
check("and the value carries its class", value instanceof parts.Colour && value.r === 7);

c.f_variant = new core.Colour({ r: 1, g: 1, b: 1 });
check("a variant yields the held alternative", c.f_variant instanceof core.Colour);

c.f_set = [core.ThingKey.create(), core.ThingKey.create()];
check("a set yields a sequence of typed keys",
      c.f_set.length === 2 && c.f_set.at(0) instanceof core.ThingKey);

// Two homonymous Colours, in two units, through a container: the founding case.
check("two homonymous Colours are not confused inside a container",
      c.f_vector.at(0) instanceof parts.Colour && !(c.f_vector.at(0) instanceof core.Colour));

process.exit(ok ? 0 : 1);
