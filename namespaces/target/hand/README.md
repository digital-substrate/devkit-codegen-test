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
