#!/bin/bash
# L'épreuve : le client Python parle au serveur C++. Le serveur est celui de cpp/, il n'y en
# a qu'un -- c'est tout l'intérêt, le protocole ne connaît pas le langage de ses bords.
set -e
cd "$(dirname "${BASH_SOURCE[0]}")"
ROOT="$(cd ../.. && pwd)"
BUILD="$ROOT/build"
PORT=54328

cmake -S "$ROOT" -B "$BUILD" > /dev/null
cmake --build "$BUILD" -j --target service_server > /dev/null

"$BUILD/service/cpp/service_server" -a localhost -p $PORT &
SERVER=$!
trap 'kill $SERVER 2>/dev/null; wait $SERVER 2>/dev/null || true' EXIT
sleep 1

PYTHONPATH="$PWD/generated" python3 src/client.py localhost $PORT && STATUS=0 || STATUS=$?
exit $STATUS
