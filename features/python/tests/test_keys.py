# Copyright (c) Digital Substrate 2026, All rights reserved.
"""Tests for Kibo-generated concept key classes."""

import unittest
import dsviper
from features.data import (
    Test_ConceptAKey, Test_ConceptBKey, Test_ConceptCKey, Test_ConceptDKey,
    Test_KlubKey, AnyConceptKey
)
from features import definitions as md


class TestKeyCreation(unittest.TestCase):
    """Test key creation via create() static method."""

    def test_concept_a_key_create(self):
        key = Test_ConceptAKey.create()
        self.assertIsInstance(key, Test_ConceptAKey)
        self.assertTrue(key.instance_id().is_valid())

    def test_concept_b_key_create(self):
        key = Test_ConceptBKey.create()
        self.assertIsInstance(key, Test_ConceptBKey)
        self.assertTrue(key.instance_id().is_valid())

    def test_concept_c_key_create(self):
        key = Test_ConceptCKey.create()
        self.assertIsInstance(key, Test_ConceptCKey)
        self.assertTrue(key.instance_id().is_valid())

    def test_concept_d_key_create(self):
        key = Test_ConceptDKey.create()
        self.assertIsInstance(key, Test_ConceptDKey)
        self.assertTrue(key.instance_id().is_valid())

    def test_klub_key_from_concept_c(self):
        # KlubKey is created from member concepts, not directly
        key_c = Test_ConceptCKey.create()
        klub_key = Test_KlubKey.from_test_concept_c_key(key_c)
        self.assertIsInstance(klub_key, Test_KlubKey)
        self.assertTrue(klub_key.instance_id().is_valid())

    def test_keys_are_unique(self):
        key1 = Test_ConceptAKey.create()
        key2 = Test_ConceptAKey.create()
        self.assertNotEqual(key1, key2)
        self.assertNotEqual(key1.instance_id(), key2.instance_id())


class TestKeyFromString(unittest.TestCase):
    """Test key construction from UUID strings."""

    def test_concept_a_from_string(self):
        uuid_str = "12345678-1234-1234-1234-123456789abc"
        key = Test_ConceptAKey(uuid_str)
        self.assertEqual(key.instance_id().encoded(), uuid_str)

    def test_concept_b_from_string(self):
        uuid_str = "abcdef01-2345-6789-abcd-ef0123456789"
        key = Test_ConceptBKey(uuid_str)
        self.assertEqual(key.instance_id().encoded(), uuid_str)


class TestKeyFromUUID(unittest.TestCase):
    """Test key construction from ValueUUId."""

    def test_concept_a_from_uuid(self):
        uuid = dsviper.ValueUUId.create()
        key = Test_ConceptAKey(uuid)
        self.assertEqual(key.instance_id(), uuid)

    def test_concept_b_from_uuid(self):
        uuid = dsviper.ValueUUId.create()
        key = Test_ConceptBKey(uuid)
        self.assertEqual(key.instance_id(), uuid)


class TestKeyRuntimeId(unittest.TestCase):
    """Test runtime ID associations."""

    def test_concept_a_runtime_id(self):
        key = Test_ConceptAKey.create()
        self.assertEqual(key.runtime_id(), md.RuntimeIds.Test_ConceptA)

    def test_concept_b_runtime_id(self):
        key = Test_ConceptBKey.create()
        self.assertEqual(key.runtime_id(), md.RuntimeIds.Test_ConceptB)

    def test_concept_c_runtime_id(self):
        key = Test_ConceptCKey.create()
        self.assertEqual(key.runtime_id(), md.RuntimeIds.Test_ConceptC)

    def test_concept_d_runtime_id(self):
        key = Test_ConceptDKey.create()
        self.assertEqual(key.runtime_id(), md.RuntimeIds.Test_ConceptD)


