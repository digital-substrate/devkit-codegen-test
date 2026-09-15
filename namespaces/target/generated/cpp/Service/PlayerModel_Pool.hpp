// PlayerModel — a pool, and a unit in its own right.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/service/Service.dsm.json by kibo-2.0.0.jar

#ifndef PlayerModel_Pool_hpp
#define PlayerModel_Pool_hpp

#include "Demo_Data.hpp"

#include "Viper_AttachmentFunctionPool.hpp"
#include "Viper_ServiceRemote.hpp"

// LE CONTEXTE SUR LEQUEL LA FONCTION AGIT. Un pool ordinaire n'en prend pas ; celui-ci le
// prend en premier argument, donc il en a besoin dans ses signatures.
#include "Viper_AttachmentGetting.hpp"
#include "Viper_AttachmentMutating.hpp"

#include <cstdint>
#include <memory>

namespace PlayerModel {

Demo::PlayerKey create(std::shared_ptr<Viper::AttachmentMutating> const & attachmentMutating, std::string const & nickname, Demo::Level level);
std::optional<Demo::PlayerKey> has_player(std::shared_ptr<Viper::AttachmentGetting> const & attachmentGetting, std::string const & nickname);

std::shared_ptr<Viper::AttachmentFunctionPool> pool();

/// The same pool, seen from a client.
class Remote final {
public:
    explicit Remote(std::shared_ptr<Viper::ServiceRemote> service);
    bool isAvailable() const;

    Demo::PlayerKey create(std::shared_ptr<Viper::AttachmentMutating> const & attachmentMutating, std::string const & nickname, Demo::Level level) const;
    std::optional<Demo::PlayerKey> has_player(std::shared_ptr<Viper::AttachmentMutating> const & attachmentMutating, std::string const & nickname) const;

private:
    std::shared_ptr<Viper::ServiceRemote> _service;
};

} // namespace PlayerModel

#endif