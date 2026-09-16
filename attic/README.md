# attic — the exploratory workshop, kept because it still measures things

`chantier/` is where the namespace-based templates were designed. It has been put aside, not
deleted, because it holds instruments that nothing else replaces yet:

- `*/render.py` renders all four models, compiles the C++ against the real runtime headers,
  links `libviper.a`, type-checks Python and TypeScript, and runs both foreign suites.
- `*/link/migrate.py` ports a foreign test suite onto the new naming. It contains renames and
  nothing else, on purpose: its length *is* the migration cost, and a hand port would measure
  nothing. It reads attachment names from the rendered package rather than guessing them.
- `check.py` runs all three targets in sequence -- which is how a fix for one target that
  broke another was caught.
- `*/hand/` are hand-written references: what the output *should* look like, written before
  the template that produces it.

**It is not where to look for generated code.** Every site -- `features/`, `service/`,
`namespaces/`, `crossing/` -- generates into its own `cpp/`, `python/` and `typescript/`
directories. The chantier renders a second copy into `chantier/generated/` for its own
comparisons; that copy is an instrument, not an artefact.

What was lifted out of it, because the sites need it:

| | moved to | why |
|---|---|---|
| the templates | `templates/` | one source, selected by `features.json` |
| `runtime-proposed/` | repository root | the sites compile and ship it |
