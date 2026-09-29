# cpp — flat templates, features declared in `../features.json`

A namespace here is a **file-name prefix**, not a directory: `ModelA_Data.hpp`. C++ already
has namespaces, so the generated code declares them; the file system carries only enough to
keep two same-named types in separate files.

Which templates a project renders is `../features.json`, resolved by `../resolve.py`. Nothing
about a feature is expressed by where a `.stg` sits.

## What the dependency measurement found

`requires` came from the `#include` graph of generated code, and two things fell out of it
that no reading had produced:

- **The interface graph is a clean DAG; every cycle is in the `.cpp`.** So
  `Data`/`Codec`/`Model`/`AnyConcept` are mutually dependent only at build time — but they
  are mutually dependent, so they are one feature, `Base`. There is no cut inside it.
- **`Attachments` depended on `Database`, backwards** -- `Attachments.cpp` included a
  `Db.hpp` of two one-line helpers, so a project that wanted attachments and no database could
  not have them. The helpers are now the bodies of the database overloads themselves, and the
  `Database` feature is gone: writing to a database is two overloads of an attachment, and
  the runtime provides everything they need.

## Laboratory only

`Test` and `TestApp` (`"laboratory": true` in `features.json`) test the generator -- every type
round-tripped through each codec, every attachment through a database, every pool through the
bridge. No project selects them: `red` and `ge` take neither. They stay in this laboratory and
do not move into the pack.

## Still merged, and known to be wrong

- **`Pool` holds its own remote side.** The pack separates `FunctionPool` from
  `FunctionPoolRemote`, and not for tidiness: most projects do not expose their pools as a
  service, and selecting the pool must not force the remote. The split is real work — the
  remote lives in sub-templates inside `Pool.cpp.stg` and `Pool.hpp.stg`, not in separate
  files.
- **The JSON codec is inside `Codec`.** The pack keeps `Json` selectable on its own.

Both were merged while exploring, and merging them was a mistake: a real project
(`com.digitalsubstrate.red`) selects 10 of 17 features and refuses exactly these.
