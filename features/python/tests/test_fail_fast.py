# Copyright (c) Digital Substrate 2026, All rights reserved.
"""Fail-fast constructor contract (DESIGN.md §1).

A proxy holds exactly one runtime value of exactly its own type. Handing a
constructor a runtime value of the WRONG type must be rejected at construction,
not deferred. These checks are `raise`, not `assert`, so the contract holds even
under `python -O` (where asserts are stripped) — see the `-O` note in each class.
"""

import unittest
from features.demo import StructureS, StructureT, ConceptAKey, ConceptBKey, EnumerationE
from features.containers import Set_uint8, Set_Demo_ConceptAKey, Vector_uint8, Vector_int8, Optional_Demo_ConceptAKey, Optional_Demo_ConceptBKey, Variant_string_uint8_Demo_StructureS


class TestConstructorRejectsWrongRuntimeValue(unittest.TestCase):
    """Each proxy constructor must reject a runtime value of another type.

    The wrong value is a real ValueX of a *different* type, obtained from a
    sibling proxy's `.value`, so this exercises the `value.type() != mt.type…`
    branch specifically — the one that was a bare `assert` before §4.
    """

    def test_struct_rejects_other_struct(self):
        with self.assertRaises(TypeError):
            StructureS(StructureT().value)

    def test_concept_key_rejects_other_concept(self):
        with self.assertRaises(TypeError):
            ConceptAKey(ConceptBKey.create().value)

    def test_set_rejects_other_element_type(self):
        with self.assertRaises(TypeError):
            Set_uint8(Set_Demo_ConceptAKey().value)

    def test_vector_rejects_other_element_type(self):
        with self.assertRaises(TypeError):
            Vector_uint8(Vector_int8([1]).value)

    def test_optional_rejects_other_element_type(self):
        with self.assertRaises(TypeError):
            Optional_Demo_ConceptAKey(Optional_Demo_ConceptBKey().value)

    def test_enum_rejects_non_enum_value(self):
        with self.assertRaises(TypeError):
            EnumerationE(StructureS().value)


class TestConstructorAcceptsCorrectRuntimeValue(unittest.TestCase):
    """The fail-fast check must not reject a correctly-typed runtime value."""

    def test_struct_accepts_same_type(self):
        s = StructureS(StructureS().value)
        self.assertIsInstance(s, StructureS)

    def test_set_accepts_same_type(self):
        a = Set_uint8(Set_uint8([1, 2]).value)
        self.assertEqual(len(a), 2)


class TestVariantArmGetterPrecondition(unittest.TestCase):
    """Reading the wrong variant arm must raise, not silently misinterpret.

    This was `assert self.is<arm>()` before §4 — stripped under `-O`, which
    would let `unwrap()` reinterpret the held value as the wrong type.
    """

    def test_get_wrong_arm_raises(self):
        v = Variant_string_uint8_Demo_StructureS("hello")
        self.assertTrue(v.is_string())
        with self.assertRaises(ValueError):
            v.get_uint8()

    def test_get_right_arm_returns(self):
        v = Variant_string_uint8_Demo_StructureS("hello")
        self.assertEqual(v.get_string(), "hello")


if __name__ == "__main__":
    unittest.main()
