# namespaces — a model about namespace topology, and nothing else

`features/all.dsm` covers the type system and `service` covers pools and the remote.
Both declare a single namespace, so neither reaches any cross-namespace path in the
generator. This model covers only the topology, and stays small on purpose: the types
it uses are the simplest ones that carry an edge.

Its shape is drawn from a real integration: two driver models owned by different
vendors, a namespace that composes them, and pools on top.

```
Projection ──→ ModelA        Annotations ──→ ModelA
    │      ╲─→ ModelB        Projector   ──→ ModelA, ModelB
    ╰────────→ ModelC        Tools       ──→ (nothing)
```

## What it is for

Every case below is either a defect that has shipped or a path nothing else in the
repository reaches. `check.py` asserts each one against the generated JSON, so the
model cannot quietly stop covering what it claims:

| case | where it lives |
|---|---|
| a namespace reached **only** through an attachment | `ModelC`, via `Projection.marker` |
| a `key<NS::C>` edge in a structure field | `Projection.Pair` |
| a concept whose parent is in another namespace | `Projection::DerivedMaterial` |
| a namespace holding **only** attachments | `Annotations` |
| the same name declared in two namespaces | `Material` and `Colour`, in `ModelA` and `ModelB` |
| a container shape spanning two namespaces | `Projection.mapping` |
| a pool spanning two namespaces | `Projector` |
| a pool naming no namespaced type at all | `Tools` |
| a `void` return | `Tools.reset` |

The first two matter because a namespace reachable only through an attachment carried
no dependency edge before `9328acd`, and a namespace holding nothing but attachments
was absent from the model entirely. Both would have gone unnoticed here before that
fix; both are asserted now.

## Usage

```bash
python3 generate.py -c -p -t      # render into the working tree, like the other models
python3 check.py                  # assert the cases above are still covered
```

`check.py` exits non-zero if any case stops being covered.

To measure a change rather than render one, use `../tools/render.py`: it renders every
model into a scratch tree without touching the working tree, so it can be run before and
after an edit.

```bash
python3 ../tools/render.py /tmp/before
#   ... change a template or the generator ...
python3 ../tools/render.py /tmp/after
python3 ../tools/render.py --diff /tmp/before /tmp/after
```

The two mono-namespace models guard against regression and their diff must be empty; this
one shows the effect a change is meant to have, so its diff is read rather than asserted.
`--diff` exits non-zero only when a mono model moved.
