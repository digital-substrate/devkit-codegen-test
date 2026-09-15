// unité Woven — son identité dans le modèle.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

#ifndef Woven_Model_hpp
#define Woven_Model_hpp

#include "Woven_Data.hpp"

#include "Viper_TypedCodec.hpp"
#include "Viper_Types.hpp"

#include <memory>

namespace Woven {

/// L'identité de chaque type déclaré ici.
namespace RuntimeIds {
extern Viper::UUId const Knot;
extern Viper::UUId const Derived;
extern Viper::UUId const Weave;
extern Viper::UUId const Composites;
extern Viper::UUId const Entities;
extern Viper::UUId const Nested;
} // namespace RuntimeIds

/// Le concept dont une clé relève -- ce qu'un rétrécissement compare.
std::shared_ptr<Viper::Type> const & conceptType(Viper::Codec::tag<KnotKey>);
std::shared_ptr<Viper::Type> const & conceptType(Viper::Codec::tag<DerivedKey>);

/// Le club dont une clé relève. Distinct du précédent : une adhésion n'est pas un
/// héritage, et c'est le descripteur qui porte la différence, pas le code.
std::shared_ptr<Viper::Type> const & clubType(Viper::Codec::tag<WeaveKey>);

/// Le type lui-même, tel que le runtime le manipule -- ce que le codec générique demande.
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<KnotKey>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<DerivedKey>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<WeaveKey>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<Composites>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<Entities>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<Nested>);

} // namespace Woven

#endif