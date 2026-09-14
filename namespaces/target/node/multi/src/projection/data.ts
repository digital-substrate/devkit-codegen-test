// The composing unit. Its imports are its dependency set, and the aliases carry the
// unit because both names are `Material`.

import { Material as ModelAMaterial } from "../modelA/data.js";
import { Material as ModelBMaterial } from "../modelB/data.js";
import { Proxy } from "../data.js";

export class Pair extends Proxy<dsviper.ValueStructure> {
    get a(): ModelAMaterial { /* ... */ }
    get b(): ModelBMaterial { /* ... */ }
}

export class Link extends Proxy<dsviper.ValueKey> { /* ... */ }
export class DerivedMaterial extends Proxy<dsviper.ValueKey> { /* ... */ }
