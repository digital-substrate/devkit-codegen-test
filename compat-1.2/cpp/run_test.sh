#!/bin/bash
# The database is opened read-only: the test never modifies it.
set -e
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cmake -S "$ROOT" -B "$ROOT/build" > /dev/null
cmake --build "$ROOT/build" -j --target compat_read > /dev/null
"$ROOT/build/compat-1.2/cpp/compat_read" "$ROOT/compat-1.2/Compat-1.2.cdb"
