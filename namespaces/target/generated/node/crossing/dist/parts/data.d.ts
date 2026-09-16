/** Parts — les types que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";
import { Proxy } from "../_codegen/proxy.js";
import { AnyConceptKey } from "../_codegen/registry.js";
export declare const THING: dsviper.ValueUUId;
export declare const GRADE: dsviper.ValueUUId;
export declare const COLOUR: dsviper.ValueUUId;
/**
 * Une poignée sur une instance de Parts::Thing, pas la chose elle-même.
 *
 * Le même nom que Core::Thing, et rien de commun.
 */
export declare class ThingKey extends Proxy<dsviper.ValueKey> {
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
    static create(): ThingKey;
    static wrap(value: dsviper.Value): ThingKey;
    static decode(blob: dsviper.ValueBlob): ThingKey;
    instanceId(): dsviper.ValueUUId;
    runtimeId(): dsviper.ValueUUId;
    isValid(): boolean;
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
    static fromAnyConceptKey(key: AnyConceptKey | dsviper.ValueKey): ThingKey | undefined;
    toString(): string;
}
/** Parts::Grade. Le même nom que Core::Grade, des cases différentes. */
export type Grade = "soft" | "hard";
/**
 * UN TYPE ET UNE VALEUR SOUS LE MÊME NOM, ce que TypeScript permet et qui dit exactement ce
 * qu'on veut : `Grade` annote, `Grade.soft` désigne, `Grade.wrap` convertit. Le pack en
 * fait une classe qui enveloppe une `ValueEnumeration` ; une union de littéraux se vérifie
 * mieux et ne coûte aucun objet.
 */
export declare const Grade: {
    SOFT: string;
    HARD: string;
    type(): dsviper.TypeEnumeration;
    wrap(value: dsviper.Value): Grade;
    /** Depuis le nom d'un cas, et depuis rien d'autre. */
    fromStr(name: string): Grade;
    /** Le nom d'un cas — qui *est* le cas, puisqu'un littéral porte son propre nom. */
    name(held: Grade): string;
    /** Le rang d'un cas, tel que le modèle les numérote. */
    index(held: Grade): number;
    /** La valeur du runtime derrière un cas — ce qui porte l'encodage et l'empreinte. */
    value(held: Grade): dsviper.ValueEnumeration;
    encode(held: Grade): dsviper.ValueBlob;
    decode(blob: dsviper.ValueBlob): Grade;
    hexdigest(held: Grade): string;
};
/** Parts::Colour. Le même nom que Core::Colour, en virgule flottante. */
export declare class Colour extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure;
    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>);
    static wrap(value: dsviper.Value): Colour;
    static decode(blob: dsviper.ValueBlob): Colour;
    get r(): number;
    set r(value: number);
    get g(): number;
    set g(value: number);
    get b(): number;
    set b(value: number);
}
