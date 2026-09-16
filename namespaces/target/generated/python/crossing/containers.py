# Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

"""Crossing — les conteneurs que le modèle mentionne, nommés et constructibles."""

from __future__ import annotations

import functools

import dsviper

from ._codegen import (mapping_of, optional_of, ordered_of, sequence_of,
                       variant_of)
from . import core
from . import parts
from . import woven

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
type_Core_OtherKey = core.OtherKey.type
type_Core_ThingKey = core.ThingKey.type
type_Core_SubThingKey = core.SubThingKey.type
type_Core_KlubKey = core.KlubKey.type
type_Core_Grade = core.Grade.type
type_Core_Bag = core.Bag.type
type_Core_Colour = core.Colour.type
type_Core_Defaults = core.Defaults.type
type_Core_Scalars = core.Scalars.type
type_Core_Single = core.Single.type
type_Parts_ThingKey = parts.ThingKey.type
type_Parts_Grade = parts.Grade.type
type_Parts_Colour = parts.Colour.type
type_Woven_KnotKey = woven.KnotKey.type
type_Woven_DerivedKey = woven.DerivedKey.type
type_Woven_WeaveKey = woven.WeaveKey.type
type_Woven_Composites = woven.Composites.type
type_Woven_Entities = woven.Entities.type
type_Woven_Nested = woven.Nested.type

@functools.cache
def type_vec2_uint8(): return dsviper.TypeVec(type_uint8(), 2)
@functools.cache
def type_mat2x2_uint8(): return dsviper.TypeMat(type_uint8(), 2, 2)
@functools.cache
def type_tuple_Core_Colour_Parts_Colour(): return dsviper.TypeTuple([type_Core_Colour(), type_Parts_Colour()])
@functools.cache
def type_optional_AnyConceptKey(): return dsviper.TypeOptional(type_AnyConceptKey())
@functools.cache
def type_optional_Core_Bag(): return dsviper.TypeOptional(type_Core_Bag())
@functools.cache
def type_optional_Core_Colour(): return dsviper.TypeOptional(type_Core_Colour())
@functools.cache
def type_optional_Core_Grade(): return dsviper.TypeOptional(type_Core_Grade())
@functools.cache
def type_optional_Core_KlubKey(): return dsviper.TypeOptional(type_Core_KlubKey())
@functools.cache
def type_optional_Core_OtherKey(): return dsviper.TypeOptional(type_Core_OtherKey())
@functools.cache
def type_optional_Core_Scalars(): return dsviper.TypeOptional(type_Core_Scalars())
@functools.cache
def type_optional_Core_SubThingKey(): return dsviper.TypeOptional(type_Core_SubThingKey())
@functools.cache
def type_optional_Core_ThingKey(): return dsviper.TypeOptional(type_Core_ThingKey())
@functools.cache
def type_optional_Parts_Colour(): return dsviper.TypeOptional(type_Parts_Colour())
@functools.cache
def type_optional_Parts_ThingKey(): return dsviper.TypeOptional(type_Parts_ThingKey())
@functools.cache
def type_optional_xarray_Core_Colour(): return dsviper.TypeOptional(type_xarray_Core_Colour())
@functools.cache
def type_optional_Woven_Composites(): return dsviper.TypeOptional(type_Woven_Composites())
@functools.cache
def type_optional_Woven_DerivedKey(): return dsviper.TypeOptional(type_Woven_DerivedKey())
@functools.cache
def type_optional_Woven_KnotKey(): return dsviper.TypeOptional(type_Woven_KnotKey())
@functools.cache
def type_optional_Woven_WeaveKey(): return dsviper.TypeOptional(type_Woven_WeaveKey())
@functools.cache
def type_optional_map_Core_Grade_to_Parts_Colour(): return dsviper.TypeOptional(type_map_Core_Grade_to_Parts_Colour())
@functools.cache
def type_optional_map_Core_ThingKey_to_Core_Colour(): return dsviper.TypeOptional(type_map_Core_ThingKey_to_Core_Colour())
@functools.cache
def type_optional_map_Core_ThingKey_to_Parts_ThingKey(): return dsviper.TypeOptional(type_map_Core_ThingKey_to_Parts_ThingKey())
@functools.cache
def type_optional_optional_Core_ThingKey(): return dsviper.TypeOptional(type_optional_Core_ThingKey())
@functools.cache
def type_optional_set_Core_ThingKey(): return dsviper.TypeOptional(type_set_Core_ThingKey())
@functools.cache
def type_optional_tuple_Core_Colour_Parts_Colour(): return dsviper.TypeOptional(type_tuple_Core_Colour_Parts_Colour())
@functools.cache
def type_optional_variant_Core_Colour_Parts_Colour(): return dsviper.TypeOptional(type_variant_Core_Colour_Parts_Colour())
@functools.cache
def type_optional_vector_Parts_Colour(): return dsviper.TypeOptional(type_vector_Parts_Colour())
@functools.cache
def type_vector_Core_Colour(): return dsviper.TypeVector(type_Core_Colour())
@functools.cache
def type_vector_Parts_Colour(): return dsviper.TypeVector(type_Parts_Colour())
@functools.cache
def type_set_Core_Grade(): return dsviper.TypeSet(type_Core_Grade())
@functools.cache
def type_set_Core_ThingKey(): return dsviper.TypeSet(type_Core_ThingKey())
@functools.cache
def type_set_Parts_ThingKey(): return dsviper.TypeSet(type_Parts_ThingKey())
@functools.cache
def type_set_Woven_KnotKey(): return dsviper.TypeSet(type_Woven_KnotKey())
@functools.cache
def type_map_Core_Grade_to_Parts_Colour(): return dsviper.TypeMap(type_Core_Grade(), type_Parts_Colour())
@functools.cache
def type_map_Core_ThingKey_to_Core_Colour(): return dsviper.TypeMap(type_Core_ThingKey(), type_Core_Colour())
@functools.cache
def type_map_Core_ThingKey_to_Parts_ThingKey(): return dsviper.TypeMap(type_Core_ThingKey(), type_Parts_ThingKey())
@functools.cache
def type_xarray_Core_Colour(): return dsviper.TypeXArray(type_Core_Colour())
@functools.cache
def type_variant_Core_Colour_Parts_Colour_string(): return dsviper.TypeVariant([type_Core_Colour(), type_Parts_Colour(), type_string()])
@functools.cache
def type_variant_Core_Colour_Parts_Colour(): return dsviper.TypeVariant([type_Core_Colour(), type_Parts_Colour()])

