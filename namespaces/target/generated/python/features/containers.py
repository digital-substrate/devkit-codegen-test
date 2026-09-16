# Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/features/Features.dsm.json by kibo-2.0.0.jar

"""Features — les conteneurs que le modèle mentionne, nommés et constructibles."""

from __future__ import annotations

import functools

import dsviper

from ._codegen import mapping_of, ordered_of, sequence_of
from . import demo

# ── les descripteurs de type, chaînés par forme ──
#
# Chaque forme compose celui de ses éléments, donc la chaîne s'arrête sur un primitif ou sur un
# type qu'une unité déclare. Mémoïsés : le runtime rend un objet neuf à chaque appel, et deux
# descripteurs égaux mais distincts feraient échouer la comparaison d'une construction.

type_bool = lambda: dsviper.TypeBool()
type_uint8 = lambda: dsviper.TypeUInt8()
type_uint16 = lambda: dsviper.TypeUInt16()
type_uint32 = lambda: dsviper.TypeUInt32()
type_uint64 = lambda: dsviper.TypeUInt64()
type_int8 = lambda: dsviper.TypeInt8()
type_int16 = lambda: dsviper.TypeInt16()
type_int32 = lambda: dsviper.TypeInt32()
type_int64 = lambda: dsviper.TypeInt64()
type_float = lambda: dsviper.TypeFloat()
type_double = lambda: dsviper.TypeDouble()
type_string = lambda: dsviper.TypeString()
type_blob = lambda: dsviper.TypeBlob()
type_blob_id = lambda: dsviper.TypeBlobId()
type_commit_id = lambda: dsviper.TypeCommitId()
type_uuid = lambda: dsviper.TypeUUId()
type_any = lambda: dsviper.TypeAny()
type_AnyConceptKey = lambda: dsviper.TypeKey(dsviper.TypeAnyConcept())
type_Demo_ConceptAKey = demo.ConceptAKey.type
type_Demo_ConceptBKey = demo.ConceptBKey.type
type_Demo_ConceptCoverageKey = demo.ConceptCoverageKey.type
type_Demo_ConceptDKey = demo.ConceptDKey.type
type_Demo_ConceptCKey = demo.ConceptCKey.type
type_Demo_EmptyKlubKey = demo.EmptyKlubKey.type
type_Demo_KlubKey = demo.KlubKey.type
type_Demo_EnumerationE = demo.EnumerationE.type
type_Demo_StructureS = demo.StructureS.type
type_Demo_StructureT = demo.StructureT.type
type_Demo_StructureU = demo.StructureU.type
type_Demo_StructureV = demo.StructureV.type
type_Demo_StructureW = demo.StructureW.type

