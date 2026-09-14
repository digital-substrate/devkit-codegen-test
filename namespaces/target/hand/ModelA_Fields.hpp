// ModelA — how to name and address the fields of its structures.
//
// Layer 2: derived from the types, depends on nothing but them. Hand-written from the
// model.
//
// ONE ARTEFACT, WHERE THE PACK HAS TWO. Today `Field` gives a field's name and `Path`
// gives its address, in two files whose contents are in bijection. A developer wanting
// the name almost always wants the address in the next line -- `attachment.diff(key,
// Path::Colour::r(), 4)` reads the path, `Field::Colour::r` names it in an error. Two
// files is an implementation decomposition, not a domain.

#ifndef ModelA_Fields_hpp
#define ModelA_Fields_hpp

#include "ModelA_Data.hpp"
#include "Viper_Path.hpp"

#include <string_view>

namespace ModelA::Fields::Colour {

/// The field names, as the model spells them.
///
/// `string_view` and not `std::string`: a name is a compile-time constant of the model,
/// so it costs nothing at run time and can be used in a constant expression. The pack
/// emits `extern std::string const`, which allocates once per name at static init for
/// something that never changes.
inline constexpr std::string_view r{"r"};
inline constexpr std::string_view g{"g"};
inline constexpr std::string_view b{"b"};

/// Where each field sits, for a partial read or write.
///
/// A path is a property of the structure, not of a value, so there is one per field for
/// the life of the program. Returned by reference to a memoised instance rather than
/// rebuilt, and `shared_ptr` because that is what the runtime's API takes.
std::shared_ptr<Viper::Path const> const & rPath();
std::shared_ptr<Viper::Path const> const & gPath();
std::shared_ptr<Viper::Path const> const & bPath();

} // namespace ModelA::Fields::Colour

#endif
