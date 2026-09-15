// unité Projection — l'implémentation de l'adressage de ses champs.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "Projection_Fields.hpp"

namespace Projection::Fields::Pair {

std::shared_ptr<Viper::Path const> const & aPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{a})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & bPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{b})};
    return instance;
}

} // namespace Projection::Fields::Pair