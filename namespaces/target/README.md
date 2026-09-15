# target — the C++ reference, and how far it has got

The success condition is **iso-functionality**: everything the existing templates produce
must still be produced, in the idioms this work proposes. Not "most of it", and not "the
interesting parts".

`hand/` is the reference, written from the model and compiled. `templated/` reproduces it.
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
| `Database` — 11 of 13 | 11 | ~1 638 | **not generated at all** |
| `Database/DatabaseAttachments` | 2 | 156 | per-attachment, so per-unit — to do |
| `AttachmentFunctionPool_Attachments` | 2 | 787 | the dynamic side of attachments — to do |
| `Test` | 14 | 1 403 | **declared only** — `Test.hpp.stg` has no implementation |
| `TestApp` | 4 | 294 | a command-line driver — to do |
| `Json` | 4 | 262 | a composition over `encode` — a few lines |
| `ValueHasher` | 2 | 287 | a composition over `encode` — a few lines |
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

## What is not yet proven

That the decomposition absorbs everything. Two of the three largest remaining pieces —
`Test` at 1 403 lines and `AttachmentFunctionPool_Attachments` at 787 — have not been opened
beyond their signatures, and they are where a new shape is most likely to appear.
