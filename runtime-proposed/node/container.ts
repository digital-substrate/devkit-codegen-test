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
 * ET NOMMÉES, PARCE QU'UNE VUE SEULE NE SUFFIT PAS. Elle enveloppe la valeur d'un champ qui
 * existe déjà ; elle ne permet pas d'écrire `new Vector_uint8([1, 2, 3])`, donc pas de
 * construire un conteneur pour le passer à une fonction de pool ni de bâtir un document avant
 * de l'attacher. La fabrique en bas lie une vue générique à un descripteur : un *nom* par
 * forme, pas une classe.
 *
 * UNE VUE ET NON UNE COPIE. La donnée reste dans la Value : `c.fVector.at(0)` construit un
 * `Colour` au moment où on le demande, et `push` écrit dans la Value.
 */
import dsviper from "@digitalsubstrate/dsviper";

import { definitionsOf, unwrap, wrap } from "./registry.js";

/** Ce que les quatre vues ont en commun, et qui vient de la Value.
 *
 * Le type, l'encodage, la copie, l'empreinte : aucun ne dépend de la forme du conteneur. Ce
 * sont des questions posées à la valeur, et la vue ne fait que les transmettre — une vue
 * obtenue d'un champ doit y répondre comme une vue construite par son nom, puisque c'est la
 * même valeur derrière.
 */
export class View {
    readonly vprValue: dsviper.Value;

    constructor(value: dsviper.Value) {
        this.vprValue = value;

        // LA VUE NE CHOISIT PAS CE QUI PASSE. Un ensemble a `isdisjoint`, `union`, `min` ; un
        // xarray a `positionOf`, `toVector`, `disablePosition` ; les nommer un par un
        // reviendrait à recopier le runtime et à se périmer au premier ajout. Un `Proxy` est
        // ce que JavaScript offre là où Python a `__getattr__` : ce qui n'est pas de la vue
        // est demandé à la valeur, enveloppé au retour, déballé à l'aller.
        //
        // LA CHAÎNE DE PROTOTYPES EST CELLE DE LA CIBLE, donc `instanceof` continue de dire
        // vrai — c'est ce qui permet de l'employer sans rien perdre du typage.
        return new globalThis.Proxy(this, {
            get(view, name, receiver) {
                if (name in view || typeof name === "symbol") {
                    return Reflect.get(view, name, receiver);
                }
                if (view instanceof Variant) {
                    const arm = view.arm(name);
                    if (arm !== undefined) {
                        return arm;
                    }
                }
                const inner = (view.vprValue as unknown as Record<string, unknown>)[name];
                if (typeof inner !== "function") {
                    return inner === undefined ? undefined : wrap(inner as dsviper.OutputValue);
                }
                return (...args: unknown[]) => {
                    const result = (inner as (...a: unknown[]) => unknown)
                        .apply(view.vprValue, args.map(unwrap));
                    return result instanceof dsviper.Value ? wrap(result) : result;
                };
            },
        });
    }

    type(): dsviper.Type {
        return this.vprValue.type();
    }

    hash(): bigint {
        return this.vprValue.hash();
    }

    hashKey(): bigint {
        return this.vprValue.hashKey();
    }

    equals(other: unknown): boolean {
        const compared = other instanceof View ? other.vprValue : other;
        // NE PAS DEMANDER AU RUNTIME CE QU'IL NE PEUT PAS RÉPONDRE. Comparer une suite à un
        // entier le fait lever, et une question deviendrait une erreur.
        if (compared === null || compared === undefined) {
            return false;
        }
        try {
            return this.vprValue.equals(compared);
        } catch {
            return false;
        }
    }

    encode(streamCodecInstancing?: dsviper.StreamCodecInstancing): dsviper.ValueBlob {
        return dsviper.Value.encode(this.vprValue, streamCodecInstancing);
    }

    hexdigest(): string {
        return dsviper.Value.hexdigest(this.vprValue);
    }

