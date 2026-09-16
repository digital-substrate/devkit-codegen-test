// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/features/Features.dsm.json by kibo-2.0.0.jar

/** Demo — les types que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";

import { Mapping, Ordered, Sequence } from "../_codegen/container.js";
import { Proxy } from "../_codegen/proxy.js";
import { AnyConceptKey, isKnown, register, setField, wrap } from "../_codegen/registry.js";
import { definitions } from "../index.js";

// ── l'identité de cette unité dans le modèle ──
//
// LE MÊME ARTEFACT QU'EN C++ ET EN PYTHON, POUR LA MÊME RAISON : plusieurs couches en ont
// besoin et ce n'est pas de la sérialisation.

export const CONCEPT_A = dsviper.ValueUUId.create("bcc4e978-a438-ddba-66b9-d767b3b2649e");
export const CONCEPT_B = dsviper.ValueUUId.create("cdb6cd9f-f1b4-03b0-dff8-b8a2092ec01c");
export const CONCEPT_COVERAGE = dsviper.ValueUUId.create("28892760-a292-acbb-40ba-1aa63fc833e6");
export const CONCEPT_D = dsviper.ValueUUId.create("edc1351f-a74f-2036-f170-e1a67570b90a");
export const CONCEPT_C = dsviper.ValueUUId.create("ce7c9e3d-ae5f-2e57-c693-4b3e351d105b");
export const EMPTY_KLUB = dsviper.ValueUUId.create("f1a3dba5-200b-4fb9-e8e7-a5a62af2a843");
export const KLUB = dsviper.ValueUUId.create("0e64c619-6b27-330c-52ca-d2b0b6d88c0a");
export const ENUMERATION_E = dsviper.ValueUUId.create("57233334-ee71-b77f-d6a6-b4ff25bb2350");
export const STRUCTURE_S = dsviper.ValueUUId.create("c4f62cf6-2d27-05b0-018c-67d1b99df4a6");
export const STRUCTURE_T = dsviper.ValueUUId.create("773ad0a2-1c7b-302e-e1b5-314ab0edb74a");
export const STRUCTURE_U = dsviper.ValueUUId.create("019d066d-bd5a-19b7-4565-9c5a6f95c808");
export const STRUCTURE_V = dsviper.ValueUUId.create("8b5d06ab-5a9f-d427-23b8-7ec3611aabde");
export const STRUCTURE_W = dsviper.ValueUUId.create("df0e54fc-b3ac-a527-d8d7-678fc2d56d3f");

let concept_aConcept: dsviper.TypeConcept | undefined;
let concept_aType: dsviper.TypeKey | undefined;

/**
 * Une poignée sur une instance de Demo::ConceptA, pas la chose elle-même.
 *
 * This is the documentation for the concept A
 */
export class ConceptAKey extends Proxy<dsviper.ValueKey> {
    static concept(): dsviper.TypeConcept {
        return (concept_aConcept ??= definitions().checkConcept(CONCEPT_A));
    }

    /**
     * Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin --
     * l'appelant écrit déjà le nom de la classe.
     */
    static type(): dsviper.TypeKey {
        return (concept_aType ??= new dsviper.TypeKey(ConceptAKey.concept()));
    }

    constructor(identifier?: dsviper.ValueKey | dsviper.ValueUUId) {
        if (identifier instanceof dsviper.ValueKey) {
            if (!identifier.type().equals(ConceptAKey.type())) {
                throw new TypeError("cette valeur n'est pas un Demo::ConceptAKey");
            }
            super(identifier);
        } else {
            super(dsviper.ValueKey.create(ConceptAKey.concept(), identifier));
        }
    }

    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create(): ConceptAKey {
        return new ConceptAKey(dsviper.ValueUUId.create());
    }

    static wrap(value: dsviper.Value): ConceptAKey {
        return new ConceptAKey(dsviper.ValueKey.cast(value));
    }

