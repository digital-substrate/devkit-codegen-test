"""ModelB — les attachments que ce namespace déclare.

UN ATTACHMENT EST UN OBJET, PAS UNE FAMILLE DE FONCTIONS. Le pack écrit
`modela_material_colour_get(getting, key)` : le namespace, le concept et le nom de
l'attachment collés dans un identifiant, parce qu'un module plat n'a aucun autre moyen de
les distinguer. Ici le module est le namespace, la classe est le concept, et l'attribut est
l'attachment — les trois parties du nom redeviennent trois portées, et rien n'est collé.

En C++ il fallait une portée (`Attachments::Material::colour`) parce qu'une fonction ne peut
pas être une valeur. En Python elle peut : `colour` est un objet, donc `get`, `set` et
`keys` sont ses méthodes et non des fonctions qui répètent son nom.
"""

from __future__ import annotations

import dsviper

from .. import definitions
from .._codegen import AttachmentProxy
from .data import Colour, MaterialKey


class Material:
    """Les attachments portés par ModelB::Material."""

    colour = AttachmentProxy(
        dsviper.ValueUUId.create("09eeb3f7-b0a6-9ad9-a80f-d2a85070ec08"),
        definitions, MaterialKey, Colour)


material = Material()