    copy(): this {
        return new (this.constructor as new (value: dsviper.Value) => this)(
            (this.vprValue as unknown as { copy(): dsviper.Value }).copy());
    }

    toJSON(): dsviper.NativeValue {
        return this.vprValue.toJSON();
    }

    toString(): string {
        return this.vprValue.toString();
    }
}

/** La surface commune aux quatre suites du runtime : `size`, `at`, `contains`, l'itération. */
interface Suite extends Iterable<dsviper.OutputValue> {
    size(): number;
    // UNE MATRICE PREND DEUX RANGS ET LES AUTRES UN SEUL : la signature commune est celle qui
    // les admet tous, et c'est la valeur qui refuse une arité qu'elle ne connaît pas.
    at(...position: number[]): dsviper.OutputValue;
    contains(value: dsviper.InputValue): boolean;
}

/** Une suite du runtime — vector, set, vec, tuple — dont les éléments portent leurs noms. */
export class Sequence<E> extends View {
    private get suite(): Suite {
        return this.vprValue as unknown as Suite;
    }

    get size(): number {
        return this.suite.size();
    }

    get length(): number {
        return this.suite.size();
    }

    at(...position: number[]): E {
        // UNE MATRICE S'INDEXE PAR COLONNE ET PAR LIGNE, les autres suites par un seul rang.
        return wrap(this.suite.at(...position));
    }

    has(element: E): boolean {
        return this.suite.contains(unwrap(element));
    }

    *[Symbol.iterator](): Iterator<E> {
        const type = this.vprValue.type() as unknown as { columns?(): number; rows?(): number };
        if (typeof type.columns === "function" && typeof type.rows === "function") {
            // UNE MATRICE EST UNE SUITE DE COLONNES, et non une suite de nombres : la parcourir
            // à plat perdrait la forme que le modèle lui donne.
            for (let column = 0; column < type.columns(); column += 1) {
                const held: unknown[] = [];
                for (let row = 0; row < type.rows(); row += 1) {
                    held.push(wrap(this.suite.at(column, row)));
                }
                yield held as E;
            }
            return;
        }
        for (const element of this.suite) {
            yield wrap(element);
        }
    }

    toArray(): E[] {
        return [...this];
    }

    /** Une ligne d'une matrice, telle qu'on l'écrit.
     *
     * LE RUNTIME RANGE PAR COLONNES, ET UN LITTÉRAL SE LIT PAR LIGNES. `[[1, 2], [3, 4]]`
     * donne `row(0) === [1, 2]` pour qui l'a écrit ; le runtime appelle ça sa première
     * colonne. Suivre ce que l'appelant a écrit plutôt que la disposition interne est ce qui
     * évite une transposition silencieuse.
     */
    row(index: number): unknown[] {
        const type = this.vprValue.type() as unknown as { rows(): number };
        const held: unknown[] = [];
        for (let position = 0; position < type.rows(); position += 1) {
            held.push(this.at(index, position));
        }
        return held;
    }

    setRow(index: number, elements: unknown[]): void {
        const inner = this.vprValue as unknown as { set(c: number, r: number, v: unknown): void };
        elements.forEach((element, position) => inner.set(index, position, unwrap(element)));
    }

    /** Ce que la valeur sait faire et que la vue ne nomme pas.
     *
     * LA VUE NE CHOISIT PAS CE QUI PASSE. Un ensemble a `isdisjoint`, `union`, `min` ; un
     * vecteur en a d'autres ; les nommer un par un reviendrait à recopier le runtime et à se
     * périmer au premier ajout.
     */
    call(name: string, ...args: unknown[]): unknown {
        return forward(this, name, args);
    }
}

/** Une map du runtime, dont les clés et les valeurs portent leurs noms.
 *
 * ELLE N'EST PAS UNE `Map` DE JAVASCRIPT, ET NE PEUT PAS L'ÊTRE. Une `Map` indexe par identité
 * et n'appelle aucune méthode : deux clés égales mais distinctes y seraient deux entrées. La
 * correspondance du runtime indexe par valeur — c'est pour ça qu'on la garde.
 */
