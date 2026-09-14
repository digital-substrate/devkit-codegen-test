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

## Not yet written

Python and node, and the other five features — `ValueType`, `Attachments`, `Path`,
`Definitions` (the aggregate) and one pool. `Definitions` and `ValueType` are the base
layer and do not become per-unit; they are the interesting ones for that reason.
