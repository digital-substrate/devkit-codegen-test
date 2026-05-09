# Copyright (c) Digital Substrate 2026, All rights reserved.
"""Tests for Kibo-generated database attachment operations."""

import unittest
import dsviper
from features import definitions as md
from features import database_attachments as db
from features.data import (
    Test_ConceptAKey, Test_ConceptBKey, Test_ConceptCKey,
    Test_StructureV, Test_StructureT, Test_StructureU,
    Set_int8, Map_int8_to_string, XArray_int8
)


def create_database() -> dsviper.Database:
    """Create an in-memory database with Exp definitions."""
    database = dsviper.Database.create_in_memory()
    database.extend_definitions(md.definitions())
    return database


class TestAttachmentKeys(unittest.TestCase):
    """Test attachment keys() function."""

    def setUp(self):
        self.database = create_database()

    def test_keys_empty_initially(self):
        keys = db.test_concept_a_properties_keys(self.database)
        self.assertEqual(len(keys), 0)

    def test_keys_after_set(self):
        key = Test_ConceptAKey.create()
        value = Test_StructureV()

        self.database.begin_transaction()
        db.test_concept_a_properties_set(self.database, key, value)
        self.database.commit()

        keys = db.test_concept_a_properties_keys(self.database)
        self.assertEqual(len(keys), 1)
        self.assertIn(key, keys)


class TestAttachmentHas(unittest.TestCase):
    """Test attachment has() function."""

    def setUp(self):
        self.database = create_database()

    def test_has_absent(self):
        key = Test_ConceptAKey.create()
        self.assertFalse(db.test_concept_a_properties_has(self.database, key))

    def test_has_present(self):
        key = Test_ConceptAKey.create()
        value = Test_StructureV()

        self.database.begin_transaction()
        db.test_concept_a_properties_set(self.database, key, value)
        self.database.commit()

        self.assertTrue(db.test_concept_a_properties_has(self.database, key))


class TestAttachmentGetSet(unittest.TestCase):
    """Test attachment get() and set() functions."""

    def setUp(self):
        self.database = create_database()

    def test_get_absent_returns_nil(self):
        key = Test_ConceptAKey.create()
        result = db.test_concept_a_properties_get(self.database, key)
        self.assertTrue(result.is_nil())

    def test_set_then_get(self):
        key = Test_ConceptAKey.create()
        value = Test_StructureV()
        value.f_bool = True
        value.f_string = "test value"

        self.database.begin_transaction()
        db.test_concept_a_properties_set(self.database, key, value)
        self.database.commit()

        result = db.test_concept_a_properties_get(self.database, key)

        self.assertFalse(result.is_nil())
        retrieved = result.unwrap()
        self.assertTrue(retrieved.f_bool)
        self.assertEqual(retrieved.f_string, "test value")

    def test_overwrite_value(self):
        key = Test_ConceptAKey.create()

        value1 = Test_StructureV()
        value1.f_string = "first"
        self.database.begin_transaction()
        db.test_concept_a_properties_set(self.database, key, value1)
        self.database.commit()

        value2 = Test_StructureV()
        value2.f_string = "second"
        self.database.begin_transaction()
        db.test_concept_a_properties_set(self.database, key, value2)
        self.database.commit()

        result = db.test_concept_a_properties_get(self.database, key)
        self.assertEqual(result.unwrap().f_string, "second")


class TestAttachmentDelete(unittest.TestCase):
    """Test attachment del() function."""

    def setUp(self):
        self.database = create_database()

    def test_delete_removes_entry(self):
        key = Test_ConceptAKey.create()
        value = Test_StructureV()

        self.database.begin_transaction()
        db.test_concept_a_properties_set(self.database, key, value)
        self.database.commit()

        self.assertTrue(db.test_concept_a_properties_has(self.database, key))

        self.database.begin_transaction()
        db.test_concept_a_properties_del(self.database, key)
        self.database.commit()

        self.assertFalse(db.test_concept_a_properties_has(self.database, key))

    def test_delete_absent_no_error(self):
        key = Test_ConceptAKey.create()
        # Should not raise
        self.database.begin_transaction()
        db.test_concept_a_properties_del(self.database, key)
        self.database.commit()


class TestAttachmentEnumerate(unittest.TestCase):
    """Test attachment enumerate() function."""

    def setUp(self):
        self.database = create_database()

    def test_enumerate_empty(self):
        items = list(db.test_concept_a_properties_enumerate(self.database))
        self.assertEqual(len(items), 0)

    def test_enumerate_entries(self):
        key1 = Test_ConceptAKey.create()
        key2 = Test_ConceptAKey.create()

        value1 = Test_StructureV()
        value1.f_string = "value1"
        value2 = Test_StructureV()
        value2.f_string = "value2"

        self.database.begin_transaction()
        db.test_concept_a_properties_set(self.database, key1, value1)
        db.test_concept_a_properties_set(self.database, key2, value2)
        self.database.commit()

        items = list(db.test_concept_a_properties_enumerate(self.database))
        self.assertEqual(len(items), 2)

        keys = [k for k, v in items]
        self.assertIn(key1, keys)
        self.assertIn(key2, keys)


