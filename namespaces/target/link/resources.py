#!/usr/bin/env python3
"""Produire les octets d'un modèle, comme la chaîne de production le fait.

Un paquet livré embarque le document et le décode au chargement ; la référence doit faire
pareil, sinon elle se lie mais ne tourne pas -- ce qui était le cas tant que la ressource
était un octet nul.
"""
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parent.parent.parent
sys.path.insert(0, str(ROOT / "tools"))

from dsviper import DSMBuilder                                      # noqa: E402

MODELS = {"Topology": ROOT / "namespaces" / "definitions"}

for model, definitions in MODELS.items():
    report, dsm, _ = DSMBuilder.assemble(str(definitions)).parse()
    if report.has_error():
        raise SystemExit("\n".join(repr(e) for e in report.errors()))

    blob = dsm.to_definitions().const().encode()
    body = blob.embed("definitions").replace(
        "static unsigned char const definitions_data[]", "inline constexpr unsigned char definitions[]")

    out = ROOT / "namespaces/target/hand" / f"{model}_Resources.hpp"
    head = out.read_text().split("namespace")[0]
    out.write_text(f"{head}namespace {model}::Resources {{\n\n{body}\n}} // namespace {model}::Resources\n\n#endif\n")
    print(f"  {model:10} {len(body.splitlines()):5} lignes d'octets")
