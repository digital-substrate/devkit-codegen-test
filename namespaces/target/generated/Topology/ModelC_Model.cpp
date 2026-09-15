// ModelC — son identité dans le modèle.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "ModelC_Model.hpp"

#include "Topology_Codec.hpp"

#include "Viper_Definitions.hpp"

namespace ModelC {

namespace RuntimeIds {
Viper::UUId const Marker{Viper::UUId::parse("257888a7-848c-4568-5258-f8822be61ab0")};
} // namespace RuntimeIds

std::shared_ptr<Viper::Type> const & conceptType(Viper::Codec::tag<MarkerKey>) {
    static std::shared_ptr<Viper::Type> const instance{
        Topology::Codec::definitions()->checkConcept(RuntimeIds::Marker)};
    return instance;
}


std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<MarkerKey>) {
    static std::shared_ptr<Viper::Type> const instance{Viper::TypeKey::make(conceptType(Viper::Codec::tag<MarkerKey>{}))};
    return instance;
}




} // namespace ModelC