// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/service/Service.dsm.json by kibo-2.0.0.jar

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

export const PLAYER = dsviper.ValueUUId.create("c177a251-4de8-57a0-de3b-6cc2ae68eb13");
export const LEVEL = dsviper.ValueUUId.create("238d8f84-734d-df83-fc48-f4dc69cc127a");
export const PLAYER_PROPERTY = dsviper.ValueUUId.create("2fa5978a-9426-26a5-e8e7-35c80ce00ffd");
export const VECTOR_3 = dsviper.ValueUUId.create("9099c892-b971-86b4-6d84-ab38cc2d3d16");

let playerConcept: dsviper.TypeConcept | undefined;
let playerType: dsviper.TypeKey | undefined;

/**
 * Une poignée sur une instance de Demo::Player, pas la chose elle-même.
 */
export class PlayerKey extends Proxy<dsviper.ValueKey> {
    static concept(): dsviper.TypeConcept {
        return (playerConcept ??= definitions().checkConcept(PLAYER));
    }

    /**
     * Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin --
     * l'appelant écrit déjà le nom de la classe.
     */
    static type(): dsviper.TypeKey {
        return (playerType ??= new dsviper.TypeKey(PlayerKey.concept()));
    }

    constructor(identifier?: dsviper.ValueKey | dsviper.ValueUUId | null) {
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
        } else {
            super(dsviper.ValueKey.create(PlayerKey.concept(), identifier));
        }
    }

    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create(): PlayerKey {
        return new PlayerKey(dsviper.ValueUUId.create());
    }

    static wrap(value: dsviper.Value): PlayerKey {
        return new PlayerKey(dsviper.ValueKey.cast(value));
    }

    static decode(blob: dsviper.ValueBlob): PlayerKey {
        return new PlayerKey(dsviper.ValueKey.cast(
            dsviper.Value.decode(blob, PlayerKey.type(), definitions())));
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
    compareTo(other: PlayerKey | dsviper.ValueKey): number {
        return this.value.compare(other instanceof Proxy ? other.value : other);
    }

    /** L'instance et son type, dits comme le modèle les nomme. */
    description(): string {
        return `${this.value.instanceId().encoded()}:Demo::PlayerKey`;
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
    static fromAnyConceptKey(key: AnyConceptKey | dsviper.ValueKey): PlayerKey | undefined {
        const value = key instanceof AnyConceptKey ? key.value : key;
        return value.typeConcept().runtimeId().equals(PLAYER)
            ? new PlayerKey(value) : undefined;
    }

    override toString(): string {
        return this.description();
    }
}

let levelType: dsviper.TypeEnumeration | undefined;

/** Demo::Level. */
export type Level = "beginner" | "intermediate" | "expert";

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

    type(): dsviper.TypeEnumeration {
        return (levelType ??= definitions().checkEnumeration(LEVEL));
    },

    wrap(value: dsviper.Value): Level {
        return dsviper.ValueEnumeration.cast(value).name() as Level;
    },

    /** Depuis le nom d'un cas, et depuis rien d'autre. */
    fromStr(name: string): Level {
        if (typeof name !== "string") {
            throw new TypeError(`${name} n'est pas un nom de cas`);
        }
        return Level.wrap(new dsviper.ValueEnumeration(Level.type(), name));
    },

    /** Le nom d'un cas — qui *est* le cas, puisqu'un littéral porte son propre nom. */
    name(held: Level): string {
        return held;
    },

    /** Le rang d'un cas, tel que le modèle les numérote. */
    index(held: Level): number {
        return Level.type().cases().findIndex((c) => c.name() === held);
    },

    /** La valeur du runtime derrière un cas — ce qui porte l'encodage et l'empreinte. */
    value(held: Level): dsviper.ValueEnumeration {
        return new dsviper.ValueEnumeration(Level.type(), held);
    },

    encode(held: Level): dsviper.ValueBlob {
        return dsviper.Value.encode(Level.value(held));
    },

    decode(blob: dsviper.ValueBlob): Level {
        return Level.wrap(dsviper.Value.decode(blob, Level.type(), definitions()));
    },

    hexdigest(held: Level): string {
        return dsviper.Value.hexdigest(Level.value(held));
    },
};

let player_propertyType: dsviper.TypeStructure | undefined;

/** Demo::PlayerProperty. */
export class PlayerProperty extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure {
        return (player_propertyType ??= definitions().checkStructure(PLAYER_PROPERTY));
    }

    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(PlayerProperty.type())) {
                throw new TypeError("cette valeur n'est pas un Demo::PlayerProperty");
            }
            super(value);
        } else {
            super(new dsviper.ValueStructure(PlayerProperty.type(), value));
        }
    }

    static wrap(value: dsviper.Value): PlayerProperty {
        return new PlayerProperty(dsviper.ValueStructure.cast(value));
    }

    static decode(blob: dsviper.ValueBlob): PlayerProperty {
        return new PlayerProperty(dsviper.ValueStructure.cast(
            dsviper.Value.decode(blob, PlayerProperty.type(), definitions())));
    }

    get nickname(): string {
        return this.value.at("nickname") as string;
    }

    set nickname(value: string) {
        setField(this.value, "nickname", value);
    }

    get level(): Level {
        return wrap(this.value.at("level", false));
    }

    set level(value: Level) {
        setField(this.value, "level", value);
    }
}

let vector_3Type: dsviper.TypeStructure | undefined;

/** Demo::Vector3. */
export class Vector3 extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure {
        return (vector_3Type ??= definitions().checkStructure(VECTOR_3));
    }

    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(Vector3.type())) {
                throw new TypeError("cette valeur n'est pas un Demo::Vector3");
            }
            super(value);
        } else {
            super(new dsviper.ValueStructure(Vector3.type(), value));
        }
    }

    static wrap(value: dsviper.Value): Vector3 {
        return new Vector3(dsviper.ValueStructure.cast(value));
    }

    static decode(blob: dsviper.ValueBlob): Vector3 {
        return new Vector3(dsviper.ValueStructure.cast(
            dsviper.Value.decode(blob, Vector3.type(), definitions())));
    }

    get x(): number {
        return this.value.at("x") as number;
    }

    set x(value: number) {
        setField(this.value, "x", value);
    }

    get y(): number {
        return this.value.at("y") as number;
    }

    set y(value: number) {
        setField(this.value, "y", value);
    }

    get z(): number {
        return this.value.at("z") as number;
    }

    set z(value: number) {
        setField(this.value, "z", value);
    }
}

// Les classes de cette unité, par l'identifiant d'exécution de leur type : c'est ce qui permet
// à `wrap` de rendre un élément de conteneur, ou un document d'attachment, avec son nom.
register([PLAYER, PlayerKey], [LEVEL, Level], [PLAYER_PROPERTY, PlayerProperty], [VECTOR_3, Vector3]);