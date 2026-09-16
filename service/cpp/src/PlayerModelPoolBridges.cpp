#include "PlayerModel_Pool.hpp"
#include "Demo_Attachments.hpp"

using namespace Demo;

// MARK: - VertexModel
namespace PlayerModel {

PlayerKey create(std::shared_ptr<Viper::AttachmentMutating> const & mutating, std::string const & nickname, Demo::Level level) {
    auto const key{PlayerKey::create()};
    auto const property{PlayerProperty{nickname, level}};
    Attachments::Player::property::set(mutating, key, property);
    return key;
}

std::optional<PlayerKey> has_player(std::shared_ptr<Viper::AttachmentGetting> const & getting, std::string const & nickname) {
  for (auto const & key : Attachments::Player::property::keys(getting))
    if (auto const property{Attachments::Player::property::get(getting, key)})
        if (property->nickname == nickname)
          return key;

  return std::nullopt;
}

} // ns