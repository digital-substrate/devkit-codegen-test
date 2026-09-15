// unité Demo — l'implémentation des attachments qu'elle déclare.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/features/Features.dsm.json by kibo-2.0.0.jar

#include "Demo_Attachments.hpp"

#include "Demo_Codec.hpp"
#include "Demo_Fields.hpp"
#include "Demo_Model.hpp"

#include "Features_Codec.hpp"
#include "Features_Db.hpp"

#include "Viper_Attachment.hpp"
#include "Viper_Definitions.hpp"
#include "Viper_Path.hpp"
#include "Viper_Values.hpp"
#include "Viper_ValueSetIter.hpp"

namespace Demo::Attachments::AnyConcept::propertiesAnyConceptAny {

Viper::UUId const runtimeId{Viper::UUId::parse("8de8e47b-58e8-5699-59a7-5a3193aef7f1")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(::Features::AnyConceptKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<::Features::AnyConceptKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<::Features::AnyConceptKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<::Features::AnyConceptKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ::Features::AnyConceptKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<Viper::Any> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ::Features::AnyConceptKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<Viper::Any>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ::Features::AnyConceptKey const & key, Viper::Any const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ::Features::AnyConceptKey const & key, Viper::Any const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ::Features::AnyConceptKey const & key, Viper::Any const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ::Features::AnyConceptKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::AnyConcept::propertiesAnyConceptAny

namespace Demo::Attachments::ConceptA::properties {

Viper::UUId const runtimeId{Viper::UUId::parse("3b79131f-a619-5b33-66ab-3b78ca749cd0")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptAKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptAKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptAKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptAKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptAKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<StructureV> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptAKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<StructureV>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, StructureV const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, StructureV const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key, StructureV const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

void setF_bool(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, bool value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_boolPath(),
                    Features::Codec::encode(value));
}


void setF_uint8(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::uint8_t value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_uint8Path(),
                    Features::Codec::encode(value));
}


void setF_uint16(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::uint16_t value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_uint16Path(),
                    Features::Codec::encode(value));
}


void setF_uint32(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::uint32_t value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_uint32Path(),
                    Features::Codec::encode(value));
}


void setF_uint64(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::uint64_t value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_uint64Path(),
                    Features::Codec::encode(value));
}


void setF_int8(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::int8_t value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_int8Path(),
                    Features::Codec::encode(value));
}


void setF_int16(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::int16_t value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_int16Path(),
                    Features::Codec::encode(value));
}


void setF_int32(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::int32_t value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_int32Path(),
                    Features::Codec::encode(value));
}


void setF_int64(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::int64_t value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_int64Path(),
                    Features::Codec::encode(value));
}


void setF_float(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, float value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_floatPath(),
                    Features::Codec::encode(value));
}


void setF_double(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, double value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_doublePath(),
                    Features::Codec::encode(value));
}


void setF_uuid(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, Viper::UUId const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_uuidPath(),
                    Features::Codec::encode(value));
}


void setF_string(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::string const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_stringPath(),
                    Features::Codec::encode(value));
}


void setF_vec(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::array<std::uint8_t, 2> const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_vecPath(),
                    Features::Codec::encode(value));
}


void setF_mat(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::array<std::array<std::uint8_t, 3>, 2> const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_matPath(),
                    Features::Codec::encode(value));
}


void setF_tuple(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::tuple<std::uint8_t, std::string> const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_tuplePath(),
                    Features::Codec::encode(value));
}


void setF_optional(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::optional<std::uint8_t> const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_optionalPath(),
                    Features::Codec::encode(value));
}


void setF_vector(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::vector<std::uint8_t> const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_vectorPath(),
                    Features::Codec::encode(value));
}


void setF_set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::set<std::uint8_t> const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_setPath(),
                    Features::Codec::encode(value));
}

void unionF_set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::set<std::uint8_t> const & value) {
    mutating->unionInSet(attachment(), encodeKey(key), Demo::Fields::StructureV::f_setPath(), Viper::ValueSet::cast(Features::Codec::encode(value)));
}

void subtractF_set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::set<std::uint8_t> const & value) {
    mutating->subtractInSet(attachment(), encodeKey(key), Demo::Fields::StructureV::f_setPath(), Viper::ValueSet::cast(Features::Codec::encode(value)));
}


void setF_map(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::map<std::uint8_t, std::string> const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_mapPath(),
                    Features::Codec::encode(value));
}

void unionF_map(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::map<std::uint8_t, std::string> const & value) {
    mutating->unionInMap(attachment(), encodeKey(key), Demo::Fields::StructureV::f_mapPath(), Viper::ValueMap::cast(Features::Codec::encode(value)));
}

void subtractF_map(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::set<std::uint8_t> const & value) {
    mutating->subtractInMap(attachment(), encodeKey(key), Demo::Fields::StructureV::f_mapPath(), Viper::ValueSet::cast(Features::Codec::encode(value)));
}

