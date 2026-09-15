// ModelA — son identité dans le modèle.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "ModelA_Model.hpp"

#include "Topology_Codec.hpp"

#include "Viper_Definitions.hpp"

namespace ModelA {

namespace RuntimeIds {
Viper::UUId const Material{Viper::UUId::parse("de42abc9-3fd6-ac10-63ba-d0d6fba6cb9e")};
Viper::UUId const Finish{Viper::UUId::parse("cc101b86-fc5f-855a-b0f6-59844b9f5e3e")};
Viper::UUId const Colour{Viper::UUId::parse("887a78c8-07ff-3c8a-8172-ff5ae381dfd9")};
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


std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<Finish>) {
    static std::shared_ptr<Viper::Type> const instance{
        Topology::Codec::definitions()->checkEnumeration(RuntimeIds::Finish)};
    return instance;
}

std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<Colour>) {
    static std::shared_ptr<Viper::Type> const instance{
        Topology::Codec::definitions()->checkStructure(RuntimeIds::Colour)};
    return instance;
}

} // namespace ModelA