/** Projection — les types que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";
import { Proxy } from "../_codegen/proxy.js";
import { AnyConceptKey } from "../_codegen/registry.js";
import * as model_b from "../model_b/data.js";
import * as model_a from "../model_a/data.js";
export declare const LINK: dsviper.ValueUUId;
export declare const DERIVED_MATERIAL: dsviper.ValueUUId;
export declare const PAIR: dsviper.ValueUUId;
/**
 * Une poignée sur une instance de Projection::Link, pas la chose elle-même.
 *
 * What one link between two driver materials is.
 */
export declare class LinkKey extends Proxy<dsviper.ValueKey> {
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
    static create(): LinkKey;
    static wrap(value: dsviper.Value): LinkKey;
    static decode(blob: dsviper.ValueBlob): LinkKey;
    instanceId(): dsviper.ValueUUId;
    runtimeId(): dsviper.ValueUUId;
    isValid(): boolean;
    /** Un ordre total sur les clés — ce qui permet de trier, que JavaScript ne déduit pas. */
    compareTo(other: LinkKey | dsviper.ValueKey): number;
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
    static fromAnyConceptKey(key: AnyConceptKey | dsviper.ValueKey): LinkKey | undefined;
    toString(): string;
}
/**
 * Une poignée sur une instance de Projection::DerivedMaterial, pas la chose elle-même.
 *
 * A concept whose parent lives in another namespace.
 */
export declare class DerivedMaterialKey extends Proxy<dsviper.ValueKey> {
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
    static create(): DerivedMaterialKey;
    static wrap(value: dsviper.Value): DerivedMaterialKey;
    static decode(blob: dsviper.ValueBlob): DerivedMaterialKey;
    instanceId(): dsviper.ValueUUId;
    runtimeId(): dsviper.ValueUUId;
    isValid(): boolean;
    /** Un ordre total sur les clés — ce qui permet de trier, que JavaScript ne déduit pas. */
    compareTo(other: DerivedMaterialKey | dsviper.ValueKey): number;
    /** L'instance et son type, dits comme le modèle les nomme. */
    description(): string;
    isKnown(): boolean;
    /** Élargir vers le parent. Ne perd rien : l'identifiant d'exécution reste celui du concept
     *  réel, et c'est ce qui permet d'en revenir ensuite. */
    toParentKey(): model_a.MaterialKey;
    /** La clé, vue sans son type. */
    toAnyConceptKey(): AnyConceptKey;
    /** La clé non typée, retypée — ou `undefined` si elle ne désigne pas ce concept.
     *
     * LE CHEMIN DE RETOUR, ET IL PEUT ÉCHOUER. Élargir ne perd rien ; rétrécir pose une
     * question dont la réponse est dans l'identifiant que la valeur porte.
     */
    static fromAnyConceptKey(key: AnyConceptKey | dsviper.ValueKey): DerivedMaterialKey | undefined;
    toString(): string;
}
/** Projection::Pair. Two keys from two namespaces in one structure -- the key<NS::C> edge. */
export declare class Pair extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure;
    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>);
    static wrap(value: dsviper.Value): Pair;
    static decode(blob: dsviper.ValueBlob): Pair;
    get a(): model_a.MaterialKey;
    set a(value: model_a.MaterialKey);
    get b(): model_b.MaterialKey;
    set b(value: model_b.MaterialKey);
}
