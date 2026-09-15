/** Topology — le modèle, et ce qu'aucune unité ne peut revendiquer.
 *
 * ÉCRIT DEPUIS LE MODÈLE ET DEPUIS TYPESCRIPT, pas depuis le C++ ni depuis Python. Ce qui a
 * tenu ailleurs tenait *parce que* C++ ou *parce que* Python ; ce qui change ici n'est pas
 * l'écriture mais la réponse.
 *
 * TROIS CHOSES QUE CE LANGAGE DÉCIDE AUTREMENT :
 *
 *  - `instanceof` dit la vérité. La liaison Node déclare une vraie hiérarchie et l'expose à
 *    l'exécution, là où la liaison Python annonce `ValueStructure(Value)` dans son `.pyi` et
 *    ne le tient pas. La base commune n'existe donc ici que pour ne pas répéter, et non pour
 *    permettre de reconnaître.
 *  - `Map` et `Set` indexent par identité et n'appellent aucune méthode. Une clé générée n'y
 *    est donc pas utilisable telle quelle : le runtime offre `hashKey()`, un bigint qui replie
 *    le type dans le hachage, et c'est *lui* qu'on indexe. Ni le C++ — où `operator<` suffit —
 *    ni Python — où `__hash__` et `__eq__` font le travail — n'ont ce problème.
 *  - un entier 64 bits est un `bigint`, pas un `number`.
 */
import { dirname, join } from "node:path";
import { fileURLToPath } from "node:url";

import dsviper from "@digitalsubstrate/dsviper";

let cached: dsviper.DefinitionsConst | undefined;

/** Le modèle, tel que le runtime le connaît.
 *
 * Assemblé depuis le `.dsm` ici, parce que c'est une référence et qu'elle doit pouvoir
 * tourner. Un paquet livré embarque le document compressé et le décode — même objet, même
 * résultat, et c'est la seule différence entre ce fichier et celui qui sera généré.
 */
export function definitions(): dsviper.DefinitionsConst {
    if (cached === undefined) {
        const here = dirname(fileURLToPath(import.meta.url));
        const source = join(here, "..", "..", "..", "..", "definitions");
        const [report, , parsed] = dsviper.DSMBuilder.assemble(source).parse();
        if (report.hasError() || parsed === undefined) {
            throw new Error(report.errors().map((e) => e.message()).join("\n"));
        }
        cached = parsed;
    }
    return cached;
}
