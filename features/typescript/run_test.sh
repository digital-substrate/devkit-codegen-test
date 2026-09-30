#!/bin/bash
# Compiles the generated package, then runs the suite against the compiled output.
set -e
cd "$(dirname "${BASH_SOURCE[0]}")"
./node_modules/.bin/tsc -p generated/tsconfig.json
node --test test/*.mjs