# ── et le nom de chaque forme ──

Vec_uint8_2 = sequence_of(type_vec2_uint8)
Mat_uint8_2_2 = sequence_of(type_mat2x2_uint8)
Tuple_Core_Colour_Parts_Colour = sequence_of(type_tuple_Core_Colour_Parts_Colour)
Optional_AnyConceptKey = optional_of(type_optional_AnyConceptKey)
Optional_Core_Bag = optional_of(type_optional_Core_Bag)
Optional_Core_Colour = optional_of(type_optional_Core_Colour)
Optional_Core_Grade = optional_of(type_optional_Core_Grade)
Optional_Core_KlubKey = optional_of(type_optional_Core_KlubKey)
Optional_Core_OtherKey = optional_of(type_optional_Core_OtherKey)
Optional_Core_Scalars = optional_of(type_optional_Core_Scalars)
Optional_Core_SubThingKey = optional_of(type_optional_Core_SubThingKey)
Optional_Core_ThingKey = optional_of(type_optional_Core_ThingKey)
Optional_Parts_Colour = optional_of(type_optional_Parts_Colour)
Optional_Parts_ThingKey = optional_of(type_optional_Parts_ThingKey)
Optional_XArray_Core_Colour = optional_of(type_optional_xarray_Core_Colour)
Optional_Woven_Composites = optional_of(type_optional_Woven_Composites)
Optional_Woven_DerivedKey = optional_of(type_optional_Woven_DerivedKey)
Optional_Woven_KnotKey = optional_of(type_optional_Woven_KnotKey)
Optional_Woven_WeaveKey = optional_of(type_optional_Woven_WeaveKey)
Optional_Map_Core_Grade_to_Parts_Colour = optional_of(type_optional_map_Core_Grade_to_Parts_Colour)
Optional_Map_Core_ThingKey_to_Core_Colour = optional_of(type_optional_map_Core_ThingKey_to_Core_Colour)
Optional_Map_Core_ThingKey_to_Parts_ThingKey = optional_of(type_optional_map_Core_ThingKey_to_Parts_ThingKey)
Optional_Optional_Core_ThingKey = optional_of(type_optional_optional_Core_ThingKey)
Optional_Set_Core_ThingKey = optional_of(type_optional_set_Core_ThingKey)
Optional_Tuple_Core_Colour_Parts_Colour = optional_of(type_optional_tuple_Core_Colour_Parts_Colour)
Optional_Variant_Core_Colour_Parts_Colour = optional_of(type_optional_variant_Core_Colour_Parts_Colour)
Optional_Vector_Parts_Colour = optional_of(type_optional_vector_Parts_Colour)
Vector_Core_Colour = sequence_of(type_vector_Core_Colour)
Vector_Parts_Colour = sequence_of(type_vector_Parts_Colour)
Set_Core_Grade = sequence_of(type_set_Core_Grade)
Set_Core_ThingKey = sequence_of(type_set_Core_ThingKey)
Set_Parts_ThingKey = sequence_of(type_set_Parts_ThingKey)
Set_Woven_KnotKey = sequence_of(type_set_Woven_KnotKey)
Map_Core_Grade_to_Parts_Colour = mapping_of(type_map_Core_Grade_to_Parts_Colour)
Map_Core_ThingKey_to_Core_Colour = mapping_of(type_map_Core_ThingKey_to_Core_Colour)
Map_Core_ThingKey_to_Parts_ThingKey = mapping_of(type_map_Core_ThingKey_to_Parts_ThingKey)
XArray_Core_Colour = ordered_of(type_xarray_Core_Colour)
Variant_Core_Colour_Parts_Colour_string = variant_of(type_variant_Core_Colour_Parts_Colour_string)
Variant_Core_Colour_Parts_Colour = variant_of(type_variant_Core_Colour_Parts_Colour)