# templated — layer 1, in the direction that works

`Data.hpp.stg` renders the types of a unit. Its acceptance criterion is the file beside
it: `../hand/ModelA_Data.hpp`, written from the model without opening the generator's
output. The template must reproduce that, not the other way round.

```sh
java -jar ../../../../kibo/target/kibo-2.0.0.jar \
     -c cpp -n Topology -d ../../Topology.dsm.json -t . -o /tmp/out
diff <(grep -v '^//\|^$' ../hand/ModelA_Data.hpp) <(grep -v '^//\|^$' /tmp/out/ModelA_Data.hpp)
```

**It does.** What differs is the explanatory comments — which belong in the reference, not
in every generated file — and the parameter names on the operator declarations. The
declarations, the scopes, the qualifications and the includes match.

It is 80 lines and has no loop over namespaces, no dictionary, and no name built by
concatenation. `unit(u)` is called once per unit and the template says what a unit looks
like, which is what a template is for.

## Layer 2 — `Fields.hpp.stg`

Thirty lines, and it reproduces `../hand/ModelA_Fields.hpp` — except in two places where
**the template is right and the reference was wrong**, which is worth more than a match.

The reference included `ModelA_Data.hpp`. Nothing in it references the type `Colour`: the
declarations are `string_view` constants and functions returning a `Viper::Path`. A scope
named after a structure does not need the structure declared. The include was written out
of habit, and the template — written from what the content actually needs — does not
emit it.

The reference also omitted `<memory>`, and compiled only because `Viper_Path.hpp`
happened to pull it in.

**The acceptance criterion runs in both directions.** The reference is what the template
must reproduce, and the template is what checks the reference was thought through. Both
were corrected, and `../hand/f.cpp` compiles the result on its own.

## What writing it asked of the generator

**`u.dependencies` is too coarse, and this is the one that matters.**
`Projection_Data.hpp` comes out including `ModelC_Data.hpp`, which it does not use.
Projection reaches ModelC through an *attachment* — a layer-4 edge — and the dependency
set is the union over everything the unit declares. An artefact needs the dependencies of
**what it emits**, not of the unit that emits it.

`../hand/Projection_Fields.hpp` showed the same thing from the other side: it includes
neither driver unit although `Pair` holds a key from each, because a path names a position
and not a type. Two artefacts of one unit, two dependency sets.

**`parentNameInNamespace` cannot be called.** It dereferences the parent without checking,
so a concept that has none makes it throw, and the template has to guard on
`c.dsmConcept.parent` — reaching past the Template Model into the DSM layer to ask a
question the Template Model should answer. An accessor that cannot be called on every
element of the collection it belongs to is not an accessor.

**A template-authoring hazard, recorded because it cost time.** `>>` inside a `<<…>>`
body ends the template, so `std::hash<X>>` must be written `std::hash<X> >`. The
diagnostics reported it as `premature EOF` at a line thirty lines further on.
