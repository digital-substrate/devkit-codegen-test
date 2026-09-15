/** Les conteneurs, éprouvés sur le rendu de `Crossing`.
 *
 * AUCUNE UNITÉ DE LA RÉFÉRENCE N'A DE CHAMP CONTENEUR, et lui en ajouter reviendrait à écrire
 * à la main ce que les templates produisent déjà. `Crossing` porte toutes les formes du
 * système de types traversant deux unités : c'est là que la question se pose vraiment.
 */
import { Composites } from "./dist/woven/data.js";
import * as core from "./dist/core/data.js";
import * as parts from "./dist/parts/data.js";

let ok = true;
const check = (label, condition) => {
    console.log(`  ${condition ? "ok  " : "ÉCHEC"} ${label}`);
    ok &&= condition;
};

const c = new Composites();

c.f_vector = [new parts.Colour({ r: 1, g: 2, b: 3 }), new parts.Colour({ r: 4, g: 5, b: 6 })];
check("un vector rend une suite", c.f_vector.length === 2);
check("et ses éléments portent leur classe",
      c.f_vector.at(0) instanceof parts.Colour && c.f_vector.at(0).r === 1);

c.f_optional = core.ThingKey.create();
check("un optional rend la valeur", c.f_optional instanceof core.ThingKey);

c.f_map_enum = [[core.Grade.low, new parts.Colour({ r: 7, g: 8, b: 9 })]];
const [key, value] = [...c.f_map_enum][0];
check("une map rend une correspondance", c.f_map_enum.size === 1);
check("dont la clé est l'énumération du modèle", key === "low");
check("et la valeur porte sa classe", value instanceof parts.Colour && value.r === 7);

c.f_variant = new core.Colour({ r: 1, g: 1, b: 1 });
check("un variant rend l'alternative tenue", c.f_variant instanceof core.Colour);

c.f_set = [core.ThingKey.create(), core.ThingKey.create()];
check("un set rend une suite de clés typées",
      c.f_set.length === 2 && c.f_set.at(0) instanceof core.ThingKey);

// Deux Colour homonymes, dans deux unités, à travers un conteneur : le cas fondateur.
check("deux Colour homonymes ne se confondent pas dans un conteneur",
      c.f_vector.at(0) instanceof parts.Colour && !(c.f_vector.at(0) instanceof core.Colour));

process.exit(ok ? 0 : 1);
