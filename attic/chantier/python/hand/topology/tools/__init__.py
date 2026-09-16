"""Tools — ce que ce pool expose.

Un pool est une unité, donc un paquet, et son initialisateur ne porte que des noms — comme
celui de n'importe quelle autre unité. Rien ici ne distingue un pool d'un namespace, et
c'est le propos : ce qui les sépare est ce qu'ils contiennent, pas la forme qu'ils prennent.

    from topology.tools import Pool, Remote
"""

from .pool import Pool, Remote
