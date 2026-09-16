// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

/** Projection — les types que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";

import { Mapping, Ordered, Sequence } from "../_codegen/container.js";
import { Proxy } from "../_codegen/proxy.js";
import { AnyConceptKey, isKnown, register, setField, wrap } from "../_codegen/registry.js";
import { definitions } from "../index.js";
import * as model_b from "../model_b/data.js";
import * as model_a from "../model_a/data.js";

// ── l'identité de cette unité dans le modèle ──
//
// LE MÊME ARTEFACT QU'EN C++ ET EN PYTHON, POUR LA MÊME RAISON : plusieurs couches en ont
// besoin et ce n'est pas de la sérialisation.

export const LINK = dsviper.ValueUUId.create("d4f2e968-390a-ad1f-83d4-00e72fd30a50");
export const DERIVED_MATERIAL = dsviper.ValueUUId.create("4d1e4a0c-e262-8449-d792-44ee5aa2bb3f");
export const PAIR = dsviper.ValueUUId.create("9b902df2-0abc-efa8-dc98-e9de83b1c7ab");

let linkConcept: dsviper.TypeConcept | undefined;
let linkType: dsviper.TypeKey | undefined;

/**
 * Une poignée sur une instance de Projection::Link, pas la chose elle-même.
 *
 * What one link between two driver materials is.
 */
export class LinkKey extends Proxy<dsviper.ValueKey> {
    static concept(): dsviper.TypeConcept {
        return (linkConcept ??= definitions().checkConcept(LINK));
    }

    /**
     * Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin --
     * l'appelant écrit déjà le nom de la classe.
     */
    static type(): dsviper.TypeKey {
        return (linkType ??= new dsviper.TypeKey(LinkKey.concept()));
    }

    constructor(identifier?: dsviper.ValueKey | dsviper.ValueUUId | null) {
        if (identifier === null) {
            // `null` EXPLICITE N'EST PAS L'ABSENCE D'ARGUMENT. `new XKey()` demande une clé
            // neuve ; `new XKey(null)` passe quelque chose, et ce quelque chose n'en est pas un.
            throw new TypeError("null n'est pas un identifiant d'instance");
        }
        if (identifier instanceof dsviper.ValueKey) {
            if (!identifier.isMember(LinkKey.concept())) {
                throw new TypeError("cette valeur n'est pas un Projection::LinkKey");
            }
            super(identifier);
        } else {
            super(dsviper.ValueKey.create(LinkKey.concept(), identifier));
        }
    }

    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create(): LinkKey {
        return new LinkKey(dsviper.ValueUUId.create());
    }

    static wrap(value: dsviper.Value): LinkKey {
        return new LinkKey(dsviper.ValueKey.cast(value));
    }

