// THE COMPOSING UNIT, AND THE CASE THAT SETTLES IT.
//
// Projection declares `struct Pair { key<ModelA::Material> a; key<ModelB::Material> b; }`
// and an attachment of `map<key<ModelA::Material>, key<ModelB::Material>>`.
//
// Today that map is one generated function --
// write_map_ModelA_MaterialKey_to_ModelB_MaterialKey -- living in a flat scope that
// belongs to no namespace, which is the whole reason a base layer had to be invented.
//
// Here there is no such function. The map is written by the base's
// `write(Writer&, std::map<K,V> const&)` template, which calls `write` on each key and
// each value, and ADL sends those to ModelA and ModelB respectively. The spanning shape
// stops being an artefact that needs an owner: it is a composition, resolved where it
// is used.

#include "Projection_Data.hpp"
#include "ModelA_Data.hpp"        // Pair's fields
#include "ModelB_Data.hpp"

namespace Projection {

inline void write(Viper::Codec::Writer & w, Pair const & value) {
    write(w, value.a);      // ADL -> ModelA::write
    write(w, value.b);      // ADL -> ModelB::write
}

inline void write(Viper::Codec::Writer & w, LinkKey const & value) {
    w.stream()->writeUUId(value.instanceId());
    w.stream()->writeUUId(value.runtimeId());
}

// And nothing at all for the map. It is not Projection's to write, nor ModelA's, nor
// ModelB's -- it is std::map's, and std::map's writer is generic.

} // ns Projection
