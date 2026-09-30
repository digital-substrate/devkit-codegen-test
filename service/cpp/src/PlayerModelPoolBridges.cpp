#include "service_player_model_pool.hpp"
#include "service_demo_attachments.hpp"

using namespace service::demo;

// MARK: - VertexModel
namespace service::player_model {

PlayerKey create(std::shared_ptr<Viper::AttachmentMutating> const & mutating, std::string const & nickname, service::demo::Level level) {
    auto const key{PlayerKey::create()};
    auto const property{PlayerProperty{nickname, level}};
    attachments::Player::property::set(mutating, key, property);
    return key;
}

std::optional<PlayerKey> hasPlayer(std::shared_ptr<Viper::AttachmentGetting> const & getting, std::string const & nickname) {
  for (auto const & key : attachments::Player::property::keys(getting))
    if (auto const property{attachments::Player::property::get(getting, key)})
        if (property->nickname == nickname)
          return key;

  return std::nullopt;
}

} // ns