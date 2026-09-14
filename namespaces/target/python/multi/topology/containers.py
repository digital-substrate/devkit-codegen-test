# A SINK MODULE IN THE BASE PACKAGE -- the Python counterpart of the C++ pool registry.
#
# Container proxies are named by typeSuffix, and most belong to one unit:
# Set_Material goes to model_a. But Map_ModelA_MaterialKey_to_ModelB_MaterialKey spans
# two, and unlike C++ -- where the spanning type is std::map<...>, written inline and
# needing no home -- Python has to generate a class for it.
#
# It lives here rather than in projection, so that two units declaring the same shape
# get one class and not two. Two classes would be two distinct types, and an isinstance
# check would stop meaning what it says.
#
# That makes this module a sink: it imports the units, while ../data.py imports none of
# them. Both are in the base package, which is fine -- the root/sink distinction is a
# property of modules, not of packages.

from .model_a.data import Material as _ModelA_Material
from .model_b.data import Material as _ModelB_Material
from .data import Proxy


class Map_ModelA_MaterialKey_to_ModelB_MaterialKey(Proxy):
    ...   # unchanged; its name stays the structural typeSuffix, as in C++
