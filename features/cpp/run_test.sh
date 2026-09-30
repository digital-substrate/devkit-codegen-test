#!/bin/bash
# Builds the generated library and runs the test programs.
# features_contract is written against this site's own model (all.dsm); it is built and run only
# when that model is the one generated, so the site can also check another folder of definitions.
set -e
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
BUILD="$ROOT/build"
OWN_MODEL="$ROOT/features/cpp/generated/features_demo_data.hpp"
TARGETS="features_test"
[ -f "$OWN_MODEL" ] && TARGETS="$TARGETS features_contract"
cmake -S "$ROOT" -B "$BUILD" > /dev/null
cmake --build "$BUILD" -j --target $TARGETS > /dev/null
[ -f "$OWN_MODEL" ] && "$BUILD/features/cpp/features_contract"
"$BUILD/features/cpp/features_test"
