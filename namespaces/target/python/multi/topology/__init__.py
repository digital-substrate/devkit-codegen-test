# THE RE-EXPORT RULE, and the only place the collision is answered.
#
# Today this file is one line -- `from .data import *` -- and it works because every
# class already carries its namespace in its name: ModelA_MaterialKey. That prefix is
# what the whole design removes, which puts the ambiguity back and makes this file
# have to decide.
#
# The rule: re-export the names that are unambiguous across units, and leave the rest
# reachable only through their unit. kibo knows every name, so it computes this.
#
# In a mono-namespace model no name can collide, so everything is flat and the 99%
# see exactly what they see today, minus the prefix.

from . import model_a, model_b, model_c, projection, annotations
from . import tools, projector

# Unambiguous: exactly one unit declares each.
from .model_c.data import Marker
from .projection.data import Link, DerivedMaterial, Pair

# NOT re-exported: Material and Colour are declared by both model_a and model_b.
# Reach them through their unit -- `topology.model_a.Material` -- which is what a
# namespace is for, and what ModelA_Material was imitating.
