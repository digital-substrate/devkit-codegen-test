// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar
/** Woven — les types que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";
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
let knotConcept;
let knotType;
/**
 * Une poignée sur une instance de Woven::Knot, pas la chose elle-même.
 *
 * Ce sur quoi les attachments de ce namespace sont accrochés.
 */
export class KnotKey extends Proxy {
    static concept() {
        return (knotConcept ??= definitions().checkConcept(KNOT));
    }
    /**
     * Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin --
     * l'appelant écrit déjà le nom de la classe.
     */
    static type() {
        return (knotType ??= new dsviper.TypeKey(KnotKey.concept()));
    }
    constructor(identifier) {
        if (identifier === null) {
            // `null` EXPLICITE N'EST PAS L'ABSENCE D'ARGUMENT. `new XKey()` demande une clé
            // neuve ; `new XKey(null)` passe quelque chose, et ce quelque chose n'en est pas un.
            throw new TypeError("null n'est pas un identifiant d'instance");
        }
        if (identifier instanceof dsviper.ValueKey) {
            if (!identifier.isMember(KnotKey.concept())) {
                throw new TypeError("cette valeur n'est pas un Woven::KnotKey");
            }
            super(identifier);
        }
        else {
            super(dsviper.ValueKey.create(KnotKey.concept(), identifier));
        }
    }
    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create() {
        return new KnotKey(dsviper.ValueUUId.create());
    }
    static wrap(value) {
        return new KnotKey(dsviper.ValueKey.cast(value));
    }
    static decode(blob) {
        return new KnotKey(dsviper.ValueKey.cast(dsviper.Value.decode(blob, KnotKey.type(), definitions())));
    }
    instanceId() {
        return this.value.instanceId();
    }
    runtimeId() {
        return this.value.typeConcept().runtimeId();
    }
    isValid() {
        return this.value.instanceId().isValid();
    }
    /** Un ordre total sur les clés — ce qui permet de trier, que JavaScript ne déduit pas. */
    compareTo(other) {
        return this.value.compare(other instanceof Proxy ? other.value : other);
    }
    /** L'instance et son type, dits comme le modèle les nomme. */
    description() {
        return `${this.value.instanceId().encoded()}:Woven::KnotKey`;
    }
    isKnown() {
        return isKnown(this.value);
    }
    /** La clé, vue sans son type. */
    toAnyConceptKey() {
        return new AnyConceptKey(this.value.toAnyConceptKey());
    }
    /** La clé non typée, retypée — ou `undefined` si elle ne désigne pas ce concept.
     *
     * LE CHEMIN DE RETOUR, ET IL PEUT ÉCHOUER. Élargir ne perd rien ; rétrécir pose une
     * question dont la réponse est dans l'identifiant que la valeur porte.
     */
    static fromAnyConceptKey(key) {
        const value = key instanceof AnyConceptKey ? key.value : key;
        return value.typeConcept().runtimeId().equals(KNOT)
            ? new KnotKey(value) : undefined;
    }
    toString() {
        return this.description();
    }
}
let derivedConcept;
let derivedType;
/**
 * Une poignée sur une instance de Woven::Derived, pas la chose elle-même.
 *
 * Un concept dont le parent vit ailleurs.
 */
