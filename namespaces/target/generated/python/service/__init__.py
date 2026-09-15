# Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/service/Service.dsm.json by kibo-2.0.0.jar

"""Service — le modèle, et ce qu'aucune unité ne peut revendiquer.

UN NAMESPACE EST UN PAQUET, ET C'EST GRATUIT. `ModelA::Colour` est `service.modela.Colour`
et `ModelB::Colour` est `service.modelb.Colour` : les deux coexistent sans qu'un nom bouge.
Ce qui a déclenché ce chantier coûte, ici, une arborescence de fichiers.

CE QUI RESTE AU SOCLE EST PLUS PETIT QU'EN C++. Là-bas il portait `encode`/`decode` parce
qu'une valeur C++ et une `Value` du runtime sont deux choses qu'il faut faire passer l'une
dans l'autre ; ici une valeur générée *est* une Value. Il n'y a pas de passage, donc pas de
couche pour le faire — il ne reste que les définitions.
"""

from __future__ import annotations

import base64
import functools
import zlib

import dsviper

from . import resources


@functools.cache
def definitions() -> dsviper.DefinitionsConst:
    """Le modèle, tel que le runtime le connaît.

    LE DOCUMENT EMBARQUÉ, DÉCODÉ AU CHARGEMENT. Le générateur ne produit aucun code
    d'enregistrement de types : c'est aussi la réponse à « qui tient la liste des concepts
    connus » -- cette donnée-là.
    """
    blob = dsviper.ValueBlob(zlib.decompress(base64.b64decode(resources.B64_DEFINITIONS)))
    return dsviper.Definitions.decode(blob).const()