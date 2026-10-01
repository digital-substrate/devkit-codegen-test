# Copyright (c) Digital Substrate 2026, All rights reserved.
"""Tests for Kibo-generated encode/decode serialization."""

import unittest
import dsviper
from features.demo import ConceptAKey, ConceptBKey, StructureS, StructureT, StructureU, StructureV
from features.containers import Optional_of_uint8, Vector_of_uint8, Set_of_uint8, Map_of_int8_to_string
from features import AnyConceptKey, definitions


class TestKeyEncodeDecode(unittest.TestCase):
    """Test key encode/decode roundtrip."""

    def test_concept_a_key_roundtrip(self):
        key1 = ConceptAKey.create()
        blob = dsviper.Value.encode(key1.vpr_value)
        key2 = ConceptAKey(dsviper.Value.decode(blob, ConceptAKey.type(), definitions()))
        self.assertEqual(key1, key2)

    def test_concept_b_key_roundtrip(self):
        key1 = ConceptBKey.create()
        blob = dsviper.Value.encode(key1.vpr_value)
        key2 = ConceptBKey(dsviper.Value.decode(blob, ConceptBKey.type(), definitions()))
        self.assertEqual(key1, key2)

    def test_any_concept_key_roundtrip(self):
        key = ConceptAKey.create()
        any_key1 = key.to_any_concept_key()
        blob = dsviper.Value.encode(any_key1.vpr_value)
        any_key2 = AnyConceptKey(dsviper.Value.decode(blob, AnyConceptKey.type(), definitions()))
        self.assertEqual(any_key1, any_key2)


class TestStructureEncodeDecode(unittest.TestCase):
    """Test structure encode/decode roundtrip."""

    def test_structure_s_roundtrip(self):
        s1 = StructureS({"f_float": 3.14, "f_string": "hello"})
        blob = dsviper.Value.encode(s1.vpr_value)
        s2 = StructureS(dsviper.Value.decode(blob, StructureS.type(), definitions()))
        self.assertAlmostEqual(s1.f_float, s2.f_float, places=5)
        self.assertEqual(s1.f_string, s2.f_string)

    def test_structure_t_roundtrip(self):
        inner = StructureS({"f_float": 1.5, "f_string": "inner"})
        t1 = StructureT()
        t1.field_string = "outer"
        t1.field_structure_s = inner

        blob = dsviper.Value.encode(t1.vpr_value)
        t2 = StructureT(dsviper.Value.decode(blob, StructureT.type(), definitions()))

        self.assertEqual(t1.field_string, t2.field_string)
        self.assertAlmostEqual(t1.field_structure_s.f_float, t2.field_structure_s.f_float, places=5)

    def test_structure_v_roundtrip(self):
        v1 = StructureV()
        v1.f_bool = True
        v1.f_uint8 = 255
        v1.f_string = "test"

        blob = dsviper.Value.encode(v1.vpr_value)
        v2 = StructureV(dsviper.Value.decode(blob, StructureV.type(), definitions()))

        self.assertEqual(v1.f_bool, v2.f_bool)
        self.assertEqual(v1.f_uint8, v2.f_uint8)
        self.assertEqual(v1.f_string, v2.f_string)


class TestContainerEncodeDecode(unittest.TestCase):
    """Test container encode/decode roundtrip."""

    def test_optional_nil_roundtrip(self):
        opt1 = Optional_of_uint8()
        blob = dsviper.Value.encode(opt1.vpr_value)
        opt2 = Optional_of_uint8(dsviper.Value.decode(blob, Optional_of_uint8.type(), definitions()))
        self.assertTrue(opt2.is_nil())

    def test_optional_value_roundtrip(self):
        opt1 = Optional_of_uint8(42)
        blob = dsviper.Value.encode(opt1.vpr_value)
        opt2 = Optional_of_uint8(dsviper.Value.decode(blob, Optional_of_uint8.type(), definitions()))
        self.assertFalse(opt2.is_nil())
        self.assertEqual(opt2.unwrap(), 42)

    def test_vector_roundtrip(self):
        v1 = Vector_of_uint8([1, 2, 3, 4, 5])
        blob = dsviper.Value.encode(v1.vpr_value)
        v2 = Vector_of_uint8(dsviper.Value.decode(blob, Vector_of_uint8.type(), definitions()))
        self.assertEqual(list(v1), list(v2))

    def test_set_roundtrip(self):
        s1 = Set_of_uint8([1, 2, 3])
        blob = dsviper.Value.encode(s1.vpr_value)
        s2 = Set_of_uint8(dsviper.Value.decode(blob, Set_of_uint8.type(), definitions()))
        self.assertEqual(len(s1), len(s2))
        for x in s1:
            self.assertIn(x, s2)

    def test_map_roundtrip(self):
        m1 = Map_of_int8_to_string({1: "one", 2: "two", 3: "three"})
        blob = dsviper.Value.encode(m1.vpr_value)
        m2 = Map_of_int8_to_string(dsviper.Value.decode(blob, Map_of_int8_to_string.type(), definitions()))
        self.assertEqual(m1[1], m2[1])
        self.assertEqual(m1[2], m2[2])
        self.assertEqual(m1[3], m2[3])


