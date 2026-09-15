// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

/** Core — les types que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";

import { Mapping, Ordered, Sequence } from "../_codegen/container.js";
import { Proxy } from "../_codegen/proxy.js";
import { AnyConceptKey, register, setField, wrap } from "../_codegen/registry.js";
import { definitions } from "../index.js";

// ── l'identité de cette unité dans le modèle ──
//
// LE MÊME ARTEFACT QU'EN C++ ET EN PYTHON, POUR LA MÊME RAISON : plusieurs couches en ont
// besoin et ce n'est pas de la sérialisation.

export const OTHER = dsviper.ValueUUId.create("fe5c9495-ee60-2c05-59a7-76a3acb2102c");
export const THING = dsviper.ValueUUId.create("43ac162e-d31b-650b-ff35-6e284bd06ea2");
export const SUB_THING = dsviper.ValueUUId.create("4953d146-1dcb-1d23-03b4-2d7e90cef4b2");
export const KLUB = dsviper.ValueUUId.create("f99852de-1837-1c8c-c831-4fc0ceee8688");
export const GRADE = dsviper.ValueUUId.create("fbfc67e2-b360-2377-80bf-d58461a34eb0");
export const BAG = dsviper.ValueUUId.create("2a160921-2e7a-0f1a-2800-10ef9b577166");
export const COLOUR = dsviper.ValueUUId.create("771d31fe-d3b9-603c-ca38-43a03717815e");
export const DEFAULTS = dsviper.ValueUUId.create("7da8213c-bddd-98ee-c3c1-c9b26e3e6ef5");
export const SCALARS = dsviper.ValueUUId.create("3e6c9792-57f3-e845-33fb-a29fdcb567f9");
export const SINGLE = dsviper.ValueUUId.create("52b43309-f09f-02d0-fe4e-6baf9f7adf49");

let otherConcept: dsviper.TypeConcept | undefined;
let otherType: dsviper.TypeKey | undefined;

/**
 * Une poignée sur une instance de Core::Other, pas la chose elle-même.
 */
export class OtherKey extends Proxy<dsviper.ValueKey> {
    static concept(): dsviper.TypeConcept {
        return (otherConcept ??= definitions().checkConcept(OTHER));
    }

    /**
     * Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin --
     * l'appelant écrit déjà le nom de la classe.
     */
    static type(): dsviper.TypeKey {
        return (otherType ??= new dsviper.TypeKey(OtherKey.concept()));
    }

    constructor(identifier?: dsviper.ValueKey | dsviper.ValueUUId) {
        if (identifier instanceof dsviper.ValueKey) {
            if (!identifier.type().equals(OtherKey.type())) {
                throw new TypeError("cette valeur n'est pas un Core::OtherKey");
            }
            super(identifier);
        } else {
            super(dsviper.ValueKey.create(OtherKey.concept(), identifier));
        }
    }

    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create(): OtherKey {
        return new OtherKey(dsviper.ValueUUId.create());
    }

    static wrap(value: dsviper.Value): OtherKey {
        return new OtherKey(dsviper.ValueKey.cast(value));
    }

    get instanceId(): dsviper.ValueUUId {
        return this.value.instanceId();
    }

    isValid(): boolean {
        return this.instanceId.isValid();
    }

    /** La clé, vue sans son type. */
    toAny(): AnyConceptKey {
        return new AnyConceptKey(this.value.toAnyConceptKey());
    }

    override toString(): string {
        return `Core::OtherKey(${this.value.representation()})`;
    }
}

let thingConcept: dsviper.TypeConcept | undefined;
let thingType: dsviper.TypeKey | undefined;

/**
 * Une poignée sur une instance de Core::Thing, pas la chose elle-même.
 *
 * Ce sur quoi on accroche des choses.
 */
export class ThingKey extends Proxy<dsviper.ValueKey> {
    static concept(): dsviper.TypeConcept {
        return (thingConcept ??= definitions().checkConcept(THING));
    }

    /**
     * Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin --
     * l'appelant écrit déjà le nom de la classe.
     */
    static type(): dsviper.TypeKey {
        return (thingType ??= new dsviper.TypeKey(ThingKey.concept()));
    }

    constructor(identifier?: dsviper.ValueKey | dsviper.ValueUUId) {
        if (identifier instanceof dsviper.ValueKey) {
            if (!identifier.type().equals(ThingKey.type())) {
                throw new TypeError("cette valeur n'est pas un Core::ThingKey");
            }
            super(identifier);
        } else {
            super(dsviper.ValueKey.create(ThingKey.concept(), identifier));
        }
    }

    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create(): ThingKey {
        return new ThingKey(dsviper.ValueUUId.create());
    }

    static wrap(value: dsviper.Value): ThingKey {
        return new ThingKey(dsviper.ValueKey.cast(value));
    }

