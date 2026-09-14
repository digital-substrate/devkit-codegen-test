// THE BASE UNIT's half of Definitions: the model-wide accessor, and only that.
//
// definitions() decodes the blob the caller embeds (Topology_Resources.hpp, written
// by generate.py, not by any template). That caller-provided edge lives here, in the
// base, so no unit carries it.
//
// The per-namespace RuntimeIds move out, to each unit -- see ModelA_Definitions.hpp.

#ifndef Topology_Definitions_hpp
#define Topology_Definitions_hpp

#include "Viper_Definitions.hpp"
#include <memory>

namespace Topology {

std::shared_ptr<Viper::Definitions const> const & definitions();

} // ns Topology

#endif
