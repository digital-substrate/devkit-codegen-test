// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

/** Woven — les types que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";

import { Mapping, Ordered, Sequence } from "../_codegen/container.js";
import { Proxy } from "../_codegen/proxy.js";
import { AnyConceptKey, isKnown, register, setField, wrap } from "../_codegen/registry.js";
import { definitions } from "../index.js";
import * as parts from "../parts/data.js";
import * as core from "../core/data.js";

// ── l'identité de cette unité dans le modèle ──
//
// LE MÊME ARTEFACT QU'EN C++ ET EN PYTHON, POUR LA MÊME RAISON : plusieurs couches en ont
// besoin et ce n'est pas de la sérialisation.

export const KNOT = dsviper.ValueUUId.create("f60cecc5-a96c-bab5-77f1-1130bc338fda");
export const DERIVED = dsviper.ValueUUId.create("d0d3c1b6-50b8-9684-bec1-3b9b3583e571");
export const WEAVE = dsviper.ValueUUId.create("356db13d-6594-8f58-4602-b13293f04281");
export const COMPOSITES = dsviper.ValueUUId.create("77ab62f8-cfe3-5a99-7af4-c2f2befc866a");
export const ENTITIES = dsviper.ValueUUId.create("e8bdbb4b-956b-a468-b60d-0dc796c6a949");
export const NESTED = dsviper.ValueUUId.create("3cfb3a88-6f75-c5d2-f501-5bb814a9c6f4");

let knotConcept: dsviper.TypeConcept | undefined;
let knotType: dsviper.TypeKey | undefined;

/**
 * Une poignée sur une instance de Woven::Knot, pas la chose elle-même.
 *
 * Ce sur quoi les attachments de ce namespace sont accrochés.
 */
export class KnotKey extends Proxy<dsviper.ValueKey> {
    static concept(): dsviper.TypeConcept {
        return (knotConcept ??= definitions().checkConcept(KNOT));
    }

    /**
     * Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin --
     * l'appelant écrit déjà le nom de la classe.
     */
    static type(): dsviper.TypeKey {
        return (knotType ??= new dsviper.TypeKey(KnotKey.concept()));
    }

    constructor(identifier?: dsviper.ValueKey | dsviper.ValueUUId) {
        if (identifier instanceof dsviper.ValueKey) {
            if (!identifier.type().equals(KnotKey.type())) {
                throw new TypeError("cette valeur n'est pas un Woven::KnotKey");
            }
            super(identifier);
        } else {
            super(dsviper.ValueKey.create(KnotKey.concept(), identifier));
        }
    }

    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create(): KnotKey {
        return new KnotKey(dsviper.ValueUUId.create());
    }

    static wrap(value: dsviper.Value): KnotKey {
        return new KnotKey(dsviper.ValueKey.cast(value));
    }

    static decode(blob: dsviper.ValueBlob): KnotKey {
        return new KnotKey(dsviper.ValueKey.cast(
            dsviper.Value.decode(blob, KnotKey.type(), definitions())));
    }

    instanceId(): dsviper.ValueUUId {
        return this.value.instanceId();
    }

    runtimeId(): dsviper.ValueUUId {
        return this.value.typeConcept().runtimeId();
    }

    isValid(): boolean {
        return this.value.instanceId().isValid();
    }

    /** L'instance et son type, dits comme le modèle les nomme. */
    description(): string {
        return `${this.value.instanceId().encoded()}:Woven::KnotKey`;
    }

    isKnown(): boolean {
        return isKnown(this.value);
    }

    /** La clé, vue sans son type. */
    toAnyConceptKey(): AnyConceptKey {
        return new AnyConceptKey(this.value.toAnyConceptKey());
    }

    /** La clé non typée, retypée — ou `undefined` si elle ne désigne pas ce concept.
     *
     * LE CHEMIN DE RETOUR, ET IL PEUT ÉCHOUER. Élargir ne perd rien ; rétrécir pose une
     * question dont la réponse est dans l'identifiant que la valeur porte.
     */
    static fromAnyConceptKey(key: AnyConceptKey | dsviper.ValueKey): KnotKey | undefined {
        const value = key instanceof AnyConceptKey ? key.value : key;
        return value.typeConcept().runtimeId().equals(KNOT)
            ? new KnotKey(value) : undefined;
    }

    override toString(): string {
        return this.description();
    }
}

let derivedConcept: dsviper.TypeConcept | undefined;
let derivedType: dsviper.TypeKey | undefined;

