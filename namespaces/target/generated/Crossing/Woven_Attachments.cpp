// unité Woven — l'implémentation des attachments qu'elle déclare.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

#include "Woven_Attachments.hpp"

#include "Woven_Codec.hpp"
#include "Woven_Fields.hpp"
#include "Woven_Model.hpp"
#include "Parts_Codec.hpp"
#include "Core_Codec.hpp"
#include "Parts_Model.hpp"
#include "Core_Model.hpp"
#include "Parts_Fields.hpp"
#include "Core_Fields.hpp"

#include "Crossing_Codec.hpp"
#include "Crossing_Db.hpp"

#include "Viper_Attachment.hpp"
#include "Viper_Definitions.hpp"
#include "Viper_Path.hpp"
#include "Viper_Values.hpp"
#include "Viper_ValueSetIter.hpp"

namespace Woven::Attachments::Core_Thing::mark {

Viper::UUId const runtimeId{Viper::UUId::parse("29b28189-1b55-86c3-5e2c-59344e124aa2")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Crossing::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(Core::ThingKey const & key) {
    return Viper::ValueKey::cast(Crossing::Codec::encode(key));
}

} // namespace

std::set<Core::ThingKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<Core::ThingKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Crossing::Codec::decode<Core::ThingKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, Core::ThingKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<Parts::Colour> get(Viper::AttachmentGetting const & getting, Core::ThingKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Crossing::Codec::decode<Parts::Colour>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, Core::ThingKey const & key, Parts::Colour const & value) {
    mutating.set(attachment(), encodeKey(key), Crossing::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, Core::ThingKey const & key, Parts::Colour const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Crossing::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, Core::ThingKey const & key, Parts::Colour const & value) {
    return Crossing::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, Core::ThingKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

void setR(Viper::AttachmentMutating & mutating, Core::ThingKey const & key, float value) {
    mutating.update(attachment(), encodeKey(key), Parts::Fields::Colour::rPath(),
                    Crossing::Codec::encode(value));
}


void setG(Viper::AttachmentMutating & mutating, Core::ThingKey const & key, float value) {
    mutating.update(attachment(), encodeKey(key), Parts::Fields::Colour::gPath(),
                    Crossing::Codec::encode(value));
}


void setB(Viper::AttachmentMutating & mutating, Core::ThingKey const & key, float value) {
    mutating.update(attachment(), encodeKey(key), Parts::Fields::Colour::bPath(),
                    Crossing::Codec::encode(value));
}

} // namespace Woven::Attachments::Core_Thing::mark

namespace Woven::Attachments::Knot::docAnyConceptKey {

Viper::UUId const runtimeId{Viper::UUId::parse("4a9fcd14-9b14-51cd-1865-cb55edb9021e")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Crossing::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(KnotKey const & key) {
    return Viper::ValueKey::cast(Crossing::Codec::encode(key));
}

} // namespace

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<KnotKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Crossing::Codec::decode<KnotKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<::Crossing::AnyConceptKey> get(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Crossing::Codec::decode<::Crossing::AnyConceptKey>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, ::Crossing::AnyConceptKey const & value) {
    mutating.set(attachment(), encodeKey(key), Crossing::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, ::Crossing::AnyConceptKey const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Crossing::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, ::Crossing::AnyConceptKey const & value) {
    return Crossing::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}
} // namespace Woven::Attachments::Knot::docAnyConceptKey

namespace Woven::Attachments::Knot::docColour {

Viper::UUId const runtimeId{Viper::UUId::parse("b6352063-8d70-8a69-963c-d1441b676370")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Crossing::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(KnotKey const & key) {
    return Viper::ValueKey::cast(Crossing::Codec::encode(key));
}

} // namespace

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<KnotKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Crossing::Codec::decode<KnotKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<Core::Colour> get(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Crossing::Codec::decode<Core::Colour>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, Core::Colour const & value) {
    mutating.set(attachment(), encodeKey(key), Crossing::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, Core::Colour const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Crossing::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, Core::Colour const & value) {
    return Crossing::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

void setR(Viper::AttachmentMutating & mutating, KnotKey const & key, std::uint8_t value) {
    mutating.update(attachment(), encodeKey(key), Core::Fields::Colour::rPath(),
                    Crossing::Codec::encode(value));
}


void setG(Viper::AttachmentMutating & mutating, KnotKey const & key, std::uint8_t value) {
    mutating.update(attachment(), encodeKey(key), Core::Fields::Colour::gPath(),
                    Crossing::Codec::encode(value));
}


void setB(Viper::AttachmentMutating & mutating, KnotKey const & key, std::uint8_t value) {
    mutating.update(attachment(), encodeKey(key), Core::Fields::Colour::bPath(),
                    Crossing::Codec::encode(value));
}

} // namespace Woven::Attachments::Knot::docColour

namespace Woven::Attachments::Knot::docComposites {

Viper::UUId const runtimeId{Viper::UUId::parse("d81beea7-b5ce-6808-94fb-4487e4ee79d6")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Crossing::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(KnotKey const & key) {
    return Viper::ValueKey::cast(Crossing::Codec::encode(key));
}

} // namespace

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<KnotKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Crossing::Codec::decode<KnotKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<Composites> get(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Crossing::Codec::decode<Composites>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, Composites const & value) {
    mutating.set(attachment(), encodeKey(key), Crossing::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, Composites const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Crossing::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, Composites const & value) {
    return Crossing::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

void setF_tuple(Viper::AttachmentMutating & mutating, KnotKey const & key, std::tuple<Core::Colour, Parts::Colour> const & value) {
    mutating.update(attachment(), encodeKey(key), Woven::Fields::Composites::f_tuplePath(),
                    Crossing::Codec::encode(value));
}


void setF_optional(Viper::AttachmentMutating & mutating, KnotKey const & key, std::optional<Core::ThingKey> const & value) {
    mutating.update(attachment(), encodeKey(key), Woven::Fields::Composites::f_optionalPath(),
                    Crossing::Codec::encode(value));
}


void setF_vector(Viper::AttachmentMutating & mutating, KnotKey const & key, std::vector<Parts::Colour> const & value) {
    mutating.update(attachment(), encodeKey(key), Woven::Fields::Composites::f_vectorPath(),
                    Crossing::Codec::encode(value));
}


void setF_set(Viper::AttachmentMutating & mutating, KnotKey const & key, std::set<Core::ThingKey> const & value) {
    mutating.update(attachment(), encodeKey(key), Woven::Fields::Composites::f_setPath(),
                    Crossing::Codec::encode(value));
}

void unionF_set(Viper::AttachmentMutating & mutating, KnotKey const & key, std::set<Core::ThingKey> const & value) {
    mutating.unionInSet(attachment(), encodeKey(key), Woven::Fields::Composites::f_setPath(), Viper::ValueSet::cast(Crossing::Codec::encode(value)));
}

void subtractF_set(Viper::AttachmentMutating & mutating, KnotKey const & key, std::set<Core::ThingKey> const & value) {
    mutating.subtractInSet(attachment(), encodeKey(key), Woven::Fields::Composites::f_setPath(), Viper::ValueSet::cast(Crossing::Codec::encode(value)));
}


void setF_map_keys(Viper::AttachmentMutating & mutating, KnotKey const & key, std::map<Core::ThingKey, Parts::ThingKey> const & value) {
    mutating.update(attachment(), encodeKey(key), Woven::Fields::Composites::f_map_keysPath(),
                    Crossing::Codec::encode(value));
}

void unionF_map_keys(Viper::AttachmentMutating & mutating, KnotKey const & key, std::map<Core::ThingKey, Parts::ThingKey> const & value) {
    mutating.unionInMap(attachment(), encodeKey(key), Woven::Fields::Composites::f_map_keysPath(), Viper::ValueMap::cast(Crossing::Codec::encode(value)));
}

void subtractF_map_keys(Viper::AttachmentMutating & mutating, KnotKey const & key, std::set<Core::ThingKey> const & value) {
    mutating.subtractInMap(attachment(), encodeKey(key), Woven::Fields::Composites::f_map_keysPath(), Viper::ValueSet::cast(Crossing::Codec::encode(value)));
}

void updateF_map_keys(Viper::AttachmentMutating & mutating, KnotKey const & key, std::map<Core::ThingKey, Parts::ThingKey> const & value) {
    mutating.updateInMap(attachment(), encodeKey(key), Woven::Fields::Composites::f_map_keysPath(), Viper::ValueMap::cast(Crossing::Codec::encode(value)));
}


void setF_map_enum(Viper::AttachmentMutating & mutating, KnotKey const & key, std::map<Core::Grade, Parts::Colour> const & value) {
    mutating.update(attachment(), encodeKey(key), Woven::Fields::Composites::f_map_enumPath(),
                    Crossing::Codec::encode(value));
}

void unionF_map_enum(Viper::AttachmentMutating & mutating, KnotKey const & key, std::map<Core::Grade, Parts::Colour> const & value) {
    mutating.unionInMap(attachment(), encodeKey(key), Woven::Fields::Composites::f_map_enumPath(), Viper::ValueMap::cast(Crossing::Codec::encode(value)));
}

void subtractF_map_enum(Viper::AttachmentMutating & mutating, KnotKey const & key, std::set<Core::Grade> const & value) {
    mutating.subtractInMap(attachment(), encodeKey(key), Woven::Fields::Composites::f_map_enumPath(), Viper::ValueSet::cast(Crossing::Codec::encode(value)));
}

void updateF_map_enum(Viper::AttachmentMutating & mutating, KnotKey const & key, std::map<Core::Grade, Parts::Colour> const & value) {
    mutating.updateInMap(attachment(), encodeKey(key), Woven::Fields::Composites::f_map_enumPath(), Viper::ValueMap::cast(Crossing::Codec::encode(value)));
}


void setF_xarray(Viper::AttachmentMutating & mutating, KnotKey const & key, Viper::XArray<Core::Colour> const & value) {
    mutating.update(attachment(), encodeKey(key), Woven::Fields::Composites::f_xarrayPath(),
                    Crossing::Codec::encode(value));
}

void insertF_xarray(Viper::AttachmentMutating & mutating, KnotKey const & key, Viper::UUId const & beforePosition, Viper::UUId const & newPosition, Core::Colour const & value) {
    mutating.insertInXArray(attachment(), encodeKey(key), Woven::Fields::Composites::f_xarrayPath(),
                            beforePosition, newPosition, Crossing::Codec::encode(value));
}

void updateF_xarray(Viper::AttachmentMutating & mutating, KnotKey const & key, Viper::UUId const & position, Core::Colour const & value) {
    mutating.updateInXArray(attachment(), encodeKey(key), Woven::Fields::Composites::f_xarrayPath(),
                            position, Crossing::Codec::encode(value));
}

void removeF_xarray(Viper::AttachmentMutating & mutating, KnotKey const & key, Viper::UUId const & position) {
    mutating.removeInXArray(attachment(), encodeKey(key), Woven::Fields::Composites::f_xarrayPath(), position);
}


void setF_variant(Viper::AttachmentMutating & mutating, KnotKey const & key, std::variant<Core::Colour, Parts::Colour, std::string> const & value) {
    mutating.update(attachment(), encodeKey(key), Woven::Fields::Composites::f_variantPath(),
                    Crossing::Codec::encode(value));
}

} // namespace Woven::Attachments::Knot::docComposites

namespace Woven::Attachments::Knot::docGrade {

Viper::UUId const runtimeId{Viper::UUId::parse("9ff5bafb-4555-2539-1cf8-28794071e3f9")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Crossing::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(KnotKey const & key) {
    return Viper::ValueKey::cast(Crossing::Codec::encode(key));
}

} // namespace

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<KnotKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Crossing::Codec::decode<KnotKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<Core::Grade> get(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Crossing::Codec::decode<Core::Grade>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, Core::Grade const & value) {
    mutating.set(attachment(), encodeKey(key), Crossing::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, Core::Grade const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Crossing::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, Core::Grade const & value) {
    return Crossing::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}
} // namespace Woven::Attachments::Knot::docGrade

namespace Woven::Attachments::Knot::docKlubKey {

Viper::UUId const runtimeId{Viper::UUId::parse("9e24eff7-c018-1b1f-df8a-ba06bf0393c7")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Crossing::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(KnotKey const & key) {
    return Viper::ValueKey::cast(Crossing::Codec::encode(key));
}

} // namespace

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<KnotKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Crossing::Codec::decode<KnotKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<Core::KlubKey> get(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Crossing::Codec::decode<Core::KlubKey>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, Core::KlubKey const & value) {
    mutating.set(attachment(), encodeKey(key), Crossing::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, Core::KlubKey const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Crossing::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, Core::KlubKey const & value) {
    return Crossing::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}
} // namespace Woven::Attachments::Knot::docKlubKey

namespace Woven::Attachments::Knot::docMapEnum {

Viper::UUId const runtimeId{Viper::UUId::parse("bb379295-5f29-328c-7c5b-7c3073b675fb")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Crossing::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(KnotKey const & key) {
    return Viper::ValueKey::cast(Crossing::Codec::encode(key));
}

} // namespace

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<KnotKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Crossing::Codec::decode<KnotKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::map<Core::Grade, Parts::Colour>> get(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Crossing::Codec::decode<std::map<Core::Grade, Parts::Colour>>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, std::map<Core::Grade, Parts::Colour> const & value) {
    mutating.set(attachment(), encodeKey(key), Crossing::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, std::map<Core::Grade, Parts::Colour> const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Crossing::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, std::map<Core::Grade, Parts::Colour> const & value) {
    return Crossing::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

void union_(Viper::AttachmentMutating & mutating, KnotKey const & key, std::map<Core::Grade, Parts::Colour> const & value) {
    mutating.unionInMap(attachment(), encodeKey(key), Viper::Path::make(), Viper::ValueMap::cast(Crossing::Codec::encode(value)));
}

void subtract(Viper::AttachmentMutating & mutating, KnotKey const & key, std::set<Core::Grade> const & value) {
    mutating.subtractInMap(attachment(), encodeKey(key), Viper::Path::make(), Viper::ValueSet::cast(Crossing::Codec::encode(value)));
}

void update(Viper::AttachmentMutating & mutating, KnotKey const & key, std::map<Core::Grade, Parts::Colour> const & value) {
    mutating.updateInMap(attachment(), encodeKey(key), Viper::Path::make(), Viper::ValueMap::cast(Crossing::Codec::encode(value)));
}

} // namespace Woven::Attachments::Knot::docMapEnum

namespace Woven::Attachments::Knot::docMapKeys {

Viper::UUId const runtimeId{Viper::UUId::parse("ca705caa-f5bf-b94f-5f52-cf0745c338be")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Crossing::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(KnotKey const & key) {
    return Viper::ValueKey::cast(Crossing::Codec::encode(key));
}

} // namespace

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<KnotKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Crossing::Codec::decode<KnotKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::map<Core::ThingKey, Parts::ThingKey>> get(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Crossing::Codec::decode<std::map<Core::ThingKey, Parts::ThingKey>>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, std::map<Core::ThingKey, Parts::ThingKey> const & value) {
    mutating.set(attachment(), encodeKey(key), Crossing::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, std::map<Core::ThingKey, Parts::ThingKey> const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Crossing::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, std::map<Core::ThingKey, Parts::ThingKey> const & value) {
    return Crossing::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

void union_(Viper::AttachmentMutating & mutating, KnotKey const & key, std::map<Core::ThingKey, Parts::ThingKey> const & value) {
    mutating.unionInMap(attachment(), encodeKey(key), Viper::Path::make(), Viper::ValueMap::cast(Crossing::Codec::encode(value)));
}

void subtract(Viper::AttachmentMutating & mutating, KnotKey const & key, std::set<Core::ThingKey> const & value) {
    mutating.subtractInMap(attachment(), encodeKey(key), Viper::Path::make(), Viper::ValueSet::cast(Crossing::Codec::encode(value)));
}

void update(Viper::AttachmentMutating & mutating, KnotKey const & key, std::map<Core::ThingKey, Parts::ThingKey> const & value) {
    mutating.updateInMap(attachment(), encodeKey(key), Viper::Path::make(), Viper::ValueMap::cast(Crossing::Codec::encode(value)));
}

} // namespace Woven::Attachments::Knot::docMapKeys

namespace Woven::Attachments::Knot::docOptional {

Viper::UUId const runtimeId{Viper::UUId::parse("7a6d4307-8841-d296-cbea-938d5bb346cd")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Crossing::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(KnotKey const & key) {
    return Viper::ValueKey::cast(Crossing::Codec::encode(key));
}

} // namespace

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<KnotKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Crossing::Codec::decode<KnotKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::optional<Core::ThingKey>> get(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Crossing::Codec::decode<std::optional<Core::ThingKey>>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, std::optional<Core::ThingKey> const & value) {
    mutating.set(attachment(), encodeKey(key), Crossing::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, std::optional<Core::ThingKey> const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Crossing::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, std::optional<Core::ThingKey> const & value) {
    return Crossing::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}
} // namespace Woven::Attachments::Knot::docOptional

namespace Woven::Attachments::Knot::docOtherColour {

Viper::UUId const runtimeId{Viper::UUId::parse("791ea025-2d11-6f01-fc7d-749a85470a7c")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Crossing::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(KnotKey const & key) {
    return Viper::ValueKey::cast(Crossing::Codec::encode(key));
}

} // namespace

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<KnotKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Crossing::Codec::decode<KnotKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<Parts::Colour> get(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Crossing::Codec::decode<Parts::Colour>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, Parts::Colour const & value) {
    mutating.set(attachment(), encodeKey(key), Crossing::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, Parts::Colour const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Crossing::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, Parts::Colour const & value) {
    return Crossing::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

void setR(Viper::AttachmentMutating & mutating, KnotKey const & key, float value) {
    mutating.update(attachment(), encodeKey(key), Parts::Fields::Colour::rPath(),
                    Crossing::Codec::encode(value));
}


void setG(Viper::AttachmentMutating & mutating, KnotKey const & key, float value) {
    mutating.update(attachment(), encodeKey(key), Parts::Fields::Colour::gPath(),
                    Crossing::Codec::encode(value));
}


void setB(Viper::AttachmentMutating & mutating, KnotKey const & key, float value) {
    mutating.update(attachment(), encodeKey(key), Parts::Fields::Colour::bPath(),
                    Crossing::Codec::encode(value));
}

} // namespace Woven::Attachments::Knot::docOtherColour

namespace Woven::Attachments::Knot::docSet {

Viper::UUId const runtimeId{Viper::UUId::parse("eb7bdd6d-a772-3d04-bc8c-077f3ed44532")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Crossing::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(KnotKey const & key) {
    return Viper::ValueKey::cast(Crossing::Codec::encode(key));
}

} // namespace

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<KnotKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Crossing::Codec::decode<KnotKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::set<Core::ThingKey>> get(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Crossing::Codec::decode<std::set<Core::ThingKey>>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, std::set<Core::ThingKey> const & value) {
    mutating.set(attachment(), encodeKey(key), Crossing::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, std::set<Core::ThingKey> const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Crossing::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, std::set<Core::ThingKey> const & value) {
    return Crossing::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

void union_(Viper::AttachmentMutating & mutating, KnotKey const & key, std::set<Core::ThingKey> const & value) {
    mutating.unionInSet(attachment(), encodeKey(key), Viper::Path::make(), Viper::ValueSet::cast(Crossing::Codec::encode(value)));
}

void subtract(Viper::AttachmentMutating & mutating, KnotKey const & key, std::set<Core::ThingKey> const & value) {
    mutating.subtractInSet(attachment(), encodeKey(key), Viper::Path::make(), Viper::ValueSet::cast(Crossing::Codec::encode(value)));
}

} // namespace Woven::Attachments::Knot::docSet

namespace Woven::Attachments::Knot::docThingKey {

Viper::UUId const runtimeId{Viper::UUId::parse("831d85fc-bf2f-16af-4cd7-bd71cde7cf3c")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Crossing::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(KnotKey const & key) {
    return Viper::ValueKey::cast(Crossing::Codec::encode(key));
}

} // namespace

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<KnotKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Crossing::Codec::decode<KnotKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<Core::ThingKey> get(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Crossing::Codec::decode<Core::ThingKey>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, Core::ThingKey const & value) {
    mutating.set(attachment(), encodeKey(key), Crossing::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, Core::ThingKey const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Crossing::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, Core::ThingKey const & value) {
    return Crossing::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}
} // namespace Woven::Attachments::Knot::docThingKey

namespace Woven::Attachments::Knot::docTuple {

Viper::UUId const runtimeId{Viper::UUId::parse("80700838-18f7-ae9f-9f1c-2d232720258e")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Crossing::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(KnotKey const & key) {
    return Viper::ValueKey::cast(Crossing::Codec::encode(key));
}

} // namespace

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<KnotKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Crossing::Codec::decode<KnotKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::tuple<Core::Colour, Parts::Colour>> get(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Crossing::Codec::decode<std::tuple<Core::Colour, Parts::Colour>>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, std::tuple<Core::Colour, Parts::Colour> const & value) {
    mutating.set(attachment(), encodeKey(key), Crossing::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, std::tuple<Core::Colour, Parts::Colour> const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Crossing::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, std::tuple<Core::Colour, Parts::Colour> const & value) {
    return Crossing::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}
} // namespace Woven::Attachments::Knot::docTuple

namespace Woven::Attachments::Knot::docVariant {

Viper::UUId const runtimeId{Viper::UUId::parse("a30edeff-00f1-96fd-7ee4-8a4bb2e51849")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Crossing::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(KnotKey const & key) {
    return Viper::ValueKey::cast(Crossing::Codec::encode(key));
}

} // namespace

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<KnotKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Crossing::Codec::decode<KnotKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::variant<Core::Colour, Parts::Colour>> get(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Crossing::Codec::decode<std::variant<Core::Colour, Parts::Colour>>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, std::variant<Core::Colour, Parts::Colour> const & value) {
    mutating.set(attachment(), encodeKey(key), Crossing::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, std::variant<Core::Colour, Parts::Colour> const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Crossing::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, std::variant<Core::Colour, Parts::Colour> const & value) {
    return Crossing::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}
} // namespace Woven::Attachments::Knot::docVariant

namespace Woven::Attachments::Knot::docVector {

Viper::UUId const runtimeId{Viper::UUId::parse("b139c73e-34f5-265b-1052-23a0685f66a9")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Crossing::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(KnotKey const & key) {
    return Viper::ValueKey::cast(Crossing::Codec::encode(key));
}

} // namespace

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<KnotKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Crossing::Codec::decode<KnotKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::vector<Parts::Colour>> get(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Crossing::Codec::decode<std::vector<Parts::Colour>>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, std::vector<Parts::Colour> const & value) {
    mutating.set(attachment(), encodeKey(key), Crossing::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, std::vector<Parts::Colour> const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Crossing::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, std::vector<Parts::Colour> const & value) {
    return Crossing::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}
} // namespace Woven::Attachments::Knot::docVector

namespace Woven::Attachments::Knot::docXArray {

Viper::UUId const runtimeId{Viper::UUId::parse("70c9c550-d044-dd9a-e924-f988a02bcb6a")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Crossing::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(KnotKey const & key) {
    return Viper::ValueKey::cast(Crossing::Codec::encode(key));
}

} // namespace

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<KnotKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Crossing::Codec::decode<KnotKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<Viper::XArray<Core::Colour>> get(Viper::AttachmentGetting const & getting, KnotKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Crossing::Codec::decode<Viper::XArray<Core::Colour>>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, Viper::XArray<Core::Colour> const & value) {
    mutating.set(attachment(), encodeKey(key), Crossing::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, Viper::XArray<Core::Colour> const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Crossing::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, Viper::XArray<Core::Colour> const & value) {
    return Crossing::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

void insert(Viper::AttachmentMutating & mutating, KnotKey const & key, Viper::UUId const & beforePosition, Viper::UUId const & newPosition, Core::Colour const & value) {
    mutating.insertInXArray(attachment(), encodeKey(key), Viper::Path::make(),
                            beforePosition, newPosition, Crossing::Codec::encode(value));
}

void update(Viper::AttachmentMutating & mutating, KnotKey const & key, Viper::UUId const & position, Core::Colour const & value) {
    mutating.updateInXArray(attachment(), encodeKey(key), Viper::Path::make(), position, Crossing::Codec::encode(value));
}

void remove(Viper::AttachmentMutating & mutating, KnotKey const & key, Viper::UUId const & position) {
    mutating.removeInXArray(attachment(), encodeKey(key), Viper::Path::make(), position);
}

} // namespace Woven::Attachments::Knot::docXArray

namespace Woven::Attachments::Parts_Thing::mark {

Viper::UUId const runtimeId{Viper::UUId::parse("f3fbea66-985b-da2b-f523-016cf94b43cc")};

std::shared_ptr<Viper::Attachment> const & descriptor() {
    static auto const instance = Crossing::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

namespace {

std::shared_ptr<Viper::Attachment> const & attachment() { return descriptor(); }

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(Parts::ThingKey const & key) {
    return Viper::ValueKey::cast(Crossing::Codec::encode(key));
}

} // namespace

std::set<Parts::ThingKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<Parts::ThingKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Crossing::Codec::decode<Parts::ThingKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, Parts::ThingKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<Core::Colour> get(Viper::AttachmentGetting const & getting, Parts::ThingKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Crossing::Codec::decode<Core::Colour>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, Parts::ThingKey const & key, Core::Colour const & value) {
    mutating.set(attachment(), encodeKey(key), Crossing::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, Parts::ThingKey const & key, Core::Colour const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Crossing::Codec::encode(value), recursive);
}

bool set(std::shared_ptr<Viper::Database> const & db, Parts::ThingKey const & key, Core::Colour const & value) {
    return Crossing::Db::set(db, attachment(), key, value);
}

bool del(std::shared_ptr<Viper::Database> const & db, Parts::ThingKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

void setR(Viper::AttachmentMutating & mutating, Parts::ThingKey const & key, std::uint8_t value) {
    mutating.update(attachment(), encodeKey(key), Core::Fields::Colour::rPath(),
                    Crossing::Codec::encode(value));
}


void setG(Viper::AttachmentMutating & mutating, Parts::ThingKey const & key, std::uint8_t value) {
    mutating.update(attachment(), encodeKey(key), Core::Fields::Colour::gPath(),
                    Crossing::Codec::encode(value));
}


void setB(Viper::AttachmentMutating & mutating, Parts::ThingKey const & key, std::uint8_t value) {
    mutating.update(attachment(), encodeKey(key), Core::Fields::Colour::bPath(),
                    Crossing::Codec::encode(value));
}

} // namespace Woven::Attachments::Parts_Thing::mark