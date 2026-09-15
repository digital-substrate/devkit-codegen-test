# hand — written from the model, never from the output

Layer 1 for C++: the types each namespace declares. Written from the `.dsm` by hand,
without opening what the generator currently emits. That distinction is the point — the
previous attempt at a hand-written target (`../cpp/`) was written as a transformation of
today's output, and inherited the flat-namespace assumptions it was meant to remove.

`use.cpp` checks the result is valid C++ and that the properties hold:

```sh
c++ -std=c++17 -fsyntax-only use.cpp
```

with `Viper_UUId.hpp` and `Viper_AnyConceptKey.hpp` as minimal stubs for what the runtime
would provide.

## What it establishes

- Two `Material` and two `Colour`, in `ModelA` and `ModelB`, neither renamed. The flat
  prefix existed to imitate this.
- A structure is an aggregate and brace-initialises, because the model says it is data.
- `Projection::Pair` qualifies its fields — not to disambiguate, but because the types
  are not Projection's, which is what a reader wants at a composition site.
- `is a` is an implicit conversion: `DerivedMaterialKey` passes where a
  `ModelA::MaterialKey` is expected without being asked.
- Everything is usable in ordered and unordered containers.

## What writing it found

**The runtime id must be stored on a key, and `ModelA` alone cannot show why.** Writing
`ModelA_Data.hpp` first, it looks like a property of the type: it identifies the concept,
so every `MaterialKey` has the same one, and storing it per key doubles the size for
nothing. That was written, and `Projection` overturned it one file later. Because
`DerivedMaterial is a Material`, a `MaterialKey` may name an instance of a derived
concept, and its runtime id is that concept's. A static would make `toAny()` lie after
every widening.

The correction is noted in `ModelA_Data.hpp` where the field is declared, rather than
here, so that whoever reads the type sees why it costs what it costs.

## Layer 2 — naming and addressing a field

`ModelA_Fields.hpp`, `Projection_Fields.hpp`. Two findings, both from writing rather than
from reasoning.

**One artefact where the pack has two.** `Field` gives a field's name and `Path` gives
its address, in two files whose contents are in bijection. Wanting the name without the
address, or the reverse, is rare — `attachment.diff(key, Colour::rPath(), 4)` uses the
path and an error message beside it uses the name. Two files is an implementation
decomposition; the §7 inventory already counts them as one capability.

**A field name is a compile-time constant and should cost nothing.** The pack emits
`extern std::string const r`, which allocates at static initialisation for something that
never changes and cannot be used in a constant expression. `inline constexpr
std::string_view` costs nothing and `static_assert(Fields::Colour::r == "r")` compiles —
checked in `use.cpp`.

**And `Projection_Fields.hpp` includes neither driver unit**, though `Pair` holds a key
from each. A path names a position, not a type. Same structure, two artefacts, two
dependency sets — which is why an include list is computed per artefact and never per
unit.

## Layer 3 — the bridge

`ModelA_Codec.hpp`, `Projection_Codec.hpp`, checked by `bridge.cpp`.

**A unit implements two things, and that is all.** Tracing what the pack's four bridge
domains actually do: `encode_ModelA_Colour` writes to a stream and decodes the result
into a `Value`; `Json` does the same through a json codec; `hexdigest_X` encodes and then
hashes. Four domains — `Stream`, `ValueCodec`, `Json`, `ValueHasher` — one implementation
underneath. A unit says how its own types go onto a stream, and what type they are.
Seven declarations for ModelA.

**`Projection_Codec.hpp` has nothing for the spanning map**, though Projection is the
namespace that declares it. The runtime's generic `write(Writer&, std::map<K,V> const&)`
walks it and ADL sends each half to ModelA and ModelB. The shape that belonged to nobody
is not an artefact needing an owner; it is a composition, resolved where it is used.

That is the whole base layer, gone. `write_map_ModelA_MaterialKey_to_ModelB_MaterialKey`
exists today only because nothing scoped the output, and it is the reason a base file had
to be invented in the first place.

## Layer 4 — attachments and pools

`ModelA_Attachments.hpp`, `Tools_Pool.hpp`, `Projector_Pool.hpp`, checked by `l4.cpp`.

**The attachment scope hides a collision the pack resolves silently.** ModelA declares
`attachment<Material, Colour> colour`. The natural scope is
`Attachments::Material::Colour` — and that `Colour` would shadow the *type* `Colour` one
header away, so every signature in it would have to qualify its own namespace's type. The
pack sidesteps this by flattening to `Material_Colour`: the flat prefix again, in a third
place, for a reason nothing records.

