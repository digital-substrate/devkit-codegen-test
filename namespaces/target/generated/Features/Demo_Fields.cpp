// unité Demo — l'implémentation de l'adressage de ses champs.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/features/Features.dsm.json by kibo-2.0.0.jar

#include "Demo_Fields.hpp"

namespace Demo::Fields::StructureS {

std::shared_ptr<Viper::Path const> const & f_floatPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_float})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_stringPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_string})};
    return instance;
}

} // namespace Demo::Fields::StructureS

namespace Demo::Fields::StructureT {

std::shared_ptr<Viper::Path const> const & field_stringPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{field_string})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & field_structure_sPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{field_structure_s})};
    return instance;
}

} // namespace Demo::Fields::StructureT

namespace Demo::Fields::StructureU {

std::shared_ptr<Viper::Path const> const & f_boolPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_bool})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_uint8Path() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_uint8})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_uint16Path() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_uint16})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_uint32Path() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_uint32})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_uint64Path() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_uint64})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_int8Path() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_int8})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_int16Path() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_int16})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_int32Path() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_int32})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_int64Path() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_int64})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_floatPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_float})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_doublePath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_double})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_blob_idPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_blob_id})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_commit_idPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_commit_id})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_uuidPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_uuid})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_stringPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_string})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_blobPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_blob})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_vecPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_vec})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_matPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_mat})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_tuplePath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_tuple})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_optionalPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_optional})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_vectorPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_vector})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_setPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_set})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_set_sPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_set_s})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_map_s1Path() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_map_s1})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_map_s2Path() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_map_s2})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_xarrayPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_xarray})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_xarray_sPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_xarray_s})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_map_vsPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_map_vs})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_variantPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_variant})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_anyPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_any})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_EPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_E})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_SPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_S})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_TPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_T})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_APath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_A})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_BPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_B})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_CPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_C})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_DPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_D})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_KlubPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_Klub})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_any_conceptPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_any_concept})};
    return instance;
}

} // namespace Demo::Fields::StructureU

namespace Demo::Fields::StructureV {

std::shared_ptr<Viper::Path const> const & f_boolPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_bool})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_uint8Path() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_uint8})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_uint16Path() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_uint16})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_uint32Path() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_uint32})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_uint64Path() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_uint64})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_int8Path() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_int8})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_int16Path() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_int16})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_int32Path() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_int32})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_int64Path() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_int64})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_floatPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_float})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_doublePath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_double})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_uuidPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_uuid})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_stringPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_string})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_vecPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_vec})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_matPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_mat})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_tuplePath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_tuple})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_optionalPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_optional})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_vectorPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_vector})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_setPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_set})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_mapPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_map})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_EPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_E})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_SPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_S})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_TPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_T})};
    return instance;
}

} // namespace Demo::Fields::StructureV

namespace Demo::Fields::StructureW {

std::shared_ptr<Viper::Path const> const & f_singlePath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_single})};
    return instance;
}

} // namespace Demo::Fields::StructureW