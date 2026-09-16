// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar
/** Projection — les types que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";
import { Proxy } from "../_codegen/proxy.js";
import { AnyConceptKey, isKnown, register, setField, wrap } from "../_codegen/registry.js";
import { definitions } from "../index.js";
// ── l'identité de cette unité dans le modèle ──
//
// LE MÊME ARTEFACT QU'EN C++ ET EN PYTHON, POUR LA MÊME RAISON : plusieurs couches en ont
// besoin et ce n'est pas de la sérialisation.
export const LINK = dsviper.ValueUUId.create("d4f2e968-390a-ad1f-83d4-00e72fd30a50");
export const DERIVED_MATERIAL = dsviper.ValueUUId.create("4d1e4a0c-e262-8449-d792-44ee5aa2bb3f");
export const PAIR = dsviper.ValueUUId.create("9b902df2-0abc-efa8-dc98-e9de83b1c7ab");
let linkConcept;
let linkType;
/**
 * Une poignée sur une instance de Projection::Link, pas la chose elle-même.
 *
 * What one link between two driver materials is.
 */
export class LinkKey extends Proxy {
    static concept() {
        return (linkConcept ??= definitions().checkConcept(LINK));
    }
    /**
     * Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin --
     * l'appelant écrit déjà le nom de la classe.
     */
    static type() {
        return (linkType ??= new dsviper.TypeKey(LinkKey.concept()));
    }
    constructor(identifier) {
        if (identifier instanceof dsviper.ValueKey) {
            if (!identifier.type().equals(LinkKey.type())) {
                throw new TypeError("cette valeur n'est pas un Projection::LinkKey");
            }
            super(identifier);
        }
        else {
            super(dsviper.ValueKey.create(LinkKey.concept(), identifier));
        }
    }
    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create() {
        return new LinkKey(dsviper.ValueUUId.create());
    }
    static wrap(value) {
        return new LinkKey(dsviper.ValueKey.cast(value));
    }
    static decode(blob) {
        return new LinkKey(dsviper.ValueKey.cast(dsviper.Value.decode(blob, LinkKey.type(), definitions())));
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
    /** L'instance et son type, dits comme le modèle les nomme. */
    description() {
        return `${this.value.instanceId().encoded()}:Projection::LinkKey`;
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
        return value.typeConcept().runtimeId().equals(LINK)
            ? new LinkKey(value) : undefined;
    }
    toString() {
        return this.description();
    }
}
let derived_materialConcept;
let derived_materialType;
/**
 * Une poignée sur une instance de Projection::DerivedMaterial, pas la chose elle-même.
 *
 * A concept whose parent lives in another namespace.
 */
export class DerivedMaterialKey extends Proxy {
    static concept() {
        return (derived_materialConcept ??= definitions().checkConcept(DERIVED_MATERIAL));
    }
    /**
     * Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin --
     * l'appelant écrit déjà le nom de la classe.
     */
    static type() {
        return (derived_materialType ??= new dsviper.TypeKey(DerivedMaterialKey.concept()));
    }
    constructor(identifier) {
        if (identifier instanceof dsviper.ValueKey) {
            if (!identifier.type().equals(DerivedMaterialKey.type())) {
                throw new TypeError("cette valeur n'est pas un Projection::DerivedMaterialKey");
            }
            super(identifier);
        }
        else {
            super(dsviper.ValueKey.create(DerivedMaterialKey.concept(), identifier));
        }
    }
    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create() {
        return new DerivedMaterialKey(dsviper.ValueUUId.create());
    }
    static wrap(value) {
        return new DerivedMaterialKey(dsviper.ValueKey.cast(value));
    }
    static decode(blob) {
        return new DerivedMaterialKey(dsviper.ValueKey.cast(dsviper.Value.decode(blob, DerivedMaterialKey.type(), definitions())));
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
    /** L'instance et son type, dits comme le modèle les nomme. */
    description() {
        return `${this.value.instanceId().encoded()}:Projection::DerivedMaterialKey`;
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
        return value.typeConcept().runtimeId().equals(DERIVED_MATERIAL)
            ? new DerivedMaterialKey(value) : undefined;
    }
    toString() {
        return this.description();
    }
}
let pairType;
/** Projection::Pair. Two keys from two namespaces in one structure -- the key<NS::C> edge. */
export class Pair extends Proxy {
    static type() {
        return (pairType ??= definitions().checkStructure(PAIR));
    }
    constructor(value) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(Pair.type())) {
                throw new TypeError("cette valeur n'est pas un Projection::Pair");
            }
            super(value);
        }
        else {
            super(new dsviper.ValueStructure(Pair.type(), value));
        }
    }
    static wrap(value) {
        return new Pair(dsviper.ValueStructure.cast(value));
    }
    static decode(blob) {
        return new Pair(dsviper.ValueStructure.cast(dsviper.Value.decode(blob, Pair.type(), definitions())));
    }
    get a() {
        return wrap(this.value.at("a", false));
    }
    set a(value) {
        setField(this.value, "a", value);
    }
    get b() {
        return wrap(this.value.at("b", false));
    }
    set b(value) {
        setField(this.value, "b", value);
    }
}
// Les classes de cette unité, par l'identifiant d'exécution de leur type : c'est ce qui permet
// à `wrap` de rendre un élément de conteneur, ou un document d'attachment, avec son nom.
register([LINK, LinkKey], [DERIVED_MATERIAL, DerivedMaterialKey], [PAIR, Pair]);
