/** L'accesseur typé d'un attachment — écrit une fois, pour tous.
 *
 * CE FICHIER NE NOMME AUCUN TYPE DU MODÈLE, ET C'EST TOUT SON PROPOS. Le pack TypeScript écrit
 * 174 lignes de template qui rendent une famille de fonctions par attachment ; pas une ne fait
 * autre chose que passer le descripteur de l'attachment à `AttachmentGetting` ou
 * `AttachmentMutating`. Ce qui varie d'un attachment à l'autre — son identifiant, la classe de
 * sa clé, celle de son document — sont trois valeurs, pas trois cents lignes.
 *
 * `AttachmentProxy` ET NON `Attachment` : `dsviper.Attachment` existe et n'est pas ça. Le sien
 * est le *descripteur*, celui-ci est l'accesseur typé qui le résout et s'en sert — du même mot
 * que `Proxy`, qui est l'accesseur typé d'une `Value`.
 */
import dsviper from "@digitalsubstrate/dsviper";

import { wrap, unwrap, type Wrapping } from "./registry.js";

/** Le contexte sur lequel une opération de lecture porte : un état en mémoire, ou une base. */
export interface Getting {
    keys(attachment: dsviper.Attachment): dsviper.ValueSet;
    has(attachment: dsviper.Attachment, key: dsviper.ValueKey): boolean;
    get(attachment: dsviper.Attachment, key: dsviper.ValueKey): dsviper.ValueOptional;
}

/** Poser un document entier. Un état en mémoire ne rend rien, une base rend un statut. */
export interface Setting extends Getting {
    set(attachment: dsviper.Attachment, key: dsviper.ValueKey, value: dsviper.InputValue): unknown;
}

/** ÉCRIRE UNE PARTIE D'UN DOCUMENT, CE QU'UNE BASE NE SAIT PAS FAIRE.
 *
 * `dsviper.Database` porte `keys`, `has`, `get` et `set`, et s'arrête là : `diff` et `update`
 * demandent de connaître l'état courant pour en dériver une mutation, ce qu'un état en
 * mémoire a et qu'un enregistrement n'a pas. Trois interfaces donc, et non deux — et c'est le
 * vérificateur de types qui l'a dit, là où en C++ il avait fallu attendre l'édition de liens.
 */
export interface Mutating extends Setting {
    diff(attachment: dsviper.Attachment, key: dsviper.ValueKey, value: dsviper.InputValue,
         recursive?: boolean): void;
    update(attachment: dsviper.Attachment, key: dsviper.ValueKey, path: dsviper.PathConst,
           value: dsviper.InputValue): void;
}

/** Un attachment du modèle, vu depuis l'unité qui le déclare.
 *
 * LA BASE N'A PRESQUE PAS DE MÉTHODES À ELLE. `dsviper.Database` porte les mêmes `keys`,
 * `has`, `get` et `set` qu'un état en mémoire — d'où deux interfaces structurelles plutôt
 * qu'un type nommé : TypeScript les accepte toutes deux sans rien déclarer. Il ne reste en
 * propre que `delete`.
 */
export class AttachmentProxy<K, D> {
    private readonly runtimeId: dsviper.ValueUUId;
    private readonly definitions: () => dsviper.DefinitionsConst;
    private resolved?: dsviper.Attachment;

    /** LES DEUX CLASSES NE SERVENT PAS À CONVERTIR — `wrap` le fait depuis le type que la
     *  valeur porte. Elles sont là pour que l'unité les nomme, parce que **les nommer force
     *  leur import**, et que c'est l'import qui remplit la table des classes. Sans elles la
     *  conversion marcherait tant que quelqu'un d'autre a importé l'unité d'abord — la pire
     *  forme de correction, celle qui dépend de l'ordre. */
    constructor(runtimeId: dsviper.ValueUUId,
                definitions: () => dsviper.DefinitionsConst,
                _key: Wrapping,
                _document: Wrapping | undefined) {
        this.runtimeId = runtimeId;
        this.definitions = definitions;
    }

    /** Le descripteur que le runtime en tire, résolu une fois. */
    get descriptor(): dsviper.Attachment {
        return (this.resolved ??= this.definitions().checkAttachment(this.runtimeId));
    }

    keys(getting: Getting): K[] {
        return [...getting.keys(this.descriptor)].map(wrap);
    }

    has(getting: Getting, key: K): boolean {
        return getting.has(this.descriptor, unwrap(key) as dsviper.ValueKey);
    }

    /** Le document, ou `undefined` — et non un `Optional` enveloppé.
     *
     * LE PACK REND UN `Optional_Colour`, UN PROXY DE PLUS À NOMMER ET À GÉNÉRER. JavaScript a
     * déjà `undefined` et le typage l'exprime dans le retour, ce qui dit la même chose sans
     * qu'une classe existe pour ça.
     */
    get(getting: Getting, key: K): D | undefined {
        const document = getting.get(this.descriptor, unwrap(key) as dsviper.ValueKey);
        return document.isNil() ? undefined : wrap(document.unwrap());
    }

    /** Poser le document. Rend ce que le contexte rend : rien en mémoire, un statut sur base.
     *
     * LA VÉRIFICATION DU TYPE EST ICI PARCE QUE LA LIAISON NE LA FAIT PAS. Mesuré : écrire un
     * `Parts::Colour` dans un attachment dont le document est déclaré `Core::Colour` est
     * accepté par `AttachmentMutating.set` de la liaison Node, et se relit tel quel. La
     * liaison Python refuse la même écriture. Un document du mauvais type doit être rejeté là
     * où il apparaît -- c'est le contrat de viper, et il tient partout ailleurs par
     * construction, puisqu'un proxy ne détient rien et que toute écriture atteint le runtime.
     *
     * À retirer le jour où la liaison vérifie, et à signaler d'ici là.
     */
    set(setting: Setting, key: K, value: D): unknown {
        const document = unwrap(value);
        if (document instanceof dsviper.Value
            && !document.type().equals(this.descriptor.documentType())) {
            throw new TypeError(
                `document de type ${document.type().representation()} pour `
                + `${this.descriptor.representation()}, qui en attend `
                + `${this.descriptor.documentType().representation()}`);
        }
        return setting.set(this.descriptor, unwrap(key) as dsviper.ValueKey, document);
    }

    diff(mutating: Mutating, key: K, value: D, recursive = false): void {
        mutating.diff(this.descriptor, unwrap(key) as dsviper.ValueKey, unwrap(value), recursive);
    }

    /** Écrire un seul champ.
     *
     * LE CHEMIN SE FAIT DEPUIS LE NOM DU CHAMP, ICI ET MAINTENANT. Le pack en fait un module
     * entier — une constante par champ de chaque structure du modèle — alors que
     * `Path.fromField` ne dépend que du nom, que l'appelant vient d'écrire.
     */
    update(mutating: Mutating, key: K, field: string, value: unknown): void {
        mutating.update(this.descriptor, unwrap(key) as dsviper.ValueKey, path(field), unwrap(value));
    }

    /** Retirer le document. La seule opération qu'une base ajoute. */
    delete(database: { delete(a: dsviper.Attachment, k: dsviper.ValueKey): boolean }, key: K): boolean {
        return database.delete(this.descriptor, unwrap(key) as dsviper.ValueKey);
    }
}

const paths = new Map<string, dsviper.PathConst>();

function path(field: string): dsviper.PathConst {
    let found = paths.get(field);
    if (found === undefined) {
        found = dsviper.Path.fromField(field).const();
        paths.set(field, found);
    }
    return found;
}