    static decode(blob: dsviper.ValueBlob): ConceptAKey {
        return new ConceptAKey(dsviper.ValueKey.cast(
            dsviper.Value.decode(blob, ConceptAKey.type(), definitions())));
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
        return `${this.value.instanceId().encoded()}:Demo::ConceptAKey`;
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
    static fromAnyConceptKey(key: AnyConceptKey | dsviper.ValueKey): ConceptAKey | undefined {
        const value = key instanceof AnyConceptKey ? key.value : key;
        return value.typeConcept().runtimeId().equals(CONCEPT_A)
            ? new ConceptAKey(value) : undefined;
    }

    override toString(): string {
        return this.description();
    }
}

let concept_bConcept: dsviper.TypeConcept | undefined;
let concept_bType: dsviper.TypeKey | undefined;

/**
 * Une poignée sur une instance de Demo::ConceptB, pas la chose elle-même.
 */
export class ConceptBKey extends Proxy<dsviper.ValueKey> {
    static concept(): dsviper.TypeConcept {
        return (concept_bConcept ??= definitions().checkConcept(CONCEPT_B));
    }

    /**
     * Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin --
     * l'appelant écrit déjà le nom de la classe.
     */
    static type(): dsviper.TypeKey {
        return (concept_bType ??= new dsviper.TypeKey(ConceptBKey.concept()));
    }

    constructor(identifier?: dsviper.ValueKey | dsviper.ValueUUId) {
        if (identifier instanceof dsviper.ValueKey) {
            if (!identifier.type().equals(ConceptBKey.type())) {
                throw new TypeError("cette valeur n'est pas un Demo::ConceptBKey");
            }
            super(identifier);
        } else {
            super(dsviper.ValueKey.create(ConceptBKey.concept(), identifier));
        }
    }

    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create(): ConceptBKey {
        return new ConceptBKey(dsviper.ValueUUId.create());
    }

    static wrap(value: dsviper.Value): ConceptBKey {
        return new ConceptBKey(dsviper.ValueKey.cast(value));
    }

    static decode(blob: dsviper.ValueBlob): ConceptBKey {
        return new ConceptBKey(dsviper.ValueKey.cast(
            dsviper.Value.decode(blob, ConceptBKey.type(), definitions())));
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
        return `${this.value.instanceId().encoded()}:Demo::ConceptBKey`;
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
    static fromAnyConceptKey(key: AnyConceptKey | dsviper.ValueKey): ConceptBKey | undefined {
        const value = key instanceof AnyConceptKey ? key.value : key;
        return value.typeConcept().runtimeId().equals(CONCEPT_B)
            ? new ConceptBKey(value) : undefined;
    }

    override toString(): string {
        return this.description();
    }
}

let concept_coverageConcept: dsviper.TypeConcept | undefined;
let concept_coverageType: dsviper.TypeKey | undefined;

/**
 * Une poignée sur une instance de Demo::ConceptCoverage, pas la chose elle-même.
 */
export class ConceptCoverageKey extends Proxy<dsviper.ValueKey> {
    static concept(): dsviper.TypeConcept {
        return (concept_coverageConcept ??= definitions().checkConcept(CONCEPT_COVERAGE));
    }

    /**
     * Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin --
     * l'appelant écrit déjà le nom de la classe.
     */
    static type(): dsviper.TypeKey {
        return (concept_coverageType ??= new dsviper.TypeKey(ConceptCoverageKey.concept()));
    }

    constructor(identifier?: dsviper.ValueKey | dsviper.ValueUUId) {
        if (identifier instanceof dsviper.ValueKey) {
            if (!identifier.type().equals(ConceptCoverageKey.type())) {
                throw new TypeError("cette valeur n'est pas un Demo::ConceptCoverageKey");
            }
            super(identifier);
        } else {
            super(dsviper.ValueKey.create(ConceptCoverageKey.concept(), identifier));
        }
    }

    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create(): ConceptCoverageKey {
        return new ConceptCoverageKey(dsviper.ValueUUId.create());
    }

    static wrap(value: dsviper.Value): ConceptCoverageKey {
        return new ConceptCoverageKey(dsviper.ValueKey.cast(value));
    }