    get instanceId(): dsviper.ValueUUId {
        return this.value.instanceId();
    }

    isValid(): boolean {
        return this.instanceId.isValid();
    }

    /** La clé, vue sans son type. */
    toAny(): AnyConceptKey {
        return new AnyConceptKey(this.value.toAnyConceptKey());
    }

    override toString(): string {
        return `Core::ThingKey(${this.value.representation()})`;
    }
}

let sub_thingConcept: dsviper.TypeConcept | undefined;
let sub_thingType: dsviper.TypeKey | undefined;

/**
 * Une poignée sur une instance de Core::SubThing, pas la chose elle-même.
 *
 * Un dérivé, dans le même namespace : le cas facile de l'héritage.
 */
export class SubThingKey extends Proxy<dsviper.ValueKey> {
    static concept(): dsviper.TypeConcept {
        return (sub_thingConcept ??= definitions().checkConcept(SUB_THING));
    }

    /**
     * Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin --
     * l'appelant écrit déjà le nom de la classe.
     */
    static type(): dsviper.TypeKey {
        return (sub_thingType ??= new dsviper.TypeKey(SubThingKey.concept()));
    }

    constructor(identifier?: dsviper.ValueKey | dsviper.ValueUUId) {
        if (identifier instanceof dsviper.ValueKey) {
            if (!identifier.type().equals(SubThingKey.type())) {
                throw new TypeError("cette valeur n'est pas un Core::SubThingKey");
            }
            super(identifier);
        } else {
            super(dsviper.ValueKey.create(SubThingKey.concept(), identifier));
        }
    }

    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create(): SubThingKey {
        return new SubThingKey(dsviper.ValueUUId.create());
    }

    static wrap(value: dsviper.Value): SubThingKey {
        return new SubThingKey(dsviper.ValueKey.cast(value));
    }

    get instanceId(): dsviper.ValueUUId {
        return this.value.instanceId();
    }

    isValid(): boolean {
        return this.instanceId.isValid();
    }

    /** La clé, vue sans son type. */
    toAny(): AnyConceptKey {
        return new AnyConceptKey(this.value.toAnyConceptKey());
    }

    override toString(): string {
        return `Core::SubThingKey(${this.value.representation()})`;
    }
}

let klubClub: dsviper.TypeClub | undefined;
let klubType: dsviper.TypeKey | undefined;

/** Une poignée sur une instance d'un membre de Core::Klub. */
export class KlubKey extends Proxy<dsviper.ValueKey> {
    static club(): dsviper.TypeClub {
        return (klubClub ??= definitions().checkClub(KLUB));
    }

    static type(): dsviper.TypeKey {
        return (klubType ??= new dsviper.TypeKey(KlubKey.club()));
    }

    constructor(key: Proxy<dsviper.ValueKey> | dsviper.ValueKey) {
        const value = key instanceof Proxy ? key.value : key;
        if (!KlubKey.club().isMember(value.typeConcept())) {
            throw new TypeError("cette clé ne désigne pas un membre de Core::Klub");
        }
        super(value.toClubKey(KlubKey.club()));
    }

    static wrap(value: dsviper.Value): KlubKey {
        return new KlubKey(dsviper.ValueKey.cast(value));
    }

    get instanceId(): dsviper.ValueUUId {
        return this.value.instanceId();
    }

    /** La clé vue comme celle d'un membre, ou `undefined` si l'instance n'en est pas un. */
    as<K>(member: { concept(): dsviper.TypeConcept; wrap(value: dsviper.Value): K }): K | undefined {
        const concept = member.concept();
        return this.value.isMember(concept) ? member.wrap(this.value.toMemberKey(concept)) : undefined;
    }

    override toString(): string {
        return `Core::KlubKey(${this.value.representation()})`;
    }
}

let gradeType: dsviper.TypeEnumeration | undefined;

/** Core::Grade. Une énumération, que d'autres namespaces vont référencer. */
export type Grade = "low" | "high";

/**
 * UN TYPE ET UNE VALEUR SOUS LE MÊME NOM, ce que TypeScript permet et qui dit exactement ce
 * qu'on veut : `Grade` annote, `Grade.low` désigne, `Grade.wrap` convertit. Le pack en
 * fait une classe qui enveloppe une `ValueEnumeration` ; une union de littéraux se vérifie
 * mieux et ne coûte aucun objet.
 */
export const Grade = {
    low: "low",
    high: "high",

    type(): dsviper.TypeEnumeration {
        return (gradeType ??= definitions().checkEnumeration(GRADE));
    },

    wrap(value: dsviper.Value): Grade {
        return dsviper.ValueEnumeration.cast(value).name() as Grade;
    },
};

let colourType: dsviper.TypeStructure | undefined;

