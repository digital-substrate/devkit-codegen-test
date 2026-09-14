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

## Open, and deliberately not settled here

- **The file name.** `Data` is a template's name, inherited from the pack, not a domain.
  A developer would write `ModelA.hpp` or `ModelA_Types.hpp`. Kept for now because the
  rest of the work still calls this artefact `Data`.
- **Whether the implicit conversion is right.** `is a` says yes; implicit conversions
  between handle types are a known way to be surprised in overload resolution. An
  explicit `toParent()` is the alternative, and the case that would decide it is a
  function overloaded on both key types.