void updateF_map(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::map<std::uint8_t, std::string> const & value) {
    mutating->updateInMap(attachment(), encodeKey(key), Demo::Fields::StructureV::f_mapPath(), Viper::ValueMap::cast(Features::Codec::encode(value)));
}


void setF_E(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, EnumerationE value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_EPath(),
                    Features::Codec::encode(value));
}


void setF_S(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, StructureS const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_SPath(),
                    Features::Codec::encode(value));
}


void setF_T(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, StructureT const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_TPath(),
                    Features::Codec::encode(value));
}

} // namespace Demo::Attachments::ConceptA::properties

namespace Demo::Attachments::ConceptA::propertiesInt8 {

Viper::UUId const runtimeId{Viper::UUId::parse("58ce283d-b8eb-1f01-3841-854fccd54fd7")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptAKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptAKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptAKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptAKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptAKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<std::int8_t> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptAKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::int8_t>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::int8_t const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::int8_t const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key, std::int8_t const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptA::propertiesInt8

namespace Demo::Attachments::ConceptA::propertiesMapInt8String {

Viper::UUId const runtimeId{Viper::UUId::parse("0eb140e3-5247-d7ad-649f-5fa124359ee2")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptAKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptAKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptAKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptAKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptAKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<std::map<std::int8_t, std::string>> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptAKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::map<std::int8_t, std::string>>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::map<std::int8_t, std::string> const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::map<std::int8_t, std::string> const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key, std::map<std::int8_t, std::string> const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

void union_(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::map<std::int8_t, std::string> const & value) {
    mutating->unionInMap(attachment(), encodeKey(key), Viper::Path::make(), Viper::ValueMap::cast(Features::Codec::encode(value)));
}

void subtract(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::set<std::int8_t> const & value) {
    mutating->subtractInMap(attachment(), encodeKey(key), Viper::Path::make(), Viper::ValueSet::cast(Features::Codec::encode(value)));
}

void update(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::map<std::int8_t, std::string> const & value) {
    mutating->updateInMap(attachment(), encodeKey(key), Viper::Path::make(), Viper::ValueMap::cast(Features::Codec::encode(value)));
}

} // namespace Demo::Attachments::ConceptA::propertiesMapInt8String

namespace Demo::Attachments::ConceptA::propertiesSeInt8 {

Viper::UUId const runtimeId{Viper::UUId::parse("ad45f798-b25a-0421-c523-713ff624383e")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptAKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptAKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptAKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptAKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptAKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<std::set<std::int8_t>> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptAKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::set<std::int8_t>>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::set<std::int8_t> const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::set<std::int8_t> const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key, std::set<std::int8_t> const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

void union_(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::set<std::int8_t> const & value) {
    mutating->unionInSet(attachment(), encodeKey(key), Viper::Path::make(), Viper::ValueSet::cast(Features::Codec::encode(value)));
}

void subtract(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, std::set<std::int8_t> const & value) {
    mutating->subtractInSet(attachment(), encodeKey(key), Viper::Path::make(), Viper::ValueSet::cast(Features::Codec::encode(value)));
}

} // namespace Demo::Attachments::ConceptA::propertiesSeInt8

namespace Demo::Attachments::ConceptA::propertiesXArray {

Viper::UUId const runtimeId{Viper::UUId::parse("ff9d7eda-5ad0-d217-d910-7d2adfad208f")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptAKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptAKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptAKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptAKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptAKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<Viper::XArray<std::int8_t>> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptAKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<Viper::XArray<std::int8_t>>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, Viper::XArray<std::int8_t> const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, Viper::XArray<std::int8_t> const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key, Viper::XArray<std::int8_t> const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

void insert(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, Viper::UUId const & beforePosition, Viper::UUId const & newPosition, std::int8_t value) {
    mutating->insertInXArray(attachment(), encodeKey(key), Viper::Path::make(),
                            beforePosition, newPosition, Features::Codec::encode(value));
}

void update(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, Viper::UUId const & position, std::int8_t value) {
    mutating->updateInXArray(attachment(), encodeKey(key), Viper::Path::make(), position, Features::Codec::encode(value));
}

void remove(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptAKey const & key, Viper::UUId const & position) {
    mutating->removeInXArray(attachment(), encodeKey(key), Viper::Path::make(), position);
}

} // namespace Demo::Attachments::ConceptA::propertiesXArray

namespace Demo::Attachments::ConceptB::propertiesB {

Viper::UUId const runtimeId{Viper::UUId::parse("c117fd64-7b82-f4ab-164c-efb528a408bc")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptBKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptBKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptBKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptBKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptBKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<StructureT> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptBKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<StructureT>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptBKey const & key, StructureT const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptBKey const & key, StructureT const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptBKey const & key, StructureT const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptBKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

void setField_string(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptBKey const & key, std::string const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureT::field_stringPath(),
                    Features::Codec::encode(value));
}


void setField_structure_s(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptBKey const & key, StructureS const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureT::field_structure_sPath(),
                    Features::Codec::encode(value));
}

} // namespace Demo::Attachments::ConceptB::propertiesB

namespace Demo::Attachments::ConceptC::propertiesC {

Viper::UUId const runtimeId{Viper::UUId::parse("7f6d8d89-d32a-3214-ed11-3f23b7faaf1e")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<StructureU> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<StructureU>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, StructureU const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, StructureU const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCKey const & key, StructureU const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

void setF_bool(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, bool value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_boolPath(),
                    Features::Codec::encode(value));
}


void setF_uint8(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::uint8_t value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_uint8Path(),
                    Features::Codec::encode(value));
}


void setF_uint16(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::uint16_t value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_uint16Path(),
                    Features::Codec::encode(value));
}


void setF_uint32(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::uint32_t value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_uint32Path(),
                    Features::Codec::encode(value));
}


void setF_uint64(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::uint64_t value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_uint64Path(),
                    Features::Codec::encode(value));
}


void setF_int8(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::int8_t value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_int8Path(),
                    Features::Codec::encode(value));
}


