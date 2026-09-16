// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

/** ModelC — les types que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";

import { Mapping, Ordered, Sequence } from "../_codegen/container.js";
import { Proxy } from "../_codegen/proxy.js";
import { AnyConceptKey, isKnown, register, setField, wrap } from "../_codegen/registry.js";
import { definitions } from "../index.js";

// ── l'identité de cette unité dans le modèle ──
//
// LE MÊME ARTEFACT QU'EN C++ ET EN PYTHON, POUR LA MÊME RAISON : plusieurs couches en ont
// besoin et ce n'est pas de la sérialisation.

export const MARKER = dsviper.ValueUUId.create("257888a7-848c-4568-5258-f8822be61ab0");

let markerConcept: dsviper.TypeConcept | undefined;
let markerType: dsviper.TypeKey | undefined;

/**
 * Une poignée sur une instance de ModelC::Marker, pas la chose elle-même.
 *
 * Something a projection can point at, and nothing else refers to.
 */
export class MarkerKey extends Proxy<dsviper.ValueKey> {
    static concept(): dsviper.TypeConcept {
        return (markerConcept ??= definitions().checkConcept(MARKER));
    }

    /**
     * Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin --
     * l'appelant écrit déjà le nom de la classe.
     */
    static type(): dsviper.TypeKey {
        return (markerType ??= new dsviper.TypeKey(MarkerKey.concept()));
    }

    constructor(identifier?: dsviper.ValueKey | dsviper.ValueUUId | null) {
        if (identifier === null) {
            // `null` EXPLICITE N'EST PAS L'ABSENCE D'ARGUMENT. `new XKey()` demande une clé
            // neuve ; `new XKey(null)` passe quelque chose, et ce quelque chose n'en est pas un.
            throw new TypeError("null n'est pas un identifiant d'instance");
        }
        if (identifier instanceof dsviper.ValueKey) {
            if (!identifier.isMember(MarkerKey.concept())) {
                throw new TypeError("cette valeur n'est pas un ModelC::MarkerKey");
            }
            super(identifier);
        } else {
            super(dsviper.ValueKey.create(MarkerKey.concept(), identifier));
        }
    }

    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create(): MarkerKey {
        return new MarkerKey(dsviper.ValueUUId.create());
    }

    static wrap(value: dsviper.Value): MarkerKey {
        return new MarkerKey(dsviper.ValueKey.cast(value));
    }

    static decode(blob: dsviper.ValueBlob): MarkerKey {
        return new MarkerKey(dsviper.ValueKey.cast(
            dsviper.Value.decode(blob, MarkerKey.type(), definitions())));
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
    compareTo(other: MarkerKey | dsviper.ValueKey): number {
        return this.value.compare(other instanceof Proxy ? other.value : other);
    }

    /** L'instance et son type, dits comme le modèle les nomme. */
    description(): string {
        return `${this.value.instanceId().encoded()}:ModelC::MarkerKey`;
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
    static fromAnyConceptKey(key: AnyConceptKey | dsviper.ValueKey): MarkerKey | undefined {
        const value = key instanceof AnyConceptKey ? key.value : key;
        return value.typeConcept().runtimeId().equals(MARKER)
            ? new MarkerKey(value) : undefined;
    }

    override toString(): string {
        return this.description();
    }
}
// Les classes de cette unité, par l'identifiant d'exécution de leur type : c'est ce qui permet
// à `wrap` de rendre un élément de conteneur, ou un document d'attachment, avec son nom.
register([MARKER, MarkerKey]);