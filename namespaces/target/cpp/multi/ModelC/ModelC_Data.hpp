// Reached from nowhere but one attachment document type in Projection. Before
// kibo 9328acd this unit carried no dependency edge and could have been emitted
// after the unit that needs it.

#ifndef ModelC_Data_hpp
#define ModelC_Data_hpp

#include "Topology_Data.hpp"

namespace ModelC {

class MarkerKey final { /* ... unchanged ... */ };

} // ns ModelC

template<> struct std::hash<ModelC::MarkerKey> { /* ... */ };

#endif