export class DerivedKey extends Proxy {
    static concept() {
        return (derivedConcept ??= definitions().checkConcept(DERIVED));
    }
    /**
     * Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin --
     * l'appelant écrit déjà le nom de la classe.
     */
    static type() {
        return (derivedType ??= new dsviper.TypeKey(DerivedKey.concept()));
    }
    constructor(identifier) {
        if (identifier === null) {
            // `null` EXPLICITE N'EST PAS L'ABSENCE D'ARGUMENT. `new XKey()` demande une clé
            // neuve ; `new XKey(null)` passe quelque chose, et ce quelque chose n'en est pas un.
            throw new TypeError("null n'est pas un identifiant d'instance");
        }
        if (identifier instanceof dsviper.ValueKey) {
            if (!identifier.isMember(DerivedKey.concept())) {
                throw new TypeError("cette valeur n'est pas un Woven::DerivedKey");
            }
            super(identifier);
        }
        else {
            super(dsviper.ValueKey.create(DerivedKey.concept(), identifier));
        }
    }
    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create() {
        return new DerivedKey(dsviper.ValueUUId.create());
    }
    static wrap(value) {
        return new DerivedKey(dsviper.ValueKey.cast(value));
    }
    static decode(blob) {
        return new DerivedKey(dsviper.ValueKey.cast(dsviper.Value.decode(blob, DerivedKey.type(), definitions())));
    }
    instanceId() {
        return this.value.instanceId();
    }
    runtimeId() {
        return this.value.typeConcept().runtimeId();
    }
    isValid() {
        return this.value.instanceId().isValid();
    }
    /** Un ordre total sur les clés — ce qui permet de trier, que JavaScript ne déduit pas. */
    compareTo(other) {
        return this.value.compare(other instanceof Proxy ? other.value : other);
    }
    /** L'instance et son type, dits comme le modèle les nomme. */
    description() {
        return `${this.value.instanceId().encoded()}:Woven::DerivedKey`;
    }
    isKnown() {
        return isKnown(this.value);
    }
    /** Élargir vers le parent. Ne perd rien : l'identifiant d'exécution reste celui du concept
     *  réel, et c'est ce qui permet d'en revenir ensuite. */
    toParentKey() {
        return new core.ThingKey(this.value);
    }
    /** La clé, vue sans son type. */
    toAnyConceptKey() {
        return new AnyConceptKey(this.value.toAnyConceptKey());
    }
    /** La clé non typée, retypée — ou `undefined` si elle ne désigne pas ce concept.
     *
     * LE CHEMIN DE RETOUR, ET IL PEUT ÉCHOUER. Élargir ne perd rien ; rétrécir pose une
     * question dont la réponse est dans l'identifiant que la valeur porte.
     */
    static fromAnyConceptKey(key) {
        const value = key instanceof AnyConceptKey ? key.value : key;
        return value.typeConcept().runtimeId().equals(DERIVED)
            ? new DerivedKey(value) : undefined;
    }
    toString() {
        return this.description();
    }
}
let weaveClub;
let weaveType;
/** Une poignée sur une instance d'un membre de Woven::Weave. */
export class WeaveKey extends Proxy {
    static club() {
        return (weaveClub ??= definitions().checkClub(WEAVE));
    }
    static type() {
        return (weaveType ??= new dsviper.TypeKey(WeaveKey.club()));
    }
    constructor(key) {
        const value = key instanceof Proxy ? key.value : key;
        if (!WeaveKey.club().isMember(value.typeConcept())) {
            throw new TypeError("cette clé ne désigne pas un membre de Woven::Weave");
        }
        super(value.toClubKey(WeaveKey.club()));
    }
    static wrap(value) {
        return new WeaveKey(dsviper.ValueKey.cast(value));
    }
    static decode(blob) {
        return new WeaveKey(dsviper.ValueKey.cast(dsviper.Value.decode(blob, WeaveKey.type(), definitions())));
    }
    instanceId() {
        return this.value.instanceId();
    }
    runtimeId() {
        return this.value.typeConcept().runtimeId();
    }
    isValid() {
        return this.value.instanceId().isValid();
    }
    description() {
        return `${this.value.instanceId().encoded()}:Woven::WeaveKey`;
    }
    isKnown() {
        return isKnown(this.value);
    }
    /** La clé vue comme celle d'un membre, ou `undefined` si l'instance n'en est pas un. */
    /** La clé d'un membre, vue comme celle du club. */
    static fromCoreThingKey(key) {
        return new WeaveKey(key);
    }
    /** La clé d'un membre, vue comme celle du club. */
    static fromPartsThingKey(key) {
        return new WeaveKey(key);
    }
    /** La clé vue comme celle de ce membre, ou `undefined` si l'instance n'en est pas un. */
    toCoreThingKey() {
        return this.as(core.ThingKey);
    }
    /** Le même, sous le mot que le pack emploie. Deux noms pour une question qui n'en est
     *  qu'une, parce que les deux se lisent et qu'aucun ne se devine depuis l'autre. */
    asCoreThingKey() {
        return this.as(core.ThingKey);
    }
    /** La clé vue comme celle de ce membre, ou `undefined` si l'instance n'en est pas un. */
    toPartsThingKey() {
        return this.as(parts.ThingKey);
    }
    /** Le même, sous le mot que le pack emploie. Deux noms pour une question qui n'en est
     *  qu'une, parce que les deux se lisent et qu'aucun ne se devine depuis l'autre. */
    asPartsThingKey() {
        return this.as(parts.ThingKey);
    }
    as(member) {
        const concept = member.concept();
        return this.value.isMember(concept) ? member.wrap(this.value.toMemberKey(concept)) : undefined;
    }
    toString() {
        return this.description();
    }
}
let entitiesType;
/** Woven::Entities. Les entités des deux fournisseurs, nues, comme champs. */
export class Entities extends Proxy {
    static type() {
        return (entitiesType ??= definitions().checkStructure(ENTITIES));
    }
    constructor(value) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(Entities.type())) {
                throw new TypeError("cette valeur n'est pas un Woven::Entities");
            }
            super(value);
        }
        else {
            super(new dsviper.ValueStructure(Entities.type(), value));
        }
    }
    static wrap(value) {
        return new Entities(dsviper.ValueStructure.cast(value));
    }
    static decode(blob) {
        return new Entities(dsviper.ValueStructure.cast(dsviper.Value.decode(blob, Entities.type(), definitions())));
    }
    get f_core_grade() {
        return wrap(this.value.at("f_core_grade", false));
    }
    set f_core_grade(value) {
        setField(this.value, "f_core_grade", value);
    }
    get f_parts_grade() {
        return wrap(this.value.at("f_parts_grade", false));
    }
    set f_parts_grade(value) {
        setField(this.value, "f_parts_grade", value);
    }
    get f_core_colour() {
        return wrap(this.value.at("f_core_colour", false));
    }
    set f_core_colour(value) {
        setField(this.value, "f_core_colour", value);
    }
    get f_parts_colour() {
        return wrap(this.value.at("f_parts_colour", false));
    }
    set f_parts_colour(value) {
        setField(this.value, "f_parts_colour", value);
    }
    get f_single() {
        return wrap(this.value.at("f_single", false));
    }
    set f_single(value) {
        setField(this.value, "f_single", value);
    }
    get f_thing() {
        return wrap(this.value.at("f_thing", false));
    }
    set f_thing(value) {
        setField(this.value, "f_thing", value);
    }
    get f_sub_thing() {
        return wrap(this.value.at("f_sub_thing", false));
    }
    set f_sub_thing(value) {
        setField(this.value, "f_sub_thing", value);
    }
    get f_other_thing() {
        return wrap(this.value.at("f_other_thing", false));
    }
    set f_other_thing(value) {
        setField(this.value, "f_other_thing", value);
    }
    get f_klub() {
        return wrap(this.value.at("f_klub", false));
    }
    set f_klub(value) {
        setField(this.value, "f_klub", value);
    }
    get f_any_concept() {
        return wrap(this.value.at("f_any_concept", false));
    }
    set f_any_concept(value) {
        setField(this.value, "f_any_concept", value);
    }
}
let compositesType;
/** Woven::Composites. Chaque conteneur, avec des éléments des deux fournisseurs. */
export class Composites extends Proxy {
    static type() {
        return (compositesType ??= definitions().checkStructure(COMPOSITES));
    }
    constructor(value) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(Composites.type())) {
                throw new TypeError("cette valeur n'est pas un Woven::Composites");
            }
            super(value);
        }
        else {
            super(new dsviper.ValueStructure(Composites.type(), value));
        }
    }
    static wrap(value) {
        return new Composites(dsviper.ValueStructure.cast(value));
    }
    static decode(blob) {
        return new Composites(dsviper.ValueStructure.cast(dsviper.Value.decode(blob, Composites.type(), definitions())));
    }
    get f_tuple() {
        return wrap(this.value.at("f_tuple", false));
    }
    set f_tuple(value) {
        setField(this.value, "f_tuple", value);
    }
    get f_optional() {
        return wrap(this.value.at("f_optional", false));
    }
    set f_optional(value) {
        setField(this.value, "f_optional", value);
    }
    get f_vector() {
        return wrap(this.value.at("f_vector", false));
    }
    set f_vector(value) {
        setField(this.value, "f_vector", value);
    }
    get f_set() {
        return wrap(this.value.at("f_set", false));
    }
    set f_set(value) {
        setField(this.value, "f_set", value);
    }
    get f_map_keys() {
        return wrap(this.value.at("f_map_keys", false));
    }
    set f_map_keys(value) {
        setField(this.value, "f_map_keys", value);
    }
    get f_map_enum() {
        return wrap(this.value.at("f_map_enum", false));
    }
    set f_map_enum(value) {
        setField(this.value, "f_map_enum", value);
    }
    get f_xarray() {
        return wrap(this.value.at("f_xarray", false));
    }
    set f_xarray(value) {
        setField(this.value, "f_xarray", value);
    }
    get f_variant() {
        return wrap(this.value.at("f_variant", false));
    }
    set f_variant(value) {
        setField(this.value, "f_variant", value);
    }
}
let nestedType;
/** Woven::Nested. Une structure d'ici qui contient une structure d'ici : la profondeur reste locale. */
export class Nested extends Proxy {
    static type() {
        return (nestedType ??= definitions().checkStructure(NESTED));
    }
    constructor(value) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(Nested.type())) {
                throw new TypeError("cette valeur n'est pas un Woven::Nested");
            }
            super(value);
        }
        else {
            super(new dsviper.ValueStructure(Nested.type(), value));
        }
    }
    static wrap(value) {
        return new Nested(dsviper.ValueStructure.cast(value));
    }
    static decode(blob) {
        return new Nested(dsviper.ValueStructure.cast(dsviper.Value.decode(blob, Nested.type(), definitions())));
    }
    get f_composites() {
        return wrap(this.value.at("f_composites", false));
    }
    set f_composites(value) {
        setField(this.value, "f_composites", value);
    }
    get f_entities() {
        return wrap(this.value.at("f_entities", false));
    }
    set f_entities(value) {
        setField(this.value, "f_entities", value);
    }
}
// Les classes de cette unité, par l'identifiant d'exécution de leur type : c'est ce qui permet
// à `wrap` de rendre un élément de conteneur, ou un document d'attachment, avec son nom.
register([KNOT, KnotKey], [DERIVED, DerivedKey], [WEAVE, WeaveKey], [COMPOSITES, Composites], [ENTITIES, Entities], [NESTED, Nested]);
