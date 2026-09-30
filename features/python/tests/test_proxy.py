# Copyright (c) Digital Substrate 2026, All rights reserved.
"""Tests for the shared Proxy base of Kibo-generated classes."""

import unittest
from features.demo import StructureS
from features.containers import Set_of_uint8, Vector_of_uint8


class TestProxyEqualityWithForeignOperand(unittest.TestCase):
    """A proxy compared against a non-proxy must answer, not raise.

    `x == None` and `x in [...]` are ordinary Python idioms. Dereferencing the
    operand's `vpr_value` unconditionally turns both into AttributeError.
    """

    def test_eq_none(self):
        s = StructureS()
        self.assertFalse(s == None)  # noqa: E711 — the point is the operator, not `is`

    def test_ne_none(self):
        s = StructureS()
        self.assertTrue(s != None)  # noqa: E711

    def test_eq_unrelated_type(self):
        s = StructureS()
        self.assertFalse(s == 42)
        self.assertFalse(s == "StructureS")

    def test_membership_in_heterogeneous_list(self):
        s = Set_of_uint8([1])
        self.assertFalse(s in [1, 2, "three"])

    def test_eq_across_proxy_types(self):
        a = Set_of_uint8([1])
        b = Vector_of_uint8([1])
        self.assertFalse(a == b)


class TestProxyEqualityWithSameType(unittest.TestCase):
    """The foreign-operand fix must not weaken same-type comparison."""

    def test_equal_values_compare_equal(self):
        self.assertTrue(Set_of_uint8([1, 2]) == Set_of_uint8([1, 2]))

    def test_different_values_compare_unequal(self):
        self.assertFalse(Set_of_uint8([1, 2]) == Set_of_uint8([1, 3]))

    def test_hash_is_stable_for_equal_values(self):
        self.assertEqual(hash(Set_of_uint8([1, 2])), hash(Set_of_uint8([1, 2])))


if __name__ == "__main__":
    unittest.main()
