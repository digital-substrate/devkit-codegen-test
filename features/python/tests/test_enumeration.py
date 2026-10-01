# Copyright (c) Digital Substrate 2026, All rights reserved.
"""Tests for Kibo-generated Enumeration proxy classes."""

import unittest
import dsviper
from features import definitions
from features.demo import EnumerationE


class TestEnumerationCases(unittest.TestCase):
    """Test enumeration case access."""

    def test_case_a(self):
        e = EnumerationE.A
        self.assertIsInstance(e, EnumerationE)

    def test_case_b(self):
        e = EnumerationE.B
        self.assertIsInstance(e, EnumerationE)

    def test_case_c(self):
        e = EnumerationE.C
        self.assertIsInstance(e, EnumerationE)

    def test_cases_are_singletons(self):
        a1 = EnumerationE.A
        a2 = EnumerationE.A
        self.assertIs(a1, a2)


class TestEnumerationName(unittest.TestCase):
    """Test enumeration name() method."""

    def test_name_a(self):
        self.assertEqual(EnumerationE.A.value, "a")

    def test_name_b(self):
        self.assertEqual(EnumerationE.B.value, "b")

    def test_name_c(self):
        self.assertEqual(EnumerationE.C.value, "c")


class TestEnumerationFromStr(unittest.TestCase):
    """Test enumeration from_str() factory method."""

    def test_from_str_a(self):
        e = EnumerationE.from_str("a")
        self.assertEqual(e.value, "a")

    def test_from_str_b(self):
        e = EnumerationE.from_str("b")
        self.assertEqual(e.value, "b")

    def test_from_str_c(self):
        e = EnumerationE.from_str("c")
        self.assertEqual(e.value, "c")

    def test_from_str_invalid(self):
        with self.assertRaises(ValueError):
            EnumerationE.from_str("invalid")

    def test_from_str_type_error(self):
        with self.assertRaises(TypeError):
            EnumerationE.from_str(123)


class TestEnumerationEquality(unittest.TestCase):
    """Test enumeration equality comparison."""

    def test_same_case_equal(self):
        self.assertEqual(EnumerationE.A, EnumerationE.A)
        self.assertEqual(EnumerationE.B, EnumerationE.B)

    def test_different_cases_not_equal(self):
        self.assertNotEqual(EnumerationE.A, EnumerationE.B)
        self.assertNotEqual(EnumerationE.B, EnumerationE.C)

    def test_from_str_equals_direct(self):
        self.assertEqual(EnumerationE.from_str("a"), EnumerationE.A)
        self.assertEqual(EnumerationE.from_str("b"), EnumerationE.B)


class TestEnumerationHash(unittest.TestCase):
    """Test enumeration hashing for use in sets/dicts."""

    def test_hashable(self):
        h = hash(EnumerationE.A)
        self.assertIsInstance(h, int)

    def test_same_case_same_hash(self):
        self.assertEqual(hash(EnumerationE.A), hash(EnumerationE.A))

    def test_usable_in_set(self):
        s = {EnumerationE.A, EnumerationE.B, EnumerationE.A}
        self.assertEqual(len(s), 2)

    def test_usable_as_dict_key(self):
        d = {EnumerationE.A: "first", EnumerationE.B: "second"}
        self.assertEqual(d[EnumerationE.A], "first")


class TestEnumerationSerialization(unittest.TestCase):
    """An enumeration crosses to the runtime as a ValueEnumeration, and back by its case name."""

    def test_encode_decode_a(self):
        e1 = EnumerationE.A
        blob = dsviper.Value.encode(dsviper.ValueEnumeration(EnumerationE.type(), e1.value))
        e2 = EnumerationE(dsviper.ValueEnumeration.cast(dsviper.Value.decode(blob, EnumerationE.type(), definitions())).name())
        self.assertEqual(e2.value, "a")

    def test_encode_decode_b(self):
        e1 = EnumerationE.B
        blob = dsviper.Value.encode(dsviper.ValueEnumeration(EnumerationE.type(), e1.value))
        e2 = EnumerationE(dsviper.ValueEnumeration.cast(dsviper.Value.decode(blob, EnumerationE.type(), definitions())).name())
        self.assertEqual(e2.value, "b")

    def test_encode_decode_c(self):
        e1 = EnumerationE.C
        blob = dsviper.Value.encode(dsviper.ValueEnumeration(EnumerationE.type(), e1.value))
        e2 = EnumerationE(dsviper.ValueEnumeration.cast(dsviper.Value.decode(blob, EnumerationE.type(), definitions())).name())
        self.assertEqual(e2.value, "c")


class TestEnumerationRepr(unittest.TestCase):
    """Test enumeration string representation."""

    def test_repr_contains_name(self):
        r = repr(EnumerationE.A)
        self.assertIn("a", r.lower())


if __name__ == "__main__":
    unittest.main()
