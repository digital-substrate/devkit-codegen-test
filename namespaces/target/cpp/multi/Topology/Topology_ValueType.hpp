// THE BASE UNIT, whole and undivided. ValueType is NOT split per unit.
//
// It includes Viper_Types.hpp and nothing generated: every function returns a
// Viper::Type and composes out of the other functions here. The namespace appears
// only inside a symbol name, never as a C++ type reference -- so this file has no
// dependency on any unit and cannot acquire one.
//
// Three reasons not to split it, in order of weight:
//   - each function memoises a single instance, and a per-unit copy would produce
//     two distinct Viper::Type objects for one DSM type, which type().equals()
//     would then have to survive;
//   - a shape spanning two namespaces -- the map below -- belongs to neither unit,
//     and giving it to the unit that declares it lets two units emit the same shape;
//   - there is nothing to gain: it has no unit dependency to break.
//
// `ValueType` is the file name, not a scope. A feature does not become a namespace.

#ifndef Topology_ValueType_hpp
#define Topology_ValueType_hpp

#include "Viper_Types.hpp"
#include "Viper_Attachment.hpp"
#include <memory>

namespace Topology {

// Primitives: model-independent.
std::shared_ptr<Viper::Type> const & type_bool();
std::shared_ptr<Viper::Type> const & type_int64();
// ... unchanged ...

// Shapes of one namespace. The namespace is in the symbol, by typeSuffix.
std::shared_ptr<Viper::Type> const & type_ModelA_Colour();
std::shared_ptr<Viper::Type> const & type_check_ModelA_MaterialKey();
std::shared_ptr<Viper::Type> const & type_ModelB_Colour();

// A shape spanning two namespaces: one symbol, owned by neither unit, composed
// from the two above. This is why the table stays whole.
std::shared_ptr<Viper::Type> const & type_map_ModelA_MaterialKey_to_ModelB_MaterialKey();

} // ns Topology

#endif
