# Copyright (c) Digital Substrate 2026, All rights reserved.
"""Tests for Kibo-generated structure proxy classes."""

import unittest
import dsviper
from features.data import (
    Test_StructureS, Test_StructureT, Test_StructureU, Test_StructureV,
    Test_EnumerationE, Vec_uint8_2, Mat_uint8_2_2, Mat_uint8_2_3, Tuple_uint8_string,
    Optional_uint8, Vector_uint8, Set_uint8, Map_uint8_to_string, XArray_uint8
)


class TestStructureSConstruction(unittest.TestCase):
    """Test StructureS construction and field access."""

    def test_empty_construction(self):
        s = Test_StructureS()
        self.assertIsInstance(s, Test_StructureS)

    def test_dict_construction(self):
        s = Test_StructureS({"f_float": 3.14, "f_string": "hello"})
        self.assertAlmostEqual(s.f_float, 3.14, places=5)
        self.assertEqual(s.f_string, "hello")

    def test_field_float_access(self):
        s = Test_StructureS()
        s.f_float = 2.718
        self.assertAlmostEqual(s.f_float, 2.718, places=5)

    def test_field_string_access(self):
        s = Test_StructureS()
        s.f_string = "test"
        self.assertEqual(s.f_string, "test")


class TestStructureTConstruction(unittest.TestCase):
    """Test StructureT with nested structure."""

    def test_empty_construction(self):
        t = Test_StructureT()
        self.assertIsInstance(t, Test_StructureT)

    def test_field_string_access(self):
        t = Test_StructureT()
        t.field_string = "nested"
        self.assertEqual(t.field_string, "nested")

    def test_nested_structure_access(self):
        t = Test_StructureT()
        inner = Test_StructureS({"f_float": 1.5, "f_string": "inner"})
        t.field_structure_s = inner
        retrieved = t.field_structure_s
        self.assertAlmostEqual(retrieved.f_float, 1.5, places=5)
        self.assertEqual(retrieved.f_string, "inner")


class TestStructureUPrimitiveFields(unittest.TestCase):
    """Test StructureU primitive field access."""

    def setUp(self):
        self.u = Test_StructureU()

    def test_field_bool(self):
        self.u.f_bool = True
        self.assertTrue(self.u.f_bool)
        self.u.f_bool = False
        self.assertFalse(self.u.f_bool)

    def test_field_uint8(self):
        self.u.f_uint_8 = 255
        self.assertEqual(self.u.f_uint_8, 255)

    def test_field_uint16(self):
        self.u.f_uint_16 = 65535
        self.assertEqual(self.u.f_uint_16, 65535)

    def test_field_uint32(self):
        self.u.f_uint_32 = 4294967295
        self.assertEqual(self.u.f_uint_32, 4294967295)

    def test_field_uint64(self):
        self.u.f_uint_64 = 2**63
        self.assertEqual(self.u.f_uint_64, 2**63)

    def test_field_int8(self):
        self.u.f_int_8 = -128
        self.assertEqual(self.u.f_int_8, -128)
        self.u.f_int_8 = 127
        self.assertEqual(self.u.f_int_8, 127)

    def test_field_int16(self):
        self.u.f_int_16 = -32768
        self.assertEqual(self.u.f_int_16, -32768)

    def test_field_int32(self):
        self.u.f_int_32 = -2147483648
        self.assertEqual(self.u.f_int_32, -2147483648)

    def test_field_int64(self):
        self.u.f_int_64 = -(2**62)
        self.assertEqual(self.u.f_int_64, -(2**62))

    def test_field_float(self):
        self.u.f_float = 3.14
        self.assertAlmostEqual(self.u.f_float, 3.14, places=5)

    def test_field_double(self):
        self.u.f_double = 3.141592653589793
        self.assertAlmostEqual(self.u.f_double, 3.141592653589793, places=10)

    def test_field_string(self):
        self.u.f_string = "hello world"
        self.assertEqual(self.u.f_string, "hello world")


class TestStructureUSpecialFields(unittest.TestCase):
    """Test StructureU special type fields."""

    def setUp(self):
        self.u = Test_StructureU()

    def test_field_uuid(self):
        uuid = dsviper.ValueUUId.create()
        self.u.f_uuid = uuid
        self.assertEqual(self.u.f_uuid, uuid)

    def test_field_blob_id(self):
        blob_id = dsviper.ValueBlobId.INVALID
        self.u.f_blob_id = blob_id
        self.assertEqual(self.u.f_blob_id, blob_id)

    def test_field_commit_id(self):
        commit_id = dsviper.ValueCommitId.INVALID
        self.u.f_commit_id = commit_id
        self.assertEqual(self.u.f_commit_id, commit_id)

    def test_field_blob(self):
        blob = dsviper.ValueBlob(b"test data")
        self.u.f_blob = blob
        self.assertEqual(bytes(self.u.f_blob), b"test data")


