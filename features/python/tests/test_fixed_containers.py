# Copyright (c) Digital Substrate 2026, All rights reserved.
"""Tests for Kibo-generated fixed-size container proxy classes.

This module tests:
- Vec: Fixed-size vectors (std::array<T, N>)
- Mat: Fixed-size matrices (std::array<std::array<T, M>, N>)
- Tuple: Fixed-size heterogeneous tuples (std::tuple<T...>)
"""

import unittest
import dsviper
from features.data import (
    Vec_uint8_2,
    Mat_uint8_2_2, Mat_uint8_2_3,
    Tuple_uint8_string
)


# =============================================================================
# Vec Tests
# =============================================================================

class TestVecConstruction(unittest.TestCase):
    """Test Vec construction."""

    def test_default_construction(self):
        v = Vec_uint8_2()
        self.assertEqual(len(v), 2)

    def test_from_list(self):
        v = Vec_uint8_2([10, 20])
        self.assertEqual(len(v), 2)
        self.assertEqual(v[0], 10)
        self.assertEqual(v[1], 20)

    def test_from_tuple(self):
        v = Vec_uint8_2((5, 15))
        self.assertEqual(v[0], 5)
        self.assertEqual(v[1], 15)


class TestVecAccess(unittest.TestCase):
    """Test Vec element access."""

    def test_getitem(self):
        v = Vec_uint8_2([10, 20])
        self.assertEqual(v[0], 10)
        self.assertEqual(v[1], 20)

    def test_setitem(self):
        v = Vec_uint8_2([10, 20])
        v[0] = 99
        self.assertEqual(v[0], 99)
        self.assertEqual(v[1], 20)

    def test_setitem_all(self):
        v = Vec_uint8_2([0, 0])
        v[0] = 100
        v[1] = 200
        self.assertEqual(v[0], 100)
        self.assertEqual(v[1], 200)


class TestVecLen(unittest.TestCase):
    """Test Vec length."""

    def test_len_is_fixed(self):
        v = Vec_uint8_2([10, 20])
        self.assertEqual(len(v), 2)

    def test_len_default(self):
        v = Vec_uint8_2()
        self.assertEqual(len(v), 2)


class TestVecToTuple(unittest.TestCase):
    """Test Vec to_tuple() conversion."""

    def test_to_tuple(self):
        v = Vec_uint8_2([10, 20])
        t = v.to_tuple()
        self.assertIsInstance(t, tuple)
        self.assertEqual(t, (10, 20))

    def test_to_tuple_default_values(self):
        v = Vec_uint8_2()
        t = v.to_tuple()
        self.assertIsInstance(t, tuple)
        self.assertEqual(len(t), 2)


class TestVecCopy(unittest.TestCase):
    """Test Vec copy behavior."""

    def test_copy_creates_independent_vec(self):
        v1 = Vec_uint8_2([10, 20])
        v2 = v1.copy()
        self.assertEqual(v2[0], 10)
        self.assertEqual(v2[1], 20)
        v2[0] = 99
        self.assertEqual(v1[0], 10)
        self.assertEqual(v2[0], 99)

    def test_copy_preserves_values(self):
        v1 = Vec_uint8_2([100, 200])
        v2 = v1.copy()
        self.assertEqual(v2.to_tuple(), (100, 200))


class TestVecSerialization(unittest.TestCase):
    """Test Vec encode/decode serialization."""

    def test_encode_decode_roundtrip(self):
        v1 = Vec_uint8_2([10, 20])
        blob = v1.encode()
        v2 = Vec_uint8_2.decode(blob)
        self.assertEqual(v2[0], 10)
        self.assertEqual(v2[1], 20)

    def test_encode_decode_preserves_all(self):
        v1 = Vec_uint8_2([255, 128])
        blob = v1.encode()
        v2 = Vec_uint8_2.decode(blob)
        self.assertEqual(v2.to_tuple(), (255, 128))


# =============================================================================
# Mat Tests
# =============================================================================

class TestMatConstruction(unittest.TestCase):
    """Test Mat construction."""

    def test_default_construction_2x2(self):
        m = Mat_uint8_2_2()
        # len returns total element count (2*2=4)
        self.assertEqual(len(m), 4)

    def test_from_nested_list_2x2(self):
        m = Mat_uint8_2_2([[1, 2], [3, 4]])
        self.assertEqual(len(m), 4)

    def test_default_construction_2x3(self):
        m = Mat_uint8_2_3()
        # len returns total element count (2*3=6)
        self.assertEqual(len(m), 6)

    def test_from_nested_list_2x3(self):
        m = Mat_uint8_2_3([[1, 2, 3], [4, 5, 6]])
        self.assertEqual(len(m), 6)


