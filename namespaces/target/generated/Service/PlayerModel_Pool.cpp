// PlayerModel — l'implémentation du pool, et le pont entre le statique et le dynamique.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/service/Service.dsm.json by kibo-2.0.0.jar

#include "PlayerModel_Pool.hpp"

#include "Demo_Codec.hpp"
#include "Demo_Model.hpp"

#include "Service_Codec.hpp"

#include "Viper_AttachmentFunctionPool.hpp"
#include "Viper_FunctionPrototype.hpp"
#include "Viper_ServiceRemote.hpp"
#include "Viper_ValueVoid.hpp"
#include "Viper_AttachmentGettingFunction.hpp"
#include "Viper_AttachmentMutatingFunction.hpp"

namespace PlayerModel {

namespace {

Viper::UUId const poolId{Viper::UUId::parse("d75a8a57-f0ad-4a44-84f7-1ea409d4bd36")};

/// `create`, vue du dynamique.
class Create final : public Viper::AttachmentMutatingFunction {
public:
    static std::shared_ptr<Create> make() {
        return std::make_shared<Create>(Viper::FunctionPrototype::make(
            "create",
            {{"nickname", type(Viper::Codec::tag<std::string>{})},
             {"level", type(Viper::Codec::tag<Demo::Level>{})}},
            type(Viper::Codec::tag<Demo::PlayerKey>{})));
    }

    explicit Create(std::shared_ptr<Viper::FunctionPrototype> prototype)
    : Viper::AttachmentMutatingFunction{std::move(prototype), ""} {}

protected:
    std::shared_ptr<Viper::Value> checkedCall(
            std::shared_ptr<Viper::AttachmentMutating> const & attachmentMutating,
            std::vector<std::shared_ptr<Viper::Value>> const & args) const {
        auto const nickname{Service::Codec::decode<std::string>(args.at(0))};
        auto const level{Service::Codec::decode<Demo::Level>(args.at(1))};

        return Service::Codec::encode(create(attachmentMutating, nickname, level));
    }
};

/// `has_player`, vue du dynamique.
class HasPlayer final : public Viper::AttachmentGettingFunction {
public:
    static std::shared_ptr<HasPlayer> make() {
        return std::make_shared<HasPlayer>(Viper::FunctionPrototype::make(
            "has_player",
            {{"nickname", type(Viper::Codec::tag<std::string>{})}},
            type(Viper::Codec::tag<std::optional<Demo::PlayerKey>>{})));
    }

    explicit HasPlayer(std::shared_ptr<Viper::FunctionPrototype> prototype)
    : Viper::AttachmentGettingFunction{std::move(prototype), ""} {}

protected:
    std::shared_ptr<Viper::Value> checkedCall(
            std::shared_ptr<Viper::AttachmentGetting> const & attachmentGetting,
            std::vector<std::shared_ptr<Viper::Value>> const & args) const {
        auto const nickname{Service::Codec::decode<std::string>(args.at(0))};

        return Service::Codec::encode(has_player(attachmentGetting, nickname));
    }
};

} // namespace

std::shared_ptr<Viper::AttachmentFunctionPool> pool() {
    static auto const instance = [] {
        auto const created = Viper::AttachmentFunctionPool::make(poolId, "PlayerModel");
        created->add(Create::make());
        created->add(HasPlayer::make());
        return created;
    }();
    return instance;
}

Remote::Remote(std::shared_ptr<Viper::ServiceRemote> service)
: _service{std::move(service)} {}

bool Remote::isAvailable() const {
    return _service->queryAttachmentFunctionPool(poolId) != nullptr;
}

Demo::PlayerKey Remote::create(std::shared_ptr<Viper::AttachmentMutating> const & attachmentMutating, std::string const & nickname, Demo::Level level) const {
    return Service::Codec::decode<Demo::PlayerKey>(
        _service->call(attachmentMutating, poolId, "create", {Service::Codec::encode(nickname), Service::Codec::encode(level)}));
}

std::optional<Demo::PlayerKey> Remote::has_player(std::shared_ptr<Viper::AttachmentMutating> const & attachmentMutating, std::string const & nickname) const {
    return Service::Codec::decode<std::optional<Demo::PlayerKey>>(
        _service->call(attachmentMutating, poolId, "has_player", {Service::Codec::encode(nickname)}));
}

} // namespace PlayerModel