/**
 * Une poignée sur une instance de Woven::Derived, pas la chose elle-même.
 *
 * Un concept dont le parent vit ailleurs.
 */
export class DerivedKey extends Proxy<dsviper.ValueKey> {
    static concept(): dsviper.TypeConcept {
        return (derivedConcept ??= definitions().checkConcept(DERIVED));
    }

    /**
     * Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin --
     * l'appelant écrit déjà le nom de la classe.
     */
    static type(): dsviper.TypeKey {
        return (derivedType ??= new dsviper.TypeKey(DerivedKey.concept()));
    }

    constructor(identifier?: dsviper.ValueKey | dsviper.ValueUUId) {
        if (identifier instanceof dsviper.ValueKey) {
            if (!identifier.type().equals(DerivedKey.type())) {
                throw new TypeError("cette valeur n'est pas un Woven::DerivedKey");
            }
            super(identifier);
        } else {
            super(dsviper.ValueKey.create(DerivedKey.concept(), identifier));
        }
    }

    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create(): DerivedKey {
        return new DerivedKey(dsviper.ValueUUId.create());
    }

    static wrap(value: dsviper.Value): DerivedKey {
        return new DerivedKey(dsviper.ValueKey.cast(value));
    }

    static decode(blob: dsviper.ValueBlob): DerivedKey {
        return new DerivedKey(dsviper.ValueKey.cast(
            dsviper.Value.decode(blob, DerivedKey.type(), definitions())));
    }

    instanceId(): dsviper.ValueUUId {
        return this.value.instanceId();
    }

    runtimeId(): dsviper.ValueUUId {
        return this.value.typeConcept().runtimeId();
    }

    isValid(): boolean {
        return this.value.instanceId().isValid();
    }

    /** L'instance et son type, dits comme le modèle les nomme. */
    description(): string {
        return `${this.value.instanceId().encoded()}:Woven::DerivedKey`;
    }

    isKnown(): boolean {
        return isKnown(this.value);
    }

    /** Élargir vers le parent. Ne perd rien : l'identifiant d'exécution reste celui du concept
     *  réel, et c'est ce qui permet d'en revenir ensuite. */
    toParentKey(): core.ThingKey {
        return new core.ThingKey(this.value);
    }

    /** La clé, vue sans son type. */
    toAnyConceptKey(): AnyConceptKey {
        return new AnyConceptKey(this.value.toAnyConceptKey());
    }

    /** La clé non typée, retypée — ou `undefined` si elle ne désigne pas ce concept.
     *
     * LE CHEMIN DE RETOUR, ET IL PEUT ÉCHOUER. Élargir ne perd rien ; rétrécir pose une
     * question dont la réponse est dans l'identifiant que la valeur porte.
     */
    static fromAnyConceptKey(key: AnyConceptKey | dsviper.ValueKey): DerivedKey | undefined {
        const value = key instanceof AnyConceptKey ? key.value : key;
        return value.typeConcept().runtimeId().equals(DERIVED)
            ? new DerivedKey(value) : undefined;
    }

    override toString(): string {
        return this.description();
    }
}

let weaveClub: dsviper.TypeClub | undefined;
let weaveType: dsviper.TypeKey | undefined;

/** Une poignée sur une instance d'un membre de Woven::Weave. */
export class WeaveKey extends Proxy<dsviper.ValueKey> {
    static club(): dsviper.TypeClub {
        return (weaveClub ??= definitions().checkClub(WEAVE));
    }

    static type(): dsviper.TypeKey {
        return (weaveType ??= new dsviper.TypeKey(WeaveKey.club()));
    }

    constructor(key: Proxy<dsviper.ValueKey> | dsviper.ValueKey) {
        const value = key instanceof Proxy ? key.value : key;
        if (!WeaveKey.club().isMember(value.typeConcept())) {
            throw new TypeError("cette clé ne désigne pas un membre de Woven::Weave");
        }
        super(value.toClubKey(WeaveKey.club()));
    }

    static wrap(value: dsviper.Value): WeaveKey {
        return new WeaveKey(dsviper.ValueKey.cast(value));
    }

    static decode(blob: dsviper.ValueBlob): WeaveKey {
        return new WeaveKey(dsviper.ValueKey.cast(
            dsviper.Value.decode(blob, WeaveKey.type(), definitions())));
    }

    instanceId(): dsviper.ValueUUId {
        return this.value.instanceId();
    }

