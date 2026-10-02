#!/usr/bin/env python3
"""What the Python reference allows, executed.

The C++ was checked by a compiler against stubs; here the real runtime is importable, so
the reference actually runs. A passing assertion is worth more than a signature that compiles.
"""
import shutil
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
TARGET = HERE.parent

# The package under test is the one kibo-project has just rendered, one level up. It
# already carries its `_codegen`: the site places it, this harness no longer has to.
package = Path(sys.argv[1]).resolve() if len(sys.argv) > 1 else TARGET / "generated"
sys.path.insert(0, str(package))

import dsviper

from topology import definitions, tools
from topology import model_a as modela, model_b as modelb
from topology.model_a import attachments as modela_attachments
from topology.model_b import attachments as modelb_attachments
# The reference does not write the whole model, and need not. It carries the two units that
# raise the design questions -- two homonymous types, two homonymous attachments. Containers
# raise another, which needs a real document: `Projection`, rendered by the templates and
# written by no one by hand. Those assertions therefore only run on a rendered package, and
# say so when they do not.
try:
    from topology import model_c, projection
    from topology.projection import attachments as projection_attachments
except ImportError:
    projection = None


def check(label, condition):
    print(f"  {'ok  ' if condition else 'FAIL'} {label}")
    return condition


ok = True

# The same names, two namespaces, no renaming -- what started it all.
a = modela.Colour(r=1, g=2, b=3)
b = modelb.Colour(r=0.5, g=0.5, b=0.5)
ok &= check("two homonymous Colour types coexist", type(a) is not type(b))
ok &= check("and keep their model types",
            a.type().representation() == "ModelA::Colour"
            and b.type().representation() == "ModelB::Colour")

# Fields are properties: the name and the access are the same thing.
a.r = 9
ok &= check("a field is read and written by its name", a.r == 9)

# A key is a handle, and it compares and hashes.
k1, k2 = modela.MaterialKey.create(), modela.MaterialKey.create()
ok &= check("two new keys differ", k1 != k2)
ok &= check("a key is hashable", {k1: a}[k1] is a)

# The generated value IS the runtime value: nothing to encode.
# `==` and not `is`: the runtime returns a new Python object on each call for the same
# model type. Object identity says nothing here; type equality does.
ok &= check("the class wraps a runtime Value",
            a.vpr_value.type() == a.type())

# And the keys of the two units are not confused.
ka, kb = modela.MaterialKey.create(), modelb.MaterialKey.create()
ok &= check("the keys of the two units have distinct types",
            ka.vpr_value.type() != kb.vpr_value.type())

# ── an attachment, on an in-memory state ──
#
# The C++ reference runs this test through `CommitMutableState`, and it reads the same here:
# the context is the first argument, and it says what the call operates on.
colour = modela_attachments.Material.colour
state = dsviper.CommitState(definitions())
mutable = dsviper.CommitMutableState(state)
mutating = mutable.attachment_mutating()

key = modela.MaterialKey.create()
ok &= check("a new attachment does not know the key", not colour.has(mutating, key))

colour.set(mutating, key, modela.Colour(r=1, g=2, b=3))
ok &= check("after a write, the key is known", colour.has(mutating, key))
ok &= check("and the document comes back unchanged", colour.get(mutating, key).unwrap() == modela.Colour(r=1, g=2, b=3))
keys = colour.keys(mutating)
ok &= check("the attachment's keys are its key set, typed",
            type(keys).__name__ == "Set_of_ModelA_MaterialKey" and list(keys) == [key])

# A single field, through a method generated for it: the name completes, and a typo
# shows at import, not at call time.
colour.set_r(mutating, key, 9)
ok &= check("a single field is written through its method", colour.get(mutating, key).unwrap().r == 9)

ok &= check("a missing key returns a nil optional", colour.get(mutating, modela.MaterialKey.create()).is_nil())

