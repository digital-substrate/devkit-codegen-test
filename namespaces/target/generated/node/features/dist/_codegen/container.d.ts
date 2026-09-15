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
 * UNE VUE ET NON UNE COPIE. La donnée reste dans la Value : `c.fVector[0]` construit un
 * `Colour` au moment où on le demande, et `push` écrit dans la Value.
 */
import dsviper from "@digitalsubstrate/dsviper";
/** Une suite du runtime — vector, set, vec, tuple — dont les éléments portent leurs noms. */
export declare class Sequence<E> {
    readonly value: dsviper.Value;
    private readonly suite;
    constructor(value: dsviper.Value);
    get length(): number;
    at(index: number): E;
    has(element: E): boolean;
    [Symbol.iterator](): Iterator<E>;
    toArray(): E[];
}
/** Une map du runtime, dont les clés et les valeurs portent leurs noms.
 *
 * ELLE N'EST PAS UNE `Map` DE JAVASCRIPT, ET NE PEUT PAS L'ÊTRE. Une `Map` indexe par identité
 * et n'appelle aucune méthode : deux clés égales mais distinctes y seraient deux entrées. La
 * correspondance du runtime, elle, indexe par valeur — c'est pour ça qu'on la garde, plutôt
 * que de recopier son contenu dans une structure JavaScript qui perdrait cette propriété.
 */
export declare class Mapping<K, V> {
    readonly value: dsviper.ValueMap;
    constructor(value: dsviper.ValueMap);
    get size(): number;
    get(key: K): V;
    set(key: K, element: V): void;
    has(key: K): boolean;
    [Symbol.iterator](): Iterator<[K, V]>;
    keys(): K[];
}
/** Un xarray du runtime : une suite dont chaque place a une identité stable.
 *
 * LA POSITION EST LA CLÉ, ET C'EST TOUT CE QUI LE DISTINGUE D'UN `vector`. Deux éditeurs qui
 * insèrent au même endroit n'écrasent pas l'insertion l'un de l'autre.
 */
export declare class Ordered<E> {
    readonly value: dsviper.ValueXArray;
    constructor(value: dsviper.ValueXArray);
    get length(): number;
    positions(): dsviper.ValueUUId[];
    at(position: dsviper.ValueUUId): E | undefined;
    [Symbol.iterator](): Iterator<E>;
}
