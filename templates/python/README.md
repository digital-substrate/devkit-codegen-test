# python — one package, rendered whole

A namespace is a **module**: `Core::Colour` is `<package>.core.Colour`. The path *is* the
namespace, which is why the generator owns the on-disk layout rather than the project script.

A generated class is a box around a `dsviper.Value` and holds nothing. Every write reaches
the runtime, so the runtime's fail-fast is inherited rather than re-implemented — and the
type annotations are what replaces the type the passage dissolves, for the reader and the
IDE, not as a second line of checking.

## Open

- **`_codegen/` is vendored into every generated package.** The proxy, the container views
  and the attachment wrapper are runtime code; copying them per package lets them drift from
  the installed `dsviper`. They belong in `dsviper`, and until they are there this package is
  not something to hand a developer.
- **The generated prose is in French.** It lands in the reader's source tree.
