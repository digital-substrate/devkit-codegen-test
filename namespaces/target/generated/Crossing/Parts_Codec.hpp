// unité Parts — ce qu'il faut à ses types pour traverser vers le runtime.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar
//
// Deux déclarations par type, et c'est toute la part d'un namespace dans le pont.
// Le descripteur de type, qui était ici, est passé dans son identité de modèle : la couche
// des types en a besoin aussi, et elle ne sérialise rien. Encoding to a Value, to JSON, and hashing are compositions of the two below,
// and every container is the runtime's -- ModelA owns Material, not std::set.

#ifndef Parts_Codec_hpp
#define Parts_Codec_hpp

#include "Parts_Data.hpp"

#include "Viper_Codec.hpp"

#include <memory>

namespace Parts {

void write(Viper::Codec::Writer & w, ThingKey const & value);
ThingKey read(Viper::Codec::Reader & r, Viper::Codec::tag<ThingKey>);


void write(Viper::Codec::Writer & w, Grade value);
Grade read(Viper::Codec::Reader & r, Viper::Codec::tag<Grade>);

void write(Viper::Codec::Writer & w, Colour const & value);
Colour read(Viper::Codec::Reader & r, Viper::Codec::tag<Colour>);

} // namespace Parts

#endif