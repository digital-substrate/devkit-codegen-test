// unité Core — l'implémentation des attachments qu'elle déclare.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

#include "Core_Attachments.hpp"

#include "Core_Codec.hpp"
#include "Core_Fields.hpp"
#include "Core_Model.hpp"

#include "Crossing_Codec.hpp"
#include "Crossing_Db.hpp"

#include "Viper_Attachment.hpp"
#include "Viper_Definitions.hpp"
#include "Viper_Path.hpp"
#include "Viper_Values.hpp"
#include "Viper_ValueSetIter.hpp"

namespace Core::Attachments::Thing::bag {

Viper::UUId const runtimeId{Viper::UUId::parse("e8422ebb-3f90-3554-115a-308eca6b75d5")};

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

std::set<ThingKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ThingKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Crossing::Codec::decode<ThingKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ThingKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<Bag> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ThingKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Crossing::Codec::decode<Bag>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Bag const & value) {
    mutating->set(attachment(), encodeKey(key), Crossing::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Bag const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Crossing::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ThingKey const & key, Bag const & value) {
    return Crossing::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ThingKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

void setMembers(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::set<ThingKey> const & value) {
    mutating->update(attachment(), encodeKey(key), Core::Fields::Bag::membersPath(),
                    Crossing::Codec::encode(value));
}

void unionMembers(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::set<ThingKey> const & value) {
    mutating->unionInSet(attachment(), encodeKey(key), Core::Fields::Bag::membersPath(), Viper::ValueSet::cast(Crossing::Codec::encode(value)));
}

void subtractMembers(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::set<ThingKey> const & value) {
    mutating->subtractInSet(attachment(), encodeKey(key), Core::Fields::Bag::membersPath(), Viper::ValueSet::cast(Crossing::Codec::encode(value)));
}


void setTints(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::map<ThingKey, Colour> const & value) {
    mutating->update(attachment(), encodeKey(key), Core::Fields::Bag::tintsPath(),
                    Crossing::Codec::encode(value));
}

void unionTints(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::map<ThingKey, Colour> const & value) {
    mutating->unionInMap(attachment(), encodeKey(key), Core::Fields::Bag::tintsPath(), Viper::ValueMap::cast(Crossing::Codec::encode(value)));
}

void subtractTints(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::set<Core::ThingKey> const & value) {
    mutating->subtractInMap(attachment(), encodeKey(key), Core::Fields::Bag::tintsPath(), Viper::ValueSet::cast(Crossing::Codec::encode(value)));
}

void updateTints(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::map<ThingKey, Colour> const & value) {
    mutating->updateInMap(attachment(), encodeKey(key), Core::Fields::Bag::tintsPath(), Viper::ValueMap::cast(Crossing::Codec::encode(value)));
}


void setTrail(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Viper::XArray<Colour> const & value) {
    mutating->update(attachment(), encodeKey(key), Core::Fields::Bag::trailPath(),
                    Crossing::Codec::encode(value));
}

void insertTrail(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Viper::UUId const & beforePosition, Viper::UUId const & newPosition, Core::Colour const & value) {
    mutating->insertInXArray(attachment(), encodeKey(key), Core::Fields::Bag::trailPath(),
                            beforePosition, newPosition, Crossing::Codec::encode(value));
}

void updateTrail(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Viper::UUId const & position, Core::Colour const & value) {
    mutating->updateInXArray(attachment(), encodeKey(key), Core::Fields::Bag::trailPath(),
                            position, Crossing::Codec::encode(value));
}

void removeTrail(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Viper::UUId const & position) {
    mutating->removeInXArray(attachment(), encodeKey(key), Core::Fields::Bag::trailPath(), position);
}

} // namespace Core::Attachments::Thing::bag

namespace Core::Attachments::Thing::colour {

Viper::UUId const runtimeId{Viper::UUId::parse("1c970e1f-b2a9-80d7-f588-02c610b5f114")};

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

std::set<ThingKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ThingKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Crossing::Codec::decode<ThingKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ThingKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<Colour> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ThingKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Crossing::Codec::decode<Colour>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Colour const & value) {
    mutating->set(attachment(), encodeKey(key), Crossing::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Colour const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Crossing::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ThingKey const & key, Colour const & value) {
    return Crossing::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ThingKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

void setR(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::uint8_t value) {
    mutating->update(attachment(), encodeKey(key), Core::Fields::Colour::rPath(),
                    Crossing::Codec::encode(value));
}


void setG(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::uint8_t value) {
    mutating->update(attachment(), encodeKey(key), Core::Fields::Colour::gPath(),
                    Crossing::Codec::encode(value));
}


void setB(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::uint8_t value) {
    mutating->update(attachment(), encodeKey(key), Core::Fields::Colour::bPath(),
                    Crossing::Codec::encode(value));
}

} // namespace Core::Attachments::Thing::colour

namespace Core::Attachments::Thing::history {

Viper::UUId const runtimeId{Viper::UUId::parse("44dff56f-9628-52e8-8b6d-74fcebd89beb")};

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

std::set<ThingKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ThingKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Crossing::Codec::decode<ThingKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ThingKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<Viper::XArray<Colour>> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ThingKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Crossing::Codec::decode<Viper::XArray<Colour>>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Viper::XArray<Colour> const & value) {
    mutating->set(attachment(), encodeKey(key), Crossing::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Viper::XArray<Colour> const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Crossing::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ThingKey const & key, Viper::XArray<Colour> const & value) {
    return Crossing::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ThingKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

void insert(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Viper::UUId const & beforePosition, Viper::UUId const & newPosition, Core::Colour const & value) {
    mutating->insertInXArray(attachment(), encodeKey(key), Viper::Path::make(),
                            beforePosition, newPosition, Crossing::Codec::encode(value));
}

void update(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Viper::UUId const & position, Core::Colour const & value) {
    mutating->updateInXArray(attachment(), encodeKey(key), Viper::Path::make(), position, Crossing::Codec::encode(value));
}

void remove(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Viper::UUId const & position) {
    mutating->removeInXArray(attachment(), encodeKey(key), Viper::Path::make(), position);
}

} // namespace Core::Attachments::Thing::history

namespace Core::Attachments::Thing::palette {

Viper::UUId const runtimeId{Viper::UUId::parse("07555083-c220-c293-7992-0b2d535a315e")};

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

std::set<ThingKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ThingKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Crossing::Codec::decode<ThingKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ThingKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<std::map<ThingKey, Colour>> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ThingKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Crossing::Codec::decode<std::map<ThingKey, Colour>>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::map<ThingKey, Colour> const & value) {
    mutating->set(attachment(), encodeKey(key), Crossing::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::map<ThingKey, Colour> const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Crossing::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ThingKey const & key, std::map<ThingKey, Colour> const & value) {
    return Crossing::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ThingKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

void union_(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::map<ThingKey, Colour> const & value) {
    mutating->unionInMap(attachment(), encodeKey(key), Viper::Path::make(), Viper::ValueMap::cast(Crossing::Codec::encode(value)));
}

void subtract(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::set<Core::ThingKey> const & value) {
    mutating->subtractInMap(attachment(), encodeKey(key), Viper::Path::make(), Viper::ValueSet::cast(Crossing::Codec::encode(value)));
}

void update(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::map<ThingKey, Colour> const & value) {
    mutating->updateInMap(attachment(), encodeKey(key), Viper::Path::make(), Viper::ValueMap::cast(Crossing::Codec::encode(value)));
}

} // namespace Core::Attachments::Thing::palette

namespace Core::Attachments::Thing::related {

Viper::UUId const runtimeId{Viper::UUId::parse("78dddddb-13c8-25ce-eb7a-83d42c72c86c")};

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

std::set<ThingKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ThingKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Crossing::Codec::decode<ThingKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ThingKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<std::set<ThingKey>> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ThingKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Crossing::Codec::decode<std::set<ThingKey>>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::set<ThingKey> const & value) {
    mutating->set(attachment(), encodeKey(key), Crossing::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::set<ThingKey> const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Crossing::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ThingKey const & key, std::set<ThingKey> const & value) {
    return Crossing::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ThingKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

void union_(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::set<ThingKey> const & value) {
    mutating->unionInSet(attachment(), encodeKey(key), Viper::Path::make(), Viper::ValueSet::cast(Crossing::Codec::encode(value)));
}

void subtract(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::set<ThingKey> const & value) {
    mutating->subtractInSet(attachment(), encodeKey(key), Viper::Path::make(), Viper::ValueSet::cast(Crossing::Codec::encode(value)));
}

} // namespace Core::Attachments::Thing::related

namespace Core::Attachments::Thing::scalars {

Viper::UUId const runtimeId{Viper::UUId::parse("11386338-c74c-53da-8472-413ecd1a0cce")};

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

std::set<ThingKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ThingKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Crossing::Codec::decode<ThingKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ThingKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<Scalars> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ThingKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Crossing::Codec::decode<Scalars>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Scalars const & value) {
    mutating->set(attachment(), encodeKey(key), Crossing::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Scalars const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Crossing::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ThingKey const & key, Scalars const & value) {
    return Crossing::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ThingKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

void setF_bool(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, bool value) {
    mutating->update(attachment(), encodeKey(key), Core::Fields::Scalars::f_boolPath(),
                    Crossing::Codec::encode(value));
}


void setF_uint8(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::uint8_t value) {
    mutating->update(attachment(), encodeKey(key), Core::Fields::Scalars::f_uint8Path(),
                    Crossing::Codec::encode(value));
}


void setF_uint16(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::uint16_t value) {
    mutating->update(attachment(), encodeKey(key), Core::Fields::Scalars::f_uint16Path(),
                    Crossing::Codec::encode(value));
}


void setF_uint32(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::uint32_t value) {
    mutating->update(attachment(), encodeKey(key), Core::Fields::Scalars::f_uint32Path(),
                    Crossing::Codec::encode(value));
}


void setF_uint64(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::uint64_t value) {
    mutating->update(attachment(), encodeKey(key), Core::Fields::Scalars::f_uint64Path(),
                    Crossing::Codec::encode(value));
}


void setF_int8(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::int8_t value) {
    mutating->update(attachment(), encodeKey(key), Core::Fields::Scalars::f_int8Path(),
                    Crossing::Codec::encode(value));
}


void setF_int16(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::int16_t value) {
    mutating->update(attachment(), encodeKey(key), Core::Fields::Scalars::f_int16Path(),
                    Crossing::Codec::encode(value));
}


void setF_int32(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::int32_t value) {
    mutating->update(attachment(), encodeKey(key), Core::Fields::Scalars::f_int32Path(),
                    Crossing::Codec::encode(value));
}


void setF_int64(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::int64_t value) {
    mutating->update(attachment(), encodeKey(key), Core::Fields::Scalars::f_int64Path(),
                    Crossing::Codec::encode(value));
}


void setF_float(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, float value) {
    mutating->update(attachment(), encodeKey(key), Core::Fields::Scalars::f_floatPath(),
                    Crossing::Codec::encode(value));
}


void setF_double(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, double value) {
    mutating->update(attachment(), encodeKey(key), Core::Fields::Scalars::f_doublePath(),
                    Crossing::Codec::encode(value));
}


void setF_blob_id(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Viper::BlobId const & value) {
    mutating->update(attachment(), encodeKey(key), Core::Fields::Scalars::f_blob_idPath(),
                    Crossing::Codec::encode(value));
}


void setF_commit_id(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Viper::CommitId const & value) {
    mutating->update(attachment(), encodeKey(key), Core::Fields::Scalars::f_commit_idPath(),
                    Crossing::Codec::encode(value));
}


void setF_uuid(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Viper::UUId const & value) {
    mutating->update(attachment(), encodeKey(key), Core::Fields::Scalars::f_uuidPath(),
                    Crossing::Codec::encode(value));
}


void setF_string(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::string const & value) {
    mutating->update(attachment(), encodeKey(key), Core::Fields::Scalars::f_stringPath(),
                    Crossing::Codec::encode(value));
}


void setF_blob(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Viper::Blob const & value) {
    mutating->update(attachment(), encodeKey(key), Core::Fields::Scalars::f_blobPath(),
                    Crossing::Codec::encode(value));
}


void setF_any(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Viper::Any const & value) {
    mutating->update(attachment(), encodeKey(key), Core::Fields::Scalars::f_anyPath(),
                    Crossing::Codec::encode(value));
}


void setF_vec(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::array<std::uint8_t, 2> const & value) {
    mutating->update(attachment(), encodeKey(key), Core::Fields::Scalars::f_vecPath(),
                    Crossing::Codec::encode(value));
}


void setF_mat(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::array<std::array<std::uint8_t, 2>, 2> const & value) {
    mutating->update(attachment(), encodeKey(key), Core::Fields::Scalars::f_matPath(),
                    Crossing::Codec::encode(value));
}

} // namespace Core::Attachments::Thing::scalars