/** ModelB — les types que ce namespace déclare.
 *
 * UN NAMESPACE EST UN MODULE, ET C'EST GRATUIT. Le pack met tout dans un `data.ts` et aplatit
 * en `Test_StructureS` ; ici `ModelB::Colour` est `topology/model_a` et `ModelB::Colour` est
 * `topology/model_b`. Les deux coexistent sans qu'un nom bouge — ce qui a déclenché tout ce
 * chantier coûte, ici comme en Python, une arborescence de fichiers.
 *
 * ET LES CHAMPS SONT DES ACCESSEURS, ce qui fait disparaître la couche 2 du C++. Là-bas il
 * fallait `Fields::Colour::r` pour nommer un champ et `rPath()` pour l'adresser ; `colour.r`
 * est déjà les deux.
 */
import dsviper from "@digitalsubstrate/dsviper";
import { Proxy } from "../_codegen/proxy.js";
export declare const MATERIAL: dsviper.ValueUUId;
export declare const COLOUR: dsviper.ValueUUId;
/** Une poignée sur une instance de ModelB::Material, pas la chose elle-même. */
export declare class MaterialKey extends Proxy<dsviper.ValueKey> {
    static concept(): dsviper.TypeConcept;
    /** Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin —
     * l'appelant écrit déjà le nom de la classe.
     */
    static type(): dsviper.TypeKey;
    constructor(identifier?: dsviper.ValueKey | dsviper.ValueUUId);
    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create(): MaterialKey;
    static wrap(value: dsviper.Value): MaterialKey;
    get instanceId(): dsviper.ValueUUId;
    isValid(): boolean;
    toString(): string;
}
/** Une couleur en canaux 8 bits — le même nom que ModelB::Colour, un type différent. */
export declare class Colour extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure;
    constructor(value?: dsviper.ValueStructure | {
        r?: number;
        g?: number;
        b?: number;
    });
    static wrap(value: dsviper.Value): Colour;
    get r(): number;
    set r(value: number);
    get g(): number;
    set g(value: number);
    get b(): number;
    set b(value: number);
    toString(): string;
}
