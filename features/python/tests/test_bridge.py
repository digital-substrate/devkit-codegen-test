# Copyright (c) Digital Substrate 2026, All rights reserved.
"""The bridge to the Viper value: wrap_value takes a value without copying it, unwrap_value
gives it back, and a constructor builds a new value -- copying one it is given, as the
runtime's own constructors do."""

import unittest
import dsviper
from features import AnyValue, containers as c
from features.demo import data


class TestWrapValue(unittest.TestCase):

    def test_a_structure_wraps_the_value_itself(self):
        value = data.StructureS(f_string="a").unwrap_value()
        wrapped = data.StructureS.wrap_value(value)
        wrapped.f_string = "b"
        self.assertEqual(value.at("f_string"), "b")
        self.assertIs(wrapped.unwrap_value(), value)

    def test_a_container_wraps_the_value_itself(self):
        value = c.Vector_of_uint8([1]).unwrap_value()
        c.Vector_of_uint8.wrap_value(value).append(2)
        self.assertEqual(list(value), [1, 2])

    def test_an_any_wraps_the_value_itself(self):
        value = dsviper.ValueAny(1)
        AnyValue.wrap_value(value).wrap(2)
        self.assertEqual(value.unwrap(), 2)

    def test_keys_and_enumerations_wrap(self):
        key = data.ConceptAKey.create()
        self.assertEqual(data.ConceptAKey.wrap_value(key.unwrap_value()), key)
        self.assertIs(data.EnumerationE.wrap_value(data.EnumerationE.B.unwrap_value()), data.EnumerationE.B)

    def test_a_value_of_another_type_is_refused(self):
        with self.assertRaises(TypeError):
            data.StructureS.wrap_value(data.StructureT().unwrap_value())
        with self.assertRaises(TypeError):
            c.Vector_of_uint8.wrap_value(c.Vector_of_int8([1]).unwrap_value())
        with self.assertRaises(TypeError):
            data.ConceptAKey.wrap_value(data.ConceptDKey.create().unwrap_value())


class TestConstructor(unittest.TestCase):

    def test_a_structure_copies_the_value_it_is_given(self):
        value = data.StructureS(f_string="a").unwrap_value()
        built = data.StructureS(value)
        built.f_string = "b"
        self.assertEqual(value.at("f_string"), "a")

    def test_a_container_copies_the_container_it_is_given(self):
        source = c.Vector_of_uint8([1])
        c.Vector_of_uint8(source).append(2)
        c.Vector_of_uint8(source.unwrap_value()).append(3)
        self.assertEqual(list(source), [1])

    def test_an_any_copies_the_any_it_is_given(self):
        value = dsviper.ValueAny(1)
        AnyValue(value).wrap(2)
        self.assertEqual(value.unwrap(), 1)

    def test_a_copy_is_shallow(self):
        source = c.Vector_of_Demo_StructureS([data.StructureS(f_string="a")])
        built = c.Vector_of_Demo_StructureS(source)
        built[0].f_string = "b"
        self.assertEqual(source[0].f_string, "b")

if __name__ == "__main__":
    unittest.main()