class TestKeyEquality(unittest.TestCase):
    """Test key equality and hashing."""

    def test_same_uuid_equal(self):
        uuid_str = "12345678-1234-1234-1234-123456789abc"
        key1 = Test_ConceptAKey(uuid_str)
        key2 = Test_ConceptAKey(uuid_str)
        self.assertEqual(key1, key2)

    def test_different_uuid_not_equal(self):
        key1 = Test_ConceptAKey.create()
        key2 = Test_ConceptAKey.create()
        self.assertNotEqual(key1, key2)

    def test_hash_consistency(self):
        uuid_str = "12345678-1234-1234-1234-123456789abc"
        key1 = Test_ConceptAKey(uuid_str)
        key2 = Test_ConceptAKey(uuid_str)
        self.assertEqual(hash(key1), hash(key2))

    def test_keys_in_dict(self):
        key1 = Test_ConceptAKey.create()
        key2 = Test_ConceptAKey.create()
        d = {key1: "value1", key2: "value2"}
        self.assertEqual(d[key1], "value1")
        self.assertEqual(d[key2], "value2")


class TestKeyComparison(unittest.TestCase):
    """Test key ordering operations."""

    def test_keys_orderable(self):
        key1 = Test_ConceptAKey.create()
        key2 = Test_ConceptAKey.create()
        # Should not raise
        _ = key1 < key2 or key1 >= key2

    def test_keys_sortable(self):
        keys = [Test_ConceptAKey.create() for _ in range(5)]
        # Should not raise
        sorted_keys = sorted(keys)
        self.assertEqual(len(sorted_keys), 5)


class TestKeyDescription(unittest.TestCase):
    """Test key description and repr."""

    def test_concept_a_description(self):
        key = Test_ConceptAKey.create()
        desc = key.description()
        self.assertIn("Test::ConceptAKey", desc)
        self.assertIn(key.instance_id().encoded(), desc)

    def test_concept_b_description(self):
        key = Test_ConceptBKey.create()
        desc = key.description()
        self.assertIn("Test::ConceptBKey", desc)

    def test_repr_matches_description(self):
        key = Test_ConceptAKey.create()
        self.assertEqual(repr(key), key.description())


class TestKeyIsKnown(unittest.TestCase):
    """Test is_known() method for key types."""

    def test_concept_a_is_known(self):
        key = Test_ConceptAKey.create()
        self.assertTrue(key.is_known())

    def test_concept_b_is_known(self):
        key = Test_ConceptBKey.create()
        self.assertTrue(key.is_known())

    def test_concept_c_is_known(self):
        key = Test_ConceptCKey.create()
        self.assertTrue(key.is_known())

    def test_concept_d_is_known(self):
        key = Test_ConceptDKey.create()
        self.assertTrue(key.is_known())


class TestKeyIsValid(unittest.TestCase):
    """Test is_valid() method based on UUID validity."""

    def test_created_key_is_valid(self):
        key = Test_ConceptAKey.create()
        self.assertTrue(key.is_valid())

    def test_invalid_uuid_key(self):
        invalid_uuid = dsviper.ValueUUId.INVALID
        key = Test_ConceptAKey(invalid_uuid)
        self.assertFalse(key.is_valid())


class TestKeyValidation(unittest.TestCase):
    """Test type validation in key constructors."""

    def test_wrong_type_raises_type_error(self):
        with self.assertRaises(TypeError):
            Test_ConceptAKey(123)  # int is not valid

    def test_wrong_type_raises_type_error_for_list(self):
        with self.assertRaises(TypeError):
            Test_ConceptAKey([1, 2, 3])

    def test_none_raises_type_error(self):
        with self.assertRaises(TypeError):
            Test_ConceptAKey(None)


class TestKeyVprValue(unittest.TestCase):
    """Test access to underlying Viper value."""

    def test_vpr_value_is_value_key(self):
        key = Test_ConceptAKey.create()
        self.assertIsInstance(key.vpr_value, dsviper.ValueKey)

    def test_vpr_value_roundtrip(self):
        key1 = Test_ConceptAKey.create()
        vpr = key1.vpr_value
        key2 = Test_ConceptAKey(vpr)
        self.assertEqual(key1, key2)


if __name__ == "__main__":
    unittest.main()
