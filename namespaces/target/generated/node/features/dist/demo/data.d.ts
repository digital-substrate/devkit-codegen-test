/** Demo — les types que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";
import { Mapping, Ordered, Sequence } from "../_codegen/container.js";
import { Proxy } from "../_codegen/proxy.js";
import { AnyConceptKey } from "../_codegen/registry.js";
export declare const CONCEPT_A: dsviper.ValueUUId;
export declare const CONCEPT_B: dsviper.ValueUUId;
export declare const CONCEPT_COVERAGE: dsviper.ValueUUId;
export declare const CONCEPT_D: dsviper.ValueUUId;
export declare const CONCEPT_C: dsviper.ValueUUId;
export declare const EMPTY_KLUB: dsviper.ValueUUId;
export declare const KLUB: dsviper.ValueUUId;
export declare const ENUMERATION_E: dsviper.ValueUUId;
export declare const STRUCTURE_S: dsviper.ValueUUId;
export declare const STRUCTURE_T: dsviper.ValueUUId;
export declare const STRUCTURE_U: dsviper.ValueUUId;
export declare const STRUCTURE_V: dsviper.ValueUUId;
export declare const STRUCTURE_W: dsviper.ValueUUId;
/**
 * Une poignée sur une instance de Demo::ConceptA, pas la chose elle-même.
 *
 * This is the documentation for the concept A
 */
export declare class ConceptAKey extends Proxy<dsviper.ValueKey> {
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
    static create(): ConceptAKey;
    static wrap(value: dsviper.Value): ConceptAKey;
    get instanceId(): dsviper.ValueUUId;
    isValid(): boolean;
    /** La clé, vue sans son type. */
    toAny(): AnyConceptKey;
    toString(): string;
}
/**
 * Une poignée sur une instance de Demo::ConceptB, pas la chose elle-même.
 */
export declare class ConceptBKey extends Proxy<dsviper.ValueKey> {
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
    static create(): ConceptBKey;
    static wrap(value: dsviper.Value): ConceptBKey;
    get instanceId(): dsviper.ValueUUId;
    isValid(): boolean;
    /** La clé, vue sans son type. */
    toAny(): AnyConceptKey;
    toString(): string;
}
/**
 * Une poignée sur une instance de Demo::ConceptCoverage, pas la chose elle-même.
 */
export declare class ConceptCoverageKey extends Proxy<dsviper.ValueKey> {
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
    static create(): ConceptCoverageKey;
    static wrap(value: dsviper.Value): ConceptCoverageKey;
    get instanceId(): dsviper.ValueUUId;
    isValid(): boolean;
    /** La clé, vue sans son type. */
    toAny(): AnyConceptKey;
    toString(): string;
}
/**
 * Une poignée sur une instance de Demo::ConceptD, pas la chose elle-même.
 */
export declare class ConceptDKey extends Proxy<dsviper.ValueKey> {
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
    static create(): ConceptDKey;
    static wrap(value: dsviper.Value): ConceptDKey;
    get instanceId(): dsviper.ValueUUId;
    isValid(): boolean;
    /** La clé, vue sans son type. */
    toAny(): AnyConceptKey;
    toString(): string;
}
/**
 * Une poignée sur une instance de Demo::ConceptC, pas la chose elle-même.
 */
