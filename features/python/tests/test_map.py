# Copyright (c) Digital Substrate 2026, All rights reserved.
"""Tests for Kibo-generated Map proxy classes."""

import unittest
from features.data import (
    Map_int8_to_string, Map_string_to_Test_StructureS, Map_Test_StructureS_to_string,
    Test_StructureS
)


class TestMapConstruction(unittest.TestCase):
    """Test Map construction."""

    def test_empty_map(self):
        m = Map_int8_to_string()
        self.assertEqual(len(m), 0)

    def test_map_from_dict(self):
        m = Map_int8_to_string({1: "one", 2: "two"})
        self.assertEqual(len(m), 2)


class TestMapAccess(unittest.TestCase):
    """Test Map access operations."""

    def test_getitem(self):
        m = Map_int8_to_string({1: "one", 2: "two"})
        self.assertEqual(m[1], "one")
        self.assertEqual(m[2], "two")

    def test_setitem(self):
        m = Map_int8_to_string()
        m[1] = "one"
        self.assertEqual(m[1], "one")

    def test_contains(self):
        m = Map_int8_to_string({1: "one"})
        self.assertTrue(1 in m)
        self.assertFalse(99 in m)

    def test_get_present(self):
        m = Map_int8_to_string({1: "one"})
        self.assertEqual(m.get(1), "one")

    def test_get_absent_default(self):
        m = Map_int8_to_string({1: "one"})
        self.assertEqual(m.get(99, "default"), "default")


class TestMapMutations(unittest.TestCase):
    """Test Map mutation operations."""

    def test_delete(self):
        m = Map_int8_to_string({1: "one", 2: "two"})
        del m[1]
        self.assertEqual(len(m), 1)
        self.assertFalse(1 in m)

    def test_clear(self):
        m = Map_int8_to_string({1: "one", 2: "two"})
        m.clear()
        self.assertEqual(len(m), 0)

    def test_pop(self):
        m = Map_int8_to_string({1: "one", 2: "two"})
        val = m.pop(1)
        self.assertEqual(val, "one")
        self.assertEqual(len(m), 1)

    def test_pop_with_default(self):
        m = Map_int8_to_string({1: "one"})
        val = m.pop(99, "default")
        self.assertEqual(val, "default")
        self.assertEqual(len(m), 1)  # Map unchanged


class TestMapIteration(unittest.TestCase):
    """Test Map iteration methods."""

    def test_keys(self):
        m = Map_int8_to_string({1: "one", 2: "two"})
        keys = list(m.keys())
        self.assertEqual(sorted(keys), [1, 2])

    def test_values(self):
        m = Map_int8_to_string({1: "one", 2: "two"})
        values = list(m.values())
        self.assertEqual(sorted(values), ["one", "two"])

    def test_items(self):
        m = Map_int8_to_string({1: "one", 2: "two"})
        items = list(m.items())
        self.assertEqual(len(items), 2)


class TestMapIterDunder(unittest.TestCase):
    """Test Map __iter__ (iteration over keys directly)."""

    def test_iter(self):
        m = Map_int8_to_string({1: "one", 2: "two", 3: "three"})
        keys = list(m)
        self.assertEqual(sorted(keys), [1, 2, 3])

    def test_iter_empty(self):
        m = Map_int8_to_string()
        keys = list(m)
        self.assertEqual(keys, [])

    def test_iter_multiple_times(self):
        m = Map_int8_to_string({1: "a", 2: "b"})
        list1 = sorted(list(m))
        list2 = sorted(list(m))
        self.assertEqual(list1, list2)


class TestMapWithStructures(unittest.TestCase):
    """Test Map with structure keys or values."""

    def test_map_string_to_structure(self):
        # Map values need dicts or vpr_values, not proxy objects
        m = Map_string_to_Test_StructureS({"key": {"f_float": 1.5, "f_string": "test"}})
        retrieved = m["key"]
        self.assertAlmostEqual(retrieved.f_float, 1.5, places=5)

    def test_map_structure_to_string(self):
        s = Test_StructureS({"f_float": 1.5, "f_string": "test"})
        m = Map_Test_StructureS_to_string()
        m[s] = "value"
        self.assertEqual(m[s], "value")


class TestMapCopy(unittest.TestCase):
    """Test Map copy behavior."""

    def test_copy_creates_independent_map(self):
        m1 = Map_int8_to_string({1: "one", 2: "two"})
        m2 = m1.copy()
        self.assertEqual(len(m1), len(m2))
        m2[3] = "three"
        self.assertEqual(len(m1), 2)
        self.assertEqual(len(m2), 3)

    def test_copy_preserves_entries(self):
        m1 = Map_int8_to_string({1: "one", 2: "two"})
        m2 = m1.copy()
        self.assertEqual(m2[1], "one")
        self.assertEqual(m2[2], "two")


class TestMapAdvancedOperations(unittest.TestCase):
    """Test Map advanced operations."""

    def test_popitem(self):
        m = Map_int8_to_string({1: "one", 2: "two"})
        key, value = m.popitem()
        self.assertEqual(len(m), 1)
        self.assertIn(key, [1, 2])
        self.assertIn(value, ["one", "two"])

    def test_setdefault_new_key(self):
        m = Map_int8_to_string({1: "one"})
        m.setdefault(2, "two")
        self.assertEqual(m[2], "two")

    def test_setdefault_existing_key(self):
        m = Map_int8_to_string({1: "one"})
        m.setdefault(1, "ONE")
        self.assertEqual(m[1], "one")  # Original value preserved

    def test_update(self):
        m1 = Map_int8_to_string({1: "one"})
        m2 = Map_int8_to_string({2: "two", 3: "three"})
        m1.update(m2)
        self.assertEqual(len(m1), 3)
        self.assertEqual(m1[2], "two")
        self.assertEqual(m1[3], "three")

    def test_update_overwrites_existing(self):
        m1 = Map_int8_to_string({1: "one", 2: "two"})
        m2 = Map_int8_to_string({2: "TWO"})
        m1.update(m2)
        self.assertEqual(m1[2], "TWO")


class TestMapSerialization(unittest.TestCase):
    """Test Map encode/decode serialization."""

    def test_encode_decode_roundtrip(self):
        m1 = Map_int8_to_string({1: "one", 2: "two"})
        blob = m1.encode()
        m2 = Map_int8_to_string.decode(blob)
        self.assertEqual(len(m2), 2)
        self.assertEqual(m2[1], "one")
        self.assertEqual(m2[2], "two")

    def test_encode_decode_empty(self):
        m1 = Map_int8_to_string()
        blob = m1.encode()
        m2 = Map_int8_to_string.decode(blob)
        self.assertEqual(len(m2), 0)


if __name__ == "__main__":
    unittest.main()
