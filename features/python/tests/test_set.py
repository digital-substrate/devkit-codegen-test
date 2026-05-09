# Copyright (c) Digital Substrate 2026, All rights reserved.
"""Tests for Kibo-generated Set proxy classes."""

import unittest
from features.data import Set_uint8, Set_Test_ConceptAKey, Test_ConceptAKey


class TestSetConstruction(unittest.TestCase):
    """Test Set construction."""

    def test_empty_set(self):
        s = Set_uint8()
        self.assertEqual(len(s), 0)

    def test_set_from_list(self):
        s = Set_uint8([1, 2, 3])
        self.assertEqual(len(s), 3)

    def test_set_removes_duplicates(self):
        s = Set_uint8([1, 1, 2, 2, 3])
        self.assertEqual(len(s), 3)


class TestSetContains(unittest.TestCase):
    """Test Set membership testing."""

    def test_contains_present(self):
        s = Set_uint8([1, 2, 3])
        self.assertTrue(1 in s)

    def test_contains_absent(self):
        s = Set_uint8([1, 2, 3])
        self.assertFalse(99 in s)


class TestSetMutations(unittest.TestCase):
    """Test Set mutation operations."""

    def test_add(self):
        s = Set_uint8([1, 2])
        s.add(3)
        self.assertEqual(len(s), 3)
        self.assertTrue(3 in s)

    def test_add_duplicate(self):
        s = Set_uint8([1, 2])
        s.add(1)
        self.assertEqual(len(s), 2)

    def test_discard_present(self):
        s = Set_uint8([1, 2, 3])
        s.discard(2)
        self.assertEqual(len(s), 2)
        self.assertFalse(2 in s)

    def test_discard_absent(self):
        s = Set_uint8([1, 2, 3])
        s.discard(99)  # Should not raise
        self.assertEqual(len(s), 3)

    def test_remove_present(self):
        s = Set_uint8([1, 2, 3])
        s.remove(2)
        self.assertEqual(len(s), 2)

    def test_clear(self):
        s = Set_uint8([1, 2, 3])
        s.clear()
        self.assertEqual(len(s), 0)

    def test_pop(self):
        s = Set_uint8([1, 2, 3])
        val = s.pop()
        self.assertEqual(len(s), 2)
        self.assertIn(val, [1, 2, 3])


class TestSetOperations(unittest.TestCase):
    """Test Set operations (union, intersection, etc.)."""

    def test_union(self):
        s1 = Set_uint8([1, 2])
        s2 = Set_uint8([2, 3])
        result = s1.union(s2)
        self.assertEqual(len(result), 3)

    def test_union_operator(self):
        s1 = Set_uint8([1, 2])
        s2 = Set_uint8([2, 3])
        result = s1 | s2
        self.assertEqual(len(result), 3)

    def test_intersection(self):
        s1 = Set_uint8([1, 2, 3])
        s2 = Set_uint8([2, 3, 4])
        result = s1.intersection(s2)
        self.assertEqual(len(result), 2)

    def test_intersection_operator(self):
        s1 = Set_uint8([1, 2, 3])
        s2 = Set_uint8([2, 3, 4])
        result = s1 & s2
        self.assertEqual(len(result), 2)

    def test_difference(self):
        s1 = Set_uint8([1, 2, 3])
        s2 = Set_uint8([2, 3, 4])
        result = s1.difference(s2)
        self.assertEqual(len(result), 1)
        self.assertTrue(1 in result)

    def test_difference_operator(self):
        s1 = Set_uint8([1, 2, 3])
        s2 = Set_uint8([2, 3, 4])
        result = s1 - s2
        self.assertEqual(len(result), 1)

    def test_symmetric_difference(self):
        s1 = Set_uint8([1, 2, 3])
        s2 = Set_uint8([2, 3, 4])
        result = s1.symmetric_difference(s2)
        self.assertEqual(len(result), 2)

    def test_issubset(self):
        s1 = Set_uint8([1, 2])
        s2 = Set_uint8([1, 2, 3])
        self.assertTrue(s1.issubset(s2))
        self.assertFalse(s2.issubset(s1))

    def test_issuperset(self):
        s1 = Set_uint8([1, 2, 3])
        s2 = Set_uint8([1, 2])
        self.assertTrue(s1.issuperset(s2))

    def test_isdisjoint(self):
        s1 = Set_uint8([1, 2])
        s2 = Set_uint8([3, 4])
        self.assertTrue(s1.isdisjoint(s2))


class TestSetWithKeys(unittest.TestCase):
    """Test Set with concept key elements."""

    def test_set_of_keys(self):
        k1 = Test_ConceptAKey.create()
        k2 = Test_ConceptAKey.create()
        s = Set_Test_ConceptAKey()
        s.add(k1)
        s.add(k2)
        self.assertEqual(len(s), 2)
        self.assertIn(k1, s)


