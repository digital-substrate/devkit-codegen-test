#!/bin/bash
# The tests receive the rendered package: they do not guess where it is.
set -e
cd "$(dirname "${BASH_SOURCE[0]}")"
for t in test/*.py; do
    echo "── $(basename "$t")"
    PYTHONPATH="$PWD/generated" python3 "$t" "$PWD/generated"
done
