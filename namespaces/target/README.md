# target — what the generator should produce, written by hand

These files are **not generated**. They are the specification: the output a developer
should get, written first, so the generator has something to be measured against rather
than a design to be inferred from whatever it currently emits.

Only `Data` is covered so far, in C++, for one multi-namespace model and one mono. Class
bodies are elided — they do not change. What is being specified is the file boundaries,
the includes, the scopes, and where the cross-cutting parts land.

## What it says

**A unit per DSM namespace, and the namespace stated once.** `Demo::PlayerKey`, not
`Service::Demo::PlayerKey`; `ModelA::MaterialKey`, not `ModelA_MaterialKey`. In mono and
in multi, the same layout — no special case for the common one.

**Includes carry no path**, resolved by one `-I` per unit. This is the convention viper,
ge and red already follow, for generated and hand-written code alike, and it is what keeps
a unit's directory a build concern rather than a code one.

**A composing unit's includes are its dependency set**, computed rather than composed.
`Projection` reaches `ModelA` and `ModelB` through a structure's fields, and `ModelC`
through an attachment document type alone — the edge that carried no dependency at all
before `9328acd`.

**Names collide and nothing is renamed.** `ModelA::MaterialKey` and `ModelB::MaterialKey`
coexist in different scopes and different files. The flat prefix existed to fake exactly
this.

## Three decisions this exercise forced, now settled

**`-n` names the base unit, not an enclosing scope.** `AnyConceptKey` has to live
somewhere: it carries no model dependency — it is `(instanceId, runtimeId)` — and belongs
in the runtime, but viper 1.2's API is closed. So it is emitted as a unit of its own that
every other unit includes and that includes none of them. It is a peer, not a parent:
`ModelA::MaterialKey` is top-level, not `Topology::ModelA::MaterialKey`.

**A mono project gains a header**, which follows from the first decision rather than
being a separate choice: base unit plus driver unit, in mono as in multi. It is reached
transitively, so a consumer still writes one include. One layout, no special case for the
common one.

**A namespace with nothing to emit gets a file all the same.** `Annotations` contributes
nothing to `Data`, and `Annotations_Data.hpp` exists anyway. A predictable path is worth
more than a file saved: a build lists `<unit>/<unit>_<feature>.hpp` without asking what
the model happens to contain, and the day the namespace gains a concept its consumers
already include it.

## What `Definitions` and `ValueType` added

They were expected to be "the base layer" wholesale. Only one of them is.

**`ValueType` does not split, and the reason is checkable.** It includes `Viper_Types.hpp`
and nothing generated; every function returns a `Viper::Type` and composes out of the
others. The namespace appears only inside a symbol name, never as a C++ type reference,
so the table has no dependency on any unit and cannot acquire one. Splitting it would
break the single-instance memoisation each function relies on, and would leave a shape
spanning two namespaces — `type_map_ModelA_MaterialKey_to_ModelB_MaterialKey` — belonging
to neither unit. It stays whole, in the base.

That also settles `typeSuffix`. Carrying the DSM namespace in a flat symbol name is not a
leftover of the prefix era: it is a structural, deduplicated name for a type shape, and it
must read the same whether the model has one namespace or five. It is the one place a
namespace legitimately appears flattened.

**`Definitions` does split, and it is two things in one file.** The per-namespace
`RuntimeIds` and `AttachmentRuntimeIds` blocks belong to each unit; `definitions()`,
which decodes the blob the caller embeds, is base. So the base keeps the one edge that
points outside the pack — `Topology_Resources.hpp` is written by `generate.py`, not by a
template — and no unit inherits it.

`RuntimeIds` stays a scope where `ValueType` did not, and the distinction is worth
keeping: `ValueType` is a feature name and a feature is a file, while
`ModelA::RuntimeIds::Material` genuinely distinguishes the UUID from the type
`ModelA::MaterialKey`. Both belong to ModelA.

**And `Annotations` is empty in `Data` but not in `Definitions`** — one attachment
runtime id, no concept ids. Whether a unit has content depends on the feature, which is
the argument for emitting a file per unit per feature rather than asking the model.

## What `Attachments` and the pools added

**The attachment-borne edge is visible in a signature.** Every accessor of
`Annotations::Attachments::Material_Note` takes a `ModelA::MaterialKey`, so that unit
does not compile without including `ModelA_Data.hpp`. The edge that carried no
dependency at all before `9328acd`, and that both `backbone` projections rely on, is not
a subtlety of the graph: it is in the function signatures.

**A spanning container is written where it is declared, but its type descriptor is not.**
`Link_Mapping` takes `std::map<ModelA::MaterialKey, ModelB::MaterialKey>` in
`Projection_Attachments.hpp`, because `Projection` is the unit that declares it. The
matching `type_map_ModelA_MaterialKey_to_ModelB_MaterialKey()` stays in the base. The same
shape, split by what kind of thing it is.

**A pool is a unit, and `Tools` is the degenerate one**: it names no namespaced type, so
it includes nothing and depends on nothing. `Projector` is the opposite — its signature
names two namespaces, which is what creates the composing layer rather than being a
problem the composing layer has to absorb.

The scope is `Tools`, not `Topology::FunctionPoolBridges::Tools`. The pool's name is the
unit's name; `FunctionPoolBridges` was a template name that had become a namespace level.

**And a worry about cycles was misplaced.** The base unit is a root — `Topology_Data.hpp`
and `Topology_ValueType.hpp` include nothing generated — while a registry of every pool
plainly depends on all of them. Both hold at once, because **the root/sink distinction is
a property of files, not of units**: a namespace reopens across files, a file's includes
do not. `namespace Topology` therefore spans a root file and a sink file, and the layering
is a layering of artefacts. A unit may contribute at several layers.

## One rule this raised, and the measurement behind it

An attachment's scope named its concept **unqualified**, so two attachments declared in
one namespace on same-named concepts of two others looked like a collision waiting to
happen. The model now contains the case, and the generator handles it: it counts
attachments in the namespace sharing a name and a key-concept name, and prefixes the
key's namespace only when more than one exists. It never collides.

What it does instead is make the name a function of the whole namespace's attachment
set. With only the `ModelA` one present the scope is `Material_Note`; adding the
`ModelB` one renames it to `ModelA_Material_Note`. A source-compatible model change
moves a generated symbol.

**Proposed: qualify whenever the concept is not this unit's own, always.** A longer name
in the common case, for a name that does not move — and one that reads like the
signature beside it, which already says `ModelA::MaterialKey`.

## Not yet written

Python and node, and `Path`.
