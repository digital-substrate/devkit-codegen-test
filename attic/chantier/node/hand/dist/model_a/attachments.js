/** ModelA — les attachments que ce namespace déclare.
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
/** Les attachments portés par ModelA::Material. */
export class Material {
    static colour = new AttachmentProxy(dsviper.ValueUUId.create("faf658ea-5586-890a-0c4a-5cd2c9209b28"), definitions, MaterialKey, Colour);
}
