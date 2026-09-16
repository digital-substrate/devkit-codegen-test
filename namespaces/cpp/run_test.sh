#!/bin/bash
set -e
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cmake -S "$ROOT" -B "$ROOT/build" > /dev/null
cmake --build "$ROOT/build" -j --target topology_test > /dev/null
"$ROOT/build/namespaces/cpp/topology_test"
