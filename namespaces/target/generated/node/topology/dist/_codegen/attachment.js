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
import { wrap, unwrap } from "./registry.js";
/** Un attachment du modèle, vu depuis l'unité qui le déclare.
 *
 * LA BASE N'A PRESQUE PAS DE MÉTHODES À ELLE. `dsviper.Database` porte les mêmes `keys`,
 * `has`, `get` et `set` qu'un état en mémoire — d'où deux interfaces structurelles plutôt
 * qu'un type nommé : TypeScript les accepte toutes deux sans rien déclarer. Il ne reste en
 * propre que `delete`.
 */
export class AttachmentProxy {
    runtimeId;
    definitions;
    resolved;
    /** LES DEUX CLASSES NE SERVENT PAS À CONVERTIR — `wrap` le fait depuis le type que la
     *  valeur porte. Elles sont là pour que l'unité les nomme, parce que **les nommer force
     *  leur import**, et que c'est l'import qui remplit la table des classes. Sans elles la
     *  conversion marcherait tant que quelqu'un d'autre a importé l'unité d'abord — la pire
     *  forme de correction, celle qui dépend de l'ordre. */
    constructor(runtimeId, definitions, _key, _document) {
        this.runtimeId = runtimeId;
        this.definitions = definitions;
    }
    /** Le descripteur que le runtime en tire, résolu une fois. */
    get descriptor() {
        return (this.resolved ??= this.definitions().checkAttachment(this.runtimeId));
    }
    keys(getting) {
        return [...getting.keys(this.descriptor)].map(wrap);
    }
    has(getting, key) {
        return getting.has(this.descriptor, unwrap(key));
    }
    /** Le document, ou `undefined` — et non un `Optional` enveloppé.
     *
     * LE PACK REND UN `Optional_Colour`, UN PROXY DE PLUS À NOMMER ET À GÉNÉRER. JavaScript a
     * déjà `undefined` et le typage l'exprime dans le retour, ce qui dit la même chose sans
     * qu'une classe existe pour ça.
     */
    get(getting, key) {
        const document = getting.get(this.descriptor, unwrap(key));
        return document.isNil() ? undefined : wrap(document.unwrap());
    }
    /** Poser le document. Rend ce que le contexte rend : rien en mémoire, un statut sur base. */
    set(setting, key, value) {
        return setting.set(this.descriptor, unwrap(key), unwrap(value));
    }
    diff(mutating, key, value, recursive = false) {
        mutating.diff(this.descriptor, unwrap(key), unwrap(value), recursive);
    }
    /** Écrire un seul champ.
     *
     * LE CHEMIN SE FAIT DEPUIS LE NOM DU CHAMP, ICI ET MAINTENANT. Le pack en fait un module
     * entier — une constante par champ de chaque structure du modèle — alors que
     * `Path.fromField` ne dépend que du nom, que l'appelant vient d'écrire.
     */
    update(mutating, key, field, value) {
        mutating.update(this.descriptor, unwrap(key), path(field), unwrap(value));
    }
    /** Retirer le document. La seule opération qu'une base ajoute. */
    delete(database, key) {
        return database.delete(this.descriptor, unwrap(key));
    }
}
const paths = new Map();
function path(field) {
    let found = paths.get(field);
    if (found === undefined) {
        found = dsviper.Path.fromField(field).const();
        paths.set(field, found);
    }
    return found;
}
