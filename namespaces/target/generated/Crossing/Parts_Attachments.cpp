// unité Parts — l'implémentation des attachments qu'elle déclare.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

#include "Parts_Attachments.hpp"

#include "Parts_Codec.hpp"
#include "Parts_Fields.hpp"
#include "Parts_Model.hpp"

#include "Crossing_Codec.hpp"
#include "Crossing_Db.hpp"

#include "Viper_Attachment.hpp"
#include "Viper_Definitions.hpp"
#include "Viper_Path.hpp"
#include "Viper_Values.hpp"
#include "Viper_ValueSetIter.hpp"

namespace Parts::Attachments::Thing::colour {

Viper::UUId const runtimeId{Viper::UUId::parse("2db4209c-05b7-fed3-e045-08819f852028")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Crossing::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ThingKey const & key) {
    return Viper::ValueKey::cast(Crossing::Codec::encode(key));
}

} // namespace

std::set<ThingKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ThingKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Crossing::Codec::decode<ThingKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ThingKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<Colour> get(Viper::AttachmentGetting const & getting, ThingKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Crossing::Codec::decode<Colour>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ThingKey const & key, Colour const & value) {
    mutating.set(attachment(), encodeKey(key), Crossing::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ThingKey const & key, Colour const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Crossing::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ThingKey const & key, Colour const & value) {
    return Crossing::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ThingKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

void setR(Viper::AttachmentMutating & mutating, ThingKey const & key, float value) {
    mutating.update(attachment(), encodeKey(key), Parts::Fields::Colour::rPath(),
                    Crossing::Codec::encode(value));
}


void setG(Viper::AttachmentMutating & mutating, ThingKey const & key, float value) {
    mutating.update(attachment(), encodeKey(key), Parts::Fields::Colour::gPath(),
                    Crossing::Codec::encode(value));
}


void setB(Viper::AttachmentMutating & mutating, ThingKey const & key, float value) {
    mutating.update(attachment(), encodeKey(key), Parts::Fields::Colour::bPath(),
                    Crossing::Codec::encode(value));
}

} // namespace Parts::Attachments::Thing::colour