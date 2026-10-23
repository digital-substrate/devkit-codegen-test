#!/bin/bash
# The consumers' invariants, in Python: each line `ok ...`, or the reason and a non-zero exit.
# Both applications' packages are named `shop`: each runs in its own interpreter.
set -e
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
fail() { echo "FAIL $*"; exit 1; }
# The names the code of these files uses that match a pattern, comments and docstrings aside.
names() { local pattern="$1"; shift; python3 "$HERE/code_names.py" "$@" | grep -xE "$pattern" || true; }

# I1: no generated module mixes two usages.
DATABASE_PACKAGE="$HERE/database-app/generated/shop"
COMMIT_PACKAGE="$HERE/commit-app/generated/shop"
[ -e "$DATABASE_PACKAGE/store/commit_attachments.py" ] && fail "I1: the Database application renders commit_attachments"
[ -e "$COMMIT_PACKAGE/store/database_attachments.py" ] && fail "I1: the Commit application renders database_attachments"
[ -n "$(names "CommitAttachmentMutating|Commit.*|commit_attachments" "$DATABASE_PACKAGE/store/database_attachments.py")" ] && fail "I1: database_attachments names Commit"
for app in commit-app database-app; do
    [ -n "$(names "CommitAttachmentMutating|Commit.*|_set_in_.*|_update|_delete" "$HERE/$app/generated/shop/store/reads.py")" ] && fail "I1: $app's reads write or name Commit"
done
echo "ok I1: commit_attachments, database_attachments and reads each hold one usage"

# I2: the library imports none of the application's attachments.
[ -n "$(names ".*_attachments" "$HERE"/library/src/*.py)" ] \
    && fail "I2: the library imports an application attachments module"
echo "ok I2: the library reads through the reading usage only"

# I3: the Database application's modules name nothing of Commit -- its runtime aside, which every
# usage shares (_codegen), as the viper runtime is shared in C++.
FILES=$(find "$DATABASE_PACKAGE" -name "*.py" -not -path "*/_codegen/*")
[ -n "$(names "CommitAttachmentMutating|Commit.*|commit_attachments" $FILES "$HERE"/apps/database_app.py)" ] \
    && fail "I3: Commit named in the Database application"
echo "ok I3: the Database application names nothing of Commit"

# The library is typed against the reading usage: mypy --strict, beside each application.
if python3 -m mypy --version > /dev/null 2>&1; then
    CACHE="$(mktemp -d)"
    for app in database-app commit-app; do
        MYPYPATH="$HERE/$app/generated:$HERE/library/src" \
            python3 -m mypy --strict --cache-dir "$CACHE" -m library_describe > /dev/null \
            || fail "mypy --strict: the library beside $app"
    done
    rm -rf "$CACHE"
    echo "ok the library passes mypy --strict beside either application"
fi

# I4: the same documents, read by the library from a Database and from a Commit state.
LIBRARY_PATH="$HERE/library/src:$HERE"
DATABASE_OUT="$(PYTHONPATH="$HERE/database-app/generated:$LIBRARY_PATH" python3 "$HERE/apps/database_app.py")"
COMMIT_OUT="$(PYTHONPATH="$HERE/commit-app/generated:$LIBRARY_PATH" python3 "$HERE/apps/commit_app.py")"
[ -n "$DATABASE_OUT" ] || fail "I4: the library read nothing"
[ "$DATABASE_OUT" = "$COMMIT_OUT" ] || fail "I4: the reads differ
$DATABASE_OUT
---
$COMMIT_OUT"
echo "ok I4: the library reads the same from a Database and from a Commit state ($(echo "$DATABASE_OUT" | wc -l | tr -d ' ') documents)"

# The C++ library reads the same documents: the same text, in both languages.
CPP="$HERE/../../build/consumers/cpp/consumers_database_app"
if [ -x "$CPP" ]; then
    [ "$DATABASE_OUT" = "$("$CPP")" ] || fail "the Python and C++ libraries read differently
$DATABASE_OUT
---
$("$CPP")"
    echo "ok the Python library reads what the C++ library reads"
fi
