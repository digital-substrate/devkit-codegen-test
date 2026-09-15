// ModelA — l'implémentation de l'adressage de ses champs.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "ModelA_Fields.hpp"

namespace ModelA::Fields::Colour {

std::shared_ptr<Viper::Path const> const & rPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{r})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & gPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{g})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & bPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{b})};
    return instance;
}

} // namespace ModelA::Fields::Colour