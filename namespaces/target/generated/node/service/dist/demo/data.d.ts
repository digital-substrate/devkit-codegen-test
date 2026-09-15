/** Demo — les types que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";
import { Proxy } from "../_codegen/proxy.js";
import { AnyConceptKey } from "../_codegen/registry.js";
export declare const PLAYER: dsviper.ValueUUId;
export declare const LEVEL: dsviper.ValueUUId;
export declare const PLAYER_PROPERTY: dsviper.ValueUUId;
export declare const VECTOR_3: dsviper.ValueUUId;
/**
 * Une poignée sur une instance de Demo::Player, pas la chose elle-même.
 */
export declare class PlayerKey extends Proxy<dsviper.ValueKey> {
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
    static create(): PlayerKey;
    static wrap(value: dsviper.Value): PlayerKey;
    get instanceId(): dsviper.ValueUUId;
    isValid(): boolean;
    /** La clé, vue sans son type. */
    toAny(): AnyConceptKey;
    toString(): string;
}
/** Demo::Level. */
export type Level = "beginner" | "intermediate" | "expert";
/**
 * UN TYPE ET UNE VALEUR SOUS LE MÊME NOM, ce que TypeScript permet et qui dit exactement ce
 * qu'on veut : `Level` annote, `Level.beginner` désigne, `Level.wrap` convertit. Le pack en
 * fait une classe qui enveloppe une `ValueEnumeration` ; une union de littéraux se vérifie
 * mieux et ne coûte aucun objet.
 */
export declare const Level: {
    beginner: string;
    intermediate: string;
    expert: string;
    type(): dsviper.TypeEnumeration;
    wrap(value: dsviper.Value): Level;
};
/** Demo::PlayerProperty. */
export declare class PlayerProperty extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure;
    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>);
    static wrap(value: dsviper.Value): PlayerProperty;
    get nickname(): string;
    set nickname(value: string);
    get level(): Level;
    set level(value: Level);
}
/** Demo::Vector3. */
export declare class Vector3 extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure;
    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>);
    static wrap(value: dsviper.Value): Vector3;
    get x(): number;
    set x(value: number);
    get y(): number;
    set y(value: number);
    get z(): number;
    set z(value: number);
}
