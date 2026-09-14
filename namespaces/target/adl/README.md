# adl — the base building *on* the units, rather than containing them

The objective: modular by namespace. What blocked it was `typeSuffix`, which names every
generated symbol independently of namespaces — `encode_map_ModelA_MaterialKey_to_ModelB_MaterialKey`
— and so keeps everything flat by construction.

`typeSuffix` turns out to be a **manual monomorphisation of what C++ resolves by itself**.
Every container encoder kibo emits has the same body, differing only in the name it calls:

```cpp
void Writer::write_map_ModelA_MaterialKey_to_ModelB_MaterialKey(
        std::map<ModelA::MaterialKey, ModelB::MaterialKey> const & value) {
    streamWriting->writeUInt64(value.size());
    for (auto const & [k, e] : value) {
        write_ModelA_MaterialKey(k);     // <- what typeSuffix exists to spell
        write_ModelB_MaterialKey(e);
    }
}
```

Written as a template, those two calls are resolved by overload resolution plus
argument-dependent lookup, and they land in the namespace that owns each type.

## Demonstrated, not argued

`write_by_adl.cpp` and `read_by_adl.cpp` compile and run with `c++ -std=c++17`.

    map qui enjambe : map{A::Material(u8(1))->B::Material(u8(2))}
    Pair            : Pair(A::Material(u8(7)),B::Material(u8(8)))
    décodé          : A::Material(4) -> B::Material(7)

What they establish:

- **The spanning container needs no generated function at all.** A generic
  `write(Writer&, std::map<K,V> const&)` walks it, and ADL sends each half to its own
  namespace. The shape that belonged to nobody stops being an artefact needing an owner:
  it is a composition, resolved where it is used.
- **Two same-named types coexist**, `ModelA::Material` and `ModelB::Material`, neither
  renamed. Overload resolution distinguishes them.
- **The generic templates are defined before the namespaces exist** and still find them,
  because a dependent call is resolved at instantiation.
- **Decoding works too**, through a tag: `tag<ModelA::Material>` carries `ModelA` as an
  associated namespace, so `read(r, tag<T>{})` reaches `ModelA::read`. The one objection
  to this design — that decode has no argument of the right type — does not hold.

## What it costs

The generated *shape* changes, not just its distribution across files. A consumer writes
`encode(x)` where today it writes `ValueEncoder::encode_Test_ConceptAKey(x)`. And the nine
container templates are model-independent, so they belong in the runtime rather than in
generated output — which is another thing waiting on `viper` 1.2's API lock.

`base/`, `ModelA/` and `Projection/` sketch what the generated code would look like.
