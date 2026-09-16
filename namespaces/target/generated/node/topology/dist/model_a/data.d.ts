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
    constructor(identifier?: dsviper.ValueKey | dsviper.ValueUUId | null);
    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create(): MaterialKey;
    static wrap(value: dsviper.Value): MaterialKey;
    static decode(blob: dsviper.ValueBlob): MaterialKey;
    instanceId(): dsviper.ValueUUId;
    runtimeId(): dsviper.ValueUUId;
    isValid(): boolean;
    /** Un ordre total sur les clés — ce qui permet de trier, que JavaScript ne déduit pas. */
    compareTo(other: MaterialKey | dsviper.ValueKey): number;
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
    static fromAnyConceptKey(key: AnyConceptKey | dsviper.ValueKey): MaterialKey | undefined;
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
    MATTE: string;
    GLOSS: string;
    type(): dsviper.TypeEnumeration;
    wrap(value: dsviper.Value): Finish;
    /** Depuis le nom d'un cas, et depuis rien d'autre. */
    fromStr(name: string): Finish;
    /** Le nom d'un cas — qui *est* le cas, puisqu'un littéral porte son propre nom. */
    name(held: Finish): string;
    /** Le rang d'un cas, tel que le modèle les numérote. */
    index(held: Finish): number;
    /** La valeur du runtime derrière un cas — ce qui porte l'encodage et l'empreinte. */
    value(held: Finish): dsviper.ValueEnumeration;
    encode(held: Finish): dsviper.ValueBlob;
    decode(blob: dsviper.ValueBlob): Finish;
    hexdigest(held: Finish): string;
};
/** ModelA::Colour. Colour in 8-bit channels -- the same name as ModelB::Colour, a different type. */
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
