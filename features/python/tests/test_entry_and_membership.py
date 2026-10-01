# Copyright (c) Digital Substrate 2026, All rights reserved.
"""The package leads to every unit and its attachments, and membership always answers.

A key is found in a container of another view of it, as the runtime's equality says; an
element of the wrong type is simply not there.
"""

import unittest
import features
from features import containers as c
from features.demo import data


class TestEntry(unittest.TestCase):

    def test_a_unit_carries_its_attachments(self):
        self.assertIs(features.demo.attachments.ConceptA, __import__("features.demo.attachments", fromlist=["x"]).ConceptA)
        self.assertTrue(hasattr(features, "AnyValue") and hasattr(features, "AnyConceptKey"))


class TestMembership(unittest.TestCase):

    def test_a_key_is_found_through_another_view(self):
        key = data.ConceptCKey.create()
        keys = c.Set_of_AnyConceptKey([key.to_any_concept_key()])
        self.assertIn(key, keys)
        self.assertIn(key.to_parent_key(), keys)
        self.assertNotIn(data.ConceptCKey.create(), keys)

    def test_an_element_of_the_wrong_type_is_not_there(self):
        self.assertNotIn("x", c.Set_of_uint8([1]))
        self.assertNotIn(300, c.Vector_of_uint8([1]))
        self.assertNotIn(3, c.Map_of_string_to_Demo_StructureS())
        self.assertFalse(c.Set_of_uint8([1]).contains("x"))  # type: ignore[arg-type]


if __name__ == "__main__":
    unittest.main()
