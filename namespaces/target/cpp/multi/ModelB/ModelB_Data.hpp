// A second driver unit, declaring the SAME names as ModelA: MaterialKey and Colour.
// Nothing is renamed. The two coexist because they are in different scopes and in
// different files, which is what a namespace is for -- and what ModelA_Material
// was faking.

#ifndef ModelB_Data_hpp
#define ModelB_Data_hpp

#include "Topology_Data.hpp"
#include "Viper_UUId.hpp"

namespace ModelB {

class MaterialKey final { /* ... unchanged ... */ };
class Colour final { /* ... unchanged: float r, g, b ... */ };

} // ns ModelB

template<> struct std::hash<ModelB::MaterialKey> { /* ... */ };

#endif
