# Copyright (c) Digital Substrate 2026, All rights reserved.
"""A key gives back its instance's own key; a document is written as a field is; a club takes
its members' keys."""

import unittest
import dsviper
import features
from features import AnyValue, containers as c
from features.demo import data
from features.demo.attachments import ConceptA, ConceptCoverage


class TestSpecificKey(unittest.TestCase):

    def test_any_view_gives_back_the_instance_key(self):
        key = data.ConceptCKey.create()
        for view in (key.to_any_concept_key(), key.to_parent_key(), data.KlubKey(key)):
            specific = view.to_concept_key()
            self.assertIs(type(specific), data.ConceptCKey)
            self.assertEqual(specific, key)


class TestDocuments(unittest.TestCase):

    def setUp(self):
        self.db = dsviper.Database.create_in_memory()
        self.db.extend_definitions(features.definitions())

    def test_a_document_takes_what_its_field_would(self):
        key = data.ConceptAKey.create()
        self.db.begin_transaction()
        ConceptA.properties_se_int8.set(self.db, key, {1, 2})
        self.db.commit()
        self.assertEqual(set(ConceptA.properties_se_int8.get(self.db.attachment_getting(), key).unwrap()), {1, 2})

    def test_an_any_document_takes_any_value(self):
        key = data.ConceptCoverageKey.create()
        self.db.begin_transaction()
        ConceptCoverage.doc_any.set(self.db, key, data.StructureS(f_string="held"))
        self.db.commit()
        held = ConceptCoverage.doc_any.get(self.db.attachment_getting(), key).unwrap()
        self.assertIs(type(held.unwrap()), data.StructureS)

    def test_an_any_value_is_built_from_a_value(self):
        self.assertEqual(AnyValue(42).unwrap(), 42)
        self.assertTrue(AnyValue().is_nil())


class TestClubKey(unittest.TestCase):

    def test_a_club_takes_a_member_key_and_refuses_another(self):
        self.assertEqual(data.KlubKey(data.ConceptDKey.create()).to_concept_d_key() is not None, True)
        with self.assertRaises(TypeError):
            data.KlubKey(data.ConceptAKey.create())  # type: ignore[arg-type]


if __name__ == "__main__":
    unittest.main()
