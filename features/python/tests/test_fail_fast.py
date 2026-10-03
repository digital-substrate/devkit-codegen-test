# Copyright (c) Digital Substrate 2026, All rights reserved.
"""Fail-fast constructor contract (DESIGN.md §1).

A proxy holds exactly one runtime value of exactly its own type. Handing a
constructor a runtime value of the WRONG type must be rejected at construction,
not deferred. These checks are `raise`, not `assert`, so the contract holds even
under `python -O` (where asserts are stripped) — see the `-O` note in each class.
"""

import unittest
import dsviper
from features.demo import StructureS, StructureT, ConceptAKey, ConceptBKey, EnumerationE
from features.containers import Set_of_uint8, Set_of_Demo_ConceptAKey, Vector_of_uint8, Vector_of_int8, Optional_of_Demo_ConceptAKey, Optional_of_Demo_ConceptBKey, Variant_of_string_or_uint8_or_Demo_StructureS


class TestConstructorRejectsWrongRuntimeValue(unittest.TestCase):
    """Each proxy constructor must reject a runtime value of another type.

    The wrong value is a real ValueX of a *different* type, obtained from a
    sibling proxy's `.unwrap_value()`, so this exercises the `value.type() != mt.type…`
    branch specifically — the one that was a bare `assert` before §4.
    """

    def test_struct_rejects_other_struct(self):
        with self.assertRaises(TypeError):
            StructureS(StructureT().unwrap_value())

    def test_concept_key_rejects_other_concept(self):
        with self.assertRaises(TypeError):
            ConceptAKey(ConceptBKey.create().unwrap_value())

    def test_set_rejects_other_element_type(self):
        with self.assertRaises(TypeError):
            Set_of_uint8(Set_of_Demo_ConceptAKey().unwrap_value())

    def test_vector_rejects_other_element_type(self):
        with self.assertRaises(TypeError):
            Vector_of_uint8(Vector_of_int8([1]).unwrap_value())

    def test_native_content_that_does_not_fit_raises_the_runtime_error(self):
        # Not a value of another type, but content the conversion refuses: as an append does.
        with self.assertRaisesRegex(dsviper.ViperError, "range of 'uint8'"):
            Vector_of_uint8([300])

    def test_optional_rejects_other_element_type(self):
        with self.assertRaises(TypeError):
            Optional_of_Demo_ConceptAKey(Optional_of_Demo_ConceptBKey().unwrap_value())

    def test_enum_rejects_non_enum_value(self):
        with self.assertRaises(TypeError):
            EnumerationE(StructureS().unwrap_value())


class TestConstructorAcceptsCorrectRuntimeValue(unittest.TestCase):
    """The fail-fast check must not reject a correctly-typed runtime value."""

    def test_struct_accepts_same_type(self):
        s = StructureS(StructureS().unwrap_value())
        self.assertIsInstance(s, StructureS)

    def test_set_accepts_same_type(self):
        a = Set_of_uint8(Set_of_uint8([1, 2]).unwrap_value())
        self.assertEqual(len(a), 2)


class TestVariantArmGetterPrecondition(unittest.TestCase):
    """Reading the wrong variant arm must raise, not silently misinterpret.

    This was `assert self.is<arm>()` before §4 — stripped under `-O`, which
    would let `unwrap()` reinterpret the held value as the wrong type.
    """

    def test_get_wrong_arm_raises(self):
        v = Variant_of_string_or_uint8_or_Demo_StructureS("hello")
        self.assertTrue(v.is_string())
        with self.assertRaises(ValueError):
            v.get_uint8()

    def test_get_right_arm_returns(self):
        v = Variant_of_string_or_uint8_or_Demo_StructureS("hello")
        self.assertEqual(v.get_string(), "hello")


if __name__ == "__main__":
    unittest.main()
