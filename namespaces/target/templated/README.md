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

## Layer 4, the implementation — `Attachments.cpp.stg`

The first implementation template, and the one that says whether any of the headers above
meant anything. It reproduces `../hand/ModelA_Attachments.cpp`; what differs is the comments,
the line wrapping, and one qualification the template cannot avoid — the reference writes
`Fields::Colour::rPath()` from inside the unit, the template writes
`ModelA::Fields::Colour::rPath()`, because the document structure may belong to another unit
and only a fully qualified name is right in both cases.

**Every generated implementation compiles**, on all five namespaces, and the object file of
`Projection_Attachments.cpp` carries this symbol:

```
Topology::Codec::type<ModelA::MaterialKey, ModelB::MaterialKey>(
    Viper::Codec::tag<std::map<ModelA::MaterialKey, ModelB::MaterialKey, …>>)
```

One template of the injected module, instantiated. Not a generated function called
`encode_map_ModelA_MaterialKey_to_ModelB_MaterialKey`. That name is where this whole
question started, and it is gone from the output, not renamed.

### Three defects the implementation found, none of them visible in a header

**A container needs a type descriptor, and no namespace can supply one.** Compiling
`Projection_Attachments.cpp` failed on `mapping`, whose document is
`map<key<ModelA::Material>, key<ModelB::Material>>`: encoding it asks for its type, and
there is nobody to ask — ModelA cannot claim a map whose value is ModelB's, and ModelB
cannot claim one whose key is ModelA's. It belongs to the injected module, for the reason
that was stated long before it could be checked: vector, set and map are std's, so they are
std containers, and no unit of the model owns one. The shape the fixture exists to produce
produced it, and the compiler said so rather than a design argument.

**The header template still had the first draft's surface** — a `remove` the runtime does
not offer, and no `diff`, no per-field setters. The hand-written header had been corrected;
the template had not, and nothing compared them until a caller needed both.

**A multi-line documentation was emitted with `///` on the first line only**, so the
remaining lines landed in the code: `unknown type name 'generator'`, from a docstring in the
model. Every `///` taking a model string had it. Now `/** … */`, which needs nothing from the
model. Present in `Data.hpp.stg` too, and in the pack.

## Layer 3, the implementation — `Codec.cpp.stg`

Three functions per declared type, matching `../hand/ModelA_Codec.cpp` but for ordering. All
five namespaces compile, and `Projection::Pair` reads as
`{read(r, tag<ModelA::MaterialKey>{}), read(r, tag<ModelB::MaterialKey>{})}` — each half sent
to its owner by the argument, with nothing in the text naming either unit.

**The template found a bug the reference had hidden by hand.** Reading a structure into one
local per field, named after the field, gives `auto const r{read(r, …)}` when the field is
called `r` — reading a variable inside its own initialiser. The pack is safe from it because
its reader is `this`; the free-function form is not, and `ModelA::Colour` has that very field.
The hand-written reference had chosen `red`, `green`, `blue` without thinking about it, which
is not a choice a generator can make. Both now emit one braced-init-list, which the language
guarantees to evaluate left to right, and name nothing.

**Two StringTemplate hazards, both silent until they are not.** `i0` exists only inside an
anonymous sub-template, so a named one gets `implicitly-defined attribute i0 not visible` —
pass it explicitly through `{m|<m:sub(e, i0)>}`. And an anonymous sub-template eats one space
after the `|`, so `{m|    <m.name>}` indents by three; a named sub-template keeps all four.

**Layer 1 was emitting no enumeration at all**, which no render had shown because no namespace
declared one. Adding `enum Finish` to `ModelA` exercised every template for the first time.

## The club, the untyped key, and a layer nobody had asked for

`Data.hpp.stg` gains the club, `Data.cpp.stg` and `Model.hpp.stg`/`Model.cpp.stg` are new,
and every generated file of both multi-namespace models compiles — with one exception,
below.

