# features — the whole type system, and no pools

`all.dsm` declares one namespace, `Demo`, and exercises every feature the generator has
except the pools: those are `service/`'s job. Concepts, clubs, enumerations, structures, the
full container tree, attachments, the database.

Generated from `../templates`, the sandbox pack — not from a sibling `kibo-template-viper`
checkout. Set `KIBO_TEMPLATES` to point elsewhere deliberately.

```
features/
  all.dsm              the source
  Features.dsm.json    deposited by generate.py
  generate.py          -c / -p / -t

  cpp/          generated/            run_test.sh   CMakeLists.txt
  python/       generated/features/   run_test.sh   tests/
  typescript/   generated/src/        run_test.sh   test/
```

**`generated/` is the only place kibo writes, and it is disposable.** Delete any of them, run
`generate.py`, and it comes back. Nothing else in a language directory is generated, so "who
wrote this file?" is answered by which directory it sits in.

## Running it

    python3 generate.py all.dsm -c -p -t
    cpp/run_test.sh · python/run_test.sh · typescript/run_test.sh

| | what it proves |
|---|---|
| C++ | the library builds against the real runtime and the generated programme runs |
| Python | 474 tests, against the package as generated |
| TypeScript | 465 tests, against the compiled package |

The Python and TypeScript suites were written by the project against the previous, flat
naming (`Test_StructureS`). They now name what the templates produce (`features.demo`,
`StructureS`) — ported once, in place, rather than translated on every run.

## Debts, visible on purpose

- **`_codegen/` is copied into every generated package** (Python and TypeScript), and
  `runtime-proposed/cpp` is compiled into the C++ library. None of it names a model type or
  varies between models: it belongs in the runtime. Until it moves, each package carries a
  copy that can drift from the `dsviper` installed beside it.
- **The TypeScript project files are written by `generate.py`**, not rendered: there is no
  `Project` feature in `templates/typescript` yet. Inventing a `package.json` is not the
  project's job.
- **The C++ test programme is generated.** In Python and TypeScript the tests are
  hand-written; here the developer receives a programme they did not write, which can only
  check what the generator already knows how to state.
- **The generated prose is in French**, and lands in the reader's source tree.
