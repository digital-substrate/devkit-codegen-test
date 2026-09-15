// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

/** ModelC — les types que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";

import { Mapping, Ordered, Sequence } from "../_codegen/container.js";
import { Proxy } from "../_codegen/proxy.js";
import { AnyConceptKey, register, setField, wrap } from "../_codegen/registry.js";
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

    constructor(identifier?: dsviper.ValueKey | dsviper.ValueUUId) {
        if (identifier instanceof dsviper.ValueKey) {
            if (!identifier.type().equals(MarkerKey.type())) {
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

    get instanceId(): dsviper.ValueUUId {
        return this.value.instanceId();
    }

    isValid(): boolean {
        return this.instanceId.isValid();
    }

    /** La clé, vue sans son type. */
    toAny(): AnyConceptKey {
        return new AnyConceptKey(this.value.toAnyConceptKey());
    }

    override toString(): string {
        return `ModelC::MarkerKey(${this.value.representation()})`;
    }
}
// Les classes de cette unité, par l'identifiant d'exécution de leur type : c'est ce qui permet
// à `wrap` de rendre un élément de conteneur, ou un document d'attachment, avec son nom.
register([MARKER, MarkerKey]);