    static decode(blob: dsviper.ValueBlob): LinkKey {
        return new LinkKey(dsviper.ValueKey.cast(
            dsviper.Value.decode(blob, LinkKey.type(), definitions())));
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

    /** Un ordre total sur les clés — ce qui permet de trier, que JavaScript ne déduit pas. */
    compareTo(other: LinkKey | dsviper.ValueKey): number {
        return this.value.compare(other instanceof Proxy ? other.value : other);
    }

    /** L'instance et son type, dits comme le modèle les nomme. */
    description(): string {
        return `${this.value.instanceId().encoded()}:Projection::LinkKey`;
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
    static fromAnyConceptKey(key: AnyConceptKey | dsviper.ValueKey): LinkKey | undefined {
        const value = key instanceof AnyConceptKey ? key.value : key;
        return value.typeConcept().runtimeId().equals(LINK)
            ? new LinkKey(value) : undefined;
    }

    override toString(): string {
        return this.description();
    }
}

let derived_materialConcept: dsviper.TypeConcept | undefined;
let derived_materialType: dsviper.TypeKey | undefined;

/**
 * Une poignée sur une instance de Projection::DerivedMaterial, pas la chose elle-même.
 *
 * A concept whose parent lives in another namespace.
 */
export class DerivedMaterialKey extends Proxy<dsviper.ValueKey> {
    static concept(): dsviper.TypeConcept {
        return (derived_materialConcept ??= definitions().checkConcept(DERIVED_MATERIAL));
    }

    /**
     * Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin --
     * l'appelant écrit déjà le nom de la classe.
     */
    static type(): dsviper.TypeKey {
        return (derived_materialType ??= new dsviper.TypeKey(DerivedMaterialKey.concept()));
    }

    constructor(identifier?: dsviper.ValueKey | dsviper.ValueUUId | null) {
        if (identifier === null) {
            // `null` EXPLICITE N'EST PAS L'ABSENCE D'ARGUMENT. `new XKey()` demande une clé
            // neuve ; `new XKey(null)` passe quelque chose, et ce quelque chose n'en est pas un.
            throw new TypeError("null n'est pas un identifiant d'instance");
        }
        if (identifier instanceof dsviper.ValueKey) {
            if (!identifier.isMember(DerivedMaterialKey.concept())) {
                throw new TypeError("cette valeur n'est pas un Projection::DerivedMaterialKey");
            }
            super(identifier);
        } else {
            super(dsviper.ValueKey.create(DerivedMaterialKey.concept(), identifier));
        }
    }

    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create(): DerivedMaterialKey {
        return new DerivedMaterialKey(dsviper.ValueUUId.create());
    }

    static wrap(value: dsviper.Value): DerivedMaterialKey {
        return new DerivedMaterialKey(dsviper.ValueKey.cast(value));
    }

    static decode(blob: dsviper.ValueBlob): DerivedMaterialKey {
        return new DerivedMaterialKey(dsviper.ValueKey.cast(
            dsviper.Value.decode(blob, DerivedMaterialKey.type(), definitions())));
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

    /** Un ordre total sur les clés — ce qui permet de trier, que JavaScript ne déduit pas. */
    compareTo(other: DerivedMaterialKey | dsviper.ValueKey): number {
        return this.value.compare(other instanceof Proxy ? other.value : other);
    }

    /** L'instance et son type, dits comme le modèle les nomme. */
    description(): string {
        return `${this.value.instanceId().encoded()}:Projection::DerivedMaterialKey`;
    }

    isKnown(): boolean {
        return isKnown(this.value);
    }

    /** Élargir vers le parent. Ne perd rien : l'identifiant d'exécution reste celui du concept
     *  réel, et c'est ce qui permet d'en revenir ensuite. */
    toParentKey(): model_a.MaterialKey {
        return new model_a.MaterialKey(this.value);
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
    static fromAnyConceptKey(key: AnyConceptKey | dsviper.ValueKey): DerivedMaterialKey | undefined {
        const value = key instanceof AnyConceptKey ? key.value : key;
        return value.typeConcept().runtimeId().equals(DERIVED_MATERIAL)
            ? new DerivedMaterialKey(value) : undefined;
    }

    override toString(): string {
        return this.description();
    }
}

let pairType: dsviper.TypeStructure | undefined;

/** Projection::Pair. Two keys from two namespaces in one structure -- the key<NS::C> edge. */
export class Pair extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure {
        return (pairType ??= definitions().checkStructure(PAIR));
    }

    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(Pair.type())) {
                throw new TypeError("cette valeur n'est pas un Projection::Pair");
            }
            super(value);
        } else {
            super(new dsviper.ValueStructure(Pair.type(), value));
        }
    }

    static wrap(value: dsviper.Value): Pair {
        return new Pair(dsviper.ValueStructure.cast(value));
    }

    static decode(blob: dsviper.ValueBlob): Pair {
        return new Pair(dsviper.ValueStructure.cast(
            dsviper.Value.decode(blob, Pair.type(), definitions())));
    }

    get a(): model_a.MaterialKey {
        return wrap(this.value.at("a", false));
    }

    set a(value: model_a.MaterialKey) {
        setField(this.value, "a", value);
    }

    get b(): model_b.MaterialKey {
        return wrap(this.value.at("b", false));
    }

    set b(value: model_b.MaterialKey) {
        setField(this.value, "b", value);
    }
}

// Les classes de cette unité, par l'identifiant d'exécution de leur type : c'est ce qui permet
// à `wrap` de rendre un élément de conteneur, ou un document d'attachment, avec son nom.
register([LINK, LinkKey], [DERIVED_MATERIAL, DerivedMaterialKey], [PAIR, Pair]);