void setF_int16(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::int16_t value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_int16Path(),
                    Features::Codec::encode(value));
}


void setF_int32(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::int32_t value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_int32Path(),
                    Features::Codec::encode(value));
}


void setF_int64(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::int64_t value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_int64Path(),
                    Features::Codec::encode(value));
}


void setF_float(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, float value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_floatPath(),
                    Features::Codec::encode(value));
}


void setF_double(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, double value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_doublePath(),
                    Features::Codec::encode(value));
}


void setF_blob_id(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, Viper::BlobId const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_blob_idPath(),
                    Features::Codec::encode(value));
}


void setF_commit_id(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, Viper::CommitId const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_commit_idPath(),
                    Features::Codec::encode(value));
}


void setF_uuid(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, Viper::UUId const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_uuidPath(),
                    Features::Codec::encode(value));
}


void setF_string(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::string const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_stringPath(),
                    Features::Codec::encode(value));
}


void setF_blob(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, Viper::Blob const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_blobPath(),
                    Features::Codec::encode(value));
}


void setF_vec(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::array<std::uint8_t, 2> const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_vecPath(),
                    Features::Codec::encode(value));
}


void setF_mat(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::array<std::array<std::uint8_t, 2>, 2> const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_matPath(),
                    Features::Codec::encode(value));
}


void setF_tuple(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::tuple<std::uint8_t, std::string> const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_tuplePath(),
                    Features::Codec::encode(value));
}


void setF_optional(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::optional<std::uint8_t> const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_optionalPath(),
                    Features::Codec::encode(value));
}


void setF_vector(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::vector<std::uint8_t> const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_vectorPath(),
                    Features::Codec::encode(value));
}


void setF_set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::set<std::uint8_t> const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_setPath(),
                    Features::Codec::encode(value));
}

void unionF_set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::set<std::uint8_t> const & value) {
    mutating->unionInSet(attachment(), encodeKey(key), Demo::Fields::StructureU::f_setPath(), Viper::ValueSet::cast(Features::Codec::encode(value)));
}

void subtractF_set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::set<std::uint8_t> const & value) {
    mutating->subtractInSet(attachment(), encodeKey(key), Demo::Fields::StructureU::f_setPath(), Viper::ValueSet::cast(Features::Codec::encode(value)));
}


void setF_set_s(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::set<StructureS> const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_set_sPath(),
                    Features::Codec::encode(value));
}

void unionF_set_s(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::set<StructureS> const & value) {
    mutating->unionInSet(attachment(), encodeKey(key), Demo::Fields::StructureU::f_set_sPath(), Viper::ValueSet::cast(Features::Codec::encode(value)));
}

void subtractF_set_s(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::set<StructureS> const & value) {
    mutating->subtractInSet(attachment(), encodeKey(key), Demo::Fields::StructureU::f_set_sPath(), Viper::ValueSet::cast(Features::Codec::encode(value)));
}


void setF_map_s1(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::map<StructureS, std::string> const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_map_s1Path(),
                    Features::Codec::encode(value));
}

void unionF_map_s1(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::map<StructureS, std::string> const & value) {
    mutating->unionInMap(attachment(), encodeKey(key), Demo::Fields::StructureU::f_map_s1Path(), Viper::ValueMap::cast(Features::Codec::encode(value)));
}

void subtractF_map_s1(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::set<Demo::StructureS> const & value) {
    mutating->subtractInMap(attachment(), encodeKey(key), Demo::Fields::StructureU::f_map_s1Path(), Viper::ValueSet::cast(Features::Codec::encode(value)));
}

