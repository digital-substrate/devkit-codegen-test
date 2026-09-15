/** Le passage entre une valeur du runtime et un nom du modèle.
 *
 * UNE VALEUR CONNAÎT SON TYPE, ET UN TYPE NOMMÉ CONNAÎT SON IDENTIFIANT D'EXÉCUTION. Il ne
 * manque donc qu'une table qui dise quelle classe va avec quel identifiant, et chaque unité la
 * remplit en une ligne pour les types qu'elle déclare. C'est ce qui permet à un conteneur de
 * rendre ses éléments avec leurs noms sans qu'aucune classe de conteneur soit générée : le
 * pack en émet une par combinaison rencontrée, ici il n'y en a aucune.
 */
import dsviper from "@digitalsubstrate/dsviper";

import { Mapping, Ordered, Sequence } from "./container.js";
import { Proxy } from "./proxy.js";

/** Ce qu'une classe générée sait faire : se construire depuis une Value. */
export interface Wrapping {
    wrap(value: dsviper.Value): unknown;
}

const classes = new Map<string, Wrapping>();

/** Déclarer les classes d'une unité, par l'identifiant d'exécution de leur type. */
export function register(entries: Iterable<[dsviper.ValueUUId, Wrapping]>): void {
    for (const [runtimeId, wrapping] of entries) {
        classes.set(runtimeId.encoded(), wrapping);
    }
}

/** La valeur du runtime, rendue avec les noms du modèle quand il y en a.
 *
 * RENDUE `any`, ET C'EST UNE DÉCISION PLUTÔT QU'UN RENONCEMENT. Le type réel dépend de ce que
 * la valeur porte, donc il ne peut pas être écrit ici ; mais il est écrit à chaque endroit qui
 * appelle — un accesseur annoté `Sequence<Colour>`, un pool annoté `MaterialKey`. Le
 * vérificateur y trouve un type exact. Ce qu'on concède est un point de passage, déclaré une
 * fois, au lieu d'un `any` répandu sur chaque champ.
 */
// eslint-disable-next-line @typescript-eslint/no-explicit-any
export function wrap(value: dsviper.OutputValue): any {
    if (!(value instanceof dsviper.Value)) {
        return value;
    }

    switch (value.typeCode()) {
        case "struct":
        case "enum": {
            const found = classes.get(value.type().runtimeId().encoded());
            return found ? found.wrap(value) : value;
        }
        case "key": {
            const key = dsviper.ValueKey.cast(value);
            const found = classes.get(key.typeConcept().runtimeId().encoded());
            return found ? found.wrap(key) : key;
        }
        case "optional":
        case "any": {
            const held = value as dsviper.ValueOptional;
            return held.isNil() ? undefined : wrap(held.unwrap());
        }
        case "variant":
            return wrap((value as dsviper.ValueVariant).unwrap());
        case "map":
            return new Mapping(dsviper.ValueMap.cast(value));
        case "xarray":
            return new Ordered(dsviper.ValueXArray.cast(value));
        case "vector":
        case "set":
        case "vec":
        case "mat":
        case "tuple":
            return new Sequence(value);
        default:
            return value;
    }
}

/** La Value que le runtime attend, depuis ce que l'appelant a écrit.
 *
 * Ce qui n'est pas une de nos classes passe tel quel : `Value.loads` du runtime sait déjà
 * convertir un objet JavaScript depuis le descripteur de type. Un tableau est déplié élément
 * par élément, parce qu'il peut en contenir qui, eux, ont une classe.
 */
export function unwrap(value: unknown): dsviper.InputValue {
    if (value instanceof Proxy) {
        return value.value;
    }
    if (value instanceof Sequence || value instanceof Ordered || value instanceof Mapping) {
        return value.value;
    }
    if (Array.isArray(value)) {
        return value.map(unwrap) as dsviper.InputValue;
    }
    return value as dsviper.InputValue;
}