/** Core::Colour. Le même nom que Parts::Colour, un type différent -- la collision de re-export. */
export class Colour extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure {
        return (colourType ??= definitions().checkStructure(COLOUR));
    }

    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(Colour.type())) {
                throw new TypeError("cette valeur n'est pas un Core::Colour");
            }
            super(value);
        } else {
            super(new dsviper.ValueStructure(Colour.type(), value));
        }
    }

    static wrap(value: dsviper.Value): Colour {
        return new Colour(dsviper.ValueStructure.cast(value));
    }

    get r(): number {
        return this.value.at("r") as number;
    }

    set r(value: number) {
        setField(this.value, "r", value);
    }

    get g(): number {
        return this.value.at("g") as number;
    }

    set g(value: number) {
        setField(this.value, "g", value);
    }

    get b(): number {
        return this.value.at("b") as number;
    }

    set b(value: number) {
        setField(this.value, "b", value);
    }
}

let scalarsType: dsviper.TypeStructure | undefined;

/** Core::Scalars. Toutes les formes scalaires du langage, dans le namespace qui n'en référence aucun
autre. Ce qui ne peut pas traverser une frontière est couvert ici, une fois. */
export class Scalars extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure {
        return (scalarsType ??= definitions().checkStructure(SCALARS));
    }

    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(Scalars.type())) {
                throw new TypeError("cette valeur n'est pas un Core::Scalars");
            }
            super(value);
        } else {
            super(new dsviper.ValueStructure(Scalars.type(), value));
        }
    }

    static wrap(value: dsviper.Value): Scalars {
        return new Scalars(dsviper.ValueStructure.cast(value));
    }

    get f_bool(): boolean {
        return this.value.at("f_bool") as boolean;
    }

    set f_bool(value: boolean) {
        setField(this.value, "f_bool", value);
    }

    get f_uint8(): number {
        return this.value.at("f_uint8") as number;
    }

    set f_uint8(value: number) {
        setField(this.value, "f_uint8", value);
    }

    get f_uint16(): number {
        return this.value.at("f_uint16") as number;
    }

    set f_uint16(value: number) {
        setField(this.value, "f_uint16", value);
    }

    get f_uint32(): number {
        return this.value.at("f_uint32") as number;
    }

    set f_uint32(value: number) {
        setField(this.value, "f_uint32", value);
    }

    get f_uint64(): bigint {
        return this.value.at("f_uint64") as bigint;
    }

    set f_uint64(value: bigint) {
        setField(this.value, "f_uint64", value);
    }

    get f_int8(): number {
        return this.value.at("f_int8") as number;
    }

    set f_int8(value: number) {
        setField(this.value, "f_int8", value);
    }

    get f_int16(): number {
        return this.value.at("f_int16") as number;
    }

    set f_int16(value: number) {
        setField(this.value, "f_int16", value);
    }

    get f_int32(): number {
        return this.value.at("f_int32") as number;
    }

    set f_int32(value: number) {
        setField(this.value, "f_int32", value);
    }

    get f_int64(): bigint {
        return this.value.at("f_int64") as bigint;
    }

    set f_int64(value: bigint) {
        setField(this.value, "f_int64", value);
    }

    get f_float(): number {
        return this.value.at("f_float") as number;
    }

    set f_float(value: number) {
        setField(this.value, "f_float", value);
    }

    get f_double(): number {
        return this.value.at("f_double") as number;
    }

    set f_double(value: number) {
        setField(this.value, "f_double", value);
    }

    get f_blob_id(): dsviper.ValueBlobId {
        return this.value.at("f_blob_id") as dsviper.ValueBlobId;
    }

    set f_blob_id(value: dsviper.ValueBlobId) {
        setField(this.value, "f_blob_id", value);
    }

    get f_commit_id(): dsviper.ValueCommitId {
        return this.value.at("f_commit_id") as dsviper.ValueCommitId;
    }

    set f_commit_id(value: dsviper.ValueCommitId) {
        setField(this.value, "f_commit_id", value);
    }

    get f_uuid(): dsviper.ValueUUId {
        return this.value.at("f_uuid") as dsviper.ValueUUId;
    }

    set f_uuid(value: dsviper.ValueUUId) {
        setField(this.value, "f_uuid", value);
    }

    get f_string(): string {
        return this.value.at("f_string") as string;
    }

    set f_string(value: string) {
        setField(this.value, "f_string", value);
    }

    get f_blob(): dsviper.ValueBlob {
        return this.value.at("f_blob") as dsviper.ValueBlob;
    }

    set f_blob(value: dsviper.ValueBlob) {
        setField(this.value, "f_blob", value);
    }

    get f_any(): unknown {
        return this.value.at("f_any") as unknown;
    }

    set f_any(value: unknown) {
        setField(this.value, "f_any", value);
    }

    get f_vec(): Sequence<number> {
        return wrap(this.value.at("f_vec", false));
    }

    set f_vec(value: Sequence<number>) {
        setField(this.value, "f_vec", value);
    }

    get f_mat(): Sequence<Sequence<number>> {
        return wrap(this.value.at("f_mat", false));
    }

    set f_mat(value: Sequence<Sequence<number>>) {
        setField(this.value, "f_mat", value);
    }
}