export declare class ConceptCKey extends Proxy<dsviper.ValueKey> {
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
    static create(): ConceptCKey;
    static wrap(value: dsviper.Value): ConceptCKey;
    get instanceId(): dsviper.ValueUUId;
    isValid(): boolean;
    /** La clé, vue sans son type. */
    toAny(): AnyConceptKey;
    toString(): string;
}
/** Une poignée sur une instance d'un membre de Demo::EmptyKlub. */
export declare class EmptyKlubKey extends Proxy<dsviper.ValueKey> {
    static club(): dsviper.TypeClub;
    static type(): dsviper.TypeKey;
    constructor(key: Proxy<dsviper.ValueKey> | dsviper.ValueKey);
    static wrap(value: dsviper.Value): EmptyKlubKey;
    get instanceId(): dsviper.ValueUUId;
    /** La clé vue comme celle d'un membre, ou `undefined` si l'instance n'en est pas un. */
    as<K>(member: {
        concept(): dsviper.TypeConcept;
        wrap(value: dsviper.Value): K;
    }): K | undefined;
    toString(): string;
}
/** Une poignée sur une instance d'un membre de Demo::Klub. */
export declare class KlubKey extends Proxy<dsviper.ValueKey> {
    static club(): dsviper.TypeClub;
    static type(): dsviper.TypeKey;
    constructor(key: Proxy<dsviper.ValueKey> | dsviper.ValueKey);
    static wrap(value: dsviper.Value): KlubKey;
    get instanceId(): dsviper.ValueUUId;
    /** La clé vue comme celle d'un membre, ou `undefined` si l'instance n'en est pas un. */
    as<K>(member: {
        concept(): dsviper.TypeConcept;
        wrap(value: dsviper.Value): K;
    }): K | undefined;
    toString(): string;
}
/** Demo::EnumerationE. This is the documentation for enumeration E */
export type EnumerationE = "a" | "b" | "c";
/**
 * UN TYPE ET UNE VALEUR SOUS LE MÊME NOM, ce que TypeScript permet et qui dit exactement ce
 * qu'on veut : `EnumerationE` annote, `EnumerationE.a` désigne, `EnumerationE.wrap` convertit. Le pack en
 * fait une classe qui enveloppe une `ValueEnumeration` ; une union de littéraux se vérifie
 * mieux et ne coûte aucun objet.
 */
