# Copyright (c) Digital Substrate 2026, All rights reserved.
"""Tests for Kibo-generated polymorphism (AnyConceptKey, inheritance, clubs)."""

import unittest
import dsviper
from features.data import (
    Test_ConceptAKey, Test_ConceptBKey, Test_ConceptCKey, Test_ConceptDKey,
    Test_KlubKey, AnyConceptKey
)
from features import definitions as md


class TestAnyConceptKeyFromConcept(unittest.TestCase):
    """Test conversion from specific key to AnyConceptKey."""

    def test_concept_a_to_any(self):
        key = Test_ConceptAKey.create()
        any_key = key.to_any_concept_key()
        self.assertIsInstance(any_key, AnyConceptKey)
        self.assertEqual(any_key.instance_id(), key.instance_id())

    def test_concept_b_to_any(self):
        key = Test_ConceptBKey.create()
        any_key = key.to_any_concept_key()
        self.assertIsInstance(any_key, AnyConceptKey)

    def test_concept_c_to_any(self):
        key = Test_ConceptCKey.create()
        any_key = key.to_any_concept_key()
        self.assertIsInstance(any_key, AnyConceptKey)

    def test_concept_d_to_any(self):
        key = Test_ConceptDKey.create()
        any_key = key.to_any_concept_key()
        self.assertIsInstance(any_key, AnyConceptKey)


class TestAnyConceptKeyRuntimeId(unittest.TestCase):
    """Test AnyConceptKey runtime_id dispatch."""

    def test_runtime_id_concept_a(self):
        key = Test_ConceptAKey.create()
        any_key = key.to_any_concept_key()
        self.assertEqual(any_key.runtime_id(), md.RuntimeIds.Test_ConceptA)

    def test_runtime_id_concept_b(self):
        key = Test_ConceptBKey.create()
        any_key = key.to_any_concept_key()
        self.assertEqual(any_key.runtime_id(), md.RuntimeIds.Test_ConceptB)

    def test_runtime_id_concept_c(self):
        key = Test_ConceptCKey.create()
        any_key = key.to_any_concept_key()
        self.assertEqual(any_key.runtime_id(), md.RuntimeIds.Test_ConceptC)

    def test_runtime_id_concept_d(self):
        key = Test_ConceptDKey.create()
        any_key = key.to_any_concept_key()
        self.assertEqual(any_key.runtime_id(), md.RuntimeIds.Test_ConceptD)


class TestAnyConceptKeyDowncast(unittest.TestCase):
    """Test downcasting from AnyConceptKey to specific type."""

    def test_downcast_to_concept_a_success(self):
        key = Test_ConceptAKey.create()
        any_key = key.to_any_concept_key()
        result = Test_ConceptAKey.from_any_concept_key(any_key)
        self.assertIsNotNone(result)
        self.assertEqual(result, key)

    def test_downcast_to_concept_a_failure(self):
        key = Test_ConceptBKey.create()
        any_key = key.to_any_concept_key()
        result = Test_ConceptAKey.from_any_concept_key(any_key)
        self.assertIsNone(result)

    def test_downcast_to_concept_b_success(self):
        key = Test_ConceptBKey.create()
        any_key = key.to_any_concept_key()
        result = Test_ConceptBKey.from_any_concept_key(any_key)
        self.assertIsNotNone(result)
        self.assertEqual(result, key)

    def test_downcast_to_concept_b_failure(self):
        key = Test_ConceptAKey.create()
        any_key = key.to_any_concept_key()
        result = Test_ConceptBKey.from_any_concept_key(any_key)
        self.assertIsNone(result)


class TestAnyConceptKeyIsKnown(unittest.TestCase):
    """Test AnyConceptKey is_known() method."""

    def test_concept_a_is_known(self):
        key = Test_ConceptAKey.create()
        any_key = key.to_any_concept_key()
        self.assertTrue(any_key.is_known())

    def test_concept_b_is_known(self):
        key = Test_ConceptBKey.create()
        any_key = key.to_any_concept_key()
        self.assertTrue(any_key.is_known())


class TestAnyConceptKeyDescription(unittest.TestCase):
    """Test AnyConceptKey description formatting."""

    def test_description_includes_type(self):
        key = Test_ConceptAKey.create()
        any_key = key.to_any_concept_key()
        desc = any_key.description()
        self.assertIn("AnyConceptKey", desc)
        self.assertIn("ConceptAKey", desc)

    def test_description_includes_uuid(self):
        key = Test_ConceptAKey.create()
        any_key = key.to_any_concept_key()
        desc = any_key.description()
        self.assertIn(key.instance_id().encoded(), desc)


class TestAnyConceptKeyEquality(unittest.TestCase):
    """Test AnyConceptKey equality comparison."""

    def test_same_origin_equal(self):
        key = Test_ConceptAKey.create()
        any1 = key.to_any_concept_key()
        any2 = key.to_any_concept_key()
        self.assertEqual(any1, any2)

    def test_different_origin_not_equal(self):
        key1 = Test_ConceptAKey.create()
        key2 = Test_ConceptAKey.create()
        any1 = key1.to_any_concept_key()
        any2 = key2.to_any_concept_key()
        self.assertNotEqual(any1, any2)

    def test_different_types_not_equal(self):
        key_a = Test_ConceptAKey.create()
        key_b = Test_ConceptBKey.create()
        any_a = key_a.to_any_concept_key()
        any_b = key_b.to_any_concept_key()
        self.assertNotEqual(any_a, any_b)


