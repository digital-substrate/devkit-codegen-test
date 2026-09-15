// unité Core — ce qu'il faut à ses types pour traverser vers le runtime.
//
// Des déclarations seulement : la référence croisée ne couvre que les formes que le modèle
// topologique ne déclare pas, et le pont lui-même y est déjà écrit et compilé.

#ifndef Core_Codec_hpp
#define Core_Codec_hpp

#include "Core_Data.hpp"

#include "Viper_Codec.hpp"

namespace Core {

void write(Viper::Codec::Writer & w, ThingKey const & value);
ThingKey read(Viper::Codec::Reader & r, Viper::Codec::tag<ThingKey>);

void write(Viper::Codec::Writer & w, Colour const & value);
Colour read(Viper::Codec::Reader & r, Viper::Codec::tag<Colour>);

void write(Viper::Codec::Writer & w, Bag const & value);
Bag read(Viper::Codec::Reader & r, Viper::Codec::tag<Bag>);

} // namespace Core

#endif