class TestStructureUContainerFields(unittest.TestCase):
    """Test StructureU container type fields."""

    def setUp(self):
        self.u = Test_StructureU()

    def test_field_vec(self):
        vec = Vec_uint8_2([10, 20])
        self.u.f_vec = vec
        retrieved = self.u.f_vec
        self.assertEqual(retrieved[0], 10)
        self.assertEqual(retrieved[1], 20)

    def test_field_mat(self):
        mat = Mat_uint8_2_2([[1, 2], [3, 4]])
        self.u.f_mat = mat
        retrieved = self.u.f_mat
        self.assertEqual(retrieved[0, 0], 1)
        self.assertEqual(retrieved[1, 1], 4)

    def test_field_tuple(self):
        tup = Tuple_uint8_string((42, "answer"))
        self.u.f_tuple = tup
        retrieved = self.u.f_tuple
        self.assertEqual(retrieved[0], 42)
        self.assertEqual(retrieved[1], "answer")

    def test_field_optional_nil(self):
        opt = Optional_uint8()
        self.u.f_optional = opt
        retrieved = self.u.f_optional
        self.assertTrue(retrieved.is_nil())

    def test_field_optional_value(self):
        opt = Optional_uint8(42)
        self.u.f_optional = opt
        retrieved = self.u.f_optional
        self.assertFalse(retrieved.is_nil())
        self.assertEqual(retrieved.unwrap(), 42)

    def test_field_vector(self):
        vec = Vector_uint8([1, 2, 3, 4, 5])
        self.u.f_vector = vec
        retrieved = self.u.f_vector
        self.assertEqual(len(retrieved), 5)
        self.assertEqual(list(retrieved), [1, 2, 3, 4, 5])

    def test_field_set(self):
        s = Set_uint8([1, 2, 3])
        self.u.f_set = s
        retrieved = self.u.f_set
        self.assertEqual(len(retrieved), 3)
        self.assertIn(1, [x for x in retrieved])

    def test_field_xarray(self):
        xa = XArray_uint8([10, 20, 30])
        self.u.f_xarray = xa
        retrieved = self.u.f_xarray
        self.assertEqual(len(retrieved), 3)


class TestStructureUEnumeration(unittest.TestCase):
    """Test StructureU enumeration field."""

    def test_field_enumeration(self):
        u = Test_StructureU()
        e = Test_EnumerationE.A
        u.f_e = e
        retrieved = u.f_e
        # Compare underlying values since the proxy returns the same enum
        self.assertEqual(retrieved, e)


class TestStructureVConstruction(unittest.TestCase):
    """Test StructureV construction."""

    def test_empty_construction(self):
        v = Test_StructureV()
        self.assertIsInstance(v, Test_StructureV)

    def test_dict_construction_primitives(self):
        v = Test_StructureV({
            "f_bool": True,
            "f_uint8": 42,
            "f_int8": -10,
            "f_float": 3.14,
            "f_string": "hello"
        })
        self.assertTrue(v.f_bool)
        self.assertEqual(v.f_uint_8, 42)
        self.assertEqual(v.f_int_8, -10)
        self.assertAlmostEqual(v.f_float, 3.14, places=5)
        self.assertEqual(v.f_string, "hello")


class TestStructureVPrimitiveFields(unittest.TestCase):
    """Test StructureV primitive field access."""

    def setUp(self):
        self.v = Test_StructureV()

    def test_field_bool(self):
        self.v.f_bool = True
        self.assertTrue(self.v.f_bool)
        self.v.f_bool = False
        self.assertFalse(self.v.f_bool)

    def test_field_uint8(self):
        self.v.f_uint_8 = 255
        self.assertEqual(self.v.f_uint_8, 255)

    def test_field_uint16(self):
        self.v.f_uint_16 = 65535
        self.assertEqual(self.v.f_uint_16, 65535)

    def test_field_uint32(self):
        self.v.f_uint_32 = 4294967295
        self.assertEqual(self.v.f_uint_32, 4294967295)

    def test_field_uint64(self):
        self.v.f_uint_64 = 2**63
        self.assertEqual(self.v.f_uint_64, 2**63)

    def test_field_int8(self):
        self.v.f_int_8 = -128
        self.assertEqual(self.v.f_int_8, -128)
        self.v.f_int_8 = 127
        self.assertEqual(self.v.f_int_8, 127)

    def test_field_int16(self):
        self.v.f_int_16 = -32768
        self.assertEqual(self.v.f_int_16, -32768)

    def test_field_int32(self):
        self.v.f_int_32 = -2147483648
        self.assertEqual(self.v.f_int_32, -2147483648)

    def test_field_int64(self):
        self.v.f_int_64 = -(2**62)
        self.assertEqual(self.v.f_int_64, -(2**62))

    def test_field_float(self):
        self.v.f_float = 3.14
        self.assertAlmostEqual(self.v.f_float, 3.14, places=5)

    def test_field_double(self):
        self.v.f_double = 3.141592653589793
        self.assertAlmostEqual(self.v.f_double, 3.141592653589793, places=10)

    def test_field_string(self):
        self.v.f_string = "hello world"
        self.assertEqual(self.v.f_string, "hello world")


