#!/bin/bash
# Construit la bibliothèque générée et lance le programme d'épreuve.
set -e
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
BUILD="$ROOT/build"
cmake -S "$ROOT" -B "$BUILD" > /dev/null
cmake --build "$BUILD" -j --target features_test features_contract > /dev/null
"$BUILD/features/cpp/features_contract"
"$BUILD/features/cpp/features_test"
