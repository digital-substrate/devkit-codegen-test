# Copyright (c) Digital Substrate 2026, All rights reserved.
"""One instance, many views: a key's conversions keep its instance.

A key is a static type (a concept, a club, any_concept), the concept of its instance and an
instance id. The conversions change only the static type; equality and hash look only at the
instance. These are the patterns a projection leans on: parent chains, a key map across views,
narrowing back from any_concept.
"""

import unittest
import dsviper
from features import AnyConceptKey, definitions
from features.demo import data
from features.demo.attachments import ConceptB


class TestKeyViews(unittest.TestCase):

    def setUp(self):
        self.c = data.ConceptCKey.create()
        self.b = self.c.to_parent_key()
        self.a = self.c.to_any_concept_key()

    def test_parent_key_has_the_parent_static_type(self):
        self.assertIs(type(self.b), data.ConceptBKey)
        self.assertEqual(self.b.vpr_value.type_key(), data.ConceptBKey.type())

    def test_parent_key_is_accepted_by_a_parent_slot(self):
        u = data.StructureU(f_b=self.b)
        self.assertEqual(u.f_b, self.b)
        self.assertIs(type(u.f_b), data.ConceptBKey)

    def test_views_of_one_instance_are_equal_and_hash_alike(self):
        self.assertTrue(self.b == self.c == self.a)
        self.assertEqual(len({self.b, self.c, self.a}), 1)

    def test_from_any_concept_key_accepts_a_descendant(self):
        self.assertEqual(data.ConceptBKey.from_any_concept_key(self.a), self.b)
        self.assertIsNone(data.ConceptDKey.from_any_concept_key(self.a))

    def test_from_key_raises_for_an_unrelated_instance(self):
        with self.assertRaises(TypeError):
            data.ConceptDKey.from_key(self.a)

    def test_narrowing_and_widening_by_name(self):
        self.assertIs(type(self.b.to_concept_c_key()), data.ConceptCKey)
        self.assertEqual(self.b.to_concept_c_key(), self.c)
        self.assertIsNone(data.ConceptBKey.create().to_concept_c_key())
        self.assertEqual(data.ConceptBKey.from_concept_c_key(self.c), self.b)

    def test_as(self):
        self.assertEqual(self.b.as_(data.ConceptCKey), self.c)
        self.assertEqual(self.a.as_(data.ConceptBKey), self.b)

    def test_club(self):
        k = data.KlubKey.from_concept_c_key(self.c)
        self.assertEqual(k.to_concept_c_key(), self.c)
        self.assertIsNone(k.to_concept_d_key())
        self.assertEqual(data.KlubKey.from_any_concept_key(self.a), k)
        self.assertIsNone(data.KlubKey.from_any_concept_key(data.ConceptAKey.create().to_any_concept_key()))

    def test_a_field_reads_the_class_of_its_static_type(self):
        u = data.StructureU(f_klub=data.KlubKey(self.c), f_any_concept=self.a, f_c=self.c)
        self.assertIs(type(u.f_klub), data.KlubKey)
        self.assertIs(type(u.f_any_concept), AnyConceptKey)

    def test_the_constructor_takes_exactly_its_static_type(self):
        with self.assertRaises(TypeError):
            data.ConceptBKey(self.c.vpr_value)

    def test_any_concept_key_from_a_key(self):
        self.assertEqual(AnyConceptKey(self.c), self.a)
        self.assertEqual(AnyConceptKey(self.c.to_any_concept_key()), self.a)

    def test_a_description_names_the_instance_concept_when_the_view_differs(self):
        name = self.c.instance_id().encoded()
        self.assertEqual(str(self.c), f"{name}:Demo::ConceptCKey")
        self.assertEqual(str(self.b), f"{name}:Demo::ConceptBKey(Demo::ConceptCKey)")
        self.assertEqual(str(data.KlubKey(self.c)), f"{name}:Demo::KlubKey(Demo::ConceptCKey)")

    def test_a_descendant_filed_under_its_parent(self):
        cdb = dsviper.CommitDatabase.create_in_memory()
        cdb.extend_definitions(definitions())
        mutable = dsviper.CommitMutableState(dsviper.CommitStateBuilder.initial_state(cdb))
        ConceptB.properties_b.set(mutable.attachment_mutating(), self.b, data.StructureT())
        state = dsviper.CommitStateBuilder.state(cdb, cdb.commit_mutations("b", mutable))
        keys = list(ConceptB.properties_b.keys(state.attachment_getting()))
        self.assertEqual(keys, [self.b])
        self.assertIs(type(keys[0]), data.ConceptBKey)
        self.assertEqual(keys[0].to_concept_c_key(), self.c)


if __name__ == "__main__":
    unittest.main()
