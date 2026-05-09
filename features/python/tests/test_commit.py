# Copyright (c) Digital Substrate 2026, All rights reserved.
"""Tests for Kibo-generated commit/transaction operations."""

import unittest
import dsviper
from features import definitions as md
from features import attachments as ma
from features.data import Test_ConceptAKey, Test_StructureV


def create_commit_state() -> dsviper.CommitState:
    """Create a CommitState with Exp definitions."""
    return dsviper.CommitState(md.definitions())


class TestAttachmentGettingKeys(unittest.TestCase):
    """Test attachment getting keys() function."""

    def setUp(self):
        self.state = create_commit_state()

    def test_keys_empty_initially(self):
        getting = self.state.attachment_getting()
        keys = ma.test_concept_a_properties_keys(getting)
        self.assertEqual(len(keys), 0)


class TestAttachmentMutatingSetGet(unittest.TestCase):
    """Test attachment mutating set and getting."""

    def setUp(self):
        self.state = create_commit_state()

    def test_set_then_get(self):
        key = Test_ConceptAKey.create()
        value = Test_StructureV()
        value.f_string = "test"
        value.f_bool = True

        # Mutate
        mutable = dsviper.CommitMutableState(self.state)
        mutating = mutable.attachment_mutating()
        ma.test_concept_a_properties_set(mutating, key, value)

        # Read back from mutable state (sees uncommitted changes)
        getting = mutable.attachment_getting()
        result = ma.test_concept_a_properties_get(getting, key)
        self.assertFalse(result.is_nil())
        retrieved = result.unwrap()
        self.assertEqual(retrieved.f_string, "test")
        self.assertTrue(retrieved.f_bool)

    def test_uncommitted_changes_visible_in_mutable_state(self):
        key = Test_ConceptAKey.create()
        value = Test_StructureV()
        value.f_string = "uncommitted"

        mutable = dsviper.CommitMutableState(self.state)
        mutating = mutable.attachment_mutating()
        ma.test_concept_a_properties_set(mutating, key, value)

        # Read within same mutable state (should see uncommitted changes)
        getting = mutable.attachment_getting()
        result = ma.test_concept_a_properties_get(getting, key)
        self.assertFalse(result.is_nil())
        self.assertEqual(result.unwrap().f_string, "uncommitted")


class TestCommitFieldUpdate(unittest.TestCase):
    """Test commit field-level update operations."""

    def setUp(self):
        self.state = create_commit_state()

    def test_set_f_bool(self):
        key = Test_ConceptAKey.create()
        value = Test_StructureV()
        value.f_bool = False

        mutable = dsviper.CommitMutableState(self.state)
        mutating = mutable.attachment_mutating()
        ma.test_concept_a_properties_set(mutating, key, value)

        # Update single field
        ma.test_concept_a_properties_set_f_bool(mutating, key, True)

        getting = mutable.attachment_getting()
        result = ma.test_concept_a_properties_get(getting, key)
        self.assertTrue(result.unwrap().f_bool)

    def test_set_f_uint8(self):
        key = Test_ConceptAKey.create()
        value = Test_StructureV()

        mutable = dsviper.CommitMutableState(self.state)
        mutating = mutable.attachment_mutating()
        ma.test_concept_a_properties_set(mutating, key, value)

        ma.test_concept_a_properties_set_f_uint_8(mutating, key, 255)

        getting = mutable.attachment_getting()
        result = ma.test_concept_a_properties_get(getting, key)
        self.assertEqual(result.unwrap().f_uint_8, 255)

    def test_set_f_string(self):
        key = Test_ConceptAKey.create()
        value = Test_StructureV()
        value.f_string = "original"

        mutable = dsviper.CommitMutableState(self.state)
        mutating = mutable.attachment_mutating()
        ma.test_concept_a_properties_set(mutating, key, value)

        ma.test_concept_a_properties_set_f_string(mutating, key, "modified")

        getting = mutable.attachment_getting()
        result = ma.test_concept_a_properties_get(getting, key)
        self.assertEqual(result.unwrap().f_string, "modified")


