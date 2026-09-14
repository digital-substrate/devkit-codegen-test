// THE COMPOSING UNIT. Its includes are the dependency set, computed rather than
// composed: ModelA and ModelB through Pair's fields, ModelC through an attachment
// document type alone.

#ifndef Projection_Data_hpp
#define Projection_Data_hpp

#include "Topology_Data.hpp"        // base
#include "ModelA_Data.hpp"          // key<ModelA::Material>, and DerivedMaterial's parent
#include "ModelB_Data.hpp"          // key<ModelB::Material>
#include "ModelC_Data.hpp"          // key<ModelC::Marker>, via the marker attachment

namespace Projection {

class DerivedMaterialKey;
class LinkKey;

class DerivedMaterialKey final { /* ... parent is ModelA::Material ... */ };
class LinkKey final { /* ... unchanged ... */ };

class Pair final {
public:
    ModelA::MaterialKey a{};      // qualified: a composition site, not a prefix
    ModelB::MaterialKey b{};

    // ... unchanged ...
};

} // ns Projection

template<> struct std::hash<Projection::DerivedMaterialKey> { /* ... */ };
template<> struct std::hash<Projection::LinkKey> { /* ... */ };

#endif
