#!/usr/bin/env python3
"""Produire les octets d'un modèle, comme la chaîne de production le fait.

Un paquet livré embarque le document et le décode au chargement ; la référence doit faire
pareil, sinon elle se lie mais ne tourne pas -- ce qui était le cas tant que la ressource
était un octet nul.
"""
import base64
import sys
import zlib
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
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

    out = ROOT / "namespaces/target/cpp/link/resources" / f"{model}_Resources.hpp"
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(HEAD.format(model=model) + f"namespace {model}::Resources {{\n\n{body}\n"
                   f"}} // namespace {model}::Resources\n\n#endif\n")

    # LES MÊMES OCTETS, SOUS LA FORME QU'UN PAQUET PORTE. Un en-tête C++ embarque un tableau
    # d'octets ; une roue Python embarque une chaîne, compressée puis encodée, parce que
    # c'est ce qu'un fichier source Python sait contenir sans se déformer.
    payload = base64.b64encode(zlib.compress(bytes(blob))).decode()

    # NODE LIT LE BASE64 BRUT. `ValueBlob.base64Decode` fait le décodage lui-même, donc y
    # ajouter une compression obligerait le code rendu à embarquer zlib pour rien.
    plain = base64.b64encode(bytes(blob)).decode()
    chunks = "\n".join(f'    "{payload[i:i + 92]}"' for i in range(0, len(payload), 92))
    python = ROOT / "namespaces/target/cpp/link/resources" / f"{model}_resources.py"
    python.write_text(
        f'"""modèle {model} — le modèle, en octets.\n\n'
        "LE .DSM EMBARQUÉ TEL QUEL, compressé et encodé. Le générateur ne produit aucun code\n"
        "d'enregistrement de types : le document est embarqué et décodé au chargement.\n\n"
        'Produit par `link/resources.py`. Ce n\'est pas un texte écrit à la main.\n"""\n\n'
        f"B64_DEFINITIONS = (\n{chunks}\n)\n")

    # Et la même chaîne pour Node, qui la lit comme Python : embarquée dans une source.
    node = ROOT / "namespaces/target/cpp/link/resources" / f"{model}_resources.ts"
    node.write_text(
        f"// modèle {model} — le modèle, en octets.\n//\n"
        "// LE .DSM EMBARQUÉ TEL QUEL, compressé et encodé. Le générateur ne produit aucun code\n"
        "// d'enregistrement de types : le document est embarqué et décodé au chargement.\n//\n"
        "// Produit par `cpp/link/resources.py`. Ce n'est pas un texte écrit à la main.\n\n"
        "export const B64_DEFINITIONS =\n"
        + "\n".join(f'    "{plain[i:i + 92]}" +' for i in range(0, len(plain), 92))[:-2]
        + ";\n")

    print(f"  {model:10} {len(body.splitlines()):5} lignes d'octets, "
          f"{len(payload):6} caractères encodés")
