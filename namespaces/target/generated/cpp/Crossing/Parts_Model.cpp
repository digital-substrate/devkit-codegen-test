// unité Parts — son identité dans le modèle.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

#include "Parts_Model.hpp"

#include "Crossing_Codec.hpp"

#include "Viper_Definitions.hpp"

namespace Parts {

namespace RuntimeIds {
Viper::UUId const Thing{Viper::UUId::parse("12f4a98d-d084-f535-db87-e58f8757a553")};
Viper::UUId const Grade{Viper::UUId::parse("b377e61b-49b9-6e92-5ccf-ea47d5bbfb30")};
Viper::UUId const Colour{Viper::UUId::parse("08261ca9-72d6-3df5-6608-c88279d35a48")};
} // namespace RuntimeIds

std::shared_ptr<Viper::Type> const & conceptType(Viper::Codec::tag<ThingKey>) {
    static std::shared_ptr<Viper::Type> const instance{
        Crossing::Codec::definitions()->checkConcept(RuntimeIds::Thing)};
    return instance;
}


std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<ThingKey>) {
    static std::shared_ptr<Viper::Type> const instance{Viper::TypeKey::make(conceptType(Viper::Codec::tag<ThingKey>{}))};
    return instance;
}


std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<Grade>) {
    static std::shared_ptr<Viper::Type> const instance{
        Crossing::Codec::definitions()->checkEnumeration(RuntimeIds::Grade)};
    return instance;
}

std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<Colour>) {
    static std::shared_ptr<Viper::Type> const instance{
        Crossing::Codec::definitions()->checkStructure(RuntimeIds::Colour)};
    return instance;
}

} // namespace Parts