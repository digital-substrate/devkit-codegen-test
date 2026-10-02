# Copyright (c) Digital Substrate 2026, All rights reserved.
"""The operations generated for each attachment: one method per field, typed and completable."""

import unittest
import dsviper
from features import definitions
from features.demo import attachments as ma
from features.demo import ConceptAKey, ConceptCKey, StructureU, StructureV


def as_dict(mapping) -> dict:
    return {k: mapping[k] for k in mapping}


class Operations(unittest.TestCase):

    def setUp(self):
        self.mutable = dsviper.CommitMutableState(dsviper.CommitState(definitions()))
        self.m = self.mutable.attachment_mutating()


class TestFieldOperations(Operations):
    """Operations on one field of a structure document."""

    def test_set_field(self):
        key = ConceptAKey.create()
        ma.ConceptA.properties.set(self.m, key, StructureV())
        ma.ConceptA.properties.union_f_set(self.m, key, {7, 8})
        self.assertEqual(set(ma.ConceptA.properties.get(self.m, key).unwrap().f_set), {1, 2, 3, 7, 8})
        ma.ConceptA.properties.subtract_f_set(self.m, key, [1, 7])
        self.assertEqual(set(ma.ConceptA.properties.get(self.m, key).unwrap().f_set), {2, 3, 8})

    def test_map_field(self):
        key = ConceptAKey.create()
        ma.ConceptA.properties.set(self.m, key, StructureV())
        ma.ConceptA.properties.union_f_map(self.m, key, {2: "Two"})
        ma.ConceptA.properties.update_f_map(self.m, key, {0: "zero", 9: "Nine"})
        ma.ConceptA.properties.subtract_f_map(self.m, key, [1])
        self.assertEqual(as_dict(ma.ConceptA.properties.get(self.m, key).unwrap().f_map), {0: "zero", 2: "Two"})

    def test_xarray_field(self):
        key = ConceptCKey.create()
        ma.ConceptC.properties_c.set(self.m, key, StructureU())
        first, second = dsviper.ValueUUId.create(), dsviper.ValueUUId.create()
        ma.ConceptC.properties_c.insert_f_xarray(self.m, key, dsviper.ValueUUId.INVALID, first, 5)
        ma.ConceptC.properties_c.insert_f_xarray(self.m, key, dsviper.ValueUUId.INVALID, second, 6)
        ma.ConceptC.properties_c.update_f_xarray(self.m, key, first, 50)
        ma.ConceptC.properties_c.remove_f_xarray(self.m, key, second)
        self.assertEqual(list(ma.ConceptC.properties_c.get(self.m, key).unwrap().f_xarray), [50])

    def test_scalar_field(self):
        key = ConceptAKey.create()
        ma.ConceptA.properties.set(self.m, key, StructureV())
        ma.ConceptA.properties.set_f_string(self.m, key, "written")
        self.assertEqual(ma.ConceptA.properties.get(self.m, key).unwrap().f_string, "written")


class TestDocumentOperations(Operations):
    """The same operations when the document is itself the aggregate."""

    def test_set_document(self):
        key = ConceptAKey.create()
        ma.ConceptA.properties_se_int8.set(self.m, key, {1, 2})
        ma.ConceptA.properties_se_int8.union(self.m, key, {3})
        ma.ConceptA.properties_se_int8.subtract(self.m, key, {1})
        self.assertEqual(set(ma.ConceptA.properties_se_int8.get(self.m, key).unwrap()), {2, 3})

    def test_map_document(self):
        key = ConceptAKey.create()
        ma.ConceptA.properties_map_int8_string.set(self.m, key, {1: "One"})
        ma.ConceptA.properties_map_int8_string.union(self.m, key, {2: "Two"})
        ma.ConceptA.properties_map_int8_string.update(self.m, key, {1: "one", 3: "Three"})
        ma.ConceptA.properties_map_int8_string.subtract(self.m, key, [2])
        self.assertEqual(as_dict(ma.ConceptA.properties_map_int8_string.get(self.m, key).unwrap()), {1: "one"})

    def test_xarray_document(self):
        key = ConceptAKey.create()
        ma.ConceptA.properties_xarray.set(self.m, key, [])
        position = dsviper.ValueUUId.create()
        ma.ConceptA.properties_xarray.insert(self.m, key, dsviper.ValueUUId.INVALID, position, 4)
        ma.ConceptA.properties_xarray.update(self.m, key, position, 40)
        self.assertEqual(list(ma.ConceptA.properties_xarray.get(self.m, key).unwrap()), [40])
        ma.ConceptA.properties_xarray.remove(self.m, key, position)
        self.assertEqual(list(ma.ConceptA.properties_xarray.get(self.m, key).unwrap()), [])


class TestOnlyWhatTheDocumentHas(unittest.TestCase):
    """An operation exists only where the document gives it a meaning."""

    def test_no_aggregate_operation_on_a_scalar_document(self):
        self.assertFalse(hasattr(ma.ConceptA.properties_int8, "union"))

    def test_no_lookup_by_name(self):
        self.assertFalse(hasattr(ma.ConceptA.properties, "union_f_sett"))
        self.assertFalse(hasattr(ma.ConceptA.properties, "update"))


if __name__ == "__main__":
    unittest.main()
