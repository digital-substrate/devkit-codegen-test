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

import { unwrap, wrap } from "./registry.js";

/** LA SURFACE COMMUNE AUX QUATRE SUITES DU RUNTIME, et rien de plus.
 *
 * `vector`, `set`, `vec` et `tuple` sont quatre classes distinctes qui ne partagent aucun
 * ancêtre utile ; ce qu'elles ont toutes est `size`, `at`, `contains` et l'itération. C'est
 * donc ce qu'une vue peut offrir sans mentir. Ce qui n'est vrai que d'une seule — ajouter à
 * un vector, unir deux sets — se demande à `value`, qui est là pour ça.
 */
interface Suite extends Iterable<dsviper.OutputValue> {
    size(): number;
    at(index: number, encoded?: boolean): dsviper.OutputValue;
    contains(value: dsviper.InputValue): boolean;
}

/** Une suite du runtime — vector, set, vec, tuple — dont les éléments portent leurs noms. */
export class Sequence<E> {
    readonly value: dsviper.Value;
    private readonly suite: Suite;

    constructor(value: dsviper.Value) {
        this.value = value;
        this.suite = value as unknown as Suite;
    }

    get length(): number {
        return this.suite.size();
    }

    at(index: number): E {
        return wrap(this.suite.at(index));
    }

    has(element: E): boolean {
        return this.suite.contains(unwrap(element));
    }

    *[Symbol.iterator](): Iterator<E> {
        for (const element of this.suite) {
            yield wrap(element);
        }
    }

    toArray(): E[] {
        return [...this];
    }
}

/** Une map du runtime, dont les clés et les valeurs portent leurs noms.
 *
 * ELLE N'EST PAS UNE `Map` DE JAVASCRIPT, ET NE PEUT PAS L'ÊTRE. Une `Map` indexe par identité
 * et n'appelle aucune méthode : deux clés égales mais distinctes y seraient deux entrées. La
 * correspondance du runtime, elle, indexe par valeur — c'est pour ça qu'on la garde, plutôt
 * que de recopier son contenu dans une structure JavaScript qui perdrait cette propriété.
 */
export class Mapping<K, V> {
    readonly value: dsviper.ValueMap;

    constructor(value: dsviper.ValueMap) {
        this.value = value;
    }

    get size(): number {
        return this.value.size();
    }

    get(key: K): V {
        return wrap(this.value.at(unwrap(key)));
    }

    set(key: K, element: V): void {
        this.value.set(unwrap(key), unwrap(element));
    }

    has(key: K): boolean {
        return this.value.contains(unwrap(key));
    }

    *[Symbol.iterator](): Iterator<[K, V]> {
        for (const [key, element] of this.value as unknown as Iterable<[dsviper.ValueKey, dsviper.OutputValue]>) {
            yield [wrap(key), wrap(element)];
        }
    }

    keys(): K[] {
        return [...this].map(([key]) => key);
    }
}

/** Un xarray du runtime : une suite dont chaque place a une identité stable.
 *
 * LA POSITION EST LA CLÉ, ET C'EST TOUT CE QUI LE DISTINGUE D'UN `vector`. Deux éditeurs qui
 * insèrent au même endroit n'écrasent pas l'insertion l'un de l'autre.
 */
export class Ordered<E> {
    readonly value: dsviper.ValueXArray;

    constructor(value: dsviper.ValueXArray) {
        this.value = value;
    }

    get length(): number {
        return this.value.positions().length;
    }

    positions(): dsviper.ValueUUId[] {
        return this.value.positions();
    }

    at(position: dsviper.ValueUUId): E | undefined {
        const element = this.value.at(position);
        return element === undefined ? undefined : wrap(element);
    }

    *[Symbol.iterator](): Iterator<E> {
        for (const element of this.value as unknown as Iterable<dsviper.OutputValue>) {
            yield wrap(element);
        }
    }
}
