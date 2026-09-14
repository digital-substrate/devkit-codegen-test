# A UNIT MODULE. The names are unqualified: Material, not ModelA_Material.
#
# The subpackage is the namespace. `from topology.model_a import Material` reads the
# way a Python user expects, and model_b declares its own Material without either
# being renamed.

from __future__ import annotations
import dsviper

from .. import value_type as mt        # the base table, whole and shared
from .. import definitions as md       # the base accessor
from ..data import Proxy               # the base's Proxy, AnyConceptKey live there


class Material(Proxy):
    ...   # unchanged


class Colour(Proxy):
    ...   # unchanged