**The club renders the crossing case correctly.** `Woven::Weave` has `Core::Thing` and
`Parts::Thing` as members:

```cpp
WeaveKey(Core::ThingKey const & key) noexcept;
WeaveKey(Parts::ThingKey const & key) noexcept;
std::optional<Core::ThingKey>  asCoreThingKey()  const noexcept;
std::optional<Parts::ThingKey> asPartsThingKey() const noexcept;
```

Conversions on the club, never on the member — a member may live in a unit that knows
nothing of the club's and that the club's depends on. And the getter names carry the
member's unit because two members are called `Thing` and a function name cannot hold `::`.
That flat prefix depends only on the member, so adding one never renames another's getter.

**`Model.hpp` is a layer the decomposition had not foreseen.** A unit's runtime ids and type
descriptors were sitting with the codec, because the codec asked for them. But `create()`
needs its concept's id and `from()` needs its descriptor, and the types layer serialises
nothing. They are not codec functions. They live in namespace `<unit>` and not
`<unit>::Model`, because `type(tag<T>)` has to be reachable by argument-dependent lookup
from the injected module, and lookup associates the type's namespace, not its sub-scopes.

### What compiling the crossing model found

**An enumeration was declared by reference and defined by value.** `Codec.hpp.stg` emitted
`write(Writer&, Grade const &)` and `Codec.cpp.stg` emitted `write(Writer&, Grade)`. Two
overloads, so the call site is *ambiguous* rather than unresolved — a diagnostic that never
names what is missing. Split into its own sub-template.

**An enumeration had no hash at all.** Layer 1 hashed concepts, clubs and structures, and a
structure holding an enumeration field did not compile.

**An implementation file needs the model identities of the units it reaches**, not only
their codecs. `Parts_Attachments.cpp` encodes a `Parts::ThingKey`, which asks for its type
descriptor, which now lives in `Parts_Model.hpp`.

### The one thing still open, and it needs the runtime

`key<any_concept>` comes out of the converter as a bare `AnyConceptKey`, which resolves to
nothing inside a unit. It cannot be fixed in a template, and fixing it in the converter
alone would break the existing whole-model templates, which declare a class of that name in
the model's own namespace.

The reference says where it belongs — `Viper::AnyConceptKey`, seven of whose nine members
name no concept — so the change has an order and three repositories:

1. the runtime gains the type;
2. the converter qualifies it, as it already qualifies `Viper::Any`;
3. the whole-model templates stop declaring their own.

Nothing before step 1 is safe, so the crossing model carries that one failure, visible.

## Layer 2, the implementation — `Fields.cpp.stg`

Twenty lines, and the render is **identical to `../hand/ModelA_Fields.cpp`** once comments
are stripped — the first artefact where that is true with no ordering difference either,
because a structure's fields have one order and it is the model's.

Every generated file of the topology model now compiles: five artefacts per unit, headers
and implementations, on all five namespaces. The crossing model compiles too except the
three files that name `AnyConceptKey`.

## The injected module, generated — one file, two entries

`Codec.hpp.stg` and `Codec.cpp.stg` now declare both `unit(u)` and `model(m)`: the first
renders once per namespace, the second once for the model. That is what discriminating on
the declared entry was for, and it puts a unit's codec and the base that carries it in the
same file, which is where a reader looks.

The render matches `../hand/Topology_Codec.hpp` exactly and `.cpp` but for one comment.
**All 34 generated files of the topology model compile**, base included.

**The base is four declarations**, and the criterion is the same for all four: each needs
the whole model. Everything else that had been put there left once it was traced — the
registration, because the model is embedded data rather than generated code, and the
primitive and container descriptors, because a primitive's type is a runtime singleton and a
container's composes from its elements.

`type(tag<std::map<ModelA::MaterialKey, ModelB::MaterialKey>>{})` is now assembled by a
runtime template from two units' descriptors. The shape this whole line of work started
from produces no generated line at all.
