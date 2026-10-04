# Copyright (c) Digital Substrate 2026, All rights reserved.
"""The bridge to the Viper value: a generated class is a box around one. wrap_value and a
constructor given a value box it without copying, unwrap_value gives it back, and a copy is
explicit."""

import unittest
import dsviper
from features import AnyConceptKey, AnyValue, containers as c
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

    def test_a_value_of_another_kind_is_refused(self):
        text = dsviper.Value.create(dsviper.Type.STRING, "a")
        for cls in (data.StructureS, data.ConceptAKey, data.KlubKey, data.EnumerationE, AnyValue, AnyConceptKey,
                    c.Vector_of_uint8):
            with self.subTest(cls=cls.__name__), self.assertRaises(TypeError):
                cls.wrap_value(text)


class TestConstructor(unittest.TestCase):

    def test_a_structure_boxes_the_value_it_is_given(self):
        value = data.StructureS(f_string="a").unwrap_value()
        data.StructureS(value).f_string = "b"
        self.assertEqual(value.at("f_string"), "b")

    def test_a_container_boxes_the_container_it_is_given(self):
        source = c.Vector_of_uint8([1])
        c.Vector_of_uint8(source).append(2)
        c.Vector_of_uint8(source.unwrap_value()).append(3)
        self.assertEqual(list(source), [1, 2, 3])

    def test_an_any_boxes_the_any_it_is_given(self):
        value = dsviper.ValueAny(1)
        AnyValue(value).wrap(2)
        self.assertEqual(value.unwrap(), 2)

    def test_a_copy_is_explicit(self):
        value = data.StructureS(f_string="a").unwrap_value()
        data.StructureS(value.copy()).f_string = "b"
        self.assertEqual(value.at("f_string"), "a")

    def test_a_container_built_from_elements_keeps_them_whatever_its_kind(self):
        built = [
            lambda s: c.Vector_of_Demo_StructureS([s])[0],
            lambda s: c.XArray_of_Demo_StructureS([s])[0],
            lambda s: c.Map_of_string_to_Demo_StructureS({"k": s})["k"],
            lambda s: c.Optional_of_Demo_StructureS(s).unwrap(),
        ]
        for read in built:
            s = data.StructureS(f_string="a")
            held = read(s)
            s.f_string = "b"
            self.assertEqual(held.f_string, "b")

    def test_natives_build_a_new_value(self):
        self.assertEqual(list(c.Vector_of_uint8([1, 2])), [1, 2])

if __name__ == "__main__":
    unittest.main()
