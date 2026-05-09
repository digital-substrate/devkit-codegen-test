# Copyright (c) Digital Substrate 2026, All rights reserved.
"""Tests for Kibo-generated Enumeration proxy classes."""

import unittest
from features.data import Test_EnumerationE


class TestEnumerationCases(unittest.TestCase):
    """Test enumeration case access."""

    def test_case_a(self):
        e = Test_EnumerationE.A
        self.assertIsInstance(e, Test_EnumerationE)

    def test_case_b(self):
        e = Test_EnumerationE.B
        self.assertIsInstance(e, Test_EnumerationE)

    def test_case_c(self):
        e = Test_EnumerationE.C
        self.assertIsInstance(e, Test_EnumerationE)

    def test_cases_are_singletons(self):
        a1 = Test_EnumerationE.A
        a2 = Test_EnumerationE.A
        self.assertIs(a1, a2)


class TestEnumerationName(unittest.TestCase):
    """Test enumeration name() method."""

    def test_name_a(self):
        self.assertEqual(Test_EnumerationE.A.name(), "a")

    def test_name_b(self):
        self.assertEqual(Test_EnumerationE.B.name(), "b")

    def test_name_c(self):
        self.assertEqual(Test_EnumerationE.C.name(), "c")


class TestEnumerationFromStr(unittest.TestCase):
    """Test enumeration from_str() factory method."""

    def test_from_str_a(self):
        e = Test_EnumerationE.from_str("a")
        self.assertEqual(e.name(), "a")

    def test_from_str_b(self):
        e = Test_EnumerationE.from_str("b")
        self.assertEqual(e.name(), "b")

    def test_from_str_c(self):
        e = Test_EnumerationE.from_str("c")
        self.assertEqual(e.name(), "c")

    def test_from_str_invalid(self):
        with self.assertRaises(ValueError):
            Test_EnumerationE.from_str("invalid")

    def test_from_str_type_error(self):
        with self.assertRaises(TypeError):
            Test_EnumerationE.from_str(123)


class TestEnumerationEquality(unittest.TestCase):
    """Test enumeration equality comparison."""

    def test_same_case_equal(self):
        self.assertEqual(Test_EnumerationE.A, Test_EnumerationE.A)
        self.assertEqual(Test_EnumerationE.B, Test_EnumerationE.B)

    def test_different_cases_not_equal(self):
        self.assertNotEqual(Test_EnumerationE.A, Test_EnumerationE.B)
        self.assertNotEqual(Test_EnumerationE.B, Test_EnumerationE.C)

    def test_from_str_equals_direct(self):
        self.assertEqual(Test_EnumerationE.from_str("a"), Test_EnumerationE.A)
        self.assertEqual(Test_EnumerationE.from_str("b"), Test_EnumerationE.B)


class TestEnumerationHash(unittest.TestCase):
    """Test enumeration hashing for use in sets/dicts."""

    def test_hashable(self):
        h = hash(Test_EnumerationE.A)
        self.assertIsInstance(h, int)

    def test_same_case_same_hash(self):
        self.assertEqual(hash(Test_EnumerationE.A), hash(Test_EnumerationE.A))

    def test_usable_in_set(self):
        s = {Test_EnumerationE.A, Test_EnumerationE.B, Test_EnumerationE.A}
        self.assertEqual(len(s), 2)

    def test_usable_as_dict_key(self):
        d = {Test_EnumerationE.A: "first", Test_EnumerationE.B: "second"}
        self.assertEqual(d[Test_EnumerationE.A], "first")


class TestEnumerationSerialization(unittest.TestCase):
    """Test enumeration encode/decode serialization."""

    def test_encode_decode_a(self):
        e1 = Test_EnumerationE.A
        blob = e1.encode()
        e2 = Test_EnumerationE.decode(blob)
        self.assertEqual(e2.name(), "a")

    def test_encode_decode_b(self):
        e1 = Test_EnumerationE.B
        blob = e1.encode()
        e2 = Test_EnumerationE.decode(blob)
        self.assertEqual(e2.name(), "b")

    def test_encode_decode_c(self):
        e1 = Test_EnumerationE.C
        blob = e1.encode()
        e2 = Test_EnumerationE.decode(blob)
        self.assertEqual(e2.name(), "c")


class TestEnumerationRepr(unittest.TestCase):
    """Test enumeration string representation."""

    def test_repr_contains_name(self):
        r = repr(Test_EnumerationE.A)
        self.assertIn("a", r.lower())


if __name__ == "__main__":
    unittest.main()
