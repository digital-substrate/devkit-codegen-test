// THE STRIKING CASE: the structure that spans two namespaces produces no edge here.
//
// Pair holds a key<ModelA::Material> and a key<ModelB::Material>, and
// Projection_Attachments.hpp has to include both units because its accessors take
// those types. This file takes none of them -- a() and b() return a Viper::Path,
// which names a position, not a type.
//
// Same structure, same unit, two artefacts, two different dependency sets. Which is
// why the include list is computed per artefact rather than per unit.

#ifndef Projection_Path_hpp
#define Projection_Path_hpp

#include "Viper_Path.hpp"
#include <memory>

namespace Projection::Path::Pair {
std::shared_ptr<Viper::Path const> const & a();
std::shared_ptr<Viper::Path const> const & b();
} // ns

#endif