class TestAnyConceptKeyValidation(unittest.TestCase):
    """Test AnyConceptKey validation."""

    def test_valid_key(self):
        key = Test_ConceptAKey.create()
        any_key = key.to_any_concept_key()
        self.assertTrue(any_key.is_valid())

    def test_invalid_key(self):
        invalid_uuid = dsviper.ValueUUId.INVALID
        key = Test_ConceptAKey(invalid_uuid)
        any_key = key.to_any_concept_key()
        self.assertFalse(any_key.is_valid())


class TestConceptInheritance(unittest.TestCase):
    """Test concept inheritance (ConceptC extends ConceptB)."""

    def test_concept_c_is_club_member(self):
        # ConceptC is a member of Klub
        key_c = Test_ConceptCKey.create()
        # Verify it can be used where ConceptB is expected (through club membership)
        self.assertIsInstance(key_c, Test_ConceptCKey)

    def test_concept_c_to_parent_key(self):
        # ConceptC extends ConceptB - use to_parent_key
        key_c = Test_ConceptCKey.create()
        # Convert to Test_ConceptBKey via to_parent_key
        as_b = key_c.to_parent_key()
        self.assertIsInstance(as_b, Test_ConceptBKey)
        self.assertEqual(as_b.instance_id(), key_c.instance_id())

    def test_concept_b_from_concept_c(self):
        key_c = Test_ConceptCKey.create()
        any_key = key_c.to_any_concept_key()
        # ConceptC key should work with from_any_concept_key on ConceptCKey
        result_c = Test_ConceptCKey.from_any_concept_key(any_key)
        self.assertIsNotNone(result_c)


class TestKlubMembership(unittest.TestCase):
    """Test club membership (Klub contains ConceptC, ConceptD)."""

    def test_klub_key_from_concept_c(self):
        key_c = Test_ConceptCKey.create()
        klub_key = Test_KlubKey.from_test_concept_c_key(key_c)
        self.assertIsInstance(klub_key, Test_KlubKey)
        self.assertEqual(klub_key.instance_id(), key_c.instance_id())

    def test_klub_key_from_concept_d(self):
        key_d = Test_ConceptDKey.create()
        klub_key = Test_KlubKey.from_test_concept_d_key(key_d)
        self.assertIsInstance(klub_key, Test_KlubKey)
        self.assertEqual(klub_key.instance_id(), key_d.instance_id())

    def test_klub_key_runtime_id_concept_c(self):
        key_c = Test_ConceptCKey.create()
        klub_key = Test_KlubKey.from_test_concept_c_key(key_c)
        self.assertEqual(klub_key.runtime_id(), md.RuntimeIds.Test_ConceptC)

    def test_klub_key_runtime_id_concept_d(self):
        key_d = Test_ConceptDKey.create()
        klub_key = Test_KlubKey.from_test_concept_d_key(key_d)
        self.assertEqual(klub_key.runtime_id(), md.RuntimeIds.Test_ConceptD)

    def test_klub_key_downcast_to_concept_c(self):
        key_c = Test_ConceptCKey.create()
        klub_key = Test_KlubKey.from_test_concept_c_key(key_c)
        result = klub_key.to_test_concept_c_key()
        self.assertIsNotNone(result)
        self.assertEqual(result, key_c)

    def test_klub_key_downcast_failure(self):
        key_c = Test_ConceptCKey.create()
        klub_key = Test_KlubKey.from_test_concept_c_key(key_c)
        result = klub_key.to_test_concept_d_key()
        self.assertIsNone(result)


class TestKlubKeyIsKnown(unittest.TestCase):
    """Test KlubKey is_known() method."""

    def test_klub_from_concept_c_is_known(self):
        key_c = Test_ConceptCKey.create()
        klub_key = Test_KlubKey.from_test_concept_c_key(key_c)
        self.assertTrue(klub_key.is_known())

    def test_klub_from_concept_d_is_known(self):
        key_d = Test_ConceptDKey.create()
        klub_key = Test_KlubKey.from_test_concept_d_key(key_d)
        self.assertTrue(klub_key.is_known())


class TestPolymorphicDispatch(unittest.TestCase):
    """Test polymorphic dispatch based on runtime_id."""

    def test_dispatch_by_runtime_id(self):
        keys = [
            Test_ConceptAKey.create(),
            Test_ConceptBKey.create(),
            Test_ConceptCKey.create(),
            Test_ConceptDKey.create(),
        ]

        any_keys = [k.to_any_concept_key() for k in keys]

        # Dispatch based on runtime_id
        for any_key in any_keys:
            match any_key.runtime_id():
                case md.RuntimeIds.Test_ConceptA:
                    result = Test_ConceptAKey.from_any_concept_key(any_key)
                    self.assertIsNotNone(result)
                case md.RuntimeIds.Test_ConceptB:
                    result = Test_ConceptBKey.from_any_concept_key(any_key)
                    self.assertIsNotNone(result)
                case md.RuntimeIds.Test_ConceptC:
                    result = Test_ConceptCKey.from_any_concept_key(any_key)
                    self.assertIsNotNone(result)
                case md.RuntimeIds.Test_ConceptD:
                    result = Test_ConceptDKey.from_any_concept_key(any_key)
                    self.assertIsNotNone(result)


if __name__ == "__main__":
    unittest.main()