@functools.cache
def type_vec2_uint8(): return dsviper.TypeVec(type_uint8(), 2)
@functools.cache
def type_mat2x2_uint8(): return dsviper.TypeMat(type_uint8(), 2, 2)
@functools.cache
def type_mat2x3_uint8(): return dsviper.TypeMat(type_uint8(), 2, 3)
@functools.cache
def type_tuple_uint8_string(): return dsviper.TypeTuple([type_uint8(), type_string()])
@functools.cache
def type_optional_AnyConceptKey(): return dsviper.TypeOptional(type_AnyConceptKey())
@functools.cache
def type_optional_Demo_ConceptAKey(): return dsviper.TypeOptional(type_Demo_ConceptAKey())
@functools.cache
def type_optional_Demo_ConceptBKey(): return dsviper.TypeOptional(type_Demo_ConceptBKey())
@functools.cache
def type_optional_Demo_ConceptCKey(): return dsviper.TypeOptional(type_Demo_ConceptCKey())
@functools.cache
def type_optional_Demo_ConceptCoverageKey(): return dsviper.TypeOptional(type_Demo_ConceptCoverageKey())
@functools.cache
def type_optional_Demo_ConceptDKey(): return dsviper.TypeOptional(type_Demo_ConceptDKey())
@functools.cache
def type_optional_Demo_EmptyKlubKey(): return dsviper.TypeOptional(type_Demo_EmptyKlubKey())
@functools.cache
def type_optional_Demo_EnumerationE(): return dsviper.TypeOptional(type_Demo_EnumerationE())
@functools.cache
def type_optional_Demo_KlubKey(): return dsviper.TypeOptional(type_Demo_KlubKey())
@functools.cache
def type_optional_Demo_StructureT(): return dsviper.TypeOptional(type_Demo_StructureT())
@functools.cache
def type_optional_Demo_StructureU(): return dsviper.TypeOptional(type_Demo_StructureU())
@functools.cache
def type_optional_Demo_StructureV(): return dsviper.TypeOptional(type_Demo_StructureV())
@functools.cache
def type_optional_Demo_StructureW(): return dsviper.TypeOptional(type_Demo_StructureW())
@functools.cache
def type_optional_any(): return dsviper.TypeOptional(type_any())
@functools.cache
def type_optional_blob(): return dsviper.TypeOptional(type_blob())
@functools.cache
def type_optional_blob_id(): return dsviper.TypeOptional(type_blob_id())
@functools.cache
def type_optional_commit_id(): return dsviper.TypeOptional(type_commit_id())
@functools.cache
def type_optional_uuid(): return dsviper.TypeOptional(type_uuid())
@functools.cache
def type_optional_xarray_int8(): return dsviper.TypeOptional(type_xarray_int8())
@functools.cache
def type_optional_xarray_uint8(): return dsviper.TypeOptional(type_xarray_uint8())
@functools.cache
def type_optional_bool(): return dsviper.TypeOptional(type_bool())
@functools.cache
def type_optional_double(): return dsviper.TypeOptional(type_double())
@functools.cache
def type_optional_float(): return dsviper.TypeOptional(type_float())
@functools.cache
def type_optional_mat2x2_uint8(): return dsviper.TypeOptional(type_mat2x2_uint8())
@functools.cache
def type_optional_vec2_uint8(): return dsviper.TypeOptional(type_vec2_uint8())
@functools.cache
def type_optional_int16(): return dsviper.TypeOptional(type_int16())
@functools.cache
def type_optional_int32(): return dsviper.TypeOptional(type_int32())
@functools.cache
def type_optional_int64(): return dsviper.TypeOptional(type_int64())
@functools.cache
def type_optional_int8(): return dsviper.TypeOptional(type_int8())
@functools.cache
def type_optional_map_int8_to_string(): return dsviper.TypeOptional(type_map_int8_to_string())
@functools.cache
def type_optional_map_uint8_to_string(): return dsviper.TypeOptional(type_map_uint8_to_string())
@functools.cache
def type_optional_optional_uint8(): return dsviper.TypeOptional(type_optional_uint8())
@functools.cache
def type_optional_set_int8(): return dsviper.TypeOptional(type_set_int8())
@functools.cache
def type_optional_set_uint8(): return dsviper.TypeOptional(type_set_uint8())
@functools.cache
def type_optional_string(): return dsviper.TypeOptional(type_string())
@functools.cache
def type_optional_tuple_uint8_string(): return dsviper.TypeOptional(type_tuple_uint8_string())
@functools.cache
def type_optional_uint16(): return dsviper.TypeOptional(type_uint16())
@functools.cache
def type_optional_uint32(): return dsviper.TypeOptional(type_uint32())
@functools.cache
def type_optional_uint64(): return dsviper.TypeOptional(type_uint64())
@functools.cache
def type_optional_uint8(): return dsviper.TypeOptional(type_uint8())
@functools.cache
def type_optional_variant_string_uint8(): return dsviper.TypeOptional(type_variant_string_uint8())
@functools.cache
def type_optional_vector_uint8(): return dsviper.TypeOptional(type_vector_uint8())
@functools.cache
def type_vector_Demo_StructureS(): return dsviper.TypeVector(type_Demo_StructureS())
@functools.cache
def type_vector_int8(): return dsviper.TypeVector(type_int8())
@functools.cache
def type_vector_uint8(): return dsviper.TypeVector(type_uint8())
@functools.cache
def type_set_AnyConceptKey(): return dsviper.TypeSet(type_AnyConceptKey())
@functools.cache
def type_set_Demo_ConceptAKey(): return dsviper.TypeSet(type_Demo_ConceptAKey())
@functools.cache
def type_set_Demo_ConceptBKey(): return dsviper.TypeSet(type_Demo_ConceptBKey())
@functools.cache
def type_set_Demo_ConceptCKey(): return dsviper.TypeSet(type_Demo_ConceptCKey())
@functools.cache
def type_set_Demo_ConceptCoverageKey(): return dsviper.TypeSet(type_Demo_ConceptCoverageKey())
@functools.cache
def type_set_Demo_KlubKey(): return dsviper.TypeSet(type_Demo_KlubKey())
@functools.cache
def type_set_Demo_StructureS(): return dsviper.TypeSet(type_Demo_StructureS())
@functools.cache
def type_set_int8(): return dsviper.TypeSet(type_int8())
@functools.cache
def type_set_string(): return dsviper.TypeSet(type_string())
@functools.cache
def type_set_uint8(): return dsviper.TypeSet(type_uint8())
@functools.cache
def type_set_vector_Demo_StructureS(): return dsviper.TypeSet(type_vector_Demo_StructureS())
@functools.cache
def type_map_Demo_StructureS_to_string(): return dsviper.TypeMap(type_Demo_StructureS(), type_string())
@functools.cache
def type_map_int8_to_string(): return dsviper.TypeMap(type_int8(), type_string())
@functools.cache
def type_map_string_to_Demo_StructureS(): return dsviper.TypeMap(type_string(), type_Demo_StructureS())
@functools.cache
def type_map_uint8_to_string(): return dsviper.TypeMap(type_uint8(), type_string())
@functools.cache
def type_map_vector_Demo_StructureS_to_string(): return dsviper.TypeMap(type_vector_Demo_StructureS(), type_string())
@functools.cache
def type_xarray_Demo_StructureS(): return dsviper.TypeXArray(type_Demo_StructureS())
@functools.cache
def type_xarray_int8(): return dsviper.TypeXArray(type_int8())
@functools.cache
def type_xarray_uint8(): return dsviper.TypeXArray(type_uint8())
@functools.cache
def type_variant_string_uint8_Demo_StructureS(): return dsviper.TypeVariant([type_string(), type_uint8(), type_Demo_StructureS()])
@functools.cache
def type_variant_string_uint8(): return dsviper.TypeVariant([type_string(), type_uint8()])

