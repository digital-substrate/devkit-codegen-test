/** Le passage entre une valeur du runtime et un nom du modèle.
 *
 * UNE VALEUR CONNAÎT SON TYPE, ET UN TYPE NOMMÉ CONNAÎT SON IDENTIFIANT D'EXÉCUTION. Il ne
 * manque donc qu'une table qui dise quelle classe va avec quel identifiant, et chaque unité la
 * remplit en une ligne pour les types qu'elle déclare. C'est ce qui permet à un conteneur de
 * rendre ses éléments avec leurs noms sans qu'aucune classe de conteneur soit générée : le
 * pack en émet une par combinaison rencontrée, ici il n'y en a aucune.
 */
import dsviper from "@digitalsubstrate/dsviper";
export { AnyConceptKey } from "./proxy.js";
/** Ce qu'une classe générée sait faire : se construire depuis une Value. */
export interface Wrapping {
    wrap(value: dsviper.Value): unknown;
}
/** Déclarer les classes d'une unité, par l'identifiant d'exécution de leur type.
 *
 * VARIADIQUE, ET CE N'EST PAS UN DÉTAIL. Un tableau littéral de paires est inféré comme un
 * tableau d'unions -- `(ValueUUId | typeof Colour)[]` -- et non comme un tableau de tuples ;
 * il ne s'assigne alors à rien. Chaque argument d'une variadique est typé dans le contexte du
 * paramètre, donc chaque paire redevient le tuple qu'elle est.
 */
export declare function register(...entries: (readonly [dsviper.ValueUUId, Wrapping])[]): void;
/** La valeur du runtime, rendue avec les noms du modèle quand il y en a.
 *
 * RENDUE `any`, ET C'EST UNE DÉCISION PLUTÔT QU'UN RENONCEMENT. Le type réel dépend de ce que
 * la valeur porte, donc il ne peut pas être écrit ici ; mais il est écrit à chaque endroit qui
 * appelle — un accesseur annoté `Sequence<Colour>`, un pool annoté `MaterialKey`. Le
 * vérificateur y trouve un type exact. Ce qu'on concède est un point de passage, déclaré une
 * fois, au lieu d'un `any` répandu sur chaque champ.
 */
export declare function wrap(value: dsviper.OutputValue): any;
/** La Value que le runtime attend, depuis ce que l'appelant a écrit.
 *
 * Ce qui n'est pas une de nos classes passe tel quel : `Value.loads` du runtime sait déjà
 * convertir un objet JavaScript depuis le descripteur de type. Un tableau est déplié élément
 * par élément, parce qu'il peut en contenir qui, eux, ont une classe.
 */
export declare function unwrap(value: unknown): dsviper.InputValue;
/** Écrire un champ d'une structure, en construisant ce que le runtime attend.
 *
 * UN VARIANT NE S'ÉCRIT PAS PAR SON ALTERNATIVE, ET C'EST UNE DIFFÉRENCE DE LIAISON. La
 * liaison Python accepte `c.f_variant = Colour(...)` et construit le variant elle-même ; celle
 * de Node refuse — « expected Core::Colour|Parts::Colour|string, got Core::Colour » — et veut
 * une `ValueVariant`. Le type du champ dit lequel des deux cas on est dans, et la structure le
 * porte : c'est donc ici, une fois, plutôt que dans chaque accesseur généré.
 *
 * À signaler : les deux liaisons devraient répondre pareil à la même écriture.
 */
export declare function setField(structure: dsviper.ValueStructure, name: string, value: unknown): void;