class TestMatAccessByRowIndex(unittest.TestCase):
    """Test Mat access by row index (returns row as tuple)."""

    def test_getitem_row_2x2(self):
        m = Mat_uint8_2_2([[1, 2], [3, 4]])
        row0 = m[0]
        row1 = m[1]
        self.assertEqual(row0, (1, 2))
        self.assertEqual(row1, (3, 4))

    def test_getitem_row_2x3(self):
        m = Mat_uint8_2_3([[1, 2, 3], [4, 5, 6]])
        row0 = m[0]
        row1 = m[1]
        self.assertEqual(row0, (1, 2, 3))
        self.assertEqual(row1, (4, 5, 6))


class TestMatAccessByCoordinates(unittest.TestCase):
    """Test Mat access by (row, col) coordinates."""

    def test_getitem_coordinates_2x2(self):
        m = Mat_uint8_2_2([[1, 2], [3, 4]])
        self.assertEqual(m[0, 0], 1)
        self.assertEqual(m[0, 1], 2)
        self.assertEqual(m[1, 0], 3)
        self.assertEqual(m[1, 1], 4)

    def test_getitem_coordinates_2x3(self):
        m = Mat_uint8_2_3([[1, 2, 3], [4, 5, 6]])
        self.assertEqual(m[0, 0], 1)
        self.assertEqual(m[0, 2], 3)
        self.assertEqual(m[1, 1], 5)
        self.assertEqual(m[1, 2], 6)

    def test_setitem_coordinates_2x2(self):
        m = Mat_uint8_2_2([[1, 2], [3, 4]])
        m[0, 1] = 99
        self.assertEqual(m[0, 1], 99)
        self.assertEqual(m[0, 0], 1)

    def test_setitem_coordinates_2x3(self):
        m = Mat_uint8_2_3([[1, 2, 3], [4, 5, 6]])
        m[1, 2] = 99
        self.assertEqual(m[1, 2], 99)


class TestMatSetRow(unittest.TestCase):
    """Test Mat row assignment."""

    def test_setitem_row_2x2(self):
        m = Mat_uint8_2_2([[1, 2], [3, 4]])
        m[0] = (10, 20)
        self.assertEqual(m[0], (10, 20))
        self.assertEqual(m[1], (3, 4))

    def test_setitem_row_2x3(self):
        m = Mat_uint8_2_3([[1, 2, 3], [4, 5, 6]])
        m[1] = (40, 50, 60)
        self.assertEqual(m[1], (40, 50, 60))


class TestMatLen(unittest.TestCase):
    """Test Mat length (total element count)."""

    def test_len_2x2(self):
        m = Mat_uint8_2_2()
        # 2x2 = 4 elements
        self.assertEqual(len(m), 4)

    def test_len_2x3(self):
        m = Mat_uint8_2_3()
        # 2x3 = 6 elements
        self.assertEqual(len(m), 6)


class TestMatToTuple(unittest.TestCase):
    """Test Mat to_tuple() conversion."""

    def test_to_tuple_2x2(self):
        m = Mat_uint8_2_2([[1, 2], [3, 4]])
        t = m.to_tuple()
        self.assertIsInstance(t, tuple)
        self.assertEqual(t, ((1, 2), (3, 4)))

    def test_to_tuple_2x3(self):
        m = Mat_uint8_2_3([[1, 2, 3], [4, 5, 6]])
        t = m.to_tuple()
        self.assertEqual(t, ((1, 2, 3), (4, 5, 6)))


class TestMatCopy(unittest.TestCase):
    """Test Mat copy behavior."""

    def test_copy_creates_independent_mat_2x2(self):
        m1 = Mat_uint8_2_2([[1, 2], [3, 4]])
        m2 = m1.copy()
        m2[0, 0] = 99
        self.assertEqual(m1[0, 0], 1)
        self.assertEqual(m2[0, 0], 99)

    def test_copy_preserves_values_2x3(self):
        m1 = Mat_uint8_2_3([[1, 2, 3], [4, 5, 6]])
        m2 = m1.copy()
        self.assertEqual(m2.to_tuple(), ((1, 2, 3), (4, 5, 6)))


class TestMatSerialization(unittest.TestCase):
    """Test Mat encode/decode serialization."""

    def test_encode_decode_roundtrip_2x2(self):
        m1 = Mat_uint8_2_2([[1, 2], [3, 4]])
        blob = m1.encode()
        m2 = Mat_uint8_2_2.decode(blob)
        self.assertEqual(m2.to_tuple(), ((1, 2), (3, 4)))

    def test_encode_decode_roundtrip_2x3(self):
        m1 = Mat_uint8_2_3([[10, 20, 30], [40, 50, 60]])
        blob = m1.encode()
        m2 = Mat_uint8_2_3.decode(blob)
        self.assertEqual(m2.to_tuple(), ((10, 20, 30), (40, 50, 60)))


