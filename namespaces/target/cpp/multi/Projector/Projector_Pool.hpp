// A POOL THAT SPANS TWO UNITS, which is the reason the composing layer exists.
//
// void link(key<ModelA::Material>, key<ModelB::Material>) is not an orphan needing a
// home: its signature is what creates the dependency on both drivers. Inferring a
// namespace for this pool from its types is not merely wrong but impossible -- it
// names two.

#ifndef Projector_Pool_hpp
#define Projector_Pool_hpp

#include "ModelA_Data.hpp"          // computed from the signature
#include "ModelB_Data.hpp"
#include "Viper_FunctionPool.hpp"
#include <memory>

namespace Projector {

void link(ModelA::MaterialKey const & a, ModelB::MaterialKey const & b);

std::shared_ptr<Viper::FunctionPool> pool();

} // ns Projector

#endif
