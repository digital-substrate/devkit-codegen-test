// unité Core — l'implémentation de l'adressage de ses champs.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

#include "Core_Fields.hpp"

namespace Core::Fields::Bag {

std::shared_ptr<Viper::Path const> const & membersPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{members})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & tintsPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{tints})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & trailPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{trail})};
    return instance;
}

} // namespace Core::Fields::Bag

namespace Core::Fields::Colour {

std::shared_ptr<Viper::Path const> const & rPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{r})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & gPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{g})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & bPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{b})};
    return instance;
}

} // namespace Core::Fields::Colour

namespace Core::Fields::Defaults {

std::shared_ptr<Viper::Path const> const & f_uint8Path() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_uint8})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_floatPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_float})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_stringPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_string})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_uuidPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_uuid})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_vecPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_vec})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_gradePath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_grade})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & f_colourPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_colour})};
    return instance;
}

} // namespace Core::Fields::Defaults

namespace Core::Fields::Scalars {

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

std::shared_ptr<Viper::Path const> const & f_anyPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_any})};
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

} // namespace Core::Fields::Scalars

namespace Core::Fields::Single {

std::shared_ptr<Viper::Path const> const & f_singlePath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{f_single})};
    return instance;
}

} // namespace Core::Fields::Single