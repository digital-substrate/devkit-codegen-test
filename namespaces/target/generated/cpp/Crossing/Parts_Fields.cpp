// unité Parts — l'implémentation de l'adressage de ses champs.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

#include "Parts_Fields.hpp"

namespace Parts::Fields::Colour {

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

} // namespace Parts::Fields::Colour