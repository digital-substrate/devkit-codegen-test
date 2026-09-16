#!/bin/bash
# L'épreuve : le client TypeScript parle au serveur C++. Un seul serveur pour les trois
# langages -- c'est l'intérêt, le protocole ne connaît pas le langage de ses bords.
set -e
cd "$(dirname "${BASH_SOURCE[0]}")"
ROOT="$(cd ../.. && pwd)"
BUILD="$ROOT/build"
PORT=54329

./node_modules/.bin/tsc -p generated/tsconfig.json
./node_modules/.bin/tsc src/client.ts --outDir build --module nodenext --target es2022 \
    --moduleResolution nodenext --types node

cmake -S "$ROOT" -B "$BUILD" > /dev/null
cmake --build "$BUILD" -j --target service_server > /dev/null

"$BUILD/service/cpp/service_server" -a localhost -p $PORT &
SERVER=$!
trap 'kill $SERVER 2>/dev/null; wait $SERVER 2>/dev/null' EXIT
sleep 1

node build/client.js localhost $PORT
