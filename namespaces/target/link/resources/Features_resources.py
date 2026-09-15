"""modèle Features — le modèle, en octets.

LE .DSM EMBARQUÉ TEL QUEL, compressé et encodé. Le générateur ne produit aucun code
d'enregistrement de types : le document est embarqué et décodé au chargement.

Produit par `link/resources.py`. Ce n'est pas un texte écrit à la main.
"""

B64_DEFINITIONS = (
    "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"
)
