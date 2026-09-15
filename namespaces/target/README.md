# target — the C++ reference, and how far it has got

The success condition is **iso-functionality**: everything the existing templates produce
must still be produced, in the idioms this work proposes. Not "most of it", and not "the
interesting parts".

`hand/` is the reference, written from the model and compiled. `templated/` reproduces it.
**`generated/` is what it produces**, versioned, so that a change to a template is visible as
a change to the output rather than as a change nobody can read.

```sh
namespaces/target/render.py            # rend les deux modèles dans generated/, et compile
namespaces/target/render.py --check    # échoue si generated/ n'est pas à jour
```
`../../crossing/target/hand/` holds the two shapes the topology model does not declare.

## Where it stands, measured

The pack is **73 templates, 8 737 lines, 17 directories**. What is in `templated/` is
**14 templates, 1 561 lines**, and it does not cover everything.

The table below is not an estimate. Each row was checked by rendering two unrelated models
and comparing the output with the model's namespace substituted — an artefact that comes out
**byte-identical** for two different models is not generated code, whatever file it lives in.

| pack directory | templates | lines | where it goes |
|---|---:|---:|---|
| `Data` | 4 | 944 | done — `Data.hpp/cpp.stg`, `AnyConcept.hpp.stg` |
| `Stream` | 4 | 908 | done — `Codec.hpp/cpp.stg`, entry `unit` |
| `ValueCodec` | 4 | 497 | done — one generic `encode`/`decode` |
| `ValueType` | 2 | 373 | done — `Model.hpp/cpp.stg`, plus runtime templates |
| `Attachments` | 2 | 340 | done — `Attachments.hpp/cpp.stg` |
| `Model` | 6 | 216 | done — `Fields.hpp/cpp.stg`, entry `model` |
| `FunctionPool`, `…Remote`, `AttachmentFunctionPool`, `…Remote` | 10 | 555 | done — `Pool.hpp/cpp.stg` |
| `Database` — 11 of 13 | 11 | ~1 638 | **not generated at all** — the model appears at four places, as an argument |
| `Database/DatabaseAttachments` | 2 | 156 | done — `Database.hpp/cpp.stg`, `Db.hpp.stg` |
| `AttachmentFunctionPool_Attachments` | 2 | 787 | done — **nothing generated**, a walk over the model's attachments |
| `Test` | 14 | 1 403 | done — `Test.hpp/cpp.stg`, five templates and a list per unit |
| `TestApp` | 4 | 294 | done — `TestApp.cpp.stg`, one driver |
| `Json` | 4 | 262 | a composition over `encode` — a few lines, not yet written |
| `ValueHasher` | 2 | 287 | a composition over `encode` — a few lines, not yet written |
| `Python` | 2 | 77 | the Python binding of this C++ — out of this pass |

## What the measurement found

**Eleven of the thirteen `Database` templates emit code that does not mention the model.**
`Databasing`, `Database`, `DatabaseSQLite`, `DatabaseRemote`, `DatabaseRemoteRPCSideClient`
and `DatabaseHelper` render byte-identical output for two unrelated models — 1 607 lines,
zero difference, once the namespace name is substituted. They are runtime code wearing a
template, and the only generated thing about them is the namespace they are wrapped in.

Only `DatabaseAttachments` is genuinely per-model, and it is per-attachment, so it is a unit
artefact like the others.

**`Json` and `ValueHasher` are compositions, and their own source says so.**

```
encode_X(v)     = JsonValueEncoder::json_encode(ValueEncoder::encode_X(v))
hexdigest_X(v)  = hexdigestValue(ValueEncoder::encode_X(v))
```

Neither adds anything per type beyond the name. 549 lines of template for what is one
function template each over the generic `encode` — which is the layer-3 claim, holding for a
third and fourth domain.

**`Test` is the one claim not yet checked.** `Test.hpp.stg` declares a `fuzz` per type and a
`test()` and asserts that the pack's 1 403 lines collapse into that. **Nothing verifies it:**
no test implementation has been written, which is the same gap that made the first four
layers look finished when only their headers existed.

## Where it stands now

Every directory of the pack has been opened, and all but two are reproduced and compiled:
**47 generated files for the topology model, 25 for the crossing one.** What is left is
`Json` and `ValueHasher`, which their own source shows to be compositions over the generic
`encode` — a few lines each, and the only reason they are not written is that nothing has
needed them yet.

No new shape appeared in the last three pieces. What appeared instead, three times, was the
same finding: an artefact that looked generated turns out to vary only by the model's name,
or by one argument.
