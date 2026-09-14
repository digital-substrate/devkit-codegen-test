// A POOL IS A UNIT, and this one depends on nothing.
//
// Tools names no namespaced type at all -- void reset(), int64 add(int64, int64) --
// so it includes no other unit. It is the degenerate case of a unit: a namespace
// holding only functions, at the top of the graph, with an empty dependency set.
//
// Nothing depends on it either. A type never references a function, so every pool
// is a sink: it can never sit in a cycle, and it can be dropped from a delivery
// without breaking anything beneath it.
//
// The scope is `Tools`, not `Topology::FunctionPoolBridges::Tools`. The pool's name
// is the unit's name; `FunctionPoolBridges` was a template name that had become a
// namespace level.

#ifndef Tools_Pool_hpp
#define Tools_Pool_hpp

#include "Viper_FunctionPool.hpp"
#include <cstdint>
#include <memory>

namespace Tools {

// Declared here, implemented by the application.
void reset();
std::int64_t add(std::int64_t a, std::int64_t b);

// This unit registers itself; the aggregate below only collects.
std::shared_ptr<Viper::FunctionPool> pool();

} // ns Tools

#endif
