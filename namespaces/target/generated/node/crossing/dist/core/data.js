// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar
/** Core — les types que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";
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
let otherConcept;
let otherType;
/**
 * Une poignée sur une instance de Core::Other, pas la chose elle-même.
 */
export class OtherKey extends Proxy {
    static concept() {
        return (otherConcept ??= definitions().checkConcept(OTHER));
    }
    /**
     * Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin --
     * l'appelant écrit déjà le nom de la classe.
     */
    static type() {
        return (otherType ??= new dsviper.TypeKey(OtherKey.concept()));
    }
    constructor(identifier) {
        if (identifier instanceof dsviper.ValueKey) {
            if (!identifier.type().equals(OtherKey.type())) {
                throw new TypeError("cette valeur n'est pas un Core::OtherKey");
            }
            super(identifier);
        }
        else {
            super(dsviper.ValueKey.create(OtherKey.concept(), identifier));
        }
    }
    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create() {
        return new OtherKey(dsviper.ValueUUId.create());
    }
    static wrap(value) {
        return new OtherKey(dsviper.ValueKey.cast(value));
    }
    get instanceId() {
        return this.value.instanceId();
    }
    isValid() {
        return this.instanceId.isValid();
    }
    /** La clé, vue sans son type. */
    toAny() {
        return new AnyConceptKey(this.value.toAnyConceptKey());
    }
    toString() {
        return `Core::OtherKey(${this.value.representation()})`;
    }
}
let thingConcept;
let thingType;
/**
 * Une poignée sur une instance de Core::Thing, pas la chose elle-même.
 *
 * Ce sur quoi on accroche des choses.
 */
export class ThingKey extends Proxy {
    static concept() {
        return (thingConcept ??= definitions().checkConcept(THING));
    }
    /**
     * Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin --
     * l'appelant écrit déjà le nom de la classe.
     */
    static type() {
        return (thingType ??= new dsviper.TypeKey(ThingKey.concept()));
    }
    constructor(identifier) {
        if (identifier instanceof dsviper.ValueKey) {
            if (!identifier.type().equals(ThingKey.type())) {
                throw new TypeError("cette valeur n'est pas un Core::ThingKey");
            }
            super(identifier);
        }
        else {
            super(dsviper.ValueKey.create(ThingKey.concept(), identifier));
        }
    }
    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create() {
        return new ThingKey(dsviper.ValueUUId.create());
    }
    static wrap(value) {
        return new ThingKey(dsviper.ValueKey.cast(value));
    }
    get instanceId() {
        return this.value.instanceId();
    }
    isValid() {
        return this.instanceId.isValid();
    }
    /** La clé, vue sans son type. */
    toAny() {
        return new AnyConceptKey(this.value.toAnyConceptKey());
    }
    toString() {
        return `Core::ThingKey(${this.value.representation()})`;
    }
}
let sub_thingConcept;
let sub_thingType;
/**
 * Une poignée sur une instance de Core::SubThing, pas la chose elle-même.
 *
 * Un dérivé, dans le même namespace : le cas facile de l'héritage.
 */
export class SubThingKey extends Proxy {
    static concept() {
        return (sub_thingConcept ??= definitions().checkConcept(SUB_THING));
    }
    /**
     * Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin --
     * l'appelant écrit déjà le nom de la classe.
     */
    static type() {
        return (sub_thingType ??= new dsviper.TypeKey(SubThingKey.concept()));
    }
    constructor(identifier) {
        if (identifier instanceof dsviper.ValueKey) {
            if (!identifier.type().equals(SubThingKey.type())) {
                throw new TypeError("cette valeur n'est pas un Core::SubThingKey");
            }
            super(identifier);
        }
        else {
            super(dsviper.ValueKey.create(SubThingKey.concept(), identifier));
        }
    }
    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create() {
        return new SubThingKey(dsviper.ValueUUId.create());
    }
    static wrap(value) {
        return new SubThingKey(dsviper.ValueKey.cast(value));
    }
    get instanceId() {
        return this.value.instanceId();
    }
    isValid() {
        return this.instanceId.isValid();
    }
    /** La clé, vue sans son type. */
    toAny() {
        return new AnyConceptKey(this.value.toAnyConceptKey());
    }
    toString() {
        return `Core::SubThingKey(${this.value.representation()})`;
    }
}
let klubClub;
let klubType;
/** Une poignée sur une instance d'un membre de Core::Klub. */
export class KlubKey extends Proxy {
    static club() {
        return (klubClub ??= definitions().checkClub(KLUB));
    }
    static type() {
        return (klubType ??= new dsviper.TypeKey(KlubKey.club()));
    }
    constructor(key) {
        const value = key instanceof Proxy ? key.value : key;
        if (!KlubKey.club().isMember(value.typeConcept())) {
            throw new TypeError("cette clé ne désigne pas un membre de Core::Klub");
        }
        super(value.toClubKey(KlubKey.club()));
    }
    static wrap(value) {
        return new KlubKey(dsviper.ValueKey.cast(value));
    }
    get instanceId() {
        return this.value.instanceId();
    }
    /** La clé vue comme celle d'un membre, ou `undefined` si l'instance n'en est pas un. */
    as(member) {
        const concept = member.concept();
        return this.value.isMember(concept) ? member.wrap(this.value.toMemberKey(concept)) : undefined;
    }
    toString() {
        return `Core::KlubKey(${this.value.representation()})`;
    }
}
let gradeType;
/**
 * UN TYPE ET UNE VALEUR SOUS LE MÊME NOM, ce que TypeScript permet et qui dit exactement ce
 * qu'on veut : `Grade` annote, `Grade.low` désigne, `Grade.wrap` convertit. Le pack en
 * fait une classe qui enveloppe une `ValueEnumeration` ; une union de littéraux se vérifie
 * mieux et ne coûte aucun objet.
 */
