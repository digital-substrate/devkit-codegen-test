#!/bin/bash
# Compile le paquet généré, puis lance les épreuves contre le résultat compilé.
set -e
cd "$(dirname "${BASH_SOURCE[0]}")"
./node_modules/.bin/tsc -p generated/tsconfig.json
node --test test/*.mjs
