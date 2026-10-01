# Copyright (c) Digital Substrate 2026, All rights reserved.
"""Tests for Kibo-generated database attachment operations."""

import unittest
import dsviper
from features import definitions
from features.demo import data as md
from features.demo import attachments as db
from features.demo import ConceptAKey, ConceptBKey, ConceptCKey, StructureV, StructureT, StructureU
from features.containers import Set_of_int8, Map_of_int8_to_string, XArray_of_int8


def create_database() -> dsviper.Database:
    """Create an in-memory database with Exp definitions."""
    database = dsviper.Database.create_in_memory()
    database.extend_definitions(definitions())
    return database


class TestAttachmentKeys(unittest.TestCase):
    """Test attachment keys() function."""

    def setUp(self):
        self.database = create_database()

    def test_keys_empty_initially(self):
        keys = db.ConceptA.properties.keys(self.database)
        self.assertEqual(len(keys), 0)

    def test_keys_after_set(self):
        key = ConceptAKey.create()
        value = StructureV()

        self.database.begin_transaction()
        db.ConceptA.properties.set(self.database, key, value)
        self.database.commit()

        keys = db.ConceptA.properties.keys(self.database)
        self.assertEqual(len(keys), 1)
        self.assertIn(key, keys)


class TestAttachmentHas(unittest.TestCase):
    """Test attachment has() function."""

    def setUp(self):
        self.database = create_database()

    def test_has_absent(self):
        key = ConceptAKey.create()
        self.assertFalse(db.ConceptA.properties.has(self.database, key))

    def test_has_present(self):
        key = ConceptAKey.create()
        value = StructureV()

        self.database.begin_transaction()
        db.ConceptA.properties.set(self.database, key, value)
        self.database.commit()

        self.assertTrue(db.ConceptA.properties.has(self.database, key))


class TestAttachmentGetSet(unittest.TestCase):
    """Test attachment get() and set() functions."""

    def setUp(self):
        self.database = create_database()

    def test_get_absent_returns_nil(self):
        key = ConceptAKey.create()
        result = db.ConceptA.properties.get(self.database, key)
        self.assertTrue(result.is_nil())
        self.assertFalse(result)

    def test_set_then_get(self):
        key = ConceptAKey.create()
        value = StructureV()
        value.f_bool = True
        value.f_string = "test value"

        self.database.begin_transaction()
        db.ConceptA.properties.set(self.database, key, value)
        self.database.commit()

        result = db.ConceptA.properties.get(self.database, key).unwrap()

        self.assertIsNotNone(result)
        retrieved = result
        self.assertTrue(retrieved.f_bool)
        self.assertEqual(retrieved.f_string, "test value")

    def test_overwrite_value(self):
        key = ConceptAKey.create()

        value1 = StructureV()
        value1.f_string = "first"
        self.database.begin_transaction()
        db.ConceptA.properties.set(self.database, key, value1)
        self.database.commit()

        value2 = StructureV()
        value2.f_string = "second"
        self.database.begin_transaction()
        db.ConceptA.properties.set(self.database, key, value2)
        self.database.commit()

        result = db.ConceptA.properties.get(self.database, key).unwrap()
        self.assertEqual(result.f_string, "second")


class TestAttachmentDelete(unittest.TestCase):
    """Test attachment del() function."""

    def setUp(self):
        self.database = create_database()

    def test_delete_removes_entry(self):
        key = ConceptAKey.create()
        value = StructureV()

        self.database.begin_transaction()
        db.ConceptA.properties.set(self.database, key, value)
        self.database.commit()

        self.assertTrue(db.ConceptA.properties.has(self.database, key))

        self.database.begin_transaction()
        db.ConceptA.properties.delete(self.database, key)
        self.database.commit()

        self.assertFalse(db.ConceptA.properties.has(self.database, key))

    def test_delete_absent_no_error(self):
        key = ConceptAKey.create()
        # Should not raise
        self.database.begin_transaction()
        db.ConceptA.properties.delete(self.database, key)
        self.database.commit()


class TestAttachmentEnumerate(unittest.TestCase):
    """Test attachment enumerate() function."""

    def setUp(self):
        self.database = create_database()

    def test_enumerate_empty(self):
        items = list(db.ConceptA.properties.enumerate(self.database))
        self.assertEqual(len(items), 0)

    def test_enumerate_entries(self):
        key1 = ConceptAKey.create()
        key2 = ConceptAKey.create()

        value1 = StructureV()
        value1.f_string = "value1"
        value2 = StructureV()
        value2.f_string = "value2"

        self.database.begin_transaction()
        db.ConceptA.properties.set(self.database, key1, value1)
        db.ConceptA.properties.set(self.database, key2, value2)
        self.database.commit()

        items = list(db.ConceptA.properties.enumerate(self.database))
        self.assertEqual(len(items), 2)

        keys = [k for k, v in items]
        self.assertIn(key1, keys)
        self.assertIn(key2, keys)


