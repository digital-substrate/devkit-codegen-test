# crossing — the type system, across namespaces

`features/all.dsm` covers every shape of the type system in **one** namespace.
`namespaces/` covers namespace topology with **three** type shapes. Neither reaches the
place where the two meet, and that is where a namespace-based generator lives: a
`map<key<Core::Thing>, key<Parts::Thing>>` is a shape whose halves belong to different
units and which belongs to neither.

This model is that crossing. Three namespaces:

```
Core   ──  everything that cannot cross: numbers, ids, strings, blobs, vec, mat,
           an enumeration, a club, a concept and its local derived concept
Parts  ──  a second supplier, declaring the same names as Core and nothing else
Woven  ──  every composite shape, with its elements taken from both suppliers,
           twice over: once as a structure field, once as an attachment document
```

The two code paths are not the same, which is why every shape appears twice: a field is
written through its own accessor, while a document is encoded, decoded and
brace-initialised, and the templates branch on the document's shape.

`Woven` also carries the three corners at once — an attachment declared by one namespace,
keyed on a concept of a second, whose document type comes from a third.

## What it found on the day it was written

Five namespace-based templates had rendered and compiled against `namespaces/` for weeks.
Against this model, on the first render:

| defect | why the other models could not see it |
|---|---|
| the model's own namespace was hard-coded as `Topology` in a template | every model until now was called Topology |
| a derived concept was emitted **before** its parent | sorting is by name, and `SubThing` < `Thing` |
| layer 1 emits no club at all | no other multi-namespace model declares one |
| `key<any_concept>` comes out as a bare `AnyConceptKey` | it belongs to no namespace, so nothing qualified it |

The first two are fixed. The last two are open, and the second of them is the question
this whole line of work started from: a type that no namespace can claim.
