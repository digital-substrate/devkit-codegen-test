# Copyright (c) Digital Substrate 2026, All rights reserved.
"""Tests for Kibo-generated concept key classes."""

import unittest
import dsviper
from features.demo import ConceptAKey, ConceptBKey, ConceptCKey, ConceptDKey, KlubKey
from features import AnyConceptKey
from features import definitions
from features.demo import data as md


class TestKeyCreation(unittest.TestCase):
    """Test key creation via create() static method."""

    def test_concept_a_key_create(self):
        key = ConceptAKey.create()
        self.assertIsInstance(key, ConceptAKey)
        self.assertTrue(key.instance_id().is_valid())

    def test_concept_b_key_create(self):
        key = ConceptBKey.create()
        self.assertIsInstance(key, ConceptBKey)
        self.assertTrue(key.instance_id().is_valid())

    def test_concept_c_key_create(self):
        key = ConceptCKey.create()
        self.assertIsInstance(key, ConceptCKey)
        self.assertTrue(key.instance_id().is_valid())

    def test_concept_d_key_create(self):
        key = ConceptDKey.create()
        self.assertIsInstance(key, ConceptDKey)
        self.assertTrue(key.instance_id().is_valid())

    def test_klub_key_from_concept_c(self):
        # KlubKey is created from member concepts, not directly
        key_c = ConceptCKey.create()
        klub_key = KlubKey.from_concept_c_key(key_c)
        self.assertIsInstance(klub_key, KlubKey)
        self.assertTrue(klub_key.instance_id().is_valid())

    def test_keys_are_unique(self):
        key1 = ConceptAKey.create()
        key2 = ConceptAKey.create()
        self.assertNotEqual(key1, key2)
        self.assertNotEqual(key1.instance_id(), key2.instance_id())


class TestKeyFromString(unittest.TestCase):
    """Test key construction from UUID strings."""

    def test_concept_a_from_string(self):
        uuid_str = "12345678-1234-1234-1234-123456789abc"
        key = ConceptAKey(uuid_str)
        self.assertEqual(key.instance_id().encoded(), uuid_str)

    def test_concept_b_from_string(self):
        uuid_str = "abcdef01-2345-6789-abcd-ef0123456789"
        key = ConceptBKey(uuid_str)
        self.assertEqual(key.instance_id().encoded(), uuid_str)


class TestKeyFromUUID(unittest.TestCase):
    """Test key construction from ValueUUId."""

    def test_concept_a_from_uuid(self):
        uuid = dsviper.ValueUUId.create()
        key = ConceptAKey(uuid)
        self.assertEqual(key.instance_id(), uuid)

    def test_concept_b_from_uuid(self):
        uuid = dsviper.ValueUUId.create()
        key = ConceptBKey(uuid)
        self.assertEqual(key.instance_id(), uuid)


class TestKeyRuntimeId(unittest.TestCase):
    """Test runtime ID associations."""

    def test_concept_a_runtime_id(self):
        key = ConceptAKey.create()
        self.assertEqual(key.runtime_id(), md.CONCEPT_A)

    def test_concept_b_runtime_id(self):
        key = ConceptBKey.create()
        self.assertEqual(key.runtime_id(), md.CONCEPT_B)

    def test_concept_c_runtime_id(self):
        key = ConceptCKey.create()
        self.assertEqual(key.runtime_id(), md.CONCEPT_C)

    def test_concept_d_runtime_id(self):
        key = ConceptDKey.create()
        self.assertEqual(key.runtime_id(), md.CONCEPT_D)


