#include "Service_AttachmentFunctionPoolBridges.hpp"
#include "Service_Attachments.hpp"

using namespace Service::Demo;

// MARK: - VertexModel
namespace Service::AttachmentFunctionPoolBridges::PlayerModel {

PlayerKey create(std::shared_ptr<Viper::AttachmentMutating> const & mutating, std::string const & nickname, Demo::Level level) {
    auto const key{PlayerKey::create()};
    auto const property{PlayerProperty{nickname, level}};
    Attachments::Player_Property::set(mutating, key, property);
    return key;
}

std::optional<PlayerKey> has_player(std::shared_ptr<Viper::AttachmentGetting> const & getting, std::string const & nickname) {
  for (auto const & key : Attachments::Player_Property::keys(getting))
    if (auto const property{Attachments::Player_Property::get(getting, key)})
        if (property->nickname == nickname)
          return key;

  return std::nullopt;
}

} // ns