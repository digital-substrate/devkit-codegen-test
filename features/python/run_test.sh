#!/bin/bash
# The generated package is under generated/; it is not installed, so it is put on the path.
cd "$(dirname "${BASH_SOURCE[0]}")"
PYTHONPATH="$PWD/generated" python3 -m unittest discover tests
