#include "topology_model_a_fields.hpp"
#include "topology_model_a_paths.hpp"
void f() { static_assert(topology::model_a::fields::Colour::r == "r"); auto const & p = topology::model_a::paths::Colour::r(); (void)p; }
