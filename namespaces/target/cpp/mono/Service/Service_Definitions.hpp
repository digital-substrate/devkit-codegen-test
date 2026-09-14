// Mono, and identical in shape to multi: the base unit carries definitions(),
// the driver unit carries its own runtime ids. No special case.

#ifndef Service_Definitions_hpp
#define Service_Definitions_hpp

#include "Viper_Definitions.hpp"
#include <memory>

namespace Service {

std::shared_ptr<Viper::Definitions const> const & definitions();

} // ns Service

#endif