    static decode(blob: dsviper.ValueBlob): ConceptCoverageKey {
        return new ConceptCoverageKey(dsviper.ValueKey.cast(
            dsviper.Value.decode(blob, ConceptCoverageKey.type(), definitions())));
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
        return `${this.value.instanceId().encoded()}:Demo::ConceptCoverageKey`;
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
    static fromAnyConceptKey(key: AnyConceptKey | dsviper.ValueKey): ConceptCoverageKey | undefined {
        const value = key instanceof AnyConceptKey ? key.value : key;
        return value.typeConcept().runtimeId().equals(CONCEPT_COVERAGE)
            ? new ConceptCoverageKey(value) : undefined;
    }

    override toString(): string {
        return this.description();
    }
}

let concept_dConcept: dsviper.TypeConcept | undefined;
let concept_dType: dsviper.TypeKey | undefined;

/**
 * Une poignée sur une instance de Demo::ConceptD, pas la chose elle-même.
 */
export class ConceptDKey extends Proxy<dsviper.ValueKey> {
    static concept(): dsviper.TypeConcept {
        return (concept_dConcept ??= definitions().checkConcept(CONCEPT_D));
    }

    /**
     * Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin --
     * l'appelant écrit déjà le nom de la classe.
     */
    static type(): dsviper.TypeKey {
        return (concept_dType ??= new dsviper.TypeKey(ConceptDKey.concept()));
    }

    constructor(identifier?: dsviper.ValueKey | dsviper.ValueUUId) {
        if (identifier instanceof dsviper.ValueKey) {
            if (!identifier.type().equals(ConceptDKey.type())) {
                throw new TypeError("cette valeur n'est pas un Demo::ConceptDKey");
            }
            super(identifier);
        } else {
            super(dsviper.ValueKey.create(ConceptDKey.concept(), identifier));
        }
    }

    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create(): ConceptDKey {
        return new ConceptDKey(dsviper.ValueUUId.create());
    }

    static wrap(value: dsviper.Value): ConceptDKey {
        return new ConceptDKey(dsviper.ValueKey.cast(value));
    }

    static decode(blob: dsviper.ValueBlob): ConceptDKey {
        return new ConceptDKey(dsviper.ValueKey.cast(
            dsviper.Value.decode(blob, ConceptDKey.type(), definitions())));
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
        return `${this.value.instanceId().encoded()}:Demo::ConceptDKey`;
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
    static fromAnyConceptKey(key: AnyConceptKey | dsviper.ValueKey): ConceptDKey | undefined {
        const value = key instanceof AnyConceptKey ? key.value : key;
        return value.typeConcept().runtimeId().equals(CONCEPT_D)
            ? new ConceptDKey(value) : undefined;
    }

    override toString(): string {
        return this.description();
    }
}

let concept_cConcept: dsviper.TypeConcept | undefined;
let concept_cType: dsviper.TypeKey | undefined;

/**
 * Une poignée sur une instance de Demo::ConceptC, pas la chose elle-même.
 */
export class ConceptCKey extends Proxy<dsviper.ValueKey> {
    static concept(): dsviper.TypeConcept {
        return (concept_cConcept ??= definitions().checkConcept(CONCEPT_C));
    }

    /**
     * Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin --
     * l'appelant écrit déjà le nom de la classe.
     */
    static type(): dsviper.TypeKey {
        return (concept_cType ??= new dsviper.TypeKey(ConceptCKey.concept()));
    }

    constructor(identifier?: dsviper.ValueKey | dsviper.ValueUUId) {
        if (identifier instanceof dsviper.ValueKey) {
            if (!identifier.type().equals(ConceptCKey.type())) {
                throw new TypeError("cette valeur n'est pas un Demo::ConceptCKey");
            }
            super(identifier);
        } else {
            super(dsviper.ValueKey.create(ConceptCKey.concept(), identifier));
        }
    }

    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create(): ConceptCKey {
        return new ConceptCKey(dsviper.ValueUUId.create());
    }

    static wrap(value: dsviper.Value): ConceptCKey {
        return new ConceptCKey(dsviper.ValueKey.cast(value));
    }

