#include "PlayerModel_Pool.hpp"
#include "Demo_Attachments.hpp"

using namespace demo;

// MARK: - VertexModel
namespace player_model {

PlayerKey create(std::shared_ptr<Viper::AttachmentMutating> const & mutating, std::string const & nickname, demo::Level level) {
    auto const key{PlayerKey::create()};
    auto const property{PlayerProperty{nickname, level}};
    attachments::Player::property::set(mutating, key, property);
    return key;
}

std::optional<PlayerKey> has_player(std::shared_ptr<Viper::AttachmentGetting> const & getting, std::string const & nickname) {
  for (auto const & key : attachments::Player::property::keys(getting))
    if (auto const property{attachments::Player::property::get(getting, key)})
        if (property->nickname == nickname)
          return key;

  return std::nullopt;
}

} // ns