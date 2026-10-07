# Copyright (c) Digital Substrate 2026, All rights reserved.
"""A field's name and path, as constants (feature Fields).

Code that handles a structure through the dynamic API names the field: a constant completes
and a type checker checks it, where a string literal is neither. The name is the model's own,
the one the runtime matches; the path addresses that field, to read it or to write it alone.
"""

import inspect
import unittest

import dsviper

from features import definitions
from features.demo import data, fields, paths
from features.demo import attachments as ma
from features.demo import ConceptAKey, StructureS, StructureV


def constants(cls: type) -> dict[str, object]:
    return {k: v for k, v in vars(cls).items() if not k.startswith("_")}


def structures(module) -> dict[str, type]:
    return {n: c for n, c in vars(module).items() if inspect.isclass(c) and c.__module__ == module.__name__}


class TestFields(unittest.TestCase):

    def test_every_structure_names_every_field_as_the_model_does(self):
        self.assertEqual(set(structures(fields)), {n for n, c in structures(data).items()
                                                   if isinstance(getattr(c, "type", None) and c.type(), dsviper.TypeStructure)})
        for name, cls in structures(fields).items():
            declared = {f.name() for f in getattr(data, name).type().fields()}
            self.assertEqual(set(constants(cls).values()), declared, name)

    def test_every_path_reads_its_field(self):
        for name, cls in structures(paths).items():
            value = dsviper.Value.create(getattr(data, name).type())
            for attribute, path in constants(cls).items():
                field = constants(getattr(fields, name))[attribute]
                self.assertEqual(str(path), str(dsviper.Path.from_field(field).const()), f"{name}.{attribute}")
                self.assertEqual(path.at(value, encoded=False), value.at(field, encoded=False), f"{name}.{attribute}")

    def test_a_path_reads_a_value_it_was_not_built_from(self):
        self.assertEqual(paths.StructureS.f_float.at(StructureS(f_float=1.5).unwrap_value()), 1.5)

    def test_a_path_writes_its_field_alone(self):
        mutable = dsviper.CommitMutableState(dsviper.CommitState(definitions()))
        m = mutable.attachment_mutating()
        key = ConceptAKey.create()
        ma.ConceptA.properties.set(m, key, StructureV(f_vector=[1]))
        m.update(ma.ConceptA.properties.descriptor, key.unwrap_value(), paths.StructureV.f_vector, [7, 8])
        document = ma.ConceptA.properties.get(m, key).unwrap()
        self.assertEqual(list(document.f_vector), [7, 8])
        self.assertEqual(document.f_bool, True)


if __name__ == "__main__":
    unittest.main()
