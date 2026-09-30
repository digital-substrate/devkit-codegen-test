/** L'accesseur typé d'un attachment : ce qui est commun à tous, écrit une fois.
 *
 * CE FICHIER NE NOMME AUCUN TYPE DU MODÈLE. Ce qui ne dépend que de l'identité d'un
 * attachment — lire, écrire, énumérer, comparer le document entier — ne fait que passer le
 * descripteur à `AttachmentGetting` ou `AttachmentMutating`, et vit ici une fois, typé par
 * `K` et `D`.
 *
 * CE QUI DÉPEND DU DOCUMENT EST GÉNÉRÉ, ET C'EST VOULU. `unionVertexKeys`, `setColor` : ce
 * sont les opérations avec lesquelles s'écrivent les fonctions métier, et elles doivent se
 * compléter et se vérifier à la compilation. Une unité déclare donc une classe par
 * attachment, dont chaque méthode appelle l'une des primitives protégées d'ici.
 *
 * `AttachmentProxy` ET NON `Attachment` : `dsviper.Attachment` existe et n'est pas ça. Le sien
 * est le *descripteur*, celui-ci est l'accesseur typé qui le résout et s'en sert — du même mot
 * que `Proxy`, qui est l'accesseur typé d'une `Value`.
 */
import dsviper from "@digitalsubstrate/dsviper";