export class Mapping<K, V> extends View {
    private get map(): dsviper.ValueMap {
        return this.vprValue as dsviper.ValueMap;
    }

    get size(): number {
        return this.map.size();
    }

    at(key: K): V {
        return wrap(this.map.at(unwrap(key)));
    }

    get(key: K, fallback?: V): V | undefined {
        const held = this.map.get(unwrap(key));
        return held === undefined ? fallback : wrap(held);
    }

    set(key: K, element: V): void {
        this.map.set(unwrap(key), unwrap(element));
    }

    has(key: K): boolean {
        return this.map.contains(unwrap(key));
    }

    remove(key: K): void {
        this.map.remove(unwrap(key));
    }

    clear(): void {
        this.map.clear();
    }

    keys(): K[] {
        return [...this];
    }

    values(): V[] {
        return this.entries().map(([, element]) => element);
    }

    entries(): [K, V][] {
        return [...this.pairs()];
    }

    /** ITÉRER REND LES CLÉS, comme une `Map` de JavaScript et un `dict` de Python.
     *
     * La map du runtime, elle, rend des paires ; `entries()` est là pour ça. Les deux langages
     * voisins rendent les clés, et suivre le runtime ici obligerait chaque appelant à défaire
     * une paire dont il ne voulait pas.
     */
    *[Symbol.iterator](): Iterator<K> {
        for (const pair of this.map as unknown as Iterable<dsviper.OutputValue>) {
            const [key] = pair as unknown as [dsviper.OutputValue, dsviper.OutputValue];
            yield wrap(key);
        }
    }

    /** Les paires clé/valeur, telles que le runtime les tient. */
    *pairs(): Generator<[K, V]> {
        for (const pair of this.map as unknown as Iterable<dsviper.OutputValue>) {
            const [key, element] = pair as unknown as [dsviper.OutputValue, dsviper.OutputValue];
            yield [wrap(key), wrap(element)];
        }
    }

    call(name: string, ...args: unknown[]): unknown {
        return forward(this, name, args);
    }
}

/** Un xarray du runtime : une suite dont chaque place a une identité stable.
 *
 * LA POSITION EST LA CLÉ, et c'est tout ce qui le distingue d'un `vector`. Deux éditeurs qui
 * insèrent au même endroit n'écrasent pas l'insertion l'un de l'autre.
 */
export class Ordered<E> extends View {
    private get ordered(): dsviper.ValueXArray {
        return this.vprValue as dsviper.ValueXArray;
    }

    static readonly END = dsviper.ValueXArray.END;

    static end(): dsviper.ValueUUId {
        return dsviper.ValueXArray.END;
    }

    static createPosition(): dsviper.ValueUUId {
        return dsviper.ValueXArray.createPosition();
    }

    /** Le nombre d'éléments — et la fin n'en est pas un.
     *
     * `positions()` rend aussi `END`, la place d'après le dernier, parce qu'on y insère. La
     * compter ferait un élément de plus dans un ordonné vide, ce qui est visiblement faux.
     */
    get size(): number {
        return this.elementPositions().length;
    }

    positions(): dsviper.ValueUUId[] {
        return this.ordered.positions();
    }

    private elementPositions(): dsviper.ValueUUId[] {
        return this.positions().filter(
            (p) => !p.equals(dsviper.ValueXArray.END) && this.ordered.at(p) !== undefined);
    }

    position(index: number): dsviper.ValueUUId | undefined {
        // Un index négatif compte depuis la fin, comme `Array.prototype.at` et comme `xa[-1]`
        // en Python. La liaison déclare l'index en uint64 et lève sur un négatif : on le ramène.
        const i = index < 0 ? this.ordered.size() + index : index;
        return i < 0 ? undefined : this.ordered.position(i);
    }

    indexOf(position: dsviper.ValueUUId): number | undefined {
        return this.ordered.index(position);
    }

    hasPosition(position: dsviper.ValueUUId): boolean {
        return this.ordered.hasPosition(position);
    }

