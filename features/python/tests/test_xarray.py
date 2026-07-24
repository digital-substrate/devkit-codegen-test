# Copyright (c) Digital Substrate 2026, All rights reserved.
"""Tests for Kibo-generated XArray proxy classes.

XArray is an extended array with stable position-based addressing using UUIDs.
Elements can be accessed by index (int) or by position (UUID), and positions
remain stable across insertions and deletions.
"""

import unittest
import dsviper
from features.data import (
    XArray_int8, XArray_uint8, Vector_int8, Vector_uint8,
    XArray_Test_StructureS, Test_StructureS,
)


class TestXArrayConstruction(unittest.TestCase):
    """Test XArray construction."""

    def test_empty_xarray(self):
        xa = XArray_int8()
        self.assertEqual(len(xa), 0)

    def test_xarray_from_list(self):
        xa = XArray_int8([1, 2, 3, 4, 5])
        self.assertEqual(len(xa), 5)

    def test_xarray_from_empty_list(self):
        xa = XArray_int8([])
        self.assertEqual(len(xa), 0)


class TestXArrayIndexAccess(unittest.TestCase):
    """Test XArray access by integer index."""

    def test_getitem_by_index(self):
        xa = XArray_int8([10, 20, 30])
        self.assertEqual(xa[0], 10)
        self.assertEqual(xa[1], 20)
        self.assertEqual(xa[2], 30)

    def test_setitem_by_index(self):
        xa = XArray_int8([10, 20, 30])
        xa[1] = 99
        self.assertEqual(xa[1], 99)

    def test_negative_index_not_supported(self):
        """XArray does not support negative indexing like Python lists."""
        xa = XArray_int8([10, 20, 30])
        # Negative indices return None in XArray
        self.assertIsNone(xa[-1])


class TestXArrayPositionAccess(unittest.TestCase):
    """Test XArray access by position (UUID)."""

    def test_getitem_by_position(self):
        xa = XArray_int8([10, 20, 30])
        pos = xa.position(1)
        self.assertIsNotNone(pos)
        self.assertEqual(xa[pos], 20)

    def test_setitem_by_position(self):
        xa = XArray_int8([10, 20, 30])
        pos = xa.position(1)
        xa[pos] = 99
        self.assertEqual(xa[pos], 99)
        self.assertEqual(xa[1], 99)


class TestXArrayContains(unittest.TestCase):
    """Test XArray membership testing."""

    def test_contains_present(self):
        xa = XArray_int8([10, 20, 30])
        self.assertTrue(20 in xa)

    def test_contains_absent(self):
        xa = XArray_int8([10, 20, 30])
        self.assertFalse(99 in xa)

    def test_contains_empty(self):
        xa = XArray_int8()
        self.assertFalse(10 in xa)


class TestXArrayPositions(unittest.TestCase):
    """Test XArray position management."""

    def test_positions_returns_list(self):
        xa = XArray_int8([10, 20, 30])
        positions = xa.positions()
        # XArray includes END position, so 3 elements = 4 positions
        self.assertEqual(len(positions), 4)
        self.assertIsInstance(positions[0], dsviper.ValueUUId)

    def test_positions_empty_xarray(self):
        xa = XArray_int8()
        positions = xa.positions()
        # Even empty XArray has END position
        self.assertEqual(len(positions), 1)

    def test_position_index_roundtrip(self):
        xa = XArray_int8([10, 20, 30])
        for i in range(3):
            pos = xa.position(i)
            self.assertIsNotNone(pos)
            idx = xa.index(pos)
            self.assertEqual(idx, i)

    def test_has_position_true(self):
        xa = XArray_int8([10, 20, 30])
        pos = xa.position(1)
        self.assertTrue(xa.has_position(pos))

    def test_has_position_false(self):
        xa = XArray_int8([10, 20, 30])
        new_pos = XArray_int8.create_position()
        self.assertFalse(xa.has_position(new_pos))

    def test_position_invalid_index(self):
        xa = XArray_int8([10, 20, 30])
        pos = xa.position(99)
        self.assertIsNone(pos)


class TestXArrayItems(unittest.TestCase):
    """Test XArray items() method."""

    def test_items_returns_position_value_pairs(self):
        xa = XArray_int8([10, 20, 30])
        items = xa.items()
        self.assertEqual(len(items), 3)
        for pos, val in items:
            self.assertIsInstance(pos, dsviper.ValueUUId)
        values = [v for _, v in items]
        self.assertEqual(values, [10, 20, 30])

    def test_items_empty(self):
        xa = XArray_int8()
        items = xa.items()
        self.assertEqual(len(items), 0)


