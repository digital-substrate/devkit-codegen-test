"""Topology — le modèle, et ce qu'aucune unité ne peut revendiquer.

ÉCRIT DEPUIS LE MODÈLE, PAS DEPUIS LE C++. Les décisions qui ont tenu en C++ tenaient
*parce que* C++ : l'ADL, les templates, les namespaces imbriqués. Python n'a rien de tout
cela et n'en a pas besoin — ce qui change la réponse, pas seulement l'écriture.

CE QUI RESTE AU SOCLE EST PLUS PETIT QU'EN C++, et pour une raison qui ne se transpose pas.
En C++, le socle portait `encode`/`decode` parce qu'une valeur C++ et une `Value` du runtime
sont deux choses qu'il faut faire passer l'une dans l'autre. Ici une valeur générée *est*
une `Value` : il n'y a pas de passage, donc pas de couche pour le faire. Il ne reste que
les définitions du modèle.
"""

from __future__ import annotations

import functools
import pathlib

import dsviper


@functools.cache
def definitions() -> dsviper.DefinitionsConst:
    """Le modèle, tel que le runtime le connaît.

    Assemblé depuis le `.dsm` ici, parce que c'est une référence et qu'elle doit pouvoir
    tourner. Un paquet livré embarque le document compressé et le décode — même objet, même
    résultat, et c'est la seule différence entre ce fichier et celui qui sera généré.
    """
    from dsviper import DSMBuilder

    source = pathlib.Path(__file__).resolve().parents[5] / "namespaces" / "definitions"
    report, dsm, _ = DSMBuilder.assemble(str(source)).parse()
    if report.has_error():
        raise RuntimeError("\n".join(repr(e) for e in report.errors()))

    return dsm.to_definitions().const()