    at(where: dsviper.ValueUUId | number): E | undefined {
        const position = typeof where === "number" ? this.position(where) : where;
        if (position === undefined) {
            return undefined;
        }
        const element = this.ordered.at(position);
        return element === undefined ? undefined : wrap(element);
    }

    /** L'élément à cette position, ou `undefined` — le même que `at`, sous le nom que le
     *  pack emploie. Deux mots pour une question qui n'en est qu'une. */
    get(where: dsviper.ValueUUId | number): E | undefined {
        return this.at(where);
    }

    set(where: dsviper.ValueUUId | number, element: E): void {
        const position = typeof where === "number" ? this.position(where) : where;
        if (position === undefined) {
            throw new RangeError(`aucune place au rang ${String(where)}`);
        }
        this.ordered.set(position, unwrap(element));
    }

    insert(beforePosition: dsviper.ValueUUId, element: E,
           newPosition?: dsviper.ValueUUId): dsviper.ValueUUId {
        return newPosition === undefined
            ? this.ordered.insert(beforePosition, unwrap(element))
            : this.ordered.insert(beforePosition, unwrap(element), newPosition);
    }

    append(element: E): dsviper.ValueUUId {
        return this.ordered.append(unwrap(element));
    }

    remove(position: dsviper.ValueUUId): void {
        this.ordered.remove(position);
    }

    /** Les paires position/élément, dans l'ordre.
     *
     * LA FIN N'EST PAS UNE PLACE : `positions()` la rend parce qu'on y insère, et la compter
     * ferait un élément de plus à chaque parcours.
     */
    /** Le xarray à plat, sous le type que le modèle lui donne.
     *
     * LA CLASSE EST CELLE QUE L'UNITÉ A DÉCLARÉE, ET NON UNE NOUVELLE. Lier à la volée rendrait
     * une classe distincte à chaque appel, donc `instanceof Vector_uint8` serait faux pour un
     * vecteur pourtant de cette forme. La table des formes est cherchée par le type, ce qu'on
     * ne peut faire qu'ici — au chargement, elle n'est pas encore remplie.
     */
    toVector(): Sequence<E> {
        const flat = this.ordered.toVector();
        const known = boundFor(Sequence, flat.type());
        return known === undefined
            ? new Sequence<E>(flat)
            : new (known as new (v: unknown) => Sequence<E>)(flat);
    }

    items(): [dsviper.ValueUUId, E | undefined][] {
        return this.elementPositions().map((position) => [position, this.at(position)]);
    }

    *[Symbol.iterator](): Iterator<E> {
        for (const element of this.ordered as unknown as Iterable<dsviper.OutputValue>) {
            yield wrap(element);
        }
    }

    call(name: string, ...args: unknown[]): unknown {
        return forward(this, name, args);
    }
}

/** Une valeur, ou rien.
 *
 * UNE VUE À ELLE, ET NON UNE SUITE. Un `optional` pose une question qu'aucun autre conteneur
 * ne pose — « y a-t-il quelque chose ? » — et trois opérations en découlent.
 */
export class Optional<E> extends View {
    private get optional(): dsviper.ValueOptional {
        return this.vprValue as dsviper.ValueOptional;
    }

    isNil(): boolean {
        return this.optional.isNil();
    }

    unwrap(): E {
        return wrap(this.optional.unwrap());
    }

    wrap(element: E): void {
        this.optional.wrap(unwrap(element));
    }

    get(fallback?: E): E | undefined {
        if (this.isNil()) {
            return fallback;
        }
        return this.unwrap();
    }

    clear(): void {
        this.optional.clear();
    }
}

/** L'une de plusieurs alternatives, et celle qui est tenue. */
export class Variant<E> extends View {
    private get variant(): dsviper.ValueVariant {
        return this.vprValue as dsviper.ValueVariant;
    }

    unwrap(): E {
        return wrap(this.variant.unwrap());
    }

    wrap(element: E, type?: dsviper.Type): void {
        if (type === undefined) {
            this.variant.wrap(unwrap(element));
        } else {
            this.variant.wrap(unwrap(element), type);
        }
    }

