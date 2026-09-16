/**
 * Topology — le modèle, et ce qu'aucune unité ne peut revendiquer.
 *
 * UN NAMESPACE EST UN MODULE, ET C'EST GRATUIT. `ModelA::Colour` est `topology/model_a` et
 * `ModelB::Colour` est `topology/model_b` : les deux coexistent sans qu'un nom bouge.
 *
 * CE QUI RESTE AU SOCLE EST PLUS PETIT QU'EN C++. Là-bas il portait `encode`/`decode` parce
 * qu'une valeur C++ et une `Value` du runtime sont deux choses qu'il faut faire passer l'une
 * dans l'autre ; ici une valeur générée *est* une Value. Il ne reste que les définitions.
 */
import dsviper from "@digitalsubstrate/dsviper";
/** Le modèle, tel que le runtime le connaît — le document embarqué, décodé au chargement. */
export declare function definitions(): dsviper.DefinitionsConst;
export * from "./containers.js";
