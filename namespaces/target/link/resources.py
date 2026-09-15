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

HEAD = """// modèle {model} — le modèle, en octets.
//
// LE .DSM EMBARQUÉ TEL QUEL. Le générateur ne produit aucun code d'enregistrement de types :
// le document est embarqué et décodé au chargement. C'est aussi la réponse à « qui tient la
// liste des concepts connus » -- cette donnée-là.
//
// Produit par `link/resources.py`, qui encode les définitions comme la chaîne de production
// le fait. Ce n'est pas un texte écrit à la main : ce sont les octets.
#ifndef {model}_Resources_hpp
#define {model}_Resources_hpp

#include <cstddef>

"""

MODELS = {
    "Topology": ROOT / "namespaces" / "definitions",
    "Crossing": ROOT / "crossing" / "definitions",
    "Features": ROOT / "features" / "all.dsm",
    "Service": ROOT / "service" / "definitions" / "Service",
}

for model, definitions in MODELS.items():
    report, dsm, _ = DSMBuilder.assemble(str(definitions)).parse()
    if report.has_error():
        raise SystemExit("\n".join(repr(e) for e in report.errors()))

    blob = dsm.to_definitions().const().encode()
    body = blob.embed("definitions").replace(
        "static unsigned char const definitions_data[]", "inline constexpr unsigned char definitions[]")

    out = ROOT / "namespaces/target/link/resources" / f"{model}_Resources.hpp"
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(HEAD.format(model=model) + f"namespace {model}::Resources {{\n\n{body}\n"
                   f"}} // namespace {model}::Resources\n\n#endif\n")
    print(f"  {model:10} {len(body.splitlines()):5} lignes d'octets")
