#!/bin/bash
# The consumers' invariants, in C++: each line `ok ...`, or the reason and a non-zero exit.
set -e
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$(cd "$HERE/../.." && pwd)"
BUILD="$ROOT/build"
cmake -S "$ROOT" -B "$BUILD" > /dev/null
cmake --build "$BUILD" -j --target consumers_database_app consumers_commit_app > /dev/null

fail() { echo "FAIL $*"; exit 1; }
# The lines of code that name a word, comments aside: a comment may point to the other usage.
names() { local word="$1"; shift; grep -h "$word" "$@" | grep -v "^ *//" || true; }

# I1: no generated module mixes two usages; the reading usage writes nothing.
[ -n "$(names "Viper_Database.hpp" "$HERE"/commit-app/generated/*commit_attachments*)" ] && fail "I1: commit_attachments includes Viper_Database"
[ -n "$(names "Commit\|AttachmentMutating" "$HERE"/database-app/generated/*database_attachments*)" ] && fail "I1: database_attachments names Commit"
ls "$HERE"/commit-app/generated/*database_attachments* 2> /dev/null && fail "I1: the Commit application renders database_attachments"
ls "$HERE"/database-app/generated/*commit_attachments* 2> /dev/null && fail "I1: the Database application renders commit_attachments"
for app in commit-app database-app; do
    [ -n "$(names "AttachmentMutating\|Viper_Database.hpp\|Commit" "$HERE"/$app/generated/*_reads.*)" ] && fail "I1: $app's reads write or name Commit"
done
echo "ok I1: commit_attachments, database_attachments and reads each hold one usage"

# I2: the library includes none of the application's attachments, and calls none.
grep -h "#include" "$HERE"/library/src/* | grep -q "_attachments" \
    && fail "I2: the library includes an application attachments header"
OBJECTS="$BUILD/consumers/cpp/CMakeFiles/consumers_database_app.dir"
for o in $(find "$OBJECTS" -path "*library*" -name "*.o"); do
    nm -u "$o" | grep -q "database_attachments\|commit_attachments" && fail "I2: $(basename "$o") calls the application's attachments"
done
echo "ok I2: the library reads through the reading usage only"

# I3: the Database application references nothing of Commit, generated or its own, nor the
# library compiled in it. On its object files: the viper runtime it links carries Commit whole.
[ -n "$(names "Commit\|AttachmentMutating" "$HERE"/database-app/generated/* "$HERE"/database-app/src/*)" ] && fail "I3: Commit named in the Database application's sources"
for o in $(find "$OBJECTS" -name "*.o"); do
    if nm -u "$o" | c++filt | grep -q "Viper::Commit\|Viper::AttachmentMutating"; then
        fail "I3: $(basename "$o") references Commit"
    fi
done
echo "ok I3: the Database application and the library compiled in it reference nothing of Commit"

# I4: the same documents, read by the library from a Database and from a Commit state.
DATABASE_OUT="$("$BUILD/consumers/cpp/consumers_database_app")"
COMMIT_OUT="$("$BUILD/consumers/cpp/consumers_commit_app")"
[ -n "$DATABASE_OUT" ] || fail "I4: the library read nothing"
[ "$DATABASE_OUT" = "$COMMIT_OUT" ] || fail "I4: the reads differ
$DATABASE_OUT
---
$COMMIT_OUT"
echo "ok I4: the library reads the same from a Database and from a Commit state ($(echo "$DATABASE_OUT" | wc -l | tr -d ' ') documents)"
