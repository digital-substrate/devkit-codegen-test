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

    /** Ce qui vient de la valeur et ne dépend d'aucun type : l'encodage, la copie, l'empreinte.
     *
     * DEUX BASES, LA MÊME SURFACE. `Proxy` enveloppe une valeur nommée — une structure, une
     * clé — et `View` un conteneur ; elles diffèrent par ce qu'elles offrent en propre et pas
     * par ce qu'elles transmettent. Une structure qui ne sait pas s'encoder alors qu'un
     * vecteur le sait serait une asymétrie que rien ne justifie.
     */
    encode(streamCodecInstancing?: dsviper.StreamCodecInstancing): dsviper.ValueBlob {
        return dsviper.Value.encode(this.value, streamCodecInstancing);
    }

    hexdigest(): string {
        return dsviper.Value.hexdigest(this.value);
    }

    copy(): this {
        return new (this.constructor as new (value: V) => this)(
            (this.value as unknown as { copy(): V }).copy());
    }

    type(): dsviper.Type {
        return this.value.type();
    }

    hash(): bigint {
        return this.value.hash();
    }

    toString(): string {
        return this.value.toString();
    }
}

/** Une clé sur une instance de n'importe quel concept.
 *
 * LE C++ EN GÉNÈRE UNE PAR MODÈLE ; ICI IL N'EN FAUT AUCUNE. Elle ne nomme aucun type : elle
 * enveloppe un `ValueKey` et pose ses questions au descripteur que la valeur porte déjà. Ce
 * qu'une version générée y ajoutait — savoir nommer les concepts du modèle — est dans les
 * définitions embarquées, lues à l'exécution, ce qui la rend juste aussi pour un descendant
 * apparu après la génération.
 */
export class AnyConceptKey extends Proxy<dsviper.ValueKey> {
    constructor(value: dsviper.ValueKey) {
        super(value);
    }

    static wrap(value: dsviper.Value): AnyConceptKey {
        return new AnyConceptKey(dsviper.ValueKey.cast(value));
    }

    instanceId(): dsviper.ValueUUId {
        return this.value.instanceId();
    }

    runtimeId(): dsviper.ValueUUId {
        return this.value.typeConcept().runtimeId();
    }

    isValid(): boolean {
        return this.value.instanceId().isValid();
    }

    description(): string {
        return `${this.value.instanceId().encoded()}:AnyConceptKey`
             + `(${this.value.typeConcept().representation()}Key)`;
    }

    /** La clé vue comme celle d'un concept donné, ou `undefined` si elle n'en est pas une. */
    as<K>(concept: { type(): dsviper.TypeKey; wrap(value: dsviper.Value): K }): K | undefined {
        return this.value.type().equals(concept.type()) ? concept.wrap(this.value) : undefined;
    }

    override toString(): string {
        return this.description();
    }
}
