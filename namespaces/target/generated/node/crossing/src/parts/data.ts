// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

/** Parts — les types que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";

import { Mapping, Ordered, Sequence } from "../_codegen/container.js";
import { Proxy } from "../_codegen/proxy.js";
import { AnyConceptKey, isKnown, register, setField, wrap } from "../_codegen/registry.js";
import { definitions } from "../index.js";

// ── l'identité de cette unité dans le modèle ──
//
// LE MÊME ARTEFACT QU'EN C++ ET EN PYTHON, POUR LA MÊME RAISON : plusieurs couches en ont
// besoin et ce n'est pas de la sérialisation.

export const THING = dsviper.ValueUUId.create("12f4a98d-d084-f535-db87-e58f8757a553");
export const GRADE = dsviper.ValueUUId.create("b377e61b-49b9-6e92-5ccf-ea47d5bbfb30");
export const COLOUR = dsviper.ValueUUId.create("08261ca9-72d6-3df5-6608-c88279d35a48");

let thingConcept: dsviper.TypeConcept | undefined;
let thingType: dsviper.TypeKey | undefined;

/**
 * Une poignée sur une instance de Parts::Thing, pas la chose elle-même.
 *
 * Le même nom que Core::Thing, et rien de commun.
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

    constructor(identifier?: dsviper.ValueKey | dsviper.ValueUUId | null) {
        if (identifier === null) {
            // `null` EXPLICITE N'EST PAS L'ABSENCE D'ARGUMENT. `new XKey()` demande une clé
            // neuve ; `new XKey(null)` passe quelque chose, et ce quelque chose n'en est pas un.
            throw new TypeError("null n'est pas un identifiant d'instance");
        }
        if (identifier instanceof dsviper.ValueKey) {
            if (!identifier.isMember(ThingKey.concept())) {
                throw new TypeError("cette valeur n'est pas un Parts::ThingKey");
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

    static decode(blob: dsviper.ValueBlob): ThingKey {
        return new ThingKey(dsviper.ValueKey.cast(
            dsviper.Value.decode(blob, ThingKey.type(), definitions())));
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
    compareTo(other: ThingKey | dsviper.ValueKey): number {
        return this.value.compare(other instanceof Proxy ? other.value : other);
    }

    /** L'instance et son type, dits comme le modèle les nomme. */
    description(): string {
        return `${this.value.instanceId().encoded()}:Parts::ThingKey`;
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
    static fromAnyConceptKey(key: AnyConceptKey | dsviper.ValueKey): ThingKey | undefined {
        const value = key instanceof AnyConceptKey ? key.value : key;
        return value.typeConcept().runtimeId().equals(THING)
            ? new ThingKey(value) : undefined;
    }

    override toString(): string {
        return this.description();
    }
}

let gradeType: dsviper.TypeEnumeration | undefined;

/** Parts::Grade. Le même nom que Core::Grade, des cases différentes. */
export type Grade = "soft" | "hard";

/**
 * UN TYPE ET UNE VALEUR SOUS LE MÊME NOM, ce que TypeScript permet et qui dit exactement ce
 * qu'on veut : `Grade` annote, `Grade.soft` désigne, `Grade.wrap` convertit. Le pack en
 * fait une classe qui enveloppe une `ValueEnumeration` ; une union de littéraux se vérifie
 * mieux et ne coûte aucun objet.
 */
export const Grade = {
    SOFT: "soft",
    HARD: "hard",

    type(): dsviper.TypeEnumeration {
        return (gradeType ??= definitions().checkEnumeration(GRADE));
    },

    wrap(value: dsviper.Value): Grade {
        return dsviper.ValueEnumeration.cast(value).name() as Grade;
    },

    /** Depuis le nom d'un cas, et depuis rien d'autre. */
    fromStr(name: string): Grade {
        if (typeof name !== "string") {
            throw new TypeError(`${name} n'est pas un nom de cas`);
        }
        return Grade.wrap(new dsviper.ValueEnumeration(Grade.type(), name));
    },

    /** Le nom d'un cas — qui *est* le cas, puisqu'un littéral porte son propre nom. */
    name(held: Grade): string {
        return held;
    },

    /** Le rang d'un cas, tel que le modèle les numérote. */
    index(held: Grade): number {
        return Grade.type().cases().findIndex((c) => c.name() === held);
    },

    /** La valeur du runtime derrière un cas — ce qui porte l'encodage et l'empreinte. */
    value(held: Grade): dsviper.ValueEnumeration {
        return new dsviper.ValueEnumeration(Grade.type(), held);
    },

    encode(held: Grade): dsviper.ValueBlob {
        return dsviper.Value.encode(Grade.value(held));
    },

    decode(blob: dsviper.ValueBlob): Grade {
        return Grade.wrap(dsviper.Value.decode(blob, Grade.type(), definitions()));
    },

    hexdigest(held: Grade): string {
        return dsviper.Value.hexdigest(Grade.value(held));
    },
};

let colourType: dsviper.TypeStructure | undefined;

/** Parts::Colour. Le même nom que Core::Colour, en virgule flottante. */
export class Colour extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure {
        return (colourType ??= definitions().checkStructure(COLOUR));
    }

    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(Colour.type())) {
                throw new TypeError("cette valeur n'est pas un Parts::Colour");
            }
            super(value);
        } else {
            super(new dsviper.ValueStructure(Colour.type(), value));
        }
    }

    static wrap(value: dsviper.Value): Colour {
        return new Colour(dsviper.ValueStructure.cast(value));
    }

    static decode(blob: dsviper.ValueBlob): Colour {
        return new Colour(dsviper.ValueStructure.cast(
            dsviper.Value.decode(blob, Colour.type(), definitions())));
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

// Les classes de cette unité, par l'identifiant d'exécution de leur type : c'est ce qui permet
// à `wrap` de rendre un élément de conteneur, ou un document d'attachment, avec son nom.
register([THING, ThingKey], [GRADE, Grade], [COLOUR, Colour]);