// The base unit's type table, whole, exactly as in multi.
//
// The symbols still carry the DSM namespace -- type_Demo_Vector3, not type_Vector3 --
// because typeSuffix is a structural, deduplicated name for a type shape, and it has
// to stay the same whether one namespace is present or five. It is the one place the
// namespace legitimately appears in a flat name.

#ifndef Service_ValueType_hpp
#define Service_ValueType_hpp

#include "Viper_Types.hpp"
#include <memory>

namespace Service {

std::shared_ptr<Viper::Type> const & type_bool();
std::shared_ptr<Viper::Type> const & type_Demo_Vector3();
std::shared_ptr<Viper::Type> const & type_check_Demo_PlayerKey();
// ... unchanged ...

} // ns Service

#endif