class TestStructureVSpecialFields(unittest.TestCase):
    """Test StructureV special type fields."""

    def setUp(self):
        self.v = Test_StructureV()

    def test_field_uuid(self):
        uuid = dsviper.ValueUUId.create()
        self.v.f_uuid = uuid
        self.assertEqual(self.v.f_uuid, uuid)


class TestStructureVFixedContainerFields(unittest.TestCase):
    """Test StructureV fixed-size container fields (Vec, Mat, Tuple)."""

    def setUp(self):
        self.v = Test_StructureV()

    def test_field_vec(self):
        vec = Vec_uint8_2([10, 20])
        self.v.f_vec = vec
        retrieved = self.v.f_vec
        self.assertEqual(retrieved[0], 10)
        self.assertEqual(retrieved[1], 20)

    def test_field_mat(self):
        # Mat_uint8_2_3 is 2 rows x 3 cols
        mat = Mat_uint8_2_3([[1, 2, 3], [4, 5, 6]])
        self.v.f_mat = mat
        retrieved = self.v.f_mat
        self.assertEqual(retrieved[0, 0], 1)
        self.assertEqual(retrieved[0, 2], 3)
        self.assertEqual(retrieved[1, 1], 5)

    def test_field_tuple(self):
        tup = Tuple_uint8_string((42, "answer"))
        self.v.f_tuple = tup
        retrieved = self.v.f_tuple
        self.assertEqual(retrieved[0], 42)
        self.assertEqual(retrieved[1], "answer")


class TestStructureVDynamicContainerFields(unittest.TestCase):
    """Test StructureV dynamic container fields (Optional, Vector, Set, Map)."""

    def setUp(self):
        self.v = Test_StructureV()

    def test_field_optional_nil(self):
        opt = Optional_uint8()
        self.v.f_optional = opt
        retrieved = self.v.f_optional
        self.assertTrue(retrieved.is_nil())

    def test_field_optional_value(self):
        opt = Optional_uint8(42)
        self.v.f_optional = opt
        retrieved = self.v.f_optional
        self.assertFalse(retrieved.is_nil())
        self.assertEqual(retrieved.unwrap(), 42)

    def test_field_vector(self):
        vec = Vector_uint8([1, 2, 3, 4, 5])
        self.v.f_vector = vec
        retrieved = self.v.f_vector
        self.assertEqual(len(retrieved), 5)
        self.assertEqual(list(retrieved), [1, 2, 3, 4, 5])

    def test_field_set(self):
        s = Set_uint8([1, 2, 3])
        self.v.f_set = s
        retrieved = self.v.f_set
        self.assertEqual(len(retrieved), 3)
        self.assertTrue(1 in retrieved)
        self.assertTrue(2 in retrieved)
        self.assertTrue(3 in retrieved)

    def test_field_map(self):
        m = Map_uint8_to_string({1: "one", 2: "two"})
        self.v.f_map = m
        retrieved = self.v.f_map
        self.assertEqual(len(retrieved), 2)
        self.assertEqual(retrieved[1], "one")
        self.assertEqual(retrieved[2], "two")


class TestStructureVEnumAndStructureFields(unittest.TestCase):
    """Test StructureV enumeration and nested structure fields."""

    def setUp(self):
        self.v = Test_StructureV()

    def test_field_enumeration(self):
        self.v.f_e = Test_EnumerationE.B
        retrieved = self.v.f_e
        self.assertEqual(retrieved, Test_EnumerationE.B)
        self.assertEqual(retrieved.name(), "b")

    def test_field_structure_s(self):
        s = Test_StructureS({"f_float": 1.5, "f_string": "nested"})
        self.v.f_s = s
        retrieved = self.v.f_s
        self.assertAlmostEqual(retrieved.f_float, 1.5, places=5)
        self.assertEqual(retrieved.f_string, "nested")

    def test_field_structure_t(self):
        t = Test_StructureT()
        t.field_string = "level1"
        inner_s = Test_StructureS({"f_float": 2.5, "f_string": "level2"})
        t.field_structure_s = inner_s
        self.v.f_t = t
        retrieved = self.v.f_t
        self.assertEqual(retrieved.field_string, "level1")
        self.assertAlmostEqual(retrieved.field_structure_s.f_float, 2.5, places=5)


