/** Core — les types que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";
import { Mapping, Ordered, Sequence } from "../_codegen/container.js";
import { Proxy } from "../_codegen/proxy.js";
import { AnyConceptKey } from "../_codegen/registry.js";
export declare const OTHER: dsviper.ValueUUId;
export declare const THING: dsviper.ValueUUId;
export declare const SUB_THING: dsviper.ValueUUId;
export declare const KLUB: dsviper.ValueUUId;
export declare const GRADE: dsviper.ValueUUId;
export declare const BAG: dsviper.ValueUUId;
export declare const COLOUR: dsviper.ValueUUId;
export declare const DEFAULTS: dsviper.ValueUUId;
export declare const SCALARS: dsviper.ValueUUId;
export declare const SINGLE: dsviper.ValueUUId;
/**
 * Une poignée sur une instance de Core::Other, pas la chose elle-même.
 */
export declare class OtherKey extends Proxy<dsviper.ValueKey> {
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
    static create(): OtherKey;
    static wrap(value: dsviper.Value): OtherKey;
    get instanceId(): dsviper.ValueUUId;
    isValid(): boolean;
    /** La clé, vue sans son type. */
    toAny(): AnyConceptKey;
    toString(): string;
}
/**
 * Une poignée sur une instance de Core::Thing, pas la chose elle-même.
 *
 * Ce sur quoi on accroche des choses.
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
    get instanceId(): dsviper.ValueUUId;
    isValid(): boolean;
    /** La clé, vue sans son type. */
    toAny(): AnyConceptKey;
    toString(): string;
}
/**
 * Une poignée sur une instance de Core::SubThing, pas la chose elle-même.
 *
 * Un dérivé, dans le même namespace : le cas facile de l'héritage.
 */
export declare class SubThingKey extends Proxy<dsviper.ValueKey> {
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
    static create(): SubThingKey;
    static wrap(value: dsviper.Value): SubThingKey;
    get instanceId(): dsviper.ValueUUId;
    isValid(): boolean;
    /** La clé, vue sans son type. */
    toAny(): AnyConceptKey;
    toString(): string;
}
/** Une poignée sur une instance d'un membre de Core::Klub. */
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
/** Core::Grade. Une énumération, que d'autres namespaces vont référencer. */
export type Grade = "low" | "high";
/**
 * UN TYPE ET UNE VALEUR SOUS LE MÊME NOM, ce que TypeScript permet et qui dit exactement ce
 * qu'on veut : `Grade` annote, `Grade.low` désigne, `Grade.wrap` convertit. Le pack en
 * fait une classe qui enveloppe une `ValueEnumeration` ; une union de littéraux se vérifie
 * mieux et ne coûte aucun objet.
 */
export declare const Grade: {
    LOW: string;
    HIGH: string;
    type(): dsviper.TypeEnumeration;
    wrap(value: dsviper.Value): Grade;
};
/** Core::Colour. Le même nom que Parts::Colour, un type différent -- la collision de re-export. */
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
/** Core::Scalars. Toutes les formes scalaires du langage, dans le namespace qui n'en référence aucun
autre. Ce qui ne peut pas traverser une frontière est couvert ici, une fois. */
export declare class Scalars extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure;
    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>);
    static wrap(value: dsviper.Value): Scalars;
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
    get f_any(): unknown;
    set f_any(value: unknown);
    get f_vec(): Sequence<number>;
    set f_vec(value: Sequence<number>);
    get f_mat(): Sequence<Sequence<number>>;
    set f_mat(value: Sequence<Sequence<number>>);
}
/** Core::Single. Une structure à un seul champ : le cas zéro/un que le générateur traite à part. */
export declare class Single extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure;
    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>);
    static wrap(value: dsviper.Value): Single;
    get f_single(): number;
    set f_single(value: number);
}
/** Core::Bag. Et un document ordinaire dont un champ est un agrégat : les mêmes opérations, à une
adresse au lieu de la racine. */
export declare class Bag extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure;
    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>);
    static wrap(value: dsviper.Value): Bag;
    get members(): Sequence<ThingKey>;
    set members(value: Sequence<ThingKey>);
    get tints(): Mapping<ThingKey, Colour>;
    set tints(value: Mapping<ThingKey, Colour>);
    get trail(): Ordered<Colour>;
    set trail(value: Ordered<Colour>);
}
/** Core::Defaults. Les valeurs par défaut, qui sont un chemin de code à part. */
export declare class Defaults extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure;
    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>);
    static wrap(value: dsviper.Value): Defaults;
    get f_uint8(): number;
    set f_uint8(value: number);
    get f_float(): number;
    set f_float(value: number);
    get f_string(): string;
    set f_string(value: string);
    get f_uuid(): dsviper.ValueUUId;
    set f_uuid(value: dsviper.ValueUUId);
    get f_vec(): Sequence<number>;
    set f_vec(value: Sequence<number>);
    get f_grade(): Grade;
    set f_grade(value: Grade);
    get f_colour(): Colour;
    set f_colour(value: Colour);
}
