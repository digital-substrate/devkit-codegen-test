"""ModelA — les attachments que ce namespace déclare.

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
from .._attachment import Attachment
from .data import Colour, MaterialKey


class Material:
    """Les attachments portés par ModelA::Material."""

    colour = Attachment(
        dsviper.ValueUUId.create("faf658ea-5586-890a-0c4a-5cd2c9209b28"),
        definitions, MaterialKey, Colour)


material = Material()
