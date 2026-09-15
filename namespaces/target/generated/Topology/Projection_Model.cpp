// Projection — son identité dans le modèle.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "Projection_Model.hpp"

#include "Topology_Codec.hpp"

#include "Viper_Definitions.hpp"

namespace Projection {

namespace RuntimeIds {
Viper::UUId const Link{Viper::UUId::parse("d4f2e968-390a-ad1f-83d4-00e72fd30a50")};
Viper::UUId const DerivedMaterial{Viper::UUId::parse("4d1e4a0c-e262-8449-d792-44ee5aa2bb3f")};
Viper::UUId const Pair{Viper::UUId::parse("9b902df2-0abc-efa8-dc98-e9de83b1c7ab")};
} // namespace RuntimeIds

std::shared_ptr<Viper::Type> const & conceptType(Viper::Codec::tag<LinkKey>) {
    static std::shared_ptr<Viper::Type> const instance{
        Topology::Codec::definitions()->checkConcept(RuntimeIds::Link)};
    return instance;
}

std::shared_ptr<Viper::Type> const & conceptType(Viper::Codec::tag<DerivedMaterialKey>) {
    static std::shared_ptr<Viper::Type> const instance{
        Topology::Codec::definitions()->checkConcept(RuntimeIds::DerivedMaterial)};
    return instance;
}


std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<LinkKey>) {
    static std::shared_ptr<Viper::Type> const instance{Viper::TypeKey::make(conceptType(Viper::Codec::tag<LinkKey>{}))};
    return instance;
}

std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<DerivedMaterialKey>) {
    static std::shared_ptr<Viper::Type> const instance{Viper::TypeKey::make(conceptType(Viper::Codec::tag<DerivedMaterialKey>{}))};
    return instance;
}



std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<Pair>) {
    static std::shared_ptr<Viper::Type> const instance{
        Topology::Codec::definitions()->checkStructure(RuntimeIds::Pair)};
    return instance;
}

} // namespace Projection