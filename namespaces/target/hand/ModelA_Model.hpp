// ModelA — son identité dans le modèle.
//
// Sorti du codec : `MaterialKey::create()` a besoin de l'identifiant du concept et
// `from()` de son descripteur, et la couche des types ne sérialise rien.

#ifndef ModelA_Model_hpp
#define ModelA_Model_hpp

#include "ModelA_Data.hpp"

#include "Viper_Codec.hpp"
#include "Viper_Types.hpp"

#include <memory>

namespace ModelA {

namespace RuntimeIds {
extern Viper::UUId const Material;
extern Viper::UUId const Finish;
extern Viper::UUId const Colour;
} // namespace RuntimeIds

std::shared_ptr<Viper::Type> const & conceptType(Viper::Codec::tag<MaterialKey>);

std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<MaterialKey>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<Finish>);
std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<Colour>);

} // namespace ModelA

#endif
