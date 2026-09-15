// unité Projection — ce qu'il faut à ses types pour traverser vers le runtime.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar
//
// Deux déclarations par type, et c'est toute la part d'un namespace dans le pont.
// Le descripteur de type, qui était ici, est passé dans son identité de modèle : la couche
// des types en a besoin aussi, et elle ne sérialise rien. Encoding to a Value, to JSON, and hashing are compositions of the two below,
// and every container is the runtime's -- ModelA owns Material, not std::set.

#ifndef Projection_Codec_hpp
#define Projection_Codec_hpp

#include "Projection_Data.hpp"
#include "ModelB_Codec.hpp"
#include "ModelA_Codec.hpp"

#include "Viper_Codec.hpp"

#include <memory>

namespace Projection {

void write(Viper::Codec::Writer & w, LinkKey const & value);
LinkKey read(Viper::Codec::Reader & r, Viper::Codec::tag<LinkKey>);

void write(Viper::Codec::Writer & w, DerivedMaterialKey const & value);
DerivedMaterialKey read(Viper::Codec::Reader & r, Viper::Codec::tag<DerivedMaterialKey>);



void write(Viper::Codec::Writer & w, Pair const & value);
Pair read(Viper::Codec::Reader & r, Viper::Codec::tag<Pair>);

} // namespace Projection

#endif