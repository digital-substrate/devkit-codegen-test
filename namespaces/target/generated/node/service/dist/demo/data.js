// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/service/Service.dsm.json by kibo-2.0.0.jar
/** Demo — les types que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";
import { Proxy } from "../_codegen/proxy.js";
import { AnyConceptKey, isKnown, register, setField, wrap } from "../_codegen/registry.js";
import { definitions } from "../index.js";
// ── l'identité de cette unité dans le modèle ──
//
// LE MÊME ARTEFACT QU'EN C++ ET EN PYTHON, POUR LA MÊME RAISON : plusieurs couches en ont
// besoin et ce n'est pas de la sérialisation.
export const PLAYER = dsviper.ValueUUId.create("c177a251-4de8-57a0-de3b-6cc2ae68eb13");
export const LEVEL = dsviper.ValueUUId.create("238d8f84-734d-df83-fc48-f4dc69cc127a");
export const PLAYER_PROPERTY = dsviper.ValueUUId.create("2fa5978a-9426-26a5-e8e7-35c80ce00ffd");
export const VECTOR_3 = dsviper.ValueUUId.create("9099c892-b971-86b4-6d84-ab38cc2d3d16");
let playerConcept;
let playerType;
/**
 * Une poignée sur une instance de Demo::Player, pas la chose elle-même.
 */
export class PlayerKey extends Proxy {
    static concept() {
        return (playerConcept ??= definitions().checkConcept(PLAYER));
    }
    /**
     * Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin --
     * l'appelant écrit déjà le nom de la classe.
     */
    static type() {
        return (playerType ??= new dsviper.TypeKey(PlayerKey.concept()));
    }
    constructor(identifier) {
        if (identifier === null) {
            // `null` EXPLICITE N'EST PAS L'ABSENCE D'ARGUMENT. `new XKey()` demande une clé
            // neuve ; `new XKey(null)` passe quelque chose, et ce quelque chose n'en est pas un.
            throw new TypeError("null n'est pas un identifiant d'instance");
        }
        if (identifier instanceof dsviper.ValueKey) {
            if (!identifier.isMember(PlayerKey.concept())) {
                throw new TypeError("cette valeur n'est pas un Demo::PlayerKey");
            }
            super(identifier);
        }
        else {
            super(dsviper.ValueKey.create(PlayerKey.concept(), identifier));
        }
    }
    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create() {
        return new PlayerKey(dsviper.ValueUUId.create());
    }
    static wrap(value) {
        return new PlayerKey(dsviper.ValueKey.cast(value));
    }
    static decode(blob) {
        return new PlayerKey(dsviper.ValueKey.cast(dsviper.Value.decode(blob, PlayerKey.type(), definitions())));
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
        return `${this.value.instanceId().encoded()}:Demo::PlayerKey`;
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
        return value.typeConcept().runtimeId().equals(PLAYER)
            ? new PlayerKey(value) : undefined;
    }
    toString() {
        return this.description();
    }
}
let levelType;
/**
 * UN TYPE ET UNE VALEUR SOUS LE MÊME NOM, ce que TypeScript permet et qui dit exactement ce
 * qu'on veut : `Level` annote, `Level.beginner` désigne, `Level.wrap` convertit. Le pack en
 * fait une classe qui enveloppe une `ValueEnumeration` ; une union de littéraux se vérifie
 * mieux et ne coûte aucun objet.
 */
export const Level = {
    BEGINNER: "beginner",
    INTERMEDIATE: "intermediate",
    EXPERT: "expert",
    type() {
        return (levelType ??= definitions().checkEnumeration(LEVEL));
    },
    wrap(value) {
        return dsviper.ValueEnumeration.cast(value).name();
    },
    /** Depuis le nom d'un cas, et depuis rien d'autre. */
    fromStr(name) {
        if (typeof name !== "string") {
            throw new TypeError(`${name} n'est pas un nom de cas`);
        }
        return Level.wrap(new dsviper.ValueEnumeration(Level.type(), name));
    },
    /** Le nom d'un cas — qui *est* le cas, puisqu'un littéral porte son propre nom. */
    name(held) {
        return held;
    },
    /** Le rang d'un cas, tel que le modèle les numérote. */
    index(held) {
        return Level.type().cases().findIndex((c) => c.name() === held);
    },
    /** La valeur du runtime derrière un cas — ce qui porte l'encodage et l'empreinte. */
    value(held) {
        return new dsviper.ValueEnumeration(Level.type(), held);
    },
    encode(held) {
        return dsviper.Value.encode(Level.value(held));
    },
    decode(blob) {
        return Level.wrap(dsviper.Value.decode(blob, Level.type(), definitions()));
    },
    hexdigest(held) {
        return dsviper.Value.hexdigest(Level.value(held));
    },
};
let player_propertyType;
/** Demo::PlayerProperty. */
export class PlayerProperty extends Proxy {
    static type() {
        return (player_propertyType ??= definitions().checkStructure(PLAYER_PROPERTY));
    }
    constructor(value) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(PlayerProperty.type())) {
                throw new TypeError("cette valeur n'est pas un Demo::PlayerProperty");
            }
            super(value);
        }
        else {
            super(new dsviper.ValueStructure(PlayerProperty.type(), value));
        }
    }
    static wrap(value) {
        return new PlayerProperty(dsviper.ValueStructure.cast(value));
    }
    static decode(blob) {
        return new PlayerProperty(dsviper.ValueStructure.cast(dsviper.Value.decode(blob, PlayerProperty.type(), definitions())));
    }
    get nickname() {
        return this.value.at("nickname");
    }
    set nickname(value) {
        setField(this.value, "nickname", value);
    }
    get level() {
        return wrap(this.value.at("level", false));
    }
    set level(value) {
        setField(this.value, "level", value);
    }
}
let vector_3Type;
/** Demo::Vector3. */
export class Vector3 extends Proxy {
    static type() {
        return (vector_3Type ??= definitions().checkStructure(VECTOR_3));
    }
    constructor(value) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(Vector3.type())) {
                throw new TypeError("cette valeur n'est pas un Demo::Vector3");
            }
            super(value);
        }
        else {
            super(new dsviper.ValueStructure(Vector3.type(), value));
        }
    }
    static wrap(value) {
        return new Vector3(dsviper.ValueStructure.cast(value));
    }
    static decode(blob) {
        return new Vector3(dsviper.ValueStructure.cast(dsviper.Value.decode(blob, Vector3.type(), definitions())));
    }
    get x() {
        return this.value.at("x");
    }
    set x(value) {
        setField(this.value, "x", value);
    }
    get y() {
        return this.value.at("y");
    }
    set y(value) {
        setField(this.value, "y", value);
    }
    get z() {
        return this.value.at("z");
    }
    set z(value) {
        setField(this.value, "z", value);
    }
}
// Les classes de cette unité, par l'identifiant d'exécution de leur type : c'est ce qui permet
// à `wrap` de rendre un élément de conteneur, ou un document d'attachment, avec son nom.
register([PLAYER, PlayerKey], [LEVEL, Level], [PLAYER_PROPERTY, PlayerProperty], [VECTOR_3, Vector3]);
