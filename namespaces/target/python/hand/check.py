#!/usr/bin/env python3
"""Ce que la référence Python permet, exécuté.

Le C++ était vérifié par un compilateur contre des stubs ; ici le vrai runtime est
importable, donc la référence tourne réellement. Une assertion qui passe vaut mieux qu'une
signature qui compile.
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

from topology import definitions
from topology import modela, modelb


def check(label, condition):
    print(f"  {'ok  ' if condition else 'ÉCHEC'} {label}")
    return condition


ok = True

# Les mêmes noms, deux namespaces, aucun renommage -- ce qui a tout déclenché.
a = modela.Colour(r=1, g=2, b=3)
b = modelb.Colour(r=0.5, g=0.5, b=0.5)
ok &= check("deux Colour homonymes coexistent", type(a) is not type(b))
ok &= check("et gardent leurs types du modèle",
            a.type().representation() == "ModelA::Colour"
            and b.type().representation() == "ModelB::Colour")

# Les champs sont des propriétés : le nom et l'accès sont la même chose.
a.r = 9
ok &= check("un champ se lit et s'écrit par son nom", a.r == 9)

# Une clé est une poignée, et elle se compare et se hache.
k1, k2 = modela.MaterialKey.create(), modela.MaterialKey.create()
ok &= check("deux clés neuves diffèrent", k1 != k2)
ok &= check("une clé est hachable", {k1: a}[k1] is a)

# La valeur générée EST la valeur du runtime : rien à encoder.
#  et non `is` : le runtime rend un nouvel objet Python à chaque appel pour le même
# type du modèle. Une identité d'objet ne dit rien ici, une égalité de type si.
ok &= check("la classe enveloppe une Value du runtime",
            a.value.type() == a.type())

# Et les clés des deux unités ne se confondent pas.
ka, kb = modela.MaterialKey.create(), modelb.MaterialKey.create()
ok &= check("les clés des deux unités ont des types distincts",
            ka.value.type() != kb.value.type())

print()
print("definitions :", len(definitions().concepts()), "concepts,",
      len(definitions().structures()), "structures")

raise SystemExit(0 if ok else 1)