class TestHexdigest(unittest.TestCase):
    """Test hexdigest for content hashing."""

    def test_key_hexdigest(self):
        key = ConceptAKey.create()
        digest = dsviper.Value.hexdigest(key.vpr_value)
        self.assertIsInstance(digest, str)
        self.assertGreater(len(digest), 0)

    def test_same_key_same_digest(self):
        uuid_str = "12345678-1234-1234-1234-123456789abc"
        key1 = ConceptAKey(uuid_str)
        key2 = ConceptAKey(uuid_str)
        self.assertEqual(dsviper.Value.hexdigest(key1.vpr_value), dsviper.Value.hexdigest(key2.vpr_value))

    def test_different_key_different_digest(self):
        key1 = ConceptAKey.create()
        key2 = ConceptAKey.create()
        self.assertNotEqual(dsviper.Value.hexdigest(key1.vpr_value), dsviper.Value.hexdigest(key2.vpr_value))

    def test_structure_hexdigest(self):
        s = StructureS({"f_float": 1.0, "f_string": "test"})
        digest = dsviper.Value.hexdigest(s.vpr_value)
        self.assertIsInstance(digest, str)
        self.assertGreater(len(digest), 0)

    def test_same_structure_same_digest(self):
        s1 = StructureS({"f_float": 1.0, "f_string": "test"})
        s2 = StructureS({"f_float": 1.0, "f_string": "test"})
        self.assertEqual(dsviper.Value.hexdigest(s1.vpr_value), dsviper.Value.hexdigest(s2.vpr_value))


class TestStreamCodecOptions(unittest.TestCase):
    """Test different stream codec instancing options."""

    def test_binary_codec(self):
        s1 = StructureS({"f_float": 1.5, "f_string": "binary"})
        blob = dsviper.Value.encode(s1.vpr_value, stream_codec_instancing=dsviper.Codec.STREAM_BINARY)
        s2 = StructureS(dsviper.Value.decode(blob, StructureS.type(), definitions(), stream_codec_instancing=dsviper.Codec.STREAM_BINARY))
        self.assertEqual(s1.f_string, s2.f_string)

    def test_raw_codec(self):
        s1 = StructureS({"f_float": 1.5, "f_string": "raw"})
        blob = dsviper.Value.encode(s1.vpr_value, stream_codec_instancing=dsviper.Codec.STREAM_RAW)
        s2 = StructureS(dsviper.Value.decode(blob, StructureS.type(), definitions(), stream_codec_instancing=dsviper.Codec.STREAM_RAW))
        self.assertEqual(s1.f_string, s2.f_string)


class TestPackSized(unittest.TestCase):
    """Test pack_sized option for structures."""

    def test_structure_pack_sized(self):
        s1 = StructureS({"f_float": 2.5, "f_string": "pack"})
        blob = dsviper.Value.encode(s1.vpr_value)
        s2 = StructureS(dsviper.Value.decode(blob, StructureS.type(), definitions(), pack_sized=False))
        self.assertEqual(s1.f_string, s2.f_string)


class TestVprValueEncode(unittest.TestCase):
    """Test that vpr_value can be encoded directly."""

    def test_key_vpr_value_encode(self):
        key = ConceptAKey.create()
        vpr = key.vpr_value
        blob = dsviper.Value.encode(vpr)
        self.assertIsInstance(blob, dsviper.ValueBlob)


class TestBlobContent(unittest.TestCase):
    """Test blob content properties."""

    def test_blob_is_not_empty(self):
        key = ConceptAKey.create()
        blob = dsviper.Value.encode(key.vpr_value)
        self.assertGreater(len(blob), 0)

    def test_blob_content_differs_by_value(self):
        key1 = ConceptAKey.create()
        key2 = ConceptAKey.create()
        blob1 = dsviper.Value.encode(key1.vpr_value)
        blob2 = dsviper.Value.encode(key2.vpr_value)
        self.assertNotEqual(bytes(blob1), bytes(blob2))


if __name__ == "__main__":
    unittest.main()
