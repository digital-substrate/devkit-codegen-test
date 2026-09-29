#include "ModelA_Fields.hpp"
void f() { static_assert(model_a::fields::Colour::r == "r"); auto const & p = model_a::fields::Colour::rPath(); (void)p; }
