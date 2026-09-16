# typescript — flat, like the pack

A namespace is a **module directory**, as in Python: `Core::Colour` reaches a consumer as
`import { Colour } from 'pkg/core'`.

The container views return a `globalThis.Proxy` from their constructor so unknown properties
forward to the underlying value — the JS counterpart of `__getattr__`, written that way
because it is the only form that keeps `instanceof` working.

## Open

- **`_codegen/` is vendored per package**, same as Python, and belongs in
  `@digitalsubstrate/dsviper`.
- **The `.d.ts` surface has not been judged from outside**: no `exports` map, no ESM/CJS
  decision, and `tsc --strict` has only ever run on code generated and consumed inside this
  repository.
- **The generated prose is in French.**
