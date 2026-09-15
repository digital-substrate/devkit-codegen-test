// unité Demo — l'implémentation des attachments qu'elle déclare.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/service/Service.dsm.json by kibo-2.0.0.jar

#include "Demo_Attachments.hpp"

#include "Demo_Codec.hpp"
#include "Demo_Fields.hpp"
#include "Demo_Model.hpp"

#include "Service_Codec.hpp"
#include "Service_Db.hpp"

#include "Viper_Attachment.hpp"
#include "Viper_Definitions.hpp"
#include "Viper_Path.hpp"
#include "Viper_Values.hpp"
#include "Viper_ValueSetIter.hpp"

namespace Demo::Attachments::Player::property {

Viper::UUId const runtimeId{Viper::UUId::parse("5f39a4c7-fa83-1290-432c-330fc392a39b")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Service::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(PlayerKey const & key) {
    return Viper::ValueKey::cast(Service::Codec::encode(key));
}

} // namespace

std::set<PlayerKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<PlayerKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Service::Codec::decode<PlayerKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, PlayerKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<PlayerProperty> get(Viper::AttachmentGetting const & getting, PlayerKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Service::Codec::decode<PlayerProperty>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, PlayerKey const & key, PlayerProperty const & value) {
    mutating.set(attachment(), encodeKey(key), Service::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, PlayerKey const & key, PlayerProperty const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Service::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, PlayerKey const & key, PlayerProperty const & value) {
    return Service::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, PlayerKey const & key) {
    return Service::Db::del(db, attachment(), key);
}

void setNickname(Viper::AttachmentMutating & mutating, PlayerKey const & key, std::string const & value) {
    mutating.update(attachment(), encodeKey(key), Demo::Fields::PlayerProperty::nicknamePath(),
                    Service::Codec::encode(value));
}


void setLevel(Viper::AttachmentMutating & mutating, PlayerKey const & key, Level value) {
    mutating.update(attachment(), encodeKey(key), Demo::Fields::PlayerProperty::levelPath(),
                    Service::Codec::encode(value));
}

} // namespace Demo::Attachments::Player::property