    static decode(blob: dsviper.ValueBlob): ConceptCKey {
        return new ConceptCKey(dsviper.ValueKey.cast(
            dsviper.Value.decode(blob, ConceptCKey.type(), definitions())));
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
        return `${this.value.instanceId().encoded()}:Demo::ConceptCKey`;
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
    static fromAnyConceptKey(key: AnyConceptKey | dsviper.ValueKey): ConceptCKey | undefined {
        const value = key instanceof AnyConceptKey ? key.value : key;
        return value.typeConcept().runtimeId().equals(CONCEPT_C)
            ? new ConceptCKey(value) : undefined;
    }

    override toString(): string {
        return this.description();
    }
}

let empty_klubClub: dsviper.TypeClub | undefined;
let empty_klubType: dsviper.TypeKey | undefined;

/** Une poignée sur une instance d'un membre de Demo::EmptyKlub. */
export class EmptyKlubKey extends Proxy<dsviper.ValueKey> {
    static club(): dsviper.TypeClub {
        return (empty_klubClub ??= definitions().checkClub(EMPTY_KLUB));
    }

    static type(): dsviper.TypeKey {
        return (empty_klubType ??= new dsviper.TypeKey(EmptyKlubKey.club()));
    }

    constructor(key: Proxy<dsviper.ValueKey> | dsviper.ValueKey) {
        const value = key instanceof Proxy ? key.value : key;
        if (!EmptyKlubKey.club().isMember(value.typeConcept())) {
            throw new TypeError("cette clé ne désigne pas un membre de Demo::EmptyKlub");
        }
        super(value.toClubKey(EmptyKlubKey.club()));
    }

    static wrap(value: dsviper.Value): EmptyKlubKey {
        return new EmptyKlubKey(dsviper.ValueKey.cast(value));
    }

    static decode(blob: dsviper.ValueBlob): EmptyKlubKey {
        return new EmptyKlubKey(dsviper.ValueKey.cast(
            dsviper.Value.decode(blob, EmptyKlubKey.type(), definitions())));
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
        return `${this.value.instanceId().encoded()}:Demo::EmptyKlubKey`;
    }

    isKnown(): boolean {
        return isKnown(this.value);
    }

    /** La clé vue comme celle d'un membre, ou `undefined` si l'instance n'en est pas un. */
    as<K>(member: { concept(): dsviper.TypeConcept; wrap(value: dsviper.Value): K }): K | undefined {
        const concept = member.concept();
        return this.value.isMember(concept) ? member.wrap(this.value.toMemberKey(concept)) : undefined;
    }

    override toString(): string {
        return this.description();
    }
}

let klubClub: dsviper.TypeClub | undefined;
let klubType: dsviper.TypeKey | undefined;

/** Une poignée sur une instance d'un membre de Demo::Klub. */
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
            throw new TypeError("cette clé ne désigne pas un membre de Demo::Klub");
        }
        super(value.toClubKey(KlubKey.club()));
    }

    static wrap(value: dsviper.Value): KlubKey {
        return new KlubKey(dsviper.ValueKey.cast(value));
    }

    static decode(blob: dsviper.ValueBlob): KlubKey {
        return new KlubKey(dsviper.ValueKey.cast(
            dsviper.Value.decode(blob, KlubKey.type(), definitions())));
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
        return `${this.value.instanceId().encoded()}:Demo::KlubKey`;
    }

    isKnown(): boolean {
        return isKnown(this.value);
    }

    /** La clé vue comme celle d'un membre, ou `undefined` si l'instance n'en est pas un. */
    as<K>(member: { concept(): dsviper.TypeConcept; wrap(value: dsviper.Value): K }): K | undefined {
        const concept = member.concept();
        return this.value.isMember(concept) ? member.wrap(this.value.toMemberKey(concept)) : undefined;
    }