# A concept named like another's key. `MaterialKey` is Material's key and a concept of its
# own; its attachments form a class of that name in the module, and Material's key must stay
# the type written there -- which the module hid while it imported bare names.
note_key = modela.MaterialKeyKey.create()
modela_attachments.MaterialKey.note.set(mutating, note_key, modela.MaterialKeyNote(material=key))
ok &= check("a concept named like another's key does not hide that key",
            modela_attachments.MaterialKey.note.get(mutating, note_key).unwrap().material == key)
# And the annotations -- what a type checker and the editor read -- do name the key:
# `key: MaterialKey` resolved in the module gave the attachments class.
import typing                                                           # noqa: E402
hints = typing.get_type_hints(type(modela_attachments.Material.colour).set_r)
ok &= check("a key's annotation names the key, not a homonymous scope", hints["key"] is modela.MaterialKey)

# ── and the same attachment, on a database ──
#
# The same calls, not one line more. The database carries `keys`, `has`, `get` and `set`;
# only `delete` is its own. The pack writes a whole second module for this case.
database = dsviper.Database.create_in_memory()
database.extend_definitions(definitions())
database.begin_transaction()
ok &= check("a write to the database returns a status",
            colour.set(database, key, modela.Colour(r=4, g=5, b=6)) is True)
ok &= check("and reads back through the same calls", colour.get(database, key).unwrap() == modela.Colour(r=4, g=5, b=6))
ok &= check("delete is the only operation the database adds", colour.delete(database, key) is True)
ok &= check("after delete, the key is no longer known", not colour.has(database, key))
database.commit()
database.close()

# ── a pool ──
#
# Nothing more to test here: `dsviper` offers no way to build a pool from Python, so the
# class is the client edge and its identity is all it asserts offline.
# Two homonymous attachments, on two homonymous concepts, in two units: the case that
# started this whole work. The pack tells them apart as `modela_material_colour_get` versus
# `modelb_material_colour_get`; here nothing collides.
ok &= check("two homonymous attachments have distinct descriptors",
            modela_attachments.Material.colour.descriptor.runtime_id()
            != modelb_attachments.Material.colour.descriptor.runtime_id())

# ── a container returns its elements with their names ──
#
# Every container shape is a class of the package's `containers` module, named after what it
# holds. A map crossing two units belongs to neither: it is declared there, and a read returns it.
if projection is None:
    print("  --   containers: not in this package, these assertions do not run")
else:
    link = projection.LinkKey.create()
    a, b = modela.MaterialKey.create(), modelb.MaterialKey.create()

    from topology.containers import Map_of_ModelA_MaterialKey_to_ModelB_MaterialKey
    try:
        projection_attachments.Link.mapping.set(mutating, link, {a: b})
        refused = False
    except TypeError:
        refused = True
    ok &= check("a native map of generated keys is refused", refused)

    typed = Map_of_ModelA_MaterialKey_to_ModelB_MaterialKey()
    typed[a] = b
    projection_attachments.Link.mapping.set(mutating, link, typed)
    mapping = projection_attachments.Link.mapping.get(mutating, link).unwrap()
    ok &= check("a map document reads back as its declared class",
                type(mapping) is Map_of_ModelA_MaterialKey_to_ModelB_MaterialKey and len(mapping) == 1)
    ok &= check("and its key carries its unit's class",
                type(next(iter(mapping))) is modela.MaterialKey)
    ok &= check("and its value that of its own", type(mapping[a]) is modelb.MaterialKey)

    marker = model_c.MarkerKey.create()
    projection_attachments.Link.marker.set(mutating, link, marker)
    ok &= check("a key document comes back typed",
                projection_attachments.Link.marker.get(mutating, link).unwrap() == marker)

ok &= check("a pool carries its model identity",
            tools.Pool.UUID.encoded() == "17e63428-03e1-41d7-ad9d-60c5665bbd66")

print()
print("definitions :", len(definitions().concepts()), "concepts,",
      len(definitions().structures()), "structures,",
      len(definitions().attachments()), "attachments")

raise SystemExit(0 if ok else 1)
