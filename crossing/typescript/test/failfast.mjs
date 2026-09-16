/** Le fail-fast, éprouvé sur le rendu.
 *
 * UN PROXY NE DÉTIENT RIEN : c'est une boîte vide devant une `Value`. Toute écriture atteint
 * donc le runtime, qui lève son exception typée — le fail-fast est hérité, pas implémenté. Ce
 * qu'il faut vérifier n'est pas qu'on l'a écrit, mais que rien dans la couche générée ne
 * l'intercepte ni ne le contourne.
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
        console.log(`  ÉCHEC ${label} — passe sans erreur`);
        ok = false;
    } catch {
        console.log(`  ok   ${label}`);
    }
};

refuses("un champ refuse une chaîne là où un nombre est attendu",
        () => { new core.Colour().r = "rouge"; });
refuses("un champ refuse la Colour d'une autre unité",
        () => { new core.Defaults().f_colour = new parts.Colour(); });
refuses("un conteneur refuse un élément du mauvais type",
        () => { new core.Bag().tints = [new parts.Colour()]; });
refuses("une clé refuse l'identifiant d'un autre concept",
        () => new core.ThingKey(core.OtherKey.create().value));
refuses("un attachment refuse une clé d'un autre concept",
        () => Thing.colour.set(mutating, core.OtherKey.create(), new core.Colour()));
refuses("un attachment refuse un document du mauvais type",
        () => Thing.colour.set(mutating, core.ThingKey.create(), new parts.Colour()));

process.exit(ok ? 0 : 1);
