# Copyright (c) Digital Substrate 2026, All rights reserved.
"""A field's name and path, as constants (feature Fields).

Code that handles a structure through the dynamic API names the field: a constant completes
and a type checker checks it, where a string literal is neither. The name is the model's own,
the one the runtime matches; the path reads that field in a Viper value.
"""

import unittest

from features.demo import data, fields, paths


class TestFields(unittest.TestCase):

    def test_a_field_name_is_the_models_name(self):
        self.assertEqual(fields.StructureS.f_float, "f_float")

    def test_a_path_reads_the_field_in_a_value(self):
        s = data.StructureS(f_float=1.5)
        self.assertEqual(paths.StructureS.f_float.at(s.unwrap_value()), 1.5)


if __name__ == "__main__":
    unittest.main()
