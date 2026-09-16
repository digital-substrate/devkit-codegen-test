# cpp — the C++ side of the features site

`generated/` is the only place kibo writes, and it is disposable: delete it, run
`../generate.py all.dsm -c`, and everything comes back. Nothing else in this directory is
generated, so "who wrote this file?" is answered by which directory it sits in. That is the
whole point of the split — before it, the generated library and the test programmes were
siblings at the site root and no one could tell them apart without opening them.

```
cpp/
  CMakeLists.txt     hand-written
  run_test.sh        hand-written
  generated/         kibo, and nobody else
```

## There is no `test/` here, and that is the finding

In Python and TypeScript the tests are hand-written and live in `test/`. In C++ they are
**generated**: the four programmes — codec, database, database fuzz, database remote — come
out of the `TestApp` template. A C++ developer receives tests they did not write; a Python
developer writes their own.

That asymmetry is not obviously right. It means the C++ tests can only ever check what the
generator already knows how to state, and that nothing a human noticed can be added to them
without being added to a template first. Recorded here rather than tidied away; a `test/`
directory appears the day something is written by hand.

## One cost, paid in `CMakeLists.txt`

The four programmes each carry a `main()`, and they now sit in the same directory as the
library sources. The glob therefore excludes them by name before building the library. That
line is the price of putting all generated output in one directory, and it is cheaper than
the ambiguity it replaces.

## Build

From the repository root, after generating:

    cd features && python3 generate.py all.dsm -c
    cd ../.. && mkdir -p build && cd build && cmake .. && cmake --build . -j

`run_test.sh` does the same and runs the four programmes.
