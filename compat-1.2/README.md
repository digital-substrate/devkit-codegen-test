# compat-1.2

A database written by the 1.2 runtime, read back by what the generation produces today.

The 1.2 line froze the storage format. Whatever the templates become, a database a 1.2
application wrote must read back, value for value, through the code generated now. This
site holds one such database and checks exactly that.

```
compat-1.2/
  definitions/Compat.dsm   the model -- frozen
  Compat-1.2.cdb           the database -- written once, committed, opened read-only
  write_1_2.py             how the database was written, under a 1.2 runtime
  generate.py              -c renders the C++; -p / -t not yet
  cpp/   generated/  src/read.cpp  run_test.sh  CMakeLists.txt
```

## Why each piece is the way it is

**The model is frozen.** A database records its definitions. Reading it with a model that
moved on would test schema evolution, which is another question. A new shape is added by
extending `Compat.dsm` *and* rewriting the database with `write_1_2.py`, under a 1.2 runtime.

**The database is written by the runtime, not by generated code.** What a database holds --
definitions, values, codec -- is the runtime's business; generated code only builds values
the runtime checks against the definitions. Writing through `dsviper` pins what a 1.2
database is without depending on any generation, old or new. The script refuses to run
under anything but a 1.2 runtime.

**Every value is compared, not merely decoded.** A transposed matrix decodes without error --
six cells read for six written -- and only shows on comparison. The expectations in
`src/read.cpp` are written in the C++ types the generation gives, side by side with the
values `write_1_2.py` writes.

**Values are chosen to make a mistake visible**: integers whose bytes all differ, a
non-square matrix with distinct cells, a variant holding an alternative that is not the
first, keys and records nested inside containers.

## What it does not guard

The read path takes a value's shape from the stream, not from the C++ type, so a wrong type
*deduced* from a C++ shape does not show here -- it breaks writing, not reading. That is
guarded by `features/` (a non-square matrix inside a container, written to a database) and
by the static layout contract test in viper.

## Run

    ./check.py compat-1.2
