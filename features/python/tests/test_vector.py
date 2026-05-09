# Copyright (c) Digital Substrate 2026, All rights reserved.
"""Tests for Kibo-generated Vector proxy classes."""

import unittest
from features.data import Vector_uint8, Vector_Test_StructureS, Test_StructureS


class TestVectorConstruction(unittest.TestCase):
    """Test Vector construction."""

    def test_empty_vector(self):
        v = Vector_uint8()
        self.assertEqual(len(v), 0)

    def test_vector_from_list(self):
        v = Vector_uint8([1, 2, 3, 4, 5])
        self.assertEqual(len(v), 5)

    def test_vector_iteration(self):
        v = Vector_uint8([10, 20, 30])
        values = list(v)
        self.assertEqual(values, [10, 20, 30])


class TestVectorAccess(unittest.TestCase):
    """Test Vector element access."""

    def test_getitem(self):
        v = Vector_uint8([1, 2, 3])
        self.assertEqual(v[0], 1)
        self.assertEqual(v[1], 2)
        self.assertEqual(v[2], 3)

    def test_negative_index(self):
        v = Vector_uint8([1, 2, 3])
        self.assertEqual(v[-1], 3)

    def test_setitem(self):
        v = Vector_uint8([1, 2, 3])
        v[1] = 99
        self.assertEqual(v[1], 99)


class TestVectorMutations(unittest.TestCase):
    """Test Vector mutation operations."""

    def test_append(self):
        v = Vector_uint8([1, 2])
        v.append(3)
        self.assertEqual(len(v), 3)
        self.assertEqual(v[2], 3)

    def test_clear(self):
        v = Vector_uint8([1, 2, 3])
        v.clear()
        self.assertEqual(len(v), 0)

    def test_pop(self):
        v = Vector_uint8([1, 2, 3])
        val = v.pop()
        self.assertEqual(val, 3)
        self.assertEqual(len(v), 2)

    def test_pop_at_index(self):
        v = Vector_uint8([1, 2, 3])
        val = v.pop(0)
        self.assertEqual(val, 1)
        self.assertEqual(list(v), [2, 3])

    def test_insert(self):
        v = Vector_uint8([1, 3])
        v.insert(1, 2)
        self.assertEqual(list(v), [1, 2, 3])

    def test_extend(self):
        v1 = Vector_uint8([1, 2])
        v2 = Vector_uint8([3, 4])
        v1.extend(v2)
        self.assertEqual(list(v1), [1, 2, 3, 4])

    def test_remove(self):
        v = Vector_uint8([1, 2, 3, 2])
        v.remove(2)
        self.assertEqual(list(v), [1, 3, 2])


class TestVectorStructure(unittest.TestCase):
    """Test Vector with structure elements."""

    def test_vector_of_structures(self):
        # Vectors of structures need dicts or vpr_values, not proxy objects
        v = Vector_Test_StructureS([
            {"f_float": 1.0, "f_string": "one"},
            {"f_float": 2.0, "f_string": "two"}
        ])
        self.assertEqual(len(v), 2)
        self.assertEqual(v[0].f_string, "one")
        self.assertEqual(v[1].f_string, "two")


class TestVectorSearch(unittest.TestCase):
    """Test Vector search operations."""

    def test_count(self):
        v = Vector_uint8([1, 2, 3, 2, 1, 2])
        self.assertEqual(v.count(2), 3)
        self.assertEqual(v.count(1), 2)
        self.assertEqual(v.count(99), 0)

    def test_index(self):
        v = Vector_uint8([1, 2, 3, 2])
        self.assertEqual(v.index(1), 0)
        self.assertEqual(v.index(2), 1)
        self.assertEqual(v.index(3), 2)

    def test_index_matches_python_list(self):
        """Verify index() returns same result as Python list."""
        data = [1, 2, 3, 2, 1]
        p = list(data)
        v = Vector_uint8(data)
        self.assertEqual(p.index(2), v.index(2))
        self.assertEqual(p.index(3), v.index(3))


class TestVectorCopy(unittest.TestCase):
    """Test Vector copy behavior."""

    def test_copy_creates_independent_vector(self):
        v1 = Vector_uint8([1, 2, 3])
        v2 = v1.copy()
        self.assertEqual(list(v1), list(v2))
        v2.append(4)
        self.assertEqual(len(v1), 3)
        self.assertEqual(len(v2), 4)

    def test_copy_preserves_values(self):
        v1 = Vector_uint8([10, 20, 30])
        v2 = v1.copy()
        self.assertEqual(list(v2), [10, 20, 30])


class TestVectorOperators(unittest.TestCase):
    """Test Vector operator overloading."""

    def test_add_creates_new_vector(self):
        v1 = Vector_uint8([1, 2])
        v2 = Vector_uint8([3, 4])
        v3 = v1 + v2
        self.assertEqual(list(v3), [1, 2, 3, 4])
        self.assertEqual(list(v1), [1, 2])  # Original unchanged
        self.assertEqual(list(v2), [3, 4])

    def test_iadd_modifies_in_place(self):
        v1 = Vector_uint8([1, 2])
        v2 = Vector_uint8([3, 4])
        v1 += v2
        self.assertEqual(list(v1), [1, 2, 3, 4])

    def test_contains(self):
        v = Vector_uint8([1, 2, 3])
        self.assertTrue(2 in v)
        self.assertFalse(99 in v)


class TestVectorSerialization(unittest.TestCase):
    """Test Vector encode/decode serialization."""

    def test_encode_decode_roundtrip(self):
        v1 = Vector_uint8([1, 2, 3, 4, 5])
        blob = v1.encode()
        v2 = Vector_uint8.decode(blob)
        self.assertEqual(list(v2), [1, 2, 3, 4, 5])

    def test_encode_decode_empty(self):
        v1 = Vector_uint8()
        blob = v1.encode()
        v2 = Vector_uint8.decode(blob)
        self.assertEqual(len(v2), 0)


if __name__ == "__main__":
    unittest.main()
