// Core — l'identité de ses types dans le modèle.
//
// UN ARTEFACT QUE LE DÉCOUPAGE EN COUCHES N'AVAIT PAS PRÉVU, et qui s'est imposé en
// écrivant `Core_Data.cpp`. Les identifiants d'exécution et les descripteurs de type
// étaient rangés avec le codec, parce que c'est le codec qui les demandait. Mais
// `ThingKey::create()` a besoin de l'identifiant du concept, et `ThingKey::from()` a besoin
// de son descripteur -- or la couche 1 n'a rien à voir avec la sérialisation.
//
// Ce ne sont donc pas des fonctions de codec : c'est ce que l'unité sait d'elle-même
// vis-à-vis du modèle, et deux couches s'en servent.
//
// DANS `Core` ET NON DANS `Core::Model` : `type(tag<T>)` doit être trouvable par ADL depuis
// le module injecté, et l'ADL sur `tag<Core::ThingKey>` associe `Core`, pas ses
// sous-portées. La portée est le fichier, pas le namespace.

#ifndef Core_Model_hpp
#define Core_Model_hpp

#include "Core_Data.hpp"

#include "Viper_Codec.hpp"
#include "Viper_Types.hpp"

#include <memory>

namespace Core {

/// L'identité de chaque type déclaré ici. Le pack les range déjà par namespace, ce qui est
/// la seule chose qu'il n'ait pas eu à aplatir.
namespace RuntimeIds {
extern Viper::UUId const Thing;
extern Viper::UUId const SubThing;
extern Viper::UUId const Other;
extern Viper::UUId const Klub;
extern Viper::UUId const Grade;
extern Viper::UUId const Colour;
} // namespace RuntimeIds

/// Le concept dont une clé relève -- ce qu'un rétrécissement compare.
std::shared_ptr<Viper::Type> const & conceptType(Viper::Codec::tag<ThingKey>);
std::shared_ptr<Viper::Type> const & conceptType(Viper::Codec::tag<SubThingKey>);
std::shared_ptr<Viper::Type> const & conceptType(Viper::Codec::tag<OtherKey>);

/// Le club dont une clé relève. Distinct du précédent parce qu'une adhésion n'est pas un
/// héritage, et que c'est le descripteur qui porte la différence.
std::shared_ptr<Viper::Type> const & clubType(Viper::Codec::tag<KlubKey>);

/// Le type lui-même, tel que le runtime le manipule -- ce que le codec générique demande.
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<ThingKey>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<SubThingKey>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<OtherKey>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<KlubKey>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<Grade>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<Colour>);

} // namespace Core

#endif