class TestAttachmentInt8(unittest.TestCase):
    """Test attachment with int8 value type."""

    def setUp(self):
        self.database = create_database()

    def test_set_get_int8(self):
        key = ConceptAKey.create()

        self.database.begin_transaction()
        db.ConceptA.properties_int_8.set(self.database, key, 42)
        self.database.commit()

        result = db.ConceptA.properties_int_8.get(self.database, key).unwrap()
        self.assertIsNotNone(result)
        self.assertEqual(result, 42)

    def test_negative_int8(self):
        key = ConceptAKey.create()

        self.database.begin_transaction()
        db.ConceptA.properties_int_8.set(self.database, key, -100)
        self.database.commit()

        result = db.ConceptA.properties_int_8.get(self.database, key).unwrap()
        self.assertEqual(result, -100)


class TestAttachmentSetInt8(unittest.TestCase):
    """Test attachment with set<int8> value type."""

    def setUp(self):
        self.database = create_database()

    def test_set_get_set_int8(self):
        key = ConceptAKey.create()
        value = Set_of_int8([1, 2, 3])

        self.database.begin_transaction()
        db.ConceptA.properties_se_int_8.set(self.database, key, value)
        self.database.commit()

        result = db.ConceptA.properties_se_int_8.get(self.database, key).unwrap()
        self.assertIsNotNone(result)
        retrieved = result
        self.assertEqual(len(retrieved), 3)

    def test_an_empty_document_is_present(self):
        key = ConceptAKey.create()

        self.database.begin_transaction()
        db.ConceptA.properties_se_int_8.set(self.database, key, Set_of_int8())
        self.database.commit()

        result = db.ConceptA.properties_se_int_8.get(self.database, key)
        self.assertTrue(result)
        self.assertEqual(len(result.unwrap()), 0)


class TestAttachmentMapInt8String(unittest.TestCase):
    """Test attachment with map<int8, string> value type."""

    def setUp(self):
        self.database = create_database()

    def test_set_get_map(self):
        key = ConceptAKey.create()
        value = Map_of_int8_to_string({1: "one", 2: "two"})

        self.database.begin_transaction()
        db.ConceptA.properties_map_int_8_string.set(self.database, key, value)
        self.database.commit()

        result = db.ConceptA.properties_map_int_8_string.get(self.database, key).unwrap()
        self.assertIsNotNone(result)
        retrieved = result
        self.assertEqual(retrieved[1], "one")
        self.assertEqual(retrieved[2], "two")


class TestAttachmentXArray(unittest.TestCase):
    """Test attachment with xarray<int8> value type."""

    def setUp(self):
        self.database = create_database()

    def test_set_get_xarray(self):
        key = ConceptAKey.create()
        value = XArray_of_int8([10, 20, 30, 40])

        self.database.begin_transaction()
        db.ConceptA.properties_x_array.set(self.database, key, value)
        self.database.commit()

        result = db.ConceptA.properties_x_array.get(self.database, key).unwrap()
        self.assertIsNotNone(result)
        retrieved = result
        self.assertEqual(len(retrieved), 4)


class TestAttachmentConceptB(unittest.TestCase):
    """Test attachment<ConceptB, StructureT>."""

    def setUp(self):
        self.database = create_database()

    def test_concept_b_attachment(self):
        key = ConceptBKey.create()
        value = StructureT()
        value.field_string = "concept B value"

        self.database.begin_transaction()
        db.ConceptB.properties_b.set(self.database, key, value)
        self.database.commit()

        result = db.ConceptB.properties_b.get(self.database, key).unwrap()

        self.assertIsNotNone(result)
        self.assertEqual(result.field_string, "concept B value")


class TestAttachmentConceptC(unittest.TestCase):
    """Test attachment<ConceptC, StructureU>."""

    def setUp(self):
        self.database = create_database()

    def test_concept_c_attachment(self):
        key = ConceptCKey.create()
        value = StructureU()
        value.f_uint8 = 255
        value.f_string = "concept C value"

        self.database.begin_transaction()
        db.ConceptC.properties_c.set(self.database, key, value)
        self.database.commit()

        result = db.ConceptC.properties_c.get(self.database, key).unwrap()

        self.assertIsNotNone(result)
        retrieved = result
        self.assertEqual(retrieved.f_uint8, 255)
        self.assertEqual(retrieved.f_string, "concept C value")


class TestMultipleAttachments(unittest.TestCase):
    """Test multiple attachments for the same concept."""

    def setUp(self):
        self.database = create_database()

    def test_multiple_attachments_independent(self):
        key = ConceptAKey.create()

        # Set properties attachment
        props = StructureV()
        props.f_string = "properties"
        self.database.begin_transaction()
        db.ConceptA.properties.set(self.database, key, props)
        self.database.commit()

        # Set propertiesInt8 attachment
        self.database.begin_transaction()
        db.ConceptA.properties_int_8.set(self.database, key, 42)
        self.database.commit()

        # Verify both exist independently
        self.assertTrue(db.ConceptA.properties.has(self.database, key))
        self.assertTrue(db.ConceptA.properties_int_8.has(self.database, key))

        # Delete one, other should remain
        self.database.begin_transaction()
        db.ConceptA.properties.delete(self.database, key)
        self.database.commit()

        self.assertFalse(db.ConceptA.properties.has(self.database, key))
        self.assertTrue(db.ConceptA.properties_int_8.has(self.database, key))


if __name__ == "__main__":
    unittest.main()