import { Sequence } from "./container.js";
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
    unionInSet(attachment: dsviper.Attachment, key: dsviper.ValueKey, path: dsviper.PathConst,
               value: dsviper.InputValue): void;
    subtractInSet(attachment: dsviper.Attachment, key: dsviper.ValueKey, path: dsviper.PathConst,
                  value: dsviper.InputValue): void;
    unionInMap(attachment: dsviper.Attachment, key: dsviper.ValueKey, path: dsviper.PathConst,
               value: dsviper.InputValue): void;
    subtractInMap(attachment: dsviper.Attachment, key: dsviper.ValueKey, path: dsviper.PathConst,
                  value: dsviper.InputValue): void;
    updateInMap(attachment: dsviper.Attachment, key: dsviper.ValueKey, path: dsviper.PathConst,
                value: dsviper.InputValue): void;
    insertInXarray(attachment: dsviper.Attachment, key: dsviper.ValueKey, path: dsviper.PathConst,
                   beforePosition: dsviper.ValueUUId, newPosition: dsviper.ValueUUId,
                   value: dsviper.InputValue): void;
    updateInXarray(attachment: dsviper.Attachment, key: dsviper.ValueKey, path: dsviper.PathConst,
                   position: dsviper.ValueUUId, value: dsviper.InputValue): void;
    removeInXarray(attachment: dsviper.Attachment, key: dsviper.ValueKey, path: dsviper.PathConst,
                   position: dsviper.ValueUUId): void;
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

    /** Les clés, comme le runtime les tient — un ensemble, et non un tableau recopié.
     *
     * RECOPIER PERDRAIT DEUX CHOSES : la taille sans parcours, et l'appartenance par valeur.
     * Un tableau de JavaScript n'a ni l'une ni l'autre, et l'ensemble du runtime a les deux.
     */
    keys(getting: Getting): Sequence<K> {
        return new Sequence<K>(getting.keys(this.descriptor));
    }

    /** Les paires clé/document, telles que le runtime les rend.
     *
     * UNE BASE N'ÉNUMÈRE PAS ELLE-MÊME : elle offre l'interface de lecture qui le fait.
     */
    enumerate(getting: Getting): [K, D | undefined][] {
        const source = (getting as unknown as { enumerate?: unknown; attachmentGetting?: () => dsviper.AttachmentGetting });
        const reader = typeof source.enumerate === "function"
            ? (getting as unknown as dsviper.AttachmentGetting)
            : (source.attachmentGetting as () => dsviper.AttachmentGetting)();
        return reader.enumerate(this.descriptor)
            .map(([key, document]) => [wrap(key), wrap(document)]);
    }

    /** Ce qui a changé entre deux états : ajouté, retiré, modifié, identique. */
    diffKeys(current: Getting, other: Getting):
            [Sequence<K>, Sequence<K>, Sequence<K>, Sequence<K>] {
        const groups = dsviper.AttachmentGetting.diffKeys(
            current as unknown as dsviper.AttachmentGetting,
            other as unknown as dsviper.AttachmentGetting, this.descriptor);
        return groups.map((group) => new Sequence<K>(group)) as unknown as
            [Sequence<K>, Sequence<K>, Sequence<K>, Sequence<K>];
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

    /** Retirer le document. La seule opération qu'une base ajoute. */
    delete(database: { delete(a: dsviper.Attachment, k: dsviper.ValueKey): boolean }, key: K): boolean {
        return database.delete(this.descriptor, unwrap(key) as dsviper.ValueKey);
    }

    // ── les primitives des méthodes générées ──
    //
    // UNE PAR OPÉRATION DU RUNTIME, ET AUCUNE N'EST PUBLIQUE. Le champ est nommé comme le
    // modèle le déclare, parce que c'est le nom du chemin ; `undefined` désigne la racine,
    // pour un document qui est lui-même un set, une map ou une xarray. Une unité les appelle
    // depuis des méthodes qui portent le nom et les types de chaque champ.

    protected updateField(mutating: Mutating, key: K, field: string, value: unknown): void {
        mutating.update(this.descriptor, this.keyOf(key), path(field), unwrap(value));
    }

    protected unionInSet(mutating: Mutating, key: K, field: string | undefined, value: unknown): void {
        mutating.unionInSet(this.descriptor, this.keyOf(key), path(field), this.valueAt(field, value));
    }

    protected subtractInSet(mutating: Mutating, key: K, field: string | undefined, value: unknown): void {
        mutating.subtractInSet(this.descriptor, this.keyOf(key), path(field), this.valueAt(field, value));
    }

    protected unionInMap(mutating: Mutating, key: K, field: string | undefined, value: unknown): void {
        mutating.unionInMap(this.descriptor, this.keyOf(key), path(field), this.valueAt(field, value));
    }

    protected subtractInMap(mutating: Mutating, key: K, field: string | undefined, value: unknown): void {
        mutating.subtractInMap(this.descriptor, this.keyOf(key), path(field), this.valueAt(field, value, "keys"));
    }

    protected updateInMap(mutating: Mutating, key: K, field: string | undefined, value: unknown): void {
        mutating.updateInMap(this.descriptor, this.keyOf(key), path(field), this.valueAt(field, value));
    }

    protected insertInXArray(mutating: Mutating, key: K, field: string | undefined,
                             beforePosition: dsviper.ValueUUId, newPosition: dsviper.ValueUUId,
                             value: unknown): void {
        mutating.insertInXarray(this.descriptor, this.keyOf(key), path(field),
                                beforePosition, newPosition, this.valueAt(field, value, "element"));
    }

    protected updateInXArray(mutating: Mutating, key: K, field: string | undefined,
                             position: dsviper.ValueUUId, value: unknown): void {
        mutating.updateInXarray(this.descriptor, this.keyOf(key), path(field), position, this.valueAt(field, value, "element"));
    }

    protected removeInXArray(mutating: Mutating, key: K, field: string | undefined,
                             position: dsviper.ValueUUId): void {
        mutating.removeInXarray(this.descriptor, this.keyOf(key), path(field), position);
    }

    private keyOf(key: K): dsviper.ValueKey {
        return unwrap(key) as dsviper.ValueKey;
    }

    /** La valeur que la liaison attend, construite depuis le type au chemin.
     *
     * LA LIAISON NODE NE CONVERTIT PAS ICI CE QU'ELLE CONVERTIT AILLEURS. Mesuré :
     * `AttachmentMutating.update` accepte un objet natif et le vérifie contre le type au
     * chemin ; `unionInSet`, `unionInMap`, `insertInXarray` et les autres exigent une `Value`
     * déjà construite -- « expects a Value handle ». La liaison Python accepte l'objet natif
     * partout. La construction se fait donc ici, depuis le type que le descripteur porte :
     * l'agrégat entier, ses seules clés pour retirer d'une map, ou un élément pour une xarray.
     *
     * À retirer le jour où la liaison convertit, et à signaler d'ici là.
     */
    private valueAt(field: string | undefined, value: unknown,
                    part: "whole" | "keys" | "element" = "whole"): dsviper.Value {
        const document = this.descriptor.documentType();
        const aggregate = field === undefined
            ? document
            : (document as dsviper.TypeStructure).check(field).type();
        const type = part === "keys"
            ? new dsviper.TypeSet((aggregate as dsviper.TypeMap).keyType())
            : part === "element"
                ? (aggregate as dsviper.TypeXArray).elementType()
                : aggregate;
        const native = unwrap(value);
        return native instanceof dsviper.Value ? native : dsviper.Value.create(type, native);
    }
}

const paths = new Map<string | undefined, dsviper.PathConst>();

/** Le chemin d'un champ, ou la racine ; construit une fois par nom. */
function path(field: string | undefined): dsviper.PathConst {
    let found = paths.get(field);
    if (found === undefined) {
        found = (field === undefined ? new dsviper.Path() : dsviper.Path.fromField(field)).const();
        paths.set(field, found);
    }
    return found;
}
