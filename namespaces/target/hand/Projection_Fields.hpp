// Projection — how to name and address the fields of its structures.
//
// Pair holds keys from two other namespaces, and this file includes neither of them.
// A path names a position, not a type, so addressing a field of a composed structure
// reaches nothing outside the unit. Same structure, two artefacts, two different
// dependency sets -- which is why an include list is computed per artefact.

#ifndef Projection_Fields_hpp
#define Projection_Fields_hpp

#include "Viper_Path.hpp"

#include <memory>
#include <string_view>

namespace Projection::Fields::Pair {

inline constexpr std::string_view a{"a"};
inline constexpr std::string_view b{"b"};

std::shared_ptr<Viper::Path const> const & aPath();
std::shared_ptr<Viper::Path const> const & bPath();

} // namespace Projection::Fields::Pair

#endif
