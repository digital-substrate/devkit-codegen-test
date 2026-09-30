# runtime-proposed — the runtime of the templates

The generated Python and TypeScript packages rely on code that no model decides: the base class
of the generated proxies, the registry that wraps and unwraps runtime values, the container
views, and the typed attachment accessor. It is written once, here, and every site copies it
into the package it generates, as `_codegen`.

| | Python (`python/`) | TypeScript (`node/`) |
|---|---|---|
| the proxy base, the registry | `proxy.py` | `proxy.ts`, `registry.ts` |
| the container views | `container.py` | `container.ts` |
| the attachment accessor | `attachment.py` | `attachment.ts` |

## Who owns what

The criterion: **the runtime takes what is not a choice; the template pack keeps what is one
exposition among others.**

- **This code belongs to the template pack**, and moves with the templates into
  `kibo-template-viper`. It is an exposition: a generated class is a proxy over a `Value` (a pack
  could as well copy the value, as the C++ templates do), the registry follows from that, and the
  container views — their names, their methods, their liveness — are the most visible choice of
  all. It does not move into `dsviper`.
- **What `dsviper` owes every pack are neutral capabilities.** The two this runtime needed are in
  the wheel since 1.2.27: a class hierarchy that `isinstance(value, dsviper.Value)` can test, and
  `Value.decode(..., encoded=False)`. The generated Python therefore requires
  `dsviper >= 1.2.27, < 1.3`.
- **C++ has nothing here.** The static layer — `Viper_StaticType`, `Viper_StaticWriter`,
  `Viper_StaticReader`, `Viper_StaticHash` — is viper's, on its `LTS-1.2` branch since
  2026-09-30. Two packs may shape the static side differently, but they cannot serialize it
  differently: there is one layout, the one `ValueReader` reads back. `AnyConceptKey` stays
  generated per model, because two models linked into one program would each define it.

## Known gap

The Node binding's aggregate mutations (`unionInSet` and its siblings) accepted only a `Value`
handle, and an xarray argument only in the projected form `dumps` writes. `attachment.ts`
therefore builds the value itself. The binding is fixed on viper `LTS-1.2`, not yet released on
npm; the workaround goes once a release carries the fix.
