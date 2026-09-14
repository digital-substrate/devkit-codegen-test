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

## Layer 3 — `Codec.hpp.stg`

Three declarations per type, and that is a namespace's whole part in the bridge. Forty
lines, matching `../hand/ModelA_Codec.hpp` but for ordering and alignment.

**`Projection_Codec.hpp` contains no mention of `std::map`** — checked, zero occurrences —
although Projection is the namespace that declares an attachment of
`map<key<ModelA::Material>, key<ModelB::Material>>`. There is nothing to emit for it: the
runtime's generic `write(Writer&, std::map<K,V>)` walks it and ADL sends each half to its
owner. The shape that forced a base layer into existence produces no line in any template.

It includes `ModelA_Codec.hpp` and `ModelB_Codec.hpp`, from `dependencies.types`, because
`Pair` holds a key from each — the same axis as layer 1, a different artefact to reach.

**A StringTemplate hazard with a visible cost.** A `>>` in emitted text closes a `<<…>>`
body, so `tag<Colour>` cannot be written in one. The first draft wrote `tag<Colour >`,
which is valid C++ and a workaround leaking into the output. `<%…%>` has different
delimiters and takes the text as written. Worth knowing before a pack fills up with
spaces nobody can explain.

## Layer 4 — `Attachments.hpp.stg`, `Pool.hpp.stg`

**A namespace level cannot hold a qualified name.** `Annotations` declares an attachment
on `ModelA::Material`, and the scope wants to be
`Annotations::Attachments::ModelA::Material::note` — which would create
`Annotations::ModelA`. So the concept's origin has to be flattened into the level's name:
`ModelA_Material`. The flat prefix, once, for a reason that holds.

It happens **on principle, not on demand**. The pack flattens only when two attachments
would otherwise collide, which makes a scope name a function of the whole namespace's
attachment set — adding one attachment renames another, and a caller that named the first
stops compiling for a change that did not touch it. Here `ModelA::Attachments::Material`
stays bare because the concept is ModelA's own, and `Annotations::Attachments::ModelA_Material`
carries the origin because it is not.

**And a template cannot decide that.** StringTemplate has no string comparison, so "is
this concept mine?" is a question only the model can answer —
`TemplateAttachment.getConceptScope()`, added for this.

**A pool has a dependency set, and the model does not expose it.**
`Projector_Pool.hpp` comes out including the whole model's `Data` because
`p.model.include.Data` is the only thing available, when `Projector::link(ModelA::MaterialKey,
ModelB::MaterialKey)` needs exactly ModelA's and ModelB's. The signatures say which units
a pool reaches, and nothing collects it — the same gap the namespace dependency graph had
before `9328acd`, in the one place that graph does not look.

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

## Layer 5 — `Test.hpp.stg`

One `fuzz` declaration per declared type, and the `test(Rng&)` a driver calls. Thirty-five
lines, mirroring `Codec.hpp.stg` line for line, which is the check on the four layers
below it: templatising the tests needed no idea the codec had not already needed.

`Annotations_Test.hpp` comes out with no `fuzz` at all and an empty `test()`, which is
right — a namespace that declares only attachments has no type of its own to round-trip,
and its attachments' document types are round-tripped by whoever declares them.

**The codec include is load-bearing, and unlike layer 2 that is now checked.** Nothing in
`ModelA_Test.hpp`'s *declarations* names anything from `ModelA_Codec.hpp`, so by the layer-2
rule — emit what the content needs — it should not be there. It must be. The header exists
so that a consumer can instantiate `roundTrip<ModelA::Colour>`, and that instantiation
resolves `write` and `read` by ADL at the point of instantiation, where the declarations
have to be visible. Deleting the include and compiling `../hand/l5.cpp` gives
`no matching function for call to 'write'`. An include is justified by what the header
makes possible, not only by what it says.

## Compiling the rendered output, for the first time

The templates had been checked against the reference by reading. Layer 5 came with a
consumer, so the whole rendered tree went through the compiler — hand-written `Viper_*`
stubs, generated everything else, `use.cpp`, `bridge.cpp`, `l4.cpp`, `l5.cpp`, `f.cpp`.

**Layer 1 was wrong in a way no diff had shown.** `std::hash` specialisations stand
*outside* the namespace, so the type has to be qualified, and the template emitted
`std::hash<Material>` — undeclared at that point — instead of `std::hash<ModelA::MaterialKey>`.
Two bugs in one line: the missing qualification, and a concept spelled without its `Key`.
A third was next to them: a key hashes through its member `hash()`, a structure through the
free `hash()` of its namespace, and the template used the member form for both.

The reference has it right on every count, and the diff against it had been read four times
without anyone seeing it. **Reading a template against a reference finds what the reference
says; only a compiler finds what it does not.**

Fixed, and `use.cpp` and `bridge.cpp` now compile against the generated tree —
`bridge.cpp` for the first time anywhere, since `../hand/` never had a `ModelB_Codec.hpp`
to satisfy it.

**And the layer-4 pool gap was not an over-include, it was a dangling one.** `l4.cpp` failed
on `Tools_Pool.hpp:8: 'Topology_Data.hpp' file not found` — `p.model.include.Data` named a
model-wide artefact no namespace-based template produces, so no generated pool header could
be included at all.

Fixed: a pool now carries `dependencies.functions`, the namespaces its own signatures reach.
`Projector` includes `ModelA_Data.hpp` and `ModelB_Data.hpp`, `LinkModel` includes
`Projection_Data.hpp`, and `Tools` — whose signatures name no namespaced type — includes
nothing. A third kind of declaration beside `types` and `attachments`, so both kinds of unit
are asked the same question and the wrong kind answers with an empty list.

**One more invention removed from the reference.** `../hand/ModelA_Attachments.hpp` declared
`set(mutating, key, path, value)`, to motivate layer 2. Nothing in the pack has it, and it
could not be generated anyway: it would take one overload per field type of every document.
Writing one field is real, but it is the runtime's operation — a path and an encoded value go
to the mutating interface, one signature covering every field of every document. Layer 2
exists for that caller, not for a declaration in a unit.

**The whole generated tree now compiles**: `use.cpp`, `bridge.cpp`, `l4.cpp`, `l5.cpp`,
`f.cpp`, against generated headers and hand-written `Viper_*` stubs.
