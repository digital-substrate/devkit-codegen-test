# service — the pools, and a service that actually runs

`Service.dsm.json` declares two pools — `Tools` (plain functions) and `PlayerModel`
(functions over an attachment) — and the smallest model they need. `features/` covers the
type system and declares no pool; this is where the pools are.

Generated from `../templates`, the sandbox pack.

```
service/
  definitions/  Service.dsm.json  generate.py

  cpp/          generated/   src/   run_test.sh   CMakeLists.txt
  python/       generated/service/  src/client.py  run_test.sh
  typescript/   generated/src/      src/client.ts  run_test.sh
```

**`generated/` is kibo's; `src/` is the developer's.** That line is the point of this site.
A pool generates a declaration and leaves the implementation to whoever owns the behaviour:
`cpp/src/ToolsPoolBridges.cpp` and `cpp/src/PlayerModelPoolBridges.cpp` are what nobody can
generate on your behalf.

## What the tests prove

One C++ server, three clients. The protocol does not know the language of its ends, and that
is what is being checked.

    cpp/run_test.sh          C++ client ↔ C++ server, over an AF_LOCAL socket
    python/run_test.sh       Python client ↔ the same C++ server, over TCP
    typescript/run_test.sh   TypeScript client ↔ the same C++ server, over TCP

Each prints the same four lines: a scalar call, a struct call, a key created through an
attachment pool, and the document read back.

## What porting the clients found

The three clients are hand-written, so what had to change in them is exactly what the new
templates renamed under a developer's feet — 19 renames across the four C++ files. Two were
not renames but defects, and neither was visible from inside the generator:

- **A Python pool returned a raw `ValueOptional` while promising `PlayerKey | None`.** Only
  named types were wrapped, so an optional slipped through unwrapped and a consumer following
  the signature got an `AttributeError`. Every return now goes through the registry, which
  reads the type the value carries: it unties the optional, picks a key's class from its real
  concept, and passes primitives through untouched. The TypeScript template already did this.
- **A TypeScript enum constant was typed `string`, not its own union.** In a plain object
  literal TypeScript widens `"beginner"`, so `Level.BEGINNER` — the constant the module
  offers — could not be passed to a parameter of type `Level`. `as const` freezes it.

## A debt this site makes concrete

**The C++ client is forced to link the pool bridges.** `Pool` and `PoolRemote` are merged in
`templates/cpp`, so both edges of a pool — the one called in-process and the one called down
a wire — land in a single `Tools_Pool.cpp`. A client wants only the remote edge but receives
the whole object, so the linker demands `Tools::add`, a function only a server implements.

That is the split noted in `templates/cpp/README.md`, failing at link time rather than as a
matter of tidiness.
