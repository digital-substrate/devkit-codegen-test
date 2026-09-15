// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

/** ModelA — les types que ce namespace déclare. */
import dsviper from "@digitalsubstrate/dsviper";

import { Mapping, Ordered, Sequence } from "../_codegen/container.js";
import { Proxy } from "../_codegen/proxy.js";
import { AnyConceptKey, register, setField, wrap } from "../_codegen/registry.js";
import { definitions } from "../index.js";

// ── l'identité de cette unité dans le modèle ──
//
// LE MÊME ARTEFACT QU'EN C++ ET EN PYTHON, POUR LA MÊME RAISON : plusieurs couches en ont
// besoin et ce n'est pas de la sérialisation.

export const MATERIAL = dsviper.ValueUUId.create("de42abc9-3fd6-ac10-63ba-d0d6fba6cb9e");
export const FINISH = dsviper.ValueUUId.create("cc101b86-fc5f-855a-b0f6-59844b9f5e3e");
export const COLOUR = dsviper.ValueUUId.create("887a78c8-07ff-3c8a-8172-ff5ae381dfd9");

let materialConcept: dsviper.TypeConcept | undefined;
let materialType: dsviper.TypeKey | undefined;

/**
 * Une poignée sur une instance de ModelA::Material, pas la chose elle-même.
 *
 * A material, as ModelA understands one.
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

    constructor(identifier?: dsviper.ValueKey | dsviper.ValueUUId) {
        if (identifier instanceof dsviper.ValueKey) {
            if (!identifier.type().equals(MaterialKey.type())) {
                throw new TypeError("cette valeur n'est pas un ModelA::MaterialKey");
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

    /** La clé, vue sans son type. */
    toAny(): AnyConceptKey {
        return new AnyConceptKey(this.value.toAnyConceptKey());
    }

    override toString(): string {
        return `ModelA::MaterialKey(${this.value.representation()})`;
    }
}

let finishType: dsviper.TypeEnumeration | undefined;

/** ModelA::Finish. Un type énuméré, pour que les templates en rencontrent un. Aucun autre namespace
n'en déclare, et c'est voulu : ce qui est testé ici est la topologie, pas le système de
types -- mais une couche qui ne sait pas sérialiser une énumération est incomplète. */
export type Finish = "matte" | "gloss";

/**
 * UN TYPE ET UNE VALEUR SOUS LE MÊME NOM, ce que TypeScript permet et qui dit exactement ce
 * qu'on veut : `Finish` annote, `Finish.matte` désigne, `Finish.wrap` convertit. Le pack en
 * fait une classe qui enveloppe une `ValueEnumeration` ; une union de littéraux se vérifie
 * mieux et ne coûte aucun objet.
 */
export const Finish = {
    matte: "matte",
    gloss: "gloss",

    type(): dsviper.TypeEnumeration {
        return (finishType ??= definitions().checkEnumeration(FINISH));
    },

    wrap(value: dsviper.Value): Finish {
        return dsviper.ValueEnumeration.cast(value).name() as Finish;
    },
};

let colourType: dsviper.TypeStructure | undefined;

/** ModelA::Colour. Colour in 8-bit channels -- the same name as ModelB::Colour, a different type. */
export class Colour extends Proxy<dsviper.ValueStructure> {
    static type(): dsviper.TypeStructure {
        return (colourType ??= definitions().checkStructure(COLOUR));
    }

    constructor(value?: dsviper.ValueStructure | Record<string, dsviper.InputValue>) {
        if (value instanceof dsviper.ValueStructure) {
            if (!value.type().equals(Colour.type())) {
                throw new TypeError("cette valeur n'est pas un ModelA::Colour");
            }
            super(value);
        } else {
            super(new dsviper.ValueStructure(Colour.type(), value));
        }
    }

    static wrap(value: dsviper.Value): Colour {
        return new Colour(dsviper.ValueStructure.cast(value));
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
register([MATERIAL, MaterialKey], [FINISH, Finish], [COLOUR, Colour]);