class TestKeyEquality(unittest.TestCase):
    """Test key equality and hashing."""

    def test_same_uuid_equal(self):
        uuid_str = "12345678-1234-1234-1234-123456789abc"
        key1 = ConceptAKey(uuid_str)
        key2 = ConceptAKey(uuid_str)
        self.assertEqual(key1, key2)

    def test_different_uuid_not_equal(self):
        key1 = ConceptAKey.create()
        key2 = ConceptAKey.create()
        self.assertNotEqual(key1, key2)

    def test_hash_consistency(self):
        uuid_str = "12345678-1234-1234-1234-123456789abc"
        key1 = ConceptAKey(uuid_str)
        key2 = ConceptAKey(uuid_str)
        self.assertEqual(hash(key1), hash(key2))

    def test_keys_in_dict(self):
        key1 = ConceptAKey.create()
        key2 = ConceptAKey.create()
        d = {key1: "value1", key2: "value2"}
        self.assertEqual(d[key1], "value1")
        self.assertEqual(d[key2], "value2")


class TestKeyComparison(unittest.TestCase):
    """Test key ordering operations."""

    def test_keys_orderable(self):
        key1 = ConceptAKey.create()
        key2 = ConceptAKey.create()
        # Should not raise
        _ = key1 < key2 or key1 >= key2

    def test_keys_sortable(self):
        keys = [ConceptAKey.create() for _ in range(5)]
        # Should not raise
        sorted_keys = sorted(keys)
        self.assertEqual(len(sorted_keys), 5)


class TestKeyDescription(unittest.TestCase):
    """Test key description and repr."""

    def test_concept_a_description(self):
        key = ConceptAKey.create()
        desc = key.description()
        self.assertIn("Demo::ConceptAKey", desc)
        self.assertIn(key.instance_id().encoded(), desc)

    def test_concept_b_description(self):
        key = ConceptBKey.create()
        desc = key.description()
        self.assertIn("Demo::ConceptBKey", desc)

    def test_repr_matches_description(self):
        key = ConceptAKey.create()
        self.assertEqual(repr(key), key.description())


class TestKeyIsKnown(unittest.TestCase):
    """Test is_known() method for key types."""

    def test_concept_a_is_known(self):
        key = ConceptAKey.create()
        self.assertTrue(key.is_known())

    def test_concept_b_is_known(self):
        key = ConceptBKey.create()
        self.assertTrue(key.is_known())

    def test_concept_c_is_known(self):
        key = ConceptCKey.create()
        self.assertTrue(key.is_known())

    def test_concept_d_is_known(self):
        key = ConceptDKey.create()
        self.assertTrue(key.is_known())


class TestKeyIsValid(unittest.TestCase):
    """Test is_valid() method based on UUID validity."""

    def test_created_key_is_valid(self):
        key = ConceptAKey.create()
        self.assertTrue(key.is_valid())

    def test_invalid_uuid_key(self):
        invalid_uuid = dsviper.ValueUUId.INVALID
        key = ConceptAKey(invalid_uuid)
        self.assertFalse(key.is_valid())


class TestKeyValidation(unittest.TestCase):
    """Test type validation in key constructors."""

    def test_wrong_type_raises_type_error(self):
        with self.assertRaises(TypeError):
            ConceptAKey(123)  # int is not valid

    def test_wrong_type_raises_type_error_for_list(self):
        with self.assertRaises(TypeError):
            ConceptAKey([1, 2, 3])

    def test_none_raises_type_error(self):
        with self.assertRaises(TypeError):
            ConceptAKey(None)

    def test_a_key_of_another_concept_says_how_to_convert_it(self):
        with self.assertRaisesRegex(TypeError, "to_parent_key"):
            ConceptAKey(ConceptDKey.create())

    def test_a_key_of_the_same_concept_is_used_as_it_is(self):
        with self.assertRaisesRegex(TypeError, "already"):
            ConceptAKey(ConceptAKey.create())


class TestKeyVprValue(unittest.TestCase):
    """Test access to underlying Viper value."""

    def test_vpr_value_is_value_key(self):
        key = ConceptAKey.create()
        self.assertIsInstance(key.unwrap_value(), dsviper.ValueKey)

    def test_vpr_value_roundtrip(self):
        key1 = ConceptAKey.create()
        vpr = key1.unwrap_value()
        key2 = ConceptAKey(vpr)
        self.assertEqual(key1, key2)


if __name__ == "__main__":
    unittest.main()
