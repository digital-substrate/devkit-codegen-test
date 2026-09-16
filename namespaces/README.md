# namespaces — namespace topology, and nothing else

Six namespaces, including the global one, and every kind of edge between them: a homonym
declared twice (`ModelA::Colour` and `ModelB::Colour`), a namespace that references two
others, three pools. `features/` covers the type system in one namespace; this covers what
having several does to it.

Generated from `../templates`.

```
namespaces/
  definitions/  Topology.dsm.json  generate.py  check.py

  cpp/          generated/   src/   run_test.sh   CMakeLists.txt
  python/       generated/topology/  test/   run_test.sh
  typescript/   generated/src/       test/   run_test.sh
```

**`generated/` is kibo's; `src/` is the developer's.** The six files in `cpp/src` carry no
`main()`: each exercises one facet of the generated surface — fields, codec, json, an
attachment read, a pool — so compiling them proves the surface is usable, and linking them
proves it resolves. `application.cpp` implements what the three pools declare, which is the
line the generator does not cross.

## What the tests prove

    cpp/run_test.sh          the library links and the generated programme runs
    python/run_test.sh       23 assertions on the rendered package
    typescript/run_test.sh   4 assertions: two namespaces declare the same name, neither moved

The TypeScript check is the smallest statement of why this whole line exists. Where the
previous pack wrote `ModelA_Colour` and `ModelB_Colour` — a flattening that hides the clash
by having already resolved it inside the name — here the path *is* the namespace and `Colour`
stays `Colour`.

`check.py` at the site root is a different thing: it asserts the *model* still exercises what
it claims, and is run after regenerating the JSON.