class TestAttachmentInt8(unittest.TestCase):
    """Test attachment with int8 value type."""

    def setUp(self):
        self.database = create_database()

    def test_set_get_int8(self):
        key = Test_ConceptAKey.create()

        self.database.begin_transaction()
        db.test_concept_a_properties_int_8_set(self.database, key, 42)
        self.database.commit()

        result = db.test_concept_a_properties_int_8_get(self.database, key)
        self.assertFalse(result.is_nil())
        self.assertEqual(result.unwrap(), 42)

    def test_negative_int8(self):
        key = Test_ConceptAKey.create()

        self.database.begin_transaction()
        db.test_concept_a_properties_int_8_set(self.database, key, -100)
        self.database.commit()

        result = db.test_concept_a_properties_int_8_get(self.database, key)
        self.assertEqual(result.unwrap(), -100)


class TestAttachmentSetInt8(unittest.TestCase):
    """Test attachment with set<int8> value type."""

    def setUp(self):
        self.database = create_database()

    def test_set_get_set_int8(self):
        key = Test_ConceptAKey.create()
        value = Set_int8([1, 2, 3])

        self.database.begin_transaction()
        db.test_concept_a_properties_se_int_8_set(self.database, key, value)
        self.database.commit()

        result = db.test_concept_a_properties_se_int_8_get(self.database, key)
        self.assertFalse(result.is_nil())
        retrieved = result.unwrap()
        self.assertEqual(len(retrieved), 3)


class TestAttachmentMapInt8String(unittest.TestCase):
    """Test attachment with map<int8, string> value type."""

    def setUp(self):
        self.database = create_database()

    def test_set_get_map(self):
        key = Test_ConceptAKey.create()
        value = Map_int8_to_string({1: "one", 2: "two"})

        self.database.begin_transaction()
        db.test_concept_a_properties_map_int_8_string_set(self.database, key, value)
        self.database.commit()

        result = db.test_concept_a_properties_map_int_8_string_get(self.database, key)
        self.assertFalse(result.is_nil())
        retrieved = result.unwrap()
        self.assertEqual(retrieved[1], "one")
        self.assertEqual(retrieved[2], "two")


class TestAttachmentXArray(unittest.TestCase):
    """Test attachment with xarray<int8> value type."""

    def setUp(self):
        self.database = create_database()

    def test_set_get_xarray(self):
        key = Test_ConceptAKey.create()
        value = XArray_int8([10, 20, 30, 40])

        self.database.begin_transaction()
        db.test_concept_a_properties_x_array_set(self.database, key, value)
        self.database.commit()

        result = db.test_concept_a_properties_x_array_get(self.database, key)
        self.assertFalse(result.is_nil())
        retrieved = result.unwrap()
        self.assertEqual(len(retrieved), 4)


class TestAttachmentConceptB(unittest.TestCase):
    """Test attachment<ConceptB, StructureT>."""

    def setUp(self):
        self.database = create_database()

    def test_concept_b_attachment(self):
        key = Test_ConceptBKey.create()
        value = Test_StructureT()
        value.field_string = "concept B value"

        self.database.begin_transaction()
        db.test_concept_b_properties_b_set(self.database, key, value)
        self.database.commit()

        result = db.test_concept_b_properties_b_get(self.database, key)

        self.assertFalse(result.is_nil())
        self.assertEqual(result.unwrap().field_string, "concept B value")


class TestAttachmentConceptC(unittest.TestCase):
    """Test attachment<ConceptC, StructureU>."""

    def setUp(self):
        self.database = create_database()

    def test_concept_c_attachment(self):
        key = Test_ConceptCKey.create()
        value = Test_StructureU()
        value.f_uint_8 = 255
        value.f_string = "concept C value"

        self.database.begin_transaction()
        db.test_concept_c_properties_c_set(self.database, key, value)
        self.database.commit()

        result = db.test_concept_c_properties_c_get(self.database, key)

        self.assertFalse(result.is_nil())
        retrieved = result.unwrap()
        self.assertEqual(retrieved.f_uint_8, 255)
        self.assertEqual(retrieved.f_string, "concept C value")


class TestMultipleAttachments(unittest.TestCase):
    """Test multiple attachments for the same concept."""

    def setUp(self):
        self.database = create_database()

    def test_multiple_attachments_independent(self):
        key = Test_ConceptAKey.create()

        # Set properties attachment
        props = Test_StructureV()
        props.f_string = "properties"
        self.database.begin_transaction()
        db.test_concept_a_properties_set(self.database, key, props)
        self.database.commit()

        # Set propertiesInt8 attachment
        self.database.begin_transaction()
        db.test_concept_a_properties_int_8_set(self.database, key, 42)
        self.database.commit()

        # Verify both exist independently
        self.assertTrue(db.test_concept_a_properties_has(self.database, key))
        self.assertTrue(db.test_concept_a_properties_int_8_has(self.database, key))

        # Delete one, other should remain
        self.database.begin_transaction()
        db.test_concept_a_properties_del(self.database, key)
        self.database.commit()

        self.assertFalse(db.test_concept_a_properties_has(self.database, key))
        self.assertTrue(db.test_concept_a_properties_int_8_has(self.database, key))


if __name__ == "__main__":
    unittest.main()
