#!/bin/bash
# Build the kibo-generated `features` package and run the TypeScript test suite.
# Requires the @digitalsubstrate/dsviper binding to be installable/available.
set -e
cd "$(dirname "$0")"
npm install
./node_modules/.bin/tsc -p features/tsconfig.json
node --test test/*.test.mjs
