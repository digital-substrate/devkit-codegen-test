"""modèle Topology — le modèle, en octets.

LE .DSM EMBARQUÉ TEL QUEL, compressé et encodé. Le générateur ne produit aucun code
d'enregistrement de types : le document est embarqué et décodé au chargement.

Produit par `link/resources.py`. Ce n'est pas un texte écrit à la main.
"""

B64_DEFINITIONS = (
    "eJydVn9sFEUUbrECPdgtERINtTgBAQ3XMyFqbEWwLSVSARsLgkiEud2525Hd2WVnt9dqiEEqAYIESURjRQmppRckqT8T"
    "0PiDwwixQQVEGw0mFDCYBiN/oFEE3+zu7bWyhML9de/dzLz3vve9711JaZH/KZ4gXdx36Ym2E1saFjdYY/vKNzZJHSPO"
    "f/Rl+SO1m0d17B9/+YAuDw8OzzdVotfKI/MmdohNsS5PCRw1yAhccYQ58o8jl6nE5g5mKkcmIwkv6Ina3YdmHX9njLLv"
    "2+P/dH79prTpzi/2fvPZY7M2rK77V5s/ThoctOb6gtZEBz12/qxWFdtzx9pjRb/eczTWKPXba1cfvW/eLR3b57495ZXO"
    "n+RY8GijbT5DFIeaTC4JXPMoWyknAmOxhh3xLtLBi5LEyRDCkJMxkWrTZmKHOXFEuR98/oSG0SeTbXN/2Dr73NKdH88a"
    "UvCywDWbiGfVsPjpYfGKyRRiOSijmZwgC9uEOZBVM4HIDGFmOhqkw7BBuIUVAKI4An1wTW5Zv6ttU732+JK/Xph2Zny3"
    "9NDEVTu7/1hQ375Xmn74+73HBzekrmBieyWx5YcDs8k0iKNRlkYYWWEhSMEMWSaF3LADfWIqEpmJY0SHvG2SgnYhxxRY"
    "lUs9Y8rXXVz+4tLuC0+2PfrW0zOvyY68OYcyyjV5eLFvLoKetFoE5bLMNXJZO5eNQxaujVa50DqAyCGGpQOoHEH7ADpA"
    "0/EQdFkC1biKCxC64CkAGGNT4aiayyo6YB1HxEHKVMId1Gy6uouqkULgdYqEC951cllEFd/UMRRombqZpnDRArLqBPFW"
    "ONNlEKSSmMiVo8pKYA/lkAKB7rqK5j8IFsfU8e5xqAVoQDm0VhzL14c9rEUsCqVAabkuhyRKhgXoyDcHX4CdDpGL/u9O"
    "6ybnobv4dmnX8uWf9o3p6dw3+o3mqtpT+JrSkDfroErXlhcMMgUhU7oJSULbfTJArcBPKMzwIS5McHW1fwnIglSaAnqI"
    "tgiEEiU35RMP2lxkF5KODXCno93JQW4os31L5fnYJ793/fza2RNr3/1q93XpQiOmtlwfGAtBAVaSVo5Stml4ehASx5tH"
    "IRncsV3FcYFUQfVwYcaCJih4JiJqemC/8hnjQsYVEeMbXVtFhLZ75a5/tuXgiMszNq6xLy/tW/NL75Cn66pdfaAyCcxU"
    "NMwYjPPVu1p7o10dFt3VYdGVg7tkRGAMmbKKl1gEZhFzEIaSSs+9/2d35+u9XWVHuhqt/pHXRR0LqBOxliIYWQg4reTD"
    "57ZlTpauKHr5wIYfx04aUsB8jYan1VEhKyJWgFwXXFsIzTSZ3urLNKgkASHzO1oHWt6agRVDquEbiLuDFc0QTVVNxTXC"
    "7kpPrX5PurQivg3p/al1H2gTpdP7eydsL62v6O4/+tK4ZZN1eVQQrYbBavCUjIdIgYdEtaZM7hmQo0e4ASkI7sUh85CN"
    "lcKjhjvTTEUsSAQvxdKEEVBTU2wK0NkUhfFNwknEFVNoNPwmbjnAeHhN16kqNA14n3QdHyrTQ0kDHecE4qkxMfqkhXKH"
    "xxE3EVa9KzA2AKgI7iWZovCnJSHtmN41KZN9sMW49+D9Fn2+94bAumLJl8lV+Vti+8J2wbZNAY9kK4xj/h+Ln3SIB/QR"
    "coPjyMywhJS9iDt62m9L3/1q3+nNM8/khkS//Cwa2LKg6Cj+3RopbJEaJs8LqxDrGlNoFeIahj0PGTMmYB2svNWe7goe"
    "NrmpFG2Ji1r8uhmhopMJ6dScsYf37Di4M/sd6m44Vff5kEUx1I0rkr9SaQtj/PeFJb8tWrchNrph2ZFDqP2u/wBCr6HX"
)
