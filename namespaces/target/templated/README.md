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
