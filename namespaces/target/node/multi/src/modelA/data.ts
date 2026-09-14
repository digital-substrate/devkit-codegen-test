// A UNIT MODULE. `Material`, not `ModelA_Material`.
//
// Structurally Python's twin: module equals file, a cross-unit reference needs an
// import, and the spelling follows from it. What differs is only the data --
// `import { X } from './y.js'` against `from .y import X` -- which is the one place
// the two delegating targets genuinely share an implementation.

import * as dsviper from "@digitalsubstrate/dsviper";
import { Proxy } from "../data.js";          // the base
import * as mt from "../value_type.js";      // the base table, whole

export class Material extends Proxy<dsviper.ValueKey> {
    // ... unchanged ...
}

export class Colour extends Proxy<dsviper.ValueStructure> {
    // ... unchanged ...
}
