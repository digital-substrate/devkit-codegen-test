// Core — l'implémentation des attachments qu'il déclare.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

#include "Core_Attachments.hpp"

#include "Core_Codec.hpp"
#include "Core_Fields.hpp"
#include "Core_Model.hpp"

#include "Crossing_Codec.hpp"

#include "Viper_Attachment.hpp"
#include "Viper_Definitions.hpp"
#include "Viper_Path.hpp"
#include "Viper_Values.hpp"

namespace Core::Attachments::Thing::colour {

Viper::UUId const runtimeId{Viper::UUId::parse("1c970e1f-b2a9-80d7-f588-02c610b5f114")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Crossing::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

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

void setR(Viper::AttachmentMutating & mutating, ThingKey const & key, std::uint8_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Core::Fields::Colour::rPath(),
                    Crossing::Codec::encode(value));
}

void setG(Viper::AttachmentMutating & mutating, ThingKey const & key, std::uint8_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Core::Fields::Colour::gPath(),
                    Crossing::Codec::encode(value));
}

void setB(Viper::AttachmentMutating & mutating, ThingKey const & key, std::uint8_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Core::Fields::Colour::bPath(),
                    Crossing::Codec::encode(value));
}

} // namespace Core::Attachments::Thing::colour

namespace Core::Attachments::Thing::scalars {

Viper::UUId const runtimeId{Viper::UUId::parse("11386338-c74c-53da-8472-413ecd1a0cce")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Crossing::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

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

std::optional<Scalars> get(Viper::AttachmentGetting const & getting, ThingKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Crossing::Codec::decode<Scalars>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ThingKey const & key, Scalars const & value) {
    mutating.set(attachment(), encodeKey(key), Crossing::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ThingKey const & key, Scalars const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Crossing::Codec::encode(value), recursive);
}

void setF_bool(Viper::AttachmentMutating & mutating, ThingKey const & key, bool value) {
    mutating.update(attachment(), encodeKey(key),
                    Core::Fields::Scalars::f_boolPath(),
                    Crossing::Codec::encode(value));
}

void setF_uint8(Viper::AttachmentMutating & mutating, ThingKey const & key, std::uint8_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Core::Fields::Scalars::f_uint8Path(),
                    Crossing::Codec::encode(value));
}

void setF_uint16(Viper::AttachmentMutating & mutating, ThingKey const & key, std::uint16_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Core::Fields::Scalars::f_uint16Path(),
                    Crossing::Codec::encode(value));
}

void setF_uint32(Viper::AttachmentMutating & mutating, ThingKey const & key, std::uint32_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Core::Fields::Scalars::f_uint32Path(),
                    Crossing::Codec::encode(value));
}

void setF_uint64(Viper::AttachmentMutating & mutating, ThingKey const & key, std::uint64_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Core::Fields::Scalars::f_uint64Path(),
                    Crossing::Codec::encode(value));
}

void setF_int8(Viper::AttachmentMutating & mutating, ThingKey const & key, std::int8_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Core::Fields::Scalars::f_int8Path(),
                    Crossing::Codec::encode(value));
}

void setF_int16(Viper::AttachmentMutating & mutating, ThingKey const & key, std::int16_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Core::Fields::Scalars::f_int16Path(),
                    Crossing::Codec::encode(value));
}

void setF_int32(Viper::AttachmentMutating & mutating, ThingKey const & key, std::int32_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Core::Fields::Scalars::f_int32Path(),
                    Crossing::Codec::encode(value));
}

void setF_int64(Viper::AttachmentMutating & mutating, ThingKey const & key, std::int64_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Core::Fields::Scalars::f_int64Path(),
                    Crossing::Codec::encode(value));
}

void setF_float(Viper::AttachmentMutating & mutating, ThingKey const & key, float value) {
    mutating.update(attachment(), encodeKey(key),
                    Core::Fields::Scalars::f_floatPath(),
                    Crossing::Codec::encode(value));
}

void setF_double(Viper::AttachmentMutating & mutating, ThingKey const & key, double value) {
    mutating.update(attachment(), encodeKey(key),
                    Core::Fields::Scalars::f_doublePath(),
                    Crossing::Codec::encode(value));
}

void setF_blob_id(Viper::AttachmentMutating & mutating, ThingKey const & key, Viper::BlobId const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Core::Fields::Scalars::f_blob_idPath(),
                    Crossing::Codec::encode(value));
}

void setF_commit_id(Viper::AttachmentMutating & mutating, ThingKey const & key, Viper::CommitId const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Core::Fields::Scalars::f_commit_idPath(),
                    Crossing::Codec::encode(value));
}

void setF_uuid(Viper::AttachmentMutating & mutating, ThingKey const & key, Viper::UUId const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Core::Fields::Scalars::f_uuidPath(),
                    Crossing::Codec::encode(value));
}

void setF_string(Viper::AttachmentMutating & mutating, ThingKey const & key, std::string const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Core::Fields::Scalars::f_stringPath(),
                    Crossing::Codec::encode(value));
}

void setF_blob(Viper::AttachmentMutating & mutating, ThingKey const & key, Viper::Blob const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Core::Fields::Scalars::f_blobPath(),
                    Crossing::Codec::encode(value));
}

void setF_any(Viper::AttachmentMutating & mutating, ThingKey const & key, Viper::Any const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Core::Fields::Scalars::f_anyPath(),
                    Crossing::Codec::encode(value));
}

void setF_vec(Viper::AttachmentMutating & mutating, ThingKey const & key, std::array<std::uint8_t, 2> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Core::Fields::Scalars::f_vecPath(),
                    Crossing::Codec::encode(value));
}

void setF_mat(Viper::AttachmentMutating & mutating, ThingKey const & key, std::array<std::array<std::uint8_t, 2>, 2> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Core::Fields::Scalars::f_matPath(),
                    Crossing::Codec::encode(value));
}

} // namespace Core::Attachments::Thing::scalars