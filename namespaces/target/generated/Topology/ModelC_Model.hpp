// unité ModelC — son identité dans le modèle.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#ifndef ModelC_Model_hpp
#define ModelC_Model_hpp

#include "ModelC_Data.hpp"

#include "Viper_Codec.hpp"
#include "Viper_Types.hpp"

#include <memory>

namespace ModelC {

/// L'identité de chaque type déclaré ici.
namespace RuntimeIds {
extern Viper::UUId const Marker;
} // namespace RuntimeIds

/// Le concept dont une clé relève -- ce qu'un rétrécissement compare.
std::shared_ptr<Viper::Type> const & conceptType(Viper::Codec::tag<MarkerKey>);

/// Le club dont une clé relève. Distinct du précédent : une adhésion n'est pas un
/// héritage, et c'est le descripteur qui porte la différence, pas le code.

/// Le type lui-même, tel que le runtime le manipule -- ce que le codec générique demande.
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<MarkerKey>);

} // namespace ModelC

#endif