# consumers — the shapes of the generated code's real consumers

Viper has two databases that share nothing: a `Database`, read and written whole, and a Commit
database, read through a state and written by mutations. The pack generates each usage on its
own (`DatabaseAttachments`, `CommitAttachments`). This site renders one small model for each
shape of consumer that meets them, and checks that each gets its usage and nothing of the other:

| Shape | Features | For instance |
|---|---|---|
| `commit-app`: a Commit application with pools | `Base`, `CommitAttachments`, `Pool`, `AttachmentPool` | an editor whose document is a Commit database |
| `database-app`: a Database application | `Base`, `DatabaseAttachments` | a viewer reading exported databases as they are |
| `library`: a library compiled by applications of both usages, reading either base | `LibraryReads`, the laboratory's | a render engine both of them compile (C++); a converter reading either base (Python) |

A library must not choose a usage for its applications. It renders its own reads -- `keys`, `has`,
`get` over an `AttachmentGetting`, in its own namespace -- from a template of its own
(`../templates/cpp/reads.*.stg`, `../templates/python/reads.py.stg`), and takes from the
application's infrastructure, which it names (`shop`), its `Base` only. Both applications compile
it, as applications compile a shared engine from its sources.

```
consumers/
  definitions/Store/   kibo.toml
  cpp/      commit-app/  database-app/  library/   (generated/ and src/ each)   common/   run_test.sh
  python/   commit-app/  database-app/  library/   apps/   fixture.py   code_names.py   run_test.sh
```

**`generated/` is kibo's; `src/`, `common/` and `apps/` are the developer's.** Both applications
write the same documents (`common/fixture.hpp`, `fixture.py`), each through its own usage, then
print what the library reads back.

## What the tests prove

| # | Invariant | C++ | Python |
|---|---|---|---|
| I1 | No generated module mixes two usages | each application renders its usage's module only; `commit_attachments` includes no `Viper_Database.hpp`, `database_attachments` names nothing of Commit | the same, on the modules' code (`code_names.py`: comments and docstrings aside) |
| I2 | The library reads through its own reads, over `Base` | its sources include no `*_attachments` header; its objects call none (`nm -u`) | its code imports no `*_attachments` module |
| I3 | The Database application references nothing of Commit | its sources name nothing of Commit; no object it compiles -- its own, the generated ones, the library's -- references `Viper::Commit…` or `Viper::AttachmentMutating` (`nm -u`; the viper runtime it links carries Commit whole) | its modules' code names nothing of Commit, the runtime every usage shares (`_codegen`) aside |
| I4 | The library reads the same documents from a `Database` and from a Commit state | the two applications print the same | the same, and the same text as the C++ |

The two Python applications' packages are both named `shop`: each runs in its own interpreter.
