# Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/features/Features.dsm.json by kibo-2.0.0.jar

"""Demo — ce que cette unité expose.

L'INITIALISATEUR NE PORTE QUE DES NOMS. Les classes vivent dans `data`, les attachments
dans `attachments`, et l'un des deux n'est pas importé ici : un initialisateur qui
importerait `attachments` ferait de l'import d'une unité l'import de tout ce qu'elle
atteint, et deux unités qui se référencent par un attachment deviendraient un cycle.

    from features.demo import attachments
"""

from .data import *