class TestXArrayAt(unittest.TestCase):
    """Test XArray at() method for position-based access."""

    def test_at_valid_position(self):
        xa = XArray_int8([10, 20, 30])
        pos = xa.position(1)
        self.assertEqual(xa.at(pos), 20)

    def test_at_invalid_position_raises(self):
        """Accessing an invalid position raises ViperError."""
        xa = XArray_int8([10, 20, 30])
        invalid_pos = XArray_int8.create_position()
        with self.assertRaises(dsviper.ViperError):
            xa.at(invalid_pos)


class TestXArraySet(unittest.TestCase):
    """Test XArray set() method for position-based mutation."""

    def test_set_value_at_position(self):
        xa = XArray_int8([10, 20, 30])
        pos = xa.position(1)
        xa.set(pos, 99)
        self.assertEqual(xa.at(pos), 99)
        self.assertEqual(xa[1], 99)


class TestXArrayAppend(unittest.TestCase):
    """Test XArray append() method."""

    def test_append_to_empty(self):
        xa = XArray_int8()
        xa.append(42)
        self.assertEqual(len(xa), 1)
        self.assertEqual(xa[0], 42)

    def test_append_multiple(self):
        xa = XArray_int8()
        xa.append(1)
        xa.append(2)
        xa.append(3)
        self.assertEqual(len(xa), 3)
        self.assertEqual(xa[0], 1)
        self.assertEqual(xa[1], 2)
        self.assertEqual(xa[2], 3)

    def test_append_to_existing(self):
        xa = XArray_int8([10, 20])
        xa.append(30)
        self.assertEqual(len(xa), 3)
        self.assertEqual(xa[2], 30)


class TestXArrayInsert(unittest.TestCase):
    """Test XArray insert() method."""

    def test_insert_at_beginning(self):
        xa = XArray_int8([20, 30])
        first_pos = xa.position(0)
        xa.insert(first_pos, 10)
        self.assertEqual(len(xa), 3)
        self.assertEqual(xa[0], 10)
        self.assertEqual(xa[1], 20)
        self.assertEqual(xa[2], 30)

    def test_insert_at_end(self):
        xa = XArray_int8([10, 20])
        end_pos = XArray_int8.end()
        xa.insert(end_pos, 30)
        self.assertEqual(len(xa), 3)
        self.assertEqual(xa[2], 30)

    def test_insert_in_middle(self):
        xa = XArray_int8([10, 30])
        pos_30 = xa.position(1)
        xa.insert(pos_30, 20)
        self.assertEqual(len(xa), 3)
        self.assertEqual(xa[0], 10)
        self.assertEqual(xa[1], 20)
        self.assertEqual(xa[2], 30)

    def test_insert_with_explicit_position(self):
        xa = XArray_int8([10, 30])
        new_pos = XArray_int8.create_position()
        pos_30 = xa.position(1)
        xa.insert(pos_30, 20, new_pos)
        self.assertEqual(len(xa), 3)
        self.assertTrue(xa.has_position(new_pos))
        self.assertEqual(xa.at(new_pos), 20)


class TestXArrayRemove(unittest.TestCase):
    """Test XArray remove() method."""

    def test_remove_by_position(self):
        xa = XArray_int8([10, 20, 30])
        pos = xa.position(1)
        xa.remove(pos)
        self.assertEqual(len(xa), 2)
        self.assertEqual(xa[0], 10)
        self.assertEqual(xa[1], 30)

    def test_remove_first(self):
        xa = XArray_int8([10, 20, 30])
        pos = xa.position(0)
        xa.remove(pos)
        self.assertEqual(len(xa), 2)
        self.assertEqual(xa[0], 20)

    def test_remove_last(self):
        xa = XArray_int8([10, 20, 30])
        pos = xa.position(2)
        xa.remove(pos)
        self.assertEqual(len(xa), 2)
        self.assertEqual(xa[1], 20)

    def test_removed_position_returns_none(self):
        """After remove, position still exists but at() returns None."""
        xa = XArray_int8([10, 20, 30])
        pos = xa.position(1)
        self.assertIsNotNone(pos)
        xa.remove(pos)
        # Position still exists but value is None
        self.assertTrue(xa.has_position(pos))
        self.assertIsNone(xa.at(pos))


