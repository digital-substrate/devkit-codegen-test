// Projection — how to name and address the fields of its structures.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar
//
// No cross-unit include, whatever this namespace's structures hold: a path names a
// position, not a type. Its types header includes the units it reaches; this one reaches
// none.

#ifndef Projection_Fields_hpp
#define Projection_Fields_hpp

#include "Viper_Path.hpp"

#include <memory>
#include <string>
#include <string_view>

namespace Projection::Fields::Pair {

inline constexpr std::string_view a{"a"};
inline constexpr std::string_view b{"b"};

std::shared_ptr<Viper::Path const> const & aPath();
std::shared_ptr<Viper::Path const> const & bPath();

} // namespace Projection::Fields::Pair

#endif