// unité Woven — ce qu'il faut à ses types pour traverser vers le runtime.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar
//
// Deux déclarations par type, et c'est toute la part d'un namespace dans le pont.
// Le descripteur de type, qui était ici, est passé dans son identité de modèle : la couche
// des types en a besoin aussi, et elle ne sérialise rien. Encoding to a Value, to JSON, and hashing are compositions of the two below,
// and every container is the runtime's -- ModelA owns Material, not std::set.

#ifndef Woven_Codec_hpp
#define Woven_Codec_hpp

#include "Woven_Data.hpp"
#include "Parts_Codec.hpp"
#include "Core_Codec.hpp"

#include "Viper_Codec.hpp"

#include <memory>

namespace Woven {

void write(Viper::Codec::Writer & w, KnotKey const & value);
KnotKey read(Viper::Codec::Reader & r, Viper::Codec::tag<KnotKey>);

void write(Viper::Codec::Writer & w, DerivedKey const & value);
DerivedKey read(Viper::Codec::Reader & r, Viper::Codec::tag<DerivedKey>);

void write(Viper::Codec::Writer & w, WeaveKey const & value);
WeaveKey read(Viper::Codec::Reader & r, Viper::Codec::tag<WeaveKey>);


void write(Viper::Codec::Writer & w, Composites const & value);
Composites read(Viper::Codec::Reader & r, Viper::Codec::tag<Composites>);

void write(Viper::Codec::Writer & w, Entities const & value);
Entities read(Viper::Codec::Reader & r, Viper::Codec::tag<Entities>);

void write(Viper::Codec::Writer & w, Nested const & value);
Nested read(Viper::Codec::Reader & r, Viper::Codec::tag<Nested>);

} // namespace Woven

#endif