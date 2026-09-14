#include "ModelA_Fields.hpp"
void f() { static_assert(ModelA::Fields::Colour::r == "r"); auto const & p = ModelA::Fields::Colour::rPath(); (void)p; }
