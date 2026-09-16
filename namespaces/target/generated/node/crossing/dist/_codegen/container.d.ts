/** Les conteneurs, rendus avec les noms du modèle — écrits une fois, pour tous.
 *
 * CE QUE LE PACK GÉNÈRE ICI, ET POURQUOI IL N'Y A RIEN À GÉNÉRER. Le pack TypeScript émet une
 * classe par forme de conteneur rencontrée — `Optional_Colour`, `Vector_Parts_Colour` — soit
 * l'essentiel de ses 1 093 lignes de `data.ts.stg`. Or deux d'entre elles ne diffèrent que par
 * le descripteur du type et par la classe qui enveloppe un élément, et la valeur porte déjà
 * les deux.
 *
 * GÉNÉRIQUES, DONC : `Sequence<Colour>` dit à un lecteur et à `tsc` ce que
 * `Vector_Parts_Colour` disait, sans qu'une classe existe par combinaison.
 *
 * ET NOMMÉES, PARCE QU'UNE VUE SEULE NE SUFFIT PAS. Elle enveloppe la valeur d'un champ qui
 * existe déjà ; elle ne permet pas d'écrire `new Vector_uint8([1, 2, 3])`, donc pas de
 * construire un conteneur pour le passer à une fonction de pool ni de bâtir un document avant
 * de l'attacher. La fabrique en bas lie une vue générique à un descripteur : un *nom* par
 * forme, pas une classe.
 *
 * UNE VUE ET NON UNE COPIE. La donnée reste dans la Value : `c.fVector.at(0)` construit un
 * `Colour` au moment où on le demande, et `push` écrit dans la Value.
 */
import dsviper from "@digitalsubstrate/dsviper";
/** Ce que les quatre vues ont en commun, et qui vient de la Value.
 *
 * Le type, l'encodage, la copie, l'empreinte : aucun ne dépend de la forme du conteneur. Ce
 * sont des questions posées à la valeur, et la vue ne fait que les transmettre — une vue
 * obtenue d'un champ doit y répondre comme une vue construite par son nom, puisque c'est la
 * même valeur derrière.
 */
export declare class View {
    readonly value: dsviper.Value;
    constructor(value: dsviper.Value);
    type(): dsviper.Type;
    hash(): bigint;
    hashKey(): bigint;
    equals(other: unknown): boolean;
    encode(streamCodecInstancing?: dsviper.StreamCodecInstancing): dsviper.ValueBlob;
    hexdigest(): string;
    copy(): this;
    toJSON(): dsviper.NativeValue;
    toString(): string;
}
/** Une suite du runtime — vector, set, vec, tuple — dont les éléments portent leurs noms. */
export declare class Sequence<E> extends View {
    private get suite();
    get size(): number;
    get length(): number;
    at(...position: number[]): E;
    has(element: E): boolean;
    [Symbol.iterator](): Iterator<E>;
    toArray(): E[];
    /** La colonne d'une matrice, et la ligne — deux façons de la lire, et le modèle les nomme. */
    row(index: number): unknown[];
    setRow(index: number, elements: unknown[]): void;
    /** Ce que la valeur sait faire et que la vue ne nomme pas.
     *
     * LA VUE NE CHOISIT PAS CE QUI PASSE. Un ensemble a `isdisjoint`, `union`, `min` ; un
     * vecteur en a d'autres ; les nommer un par un reviendrait à recopier le runtime et à se
     * périmer au premier ajout.
     */
    call(name: string, ...args: unknown[]): unknown;
}
/** Une map du runtime, dont les clés et les valeurs portent leurs noms.
 *
 * ELLE N'EST PAS UNE `Map` DE JAVASCRIPT, ET NE PEUT PAS L'ÊTRE. Une `Map` indexe par identité
 * et n'appelle aucune méthode : deux clés égales mais distinctes y seraient deux entrées. La
 * correspondance du runtime indexe par valeur — c'est pour ça qu'on la garde.
 */