    override toString(): string {
        return this.description();
    }
}

let enumeration_eType: dsviper.TypeEnumeration | undefined;

/** Demo::EnumerationE. This is the documentation for enumeration E */
export type EnumerationE = "a" | "b" | "c";

/**
 * UN TYPE ET UNE VALEUR SOUS LE MÊME NOM, ce que TypeScript permet et qui dit exactement ce
 * qu'on veut : `EnumerationE` annote, `EnumerationE.a` désigne, `EnumerationE.wrap` convertit. Le pack en
 * fait une classe qui enveloppe une `ValueEnumeration` ; une union de littéraux se vérifie
 * mieux et ne coûte aucun objet.
 */
export const EnumerationE = {
    A: "a",
    B: "b",
    C: "c",

    type(): dsviper.TypeEnumeration {
        return (enumeration_eType ??= definitions().checkEnumeration(ENUMERATION_E));
    },

    wrap(value: dsviper.Value): EnumerationE {
        return dsviper.ValueEnumeration.cast(value).name() as EnumerationE;
    },

    /** Depuis le nom d'un cas, et depuis rien d'autre. */
    fromStr(name: string): EnumerationE {
        if (typeof name !== "string") {
            throw new TypeError(`${name} n'est pas un nom de cas`);
        }
        return EnumerationE.wrap(new dsviper.ValueEnumeration(EnumerationE.type(), name));
    },

    /** Le nom d'un cas — qui *est* le cas, puisqu'un littéral porte son propre nom. */
    name(held: EnumerationE): string {
        return held;
    },

    /** Le rang d'un cas, tel que le modèle les numérote. */
    index(held: EnumerationE): number {
        return EnumerationE.type().cases().findIndex((c) => c.name() === held);
    },

    /** La valeur du runtime derrière un cas — ce qui porte l'encodage et l'empreinte. */
    value(held: EnumerationE): dsviper.ValueEnumeration {
        return new dsviper.ValueEnumeration(EnumerationE.type(), held);
    },

    encode(held: EnumerationE): dsviper.ValueBlob {
        return dsviper.Value.encode(EnumerationE.value(held));
    },

    decode(blob: dsviper.ValueBlob): EnumerationE {
        return EnumerationE.wrap(dsviper.Value.decode(blob, EnumerationE.type(), definitions()));
    },

    hexdigest(held: EnumerationE): string {
        return dsviper.Value.hexdigest(EnumerationE.value(held));
    },
};

let structure_sType: dsviper.TypeStructure | undefined;

/** Demo::StructureS. This is the documentation for the struct S */
export class StructureS extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure {
        return (structure_sType ??= definitions().checkStructure(STRUCTURE_S));
    }

    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(StructureS.type())) {
                throw new TypeError("cette valeur n'est pas un Demo::StructureS");
            }
            super(value);
        } else {
            super(new dsviper.ValueStructure(StructureS.type(), value));
        }
    }

    static wrap(value: dsviper.Value): StructureS {
        return new StructureS(dsviper.ValueStructure.cast(value));
    }

    static decode(blob: dsviper.ValueBlob): StructureS {
        return new StructureS(dsviper.ValueStructure.cast(
            dsviper.Value.decode(blob, StructureS.type(), definitions())));
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
}

let structure_wType: dsviper.TypeStructure | undefined;

/** Demo::StructureW. */
export class StructureW extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure {
        return (structure_wType ??= definitions().checkStructure(STRUCTURE_W));
    }

    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(StructureW.type())) {
                throw new TypeError("cette valeur n'est pas un Demo::StructureW");
            }
            super(value);
        } else {
            super(new dsviper.ValueStructure(StructureW.type(), value));
        }
    }

    static wrap(value: dsviper.Value): StructureW {
        return new StructureW(dsviper.ValueStructure.cast(value));
    }

    static decode(blob: dsviper.ValueBlob): StructureW {
        return new StructureW(dsviper.ValueStructure.cast(
            dsviper.Value.decode(blob, StructureW.type(), definitions())));
    }

    get f_single(): number {
        return this.value.at("f_single") as number;
    }

    set f_single(value: number) {
        setField(this.value, "f_single", value);
    }
}

let structure_tType: dsviper.TypeStructure | undefined;

/** Demo::StructureT. */
export class StructureT extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure {
        return (structure_tType ??= definitions().checkStructure(STRUCTURE_T));
    }

    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(StructureT.type())) {
                throw new TypeError("cette valeur n'est pas un Demo::StructureT");
            }
            super(value);
        } else {
            super(new dsviper.ValueStructure(StructureT.type(), value));
        }
    }

    static wrap(value: dsviper.Value): StructureT {
        return new StructureT(dsviper.ValueStructure.cast(value));
    }

    static decode(blob: dsviper.ValueBlob): StructureT {
        return new StructureT(dsviper.ValueStructure.cast(
            dsviper.Value.decode(blob, StructureT.type(), definitions())));
    }

    get field_string(): string {
        return this.value.at("field_string") as string;
    }

    set field_string(value: string) {
        setField(this.value, "field_string", value);
    }

    get field_structure_s(): StructureS {
        return wrap(this.value.at("field_structure_s", false));
    }

    set field_structure_s(value: StructureS) {
        setField(this.value, "field_structure_s", value);
    }
}

