// ModelA — son identité dans le modèle.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#ifndef ModelA_Model_hpp
#define ModelA_Model_hpp

#include "ModelA_Data.hpp"

#include "Viper_Codec.hpp"
#include "Viper_Types.hpp"

#include <memory>

namespace ModelA {

/// L'identité de chaque type déclaré ici.
namespace RuntimeIds {
extern Viper::UUId const Material;
extern Viper::UUId const Finish;
extern Viper::UUId const Colour;
} // namespace RuntimeIds

/// Le concept dont une clé relève -- ce qu'un rétrécissement compare.
std::shared_ptr<Viper::Type> const & conceptType(Viper::Codec::tag<MaterialKey>);

/// Le club dont une clé relève. Distinct du précédent : une adhésion n'est pas un
/// héritage, et c'est le descripteur qui porte la différence, pas le code.

/// Le type lui-même, tel que le runtime le manipule -- ce que le codec générique demande.
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<MaterialKey>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<Finish>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<Colour>);

} // namespace ModelA

#endif