Using the attachment's own spelling — `Material::colour`, as the model writes it — costs
nothing and removes the clash. It also reads as what it is.

**A pool's two sides belong together.** `Tools::add` and `Tools::Remote::add` are the
same operation in process and across a wire, and a reader looking for one wants the
other. Today they are in `FunctionPoolBridges::Tools` and `FunctionPoolRemotes::Tools` —
two scopes named after templates, neither named after anything in the model.

**And `Projector` shows what a pool is not.** Its `link(ModelA::MaterialKey,
ModelB::MaterialKey)` names two namespaces, so asking which owns it is the wrong
question. A pool is not owned by the namespaces whose types it mentions: it is the
operations an application chooses to expose, and another application over the same models
would expose different ones.

## Layer 5 — the generated tests

`ModelA_Test.hpp`, checked by `l5.cpp`. It was written last on the expectation that it
would need no new idea, and it did not — which is the check on the four layers below it.

**It mirrors layer 3 exactly.** A round-trip test is generic: make a value, encode it,
decode it, compare. The only part that is not generic is making one, and ModelA makes a
Colour because ModelA knows it has three channels. Two `fuzz` declarations and one
`test()`, where the pack emits seven test artefacts with a function per type per codec.

**A container of ModelA's types needs no line at all.** The generic fuzz builds a
`std::set<Colour>` by calling `fuzz(rng, tag<Colour>{})`, and ADL brings it back — the
same mechanism as the codec, in the same place, for the same reason.

**What stayed model-wide is the driver**, and only the driver: something has to enumerate
the model's units and call each one's `test()`. That is genuinely about the assembly, and
it is the one thing at this layer that belongs to the base.

## Five layers, and one cause

Each layer's hand-written form removed a flattening, and the four are the same flattening:

| where | today | because |
|---|---|---|
| types | `ModelA_Material` | the namespace could not scope it |
| shapes | `encode_map_ModelA_MaterialKey_to_ModelB_MaterialKey` | nothing owned a `std::map` |
| attachments | `Material_Colour` | a scope would have shadowed the type |
| pools | `FunctionPoolBridges::Tools` | a template's name became a scope |

Four symptoms, one cause: something had to be distinguished, the namespace was not
available to do it, so the name absorbed the distinction. None of them needed inventing
away — each dissolves once the namespace structures the output.

## Open, and deliberately not settled here

- **The file name.** `Data` is a template's name, inherited from the pack, not a domain.
  A developer would write `ModelA.hpp` or `ModelA_Types.hpp`. Kept for now because the
  rest of the work still calls this artefact `Data`.
- **Whether the implicit conversion is right.** `is a` says yes; implicit conversions
  between handle types are a known way to be surprised in overload resolution. An
  explicit `toParent()` is the alternative, and the case that would decide it is a
  function overloaded on both key types.

## Layer 4, implemented — and the three modules become visible

`ModelA_Attachments.cpp`, the first implementation file written at all. Until it existed,
every layer was a header: declarations, checked by a caller that never needed a body. That
made the easy quarter of the work look like the whole of it — across the pack, headers are
2 589 lines of template and implementations are 6 148.

It is forty lines, and the object file says what it is made of. Compiling it and listing
the symbols it leaves undefined gives exactly three groups and nothing else:

```
ModelA::write, ModelA::read, ModelA::type, ModelA::Fields::Colour::rPath   the unit
Topology::Codec::definitions, ::stream, ::type                             the injected module
Viper::ValueKey::cast, ::ValueDecoder::decode, ::Definitions::…            the runtime
```

No `encode_ModelA_MaterialKey`, no `ValueEncoder::encode_ModelA_Colour`, no
`ValueType::attachment_ModelA_Material_Colour`. That is not a reading of the source, it is
what the compiler emitted.

**The generic encode holds, and the pack's own code is the evidence.** Its `encode_<suffix>`
body is ten lines repeated once per type, and only the suffix varies — a stream encoder, a
write, and a decode back into a `Value` through the type descriptor. Write, and the type
descriptor, are precisely what a unit declares. One function template replaces the whole
family, with argument-dependent lookup choosing the unit. The layer-3 claim was checked here
and it survived.

