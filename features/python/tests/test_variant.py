# Copyright (c) Digital Substrate 2026, All rights reserved.
"""Tests for Kibo-generated Variant proxy classes."""

import unittest
from features.data import Variant_string_uint8_Test_StructureS, Test_StructureS


class TestVariant(unittest.TestCase):
    """Test Variant type."""

    def test_variant_string(self):
        v = Variant_string_uint8_Test_StructureS()
        v.set_string("hello")
        self.assertTrue(v.is_string())
        self.assertEqual(v.get_string(), "hello")

    def test_variant_uint8(self):
        v = Variant_string_uint8_Test_StructureS()
        v.set_uint8(42)
        self.assertTrue(v.is_uint8())
        self.assertEqual(v.get_uint8(), 42)

    def test_variant_structure(self):
        s = Test_StructureS({"f_float": 1.5, "f_string": "test"})
        v = Variant_string_uint8_Test_StructureS()
        v.set_Test_StructureS(s)
        self.assertTrue(v.is_Test_StructureS())
        unwrapped = v.get_Test_StructureS()
        self.assertAlmostEqual(unwrapped.f_float, 1.5, places=5)


class TestVariantConstruction(unittest.TestCase):
    """Test Variant construction with initial value."""

    def test_construct_with_string(self):
        v = Variant_string_uint8_Test_StructureS("hello")
        self.assertTrue(v.is_string())
        self.assertEqual(v.get_string(), "hello")

    def test_construct_with_uint8(self):
        v = Variant_string_uint8_Test_StructureS(42)
        self.assertTrue(v.is_uint8())
        self.assertEqual(v.get_uint8(), 42)

    def test_construct_with_structure(self):
        s = Test_StructureS({"f_float": 2.5, "f_string": "world"})
        v = Variant_string_uint8_Test_StructureS(s)
        self.assertTrue(v.is_Test_StructureS())


class TestVariantTypeChecking(unittest.TestCase):
    """Test Variant type checking methods."""

    def test_is_string_false(self):
        v = Variant_string_uint8_Test_StructureS()
        v.set_uint8(42)
        self.assertFalse(v.is_string())

    def test_is_uint8_false(self):
        v = Variant_string_uint8_Test_StructureS()
        v.set_string("hello")
        self.assertFalse(v.is_uint8())

    def test_is_structure_false(self):
        v = Variant_string_uint8_Test_StructureS()
        v.set_string("hello")
        self.assertFalse(v.is_Test_StructureS())


class TestVariantSwitch(unittest.TestCase):
    """Test Variant type switching."""

    def test_switch_from_string_to_uint8(self):
        v = Variant_string_uint8_Test_StructureS()
        v.set_string("hello")
        self.assertTrue(v.is_string())
        v.set_uint8(42)
        self.assertTrue(v.is_uint8())
        self.assertFalse(v.is_string())

    def test_switch_from_uint8_to_structure(self):
        v = Variant_string_uint8_Test_StructureS()
        v.set_uint8(42)
        s = Test_StructureS({"f_float": 1.0, "f_string": "test"})
        v.set_Test_StructureS(s)
        self.assertTrue(v.is_Test_StructureS())
        self.assertFalse(v.is_uint8())


class TestVariantCopy(unittest.TestCase):
    """Test Variant copy behavior."""

    def test_copy_string_variant(self):
        v1 = Variant_string_uint8_Test_StructureS()
        v1.set_string("hello")
        v2 = v1.copy()
        self.assertTrue(v2.is_string())
        self.assertEqual(v2.get_string(), "hello")

    def test_copy_uint8_variant(self):
        v1 = Variant_string_uint8_Test_StructureS()
        v1.set_uint8(42)
        v2 = v1.copy()
        self.assertTrue(v2.is_uint8())
        self.assertEqual(v2.get_uint8(), 42)

    def test_copy_structure_variant(self):
        s = Test_StructureS({"f_float": 1.5, "f_string": "test"})
        v1 = Variant_string_uint8_Test_StructureS()
        v1.set_Test_StructureS(s)
        v2 = v1.copy()
        self.assertTrue(v2.is_Test_StructureS())
        self.assertAlmostEqual(v2.get_Test_StructureS().f_float, 1.5, places=5)

    def test_copy_independent(self):
        v1 = Variant_string_uint8_Test_StructureS()
        v1.set_string("hello")
        v2 = v1.copy()
        v1.set_uint8(99)
        self.assertTrue(v2.is_string())
        self.assertEqual(v2.get_string(), "hello")


class TestVariantSerialization(unittest.TestCase):
    """Test Variant encode/decode serialization."""

    def test_encode_decode_string(self):
        v1 = Variant_string_uint8_Test_StructureS()
        v1.set_string("hello")
        blob = v1.encode()
        v2 = Variant_string_uint8_Test_StructureS.decode(blob)
        self.assertTrue(v2.is_string())
        self.assertEqual(v2.get_string(), "hello")

    def test_encode_decode_uint8(self):
        v1 = Variant_string_uint8_Test_StructureS()
        v1.set_uint8(42)
        blob = v1.encode()
        v2 = Variant_string_uint8_Test_StructureS.decode(blob)
        self.assertTrue(v2.is_uint8())
        self.assertEqual(v2.get_uint8(), 42)

    def test_encode_decode_structure(self):
        s = Test_StructureS({"f_float": 2.5, "f_string": "world"})
        v1 = Variant_string_uint8_Test_StructureS()
        v1.set_Test_StructureS(s)
        blob = v1.encode()
        v2 = Variant_string_uint8_Test_StructureS.decode(blob)
        self.assertTrue(v2.is_Test_StructureS())
        self.assertEqual(v2.get_Test_StructureS().f_string, "world")


if __name__ == "__main__":
    unittest.main()
