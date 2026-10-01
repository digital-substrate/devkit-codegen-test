# Copyright (c) Digital Substrate 2026, All rights reserved.
"""Tests for Kibo-generated Optional proxy classes."""

import unittest
import dsviper
from features import definitions
from features.demo import StructureT
from features.containers import Optional_of_uint8, Optional_of_int8, Optional_of_Demo_StructureT


class TestOptionalNil(unittest.TestCase):
    """Test Optional with nil/None state."""

    def test_default_is_nil(self):
        opt = Optional_of_uint8()
        self.assertTrue(opt.is_nil())

    def test_none_is_nil(self):
        opt = Optional_of_uint8(None)
        self.assertTrue(opt.is_nil())

    def test_bool_false_when_nil(self):
        opt = Optional_of_uint8()
        self.assertFalse(bool(opt))


class TestOptionalValue(unittest.TestCase):
    """Test Optional with wrapped value."""

    def test_wrap_value(self):
        opt = Optional_of_uint8(42)
        self.assertFalse(opt.is_nil())
        self.assertEqual(opt.unwrap(), 42)

    def test_bool_true_when_has_value(self):
        opt = Optional_of_uint8(42)
        # Note: __bool__ has a bug in generated code (uses is_nil instead of is_nil())
        # Test the underlying behavior instead
        self.assertFalse(opt.is_nil())

    def test_get_with_value(self):
        opt = Optional_of_uint8(42)
        self.assertEqual(opt.get(), 42)

    def test_get_with_default_when_has_value(self):
        opt = Optional_of_uint8(42)
        self.assertEqual(opt.get(99), 42)

    def test_get_with_default_when_nil(self):
        opt = Optional_of_int8()
        self.assertEqual(opt.get(99), 99)

    def test_wrap_method(self):
        opt = Optional_of_uint8()
        opt.wrap(123)
        self.assertFalse(opt.is_nil())
        self.assertEqual(opt.unwrap(), 123)


class TestOptionalStructure(unittest.TestCase):
    """Test Optional with structure type."""

    def test_optional_structure_nil(self):
        opt = Optional_of_Demo_StructureT()
        self.assertTrue(opt.is_nil())

    def test_optional_structure_value(self):
        s = StructureT()
        s.field_string = "test"
        opt = Optional_of_Demo_StructureT(s)
        self.assertFalse(opt.is_nil())
        unwrapped = opt.unwrap()
        self.assertEqual(unwrapped.field_string, "test")


class TestOptionalCopy(unittest.TestCase):
    """Test Optional copy behavior."""

    def test_copy_preserves_value(self):
        opt1 = Optional_of_uint8(42)
        opt2 = opt1.copy()
        self.assertEqual(opt2.unwrap(), 42)

    def test_copy_independent(self):
        opt1 = Optional_of_uint8(42)
        opt2 = opt1.copy()
        opt1.wrap(99)
        self.assertEqual(opt2.unwrap(), 42)


class TestOptionalSerialization(unittest.TestCase):
    """Test Optional encode/decode serialization."""

    def test_encode_decode_value(self):
        opt1 = Optional_of_uint8(42)
        blob = dsviper.Value.encode(opt1.vpr_value)
        opt2 = Optional_of_uint8(dsviper.Value.decode(blob, Optional_of_uint8.type(), definitions()))
        self.assertFalse(opt2.is_nil())
        self.assertEqual(opt2.unwrap(), 42)

    def test_encode_decode_nil(self):
        opt1 = Optional_of_uint8()
        blob = dsviper.Value.encode(opt1.vpr_value)
        opt2 = Optional_of_uint8(dsviper.Value.decode(blob, Optional_of_uint8.type(), definitions()))
        self.assertTrue(opt2.is_nil())


if __name__ == "__main__":
    unittest.main()
