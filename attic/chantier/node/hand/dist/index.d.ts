import dsviper from "@digitalsubstrate/dsviper";
/** Le modèle, tel que le runtime le connaît.
 *
 * Assemblé depuis le `.dsm` ici, parce que c'est une référence et qu'elle doit pouvoir
 * tourner. Un paquet livré embarque le document compressé et le décode — même objet, même
 * résultat, et c'est la seule différence entre ce fichier et celui qui sera généré.
 */
export declare function definitions(): dsviper.DefinitionsConst;