let singleType: dsviper.TypeStructure | undefined;

/** Core::Single. Une structure à un seul champ : le cas zéro/un que le générateur traite à part. */
export class Single extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure {
        return (singleType ??= definitions().checkStructure(SINGLE));
    }

    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(Single.type())) {
                throw new TypeError("cette valeur n'est pas un Core::Single");
            }
            super(value);
        } else {
            super(new dsviper.ValueStructure(Single.type(), value));
        }
    }

    static wrap(value: dsviper.Value): Single {
        return new Single(dsviper.ValueStructure.cast(value));
    }

    get f_single(): number {
        return this.value.at("f_single") as number;
    }

    set f_single(value: number) {
        setField(this.value, "f_single", value);
    }
}

let bagType: dsviper.TypeStructure | undefined;

/** Core::Bag. Et un document ordinaire dont un champ est un agrégat : les mêmes opérations, à une
adresse au lieu de la racine. */
export class Bag extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure {
        return (bagType ??= definitions().checkStructure(BAG));
    }

    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(Bag.type())) {
                throw new TypeError("cette valeur n'est pas un Core::Bag");
            }
            super(value);
        } else {
            super(new dsviper.ValueStructure(Bag.type(), value));
        }
    }

    static wrap(value: dsviper.Value): Bag {
        return new Bag(dsviper.ValueStructure.cast(value));
    }

    get members(): Sequence<ThingKey> {
        return wrap(this.value.at("members", false));
    }

    set members(value: Sequence<ThingKey>) {
        setField(this.value, "members", value);
    }

    get tints(): Mapping<ThingKey, Colour> {
        return wrap(this.value.at("tints", false));
    }

    set tints(value: Mapping<ThingKey, Colour>) {
        setField(this.value, "tints", value);
    }

    get trail(): Ordered<Colour> {
        return wrap(this.value.at("trail", false));
    }

    set trail(value: Ordered<Colour>) {
        setField(this.value, "trail", value);
    }
}

let defaultsType: dsviper.TypeStructure | undefined;

/** Core::Defaults. Les valeurs par défaut, qui sont un chemin de code à part. */
export class Defaults extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure {
        return (defaultsType ??= definitions().checkStructure(DEFAULTS));
    }

    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(Defaults.type())) {
                throw new TypeError("cette valeur n'est pas un Core::Defaults");
            }
            super(value);
        } else {
            super(new dsviper.ValueStructure(Defaults.type(), value));
        }
    }

    static wrap(value: dsviper.Value): Defaults {
        return new Defaults(dsviper.ValueStructure.cast(value));
    }

    get f_uint8(): number {
        return this.value.at("f_uint8") as number;
    }

    set f_uint8(value: number) {
        setField(this.value, "f_uint8", value);
    }

    get f_float(): number {
        return this.value.at("f_float") as number;
    }

    set f_float(value: number) {
        setField(this.value, "f_float", value);
    }

    get f_string(): string {
        return this.value.at("f_string") as string;
    }

    set f_string(value: string) {
        setField(this.value, "f_string", value);
    }

    get f_uuid(): dsviper.ValueUUId {
        return this.value.at("f_uuid") as dsviper.ValueUUId;
    }

    set f_uuid(value: dsviper.ValueUUId) {
        setField(this.value, "f_uuid", value);
    }

    get f_vec(): Sequence<number> {
        return wrap(this.value.at("f_vec", false));
    }

    set f_vec(value: Sequence<number>) {
        setField(this.value, "f_vec", value);
    }

    get f_grade(): Grade {
        return wrap(this.value.at("f_grade", false));
    }

    set f_grade(value: Grade) {
        setField(this.value, "f_grade", value);
    }

    get f_colour(): Colour {
        return wrap(this.value.at("f_colour", false));
    }

    set f_colour(value: Colour) {
        setField(this.value, "f_colour", value);
    }
}

// Les classes de cette unité, par l'identifiant d'exécution de leur type : c'est ce qui permet
// à `wrap` de rendre un élément de conteneur, ou un document d'attachment, avec son nom.
register([OTHER, OtherKey], [THING, ThingKey], [SUB_THING, SubThingKey], [KLUB, KlubKey], [GRADE, Grade], [BAG, Bag], [COLOUR, Colour], [DEFAULTS, Defaults], [SCALARS, Scalars], [SINGLE, Single]);