**The boundary drew itself at the first compilation.** `setR` encodes a `std::uint8_t`, so
`encode<std::uint8_t>` asks for `type(tag<std::uint8_t>)` — and no unit declares it, because
a `uint8` belongs to nobody; lookup from `tag<unsigned char>` reaches no namespace either. It
has to be the injected module's, for a concrete reason: a `Type` is an object registered in
the model's `Definitions`, so obtaining one needs the whole model. The same will hold for
`type(tag<std::set<T>>)`, a `std::set` belonging to no namespace of the model. That is the
frontier this whole exercise was looking for, and it appeared on its own.

**Three corrections the implementation forced on the layers below.**

The type descriptor returns `std::shared_ptr<Viper::Type>`, not `…<Type const>`. Layer 3 had
it const, the runtime's `ValueDecoder::decode` takes it non-const, and no reading of the
header would ever have shown it.

There is no `remove`. `Viper::AttachmentMutating` offers `set`, `diff` and `update`, and
nothing that removes a document. The header declared one.

What writes a single field is a setter per field — `setR`, `setG`, `setB` — and not the
path-taking overload the first draft had. `update` takes a path and an encoded value; binding
the two in one signature is what makes the path type-safe, and a generic `(path, value)`
overload would let them disagree silently. The path-taking overload was deleted once already
as an invention; it was half right, and this is its real shape.

**And the runtime ids lose their flat names.** The pack puts them in
`ModelA::AttachmentRuntimeIds::Material_Colour`, one scope holding every attachment's id.
Here the scope already names the attachment, so what is left is `runtimeId`.

## Layer 3, implemented — three functions per type, and the unit is done

`ModelA_Codec.cpp`. The pack emits seven serialisation artefacts per unit, each with a
function per type; here there are `write`, `read` and `type`, and everything the pack emits
besides is a generic composition of those three. Its undefined symbols are its own Data, the
runtime's primitives, and `Topology::Codec::definitions()`. Nothing else, and no other unit.

**A fixture gap, found by having nothing to write.** No namespace declared an enumeration, so
five templates had never been asked to handle one — and layer 1 turned out to emit no
enumeration declaration at all. `ModelA` now declares `enum Finish { matte, gloss }`. The
mono models are byte-identical; only the multi model moved, where the new type lands.

**`enum class`, and no explicit values.** The scope already names the unit, so an unscoped
enum would pour `matte` and `gloss` straight into it. What crosses the wire is the case's
index, and the model is the source of that order — writing a C++ value as well would let the
language and the model disagree.

**A key on the wire is two uuids**, the instance and the concept it actually is. The second is
stored rather than derived from the type, because a `MaterialKey` may name an instance of a
derived concept, and it is that concept's identity that has to travel.

**And a real hazard the free-function form introduces.** The pack reads a structure into one
local per field, named after the field, which is safe there because its reader is `this`. Here
the reader is a parameter, so a field named `r` produces `auto const r{read(r, …)}` — a
variable read inside its own initialiser. `ModelA::Colour` has exactly that field. The
reference avoided it by naming its locals by hand, which is not a property a generator has.
Fixed by naming nothing: a braced-init-list evaluates left to right by guarantee, so the
model's field order holds without a single local.

## Layer 2, implemented — the field name appears once

`ModelA_Fields.cpp`. Three lines per field, and one observation worth the detour: the path
is built from the constant declared above it, not from a copied literal.

```cpp
std::shared_ptr<Viper::Path const> const & rPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{r})};
    return instance;
}
```

The pack writes `Viper::Path::makeField("r")` in one file and `std::string const r{"r"}` in
another, and nothing holds the two together. Here the field's name appears once in the whole
unit, which is what merging `Field` and `Path` into one artefact was for.

A path is a property of the structure and not of a value, so there is one per field for the
life of the program: built once, returned by reference.

The runtime takes a `std::string const &`, so the `string_view` constant is converted at the
one call. A `string_view` overload on `makeField` would remove even that, which is a note
for the runtime rather than a change here.

## Layer 4, the pools implemented — and the format contract comes due

`Tools_Pool.cpp` and `Projector_Pool.cpp`. A pool is two things that resemble each other:
static C++ functions the developer writes, and `Viper::Function` objects that take and
return `Viper::Value`, because that is how a call arrives from a script, an RPC or a tool.

**The bridge converts nothing type by type.** It decodes each argument from its Value, calls
the static function, encodes the return. `Projector::link` spans two units and the bridge
does not know it: `decode<T>` finds T's `read` by argument-dependent lookup. The pack writes
`ValueDecoder::decode_ModelA_MaterialKey` and `..._ModelB_MaterialKey` there — two flat names
that existed because nothing else told the two calls apart.

