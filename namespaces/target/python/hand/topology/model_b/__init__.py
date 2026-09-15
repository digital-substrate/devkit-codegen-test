"""ModelB — ce que cette unité expose.

L'INITIALISATEUR EST CE QUE LE LECTEUR IMPORTE, ET IL NE PORTE QUE DES NOMS. Les classes
vivent dans `data`, les attachments dans `attachments` ; ici il n'y a que la liste de ce que
l'unité rend public. Deux raisons, et la seconde est la vraie : un module qui ne contient
rien ne peut pas créer de cycle d'import, et `attachments` a besoin de `data` alors que le
lecteur veut les deux sous le même nom.

    from topology.model_b import Colour, MaterialKey
    from topology.model_b import attachments
"""

from .data import *
from . import attachments