export declare class Mapping<K, V> extends View {
    private get map();
    get size(): number;
    at(key: K): V;
    get(key: K): V | undefined;
    set(key: K, element: V): void;
    has(key: K): boolean;
    remove(key: K): void;
    clear(): void;
    keys(): K[];
    values(): V[];
    entries(): [K, V][];
    /** ITÉRER UNE MAP DU RUNTIME REND DES PAIRES, et non des clés — contrairement à une `Map`
     *  de JavaScript et à un `dict` de Python, qui rendent les clés. Les redemander une par
     *  une serait un aller-retour de plus, et la clé encodée ne se represente pas toujours. */
    [Symbol.iterator](): Iterator<[K, V]>;
    call(name: string, ...args: unknown[]): unknown;
}
/** Un xarray du runtime : une suite dont chaque place a une identité stable.
 *
 * LA POSITION EST LA CLÉ, et c'est tout ce qui le distingue d'un `vector`. Deux éditeurs qui
 * insèrent au même endroit n'écrasent pas l'insertion l'un de l'autre.
 */
export declare class Ordered<E> extends View {
    private get ordered();
    static readonly END: dsviper.ValueUUId;
    static end(): dsviper.ValueUUId;
    static createPosition(): dsviper.ValueUUId;
    /** Le nombre d'éléments — et la fin n'en est pas un.
     *
     * `positions()` rend aussi `END`, la place d'après le dernier, parce qu'on y insère. La
     * compter ferait un élément de plus dans un ordonné vide, ce qui est visiblement faux.
     */
    get size(): number;
    positions(): dsviper.ValueUUId[];
    private elementPositions;
    position(index: number): dsviper.ValueUUId | undefined;
    indexOf(position: dsviper.ValueUUId): number | undefined;
    hasPosition(position: dsviper.ValueUUId): boolean;
    at(where: dsviper.ValueUUId | number): E | undefined;
    /** L'élément à cette position, ou `undefined` — le même que `at`, sous le nom que le
     *  pack emploie. Deux mots pour une question qui n'en est qu'une. */
    get(where: dsviper.ValueUUId | number): E | undefined;
    set(where: dsviper.ValueUUId | number, element: E): void;
    insert(beforePosition: dsviper.ValueUUId, element: E, newPosition?: dsviper.ValueUUId): dsviper.ValueUUId;
    append(element: E): dsviper.ValueUUId;
    remove(position: dsviper.ValueUUId): void;
    /** Les paires position/élément, dans l'ordre.
     *
     * LA FIN N'EST PAS UNE PLACE : `positions()` la rend parce qu'on y insère, et la compter
     * ferait un élément de plus à chaque parcours.
     */
    items(): [dsviper.ValueUUId, E | undefined][];
    [Symbol.iterator](): Iterator<E>;
    call(name: string, ...args: unknown[]): unknown;
}
/** Une valeur, ou rien.
 *
 * UNE VUE À ELLE, ET NON UNE SUITE. Un `optional` pose une question qu'aucun autre conteneur
 * ne pose — « y a-t-il quelque chose ? » — et trois opérations en découlent.
 */
export declare class Optional<E> extends View {
    private get optional();
    isNil(): boolean;
    unwrap(): E;
    wrap(element: E): void;
    get(fallback?: E): E | undefined;
    clear(): void;
}
/** L'une de plusieurs alternatives, et celle qui est tenue. */
export declare class Variant<E> extends View {
    private get variant();
    unwrap(): E;
    wrap(element: E, type?: dsviper.Type): void;
    /** L'alternative tenue, si c'est celle qu'on demande. */
    as<T>(type: dsviper.Type): T;
    holds(type: dsviper.Type): boolean;
    /** `setString`, `getString`, `isString` — dérivés des alternatives que le type porte.
     *
     * LE PACK EN ÉMET TROIS PAR ALTERNATIVE DE CHAQUE VARIANT DU MODÈLE. Le type du variant
     * les connaît : le nom demandé désigne l'une d'elles ou n'existe pas, et le dire ici coûte
     * une recherche au lieu d'une classe par combinaison.
     */
    arm(name: string): ((...args: unknown[]) => unknown) | undefined;
}
type Bound<V> = {
    new (value?: unknown): V;
    type(): dsviper.Type;
    decode(blob: dsviper.ValueBlob): V;
};
export declare const sequenceOf: <E>(typeOf: () => dsviper.Type) => Bound<Sequence<E>>;
export declare const mappingOf: <K, V>(typeOf: () => dsviper.Type) => Bound<Mapping<K, V>>;
export declare const orderedOf: <E>(typeOf: () => dsviper.Type) => Bound<Ordered<E>>;
export declare const optionalOf: <E>(typeOf: () => dsviper.Type) => Bound<Optional<E>>;
export declare const variantOf: <E>(typeOf: () => dsviper.Type) => Bound<Variant<E>>;
export {};