    /** L'alternative tenue, si c'est celle qu'on demande. */
    as<T>(type: dsviper.Type): T {
        const held = this.variant.unwrap(false) as dsviper.Value;
        if (!held.type().equals(type)) {
            throw new RangeError(`le variant tient un ${held.type().representation()}, `
                                 + `pas un ${type.representation()}`);
        }
        return wrap(held);
    }

    holds(type: dsviper.Type): boolean {
        return (this.variant.unwrap(false) as dsviper.Value).type().equals(type);
    }

    /** `setString`, `getString`, `isString` — dérivés des alternatives que le type porte.
     *
     * LE PACK EN ÉMET TROIS PAR ALTERNATIVE DE CHAQUE VARIANT DU MODÈLE. Le type du variant
     * les connaît : le nom demandé désigne l'une d'elles ou n'existe pas, et le dire ici coûte
     * une recherche au lieu d'une classe par combinaison.
     */
    arm(name: string): ((...args: unknown[]) => unknown) | undefined {
        for (const prefix of ["set", "get", "is"]) {
            if (!name.startsWith(prefix)) {
                continue;
            }
            const wanted = name.slice(prefix.length);
            for (const alternative of (this.variant.type() as dsviper.TypeVariant).types()) {
                if (armName(alternative) !== wanted) {
                    continue;
                }
                if (prefix === "set") {
                    return (...args) => this.variant.wrap(unwrap(args[0]), alternative);
                }
                if (prefix === "get") {
                    return () => this.as(alternative);
                }
                return () => this.holds(alternative);
            }
        }
        return undefined;
    }
}

/** Le nom d'une alternative, tel qu'un appelant l'écrit : `Demo::StructureS` → `Demo_StructureS`. */
function armName(type: dsviper.Type): string {
    const raw = type.representation().replace("::", "_");
    return raw.charAt(0).toUpperCase() + raw.slice(1);
}

function forward(view: View, name: string, args: unknown[]): unknown {
    const inner = (view.vprValue as unknown as Record<string, unknown>)[name];
    if (typeof inner !== "function") {
        throw new TypeError(`ni la vue ni ${view.vprValue.type().representation()} n'ont '${name}'`);
    }
    const result = (inner as (...a: unknown[]) => unknown).apply(view.vprValue, args.map(unwrap));
    return result instanceof dsviper.Value ? wrap(result) : result;
}

// ── un conteneur nommé, et constructible ──

type Bound<V> = {
    new (value?: unknown): V;
    type(): dsviper.Type;
    decode(blob: dsviper.ValueBlob): V;
};

const bound = new Map<() => dsviper.Type, unknown>();

/** La classe liée à cette forme, si une unité l'a déclarée.
 *
 * CHERCHÉE PAR LE TYPE ET NON PAR LA FONCTION, parce que l'appelant tient une valeur et pas la
 * fonction qui l'a nommée. Le parcours n'est possible qu'après chargement — évaluer un
 * descripteur pendant qu'un module s'initialise le prendrait en pleine zone morte.
 */
function boundFor(view: unknown, type: dsviper.Type): unknown {
    for (const [typeOf, held] of bound) {
        if (Object.getPrototypeOf(held as object) === view && typeOf().equals(type)) {
            return held;
        }
    }
    return undefined;
}

/** Une vue liée à un type : nommable, constructible, et qui refuse ce qui n'est pas d'elle.
 *
 * MÉMOÏSÉE PAR FORME. Deux appels pour le même type rendraient deux classes distinctes, et
 * `instanceof` deviendrait faux entre deux valeurs pourtant de la même forme.
 */
