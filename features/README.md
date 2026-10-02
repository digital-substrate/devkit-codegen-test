# features — the whole type system, and no pools

`all.dsm` declares one namespace, `Demo`, and exercises every feature the generator has
except the pools: those are `service/`'s job. Concepts, clubs, enumerations, structures, the
full container tree, attachments, the database.

Generated from the template pack, the sibling `kibo-template-viper` checkout (or
`KIBO_TEMPLATES`), plus the laboratory's own test templates in `../templates`.

```
features/
  all.dsm              the source
  kibo.toml            what is generated, and where
  features.dsm.json    deposited by kibo-project

  cpp/          generated/            run_test.sh   CMakeLists.txt
  python/       generated/features/   run_test.sh   tests/
  typescript/   generated/src/        run_test.sh   test/
```

**`generated/` is the only place kibo writes, and it is disposable.** Delete any of them, run
kibo-project, and it comes back. Nothing else in a language directory is generated, so "who
wrote this file?" is answered by which directory it sits in.

## Running it

    python3 ../../kibo-project/kibo_project.py generate
    cpp/run_test.sh · python/run_test.sh · typescript/run_test.sh

**Any model, not only `all.dsm`.** `--definitions` takes a file or a folder of definitions: the C++
test programme is generated from the model it is given, so it checks a real project's model as
it checks this one -- every type round-tripped, every attachment through a database, every
declared default value, every default key. A model with pools gets stand-in implementations
(`TestBridges`), since nobody implements them here. Only the C++ programme is generic; the
Python and TypeScript suites are written against `all.dsm`.

    python3 ../../kibo-project/kibo_project.py generate --target cpp \
        --definitions ../../kibo-2/com.digitalsubstrate.red/definitions/RE && cpp/run_test.sh

| | what it proves |
|---|---|
| C++ | the library builds against the real runtime and the generated programme runs |
| Python | 474 tests, against the package as generated |
| TypeScript | 465 tests, against the compiled package |

The Python and TypeScript suites were written by the project against the previous, flat
naming (`Test_StructureS`). They now name what the templates produce (`features.demo`,
`StructureS`) — ported once, in place, rather than translated on every run.

## Debts, visible on purpose

- **`_codegen/` is copied into every generated package** (Python and TypeScript): the pack's
  runtime, its exposition rather than `dsviper`'s, versioned with the templates. Each package
  carries its own copy. The C++ side carries none: its static layer is viper's.
- **The C++ test programme is generated.** In Python and TypeScript the tests are
  hand-written; here the developer receives a programme they did not write, which can only
  check what the generator already knows how to state.
- **The generated prose is in French**, and lands in the reader's source tree.
