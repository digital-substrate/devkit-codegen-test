// ModelC — everything its types need in order to cross into the runtime.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar
//
// Deux déclarations par type, et c'est toute la part d'un namespace dans le pont.
// Le descripteur de type, qui était ici, est passé dans son identité de modèle : la couche
// des types en a besoin aussi, et elle ne sérialise rien. Encoding to a Value, to JSON, and hashing are compositions of the two below,
// and every container is the runtime's -- ModelA owns Material, not std::set.

#ifndef ModelC_Codec_hpp
#define ModelC_Codec_hpp

#include "ModelC_Data.hpp"

#include "Viper_Codec.hpp"

#include <memory>

namespace ModelC {

void write(Viper::Codec::Writer & w, MarkerKey const & value);
MarkerKey read(Viper::Codec::Reader & r, Viper::Codec::tag<MarkerKey>);




} // namespace ModelC

#endif