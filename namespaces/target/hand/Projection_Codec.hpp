// Projection — the composing unit crossing into the runtime.
//
// The case that settles the design: Projection declares an attachment of
// `map<key<ModelA::Material>, key<ModelB::Material>>`, and there is nothing for it here.
//
// The map is written by the runtime's generic `write(Writer&, std::map<K,V> const&)`,
// which calls `write` on each key and each value, and ADL sends those to ModelA and to
// ModelB. A shape spanning two namespaces stops being an artefact in search of an owner:
// it is a composition, resolved where it is used. Demonstrated in ../adl, two programs
// that compile and run.
//
// Today that same map is one generated function,
// `write_map_ModelA_MaterialKey_to_ModelB_MaterialKey`, living in a flat scope belonging
// to no namespace -- which is the entire reason a base layer had to be invented.

#ifndef Projection_Codec_hpp
#define Projection_Codec_hpp

#include "Projection_Data.hpp"
#include "ModelA_Codec.hpp"        // Pair's fields cross too
#include "ModelB_Codec.hpp"

#include "Viper_Codec.hpp"

namespace Projection {

void write(Viper::Codec::Writer & w, Pair const & value);
void write(Viper::Codec::Writer & w, LinkKey const & value);
void write(Viper::Codec::Writer & w, DerivedMaterialKey const & value);

Pair                read(Viper::Codec::Reader & r, Viper::Codec::tag<Pair>);
LinkKey             read(Viper::Codec::Reader & r, Viper::Codec::tag<LinkKey>);
DerivedMaterialKey  read(Viper::Codec::Reader & r, Viper::Codec::tag<DerivedMaterialKey>);

std::shared_ptr<Viper::Type const> const & type(Viper::Codec::tag<Pair>);
std::shared_ptr<Viper::Type const> const & type(Viper::Codec::tag<LinkKey>);
std::shared_ptr<Viper::Type const> const & type(Viper::Codec::tag<DerivedMaterialKey>);

} // namespace Projection

#endif
