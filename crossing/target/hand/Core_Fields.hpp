// unité Core — comment nommer et adresser les champs de ses structures.
//
// LES TROIS CHEMINS QUE LES MUTATIONS D'AGRÉGAT UTILISENT, et c'est leur second usage :
// le premier était le setter par champ scalaire.

#ifndef Core_Fields_hpp
#define Core_Fields_hpp

#include "Viper_Path.hpp"

#include <memory>
#include <string>
#include <string_view>

namespace Core::Fields::Bag {

inline constexpr std::string_view members{"members"};
inline constexpr std::string_view tints{"tints"};
inline constexpr std::string_view trail{"trail"};

std::shared_ptr<Viper::Path const> const & membersPath();
std::shared_ptr<Viper::Path const> const & tintsPath();
std::shared_ptr<Viper::Path const> const & trailPath();

} // namespace Core::Fields::Bag

#endif