let structure_vType: dsviper.TypeStructure | undefined;

/** Demo::StructureV. */
export class StructureV extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure {
        return (structure_vType ??= definitions().checkStructure(STRUCTURE_V));
    }

    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(StructureV.type())) {
                throw new TypeError("cette valeur n'est pas un Demo::StructureV");
            }
            super(value);
        } else {
            super(new dsviper.ValueStructure(StructureV.type(), value));
        }
    }

    static wrap(value: dsviper.Value): StructureV {
        return new StructureV(dsviper.ValueStructure.cast(value));
    }

    static decode(blob: dsviper.ValueBlob): StructureV {
        return new StructureV(dsviper.ValueStructure.cast(
            dsviper.Value.decode(blob, StructureV.type(), definitions())));
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

    get f_tuple(): Sequence<number | string> {
        return wrap(this.value.at("f_tuple", false));
    }

    set f_tuple(value: Sequence<number | string>) {
        setField(this.value, "f_tuple", value);
    }

    get f_optional(): number | undefined {
        return wrap(this.value.at("f_optional", false));
    }

    set f_optional(value: number | undefined) {
        setField(this.value, "f_optional", value);
    }

    get f_vector(): Sequence<number> {
        return wrap(this.value.at("f_vector", false));
    }

    set f_vector(value: Sequence<number>) {
        setField(this.value, "f_vector", value);
    }

    get f_set(): Sequence<number> {
        return wrap(this.value.at("f_set", false));
    }

    set f_set(value: Sequence<number>) {
        setField(this.value, "f_set", value);
    }

    get f_map(): Mapping<number, string> {
        return wrap(this.value.at("f_map", false));
    }

    set f_map(value: Mapping<number, string>) {
        setField(this.value, "f_map", value);
    }

    get f_E(): EnumerationE {
        return wrap(this.value.at("f_E", false));
    }

    set f_E(value: EnumerationE) {
        setField(this.value, "f_E", value);
    }

    get f_S(): StructureS {
        return wrap(this.value.at("f_S", false));
    }

    set f_S(value: StructureS) {
        setField(this.value, "f_S", value);
    }

    get f_T(): StructureT {
        return wrap(this.value.at("f_T", false));
    }

    set f_T(value: StructureT) {
        setField(this.value, "f_T", value);
    }
}

let structure_uType: dsviper.TypeStructure | undefined;