class TestXArrayPositionOf(unittest.TestCase):
    """Test XArray position_of() method."""

    def test_position_of_existing(self):
        xa = XArray_int8([10, 20, 30])
        pos = xa.position_of(20)
        self.assertIsNotNone(pos)
        self.assertEqual(xa.at(pos), 20)

    def test_position_of_first_occurrence(self):
        xa = XArray_int8([10, 20, 20, 30])
        pos = xa.position_of(20)
        self.assertIsNotNone(pos)
        idx = xa.index(pos)
        self.assertEqual(idx, 1)

    def test_position_of_absent(self):
        xa = XArray_int8([10, 20, 30])
        pos = xa.position_of(99)
        self.assertIsNone(pos)


class TestXArrayInsertPosition(unittest.TestCase):
    """Test XArray insert_position() for pre-allocating positions."""

    def test_insert_position_then_set(self):
        xa = XArray_int8([10, 30])
        new_pos = XArray_int8.create_position()
        pos_30 = xa.position(1)
        xa.insert_position(pos_30, new_pos)
        self.assertTrue(xa.has_position(new_pos))
        xa.set(new_pos, 20)
        self.assertEqual(xa.at(new_pos), 20)


class TestXArrayDisablePosition(unittest.TestCase):
    """Test XArray disable_position() method."""

    def test_disable_position_removes_value(self):
        """disable_position removes the value but keeps position valid."""
        xa = XArray_int8([10, 20, 30])
        pos = xa.position(1)
        self.assertIsNotNone(pos)
        xa.disable_position(pos)
        # Position still exists but value is removed
        self.assertEqual(len(xa), 2)
        # The values should now be [10, 30]
        self.assertEqual(xa[0], 10)
        self.assertEqual(xa[1], 30)


class TestXArrayStaticMethods(unittest.TestCase):
    """Test XArray static methods."""

    def test_end_returns_uuid(self):
        end_pos = XArray_int8.end()
        self.assertIsInstance(end_pos, dsviper.ValueUUId)

    def test_create_position_returns_uuid(self):
        pos = XArray_int8.create_position()
        self.assertIsInstance(pos, dsviper.ValueUUId)

    def test_create_position_unique(self):
        pos1 = XArray_int8.create_position()
        pos2 = XArray_int8.create_position()
        self.assertNotEqual(pos1, pos2)


class TestXArrayCopy(unittest.TestCase):
    """Test XArray copy behavior."""

    def test_copy_creates_independent_xarray(self):
        xa1 = XArray_int8([10, 20, 30])
        xa2 = xa1.copy()
        self.assertEqual(len(xa1), len(xa2))
        xa2.append(40)
        self.assertEqual(len(xa1), 3)
        self.assertEqual(len(xa2), 4)

    def test_copy_preserves_values(self):
        xa1 = XArray_int8([10, 20, 30])
        xa2 = xa1.copy()
        self.assertEqual(xa2[0], 10)
        self.assertEqual(xa2[1], 20)
        self.assertEqual(xa2[2], 30)

    def test_copy_mutation_independent(self):
        xa1 = XArray_int8([10, 20, 30])
        xa2 = xa1.copy()
        xa1[1] = 99
        self.assertEqual(xa1[1], 99)
        self.assertEqual(xa2[1], 20)


class TestXArrayToVector(unittest.TestCase):
    """Test XArray to_vector() conversion."""

    def test_to_vector_preserves_values(self):
        xa = XArray_int8([10, 20, 30])
        v = xa.to_vector()
        self.assertIsInstance(v, Vector_int8)
        self.assertEqual(len(v), 3)
        self.assertEqual(list(v), [10, 20, 30])

    def test_to_vector_empty(self):
        xa = XArray_int8()
        v = xa.to_vector()
        self.assertEqual(len(v), 0)

    def test_to_vector_uint8(self):
        xa = XArray_uint8([1, 2, 3])
        v = xa.to_vector()
        self.assertIsInstance(v, Vector_uint8)
        self.assertEqual(list(v), [1, 2, 3])


