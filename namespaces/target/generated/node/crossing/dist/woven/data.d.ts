/** Woven — les types que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";
import { Mapping, Ordered, Sequence } from "../_codegen/container.js";
import { Proxy } from "../_codegen/proxy.js";
import { AnyConceptKey } from "../_codegen/registry.js";
import * as parts from "../parts/data.js";
import * as core from "../core/data.js";
export declare const KNOT: dsviper.ValueUUId;
export declare const DERIVED: dsviper.ValueUUId;
export declare const WEAVE: dsviper.ValueUUId;
export declare const COMPOSITES: dsviper.ValueUUId;
export declare const ENTITIES: dsviper.ValueUUId;
export declare const NESTED: dsviper.ValueUUId;
/**
 * Une poignée sur une instance de Woven::Knot, pas la chose elle-même.
 *
 * Ce sur quoi les attachments de ce namespace sont accrochés.
 */
export declare class KnotKey extends Proxy<dsviper.ValueKey> {
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
    static create(): KnotKey;
    static wrap(value: dsviper.Value): KnotKey;
    get instanceId(): dsviper.ValueUUId;
    isValid(): boolean;
    /** La clé, vue sans son type. */
    toAny(): AnyConceptKey;
    toString(): string;
}
/**
 * Une poignée sur une instance de Woven::Derived, pas la chose elle-même.
 *
 * Un concept dont le parent vit ailleurs.
 */
export declare class DerivedKey extends Proxy<dsviper.ValueKey> {
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
    static create(): DerivedKey;
    static wrap(value: dsviper.Value): DerivedKey;
    get instanceId(): dsviper.ValueUUId;
    isValid(): boolean;
    /** La clé, vue sans son type. */
    toAny(): AnyConceptKey;
    toString(): string;
}
/** Une poignée sur une instance d'un membre de Woven::Weave. */
export declare class WeaveKey extends Proxy<dsviper.ValueKey> {
    static club(): dsviper.TypeClub;
    static type(): dsviper.TypeKey;
    constructor(key: Proxy<dsviper.ValueKey> | dsviper.ValueKey);
    static wrap(value: dsviper.Value): WeaveKey;
    get instanceId(): dsviper.ValueUUId;
    /** La clé vue comme celle d'un membre, ou `undefined` si l'instance n'en est pas un. */
    as<K>(member: {
        concept(): dsviper.TypeConcept;
        wrap(value: dsviper.Value): K;
    }): K | undefined;
    toString(): string;
}
/** Woven::Entities. Les entités des deux fournisseurs, nues, comme champs. */
export declare class Entities extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure;
    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>);
    static wrap(value: dsviper.Value): Entities;
    get f_core_grade(): core.Grade;
    set f_core_grade(value: core.Grade);
    get f_parts_grade(): parts.Grade;
    set f_parts_grade(value: parts.Grade);
    get f_core_colour(): core.Colour;
    set f_core_colour(value: core.Colour);
    get f_parts_colour(): parts.Colour;
    set f_parts_colour(value: parts.Colour);
    get f_single(): core.Single;
    set f_single(value: core.Single);
    get f_thing(): core.ThingKey;
    set f_thing(value: core.ThingKey);
    get f_sub_thing(): core.SubThingKey;
    set f_sub_thing(value: core.SubThingKey);
    get f_other_thing(): parts.ThingKey;
    set f_other_thing(value: parts.ThingKey);
    get f_klub(): core.KlubKey;
    set f_klub(value: core.KlubKey);
    get f_any_concept(): AnyConceptKey;
    set f_any_concept(value: AnyConceptKey);
}
/** Woven::Composites. Chaque conteneur, avec des éléments des deux fournisseurs. */
export declare class Composites extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure;
    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>);
    static wrap(value: dsviper.Value): Composites;
    get f_tuple(): Sequence<core.Colour | parts.Colour>;
    set f_tuple(value: Sequence<core.Colour | parts.Colour>);
    get f_optional(): core.ThingKey | undefined;
    set f_optional(value: core.ThingKey | undefined);
    get f_vector(): Sequence<parts.Colour>;
    set f_vector(value: Sequence<parts.Colour>);
    get f_set(): Sequence<core.ThingKey>;
    set f_set(value: Sequence<core.ThingKey>);
    get f_map_keys(): Mapping<core.ThingKey, parts.ThingKey>;
    set f_map_keys(value: Mapping<core.ThingKey, parts.ThingKey>);
    get f_map_enum(): Mapping<core.Grade, parts.Colour>;
    set f_map_enum(value: Mapping<core.Grade, parts.Colour>);
    get f_xarray(): Ordered<core.Colour>;
    set f_xarray(value: Ordered<core.Colour>);
    get f_variant(): core.Colour | parts.Colour | string;
    set f_variant(value: core.Colour | parts.Colour | string);
}
/** Woven::Nested. Une structure d'ici qui contient une structure d'ici : la profondeur reste locale. */
export declare class Nested extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure;
    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>);
    static wrap(value: dsviper.Value): Nested;
    get f_composites(): Composites;
    set f_composites(value: Composites);
    get f_entities(): Entities;
    set f_entities(value: Entities);
}
