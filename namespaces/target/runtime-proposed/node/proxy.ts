/** Ce que toute classe générée a en commun — écrit une fois, pour tous.
 *
 * UNE CLASSE GÉNÉRÉE ENVELOPPE UNE `dsviper.Value`, ELLE NE LA COPIE PAS. La donnée vit dans
 * la Value ; la classe lui donne des noms. Tout ce qui en découle — l'égalité, le hachage, la
 * sérialisation — ne dépend d'aucun type d'un modèle, donc rien n'a à être émis par type.
 *
 * ET ICI, CONTRAIREMENT À PYTHON, `instanceof` DIT LA VÉRITÉ. La liaison Node déclare une vraie
 * hiérarchie et l'expose à l'exécution : `value instanceof dsviper.Value` est vrai pour toute
 * valeur concrète. La base commune n'est donc pas là pour permettre de reconnaître nos classes
 * — le runtime s'y suffit — mais seulement pour ne pas répéter ce qu'elles partagent.
 */
import dsviper from "@digitalsubstrate/dsviper";

export abstract class Proxy<V extends dsviper.Value> {
    readonly value: V;

    protected constructor(value: V) {
        this.value = value;
    }

    /** L'égalité porte sur la valeur et sur la classe.
     *
     * `ModelA::Colour` et `ModelB::Colour` enveloppent des Values de types différents, donc
     * comparer les valeurs suffirait ; exiger la même classe le dit quand même, parce que
     * c'est ce qui est voulu et non ce qui se trouve être vrai.
     */
    equals(other: unknown): boolean {
        return other instanceof Proxy
            && other.constructor === this.constructor
            && this.value.equals(other.value);
    }

    /** UN JETON UTILISABLE COMME CLÉ DE `Map` OU DE `Set`.
     *
     * JavaScript indexe par identité et n'appelle aucune méthode : deux clés égales mais
     * distinctes sont deux entrées. `hashKey()` du runtime rend un bigint qui replie le type
     * dans le hachage, et un bigint *est* comparé par valeur. C'est la seule façon de grouper
     * ou de dédupliquer, et elle n'a d'équivalent ni en C++ — où `operator<` suffit — ni en
     * Python, où `__hash__` et `__eq__` font le travail.
     */
    hashKey(): bigint {
        return this.value.hashKey();
    }

    toJSON(): dsviper.NativeValue {
        return this.value.toJSON();
    }

    toString(): string {
        return this.value.toString();
    }
}
