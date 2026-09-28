#!/bin/bash
# Les épreuves reçoivent le paquet rendu : elles ne devinent pas où il est.
set -e
cd "$(dirname "${BASH_SOURCE[0]}")"
for t in test/*.py; do
    echo "── $(basename "$t")"
    PYTHONPATH="$PWD/generated" python3 "$t" "$PWD/generated"
done
