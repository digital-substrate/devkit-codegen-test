import os
from features.commit import *

b = Bug_BKey.create()
a = Bug_AKey.from_any_concept_key(b.as_AnyConceptKey)
print(a)
