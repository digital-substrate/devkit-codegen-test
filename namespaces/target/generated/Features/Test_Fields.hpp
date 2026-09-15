// unité Test — comment nommer et adresser les champs de ses structures.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/features/Features.dsm.json by kibo-2.0.0.jar
//
// No cross-unit include, whatever this namespace's structures hold: a path names a
// position, not a type. Its types header includes the units it reaches; this one reaches
// none.

#ifndef Test_Fields_hpp
#define Test_Fields_hpp

#include "Viper_Path.hpp"

#include <memory>
#include <string>
#include <string_view>

namespace Test::Fields::StructureS {

inline constexpr std::string_view f_float{"f_float"};
inline constexpr std::string_view f_string{"f_string"};

std::shared_ptr<Viper::Path const> const & f_floatPath();
std::shared_ptr<Viper::Path const> const & f_stringPath();

} // namespace Test::Fields::StructureS

namespace Test::Fields::StructureT {

inline constexpr std::string_view field_string{"field_string"};
inline constexpr std::string_view field_structure_s{"field_structure_s"};

std::shared_ptr<Viper::Path const> const & field_stringPath();
std::shared_ptr<Viper::Path const> const & field_structure_sPath();

} // namespace Test::Fields::StructureT

namespace Test::Fields::StructureU {

inline constexpr std::string_view f_bool{"f_bool"};
inline constexpr std::string_view f_uint8{"f_uint8"};
inline constexpr std::string_view f_uint16{"f_uint16"};
inline constexpr std::string_view f_uint32{"f_uint32"};
inline constexpr std::string_view f_uint64{"f_uint64"};
inline constexpr std::string_view f_int8{"f_int8"};
inline constexpr std::string_view f_int16{"f_int16"};
inline constexpr std::string_view f_int32{"f_int32"};
inline constexpr std::string_view f_int64{"f_int64"};
inline constexpr std::string_view f_float{"f_float"};
inline constexpr std::string_view f_double{"f_double"};
inline constexpr std::string_view f_blob_id{"f_blob_id"};
inline constexpr std::string_view f_commit_id{"f_commit_id"};
inline constexpr std::string_view f_uuid{"f_uuid"};
inline constexpr std::string_view f_string{"f_string"};
inline constexpr std::string_view f_blob{"f_blob"};
inline constexpr std::string_view f_vec{"f_vec"};
inline constexpr std::string_view f_mat{"f_mat"};
inline constexpr std::string_view f_tuple{"f_tuple"};
inline constexpr std::string_view f_optional{"f_optional"};
inline constexpr std::string_view f_vector{"f_vector"};
inline constexpr std::string_view f_set{"f_set"};
inline constexpr std::string_view f_set_s{"f_set_s"};
inline constexpr std::string_view f_map_s1{"f_map_s1"};
inline constexpr std::string_view f_map_s2{"f_map_s2"};
inline constexpr std::string_view f_xarray{"f_xarray"};
inline constexpr std::string_view f_xarray_s{"f_xarray_s"};
inline constexpr std::string_view f_map_vs{"f_map_vs"};
inline constexpr std::string_view f_variant{"f_variant"};
inline constexpr std::string_view f_any{"f_any"};
inline constexpr std::string_view f_E{"f_E"};
inline constexpr std::string_view f_S{"f_S"};
inline constexpr std::string_view f_T{"f_T"};
inline constexpr std::string_view f_A{"f_A"};
inline constexpr std::string_view f_B{"f_B"};
inline constexpr std::string_view f_C{"f_C"};
inline constexpr std::string_view f_D{"f_D"};
inline constexpr std::string_view f_Klub{"f_Klub"};
inline constexpr std::string_view f_any_concept{"f_any_concept"};

std::shared_ptr<Viper::Path const> const & f_boolPath();
std::shared_ptr<Viper::Path const> const & f_uint8Path();
std::shared_ptr<Viper::Path const> const & f_uint16Path();
std::shared_ptr<Viper::Path const> const & f_uint32Path();
std::shared_ptr<Viper::Path const> const & f_uint64Path();
std::shared_ptr<Viper::Path const> const & f_int8Path();
std::shared_ptr<Viper::Path const> const & f_int16Path();
std::shared_ptr<Viper::Path const> const & f_int32Path();
std::shared_ptr<Viper::Path const> const & f_int64Path();
std::shared_ptr<Viper::Path const> const & f_floatPath();
std::shared_ptr<Viper::Path const> const & f_doublePath();
std::shared_ptr<Viper::Path const> const & f_blob_idPath();
std::shared_ptr<Viper::Path const> const & f_commit_idPath();
std::shared_ptr<Viper::Path const> const & f_uuidPath();
std::shared_ptr<Viper::Path const> const & f_stringPath();
std::shared_ptr<Viper::Path const> const & f_blobPath();
std::shared_ptr<Viper::Path const> const & f_vecPath();
std::shared_ptr<Viper::Path const> const & f_matPath();
std::shared_ptr<Viper::Path const> const & f_tuplePath();
std::shared_ptr<Viper::Path const> const & f_optionalPath();
std::shared_ptr<Viper::Path const> const & f_vectorPath();
std::shared_ptr<Viper::Path const> const & f_setPath();
std::shared_ptr<Viper::Path const> const & f_set_sPath();
std::shared_ptr<Viper::Path const> const & f_map_s1Path();
std::shared_ptr<Viper::Path const> const & f_map_s2Path();
std::shared_ptr<Viper::Path const> const & f_xarrayPath();
std::shared_ptr<Viper::Path const> const & f_xarray_sPath();
std::shared_ptr<Viper::Path const> const & f_map_vsPath();
std::shared_ptr<Viper::Path const> const & f_variantPath();
std::shared_ptr<Viper::Path const> const & f_anyPath();
std::shared_ptr<Viper::Path const> const & f_EPath();
std::shared_ptr<Viper::Path const> const & f_SPath();
std::shared_ptr<Viper::Path const> const & f_TPath();
std::shared_ptr<Viper::Path const> const & f_APath();
std::shared_ptr<Viper::Path const> const & f_BPath();
std::shared_ptr<Viper::Path const> const & f_CPath();
std::shared_ptr<Viper::Path const> const & f_DPath();
std::shared_ptr<Viper::Path const> const & f_KlubPath();
std::shared_ptr<Viper::Path const> const & f_any_conceptPath();

} // namespace Test::Fields::StructureU

