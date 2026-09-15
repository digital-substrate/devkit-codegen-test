/** ModelB — les types que ce namespace déclare.
 *
 * UN NAMESPACE EST UN MODULE, ET C'EST GRATUIT. Le pack met tout dans un `data.ts` et aplatit
 * en `Test_StructureS` ; ici `ModelB::Colour` est `topology/model_a` et `ModelB::Colour` est
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

export const MATERIAL = dsviper.ValueUUId.create("fcbafe56-84de-904a-574a-7013e31b8a53");
export const COLOUR = dsviper.ValueUUId.create("a75f5fbe-e310-cca6-ba0c-9c763942e461");

let materialConcept: dsviper.TypeConcept | undefined;
let materialType: dsviper.TypeKey | undefined;

/** Une poignée sur une instance de ModelB::Material, pas la chose elle-même. */
export class MaterialKey extends Proxy<dsviper.ValueKey> {
    static concept(): dsviper.TypeConcept {
        return (materialConcept ??= definitions().checkConcept(MATERIAL));
    }

    /** Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin —
     * l'appelant écrit déjà le nom de la classe.
     */
    static type(): dsviper.TypeKey {
        return (materialType ??= new dsviper.TypeKey(MaterialKey.concept()));
    }

    constructor(identifier?: dsviper.ValueKey | dsviper.ValueUUId) {
        if (identifier instanceof dsviper.ValueKey) {
            if (!identifier.type().equals(MaterialKey.type())) {
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

    get instanceId(): dsviper.ValueUUId {
        return this.value.instanceId();
    }

    isValid(): boolean {
        return this.instanceId.isValid();
    }

    override toString(): string {
        return `ModelB::MaterialKey(${this.value.representation()})`;
    }
}

let colourType: dsviper.TypeStructure | undefined;

/** Une couleur en canaux 8 bits — le même nom que ModelB::Colour, un type différent. */
export class Colour extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure {
        return (colourType ??= definitions().checkStructure(COLOUR));
    }

    constructor(value?: dsviper.ValueStructure | { r?: number; g?: number; b?: number }) {
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

    get r(): number { return this.value.at("r") as number; }
    set r(value: number) { this.value.set("r", value); }

    get g(): number { return this.value.at("g") as number; }
    set g(value: number) { this.value.set("g", value); }

    get b(): number { return this.value.at("b") as number; }
    set b(value: number) { this.value.set("b", value); }

    override toString(): string {
        return `ModelB::Colour(r=${this.r}, g=${this.g}, b=${this.b})`;
    }
}

// Les classes de cette unité, par l'identifiant d'exécution de leur type : c'est ce qui permet
// à `wrap` de rendre un élément de conteneur, ou un document d'attachment, avec son nom.
register([[MATERIAL, MaterialKey], [COLOUR, Colour]]);
