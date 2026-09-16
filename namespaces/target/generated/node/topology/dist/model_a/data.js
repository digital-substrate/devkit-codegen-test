// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar
/** ModelA — les types que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";
import { Proxy } from "../_codegen/proxy.js";
import { AnyConceptKey, register, setField } from "../_codegen/registry.js";
import { definitions } from "../index.js";
// ── l'identité de cette unité dans le modèle ──
//
// LE MÊME ARTEFACT QU'EN C++ ET EN PYTHON, POUR LA MÊME RAISON : plusieurs couches en ont
// besoin et ce n'est pas de la sérialisation.
export const MATERIAL = dsviper.ValueUUId.create("de42abc9-3fd6-ac10-63ba-d0d6fba6cb9e");
export const FINISH = dsviper.ValueUUId.create("cc101b86-fc5f-855a-b0f6-59844b9f5e3e");
export const COLOUR = dsviper.ValueUUId.create("887a78c8-07ff-3c8a-8172-ff5ae381dfd9");
let materialConcept;
let materialType;
/**
 * Une poignée sur une instance de ModelA::Material, pas la chose elle-même.
 *
 * A material, as ModelA understands one.
 */
export class MaterialKey extends Proxy {
    static concept() {
        return (materialConcept ??= definitions().checkConcept(MATERIAL));
    }
    /**
     * Le descripteur du type de la clé, résolu une fois.
     *
     * STATIQUE ET NON LIBRE : en C++ il fallait `type(tag<T>{})` pour que la recherche par
     * argument trouve l'unité de T. TypeScript n'a pas cette recherche et n'en a pas besoin --
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
    /** La clé, vue sans son type. */
    toAny() {
        return new AnyConceptKey(this.value.toAnyConceptKey());
    }
    toString() {
        return `ModelA::MaterialKey(${this.value.representation()})`;
    }
}
let finishType;
/**
 * UN TYPE ET UNE VALEUR SOUS LE MÊME NOM, ce que TypeScript permet et qui dit exactement ce
 * qu'on veut : `Finish` annote, `Finish.matte` désigne, `Finish.wrap` convertit. Le pack en
 * fait une classe qui enveloppe une `ValueEnumeration` ; une union de littéraux se vérifie
 * mieux et ne coûte aucun objet.
 */
export const Finish = {
    MATTE: "matte",
    GLOSS: "gloss",
    type() {
        return (finishType ??= definitions().checkEnumeration(FINISH));
    },
    wrap(value) {
        return dsviper.ValueEnumeration.cast(value).name();
    },
};
let colourType;
/** ModelA::Colour. Colour in 8-bit channels -- the same name as ModelB::Colour, a different type. */
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
register([MATERIAL, MaterialKey], [FINISH, Finish], [COLOUR, Colour]);
