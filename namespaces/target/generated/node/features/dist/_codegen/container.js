import { unwrap, wrap } from "./registry.js";
/** Une suite du runtime — vector, set, vec, tuple — dont les éléments portent leurs noms. */
export class Sequence {
    value;
    suite;
    constructor(value) {
        this.value = value;
        this.suite = value;
    }
    get length() {
        return this.suite.size();
    }
    at(index) {
        return wrap(this.suite.at(index));
    }
    has(element) {
        return this.suite.contains(unwrap(element));
    }
    *[Symbol.iterator]() {
        for (const element of this.suite) {
            yield wrap(element);
        }
    }
    toArray() {
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
export class Mapping {
    value;
    constructor(value) {
        this.value = value;
    }
    get size() {
        return this.value.size();
    }
    get(key) {
        return wrap(this.value.at(unwrap(key)));
    }
    set(key, element) {
        this.value.set(unwrap(key), unwrap(element));
    }
    has(key) {
        return this.value.contains(unwrap(key));
    }
    *[Symbol.iterator]() {
        for (const [key, element] of this.value) {
            yield [wrap(key), wrap(element)];
        }
    }
    keys() {
        return [...this].map(([key]) => key);
    }
}
/** Un xarray du runtime : une suite dont chaque place a une identité stable.
 *
 * LA POSITION EST LA CLÉ, ET C'EST TOUT CE QUI LE DISTINGUE D'UN `vector`. Deux éditeurs qui
 * insèrent au même endroit n'écrasent pas l'insertion l'un de l'autre.
 */
export class Ordered {
    value;
    constructor(value) {
        this.value = value;
    }
    get length() {
        return this.value.positions().length;
    }
    positions() {
        return this.value.positions();
    }
    at(position) {
        const element = this.value.at(position);
        return element === undefined ? undefined : wrap(element);
    }
    *[Symbol.iterator]() {
        for (const element of this.value) {
            yield wrap(element);
        }
    }
}
