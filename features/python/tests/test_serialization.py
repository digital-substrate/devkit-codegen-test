# Copyright (c) Digital Substrate 2026, All rights reserved.
"""Tests for Kibo-generated encode/decode serialization."""

import unittest
import dsviper
from features.data import (
    Test_ConceptAKey, Test_ConceptBKey,
    Test_StructureS, Test_StructureT, Test_StructureU, Test_StructureV,
    Optional_uint8, Vector_uint8, Set_uint8, Map_int8_to_string,
    AnyConceptKey
)


class TestKeyEncodeDecode(unittest.TestCase):
    """Test key encode/decode roundtrip."""

    def test_concept_a_key_roundtrip(self):
        key1 = Test_ConceptAKey.create()
        blob = key1.encode()
        key2 = Test_ConceptAKey.decode(blob)
        self.assertEqual(key1, key2)

    def test_concept_b_key_roundtrip(self):
        key1 = Test_ConceptBKey.create()
        blob = key1.encode()
        key2 = Test_ConceptBKey.decode(blob)
        self.assertEqual(key1, key2)

    def test_any_concept_key_roundtrip(self):
        key = Test_ConceptAKey.create()
        any_key1 = key.to_any_concept_key()
        blob = any_key1.encode()
        any_key2 = AnyConceptKey.decode(blob)
        self.assertEqual(any_key1, any_key2)


class TestStructureEncodeDecode(unittest.TestCase):
    """Test structure encode/decode roundtrip."""

    def test_structure_s_roundtrip(self):
        s1 = Test_StructureS({"f_float": 3.14, "f_string": "hello"})
        blob = s1.encode()
        s2 = Test_StructureS.decode(blob)
        self.assertAlmostEqual(s1.f_float, s2.f_float, places=5)
        self.assertEqual(s1.f_string, s2.f_string)

    def test_structure_t_roundtrip(self):
        inner = Test_StructureS({"f_float": 1.5, "f_string": "inner"})
        t1 = Test_StructureT()
        t1.field_string = "outer"
        t1.field_structure_s = inner

        blob = t1.encode()
        t2 = Test_StructureT.decode(blob)

        self.assertEqual(t1.field_string, t2.field_string)
        self.assertAlmostEqual(t1.field_structure_s.f_float, t2.field_structure_s.f_float, places=5)

    def test_structure_v_roundtrip(self):
        v1 = Test_StructureV()
        v1.f_bool = True
        v1.f_uint_8 = 255
        v1.f_string = "test"

        blob = v1.encode()
        v2 = Test_StructureV.decode(blob)

        self.assertEqual(v1.f_bool, v2.f_bool)
        self.assertEqual(v1.f_uint_8, v2.f_uint_8)
        self.assertEqual(v1.f_string, v2.f_string)


class TestContainerEncodeDecode(unittest.TestCase):
    """Test container encode/decode roundtrip."""

    def test_optional_nil_roundtrip(self):
        opt1 = Optional_uint8()
        blob = opt1.encode()
        opt2 = Optional_uint8.decode(blob)
        self.assertTrue(opt2.is_nil())

    def test_optional_value_roundtrip(self):
        opt1 = Optional_uint8(42)
        blob = opt1.encode()
        opt2 = Optional_uint8.decode(blob)
        self.assertFalse(opt2.is_nil())
        self.assertEqual(opt2.unwrap(), 42)

    def test_vector_roundtrip(self):
        v1 = Vector_uint8([1, 2, 3, 4, 5])
        blob = v1.encode()
        v2 = Vector_uint8.decode(blob)
        self.assertEqual(list(v1), list(v2))

    def test_set_roundtrip(self):
        s1 = Set_uint8([1, 2, 3])
        blob = s1.encode()
        s2 = Set_uint8.decode(blob)
        self.assertEqual(len(s1), len(s2))
        for x in s1:
            self.assertIn(x, s2)

    def test_map_roundtrip(self):
        m1 = Map_int8_to_string({1: "one", 2: "two", 3: "three"})
        blob = m1.encode()
        m2 = Map_int8_to_string.decode(blob)
        self.assertEqual(m1[1], m2[1])
        self.assertEqual(m1[2], m2[2])
        self.assertEqual(m1[3], m2[3])