    runtimeId(): dsviper.ValueUUId {
        return this.value.typeConcept().runtimeId();
    }

    isValid(): boolean {
        return this.value.instanceId().isValid();
    }

    description(): string {
        return `${this.value.instanceId().encoded()}:Woven::WeaveKey`;
    }

    isKnown(): boolean {
        return isKnown(this.value);
    }

    /** La clé vue comme celle d'un membre, ou `undefined` si l'instance n'en est pas un. */
    /** La clé d'un membre, vue comme celle du club. */
    static fromCoreThingKey(key: Proxy<dsviper.ValueKey> | dsviper.ValueKey): WeaveKey {
        return new WeaveKey(key);
    }

    /** La clé d'un membre, vue comme celle du club. */
    static fromPartsThingKey(key: Proxy<dsviper.ValueKey> | dsviper.ValueKey): WeaveKey {
        return new WeaveKey(key);
    }

    /** La clé vue comme celle de ce membre, ou `undefined` si l'instance n'en est pas un. */
    toCoreThingKey(): core.ThingKey | undefined {
        return this.as(core.ThingKey);
    }

    /** La clé vue comme celle de ce membre, ou `undefined` si l'instance n'en est pas un. */
    toPartsThingKey(): parts.ThingKey | undefined {
        return this.as(parts.ThingKey);
    }

    as<K>(member: { concept(): dsviper.TypeConcept; wrap(value: dsviper.Value): K }): K | undefined {
        const concept = member.concept();
        return this.value.isMember(concept) ? member.wrap(this.value.toMemberKey(concept)) : undefined;
    }

    override toString(): string {
        return this.description();
    }
}

let entitiesType: dsviper.TypeStructure | undefined;

/** Woven::Entities. Les entités des deux fournisseurs, nues, comme champs. */
export class Entities extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure {
        return (entitiesType ??= definitions().checkStructure(ENTITIES));
    }

    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(Entities.type())) {
                throw new TypeError("cette valeur n'est pas un Woven::Entities");
            }
            super(value);
        } else {
            super(new dsviper.ValueStructure(Entities.type(), value));
        }
    }

    static wrap(value: dsviper.Value): Entities {
        return new Entities(dsviper.ValueStructure.cast(value));
    }

    static decode(blob: dsviper.ValueBlob): Entities {
        return new Entities(dsviper.ValueStructure.cast(
            dsviper.Value.decode(blob, Entities.type(), definitions())));
    }

    get f_core_grade(): core.Grade {
        return wrap(this.value.at("f_core_grade", false));
    }

    set f_core_grade(value: core.Grade) {
        setField(this.value, "f_core_grade", value);
    }

    get f_parts_grade(): parts.Grade {
        return wrap(this.value.at("f_parts_grade", false));
    }

    set f_parts_grade(value: parts.Grade) {
        setField(this.value, "f_parts_grade", value);
    }

    get f_core_colour(): core.Colour {
        return wrap(this.value.at("f_core_colour", false));
    }

    set f_core_colour(value: core.Colour) {
        setField(this.value, "f_core_colour", value);
    }

    get f_parts_colour(): parts.Colour {
        return wrap(this.value.at("f_parts_colour", false));
    }

    set f_parts_colour(value: parts.Colour) {
        setField(this.value, "f_parts_colour", value);
    }

    get f_single(): core.Single {
        return wrap(this.value.at("f_single", false));
    }

    set f_single(value: core.Single) {
        setField(this.value, "f_single", value);
    }

    get f_thing(): core.ThingKey {
        return wrap(this.value.at("f_thing", false));
    }

    set f_thing(value: core.ThingKey) {
        setField(this.value, "f_thing", value);
    }

    get f_sub_thing(): core.SubThingKey {
        return wrap(this.value.at("f_sub_thing", false));
    }

    set f_sub_thing(value: core.SubThingKey) {
        setField(this.value, "f_sub_thing", value);
    }

    get f_other_thing(): parts.ThingKey {
        return wrap(this.value.at("f_other_thing", false));
    }

    set f_other_thing(value: parts.ThingKey) {
        setField(this.value, "f_other_thing", value);
    }

    get f_klub(): core.KlubKey {
        return wrap(this.value.at("f_klub", false));
    }

    set f_klub(value: core.KlubKey) {
        setField(this.value, "f_klub", value);
    }

    get f_any_concept(): AnyConceptKey {
        return wrap(this.value.at("f_any_concept", false));
    }

    set f_any_concept(value: AnyConceptKey) {
        setField(this.value, "f_any_concept", value);
    }
}