/** Demo::StructureU. */
export class StructureU extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure {
        return (structure_uType ??= definitions().checkStructure(STRUCTURE_U));
    }

    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(StructureU.type())) {
                throw new TypeError("cette valeur n'est pas un Demo::StructureU");
            }
            super(value);
        } else {
            super(new dsviper.ValueStructure(StructureU.type(), value));
        }
    }

    static wrap(value: dsviper.Value): StructureU {
        return new StructureU(dsviper.ValueStructure.cast(value));
    }

    static decode(blob: dsviper.ValueBlob): StructureU {
        return new StructureU(dsviper.ValueStructure.cast(
            dsviper.Value.decode(blob, StructureU.type(), definitions())));
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

    get f_tuple(): Sequence<number | string> {
        return wrap(this.value.at("f_tuple", false));
    }

    set f_tuple(value: Sequence<number | string>) {
        setField(this.value, "f_tuple", value);
    }

    get f_optional(): number | undefined {
        return wrap(this.value.at("f_optional", false));
    }

    set f_optional(value: number | undefined) {
        setField(this.value, "f_optional", value);
    }

    get f_vector(): Sequence<number> {
        return wrap(this.value.at("f_vector", false));
    }

    set f_vector(value: Sequence<number>) {
        setField(this.value, "f_vector", value);
    }

    get f_set(): Sequence<number> {
        return wrap(this.value.at("f_set", false));
    }

    set f_set(value: Sequence<number>) {
        setField(this.value, "f_set", value);
    }

    get f_set_s(): Sequence<StructureS> {
        return wrap(this.value.at("f_set_s", false));
    }

    set f_set_s(value: Sequence<StructureS>) {
        setField(this.value, "f_set_s", value);
    }

    get f_map_s1(): Mapping<StructureS, string> {
        return wrap(this.value.at("f_map_s1", false));
    }

    set f_map_s1(value: Mapping<StructureS, string>) {
        setField(this.value, "f_map_s1", value);
    }

    get f_map_s2(): Mapping<string, StructureS> {
        return wrap(this.value.at("f_map_s2", false));
    }

    set f_map_s2(value: Mapping<string, StructureS>) {
        setField(this.value, "f_map_s2", value);
    }

    get f_xarray(): Ordered<number> {
        return wrap(this.value.at("f_xarray", false));
    }

    set f_xarray(value: Ordered<number>) {
        setField(this.value, "f_xarray", value);
    }

    get f_xarray_s(): Ordered<StructureS> {
        return wrap(this.value.at("f_xarray_s", false));
    }

    set f_xarray_s(value: Ordered<StructureS>) {
        setField(this.value, "f_xarray_s", value);
    }

    get f_map_vs(): Mapping<Sequence<StructureS>, string> {
        return wrap(this.value.at("f_map_vs", false));
    }

    set f_map_vs(value: Mapping<Sequence<StructureS>, string>) {
        setField(this.value, "f_map_vs", value);
    }

    get f_variant(): string | number | StructureS {
        return wrap(this.value.at("f_variant", false));
    }

    set f_variant(value: string | number | StructureS) {
        setField(this.value, "f_variant", value);
    }

    get f_any(): unknown {
        return this.value.at("f_any") as unknown;
    }

    set f_any(value: unknown) {
        setField(this.value, "f_any", value);
    }

    get f_E(): EnumerationE {
        return wrap(this.value.at("f_E", false));
    }

    set f_E(value: EnumerationE) {
        setField(this.value, "f_E", value);
    }

    get f_S(): StructureS {
        return wrap(this.value.at("f_S", false));
    }

    set f_S(value: StructureS) {
        setField(this.value, "f_S", value);
    }

    get f_T(): StructureT {
        return wrap(this.value.at("f_T", false));
    }

    set f_T(value: StructureT) {
        setField(this.value, "f_T", value);
    }

    get f_A(): ConceptAKey {
        return wrap(this.value.at("f_A", false));
    }

    set f_A(value: ConceptAKey) {
        setField(this.value, "f_A", value);
    }

    get f_B(): ConceptBKey {
        return wrap(this.value.at("f_B", false));
    }

    set f_B(value: ConceptBKey) {
        setField(this.value, "f_B", value);
    }

    get f_C(): ConceptCKey {
        return wrap(this.value.at("f_C", false));
    }

    set f_C(value: ConceptCKey) {
        setField(this.value, "f_C", value);
    }

    get f_D(): ConceptDKey {
        return wrap(this.value.at("f_D", false));
    }

    set f_D(value: ConceptDKey) {
        setField(this.value, "f_D", value);
    }

    get f_Klub(): KlubKey {
        return wrap(this.value.at("f_Klub", false));
    }

    set f_Klub(value: KlubKey) {
        setField(this.value, "f_Klub", value);
    }

    get f_any_concept(): AnyConceptKey {
        return wrap(this.value.at("f_any_concept", false));
    }

    set f_any_concept(value: AnyConceptKey) {
        setField(this.value, "f_any_concept", value);
    }
}

// Les classes de cette unité, par l'identifiant d'exécution de leur type : c'est ce qui permet
// à `wrap` de rendre un élément de conteneur, ou un document d'attachment, avec son nom.
register([CONCEPT_A, ConceptAKey], [CONCEPT_B, ConceptBKey], [CONCEPT_COVERAGE, ConceptCoverageKey], [CONCEPT_D, ConceptDKey], [CONCEPT_C, ConceptCKey], [EMPTY_KLUB, EmptyKlubKey], [KLUB, KlubKey], [ENUMERATION_E, EnumerationE], [STRUCTURE_S, StructureS], [STRUCTURE_T, StructureT], [STRUCTURE_U, StructureU], [STRUCTURE_V, StructureV], [STRUCTURE_W, StructureW]);