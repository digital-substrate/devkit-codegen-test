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

## Open, and deliberately not settled here

- **The file name.** `Data` is a template's name, inherited from the pack, not a domain.
  A developer would write `ModelA.hpp` or `ModelA_Types.hpp`. Kept for now because the
  rest of the work still calls this artefact `Data`.
- **Whether the implicit conversion is right.** `is a` says yes; implicit conversions
  between handle types are a known way to be surprised in overload resolution. An
  explicit `toParent()` is the alternative, and the case that would decide it is a
  function overloaded on both key types.