# ── et le nom de chaque forme ──

Vec_uint8_2 = sequence_of(type_vec2_uint8)
Mat_uint8_2_2 = sequence_of(type_mat2x2_uint8)
Mat_uint8_2_3 = sequence_of(type_mat2x3_uint8)
Tuple_uint8_string = sequence_of(type_tuple_uint8_string)
Optional_AnyConceptKey = sequence_of(type_optional_AnyConceptKey)
Optional_Demo_ConceptAKey = sequence_of(type_optional_Demo_ConceptAKey)
Optional_Demo_ConceptBKey = sequence_of(type_optional_Demo_ConceptBKey)
Optional_Demo_ConceptCKey = sequence_of(type_optional_Demo_ConceptCKey)
Optional_Demo_ConceptCoverageKey = sequence_of(type_optional_Demo_ConceptCoverageKey)
Optional_Demo_ConceptDKey = sequence_of(type_optional_Demo_ConceptDKey)
Optional_Demo_EmptyKlubKey = sequence_of(type_optional_Demo_EmptyKlubKey)
Optional_Demo_EnumerationE = sequence_of(type_optional_Demo_EnumerationE)
Optional_Demo_KlubKey = sequence_of(type_optional_Demo_KlubKey)
Optional_Demo_StructureT = sequence_of(type_optional_Demo_StructureT)
Optional_Demo_StructureU = sequence_of(type_optional_Demo_StructureU)
Optional_Demo_StructureV = sequence_of(type_optional_Demo_StructureV)
Optional_Demo_StructureW = sequence_of(type_optional_Demo_StructureW)
Optional_Any = sequence_of(type_optional_any)
Optional_blob = sequence_of(type_optional_blob)
Optional_blob_id = sequence_of(type_optional_blob_id)
Optional_commit_id = sequence_of(type_optional_commit_id)
Optional_uuid = sequence_of(type_optional_uuid)
Optional_XArray_int8 = sequence_of(type_optional_xarray_int8)
Optional_XArray_uint8 = sequence_of(type_optional_xarray_uint8)
Optional_bool = sequence_of(type_optional_bool)
Optional_double = sequence_of(type_optional_double)
Optional_float = sequence_of(type_optional_float)
Optional_Mat_uint8_2_2 = sequence_of(type_optional_mat2x2_uint8)
Optional_Vec_uint8_2 = sequence_of(type_optional_vec2_uint8)
Optional_int16 = sequence_of(type_optional_int16)
Optional_int32 = sequence_of(type_optional_int32)
Optional_int64 = sequence_of(type_optional_int64)
Optional_int8 = sequence_of(type_optional_int8)
Optional_Map_int8_to_string = sequence_of(type_optional_map_int8_to_string)
Optional_Map_uint8_to_string = sequence_of(type_optional_map_uint8_to_string)
Optional_Optional_uint8 = sequence_of(type_optional_optional_uint8)
Optional_Set_int8 = sequence_of(type_optional_set_int8)
Optional_Set_uint8 = sequence_of(type_optional_set_uint8)
Optional_string = sequence_of(type_optional_string)
Optional_Tuple_uint8_string = sequence_of(type_optional_tuple_uint8_string)
Optional_uint16 = sequence_of(type_optional_uint16)
Optional_uint32 = sequence_of(type_optional_uint32)
Optional_uint64 = sequence_of(type_optional_uint64)
Optional_uint8 = sequence_of(type_optional_uint8)
Optional_Variant_string_uint8 = sequence_of(type_optional_variant_string_uint8)
Optional_Vector_uint8 = sequence_of(type_optional_vector_uint8)
Vector_Demo_StructureS = sequence_of(type_vector_Demo_StructureS)
Vector_int8 = sequence_of(type_vector_int8)
Vector_uint8 = sequence_of(type_vector_uint8)
Set_AnyConceptKey = sequence_of(type_set_AnyConceptKey)
Set_Demo_ConceptAKey = sequence_of(type_set_Demo_ConceptAKey)
Set_Demo_ConceptBKey = sequence_of(type_set_Demo_ConceptBKey)
Set_Demo_ConceptCKey = sequence_of(type_set_Demo_ConceptCKey)
Set_Demo_ConceptCoverageKey = sequence_of(type_set_Demo_ConceptCoverageKey)
Set_Demo_KlubKey = sequence_of(type_set_Demo_KlubKey)
Set_Demo_StructureS = sequence_of(type_set_Demo_StructureS)
Set_int8 = sequence_of(type_set_int8)
Set_string = sequence_of(type_set_string)
Set_uint8 = sequence_of(type_set_uint8)
Set_Vector_Demo_StructureS = sequence_of(type_set_vector_Demo_StructureS)
Map_Demo_StructureS_to_string = mapping_of(type_map_Demo_StructureS_to_string)
Map_int8_to_string = mapping_of(type_map_int8_to_string)
Map_string_to_Demo_StructureS = mapping_of(type_map_string_to_Demo_StructureS)
Map_uint8_to_string = mapping_of(type_map_uint8_to_string)
Map_Vector_Demo_StructureS_to_string = mapping_of(type_map_vector_Demo_StructureS_to_string)
XArray_Demo_StructureS = ordered_of(type_xarray_Demo_StructureS)
XArray_int8 = ordered_of(type_xarray_int8)
XArray_uint8 = ordered_of(type_xarray_uint8)
Variant_string_uint8_Demo_StructureS = sequence_of(type_variant_string_uint8_Demo_StructureS)
Variant_string_uint8 = sequence_of(type_variant_string_uint8)