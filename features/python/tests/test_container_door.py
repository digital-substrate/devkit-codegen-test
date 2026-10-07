# Copyright (c) Digital Substrate 2026, All rights reserved.
"""Where the host's own collections enter.

A field takes its declared container class, and also the host's collection when nothing in
it is generated: the runtime decodes it, element by element, at the line that writes it. A
host collection of generated values is refused by a field, since a wrong element would
travel unchecked until it reached the runtime; the declared container's constructor takes
one, and every element is checked where the container is built.
"""

import unittest
import dsviper
from features import containers as c
from features.demo import data


class TestContainerDoor(unittest.TestCase):

    def setUp(self):
        self.s1 = data.StructureS(f_float=1.0)
        self.s2 = data.StructureS(f_float=2.0)

    def test_a_declared_container_takes_its_generated_elements(self):
        self.assertEqual(len(c.Set_of_Demo_StructureS([self.s1, self.s2])), 2)
        self.assertEqual(len(c.Vector_of_Demo_StructureS([self.s1])), 1)
        self.assertEqual(len(c.XArray_of_Demo_StructureS([self.s1, self.s2])), 2)
        self.assertEqual(c.Map_of_string_to_Demo_StructureS({"k": self.s1})["k"], self.s1)

    def test_a_declared_container_takes_any_iterable_of_its_elements(self):
        # The constructor is annotated Iterable: a generator, a dict's keys, a mapping view.
        self.assertEqual(len(c.Set_of_Demo_StructureS(s for s in (self.s1, self.s2))), 2)
        self.assertEqual(len(c.Vector_of_Demo_StructureS(iter([self.s1]))), 1)
        self.assertEqual(len(c.Set_of_Demo_StructureS({self.s1: 1}.keys())), 1)

    def test_a_wrong_element_is_refused_where_the_container_is_built(self):
        # Content that does not fit the type: the runtime's error, naming the element at fault.
        with self.assertRaisesRegex(dsviper.ViperError, r"at\(1\)"):
            c.Set_of_Demo_StructureS([self.s1, data.StructureT()])

    def test_a_field_takes_a_host_collection_of_primitives(self):
        u = data.StructureU()
        u.f_vector = [1, 2, 3]
        u.f_set = {4, 5}
        self.assertEqual(list(u.f_vector), [1, 2, 3])
        self.assertEqual(set(u.f_set), {4, 5})
        v = data.StructureV(f_vector=[7], f_tuple=(9, "nine"), f_map={1: "one"})
        self.assertEqual(list(v.f_vector), [7])

    def test_a_field_refuses_a_host_collection_of_generated_values(self):
        u = data.StructureU()
        with self.assertRaises(TypeError):
            u.f_set_s = [self.s1]


if __name__ == "__main__":
    unittest.main()
