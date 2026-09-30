// What an application writes, and the generator does not produce.
//
// The generator declares a pool's functions; the developer implements them. The linker
// confirms the boundary: across the 43 objects of the rendered model, the only missing
// symbols were these four, plus the implementation of the two runtime additions.

#include "topology_model_a_data.hpp"
#include "topology_model_b_data.hpp"
#include "topology_projection_data.hpp"
#include "topology_projector_pool.hpp"
#include "topology_tools_pool.hpp"
#include "topology_link_model_pool.hpp"

#include <iostream>

namespace topology::tools {

void reset() {}

std::int64_t add(std::int64_t a, std::int64_t b) { return a + b; }

} // namespace topology::tools

namespace topology::projector {

void link(topology::model_a::MaterialKey const &, topology::model_b::MaterialKey const &) {}

} // namespace topology::projector

namespace topology::link_model {

void clear(std::shared_ptr<Viper::AttachmentMutating> const &, topology::projection::LinkKey const &) {}

} // namespace topology::link_model
