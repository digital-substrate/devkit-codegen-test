// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

/** ModelB — les types que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";

import { Mapping, Ordered, Sequence } from "../_codegen/container.js";
import { Proxy } from "../_codegen/proxy.js";
import { AnyConceptKey, isKnown, register, setField, wrap } from "../_codegen/registry.js";
import { definitions } from "../index.js";

// ── l'identité de cette unité dans le modèle ──
//
// LE MÊME ARTEFACT QU'EN C++ ET EN PYTHON, POUR LA MÊME RAISON : plusieurs couches en ont
// besoin et ce n'est pas de la sérialisation.

export const MATERIAL = dsviper.ValueUUId.create("fcbafe56-84de-904a-574a-7013e31b8a53");
export const COLOUR = dsviper.ValueUUId.create("a75f5fbe-e310-cca6-ba0c-9c763942e461");

let materialConcept: dsviper.TypeConcept | undefined;
let materialType: dsviper.TypeKey | undefined;

/**
 * Une poignée sur une instance de ModelB::Material, pas la chose elle-même.
 *
 * A material, as ModelB understands one.
 */
export class MaterialKey extends Proxy<dsviper.ValueKey> {
    static concept(): dsviper.TypeConcept {
        return (materialConcept ??= definitions().checkConcept(MATERIAL));
    }

    /**
     * Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin --
     * l'appelant écrit déjà le nom de la classe.
     */
    static type(): dsviper.TypeKey {
        return (materialType ??= new dsviper.TypeKey(MaterialKey.concept()));
    }

    constructor(identifier?: dsviper.ValueKey | dsviper.ValueUUId | null) {
        if (identifier === null) {
            // `null` EXPLICITE N'EST PAS L'ABSENCE D'ARGUMENT. `new XKey()` demande une clé
            // neuve ; `new XKey(null)` passe quelque chose, et ce quelque chose n'en est pas un.
            throw new TypeError("null n'est pas un identifiant d'instance");
        }
        if (identifier instanceof dsviper.ValueKey) {
            if (!identifier.isMember(MaterialKey.concept())) {
                throw new TypeError("cette valeur n'est pas un ModelB::MaterialKey");
            }
            super(identifier);
        } else {
            super(dsviper.ValueKey.create(MaterialKey.concept(), identifier));
        }
    }

    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create(): MaterialKey {
        return new MaterialKey(dsviper.ValueUUId.create());
    }

    static wrap(value: dsviper.Value): MaterialKey {
        return new MaterialKey(dsviper.ValueKey.cast(value));
    }

    static decode(blob: dsviper.ValueBlob): MaterialKey {
        return new MaterialKey(dsviper.ValueKey.cast(
            dsviper.Value.decode(blob, MaterialKey.type(), definitions())));
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
    compareTo(other: MaterialKey | dsviper.ValueKey): number {
        return this.value.compare(other instanceof Proxy ? other.value : other);
    }

    /** L'instance et son type, dits comme le modèle les nomme. */
    description(): string {
        return `${this.value.instanceId().encoded()}:ModelB::MaterialKey`;
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
    static fromAnyConceptKey(key: AnyConceptKey | dsviper.ValueKey): MaterialKey | undefined {
        const value = key instanceof AnyConceptKey ? key.value : key;
        return value.typeConcept().runtimeId().equals(MATERIAL)
            ? new MaterialKey(value) : undefined;
    }

    override toString(): string {
        return this.description();
    }
}

let colourType: dsviper.TypeStructure | undefined;

/** ModelB::Colour. Colour in floating point -- the same name as ModelA::Colour, a different type. */
export class Colour extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure {
        return (colourType ??= definitions().checkStructure(COLOUR));
    }

    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(Colour.type())) {
                throw new TypeError("cette valeur n'est pas un ModelB::Colour");
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
register([MATERIAL, MaterialKey], [COLOUR, Colour]);