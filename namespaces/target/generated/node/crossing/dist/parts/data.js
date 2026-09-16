// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar
/** Parts — les types que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";
import { Proxy } from "../_codegen/proxy.js";
import { AnyConceptKey, isKnown, register, setField } from "../_codegen/registry.js";
import { definitions } from "../index.js";
// ── l'identité de cette unité dans le modèle ──
//
// LE MÊME ARTEFACT QU'EN C++ ET EN PYTHON, POUR LA MÊME RAISON : plusieurs couches en ont
// besoin et ce n'est pas de la sérialisation.
export const THING = dsviper.ValueUUId.create("12f4a98d-d084-f535-db87-e58f8757a553");
export const GRADE = dsviper.ValueUUId.create("b377e61b-49b9-6e92-5ccf-ea47d5bbfb30");
export const COLOUR = dsviper.ValueUUId.create("08261ca9-72d6-3df5-6608-c88279d35a48");
let thingConcept;
let thingType;
/**
 * Une poignée sur une instance de Parts::Thing, pas la chose elle-même.
 *
 * Le même nom que Core::Thing, et rien de commun.
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
                throw new TypeError("cette valeur n'est pas un Parts::ThingKey");
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
    static decode(blob) {
        return new ThingKey(dsviper.ValueKey.cast(dsviper.Value.decode(blob, ThingKey.type(), definitions())));
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
        return `${this.value.instanceId().encoded()}:Parts::ThingKey`;
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
        return value.typeConcept().runtimeId().equals(THING)
            ? new ThingKey(value) : undefined;
    }
    toString() {
        return this.description();
    }
}
let gradeType;
/**
 * UN TYPE ET UNE VALEUR SOUS LE MÊME NOM, ce que TypeScript permet et qui dit exactement ce
 * qu'on veut : `Grade` annote, `Grade.soft` désigne, `Grade.wrap` convertit. Le pack en
 * fait une classe qui enveloppe une `ValueEnumeration` ; une union de littéraux se vérifie
 * mieux et ne coûte aucun objet.
 */
export const Grade = {
    SOFT: "soft",
    HARD: "hard",
    type() {
        return (gradeType ??= definitions().checkEnumeration(GRADE));
    },
    wrap(value) {
        return dsviper.ValueEnumeration.cast(value).name();
    },
    /** Depuis le nom d'un cas, et depuis rien d'autre. */
    fromStr(name) {
        if (typeof name !== "string") {
            throw new TypeError(`${name} n'est pas un nom de cas`);
        }
        return Grade.wrap(new dsviper.ValueEnumeration(Grade.type(), name));
    },
    /** Le nom d'un cas — qui *est* le cas, puisqu'un littéral porte son propre nom. */
    name(held) {
        return held;
    },
    /** Le rang d'un cas, tel que le modèle les numérote. */
    index(held) {
        return Grade.type().cases().findIndex((c) => c.name() === held);
    },
    /** La valeur du runtime derrière un cas — ce qui porte l'encodage et l'empreinte. */
    value(held) {
        return new dsviper.ValueEnumeration(Grade.type(), held);
    },
    encode(held) {
        return dsviper.Value.encode(Grade.value(held));
    },
    decode(blob) {
        return Grade.wrap(dsviper.Value.decode(blob, Grade.type(), definitions()));
    },
    hexdigest(held) {
        return dsviper.Value.hexdigest(Grade.value(held));
    },
};
let colourType;
/** Parts::Colour. Le même nom que Core::Colour, en virgule flottante. */
export class Colour extends Proxy {
    static type() {
        return (colourType ??= definitions().checkStructure(COLOUR));
    }
    constructor(value) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(Colour.type())) {
                throw new TypeError("cette valeur n'est pas un Parts::Colour");
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
    static decode(blob) {
        return new Colour(dsviper.ValueStructure.cast(dsviper.Value.decode(blob, Colour.type(), definitions())));
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
// Les classes de cette unité, par l'identifiant d'exécution de leur type : c'est ce qui permet
// à `wrap` de rendre un élément de conteneur, ou un document d'attachment, avec son nom.
register([THING, ThingKey], [GRADE, Grade], [COLOUR, Colour]);