function bind<V extends View>(view: new (value: dsviper.Value) => V,
                              typeOf: () => dsviper.Type,
                              build: (type: dsviper.Type, value: unknown) => dsviper.Value): Bound<V> {
    // MÉMOÏSÉE SUR LA FONCTION, ET NON SUR LE TYPE QU'ELLE REND. L'appeler ici la ferait
    // s'exécuter au chargement du module, avant que les définitions soient prêtes -- le paquet
    // les déclare pendant son propre chargement, et la lecture arriverait en pleine zone morte
    // temporelle. Le modèle rendu déclare une fonction par forme, donc son identité *est* la
    // forme, et la table reste juste sans rien évaluer.
    const cached = bound.get(typeOf);
    if (cached !== undefined) {
        return cached as Bound<V>;
    }

    class Lié extends (view as new (value: dsviper.Value) => View) {
        constructor(value?: unknown) {
            const given = unwrap(value);
            if (given instanceof dsviper.Value && given.type().equals(typeOf())) {
                super(given);
                return;
            }

            // DEUX FAÇONS DE SE TROMPER, ET UNE SEULE EST UNE ERREUR. `new Optional_X(s)` donne
            // l'élément et non le conteneur, ce que le runtime sait bâtir ; `new
            // Vector_uint8(vectorInt8)` donne un conteneur d'un autre type, et là il n'y a rien
            // à bâtir. Laisser le runtime trancher, et traduire son refus dans le `TypeError`
            // que le contrat annonce.
            let built: dsviper.Value;
            try {
                built = build(typeOf(), given);
            } catch (refus) {
                throw new TypeError(`cette valeur n'est pas un ${typeOf().representation()}`,
                                    { cause: refus });
            }

            // ET VÉRIFIER CE QUI EST SORTI. `Value.create` de la liaison Node rend un
            // `set<string>` quand on lui demande un `set<uint8>` : il ignore le type demandé au
            // lieu de refuser, là où la liaison Python lève. Sans ce contrôle une valeur du
            // mauvais type entrerait dans une vue qui annonce l'autre, et le fail-fast serait
            // en place et désarmé — la pire des deux situations.
            if (!built.type().equals(typeOf())) {
                throw new TypeError(`cette valeur n'est pas un ${typeOf().representation()} `
                                    + `mais un ${built.type().representation()}`);
            }
            super(built);
        }

        static type(): dsviper.Type {
            return typeOf();
        }

        static decode(blob: dsviper.ValueBlob): View {
            return new Lié(dsviper.Value.decode(blob, typeOf(), definitionsOf()));
        }
    }

    bound.set(typeOf, Lié);
    return Lié as unknown as Bound<V>;
}

// CHAQUE FORME SE BÂTIT PAR SON PROPRE CONSTRUCTEUR. `Value.create` sait faire un vecteur
// depuis un tableau mais refuse un xarray -- « vector expects an array » -- parce que la place
// d'un élément y est une identité et non un rang. Passer par la classe de la forme, c'est
// laisser le runtime dire comment elle se construit plutôt que le supposer.
export const sequenceOf = <E>(typeOf: () => dsviper.Type) =>
    bind<Sequence<E>>(Sequence as never, typeOf,
                      (t, v) => dsviper.Value.create(t, v as dsviper.InputValue));
export const mappingOf = <K, V>(typeOf: () => dsviper.Type) =>
    bind<Mapping<K, V>>(Mapping as never, typeOf,
                        (t, v) => new dsviper.ValueMap(t as dsviper.TypeMap, v as dsviper.InputValue));
export const orderedOf = <E>(typeOf: () => dsviper.Type) =>
    bind<Ordered<E>>(Ordered as never, typeOf,
                     (t, v) => new dsviper.ValueXArray(t as dsviper.TypeXArray, v as dsviper.InputValue));
export const optionalOf = <E>(typeOf: () => dsviper.Type) =>
    bind<Optional<E>>(Optional as never, typeOf,
                      (t, v) => new dsviper.ValueOptional(t as dsviper.TypeOptional, v as dsviper.InputValue));
export const variantOf = <E>(typeOf: () => dsviper.Type) =>
    bind<Variant<E>>(Variant as never, typeOf,
                     (t, v) => new dsviper.ValueVariant(t as dsviper.TypeVariant, v as dsviper.InputValue));
