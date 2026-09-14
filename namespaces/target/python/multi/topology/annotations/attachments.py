# The unit that is empty in data.py, and is not here.
#
# Both attachments are named `note`, on same-named concepts of two other units. With
# the prefix gone the two Material classes no longer tell themselves apart by name, so
# the alias carries the unit -- the same rule the C++ target proposes for the scope.

from ..model_a.data import Material as ModelA_Material
from ..model_b.data import Material as ModelB_Material


class ModelA_Material_Note:
    @staticmethod
    def get(attachment_getting, key: ModelA_Material) -> str | None: ...


class ModelB_Material_Note:
    @staticmethod
    def get(attachment_getting, key: ModelB_Material) -> str | None: ...