class TestCommitDiffKeys(unittest.TestCase):
    """Test commit diff_keys operation."""

    def setUp(self):
        self.state = create_commit_state()

    def test_diff_keys_added(self):
        """Test diff_keys detects added keys."""
        key = Test_ConceptAKey.create()
        value = Test_StructureV()
        value.f_string = "test"

        # État "before" : vide
        mutable_before = dsviper.CommitMutableState(self.state)
        before = mutable_before.attachment_getting()

        # État "after" : avec une entrée ajoutée
        mutable_after = dsviper.CommitMutableState(self.state)
        ma.test_concept_a_properties_set(mutable_after.attachment_mutating(), key, value)
        after = mutable_after.attachment_getting()

        # diff_keys(current, other): added = keys in other but not current
        added, removed, different, same = ma.test_concept_a_properties_diff_keys(before, after)
        self.assertEqual(len(added), 1)
        self.assertIn(key, added)
        self.assertEqual(len(removed), 0)
        self.assertEqual(len(different), 0)
        self.assertEqual(len(same), 0)

    def test_diff_keys_removed(self):
        """Test diff_keys detects removed keys."""
        key = Test_ConceptAKey.create()
        value = Test_StructureV()
        value.f_string = "test"

        # État "before" : avec entrée
        mutable_before = dsviper.CommitMutableState(self.state)
        ma.test_concept_a_properties_set(mutable_before.attachment_mutating(), key, value)
        before = mutable_before.attachment_getting()

        # État "after" : vide
        mutable_after = dsviper.CommitMutableState(self.state)
        after = mutable_after.attachment_getting()

        # diff_keys(current, other): removed = keys in current but not other
        added, removed, different, same = ma.test_concept_a_properties_diff_keys(before, after)
        self.assertEqual(len(added), 0)
        self.assertEqual(len(removed), 1)
        self.assertIn(key, removed)
        self.assertEqual(len(different), 0)
        self.assertEqual(len(same), 0)

    def test_diff_keys_different(self):
        """Test diff_keys detects keys with different values."""
        key = Test_ConceptAKey.create()

        # État "before" : key -> "first"
        mutable_before = dsviper.CommitMutableState(self.state)
        value1 = Test_StructureV()
        value1.f_string = "first"
        ma.test_concept_a_properties_set(mutable_before.attachment_mutating(), key, value1)
        before = mutable_before.attachment_getting()

        # État "after" : key -> "second"
        mutable_after = dsviper.CommitMutableState(self.state)
        value2 = Test_StructureV()
        value2.f_string = "second"
        ma.test_concept_a_properties_set(mutable_after.attachment_mutating(), key, value2)
        after = mutable_after.attachment_getting()

        # diff_keys(current, other): different = keys in both with different values
        added, removed, different, same = ma.test_concept_a_properties_diff_keys(before, after)
        self.assertEqual(len(added), 0)
        self.assertEqual(len(removed), 0)
        self.assertEqual(len(different), 1)
        self.assertIn(key, different)
        self.assertEqual(len(same), 0)

    def test_diff_keys_same(self):
        """Test diff_keys detects keys with identical values."""
        key = Test_ConceptAKey.create()
        value = Test_StructureV()
        value.f_string = "unchanged"

        # État "before" : key -> value
        mutable_before = dsviper.CommitMutableState(self.state)
        ma.test_concept_a_properties_set(mutable_before.attachment_mutating(), key, value)
        before = mutable_before.attachment_getting()

        # État "after" : key -> même value
        mutable_after = dsviper.CommitMutableState(self.state)
        ma.test_concept_a_properties_set(mutable_after.attachment_mutating(), key, value)
        after = mutable_after.attachment_getting()

        # diff_keys(current, other): same = keys in both with identical values
        added, removed, different, same = ma.test_concept_a_properties_diff_keys(before, after)
        self.assertEqual(len(added), 0)
        self.assertEqual(len(removed), 0)
        self.assertEqual(len(different), 0)
        self.assertEqual(len(same), 1)
        self.assertIn(key, same)


class TestCommitEnumerate(unittest.TestCase):
    """Test commit enumerate operation."""

    def setUp(self):
        self.state = create_commit_state()

    def test_enumerate_entries(self):
        key1 = Test_ConceptAKey.create()
        key2 = Test_ConceptAKey.create()

        value1 = Test_StructureV()
        value1.f_string = "one"
        value2 = Test_StructureV()
        value2.f_string = "two"

        mutable = dsviper.CommitMutableState(self.state)
        mutating = mutable.attachment_mutating()
        ma.test_concept_a_properties_set(mutating, key1, value1)
        ma.test_concept_a_properties_set(mutating, key2, value2)

        getting = mutable.attachment_getting()
        items = list(ma.test_concept_a_properties_enumerate(getting))
        self.assertEqual(len(items), 2)

        keys = [k for k, v in items]
        self.assertIn(key1, keys)
        self.assertIn(key2, keys)


class TestCommitHas(unittest.TestCase):
    """Test commit has() function."""

    def setUp(self):
        self.state = create_commit_state()

    def test_has_absent(self):
        key = Test_ConceptAKey.create()
        getting = self.state.attachment_getting()
        self.assertFalse(ma.test_concept_a_properties_has(getting, key))

    def test_has_present(self):
        key = Test_ConceptAKey.create()
        value = Test_StructureV()

        mutable = dsviper.CommitMutableState(self.state)
        mutating = mutable.attachment_mutating()
        ma.test_concept_a_properties_set(mutating, key, value)

        getting = mutable.attachment_getting()
        self.assertTrue(ma.test_concept_a_properties_has(getting, key))


class TestCommitDiff(unittest.TestCase):
    """Test commit diff() collaborative merge operation."""

    def setUp(self):
        self.state = create_commit_state()

    def test_diff_updates_existing(self):
        key = Test_ConceptAKey.create()

        value1 = Test_StructureV()
        value1.f_string = "original"
        value1.f_uint_8 = 10

        mutable = dsviper.CommitMutableState(self.state)
        mutating = mutable.attachment_mutating()
        ma.test_concept_a_properties_set(mutating, key, value1)

        # Use diff to update only changed fields
        value2 = Test_StructureV()
        value2.f_string = "modified"
        value2.f_uint_8 = 10  # Same value

        ma.test_concept_a_properties_diff(mutating, key, value2)

        getting = mutable.attachment_getting()
        result = ma.test_concept_a_properties_get(getting, key)
        self.assertEqual(result.unwrap().f_string, "modified")


if __name__ == "__main__":
    unittest.main()