class TestXArrayPositionStability(unittest.TestCase):
    """Test that positions remain stable across mutations."""

    def test_position_stable_after_insert(self):
        xa = XArray_int8([10, 30])
        pos_30 = xa.position(1)
        original_value = xa.at(pos_30)
        xa.insert(pos_30, 20)
        self.assertEqual(xa.at(pos_30), original_value)

    def test_position_stable_after_append(self):
        xa = XArray_int8([10, 20])
        pos_20 = xa.position(1)
        xa.append(30)
        self.assertEqual(xa.at(pos_20), 20)

    def test_position_stable_after_remove_other(self):
        xa = XArray_int8([10, 20, 30])
        pos_10 = xa.position(0)
        pos_30 = xa.position(2)
        xa.remove(xa.position(1))
        self.assertEqual(xa.at(pos_10), 10)
        self.assertEqual(xa.at(pos_30), 30)


class TestXArrayUint8(unittest.TestCase):
    """Test XArray_uint8 variant."""

    def test_uint8_construction(self):
        xa = XArray_uint8([1, 2, 3])
        self.assertEqual(len(xa), 3)
        self.assertEqual(xa[0], 1)

    def test_uint8_append(self):
        xa = XArray_uint8()
        xa.append(255)
        self.assertEqual(xa[0], 255)

    def test_uint8_copy(self):
        xa1 = XArray_uint8([100, 200])
        xa2 = xa1.copy()
        self.assertEqual(xa2[0], 100)
        self.assertEqual(xa2[1], 200)


class TestXArraySerialization(unittest.TestCase):
    """Test XArray encode/decode serialization."""

    def test_encode_decode_roundtrip(self):
        xa1 = XArray_int8([10, 20, 30])
        blob = xa1.encode()
        xa2 = XArray_int8.decode(blob)
        self.assertEqual(len(xa2), 3)
        self.assertEqual(xa2[0], 10)
        self.assertEqual(xa2[1], 20)
        self.assertEqual(xa2[2], 30)

    def test_encode_decode_empty(self):
        xa1 = XArray_int8()
        blob = xa1.encode()
        xa2 = XArray_int8.decode(blob)
        self.assertEqual(len(xa2), 0)

    def test_encode_decode_uint8(self):
        xa1 = XArray_uint8([1, 128, 255])
        blob = xa1.encode()
        xa2 = XArray_uint8.decode(blob)
        self.assertEqual(list(xa2.to_vector()), [1, 128, 255])

    def test_encode_decode_preserves_positions(self):
        xa1 = XArray_int8([10, 20, 30])
        pos1_original = xa1.positions()
        blob = xa1.encode()
        xa2 = XArray_int8.decode(blob)
        pos2 = xa2.positions()
        self.assertEqual(len(pos1_original), len(pos2))
        for p1, p2 in zip(pos1_original, pos2):
            self.assertEqual(p1, p2)


class TestXArrayProxiedElementWraps(unittest.TestCase):
    """An xarray over a proxied element type must WRAP on the way out (D2).

    XArray_int8 has a POD element, so a missing wrap is invisible. XArray of a
    proxied struct is the case that distinguishes `items()` returning raw runtime
    values from returning proxies. Every read path must hand back a proxy.
    """

    def _make(self):
        xa = XArray_Test_StructureS()
        xa.append(Test_StructureS({"f_float": 3.5, "f_string": "hello"}))
        xa.append(Test_StructureS({"f_float": 1.0, "f_string": "world"}))
        return xa

    def test_items_returns_wrapped_proxies(self):
        xa = self._make()
        items = xa.items()
        self.assertEqual(len(items), 2)
        for pos, val in items:
            self.assertIsInstance(pos, dsviper.ValueUUId)
            self.assertIsInstance(val, Test_StructureS)
        self.assertEqual(items[0][1].f_string, "hello")
        self.assertEqual(items[1][1].f_string, "world")

    def test_at_returns_wrapped_proxy(self):
        xa = self._make()
        pos, _ = xa.items()[0]
        got = xa.at(pos)
        self.assertIsInstance(got, Test_StructureS)
        self.assertEqual(got.f_string, "hello")

    def test_getitem_returns_wrapped_proxy(self):
        xa = self._make()
        self.assertIsInstance(xa[0], Test_StructureS)
        self.assertEqual(xa[0].f_string, "hello")

    def test_to_vector_returns_wrapped_proxies(self):
        xa = self._make()
        vec = xa.to_vector()
        self.assertIsInstance(vec[0], Test_StructureS)
        self.assertEqual(vec[0].f_string, "hello")


if __name__ == "__main__":
    unittest.main()
