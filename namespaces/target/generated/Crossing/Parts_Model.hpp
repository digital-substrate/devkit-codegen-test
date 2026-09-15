// unité Parts — son identité dans le modèle.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

#ifndef Parts_Model_hpp
#define Parts_Model_hpp

#include "Parts_Data.hpp"

#include "Viper_TypedCodec.hpp"
#include "Viper_Types.hpp"

#include <memory>

namespace Parts {

/// L'identité de chaque type déclaré ici.
namespace RuntimeIds {
extern Viper::UUId const Thing;
extern Viper::UUId const Grade;
extern Viper::UUId const Colour;
} // namespace RuntimeIds

/// Le concept dont une clé relève -- ce qu'un rétrécissement compare.
std::shared_ptr<Viper::Type> const & conceptType(Viper::Codec::tag<ThingKey>);

/// Le club dont une clé relève. Distinct du précédent : une adhésion n'est pas un
/// héritage, et c'est le descripteur qui porte la différence, pas le code.

/// Le type lui-même, tel que le runtime le manipule -- ce que le codec générique demande.
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<ThingKey>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<Grade>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<Colour>);

} // namespace Parts

#endif