class TestHexdigest(unittest.TestCase):
    """Test hexdigest for content hashing."""

    def test_key_hexdigest(self):
        key = Test_ConceptAKey.create()
        digest = key.hexdigest()
        self.assertIsInstance(digest, str)
        self.assertGreater(len(digest), 0)

    def test_same_key_same_digest(self):
        uuid_str = "12345678-1234-1234-1234-123456789abc"
        key1 = Test_ConceptAKey(uuid_str)
        key2 = Test_ConceptAKey(uuid_str)
        self.assertEqual(key1.hexdigest(), key2.hexdigest())

    def test_different_key_different_digest(self):
        key1 = Test_ConceptAKey.create()
        key2 = Test_ConceptAKey.create()
        self.assertNotEqual(key1.hexdigest(), key2.hexdigest())

    def test_structure_hexdigest(self):
        s = Test_StructureS({"f_float": 1.0, "f_string": "test"})
        digest = s.hexdigest()
        self.assertIsInstance(digest, str)
        self.assertGreater(len(digest), 0)

    def test_same_structure_same_digest(self):
        s1 = Test_StructureS({"f_float": 1.0, "f_string": "test"})
        s2 = Test_StructureS({"f_float": 1.0, "f_string": "test"})
        self.assertEqual(s1.hexdigest(), s2.hexdigest())


class TestStreamCodecOptions(unittest.TestCase):
    """Test different stream codec instancing options."""

    def test_binary_codec(self):
        s1 = Test_StructureS({"f_float": 1.5, "f_string": "binary"})
        blob = s1.encode(stream_codec_instancing=dsviper.Codec.STREAM_BINARY)
        s2 = Test_StructureS.decode(blob, stream_codec_instancing=dsviper.Codec.STREAM_BINARY)
        self.assertEqual(s1.f_string, s2.f_string)

    def test_raw_codec(self):
        s1 = Test_StructureS({"f_float": 1.5, "f_string": "raw"})
        blob = s1.encode(stream_codec_instancing=dsviper.Codec.STREAM_RAW)
        s2 = Test_StructureS.decode(blob, stream_codec_instancing=dsviper.Codec.STREAM_RAW)
        self.assertEqual(s1.f_string, s2.f_string)


class TestPackSized(unittest.TestCase):
    """Test pack_sized option for structures."""

    def test_structure_pack_sized(self):
        s1 = Test_StructureS({"f_float": 2.5, "f_string": "pack"})
        blob = s1.encode()
        s2 = Test_StructureS.decode(blob, pack_sized=False)
        self.assertEqual(s1.f_string, s2.f_string)


class TestVprValueEncode(unittest.TestCase):
    """Test that vpr_value can be encoded directly."""

    def test_key_vpr_value_encode(self):
        key = Test_ConceptAKey.create()
        vpr = key.vpr_value
        blob = dsviper.Value.encode(vpr)
        self.assertIsInstance(blob, dsviper.ValueBlob)


class TestBlobContent(unittest.TestCase):
    """Test blob content properties."""

    def test_blob_is_not_empty(self):
        key = Test_ConceptAKey.create()
        blob = key.encode()
        self.assertGreater(len(blob), 0)

    def test_blob_content_differs_by_value(self):
        key1 = Test_ConceptAKey.create()
        key2 = Test_ConceptAKey.create()
        blob1 = key1.encode()
        blob2 = key2.encode()
        self.assertNotEqual(bytes(blob1), bytes(blob2))


if __name__ == "__main__":
    unittest.main()
