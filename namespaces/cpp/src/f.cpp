#include "topology_model_a_fields.hpp"
void f() { static_assert(topology::model_a::fields::Colour::r == "r"); auto const & p = topology::model_a::fields::Colour::rPath(); (void)p; }
