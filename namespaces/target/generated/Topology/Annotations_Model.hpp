// Annotations — son identité dans le modèle.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#ifndef Annotations_Model_hpp
#define Annotations_Model_hpp

#include "Annotations_Data.hpp"

#include "Viper_Codec.hpp"
#include "Viper_Types.hpp"

#include <memory>

namespace Annotations {

/// L'identité de chaque type déclaré ici.
namespace RuntimeIds {
} // namespace RuntimeIds

/// Le concept dont une clé relève -- ce qu'un rétrécissement compare.

/// Le club dont une clé relève. Distinct du précédent : une adhésion n'est pas un
/// héritage, et c'est le descripteur qui porte la différence, pas le code.

/// Le type lui-même, tel que le runtime le manipule -- ce que le codec générique demande.

} // namespace Annotations

#endif