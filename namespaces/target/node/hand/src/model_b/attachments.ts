/** ModelB — les attachments que ce namespace déclare.
 *
 * UN ATTACHMENT EST UN OBJET, PAS UNE FAMILLE DE FONCTIONS. Le pack écrit
 * `modelA_material_colour_get(getting, key)` : le namespace, le concept et le nom de
 * l'attachment collés dans un identifiant, parce qu'un module plat n'a aucun autre moyen de
 * les distinguer. Ici le module est le namespace, la classe est le concept et la propriété est
 * l'attachment — les trois parties du nom redeviennent trois portées.
 *
 * ET LA PORTÉE DU CONCEPT EST UNE CLASSE STATIQUE. En C++ c'était un namespace, en Python une
 * classe instanciée une fois ; ici une classe à membres statiques dit la même chose sans
 * qu'un objet existe — `Material.colour` et non `material.colour`.
 */
import dsviper from "@digitalsubstrate/dsviper";

import { AttachmentProxy } from "../_codegen/attachment.js";
import { definitions } from "../index.js";
import { Colour, MaterialKey } from "./data.js";

/** Les attachments portés par ModelB::Material. */
export class Material {
    static readonly colour = new AttachmentProxy<MaterialKey, Colour>(
        dsviper.ValueUUId.create("09eeb3f7-b0a6-9ad9-a80f-d2a85070ec08"),
        definitions, MaterialKey, Colour);
}
