/** ModelC — les types que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";
import { Proxy } from "../_codegen/proxy.js";
import { AnyConceptKey } from "../_codegen/registry.js";
export declare const MARKER: dsviper.ValueUUId;
/**
 * Une poignée sur une instance de ModelC::Marker, pas la chose elle-même.
 *
 * Something a projection can point at, and nothing else refers to.
 */
export declare class MarkerKey extends Proxy<dsviper.ValueKey> {
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
    static create(): MarkerKey;
    static wrap(value: dsviper.Value): MarkerKey;
    static decode(blob: dsviper.ValueBlob): MarkerKey;
    instanceId(): dsviper.ValueUUId;
    runtimeId(): dsviper.ValueUUId;
    isValid(): boolean;
    /** Un ordre total sur les clés — ce qui permet de trier, que JavaScript ne déduit pas. */
    compareTo(other: MarkerKey | dsviper.ValueKey): number;
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
    static fromAnyConceptKey(key: AnyConceptKey | dsviper.ValueKey): MarkerKey | undefined;
    toString(): string;
}
