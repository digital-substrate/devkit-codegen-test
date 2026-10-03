# Copyright (c) Digital Substrate 2026, All rights reserved.
"""A variant and an any read as views, as every Viper type constructor does.

A variant field reads as its declared class: it tells, reads and writes each alternative by
name, keys included, and changes in place. An any field reads as a view whose content
comes back as the generated class, and takes any value, a generated one included.
"""

import unittest
import dsviper
from features import AnyValue, containers as c
from features.demo import data


class TestVariantField(unittest.TestCase):

    def test_a_variant_field_reads_as_its_declared_class(self):
        u = data.StructureU(f_variant=data.StructureS(f_float=1.0))
        self.assertIs(type(u.f_variant), c.Variant_of_string_or_uint8_or_Demo_StructureS)
        self.assertTrue(u.f_variant.is_Demo_StructureS())
        self.assertEqual(u.f_variant.get_Demo_StructureS().f_float, 1.0)

    def test_a_variant_changes_in_place(self):
        u = data.StructureU(f_variant="x")
        u.f_variant.set_uint8(3)
        self.assertTrue(u.f_variant.is_uint8())
        self.assertEqual(u.f_variant.unwrap(), 3)

    def test_getting_an_alternative_it_does_not_hold_raises(self):
        u = data.StructureU(f_variant="x")
        with self.assertRaises(ValueError):
            u.f_variant.get_uint8()

    def test_key_alternatives_have_their_names(self):
        a_key = data.ConceptAKey.create()
        v = data.StructureVariantKeys(f_target=a_key)
        self.assertTrue(v.f_target.is_Demo_ConceptAKey())
        self.assertEqual(v.f_target.get_Demo_ConceptAKey(), a_key)
        d_key = data.ConceptDKey.create()
        v.f_target.set_Demo_ConceptDKey(d_key)
        self.assertTrue(v.f_target.is_Demo_ConceptDKey())
        self.assertIs(type(v.f_target.get_Demo_ConceptDKey()), data.ConceptDKey)


class TestAnyField(unittest.TestCase):

    def test_an_any_field_reads_as_a_view(self):
        u = data.StructureU(f_any=42)
        self.assertIs(type(u.f_any), AnyValue)
        self.assertTrue(u.f_any)
        self.assertEqual(u.f_any.unwrap(), 42)

    def test_an_any_takes_a_generated_value_and_gives_back_the_runtime_value(self):
        u = data.StructureU()
        u.f_any = data.StructureS(f_string="held")
        self.assertIs(type(u.f_any.unwrap()), dsviper.ValueStructure)
        self.assertEqual(data.StructureS(u.f_any.unwrap()).f_string, "held")

    def test_an_any_gives_back_an_undeclared_shape_as_the_runtime_does(self):
        pair = dsviper.ValueTuple(dsviper.TypeTuple([dsviper.Type.FLOAT, dsviper.Type.FLOAT]), (1.0, 2.0))
        u = data.StructureU(f_any=pair)
        self.assertIs(type(u.f_any.unwrap()), dsviper.ValueTuple)
        self.assertEqual(tuple(u.f_any.unwrap()), (1.0, 2.0))

    def test_an_empty_any_is_nil(self):
        self.assertTrue(data.StructureU().f_any.is_nil())


if __name__ == "__main__":
    unittest.main()
