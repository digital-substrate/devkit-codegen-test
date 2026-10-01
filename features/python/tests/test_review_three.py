# Copyright (c) Digital Substrate 2026, All rights reserved.
"""Shapes the annotations allow, and that the runtime must then accept."""

import unittest
from features import containers as c
from features.demo import data


class TestShapes(unittest.TestCase):

    def test_a_tuple_keys_a_map_of_vectors(self):
        s1, s2 = data.StructureS(f_float=1.0), data.StructureS(f_float=2.0)
        m = c.Map_of_Vector_of_Demo_StructureS_to_string({(s1, s2): "pair"})
        self.assertEqual(len(m), 1)

    def test_a_default_structure_prints(self):
        self.assertIn("Demo::StructureU(", repr(data.StructureU()))
        self.assertTrue(data.StructureU().f_klub.instance_id() is not None)

    def test_a_dict_source_takes_generated_values(self):
        t = data.StructureT({"field_structure_s": data.StructureS(f_string="inner")})
        self.assertEqual(t.field_structure_s.f_string, "inner")

    def test_a_key_of_another_concept_points_to_from_key(self):
        with self.assertRaisesRegex(TypeError, "from_key"):
            data.ConceptAKey(data.ConceptDKey.create())  # type: ignore[arg-type]

    def test_a_removed_xarray_position_reads_none(self):
        x = c.XArray_of_uint8([1, 2])
        position = x.positions()[0]
        x.remove(position)
        self.assertIsNone(x[position])


if __name__ == "__main__":
    unittest.main()
