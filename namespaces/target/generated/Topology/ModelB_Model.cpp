// ModelB — son identité dans le modèle.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "ModelB_Model.hpp"

#include "Topology_Codec.hpp"

#include "Viper_Definitions.hpp"

namespace ModelB {

namespace RuntimeIds {
Viper::UUId const Material{Viper::UUId::parse("fcbafe56-84de-904a-574a-7013e31b8a53")};
Viper::UUId const Colour{Viper::UUId::parse("a75f5fbe-e310-cca6-ba0c-9c763942e461")};
} // namespace RuntimeIds

std::shared_ptr<Viper::Type> const & conceptType(Viper::Codec::tag<MaterialKey>) {
    static std::shared_ptr<Viper::Type> const instance{
        Topology::Codec::definitions()->checkConcept(RuntimeIds::Material)};
    return instance;
}


std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<MaterialKey>) {
    static std::shared_ptr<Viper::Type> const instance{Viper::TypeKey::make(conceptType(Viper::Codec::tag<MaterialKey>{}))};
    return instance;
}



std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<Colour>) {
    static std::shared_ptr<Viper::Type> const instance{
        Topology::Codec::definitions()->checkStructure(RuntimeIds::Colour)};
    return instance;
}

} // namespace ModelB