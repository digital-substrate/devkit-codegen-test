// unité Woven — comment nommer et adresser les champs de ses structures.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar
//
// No cross-unit include, whatever this namespace's structures hold: a path names a
// position, not a type. Its types header includes the units it reaches; this one reaches
// none.

#ifndef Woven_Fields_hpp
#define Woven_Fields_hpp

#include "Viper_Path.hpp"

#include <memory>
#include <string>
#include <string_view>

namespace Woven::Fields::Composites {

inline constexpr std::string_view f_tuple{"f_tuple"};
inline constexpr std::string_view f_optional{"f_optional"};
inline constexpr std::string_view f_vector{"f_vector"};
inline constexpr std::string_view f_set{"f_set"};
inline constexpr std::string_view f_map_keys{"f_map_keys"};
inline constexpr std::string_view f_map_enum{"f_map_enum"};
inline constexpr std::string_view f_xarray{"f_xarray"};
inline constexpr std::string_view f_variant{"f_variant"};

std::shared_ptr<Viper::Path const> const & f_tuplePath();
std::shared_ptr<Viper::Path const> const & f_optionalPath();
std::shared_ptr<Viper::Path const> const & f_vectorPath();
std::shared_ptr<Viper::Path const> const & f_setPath();
std::shared_ptr<Viper::Path const> const & f_map_keysPath();
std::shared_ptr<Viper::Path const> const & f_map_enumPath();
std::shared_ptr<Viper::Path const> const & f_xarrayPath();
std::shared_ptr<Viper::Path const> const & f_variantPath();

} // namespace Woven::Fields::Composites

namespace Woven::Fields::Entities {

inline constexpr std::string_view f_core_grade{"f_core_grade"};
inline constexpr std::string_view f_parts_grade{"f_parts_grade"};
inline constexpr std::string_view f_core_colour{"f_core_colour"};
inline constexpr std::string_view f_parts_colour{"f_parts_colour"};
inline constexpr std::string_view f_single{"f_single"};
inline constexpr std::string_view f_thing{"f_thing"};
inline constexpr std::string_view f_sub_thing{"f_sub_thing"};
inline constexpr std::string_view f_other_thing{"f_other_thing"};
inline constexpr std::string_view f_klub{"f_klub"};
inline constexpr std::string_view f_any_concept{"f_any_concept"};

std::shared_ptr<Viper::Path const> const & f_core_gradePath();
std::shared_ptr<Viper::Path const> const & f_parts_gradePath();
std::shared_ptr<Viper::Path const> const & f_core_colourPath();
std::shared_ptr<Viper::Path const> const & f_parts_colourPath();
std::shared_ptr<Viper::Path const> const & f_singlePath();
std::shared_ptr<Viper::Path const> const & f_thingPath();
std::shared_ptr<Viper::Path const> const & f_sub_thingPath();
std::shared_ptr<Viper::Path const> const & f_other_thingPath();
std::shared_ptr<Viper::Path const> const & f_klubPath();
std::shared_ptr<Viper::Path const> const & f_any_conceptPath();

} // namespace Woven::Fields::Entities

namespace Woven::Fields::Nested {

inline constexpr std::string_view f_composites{"f_composites"};
inline constexpr std::string_view f_entities{"f_entities"};

std::shared_ptr<Viper::Path const> const & f_compositesPath();
std::shared_ptr<Viper::Path const> const & f_entitiesPath();

} // namespace Woven::Fields::Nested

#endif