# =============================================================================
# Tuple Tests
# =============================================================================

class TestTupleConstruction(unittest.TestCase):
    """Test Tuple construction."""

    def test_default_construction(self):
        t = Tuple_uint8_string()
        self.assertEqual(len(t), 2)

    def test_from_tuple(self):
        t = Tuple_uint8_string((42, "hello"))
        self.assertEqual(len(t), 2)
        self.assertEqual(t[0], 42)
        self.assertEqual(t[1], "hello")

    def test_from_list(self):
        t = Tuple_uint8_string([100, "world"])
        self.assertEqual(t[0], 100)
        self.assertEqual(t[1], "world")


class TestTupleLen(unittest.TestCase):
    """Test Tuple length."""

    def test_len_is_fixed(self):
        t = Tuple_uint8_string((1, "a"))
        self.assertEqual(len(t), 2)


class TestTupleGetitem(unittest.TestCase):
    """Test Tuple element access via __getitem__."""

    def test_getitem_index_0(self):
        t = Tuple_uint8_string((42, "hello"))
        self.assertEqual(t[0], 42)

    def test_getitem_index_1(self):
        t = Tuple_uint8_string((42, "hello"))
        self.assertEqual(t[1], "hello")

    def test_getitem_out_of_range(self):
        t = Tuple_uint8_string((42, "hello"))
        with self.assertRaises(IndexError):
            _ = t[2]


class TestTupleTypedGetters(unittest.TestCase):
    """Test Tuple typed getter methods (get_0, get_1)."""

    def test_get_0(self):
        t = Tuple_uint8_string((42, "hello"))
        self.assertEqual(t.get_0(), 42)
        self.assertIsInstance(t.get_0(), int)

    def test_get_1(self):
        t = Tuple_uint8_string((42, "hello"))
        self.assertEqual(t.get_1(), "hello")
        self.assertIsInstance(t.get_1(), str)


class TestTupleIteration(unittest.TestCase):
    """Test Tuple iteration."""

    def test_iter(self):
        t = Tuple_uint8_string((42, "hello"))
        values = list(t)
        self.assertEqual(len(values), 2)
        self.assertEqual(values[0], 42)
        self.assertEqual(values[1], "hello")

    def test_iter_unpacking(self):
        t = Tuple_uint8_string((42, "hello"))
        a, b = t
        self.assertEqual(a, 42)
        self.assertEqual(b, "hello")

    def test_iter_multiple_times(self):
        t = Tuple_uint8_string((42, "hello"))
        list1 = list(t)
        list2 = list(t)
        self.assertEqual(list1, list2)


class TestTupleCopy(unittest.TestCase):
    """Test Tuple copy behavior."""

    def test_copy_creates_independent_tuple(self):
        t1 = Tuple_uint8_string((42, "hello"))
        t2 = t1.copy()
        self.assertEqual(t2[0], 42)
        self.assertEqual(t2[1], "hello")

    def test_copy_preserves_values(self):
        t1 = Tuple_uint8_string((255, "test"))
        t2 = t1.copy()
        self.assertEqual(t2.get_0(), 255)
        self.assertEqual(t2.get_1(), "test")


class TestTupleSerialization(unittest.TestCase):
    """Test Tuple encode/decode serialization."""

    def test_encode_decode_roundtrip(self):
        t1 = Tuple_uint8_string((42, "hello"))
        blob = t1.encode()
        t2 = Tuple_uint8_string.decode(blob)
        self.assertEqual(t2[0], 42)
        self.assertEqual(t2[1], "hello")

    def test_encode_decode_special_chars(self):
        t1 = Tuple_uint8_string((0, "héllo wörld"))
        blob = t1.encode()
        t2 = Tuple_uint8_string.decode(blob)
        self.assertEqual(t2[1], "héllo wörld")

    def test_encode_decode_empty_string(self):
        t1 = Tuple_uint8_string((128, ""))
        blob = t1.encode()
        t2 = Tuple_uint8_string.decode(blob)
        self.assertEqual(t2[0], 128)
        self.assertEqual(t2[1], "")


class TestTupleComparison(unittest.TestCase):
    """Test Tuple comparison operations (inherited from Proxy)."""

    def test_equal_tuples(self):
        t1 = Tuple_uint8_string((42, "hello"))
        t2 = Tuple_uint8_string((42, "hello"))
        self.assertEqual(t1, t2)

    def test_not_equal_tuples(self):
        t1 = Tuple_uint8_string((42, "hello"))
        t2 = Tuple_uint8_string((42, "world"))
        self.assertNotEqual(t1, t2)

    def test_not_equal_different_first(self):
        t1 = Tuple_uint8_string((1, "hello"))
        t2 = Tuple_uint8_string((2, "hello"))
        self.assertNotEqual(t1, t2)


if __name__ == "__main__":
    unittest.main()
