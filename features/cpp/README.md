# cpp — the C++ side of the features site

`generated/` is the only place kibo writes, and it is disposable: delete it, run
`python3 ../../kibo-project/kibo_project.py generate --target cpp` from `features/`, and
everything comes back. Nothing else in this directory is generated, so "who wrote this file?"
is answered by which directory it sits in.

```
cpp/
  CMakeLists.txt     hand-written
  run_test.sh        hand-written
  src/contract.cpp   hand-written: the bridge's contract, seen by a developer
  generated/         kibo, and nobody else
```

## Two programmes, one generated and one written

`features_test` is **generated**, by the laboratory's `TestApp` feature: it round-trips every
type of the model, takes every attachment through a database, and checks every declared default
value and default key. It can only check what the generator already knows how to state; that is
why it is generic, and why it runs on any model (`--definitions`, see the site's README).

`features_contract` is **written**: what a round trip does not show -- the type `encode`
returns, `decode` refusing a value of the wrong type, a key of another concept first. It is
what a C++ developer relies on without the generator saying so, checked from outside the
generated code. It is built only against this site's own model.

## One cost, paid in `CMakeLists.txt`

The generated test programme carries a `main()` and sits in the same directory as the library
sources, so the glob excludes it by name (`_test_app.cpp`) before building the library. That
line is the price of putting all generated output in one directory, and it is cheaper than the
ambiguity it replaces.

## Build

From the repository root, after generating:

    cd features && python3 ../../kibo-project/kibo_project.py generate --target cpp
    cd ../.. && mkdir -p build && cd build && cmake .. && cmake --build . -j

`run_test.sh` does the same and runs both programmes (`features_contract` only on this site's
own model).
