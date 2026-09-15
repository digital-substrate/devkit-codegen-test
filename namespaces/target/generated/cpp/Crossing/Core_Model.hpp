// unité Core — son identité dans le modèle.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

#ifndef Core_Model_hpp
#define Core_Model_hpp

#include "Core_Data.hpp"

#include "Viper_TypedCodec.hpp"
#include "Viper_Types.hpp"

#include <memory>

namespace Core {

/// L'identité de chaque type déclaré ici.
namespace RuntimeIds {
extern Viper::UUId const Other;
extern Viper::UUId const Thing;
extern Viper::UUId const SubThing;
extern Viper::UUId const Klub;
extern Viper::UUId const Grade;
extern Viper::UUId const Bag;
extern Viper::UUId const Colour;
extern Viper::UUId const Defaults;
extern Viper::UUId const Scalars;
extern Viper::UUId const Single;
} // namespace RuntimeIds

/// Le concept dont une clé relève -- ce qu'un rétrécissement compare.
std::shared_ptr<Viper::Type> const & conceptType(Viper::Codec::tag<OtherKey>);
std::shared_ptr<Viper::Type> const & conceptType(Viper::Codec::tag<ThingKey>);
std::shared_ptr<Viper::Type> const & conceptType(Viper::Codec::tag<SubThingKey>);

/// Le club dont une clé relève. Distinct du précédent : une adhésion n'est pas un
/// héritage, et c'est le descripteur qui porte la différence, pas le code.
std::shared_ptr<Viper::Type> const & clubType(Viper::Codec::tag<KlubKey>);

/// Le type lui-même, tel que le runtime le manipule -- ce que le codec générique demande.
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<OtherKey>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<ThingKey>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<SubThingKey>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<KlubKey>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<Grade>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<Bag>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<Colour>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<Defaults>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<Scalars>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<Single>);

} // namespace Core

#endif