export const Grade = {
    LOW: "low",
    HIGH: "high",
    type() {
        return (gradeType ??= definitions().checkEnumeration(GRADE));
    },
    wrap(value) {
        return dsviper.ValueEnumeration.cast(value).name();
    },
};
let colourType;
/** Core::Colour. Le même nom que Parts::Colour, un type différent -- la collision de re-export. */
export class Colour extends Proxy {
    static type() {
        return (colourType ??= definitions().checkStructure(COLOUR));
    }
    constructor(value) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(Colour.type())) {
                throw new TypeError("cette valeur n'est pas un Core::Colour");
            }
            super(value);
        }
        else {
            super(new dsviper.ValueStructure(Colour.type(), value));
        }
    }
    static wrap(value) {
        return new Colour(dsviper.ValueStructure.cast(value));
    }
    get r() {
        return this.value.at("r");
    }
    set r(value) {
        setField(this.value, "r", value);
    }
    get g() {
        return this.value.at("g");
    }
    set g(value) {
        setField(this.value, "g", value);
    }
    get b() {
        return this.value.at("b");
    }
    set b(value) {
        setField(this.value, "b", value);
    }
}
let scalarsType;
/** Core::Scalars. Toutes les formes scalaires du langage, dans le namespace qui n'en référence aucun
autre. Ce qui ne peut pas traverser une frontière est couvert ici, une fois. */
export class Scalars extends Proxy {
    static type() {
        return (scalarsType ??= definitions().checkStructure(SCALARS));
    }
    constructor(value) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(Scalars.type())) {
                throw new TypeError("cette valeur n'est pas un Core::Scalars");
            }
            super(value);
        }
        else {
            super(new dsviper.ValueStructure(Scalars.type(), value));
        }
    }
    static wrap(value) {
        return new Scalars(dsviper.ValueStructure.cast(value));
    }
    get f_bool() {
        return this.value.at("f_bool");
    }
    set f_bool(value) {
        setField(this.value, "f_bool", value);
    }
    get f_uint8() {
        return this.value.at("f_uint8");
    }
    set f_uint8(value) {
        setField(this.value, "f_uint8", value);
    }
    get f_uint16() {
        return this.value.at("f_uint16");
    }
    set f_uint16(value) {
        setField(this.value, "f_uint16", value);
    }
    get f_uint32() {
        return this.value.at("f_uint32");
    }
    set f_uint32(value) {
        setField(this.value, "f_uint32", value);
    }
    get f_uint64() {
        return this.value.at("f_uint64");
    }
    set f_uint64(value) {
        setField(this.value, "f_uint64", value);
    }
    get f_int8() {
        return this.value.at("f_int8");
    }
    set f_int8(value) {
        setField(this.value, "f_int8", value);
    }
    get f_int16() {
        return this.value.at("f_int16");
    }
    set f_int16(value) {
        setField(this.value, "f_int16", value);
    }
    get f_int32() {
        return this.value.at("f_int32");
    }
    set f_int32(value) {
        setField(this.value, "f_int32", value);
    }
    get f_int64() {
        return this.value.at("f_int64");
    }
    set f_int64(value) {
        setField(this.value, "f_int64", value);
    }
    get f_float() {
        return this.value.at("f_float");
    }
    set f_float(value) {
        setField(this.value, "f_float", value);
    }
    get f_double() {
        return this.value.at("f_double");
    }
    set f_double(value) {
        setField(this.value, "f_double", value);
    }
    get f_blob_id() {
        return this.value.at("f_blob_id");
    }
    set f_blob_id(value) {
        setField(this.value, "f_blob_id", value);
    }
    get f_commit_id() {
        return this.value.at("f_commit_id");
    }
    set f_commit_id(value) {
        setField(this.value, "f_commit_id", value);
    }
    get f_uuid() {
        return this.value.at("f_uuid");
    }
    set f_uuid(value) {
        setField(this.value, "f_uuid", value);
    }
    get f_string() {
        return this.value.at("f_string");
    }
    set f_string(value) {
        setField(this.value, "f_string", value);
    }
    get f_blob() {
        return this.value.at("f_blob");
    }
    set f_blob(value) {
        setField(this.value, "f_blob", value);
    }
    get f_any() {
        return this.value.at("f_any");
    }
    set f_any(value) {
        setField(this.value, "f_any", value);
    }
    get f_vec() {
        return wrap(this.value.at("f_vec", false));
    }
    set f_vec(value) {
        setField(this.value, "f_vec", value);
    }
    get f_mat() {
        return wrap(this.value.at("f_mat", false));
    }
    set f_mat(value) {
        setField(this.value, "f_mat", value);
    }
}
let singleType;
/** Core::Single. Une structure à un seul champ : le cas zéro/un que le générateur traite à part. */
export class Single extends Proxy {
    static type() {
        return (singleType ??= definitions().checkStructure(SINGLE));
    }
    constructor(value) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(Single.type())) {
                throw new TypeError("cette valeur n'est pas un Core::Single");
            }
            super(value);
        }
        else {
            super(new dsviper.ValueStructure(Single.type(), value));
        }
    }
    static wrap(value) {
        return new Single(dsviper.ValueStructure.cast(value));
    }
    get f_single() {
        return this.value.at("f_single");
    }
    set f_single(value) {
        setField(this.value, "f_single", value);
    }
}
let bagType;
/** Core::Bag. Et un document ordinaire dont un champ est un agrégat : les mêmes opérations, à une
adresse au lieu de la racine. */
export class Bag extends Proxy {
    static type() {
        return (bagType ??= definitions().checkStructure(BAG));
    }
    constructor(value) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(Bag.type())) {
                throw new TypeError("cette valeur n'est pas un Core::Bag");
            }
            super(value);
        }
        else {
            super(new dsviper.ValueStructure(Bag.type(), value));
        }
    }
    static wrap(value) {
        return new Bag(dsviper.ValueStructure.cast(value));
    }
    get members() {
        return wrap(this.value.at("members", false));
    }
    set members(value) {
        setField(this.value, "members", value);
    }
    get tints() {
        return wrap(this.value.at("tints", false));
    }
    set tints(value) {
        setField(this.value, "tints", value);
    }
    get trail() {
        return wrap(this.value.at("trail", false));
    }
    set trail(value) {
        setField(this.value, "trail", value);
    }
}
let defaultsType;
/** Core::Defaults. Les valeurs par défaut, qui sont un chemin de code à part. */
export class Defaults extends Proxy {
    static type() {
        return (defaultsType ??= definitions().checkStructure(DEFAULTS));
    }
    constructor(value) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(Defaults.type())) {
                throw new TypeError("cette valeur n'est pas un Core::Defaults");
            }
            super(value);
        }
        else {
            super(new dsviper.ValueStructure(Defaults.type(), value));
        }
    }
    static wrap(value) {
        return new Defaults(dsviper.ValueStructure.cast(value));
    }
    get f_uint8() {
        return this.value.at("f_uint8");
    }
    set f_uint8(value) {
        setField(this.value, "f_uint8", value);
    }
    get f_float() {
        return this.value.at("f_float");
    }
    set f_float(value) {
        setField(this.value, "f_float", value);
    }
    get f_string() {
        return this.value.at("f_string");
    }
    set f_string(value) {
        setField(this.value, "f_string", value);
    }
    get f_uuid() {
        return this.value.at("f_uuid");
    }
    set f_uuid(value) {
        setField(this.value, "f_uuid", value);
    }
    get f_vec() {
        return wrap(this.value.at("f_vec", false));
    }
    set f_vec(value) {
        setField(this.value, "f_vec", value);
    }
    get f_grade() {
        return wrap(this.value.at("f_grade", false));
    }
    set f_grade(value) {
        setField(this.value, "f_grade", value);
    }
    get f_colour() {
        return wrap(this.value.at("f_colour", false));
    }
    set f_colour(value) {
        setField(this.value, "f_colour", value);
    }
}
// Les classes de cette unité, par l'identifiant d'exécution de leur type : c'est ce qui permet
// à `wrap` de rendre un élément de conteneur, ou un document d'attachment, avec son nom.
register([OTHER, OtherKey], [THING, ThingKey], [SUB_THING, SubThingKey], [KLUB, KlubKey], [GRADE, Grade], [BAG, Bag], [COLOUR, Colour], [DEFAULTS, Defaults], [SCALARS, Scalars], [SINGLE, Single]);