**And the serialisation has to match `Viper::ValueWriter` byte for byte.** `decode<T>` sends
the Value through a stream and reads it back with `read`, so what `ValueWriter` puts down for
that Value must be exactly what `read` expects. The format is therefore taken from
`Viper_ValueWriter.cpp` and not chosen here:

```
optional        writeBool(present) then the value
vector/set/map  writeUInt64(size) then the elements, key before value
variant         writeUInt8(index) then the value
vec/mat         the elements, no size — it is in the type
key             writeUUId(instance) then writeUUId(the real concept)
enumeration     writeUInt8(the case's rank)
structure       its fields in the type's order
```

**A contract that is safer for being written once.** The pack re-emits these bodies per
shape per model; here they are runtime templates, next to the ValueWriter they must follow.

**Each unit a pool reaches costs three artefacts, not one** — its types for the signatures,
its codec for `write`/`read`, its model identity for the descriptor the dynamic prototype
needs. The pool's *header* needed only the first.

**And every type descriptor is now reachable by lookup.** `type(tag<std::int64_t>{})` from
inside a pool found nothing: a fundamental type has no associated namespace. `tag<T>` has
one — the runtime's — so the descriptors that belong to no unit are declared in
`Viper::Codec` and defined by the injected module. One rule for every T.

## isKnown, and who holds the set of known concepts

Someone must supply it, and someone already does: the model registers every one of its
concepts in its `Definitions` at load, which has to happen anyway or nothing in the runtime
works. Asking that registration generates nothing further.

```cpp
bool isKnown(Viper::AnyConceptKey const & key) {
    return definitions()->queryConcept(key.runtimeId()) != nullptr;
}
```

**And it is the right answer, not merely the shortest.** The pack freezes the list at
generation: `isKnown()` compares against a set closed on the day the code was written. But
`Viper::Definitions::extendConcepts` exists — a model learns concepts at run time, from a
peer or from a newer document. A frozen list then answers "unknown" for a concept the runtime
knows, which the pack acknowledges in its own comment on `description`.

Asking the model gives today's answer. Enumerating gives the generation day's.

`isMember` is the same call with one difference carried by the descriptor rather than by the
code: a concept descriptor asks whether the instance derives from it, a club descriptor asks
whether it belongs. Deriving is not joining, and one function covers both.

## The injected module — and two things it is not

`Topology_Codec.hpp` / `.cpp`. The base, and it is four declarations:

```
definitions()                          the model as the runtime knows it
stream()                               the stream codec the round trip goes through
encode<T> / decode<T>                  between a C++ value and a Viper::Value
description / isKnown / isMember       what the untyped key cannot carry itself
```

One criterion for all four: each needs the whole model, so no namespace can answer for it.
That is the entire definition of the base, and this is the entire base.

### It holds no registration, because the model is data

The pack generates no type-registration code at all. It embeds the `.dsm` as a resource and
decodes it at first use:

```cpp
Viper::Blob blob(sizeof(Resources::definitions));
std::memcpy(blob.storage.data(), Resources::definitions, blob.size());
instance = Viper::DefinitionsDecoder::decode(blob, Viper::StreamTokenBinaryCodec::Instance());
```

So there was never a registration artefact to split per unit — the question of who holds the
set of known concepts was answered before it was asked, by the document itself.

### It holds no primitive or container descriptor, and it did an hour ago

`type(tag<std::uint8_t>)` and `type(tag<std::map<K,V>>)` were put here on the reasoning that
a `Type` is registered in the model's `Definitions`, so obtaining one needs the whole model.
**That reasoning was wrong**, and the pack's own code says so: a primitive's type is
`Viper::TypeUInt8::Instance()`, a runtime singleton, and a container's is
`Viper::TypeMap::make(keyType, elementType)`, composed from its elements. Neither consults
the model.

They are therefore entirely the runtime's, as one inline function per primitive and one
template per container shape — and the container template composes by lookup, so

```cpp
type(tag<std::map<ModelA::MaterialKey, ModelB::MaterialKey>>{})
```

is built by a runtime template from two units' descriptors, with **nothing generated for it**.
The shape that forced a base into existence now produces no line anywhere.

**The base is smaller than the argument that created it.** Each time something was traced
rather than assumed, it left.
