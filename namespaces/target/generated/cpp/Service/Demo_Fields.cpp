// unité Demo — l'implémentation de l'adressage de ses champs.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/service/Service.dsm.json by kibo-2.0.0.jar

#include "Demo_Fields.hpp"

namespace Demo::Fields::PlayerProperty {

std::shared_ptr<Viper::Path const> const & nicknamePath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{nickname})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & levelPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{level})};
    return instance;
}

} // namespace Demo::Fields::PlayerProperty

namespace Demo::Fields::Vector3 {

std::shared_ptr<Viper::Path const> const & xPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{x})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & yPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{y})};
    return instance;
}

std::shared_ptr<Viper::Path const> const & zPath() {
    static std::shared_ptr<Viper::Path const> const instance{Viper::Path::makeField(std::string{z})};
    return instance;
}

} // namespace Demo::Fields::Vector3