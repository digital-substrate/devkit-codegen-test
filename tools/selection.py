#!/usr/bin/env python3
"""Ce que la sélection des features rend -- et ce qu'elle ne rend pas.

UN MODÈLE QUI DÉCLARE DES POOLS N'IMPOSE PAS DE POOLS AU CODE GÉNÉRÉ. Une application Python
pure ne peut pas construire de pool : elle sélectionne `Base`, et doit recevoir un paquet sans
un seul dossier de pool. Tant que le point d'entrée d'un pool vivait dans le template des
unités, elle en recevait un par pool, qui importait un module absent. Ce script rend le modèle
`namespaces` -- trois pools -- avec `Base` seul puis avec `Pool`, dans chaque binding.
"""
import json
import re
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from render import TEMPLATES, definitions, jar, kibo   # noqa: E402
from models import MODELS                             # noqa: E402

sys.path.insert(0, str(TEMPLATES))
import resolve                                         # noqa: E402

MODEL = "namespaces"


def pools(dsm: Path) -> set[str]:
    """The package directory each pool of the model renders to."""
    data = json.loads(dsm.read_text())
    names = [p["name"] for key in ("function_pools", "attachment_function_pools")
             for p in data.get(key, [])]
    # A pool's package is its name in lower snake case, as the layout writes it.
    return {re.sub(r"(?<!^)(?=[A-Z])", "_", n).lower() for n in names}


def rendered(language: str, features: list[str], dsm: Path, jar_path: str) -> set[str]:
    with tempfile.TemporaryDirectory() as out:
        for template in resolve.templates(language, features):
            kibo(jar_path, language, MODELS[MODEL]["package"], dsm, template, Path(out))
        return {p.name for p in Path(out).iterdir() if p.is_dir()}


def main() -> int:
    dsm = definitions(MODEL)
    jar_path = jar()
    expected = pools(dsm)
    ok = bool(expected)
    for language in ("python", "typescript"):
        alone = rendered(language, ["Base"], dsm, jar_path) & expected
        with_pool = rendered(language, ["Base", "Pool"], dsm, jar_path) & expected
        good = not alone and with_pool == expected
        ok &= good
        print(f"  {'ok  ' if good else 'ÉCHEC'} {language}: Base seul -> {sorted(alone) or 'aucun pool'}, "
              f"avec Pool -> {sorted(with_pool)}")
    return 0 if ok else 1


if __name__ == "__main__":
    raise SystemExit(main())
