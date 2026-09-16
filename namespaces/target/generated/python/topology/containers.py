# Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

"""Topology — les conteneurs que le modèle mentionne, nommés et constructibles."""

from __future__ import annotations

import functools

import dsviper

from ._codegen import mapping_of, ordered_of, sequence_of
from . import model_a
from . import model_c
from . import model_b
from . import projection
from . import annotations

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
type_ModelA_MaterialKey = model_a.MaterialKey.type
type_ModelA_Finish = model_a.Finish.type
type_ModelA_Colour = model_a.Colour.type
type_ModelC_MarkerKey = model_c.MarkerKey.type

type_ModelB_MaterialKey = model_b.MaterialKey.type
type_ModelB_Colour = model_b.Colour.type
type_Projection_LinkKey = projection.LinkKey.type
type_Projection_DerivedMaterialKey = projection.DerivedMaterialKey.type
type_Projection_Pair = projection.Pair.type



@functools.cache
def type_optional_AnyConceptKey(): return dsviper.TypeOptional(type_AnyConceptKey())
@functools.cache
def type_optional_ModelA_Colour(): return dsviper.TypeOptional(type_ModelA_Colour())
@functools.cache
def type_optional_ModelA_MaterialKey(): return dsviper.TypeOptional(type_ModelA_MaterialKey())
@functools.cache
def type_optional_ModelB_Colour(): return dsviper.TypeOptional(type_ModelB_Colour())
@functools.cache
def type_optional_ModelB_MaterialKey(): return dsviper.TypeOptional(type_ModelB_MaterialKey())
@functools.cache
def type_optional_ModelC_MarkerKey(): return dsviper.TypeOptional(type_ModelC_MarkerKey())
@functools.cache
def type_optional_Projection_DerivedMaterialKey(): return dsviper.TypeOptional(type_Projection_DerivedMaterialKey())
@functools.cache
def type_optional_Projection_LinkKey(): return dsviper.TypeOptional(type_Projection_LinkKey())
@functools.cache
def type_optional_Projection_Pair(): return dsviper.TypeOptional(type_Projection_Pair())
@functools.cache
def type_optional_map_ModelA_MaterialKey_to_ModelB_MaterialKey(): return dsviper.TypeOptional(type_map_ModelA_MaterialKey_to_ModelB_MaterialKey())
@functools.cache
def type_optional_string(): return dsviper.TypeOptional(type_string())
@functools.cache
def type_set_ModelA_MaterialKey(): return dsviper.TypeSet(type_ModelA_MaterialKey())
@functools.cache
def type_set_ModelB_MaterialKey(): return dsviper.TypeSet(type_ModelB_MaterialKey())
@functools.cache
def type_set_Projection_LinkKey(): return dsviper.TypeSet(type_Projection_LinkKey())
@functools.cache
def type_map_ModelA_MaterialKey_to_ModelB_MaterialKey(): return dsviper.TypeMap(type_ModelA_MaterialKey(), type_ModelB_MaterialKey())

# ── et le nom de chaque forme ──

Optional_AnyConceptKey = sequence_of(type_optional_AnyConceptKey)
Optional_ModelA_Colour = sequence_of(type_optional_ModelA_Colour)
Optional_ModelA_MaterialKey = sequence_of(type_optional_ModelA_MaterialKey)
Optional_ModelB_Colour = sequence_of(type_optional_ModelB_Colour)
Optional_ModelB_MaterialKey = sequence_of(type_optional_ModelB_MaterialKey)
Optional_ModelC_MarkerKey = sequence_of(type_optional_ModelC_MarkerKey)
Optional_Projection_DerivedMaterialKey = sequence_of(type_optional_Projection_DerivedMaterialKey)
Optional_Projection_LinkKey = sequence_of(type_optional_Projection_LinkKey)
Optional_Projection_Pair = sequence_of(type_optional_Projection_Pair)
Optional_Map_ModelA_MaterialKey_to_ModelB_MaterialKey = sequence_of(type_optional_map_ModelA_MaterialKey_to_ModelB_MaterialKey)
Optional_string = sequence_of(type_optional_string)
Set_ModelA_MaterialKey = sequence_of(type_set_ModelA_MaterialKey)
Set_ModelB_MaterialKey = sequence_of(type_set_ModelB_MaterialKey)
Set_Projection_LinkKey = sequence_of(type_set_Projection_LinkKey)
Map_ModelA_MaterialKey_to_ModelB_MaterialKey = mapping_of(type_map_ModelA_MaterialKey_to_ModelB_MaterialKey)
