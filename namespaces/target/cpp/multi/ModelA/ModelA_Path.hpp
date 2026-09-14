// PER-UNIT, AND WITH AN EMPTY DEPENDENCY SET.
//
// Path describes where a field sits, not what type it has: every accessor returns a
// Viper::Path. So this artefact is per-unit like Data, but unlike Data it reaches
// nothing. Its only include is the runtime's.
//
// Field, alongside it, has exactly the same shape.

#ifndef ModelA_Path_hpp
#define ModelA_Path_hpp

#include "Viper_Path.hpp"
#include <memory>

namespace ModelA::Path::Colour {
std::shared_ptr<Viper::Path const> const & r();
std::shared_ptr<Viper::Path const> const & g();
std::shared_ptr<Viper::Path const> const & b();
} // ns

#endif
