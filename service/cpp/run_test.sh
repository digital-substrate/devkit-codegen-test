#!/bin/bash
# A service is tested by a client talking to a server: build both, start the server on a
# local socket, run the client, clean up.
set -e
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
BUILD="$ROOT/build"
BIN="$BUILD/service/cpp"
SOCKET="$(mktemp -u)"

cmake -S "$ROOT" -B "$BUILD" > /dev/null
cmake --build "$BUILD" -j --target service_server service_client > /dev/null

"$BIN/service_server" -s "$SOCKET" &
SERVER=$!
trap 'kill $SERVER 2>/dev/null; wait $SERVER 2>/dev/null || true; rm -f "$SOCKET"' EXIT

for _ in $(seq 40); do [ -S "$SOCKET" ] && break; sleep 0.1; done
[ -S "$SOCKET" ] || { echo "the server did not open $SOCKET"; exit 1; }

"$BIN/service_client" -s "$SOCKET" && STATUS=0 || STATUS=$?
exit $STATUS