class TestStructureVCopy(unittest.TestCase):
    """Test StructureV copy operation."""

    def test_copy_creates_independent_structure(self):
        v1 = Test_StructureV()
        v1.f_string = "original"
        v1.f_uint_8 = 100
        v2 = v1.copy()
        v2.f_string = "modified"
        v2.f_uint_8 = 200
        self.assertEqual(v1.f_string, "original")
        self.assertEqual(v1.f_uint_8, 100)
        self.assertEqual(v2.f_string, "modified")
        self.assertEqual(v2.f_uint_8, 200)

    def test_copy_preserves_nested_structures(self):
        v1 = Test_StructureV()
        v1.f_s = Test_StructureS({"f_float": 3.14, "f_string": "pi"})
        v2 = v1.copy()
        self.assertAlmostEqual(v2.f_s.f_float, 3.14, places=5)
        self.assertEqual(v2.f_s.f_string, "pi")


class TestStructureVSerialization(unittest.TestCase):
    """Test StructureV encode/decode serialization."""

    def test_encode_decode_roundtrip(self):
        v1 = Test_StructureV()
        v1.f_bool = True
        v1.f_uint_8 = 42
        v1.f_string = "test"
        blob = v1.encode()
        v2 = Test_StructureV.decode(blob)
        self.assertTrue(v2.f_bool)
        self.assertEqual(v2.f_uint_8, 42)
        self.assertEqual(v2.f_string, "test")

    def test_encode_decode_with_containers(self):
        v1 = Test_StructureV()
        v1.f_vector = Vector_uint8([10, 20, 30])
        v1.f_set = Set_uint8([1, 2, 3])
        v1.f_map = Map_uint8_to_string({1: "a", 2: "b"})
        blob = v1.encode()
        v2 = Test_StructureV.decode(blob)
        self.assertEqual(list(v2.f_vector), [10, 20, 30])
        self.assertEqual(len(v2.f_set), 3)
        self.assertEqual(v2.f_map[1], "a")

    def test_encode_decode_with_nested_structures(self):
        v1 = Test_StructureV()
        v1.f_s = Test_StructureS({"f_float": 2.718, "f_string": "euler"})
        v1.f_e = Test_EnumerationE.C
        blob = v1.encode()
        v2 = Test_StructureV.decode(blob)
        self.assertAlmostEqual(v2.f_s.f_float, 2.718, places=3)
        self.assertEqual(v2.f_s.f_string, "euler")
        self.assertEqual(v2.f_e, Test_EnumerationE.C)


class TestStructureCopy(unittest.TestCase):
    """Test structure copy operation."""

    def test_structure_s_copy(self):
        s1 = Test_StructureS({"f_float": 1.5, "f_string": "original"})
        s2 = s1.copy()
        s2.f_string = "modified"
        self.assertEqual(s1.f_string, "original")
        self.assertEqual(s2.f_string, "modified")

    def test_structure_t_copy(self):
        t1 = Test_StructureT()
        t1.field_string = "original"
        t2 = t1.copy()
        t2.field_string = "modified"
        self.assertEqual(t1.field_string, "original")
        self.assertEqual(t2.field_string, "modified")


class TestStructureEquality(unittest.TestCase):
    """Test structure equality comparison."""

    def test_equal_structures(self):
        s1 = Test_StructureS({"f_float": 1.0, "f_string": "test"})
        s2 = Test_StructureS({"f_float": 1.0, "f_string": "test"})
        self.assertEqual(s1, s2)

    def test_unequal_structures(self):
        s1 = Test_StructureS({"f_float": 1.0, "f_string": "test"})
        s2 = Test_StructureS({"f_float": 2.0, "f_string": "test"})
        self.assertNotEqual(s1, s2)


class TestStructureVprValue(unittest.TestCase):
    """Test access to underlying Viper value."""

    def test_vpr_value_is_value_structure(self):
        s = Test_StructureS()
        self.assertIsInstance(s.vpr_value, dsviper.ValueStructure)

    def test_vpr_value_roundtrip(self):
        s1 = Test_StructureS({"f_float": 2.5, "f_string": "test"})
        vpr = s1.vpr_value
        s2 = Test_StructureS(vpr)
        self.assertEqual(s1.f_float, s2.f_float)
        self.assertEqual(s1.f_string, s2.f_string)


if __name__ == "__main__":
    unittest.main()
