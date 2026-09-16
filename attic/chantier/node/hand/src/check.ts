/** Ce que la référence Node permet, exécuté.
 *
 * `tsc` dit que les annotations tiennent ; il ne dit pas qu'un attachment écrit ni qu'une base
 * relit. Les deux servent, et celui-ci est le second.
 */
import dsviper from "@digitalsubstrate/dsviper";

import { definitions } from "./index.js";
import * as modelA from "./model_a/data.js";
import * as modelB from "./model_b/data.js";
import { Material as MaterialA } from "./model_a/attachments.js";
import { Material as MaterialB } from "./model_b/attachments.js";
import * as tools from "./tools/pool.js";

let ok = true;

function check(label: string, condition: boolean): void {
    console.log(`  ${condition ? "ok  " : "ÉCHEC"} ${label}`);
    ok &&= condition;
}

// Les mêmes noms, deux namespaces, aucun renommage -- ce qui a tout déclenché.
const a = new modelA.Colour({ r: 1, g: 2, b: 3 });
const b = new modelB.Colour({ r: 4, g: 5, b: 6 });
check("deux Colour homonymes coexistent", a.constructor !== b.constructor);
check("et gardent leurs types du modèle",
      a.value.type().representation() === "ModelA::Colour"
      && b.value.type().representation() === "ModelB::Colour");

// Les champs sont des accesseurs : le nom et l'accès sont la même chose.
a.r = 9;
check("un champ se lit et s'écrit par son nom", a.r === 9);

// Une clé est une poignée, et deux clés neuves diffèrent.
const k1 = modelA.MaterialKey.create();
const k2 = modelA.MaterialKey.create();
check("deux clés neuves diffèrent", !k1.equals(k2));

// ET C'EST ICI QUE JAVASCRIPT SE DISTINGUE. Une `Map` indexe par identité : deux clés égales
// mais distinctes y seraient deux entrées. Le jeton du runtime est ce qui rend l'indexation
// par valeur possible, et il n'a d'équivalent ni en C++ ni en Python.
const sameInstance = new modelA.MaterialKey(k1.value);
const byIdentity = new Map([[k1, "premier"]]);
check("une Map indexe par identité, donc une clé égale n'y est pas trouvée",
      byIdentity.get(sameInstance) === undefined);
const byValue = new Map([[k1.hashKey(), "premier"]]);
check("le jeton du runtime, lui, indexe par valeur",
      byValue.get(sameInstance.hashKey()) === "premier");

// Les clés des deux unités ne se confondent pas.
check("les clés des deux unités ont des types distincts",
      !modelA.MaterialKey.type().equals(modelB.MaterialKey.type()));

// ── un attachment, sur un état en mémoire ──
const state = new dsviper.CommitState(definitions());
const mutable = new dsviper.CommitMutableState(state);
const mutating = mutable.attachmentMutating();

const key = modelA.MaterialKey.create();
check("un attachment neuf ne connaît pas la clé", !MaterialA.colour.has(mutating, key));

MaterialA.colour.set(mutating, key, new modelA.Colour({ r: 1, g: 2, b: 3 }));
check("après écriture, la clé est connue", MaterialA.colour.has(mutating, key));

const read = MaterialA.colour.get(mutating, key);
check("et le document revient typé", read instanceof modelA.Colour && read.r === 1);
check("les clés de l'attachment sont typées",
      MaterialA.colour.keys(mutating).toArray().every((k) => k instanceof modelA.MaterialKey));

// Un champ seul, adressé par son nom -- ce que le pack appelle un chemin et met dans un module.
MaterialA.colour.update(mutating, key, "r", 9);
check("un seul champ s'écrit par son nom", MaterialA.colour.get(mutating, key)?.r === 9);

check("une clé absente rend undefined",
      MaterialA.colour.get(mutating, modelA.MaterialKey.create()) === undefined);

// Deux attachments homonymes, sur deux concepts homonymes, dans deux unités.
check("deux attachments homonymes ont des descripteurs distincts",
      !MaterialA.colour.descriptor.runtimeId().equals(MaterialB.colour.descriptor.runtimeId()));

// ── et le même attachment, sur une base ──
const database = dsviper.Database.createInMemory();
database.extendDefinitions(definitions());
database.beginTransaction();
check("l'écriture sur base rend un statut",
      MaterialA.colour.set(database, key, new modelA.Colour({ r: 4, g: 5, b: 6 })) === true);
check("et se relit par les mêmes appels", MaterialA.colour.get(database, key)?.g === 5);
check("le retrait est la seule opération que la base ajoute",
      MaterialA.colour.delete(database, key) === true);
check("après retrait, la clé n'est plus connue", !MaterialA.colour.has(database, key));
database.commit();
database.close();

// ── un pool ──
check("un pool porte son identité du modèle",
      tools.UUID.encoded() === "17e63428-03e1-41d7-ad9d-60c5665bbd66");

console.log();
console.log(`definitions : ${definitions().concepts().length} concepts, `
            + `${definitions().structures().length} structures, `
            + `${definitions().attachments().length} attachments`);

process.exit(ok ? 0 : 1);