namespace Test::Fields::StructureV {

inline constexpr std::string_view f_bool{"f_bool"};
inline constexpr std::string_view f_uint8{"f_uint8"};
inline constexpr std::string_view f_uint16{"f_uint16"};
inline constexpr std::string_view f_uint32{"f_uint32"};
inline constexpr std::string_view f_uint64{"f_uint64"};
inline constexpr std::string_view f_int8{"f_int8"};
inline constexpr std::string_view f_int16{"f_int16"};
inline constexpr std::string_view f_int32{"f_int32"};
inline constexpr std::string_view f_int64{"f_int64"};
inline constexpr std::string_view f_float{"f_float"};
inline constexpr std::string_view f_double{"f_double"};
inline constexpr std::string_view f_uuid{"f_uuid"};
inline constexpr std::string_view f_string{"f_string"};
inline constexpr std::string_view f_vec{"f_vec"};
inline constexpr std::string_view f_mat{"f_mat"};
inline constexpr std::string_view f_tuple{"f_tuple"};
inline constexpr std::string_view f_optional{"f_optional"};
inline constexpr std::string_view f_vector{"f_vector"};
inline constexpr std::string_view f_set{"f_set"};
inline constexpr std::string_view f_map{"f_map"};
inline constexpr std::string_view f_E{"f_E"};
inline constexpr std::string_view f_S{"f_S"};
inline constexpr std::string_view f_T{"f_T"};

std::shared_ptr<Viper::Path const> const & f_boolPath();
std::shared_ptr<Viper::Path const> const & f_uint8Path();
std::shared_ptr<Viper::Path const> const & f_uint16Path();
std::shared_ptr<Viper::Path const> const & f_uint32Path();
std::shared_ptr<Viper::Path const> const & f_uint64Path();
std::shared_ptr<Viper::Path const> const & f_int8Path();
std::shared_ptr<Viper::Path const> const & f_int16Path();
std::shared_ptr<Viper::Path const> const & f_int32Path();
std::shared_ptr<Viper::Path const> const & f_int64Path();
std::shared_ptr<Viper::Path const> const & f_floatPath();
std::shared_ptr<Viper::Path const> const & f_doublePath();
std::shared_ptr<Viper::Path const> const & f_uuidPath();
std::shared_ptr<Viper::Path const> const & f_stringPath();
std::shared_ptr<Viper::Path const> const & f_vecPath();
std::shared_ptr<Viper::Path const> const & f_matPath();
std::shared_ptr<Viper::Path const> const & f_tuplePath();
std::shared_ptr<Viper::Path const> const & f_optionalPath();
std::shared_ptr<Viper::Path const> const & f_vectorPath();
std::shared_ptr<Viper::Path const> const & f_setPath();
std::shared_ptr<Viper::Path const> const & f_mapPath();
std::shared_ptr<Viper::Path const> const & f_EPath();
std::shared_ptr<Viper::Path const> const & f_SPath();
std::shared_ptr<Viper::Path const> const & f_TPath();

} // namespace Test::Fields::StructureV

namespace Test::Fields::StructureW {

inline constexpr std::string_view f_single{"f_single"};

std::shared_ptr<Viper::Path const> const & f_singlePath();

} // namespace Test::Fields::StructureW

#endif