/** Tools — un pool, et une unité à part entière.
 *
 * ICI IL N'Y A QUE LE BORD CLIENT, ET CE N'EST PAS UN CHOIX. La liaison Node n'expose aucune
 * classe `FunctionPool` : un pool n'y est atteignable que par un `ServiceRemote`, donc à
 * travers un fil. C++ construit le pool et l'expose ; Python le tient en main et l'appelle ;
 * Node ne peut que l'appeler à distance.
 *
 * C'est la même question posée à trois langages, et la troisième réponse est « rien à
 * générer de ce côté-là ». Elle décide aussi de la découpe en fonctionnalités : `Service` et
 * `ServiceClient` ne sont pas la même chose, puisqu'une cible n'a que la seconde.
 *
 * LES MÉTHODES SONT ÉCRITES, PAS DÉDUITES. `functionPoolFunc(pool, "add").call(…)` marche sans
 * qu'on génère quoi que ce soit, et c'est pourquoi il faut les écrire : sans elles le nom
 * d'une fonction du modèle n'est qu'une chaîne, une faute de frappe n'est vue qu'à l'exécution,
 * et rien ne dit ce que l'appel prend ni ce qu'il rend.
 */
import dsviper from "@digitalsubstrate/dsviper";
export const NAME = "Tools";
export const UUID = dsviper.ValueUUId.create("17e63428-03e1-41d7-ad9d-60c5665bbd66");
/** Le pool, vu d'un client. */
export class Remote {
    service;
    constructor(service) {
        this.service = service;
    }
    isAvailable() {
        return this.service.functionPoolFuncs(NAME) !== undefined;
    }
    reset() {
        this.service.functionPoolFunc(NAME, "reset").call();
    }
    /** UN ENTIER 64 BITS EST UN `bigint`, et c'est la cible qui le décide. Le modèle dit
     *  `int64` ; C++ lit `std::int64_t`, Python lit `int`, et ici seul `bigint` porte la
     *  valeur sans perte. */
    add(a, b) {
        return this.service.functionPoolFunc(NAME, "add").call(a, b);
    }
}