class TestSetCopy(unittest.TestCase):
    """Test Set copy behavior."""

    def test_copy_creates_independent_set(self):
        s1 = Set_uint8([1, 2, 3])
        s2 = s1.copy()
        self.assertEqual(len(s1), len(s2))
        s2.add(4)
        self.assertEqual(len(s1), 3)
        self.assertEqual(len(s2), 4)

    def test_copy_preserves_elements(self):
        s1 = Set_uint8([10, 20, 30])
        s2 = s1.copy()
        self.assertTrue(10 in s2)
        self.assertTrue(20 in s2)
        self.assertTrue(30 in s2)


class TestSetUpdateOperations(unittest.TestCase):
    """Test Set in-place update operations."""

    def test_update(self):
        s1 = Set_uint8([1, 2])
        s2 = Set_uint8([2, 3])
        s1.update(s2)
        self.assertEqual(len(s1), 3)
        self.assertTrue(3 in s1)

    def test_difference_update(self):
        s1 = Set_uint8([1, 2, 3])
        s2 = Set_uint8([2, 3, 4])
        s1.difference_update(s2)
        self.assertEqual(len(s1), 1)
        self.assertTrue(1 in s1)
        self.assertFalse(2 in s1)

    def test_intersection_update(self):
        s1 = Set_uint8([1, 2, 3])
        s2 = Set_uint8([2, 3, 4])
        s1.intersection_update(s2)
        self.assertTrue(2 in s1)
        self.assertTrue(3 in s1)

    def test_symmetric_difference_update(self):
        s1 = Set_uint8([1, 2, 3])
        s2 = Set_uint8([2, 3, 4])
        s1.symmetric_difference_update(s2)
        self.assertEqual(len(s1), 2)
        self.assertTrue(1 in s1)
        self.assertTrue(4 in s1)
        self.assertFalse(2 in s1)


class TestSetMinMax(unittest.TestCase):
    """Test Set min/max operations."""

    def test_min(self):
        s = Set_uint8([3, 1, 2])
        self.assertEqual(s.min(), 1)

    def test_max(self):
        s = Set_uint8([3, 1, 2])
        self.assertEqual(s.max(), 3)


class TestSetIteration(unittest.TestCase):
    """Test Set iteration."""

    def test_iter(self):
        s = Set_uint8([1, 2, 3])
        values = list(s)
        self.assertEqual(sorted(values), [1, 2, 3])

    def test_iter_empty(self):
        s = Set_uint8()
        values = list(s)
        self.assertEqual(values, [])

    def test_iter_multiple_times(self):
        s = Set_uint8([10, 20, 30])
        list1 = sorted(list(s))
        list2 = sorted(list(s))
        self.assertEqual(list1, list2)


class TestSetGetitem(unittest.TestCase):
    """Test Set indexed access."""

    def test_getitem(self):
        s = Set_uint8([10, 20, 30])
        # Sets are ordered, so getitem returns element at index
        values = [s[i] for i in range(len(s))]
        self.assertEqual(sorted(values), [10, 20, 30])


class TestSetInPlaceOperators(unittest.TestCase):
    """Test Set in-place operators."""

    def test_ior_operator(self):
        s1 = Set_uint8([1, 2])
        s2 = Set_uint8([2, 3])
        s1 |= s2
        self.assertEqual(len(s1), 3)
        self.assertTrue(1 in s1)
        self.assertTrue(2 in s1)
        self.assertTrue(3 in s1)

    def test_iand_operator(self):
        s1 = Set_uint8([1, 2, 3])
        s2 = Set_uint8([2, 3, 4])
        s1 &= s2
        self.assertTrue(2 in s1)
        self.assertTrue(3 in s1)

    def test_isub_operator(self):
        s1 = Set_uint8([1, 2, 3])
        s2 = Set_uint8([2, 3, 4])
        s1 -= s2
        self.assertEqual(len(s1), 1)
        self.assertTrue(1 in s1)
        self.assertFalse(2 in s1)

    def test_ixor_operator(self):
        s1 = Set_uint8([1, 2, 3])
        s2 = Set_uint8([2, 3, 4])
        s1 ^= s2
        self.assertEqual(len(s1), 2)
        self.assertTrue(1 in s1)
        self.assertTrue(4 in s1)
        self.assertFalse(2 in s1)


class TestSetSerialization(unittest.TestCase):
    """Test Set encode/decode serialization."""

    def test_encode_decode_roundtrip(self):
        s1 = Set_uint8([1, 2, 3])
        blob = s1.encode()
        s2 = Set_uint8.decode(blob)
        self.assertEqual(len(s2), 3)
        self.assertTrue(1 in s2)
        self.assertTrue(2 in s2)
        self.assertTrue(3 in s2)

    def test_encode_decode_empty(self):
        s1 = Set_uint8()
        blob = s1.encode()
        s2 = Set_uint8.decode(blob)
        self.assertEqual(len(s2), 0)


if __name__ == "__main__":
    unittest.main()