export declare const EnumerationE: {
    A: string;
    B: string;
    C: string;
    type(): dsviper.TypeEnumeration;
    wrap(value: dsviper.Value): EnumerationE;
};
/** Demo::StructureS. This is the documentation for the struct S */
export declare class StructureS extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure;
    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>);
    static wrap(value: dsviper.Value): StructureS;
    get f_float(): number;
    set f_float(value: number);
    get f_string(): string;
    set f_string(value: string);
}
/** Demo::StructureW. */
export declare class StructureW extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure;
    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>);
    static wrap(value: dsviper.Value): StructureW;
    get f_single(): number;
    set f_single(value: number);
}
/** Demo::StructureT. */
export declare class StructureT extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure;
    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>);
    static wrap(value: dsviper.Value): StructureT;
    get field_string(): string;
    set field_string(value: string);
    get field_structure_s(): StructureS;
    set field_structure_s(value: StructureS);
}
/** Demo::StructureV. */
export declare class StructureV extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure;
    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>);
    static wrap(value: dsviper.Value): StructureV;
    get f_bool(): boolean;
    set f_bool(value: boolean);
    get f_uint8(): number;
    set f_uint8(value: number);
    get f_uint16(): number;
    set f_uint16(value: number);
    get f_uint32(): number;
    set f_uint32(value: number);
    get f_uint64(): bigint;
    set f_uint64(value: bigint);
    get f_int8(): number;
    set f_int8(value: number);
    get f_int16(): number;
    set f_int16(value: number);
    get f_int32(): number;
    set f_int32(value: number);
    get f_int64(): bigint;
    set f_int64(value: bigint);
    get f_float(): number;
    set f_float(value: number);
    get f_double(): number;
    set f_double(value: number);
    get f_uuid(): dsviper.ValueUUId;
    set f_uuid(value: dsviper.ValueUUId);
    get f_string(): string;
    set f_string(value: string);
    get f_vec(): Sequence<number>;
    set f_vec(value: Sequence<number>);
    get f_mat(): Sequence<Sequence<number>>;
    set f_mat(value: Sequence<Sequence<number>>);
    get f_tuple(): Sequence<number | string>;
    set f_tuple(value: Sequence<number | string>);
    get f_optional(): number | undefined;
    set f_optional(value: number | undefined);
    get f_vector(): Sequence<number>;
    set f_vector(value: Sequence<number>);
    get f_set(): Sequence<number>;
    set f_set(value: Sequence<number>);
    get f_map(): Mapping<number, string>;
    set f_map(value: Mapping<number, string>);
    get f_E(): EnumerationE;
    set f_E(value: EnumerationE);
    get f_S(): StructureS;
    set f_S(value: StructureS);
    get f_T(): StructureT;
    set f_T(value: StructureT);
}
/** Demo::StructureU. */
export declare class StructureU extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure;
    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>);
    static wrap(value: dsviper.Value): StructureU;
    get f_bool(): boolean;
    set f_bool(value: boolean);
    get f_uint8(): number;
    set f_uint8(value: number);
    get f_uint16(): number;
    set f_uint16(value: number);
    get f_uint32(): number;
    set f_uint32(value: number);
    get f_uint64(): bigint;
    set f_uint64(value: bigint);
    get f_int8(): number;
    set f_int8(value: number);
    get f_int16(): number;
    set f_int16(value: number);
    get f_int32(): number;
    set f_int32(value: number);
    get f_int64(): bigint;
    set f_int64(value: bigint);
    get f_float(): number;
    set f_float(value: number);
    get f_double(): number;
    set f_double(value: number);
    get f_blob_id(): dsviper.ValueBlobId;
    set f_blob_id(value: dsviper.ValueBlobId);
    get f_commit_id(): dsviper.ValueCommitId;
    set f_commit_id(value: dsviper.ValueCommitId);
    get f_uuid(): dsviper.ValueUUId;
    set f_uuid(value: dsviper.ValueUUId);
    get f_string(): string;
    set f_string(value: string);
    get f_blob(): dsviper.ValueBlob;
    set f_blob(value: dsviper.ValueBlob);
    get f_vec(): Sequence<number>;
    set f_vec(value: Sequence<number>);
    get f_mat(): Sequence<Sequence<number>>;
    set f_mat(value: Sequence<Sequence<number>>);
    get f_tuple(): Sequence<number | string>;
    set f_tuple(value: Sequence<number | string>);
    get f_optional(): number | undefined;
    set f_optional(value: number | undefined);
    get f_vector(): Sequence<number>;
    set f_vector(value: Sequence<number>);
    get f_set(): Sequence<number>;
    set f_set(value: Sequence<number>);
    get f_set_s(): Sequence<StructureS>;
    set f_set_s(value: Sequence<StructureS>);
    get f_map_s1(): Mapping<StructureS, string>;
    set f_map_s1(value: Mapping<StructureS, string>);
    get f_map_s2(): Mapping<string, StructureS>;
    set f_map_s2(value: Mapping<string, StructureS>);
    get f_xarray(): Ordered<number>;
    set f_xarray(value: Ordered<number>);
    get f_xarray_s(): Ordered<StructureS>;
    set f_xarray_s(value: Ordered<StructureS>);
    get f_map_vs(): Mapping<Sequence<StructureS>, string>;
    set f_map_vs(value: Mapping<Sequence<StructureS>, string>);
    get f_variant(): string | number | StructureS;
    set f_variant(value: string | number | StructureS);
    get f_any(): unknown;
    set f_any(value: unknown);
    get f_E(): EnumerationE;
    set f_E(value: EnumerationE);
    get f_S(): StructureS;
    set f_S(value: StructureS);
    get f_T(): StructureT;
    set f_T(value: StructureT);
    get f_A(): ConceptAKey;
    set f_A(value: ConceptAKey);
    get f_B(): ConceptBKey;
    set f_B(value: ConceptBKey);
    get f_C(): ConceptCKey;
    set f_C(value: ConceptCKey);
    get f_D(): ConceptDKey;
    set f_D(value: ConceptDKey);
    get f_Klub(): KlubKey;
    set f_Klub(value: KlubKey);
    get f_any_concept(): AnyConceptKey;
    set f_any_concept(value: AnyConceptKey);
}
