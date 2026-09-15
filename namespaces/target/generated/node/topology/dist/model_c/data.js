// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar
/** ModelC — les types que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";
import { Proxy } from "../_codegen/proxy.js";
import { AnyConceptKey, register } from "../_codegen/registry.js";
import { definitions } from "../index.js";
// ── l'identité de cette unité dans le modèle ──
//
// LE MÊME ARTEFACT QU'EN C++ ET EN PYTHON, POUR LA MÊME RAISON : plusieurs couches en ont
// besoin et ce n'est pas de la sérialisation.
export const MARKER = dsviper.ValueUUId.create("257888a7-848c-4568-5258-f8822be61ab0");
let markerConcept;
let markerType;
/**
 * Une poignée sur une instance de ModelC::Marker, pas la chose elle-même.
 *
 * Something a projection can point at, and nothing else refers to.
 */
export class MarkerKey extends Proxy {
    static concept() {
        return (markerConcept ??= definitions().checkConcept(MARKER));
    }
    /**
     * Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin --
     * l'appelant écrit déjà le nom de la classe.
     */
    static type() {
        return (markerType ??= new dsviper.TypeKey(MarkerKey.concept()));
    }
    constructor(identifier) {
        if (identifier instanceof dsviper.ValueKey) {
            if (!identifier.type().equals(MarkerKey.type())) {
                throw new TypeError("cette valeur n'est pas un ModelC::MarkerKey");
            }
            super(identifier);
        }
        else {
            super(dsviper.ValueKey.create(MarkerKey.concept(), identifier));
        }
    }
    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create() {
        return new MarkerKey(dsviper.ValueUUId.create());
    }
    static wrap(value) {
        return new MarkerKey(dsviper.ValueKey.cast(value));
    }
    get instanceId() {
        return this.value.instanceId();
    }
    isValid() {
        return this.instanceId.isValid();
    }
    /** La clé, vue sans son type. */
    toAny() {
        return new AnyConceptKey(this.value.toAnyConceptKey());
    }
    toString() {
        return `ModelC::MarkerKey(${this.value.representation()})`;
    }
}
// Les classes de cette unité, par l'identifiant d'exécution de leur type : c'est ce qui permet
// à `wrap` de rendre un élément de conteneur, ou un document d'attachment, avec son nom.
register([MARKER, MarkerKey]);
