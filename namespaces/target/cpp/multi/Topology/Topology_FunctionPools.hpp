// THE AGGREGATE: the base unit's namespace, but a sink file.
//
// This is where a worry about cycles turned out to be misplaced. The base unit was
// said to be a root -- Topology_Data.hpp and Topology_ValueType.hpp include nothing
// generated -- and a registry of every pool plainly depends on all of them. Both are
// true at once, because **the root/sink distinction is a property of files, not of
// units**. A namespace reopens across files; a file's includes do not.
//
// So `namespace Topology` spans a root file and a sink file, and the layering in the
// design is a layering of artefacts. A unit may contribute at several layers.

#ifndef Topology_FunctionPools_hpp
#define Topology_FunctionPools_hpp

#include "Tools_Pool.hpp"
#include "Projector_Pool.hpp"
#include "Viper_FunctionPool.hpp"
#include <memory>
#include <vector>

namespace Topology {

// Every pool this model declares, for registering them in one call.
std::vector<std::shared_ptr<Viper::FunctionPool>> functionPools();

} // ns Topology

#endif
