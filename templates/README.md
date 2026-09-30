# templates — the pack under construction

What `kibo-template-viper` will hold once this line is settled. It lives here, in the test
repository, for exactly as long as it is unfinished: a template that renders is not yet a
template a developer can read, and the four sites next door are what tells the difference.

Point a site at it with `KIBO_TEMPLATES=../templates`. Every `.stg` carries the
`Templates: kibo-template-viper 2.0.0` stamp a project's `generate.py` greps for, so the
pinning check passes against the sandbox exactly as it does against the pack.

**One namespace is one unit.** That is the whole of what separates this line from the one it
replaces: C++ gets a file-name prefix, Python and TypeScript get a directory. Where the old
pack wrote `Namespace_Type`, two namespaces can now declare the same name and neither moves.

## Templates are flat; features are declared

The pack expresses selection through the file system — one directory per feature, because
`kibo -t` renders a directory. That makes the file system carry a graph, and a graph is not
what a directory tree is good at: `Attachments` needs `Database`, and no arrangement of
folders can say so.

So selection moves one level up. `features.json` maps a **feature** — what a project asks for
— to the templates that render it and the features it requires. `resolve.py` walks the
closure:

```
$ ./resolve.py cpp Attachments
features : Base Fields Attachments
  data.cpp.stg  codec.cpp.stg  model.cpp.stg  any_concept.cpp.stg  ...  attachments.hpp.stg
```

`kibo -t` accepts a single `.stg` as readily as a directory, so nothing in the generator had
to change for this.

**`requires` was measured, not decided.** It is the `#include` graph of the generated C++,
interface (`.hpp → .hpp`) and build (`.cpp → .hpp`) unioned, since asking for a feature means
compiling it. That measurement is also how the one backwards edge was found — see
`cpp/README.md`. Re-measure when templates move.

## Layout

| | shape |
|---|---|
| `cpp/*.stg` | flat, 24 templates, 7 features and 3 for the laboratory only (`Test`, `TestApp`, `TestBridges`) |
| `python/*.stg` | flat, 3 features: `Base`, `Pool`, `Wheel` |
| `typescript/*.stg` | flat, 3 features: `Base`, `Pool`, `Package` |

A generated file carries a header and the documentation the model declares, and no other prose.
