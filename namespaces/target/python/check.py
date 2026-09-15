#!/usr/bin/env python3
"""Ce que la référence Python permet, exécuté.

Le C++ était vérifié par un compilateur contre des stubs ; ici le vrai runtime est
importable, donc la référence tourne réellement. Une assertion qui passe vaut mieux qu'une
signature qui compile.
"""
import shutil
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent

# LE PAQUET À ÉPROUVER EST DONNÉ, PARCE QU'IL Y EN A DEUX. La référence écrite à la main dit
# ce qu'on veut ; le rendu des templates dit ce qu'on obtient. Les mêmes assertions doivent
# passer sur les deux, sans quoi la référence ne référence rien.
package = Path(sys.argv[1]).resolve() if len(sys.argv) > 1 else HERE / "hand"

# Ce que `dsviper` ne porte pas encore, déposé dans le paquet comme il l'est dans un rendu.
for proposed in (HERE.parents[2] / "runtime-proposed" / "dsviper").glob("_*.py"):
    shutil.copy(proposed, package / "topology")

sys.path.insert(0, str(package))

import dsviper

from topology import definitions, tools
from topology import model_a as modela, model_b as modelb
from topology.model_a import attachments as modela_attachments
from topology.model_b import attachments as modelb_attachments


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

# ── un attachment, sur un état en mémoire ──
#
# C'est l'épreuve que la référence C++ passe par `CommitMutableState`, et elle se dit ici
# dans les mêmes termes : le contexte est le premier argument, et c'est lui qui dit sur quoi
# l'appel porte.
colour = modela_attachments.material.colour
state = dsviper.CommitState(definitions())
mutable = dsviper.CommitMutableState(state)
mutating = mutable.attachment_mutating()

key = modela.MaterialKey.create()
ok &= check("un attachment neuf ne connaît pas la clé", not colour.has(mutating, key))

colour.set(mutating, key, modela.Colour(r=1, g=2, b=3))
ok &= check("après écriture, la clé est connue", colour.has(mutating, key))
ok &= check("et le document revient tel quel", colour.get(mutating, key) == modela.Colour(r=1, g=2, b=3))
ok &= check("les clés de l'attachment sont typées", colour.keys(mutating) == {key})

# Un champ seul, adressé par son nom -- ce que le pack appelle un chemin et met dans un
# module à lui.
colour.update(mutating, key, "r", 9)
ok &= check("un seul champ s'écrit par son nom", colour.get(mutating, key).r == 9)

ok &= check("une clé absente rend None", colour.get(mutating, modela.MaterialKey.create()) is None)

# ── et le même attachment, sur une base ──
#
# LES MÊMES APPELS, SANS UNE LIGNE DE PLUS. La base porte `keys`, `has`, `get` et `set` ;
# seul `delete` lui est propre. Le pack écrit un second module entier pour ce cas.
database = dsviper.Database.create_in_memory()
database.extend_definitions(definitions())
database.begin_transaction()
ok &= check("l'écriture sur base rend un statut",
            colour.set(database, key, modela.Colour(r=4, g=5, b=6)) is True)
ok &= check("et se relit par les mêmes appels", colour.get(database, key) == modela.Colour(r=4, g=5, b=6))
ok &= check("le retrait est la seule opération que la base ajoute", colour.delete(database, key) is True)
ok &= check("après retrait, la clé n'est plus connue", not colour.has(database, key))
database.commit()
database.close()

# ── un pool ──
#
# Rien à éprouver de plus ici : `dsviper` n'offre pas de quoi construire un pool depuis
# Python, donc la classe est le bord client et son identité est tout ce qu'elle affirme
# hors connexion.
# Deux attachments homonymes, sur deux concepts homonymes, dans deux unités : le cas qui a
# déclenché tout le chantier. Le pack les distingue par `modela_material_colour_get` contre
# `modelb_material_colour_get` ; ici rien ne se touche.
ok &= check("deux attachments homonymes ont des descripteurs distincts",
            modela_attachments.material.colour.descriptor.runtime_id()
            != modelb_attachments.material.colour.descriptor.runtime_id())

ok &= check("un pool porte son identité du modèle",
            tools.Pool.UUID.encoded() == "17e63428-03e1-41d7-ad9d-60c5665bbd66")

print()
print("definitions :", len(definitions().concepts()), "concepts,",
      len(definitions().structures()), "structures,",
      len(definitions().attachments()), "attachments")

raise SystemExit(0 if ok else 1)
