/** ModelA — les types que ce namespace déclare.
 *
 * UN NAMESPACE EST UN MODULE, ET C'EST GRATUIT. Le pack met tout dans un `data.ts` et aplatit
 * en `Test_StructureS` ; ici `ModelA::Colour` est `topology/model_a` et `ModelB::Colour` est
 * `topology/model_b`. Les deux coexistent sans qu'un nom bouge — ce qui a déclenché tout ce
 * chantier coûte, ici comme en Python, une arborescence de fichiers.
 *
 * ET LES CHAMPS SONT DES ACCESSEURS, ce qui fait disparaître la couche 2 du C++. Là-bas il
 * fallait `Fields::Colour::r` pour nommer un champ et `rPath()` pour l'adresser ; `colour.r`
 * est déjà les deux.
 */
import dsviper from "@digitalsubstrate/dsviper";
import { Proxy } from "../_codegen/proxy.js";
import { register } from "../_codegen/registry.js";
import { definitions } from "../index.js";
// ── l'identité de cette unité dans le modèle ──
//
// Le même artefact qu'en C++ et en Python, pour la même raison : plusieurs couches en ont
// besoin et ce n'est pas de la sérialisation.
export const MATERIAL = dsviper.ValueUUId.create("de42abc9-3fd6-ac10-63ba-d0d6fba6cb9e");
export const FINISH = dsviper.ValueUUId.create("cc101b86-fc5f-855a-b0f6-59844b9f5e3e");
export const COLOUR = dsviper.ValueUUId.create("887a78c8-07ff-3c8a-8172-ff5ae381dfd9");
let materialConcept;
let materialType;
/** Une poignée sur une instance de ModelA::Material, pas la chose elle-même. */
export class MaterialKey extends Proxy {
    static concept() {
        return (materialConcept ??= definitions().checkConcept(MATERIAL));
    }
    /** Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin —
     * l'appelant écrit déjà le nom de la classe.
     */
    static type() {
        return (materialType ??= new dsviper.TypeKey(MaterialKey.concept()));
    }
    constructor(identifier) {
        if (identifier instanceof dsviper.ValueKey) {
            if (!identifier.type().equals(MaterialKey.type())) {
                throw new TypeError("cette valeur n'est pas un ModelA::MaterialKey");
            }
            super(identifier);
        }
        else {
            super(dsviper.ValueKey.create(MaterialKey.concept(), identifier));
        }
    }
    /** Une clé sur une instance neuve. L'instance n'existe pas tant que rien ne l'écrit. */
    static create() {
        return new MaterialKey(dsviper.ValueUUId.create());
    }
    static wrap(value) {
        return new MaterialKey(dsviper.ValueKey.cast(value));
    }
    get instanceId() {
        return this.value.instanceId();
    }
    isValid() {
        return this.instanceId.isValid();
    }
    toString() {
        return `ModelA::MaterialKey(${this.value.representation()})`;
    }
}
let colourType;
/** Une couleur en canaux 8 bits — le même nom que ModelB::Colour, un type différent. */
export class Colour extends Proxy {
    static type() {
        return (colourType ??= definitions().checkStructure(COLOUR));
    }
    constructor(value) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(Colour.type())) {
                throw new TypeError("cette valeur n'est pas un ModelA::Colour");
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
    get r() { return this.value.at("r"); }
    set r(value) { this.value.set("r", value); }
    get g() { return this.value.at("g"); }
    set g(value) { this.value.set("g", value); }
    get b() { return this.value.at("b"); }
    set b(value) { this.value.set("b", value); }
    toString() {
        return `ModelA::Colour(r=${this.r}, g=${this.g}, b=${this.b})`;
    }
}
// Les classes de cette unité, par l'identifiant d'exécution de leur type : c'est ce qui permet
// à `wrap` de rendre un élément de conteneur, ou un document d'attachment, avec son nom.
register([MATERIAL, MaterialKey], [COLOUR, Colour]);