void updateF_map_s1(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::map<StructureS, std::string> const & value) {
    mutating->updateInMap(attachment(), encodeKey(key), Demo::Fields::StructureU::f_map_s1Path(), Viper::ValueMap::cast(Features::Codec::encode(value)));
}


void setF_map_s2(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::map<std::string, StructureS> const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_map_s2Path(),
                    Features::Codec::encode(value));
}

void unionF_map_s2(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::map<std::string, StructureS> const & value) {
    mutating->unionInMap(attachment(), encodeKey(key), Demo::Fields::StructureU::f_map_s2Path(), Viper::ValueMap::cast(Features::Codec::encode(value)));
}

void subtractF_map_s2(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::set<std::string> const & value) {
    mutating->subtractInMap(attachment(), encodeKey(key), Demo::Fields::StructureU::f_map_s2Path(), Viper::ValueSet::cast(Features::Codec::encode(value)));
}

void updateF_map_s2(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::map<std::string, StructureS> const & value) {
    mutating->updateInMap(attachment(), encodeKey(key), Demo::Fields::StructureU::f_map_s2Path(), Viper::ValueMap::cast(Features::Codec::encode(value)));
}


void setF_xarray(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, Viper::XArray<std::uint8_t> const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_xarrayPath(),
                    Features::Codec::encode(value));
}

void insertF_xarray(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, Viper::UUId const & beforePosition, Viper::UUId const & newPosition, std::uint8_t value) {
    mutating->insertInXArray(attachment(), encodeKey(key), Demo::Fields::StructureU::f_xarrayPath(),
                            beforePosition, newPosition, Features::Codec::encode(value));
}

void updateF_xarray(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, Viper::UUId const & position, std::uint8_t value) {
    mutating->updateInXArray(attachment(), encodeKey(key), Demo::Fields::StructureU::f_xarrayPath(),
                            position, Features::Codec::encode(value));
}

void removeF_xarray(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, Viper::UUId const & position) {
    mutating->removeInXArray(attachment(), encodeKey(key), Demo::Fields::StructureU::f_xarrayPath(), position);
}


void setF_xarray_s(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, Viper::XArray<StructureS> const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_xarray_sPath(),
                    Features::Codec::encode(value));
}

void insertF_xarray_s(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, Viper::UUId const & beforePosition, Viper::UUId const & newPosition, Demo::StructureS const & value) {
    mutating->insertInXArray(attachment(), encodeKey(key), Demo::Fields::StructureU::f_xarray_sPath(),
                            beforePosition, newPosition, Features::Codec::encode(value));
}

void updateF_xarray_s(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, Viper::UUId const & position, Demo::StructureS const & value) {
    mutating->updateInXArray(attachment(), encodeKey(key), Demo::Fields::StructureU::f_xarray_sPath(),
                            position, Features::Codec::encode(value));
}

void removeF_xarray_s(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, Viper::UUId const & position) {
    mutating->removeInXArray(attachment(), encodeKey(key), Demo::Fields::StructureU::f_xarray_sPath(), position);
}


void setF_map_vs(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::map<std::vector<StructureS>, std::string> const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_map_vsPath(),
                    Features::Codec::encode(value));
}

void unionF_map_vs(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::map<std::vector<StructureS>, std::string> const & value) {
    mutating->unionInMap(attachment(), encodeKey(key), Demo::Fields::StructureU::f_map_vsPath(), Viper::ValueMap::cast(Features::Codec::encode(value)));
}

void subtractF_map_vs(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::set<std::vector<Demo::StructureS>> const & value) {
    mutating->subtractInMap(attachment(), encodeKey(key), Demo::Fields::StructureU::f_map_vsPath(), Viper::ValueSet::cast(Features::Codec::encode(value)));
}

void updateF_map_vs(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::map<std::vector<StructureS>, std::string> const & value) {
    mutating->updateInMap(attachment(), encodeKey(key), Demo::Fields::StructureU::f_map_vsPath(), Viper::ValueMap::cast(Features::Codec::encode(value)));
}


void setF_variant(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, std::variant<std::string, std::uint8_t, StructureS> const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_variantPath(),
                    Features::Codec::encode(value));
}


void setF_any(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, Viper::Any const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_anyPath(),
                    Features::Codec::encode(value));
}


void setF_E(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, EnumerationE value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_EPath(),
                    Features::Codec::encode(value));
}


void setF_S(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, StructureS const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_SPath(),
                    Features::Codec::encode(value));
}


void setF_T(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, StructureT const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_TPath(),
                    Features::Codec::encode(value));
}


void setF_A(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, ConceptAKey const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_APath(),
                    Features::Codec::encode(value));
}


void setF_B(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, ConceptBKey const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_BPath(),
                    Features::Codec::encode(value));
}