let compositesType: dsviper.TypeStructure | undefined;

/** Woven::Composites. Chaque conteneur, avec des éléments des deux fournisseurs. */
export class Composites extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure {
        return (compositesType ??= definitions().checkStructure(COMPOSITES));
    }

    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(Composites.type())) {
                throw new TypeError("cette valeur n'est pas un Woven::Composites");
            }
            super(value);
        } else {
            super(new dsviper.ValueStructure(Composites.type(), value));
        }
    }

    static wrap(value: dsviper.Value): Composites {
        return new Composites(dsviper.ValueStructure.cast(value));
    }

    static decode(blob: dsviper.ValueBlob): Composites {
        return new Composites(dsviper.ValueStructure.cast(
            dsviper.Value.decode(blob, Composites.type(), definitions())));
    }

    get f_tuple(): Sequence<core.Colour | parts.Colour> {
        return wrap(this.value.at("f_tuple", false));
    }

    set f_tuple(value: Sequence<core.Colour | parts.Colour>) {
        setField(this.value, "f_tuple", value);
    }

    get f_optional(): core.ThingKey | undefined {
        return wrap(this.value.at("f_optional", false));
    }

    set f_optional(value: core.ThingKey | undefined) {
        setField(this.value, "f_optional", value);
    }

    get f_vector(): Sequence<parts.Colour> {
        return wrap(this.value.at("f_vector", false));
    }

    set f_vector(value: Sequence<parts.Colour>) {
        setField(this.value, "f_vector", value);
    }

    get f_set(): Sequence<core.ThingKey> {
        return wrap(this.value.at("f_set", false));
    }

    set f_set(value: Sequence<core.ThingKey>) {
        setField(this.value, "f_set", value);
    }

    get f_map_keys(): Mapping<core.ThingKey, parts.ThingKey> {
        return wrap(this.value.at("f_map_keys", false));
    }

    set f_map_keys(value: Mapping<core.ThingKey, parts.ThingKey>) {
        setField(this.value, "f_map_keys", value);
    }

    get f_map_enum(): Mapping<core.Grade, parts.Colour> {
        return wrap(this.value.at("f_map_enum", false));
    }

    set f_map_enum(value: Mapping<core.Grade, parts.Colour>) {
        setField(this.value, "f_map_enum", value);
    }

    get f_xarray(): Ordered<core.Colour> {
        return wrap(this.value.at("f_xarray", false));
    }

    set f_xarray(value: Ordered<core.Colour>) {
        setField(this.value, "f_xarray", value);
    }

    get f_variant(): core.Colour | parts.Colour | string {
        return wrap(this.value.at("f_variant", false));
    }

    set f_variant(value: core.Colour | parts.Colour | string) {
        setField(this.value, "f_variant", value);
    }
}

let nestedType: dsviper.TypeStructure | undefined;

/** Woven::Nested. Une structure d'ici qui contient une structure d'ici : la profondeur reste locale. */
export class Nested extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure {
        return (nestedType ??= definitions().checkStructure(NESTED));
    }

    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(Nested.type())) {
                throw new TypeError("cette valeur n'est pas un Woven::Nested");
            }
            super(value);
        } else {
            super(new dsviper.ValueStructure(Nested.type(), value));
        }
    }

    static wrap(value: dsviper.Value): Nested {
        return new Nested(dsviper.ValueStructure.cast(value));
    }

    static decode(blob: dsviper.ValueBlob): Nested {
        return new Nested(dsviper.ValueStructure.cast(
            dsviper.Value.decode(blob, Nested.type(), definitions())));
    }

    get f_composites(): Composites {
        return wrap(this.value.at("f_composites", false));
    }

    set f_composites(value: Composites) {
        setField(this.value, "f_composites", value);
    }

    get f_entities(): Entities {
        return wrap(this.value.at("f_entities", false));
    }

    set f_entities(value: Entities) {
        setField(this.value, "f_entities", value);
    }
}

// Les classes de cette unité, par l'identifiant d'exécution de leur type : c'est ce qui permet
// à `wrap` de rendre un élément de conteneur, ou un document d'attachment, avec son nom.
register([KNOT, KnotKey], [DERIVED, DerivedKey], [WEAVE, WeaveKey], [COMPOSITES, Composites], [ENTITIES, Entities], [NESTED, Nested]);