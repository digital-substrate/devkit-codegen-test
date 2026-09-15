// unité Demo — son identité dans le modèle.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/service/Service.dsm.json by kibo-2.0.0.jar

#include "Demo_Model.hpp"

#include "Service_Codec.hpp"

#include "Viper_Definitions.hpp"

namespace Demo {

namespace RuntimeIds {
Viper::UUId const Player{Viper::UUId::parse("c177a251-4de8-57a0-de3b-6cc2ae68eb13")};
Viper::UUId const Level{Viper::UUId::parse("238d8f84-734d-df83-fc48-f4dc69cc127a")};
Viper::UUId const PlayerProperty{Viper::UUId::parse("2fa5978a-9426-26a5-e8e7-35c80ce00ffd")};
Viper::UUId const Vector3{Viper::UUId::parse("9099c892-b971-86b4-6d84-ab38cc2d3d16")};
} // namespace RuntimeIds

std::shared_ptr<Viper::Type> const & conceptType(Viper::Codec::tag<PlayerKey>) {
    static std::shared_ptr<Viper::Type> const instance{
        Service::Codec::definitions()->checkConcept(RuntimeIds::Player)};
    return instance;
}


std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<PlayerKey>) {
    static std::shared_ptr<Viper::Type> const instance{Viper::TypeKey::make(conceptType(Viper::Codec::tag<PlayerKey>{}))};
    return instance;
}


std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<Level>) {
    static std::shared_ptr<Viper::Type> const instance{
        Service::Codec::definitions()->checkEnumeration(RuntimeIds::Level)};
    return instance;
}

std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<PlayerProperty>) {
    static std::shared_ptr<Viper::Type> const instance{
        Service::Codec::definitions()->checkStructure(RuntimeIds::PlayerProperty)};
    return instance;
}

std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<Vector3>) {
    static std::shared_ptr<Viper::Type> const instance{
        Service::Codec::definitions()->checkStructure(RuntimeIds::Vector3)};
    return instance;
}

} // namespace Demo