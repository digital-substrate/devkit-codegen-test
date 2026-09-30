#!/usr/bin/env python3
"""What the feature selection renders -- and what it does not.

A model that declares pools does not impose pools on the generated code. A pure Python
application cannot build a pool: it selects `Base`, and must receive a package without a
single pool directory. While a pool's entry point lived in the unit template, it received one
per pool, importing a missing module. This script renders the `namespaces` model -- three
pools -- with `Base` alone and then with `Pool`, in each binding.
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
        print(f"  {'ok  ' if good else 'FAIL'} {language}: Base alone -> {sorted(alone) or 'no pool'}, "
              f"with Pool -> {sorted(with_pool)}")
    return 0 if ok else 1


if __name__ == "__main__":
    raise SystemExit(main())
