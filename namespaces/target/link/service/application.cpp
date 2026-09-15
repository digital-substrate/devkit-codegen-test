// Ce qu'une application écrit pour le modèle Service.
//
// LE SEUL MODÈLE À EXERCER LE PONT STATIQUE/DYNAMIQUE, parce qu'il est le seul à déclarer
// des pools appelés. Les trois autres déclarent des types et des attachments : leur pont
// existe, mais rien ne l'appelle, donc rien ne le vérifie.
//
// Et l'implémentation d'un pool d'attachments montre la frontière à un endroit précis : sa
// fonction reçoit l'interface sur laquelle agir, parce qu'elle opère sur des documents et
// non sur des valeurs seules. C'est le générateur qui met ce contexte en premier argument ;
// c'est le développeur qui décide quoi en faire.

#include "Demo_Attachments.hpp"
#include "Demo_Data.hpp"
#include "PlayerModel_Pool.hpp"
#include "Tools_Pool.hpp"

#include <random>

namespace Tools {

std::int64_t add(std::int64_t a, std::int64_t b) { return a + b; }

Demo::Vector3 add_vector(Demo::Vector3 const & a, Demo::Vector3 const & b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

std::string random_string(std::uint32_t size) {
    static std::mt19937_64 rng{42};
    std::string result(size, ' ');
    for (auto & c : result)
        c = static_cast<char>('a' + rng() % 26);

    return result;
}

} // namespace Tools

namespace PlayerModel {

/// Créer un joueur, c'est créer une clé et lui accrocher ses propriétés. Le pont ne sait
/// rien de tout cela : il a décodé un nom et un niveau, il appellera, et il encodera la clé.
Demo::PlayerKey create(std::shared_ptr<Viper::AttachmentMutating> const & mutating,
                       std::string const & nickname, Demo::Level level) {
    auto const key{Demo::PlayerKey::create()};
    Demo::Attachments::Player::property::set(*mutating, key, Demo::PlayerProperty{nickname, level});

    return key;
}

std::optional<Demo::PlayerKey> has_player(std::shared_ptr<Viper::AttachmentGetting> const & getting,
                                          std::string const & nickname) {
    for (auto const & key : Demo::Attachments::Player::property::keys(*getting)) {
        auto const property{Demo::Attachments::Player::property::get(*getting, key)};
        if (property && property->nickname == nickname)
            return key;
    }

    return std::nullopt;
}

} // namespace PlayerModel
