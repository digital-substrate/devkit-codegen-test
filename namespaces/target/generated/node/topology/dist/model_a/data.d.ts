/** ModelA — les types que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";
import { Proxy } from "../_codegen/proxy.js";
import { AnyConceptKey } from "../_codegen/registry.js";
export declare const MATERIAL: dsviper.ValueUUId;
export declare const FINISH: dsviper.ValueUUId;
export declare const COLOUR: dsviper.ValueUUId;
/**
 * Une poignée sur une instance de ModelA::Material, pas la chose elle-même.
 *
 * A material, as ModelA understands one.
 */
export declare class MaterialKey extends Proxy<dsviper.ValueKey> {
    static concept(): dsviper.TypeConcept;
    /**
     * Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin --
     * l'appelant écrit déjà le nom de la classe.
     */
    static type(): dsviper.TypeKey;
    constructor(identifier?: dsviper.ValueKey | dsviper.ValueUUId);
    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create(): MaterialKey;
    static wrap(value: dsviper.Value): MaterialKey;
    get instanceId(): dsviper.ValueUUId;
    isValid(): boolean;
    /** La clé, vue sans son type. */
    toAny(): AnyConceptKey;
    toString(): string;
}
/** ModelA::Finish. Un type énuméré, pour que les templates en rencontrent un. Aucun autre namespace
n'en déclare, et c'est voulu : ce qui est testé ici est la topologie, pas le système de
types -- mais une couche qui ne sait pas sérialiser une énumération est incomplète. */
export type Finish = "matte" | "gloss";
/**
 * UN TYPE ET UNE VALEUR SOUS LE MÊME NOM, ce que TypeScript permet et qui dit exactement ce
 * qu'on veut : `Finish` annote, `Finish.matte` désigne, `Finish.wrap` convertit. Le pack en
 * fait une classe qui enveloppe une `ValueEnumeration` ; une union de littéraux se vérifie
 * mieux et ne coûte aucun objet.
 */
export declare const Finish: {
    matte: string;
    gloss: string;
    type(): dsviper.TypeEnumeration;
    wrap(value: dsviper.Value): Finish;
};
/** ModelA::Colour. Colour in 8-bit channels -- the same name as ModelB::Colour, a different type. */
export declare class Colour extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure;
    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>);
    static wrap(value: dsviper.Value): Colour;
    get r(): number;
    set r(value: number);
    get g(): number;
    set g(value: number);
    get b(): number;
    set b(value: number);
}
