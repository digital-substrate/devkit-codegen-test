#!/bin/bash
# Le paquet généré est sous generated/ ; il n'est pas installé, on le met sur le chemin.
cd "$(dirname "${BASH_SOURCE[0]}")"
PYTHONPATH="$PWD/generated" python3 -m unittest discover tests
