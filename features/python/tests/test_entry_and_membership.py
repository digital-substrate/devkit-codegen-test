# Copyright (c) Digital Substrate 2026, All rights reserved.
"""The package leads to every unit and its attachments, and membership is as strict as storing.

A key is looked up as the key the container holds: another view of it is widened first, with
to_parent_key() or to_any_concept_key(), and an element of the wrong type raises.
"""

import unittest
import dsviper
import features
from features import containers as c
from features.demo import data


class TestEntry(unittest.TestCase):

    def test_attachments_are_imported_by_their_path(self):
        # The Attachments feature: a submodule of the unit, imported as a C++ header is included.
        import features.demo.attachments
        self.assertTrue(hasattr(features.demo.attachments, "ConceptA"))
        self.assertTrue(hasattr(features, "AnyValue") and hasattr(features, "AnyConceptKey"))


    def test_a_unit_exports_its_runtime_ids(self):
        from features.demo import CONCEPT_A, KLUB, ENUMERATION_E, STRUCTURE_S
        self.assertEqual(CONCEPT_A, data.ConceptAKey.concept().runtime_id())
        self.assertEqual(KLUB, data.KlubKey.club().runtime_id())
        self.assertEqual(STRUCTURE_S, data.StructureS.type().runtime_id())
        self.assertEqual(features.definitions().check_enumeration(ENUMERATION_E).runtime_id(), ENUMERATION_E)


class TestMembership(unittest.TestCase):

    def test_a_key_is_found_through_another_view(self):
        key = data.ConceptCKey.create()
        keys = c.Set_of_AnyConceptKey([key.to_any_concept_key()])
        self.assertIn(key.to_any_concept_key(), keys)
        self.assertIn(key.to_parent_key().to_any_concept_key(), keys)
        self.assertNotIn(data.ConceptCKey.create().to_any_concept_key(), keys)

    def test_another_view_is_widened_explicitly(self):
        key = data.ConceptCKey.create()
        with self.assertRaises(dsviper.ViperError):
            key in c.Set_of_AnyConceptKey([key.to_any_concept_key()])
        with self.assertRaises(dsviper.ViperError):
            key in c.Set_of_Demo_ConceptBKey([key.to_parent_key()])

    def test_an_element_of_the_wrong_type_raises(self):
        for probe in (lambda: "x" in c.Set_of_uint8([1]),
                      lambda: 300 in c.Vector_of_uint8([1]),
                      lambda: 3 in c.Map_of_string_to_Demo_StructureS(),
                      lambda: c.Set_of_uint8([1]).contains("x")):  # type: ignore[arg-type]
            with self.assertRaises(dsviper.ViperError):
                probe()


if __name__ == "__main__":
    unittest.main()
