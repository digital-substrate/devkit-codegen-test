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
    constructor(identifier?: dsviper.ValueKey | dsviper.ValueUUId | null);
    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create(): PlayerKey;
    static wrap(value: dsviper.Value): PlayerKey;
    static decode(blob: dsviper.ValueBlob): PlayerKey;
    instanceId(): dsviper.ValueUUId;
    runtimeId(): dsviper.ValueUUId;
    isValid(): boolean;
    /** Un ordre total sur les clés — ce qui permet de trier, que JavaScript ne déduit pas. */
    compareTo(other: PlayerKey | dsviper.ValueKey): number;
    /** L'instance et son type, dits comme le modèle les nomme. */
    description(): string;
    isKnown(): boolean;
    /** La clé, vue sans son type. */
    toAnyConceptKey(): AnyConceptKey;
    /** La clé non typée, retypée — ou `undefined` si elle ne désigne pas ce concept.
     *
     * LE CHEMIN DE RETOUR, ET IL PEUT ÉCHOUER. Élargir ne perd rien ; rétrécir pose une
     * question dont la réponse est dans l'identifiant que la valeur porte.
     */
    static fromAnyConceptKey(key: AnyConceptKey | dsviper.ValueKey): PlayerKey | undefined;
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
    BEGINNER: string;
    INTERMEDIATE: string;
    EXPERT: string;
    type(): dsviper.TypeEnumeration;
    wrap(value: dsviper.Value): Level;
    /** Depuis le nom d'un cas, et depuis rien d'autre. */
    fromStr(name: string): Level;
    /** Le nom d'un cas — qui *est* le cas, puisqu'un littéral porte son propre nom. */
    name(held: Level): string;
    /** Le rang d'un cas, tel que le modèle les numérote. */
    index(held: Level): number;
    /** La valeur du runtime derrière un cas — ce qui porte l'encodage et l'empreinte. */
    value(held: Level): dsviper.ValueEnumeration;
    encode(held: Level): dsviper.ValueBlob;
    decode(blob: dsviper.ValueBlob): Level;
    hexdigest(held: Level): string;
};
/** Demo::PlayerProperty. */
export declare class PlayerProperty extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure;
    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>);
    static wrap(value: dsviper.Value): PlayerProperty;
    static decode(blob: dsviper.ValueBlob): PlayerProperty;
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
    static decode(blob: dsviper.ValueBlob): Vector3;
    get x(): number;
    set x(value: number);
    get y(): number;
    set y(value: number);
    get z(): number;
    set z(value: number);
}