void setF_C(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, ConceptCKey const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_CPath(),
                    Features::Codec::encode(value));
}


void setF_D(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, ConceptDKey const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_DPath(),
                    Features::Codec::encode(value));
}


void setF_Klub(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, KlubKey const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_KlubPath(),
                    Features::Codec::encode(value));
}


void setF_any_concept(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCKey const & key, ::Features::AnyConceptKey const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureU::f_any_conceptPath(),
                    Features::Codec::encode(value));
}

} // namespace Demo::Attachments::ConceptC::propertiesC

namespace Demo::Attachments::ConceptCoverage::docAny {

Viper::UUId const runtimeId{Viper::UUId::parse("20a71745-30fb-4f1b-2245-d331c323bbba")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<Viper::Any> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<Viper::Any>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, Viper::Any const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, Viper::Any const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, Viper::Any const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptCoverage::docAny

namespace Demo::Attachments::ConceptCoverage::docAnyConceptKey {

Viper::UUId const runtimeId{Viper::UUId::parse("ab54b0a8-596a-40fc-6ef1-f1d2eba54f5c")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<::Features::AnyConceptKey> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<::Features::AnyConceptKey>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, ::Features::AnyConceptKey const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, ::Features::AnyConceptKey const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, ::Features::AnyConceptKey const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptCoverage::docAnyConceptKey

namespace Demo::Attachments::ConceptCoverage::docBlob {

Viper::UUId const runtimeId{Viper::UUId::parse("e80aaf93-0656-f497-1372-20158ecea8fb")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<Viper::Blob> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<Viper::Blob>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, Viper::Blob const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, Viper::Blob const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, Viper::Blob const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptCoverage::docBlob

namespace Demo::Attachments::ConceptCoverage::docBlobId {

Viper::UUId const runtimeId{Viper::UUId::parse("8dce567e-111b-bddf-7448-1abc8261ac90")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<Viper::BlobId> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<Viper::BlobId>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, Viper::BlobId const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, Viper::BlobId const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, Viper::BlobId const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptCoverage::docBlobId

namespace Demo::Attachments::ConceptCoverage::docBool {

Viper::UUId const runtimeId{Viper::UUId::parse("de0efd5b-90bb-216f-03f8-cbf32245a423")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<bool> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<bool>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, bool const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, bool const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, bool const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptCoverage::docBool

namespace Demo::Attachments::ConceptCoverage::docClubKey {

Viper::UUId const runtimeId{Viper::UUId::parse("6c8c6c4a-f99b-1737-f3e9-b60da806f18b")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<KlubKey> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<KlubKey>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, KlubKey const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, KlubKey const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, KlubKey const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptCoverage::docClubKey

namespace Demo::Attachments::ConceptCoverage::docCommitId {

Viper::UUId const runtimeId{Viper::UUId::parse("8bc4885f-0e59-2156-6534-f71674e16a62")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<Viper::CommitId> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<Viper::CommitId>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, Viper::CommitId const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, Viper::CommitId const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, Viper::CommitId const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptCoverage::docCommitId

namespace Demo::Attachments::ConceptCoverage::docConceptKey {

Viper::UUId const runtimeId{Viper::UUId::parse("e46092d8-19d2-786f-8ec2-ffe4eb96a2b0")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<ConceptAKey> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<ConceptAKey>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, ConceptAKey const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, ConceptAKey const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, ConceptAKey const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptCoverage::docConceptKey

namespace Demo::Attachments::ConceptCoverage::docConceptKeyB {

Viper::UUId const runtimeId{Viper::UUId::parse("72eb0057-8f6c-7e05-f68e-36ec9bbdc0e6")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<ConceptBKey> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<ConceptBKey>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, ConceptBKey const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, ConceptBKey const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, ConceptBKey const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptCoverage::docConceptKeyB

namespace Demo::Attachments::ConceptCoverage::docDouble {

Viper::UUId const runtimeId{Viper::UUId::parse("ddcc4ebf-809b-1186-a81d-e04887a55c28")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<double> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<double>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, double const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, double const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, double const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptCoverage::docDouble

namespace Demo::Attachments::ConceptCoverage::docEnumeration {

Viper::UUId const runtimeId{Viper::UUId::parse("297e6910-d347-da0c-3dd6-563406dc742f")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<EnumerationE> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<EnumerationE>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, EnumerationE const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, EnumerationE const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, EnumerationE const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptCoverage::docEnumeration

namespace Demo::Attachments::ConceptCoverage::docFloat {

Viper::UUId const runtimeId{Viper::UUId::parse("59dc723c-e718-31bd-93e1-fce13b975469")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<float> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<float>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, float const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, float const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, float const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptCoverage::docFloat

namespace Demo::Attachments::ConceptCoverage::docInt16 {

Viper::UUId const runtimeId{Viper::UUId::parse("138e62f6-c93a-11e6-8cbb-582c7de65a27")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<std::int16_t> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::int16_t>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::int16_t const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::int16_t const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::int16_t const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptCoverage::docInt16

namespace Demo::Attachments::ConceptCoverage::docInt32 {

Viper::UUId const runtimeId{Viper::UUId::parse("83d4d1bf-497b-e2ad-4efc-09509903ef47")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<std::int32_t> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::int32_t>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::int32_t const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::int32_t const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::int32_t const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptCoverage::docInt32

namespace Demo::Attachments::ConceptCoverage::docInt64 {

Viper::UUId const runtimeId{Viper::UUId::parse("bb3c8bde-0fd6-0535-4a63-361ba70dbe9c")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<std::int64_t> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::int64_t>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::int64_t const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::int64_t const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::int64_t const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptCoverage::docInt64

namespace Demo::Attachments::ConceptCoverage::docInt8 {

Viper::UUId const runtimeId{Viper::UUId::parse("0eb18fdd-6c1b-1584-34c8-f8356d4bc05d")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<std::int8_t> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::int8_t>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::int8_t const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::int8_t const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::int8_t const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptCoverage::docInt8

namespace Demo::Attachments::ConceptCoverage::docMap {

Viper::UUId const runtimeId{Viper::UUId::parse("d06b8489-8bd1-a8ff-4e64-d95c5771208f")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<std::map<std::uint8_t, std::string>> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::map<std::uint8_t, std::string>>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::map<std::uint8_t, std::string> const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::map<std::uint8_t, std::string> const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::map<std::uint8_t, std::string> const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

void union_(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::map<std::uint8_t, std::string> const & value) {
    mutating->unionInMap(attachment(), encodeKey(key), Viper::Path::make(), Viper::ValueMap::cast(Features::Codec::encode(value)));
}

void subtract(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::set<std::uint8_t> const & value) {
    mutating->subtractInMap(attachment(), encodeKey(key), Viper::Path::make(), Viper::ValueSet::cast(Features::Codec::encode(value)));
}

void update(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::map<std::uint8_t, std::string> const & value) {
    mutating->updateInMap(attachment(), encodeKey(key), Viper::Path::make(), Viper::ValueMap::cast(Features::Codec::encode(value)));
}

} // namespace Demo::Attachments::ConceptCoverage::docMap

namespace Demo::Attachments::ConceptCoverage::docMat {

Viper::UUId const runtimeId{Viper::UUId::parse("43e79483-eead-0925-cedd-78a45ce47d98")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<std::array<std::array<std::uint8_t, 2>, 2>> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::array<std::array<std::uint8_t, 2>, 2>>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::array<std::array<std::uint8_t, 2>, 2> const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::array<std::array<std::uint8_t, 2>, 2> const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::array<std::array<std::uint8_t, 2>, 2> const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptCoverage::docMat

namespace Demo::Attachments::ConceptCoverage::docOptional {

Viper::UUId const runtimeId{Viper::UUId::parse("92e537a9-7a80-e98f-6e44-8a463cf9a970")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<std::optional<std::uint8_t>> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::optional<std::uint8_t>>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::optional<std::uint8_t> const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::optional<std::uint8_t> const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::optional<std::uint8_t> const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptCoverage::docOptional

namespace Demo::Attachments::ConceptCoverage::docSet {

Viper::UUId const runtimeId{Viper::UUId::parse("7793f2b3-58ab-a3a3-bd44-04cf41b58cdc")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<std::set<std::uint8_t>> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::set<std::uint8_t>>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::set<std::uint8_t> const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::set<std::uint8_t> const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::set<std::uint8_t> const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

void union_(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::set<std::uint8_t> const & value) {
    mutating->unionInSet(attachment(), encodeKey(key), Viper::Path::make(), Viper::ValueSet::cast(Features::Codec::encode(value)));
}

void subtract(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::set<std::uint8_t> const & value) {
    mutating->subtractInSet(attachment(), encodeKey(key), Viper::Path::make(), Viper::ValueSet::cast(Features::Codec::encode(value)));
}

} // namespace Demo::Attachments::ConceptCoverage::docSet

namespace Demo::Attachments::ConceptCoverage::docString {

Viper::UUId const runtimeId{Viper::UUId::parse("9403f10d-288e-00cc-1169-f9a544777dbc")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<std::string> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::string>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::string const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::string const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::string const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptCoverage::docString

namespace Demo::Attachments::ConceptCoverage::docStructureSingleField {

Viper::UUId const runtimeId{Viper::UUId::parse("19ebae3f-d189-04a2-dea3-deb80ece9ff8")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<StructureW> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<StructureW>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, StructureW const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, StructureW const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, StructureW const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

void setF_single(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::uint8_t value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureW::f_singlePath(),
                    Features::Codec::encode(value));
}

} // namespace Demo::Attachments::ConceptCoverage::docStructureSingleField

namespace Demo::Attachments::ConceptCoverage::docTuple {

Viper::UUId const runtimeId{Viper::UUId::parse("d51d4c9f-f9cd-fe62-4417-28021df7961c")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<std::tuple<std::uint8_t, std::string>> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::tuple<std::uint8_t, std::string>>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::tuple<std::uint8_t, std::string> const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::tuple<std::uint8_t, std::string> const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::tuple<std::uint8_t, std::string> const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptCoverage::docTuple

namespace Demo::Attachments::ConceptCoverage::docUInt16 {

Viper::UUId const runtimeId{Viper::UUId::parse("3ae2904f-b0ed-d9e8-448a-fbd6d80be212")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<std::uint16_t> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::uint16_t>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::uint16_t const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::uint16_t const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::uint16_t const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptCoverage::docUInt16

namespace Demo::Attachments::ConceptCoverage::docUInt32 {

Viper::UUId const runtimeId{Viper::UUId::parse("85ced0f5-1127-8750-a18e-3ecbfbe4813a")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<std::uint32_t> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::uint32_t>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::uint32_t const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::uint32_t const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::uint32_t const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptCoverage::docUInt32

namespace Demo::Attachments::ConceptCoverage::docUInt64 {

Viper::UUId const runtimeId{Viper::UUId::parse("00a3fbe9-15b1-8e1f-fc42-c01d845ccc9a")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<std::uint64_t> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::uint64_t>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::uint64_t const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::uint64_t const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::uint64_t const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptCoverage::docUInt64

namespace Demo::Attachments::ConceptCoverage::docUInt8 {

Viper::UUId const runtimeId{Viper::UUId::parse("5ac282e6-15c4-0a8c-bab9-b14ac6a7f9ed")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<std::uint8_t> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::uint8_t>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::uint8_t const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::uint8_t const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::uint8_t const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptCoverage::docUInt8

namespace Demo::Attachments::ConceptCoverage::docUUId {

Viper::UUId const runtimeId{Viper::UUId::parse("a79058d8-5ee7-303d-1d19-50f01983a35b")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<Viper::UUId> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<Viper::UUId>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, Viper::UUId const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, Viper::UUId const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, Viper::UUId const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptCoverage::docUUId

namespace Demo::Attachments::ConceptCoverage::docVariant {

Viper::UUId const runtimeId{Viper::UUId::parse("b7a81faa-fea8-a2cb-760b-edf353f16c63")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<std::variant<std::string, std::uint8_t>> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::variant<std::string, std::uint8_t>>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::variant<std::string, std::uint8_t> const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::variant<std::string, std::uint8_t> const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::variant<std::string, std::uint8_t> const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptCoverage::docVariant

namespace Demo::Attachments::ConceptCoverage::docVec {

Viper::UUId const runtimeId{Viper::UUId::parse("73d224c0-d38f-4b5a-d225-bad481cec150")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<std::array<std::uint8_t, 2>> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::array<std::uint8_t, 2>>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::array<std::uint8_t, 2> const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::array<std::uint8_t, 2> const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::array<std::uint8_t, 2> const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptCoverage::docVec

namespace Demo::Attachments::ConceptCoverage::docVector {

Viper::UUId const runtimeId{Viper::UUId::parse("ebb21187-7004-e7fa-23e6-690803352742")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<std::vector<std::uint8_t>> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::vector<std::uint8_t>>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::vector<std::uint8_t> const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, std::vector<std::uint8_t> const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::vector<std::uint8_t> const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}
} // namespace Demo::Attachments::ConceptCoverage::docVector

namespace Demo::Attachments::ConceptCoverage::docXArray {

Viper::UUId const runtimeId{Viper::UUId::parse("d45a1e55-9fc4-037e-5ce7-856093a638be")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<Viper::XArray<std::uint8_t>> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ConceptCoverageKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<Viper::XArray<std::uint8_t>>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, Viper::XArray<std::uint8_t> const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, Viper::XArray<std::uint8_t> const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, Viper::XArray<std::uint8_t> const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

void insert(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, Viper::UUId const & beforePosition, Viper::UUId const & newPosition, std::uint8_t value) {
    mutating->insertInXArray(attachment(), encodeKey(key), Viper::Path::make(),
                            beforePosition, newPosition, Features::Codec::encode(value));
}

void update(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, Viper::UUId const & position, std::uint8_t value) {
    mutating->updateInXArray(attachment(), encodeKey(key), Viper::Path::make(), position, Features::Codec::encode(value));
}

void remove(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ConceptCoverageKey const & key, Viper::UUId const & position) {
    mutating->removeInXArray(attachment(), encodeKey(key), Viper::Path::make(), position);
}

} // namespace Demo::Attachments::ConceptCoverage::docXArray

namespace Demo::Attachments::Klub::propertiesD {

Viper::UUId const runtimeId{Viper::UUId::parse("f7a9f794-cedc-a3ff-9530-63f86e932850")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(KlubKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<KlubKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::set<KlubKey> result;
    for (Viper::ValueSetIter it{getting->keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<KlubKey>(it.value()));

    return result;
}

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, KlubKey const & key) {
    return getting->has(attachment(), encodeKey(key));
}

std::optional<StructureV> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, KlubKey const & key) {
    auto const document = getting->get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<StructureV>(document->unwrap());
}

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, StructureV const & value) {
    mutating->set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, StructureV const & value,
          bool recursive) {
    mutating->diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, KlubKey const & key, StructureV const & value) {
    return Features::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, KlubKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

void setF_bool(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, bool value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_boolPath(),
                    Features::Codec::encode(value));
}


void setF_uint8(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, std::uint8_t value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_uint8Path(),
                    Features::Codec::encode(value));
}


void setF_uint16(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, std::uint16_t value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_uint16Path(),
                    Features::Codec::encode(value));
}


void setF_uint32(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, std::uint32_t value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_uint32Path(),
                    Features::Codec::encode(value));
}


void setF_uint64(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, std::uint64_t value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_uint64Path(),
                    Features::Codec::encode(value));
}


void setF_int8(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, std::int8_t value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_int8Path(),
                    Features::Codec::encode(value));
}


void setF_int16(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, std::int16_t value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_int16Path(),
                    Features::Codec::encode(value));
}


void setF_int32(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, std::int32_t value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_int32Path(),
                    Features::Codec::encode(value));
}


void setF_int64(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, std::int64_t value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_int64Path(),
                    Features::Codec::encode(value));
}


void setF_float(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, float value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_floatPath(),
                    Features::Codec::encode(value));
}


void setF_double(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, double value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_doublePath(),
                    Features::Codec::encode(value));
}


void setF_uuid(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, Viper::UUId const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_uuidPath(),
                    Features::Codec::encode(value));
}


void setF_string(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, std::string const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_stringPath(),
                    Features::Codec::encode(value));
}


void setF_vec(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, std::array<std::uint8_t, 2> const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_vecPath(),
                    Features::Codec::encode(value));
}


void setF_mat(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, std::array<std::array<std::uint8_t, 3>, 2> const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_matPath(),
                    Features::Codec::encode(value));
}


void setF_tuple(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, std::tuple<std::uint8_t, std::string> const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_tuplePath(),
                    Features::Codec::encode(value));
}


void setF_optional(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, std::optional<std::uint8_t> const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_optionalPath(),
                    Features::Codec::encode(value));
}


void setF_vector(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, std::vector<std::uint8_t> const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_vectorPath(),
                    Features::Codec::encode(value));
}


void setF_set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, std::set<std::uint8_t> const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_setPath(),
                    Features::Codec::encode(value));
}

void unionF_set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, std::set<std::uint8_t> const & value) {
    mutating->unionInSet(attachment(), encodeKey(key), Demo::Fields::StructureV::f_setPath(), Viper::ValueSet::cast(Features::Codec::encode(value)));
}

void subtractF_set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, std::set<std::uint8_t> const & value) {
    mutating->subtractInSet(attachment(), encodeKey(key), Demo::Fields::StructureV::f_setPath(), Viper::ValueSet::cast(Features::Codec::encode(value)));
}


void setF_map(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, std::map<std::uint8_t, std::string> const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_mapPath(),
                    Features::Codec::encode(value));
}

void unionF_map(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, std::map<std::uint8_t, std::string> const & value) {
    mutating->unionInMap(attachment(), encodeKey(key), Demo::Fields::StructureV::f_mapPath(), Viper::ValueMap::cast(Features::Codec::encode(value)));
}

void subtractF_map(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, std::set<std::uint8_t> const & value) {
    mutating->subtractInMap(attachment(), encodeKey(key), Demo::Fields::StructureV::f_mapPath(), Viper::ValueSet::cast(Features::Codec::encode(value)));
}

void updateF_map(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, std::map<std::uint8_t, std::string> const & value) {
    mutating->updateInMap(attachment(), encodeKey(key), Demo::Fields::StructureV::f_mapPath(), Viper::ValueMap::cast(Features::Codec::encode(value)));
}


void setF_E(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, EnumerationE value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_EPath(),
                    Features::Codec::encode(value));
}


void setF_S(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, StructureS const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_SPath(),
                    Features::Codec::encode(value));
}


void setF_T(std::shared_ptr<Viper::AttachmentMutating> const & mutating, KlubKey const & key, StructureT const & value) {
    mutating->update(attachment(), encodeKey(key), Demo::Fields::StructureV::f_TPath(),
                    Features::Codec::encode(value));
}

} // namespace Demo::Attachments::Klub::propertiesD