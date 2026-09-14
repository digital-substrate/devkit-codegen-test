// THE RE-EXPORT RULE in node, and the idiom is already half in place.
//
// index.ts today re-exports data flat and everything else under a name:
//
//     export * from "./data.js";
//     export * as types from "./value_type.js";
//     export * as path from "./path.js";
//
// The flat half works only because every class carries its namespace in its name.
// Remove the prefix and the same distinction has to be made per unit instead.

// Each unit reachable under its own name -- always, whether or not it collides.
export * as modelA from "./modelA/data.js";
export * as modelB from "./modelB/data.js";
export * as modelC from "./modelC/data.js";
export * as projection from "./projection/data.js";
export * as annotations from "./annotations/attachments.js";
export * as tools from "./tools/pool.js";
export * as projector from "./projector/pool.js";

// Flat, for the names exactly one unit declares.
export { Marker } from "./modelC/data.js";
export { Link, DerivedMaterial, Pair } from "./projection/data.js";

// NOT flat: Material and Colour are declared by modelA and modelB both. Reach them
// as modelA.Material. In a mono-namespace model nothing collides and this section is
// empty, so the 99% get the flat surface they have today, minus the prefix.

// The base layer keeps its own names, as today.
export * as types from "./value_type.js";
export * as definitions from "./definitions.js";
