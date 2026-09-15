// Test — l'implémentation des attachments qu'il déclare.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/features/Features.dsm.json by kibo-2.0.0.jar

#include "Test_Attachments.hpp"

#include "Test_Codec.hpp"
#include "Test_Fields.hpp"
#include "Test_Model.hpp"

#include "Features_Codec.hpp"

#include "Viper_Attachment.hpp"
#include "Viper_Definitions.hpp"
#include "Viper_Path.hpp"
#include "Viper_Values.hpp"

namespace Test::Attachments::AnyConcept::propertiesAnyConceptAny {

Viper::UUId const runtimeId{Viper::UUId::parse("8de8e47b-58e8-5699-59a7-5a3193aef7f1")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(::Features::AnyConceptKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<::Features::AnyConceptKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<::Features::AnyConceptKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<::Features::AnyConceptKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ::Features::AnyConceptKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<Viper::Any> get(Viper::AttachmentGetting const & getting, ::Features::AnyConceptKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<Viper::Any>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ::Features::AnyConceptKey const & key, Viper::Any const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ::Features::AnyConceptKey const & key, Viper::Any const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::AnyConcept::propertiesAnyConceptAny

namespace Test::Attachments::ConceptA::properties {

Viper::UUId const runtimeId{Viper::UUId::parse("3b79131f-a619-5b33-66ab-3b78ca749cd0")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptAKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptAKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptAKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptAKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptAKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<StructureV> get(Viper::AttachmentGetting const & getting, ConceptAKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<StructureV>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptAKey const & key, StructureV const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptAKey const & key, StructureV const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

void setF_bool(Viper::AttachmentMutating & mutating, ConceptAKey const & key, bool value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_boolPath(),
                    Features::Codec::encode(value));
}

void setF_uint8(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::uint8_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_uint8Path(),
                    Features::Codec::encode(value));
}

void setF_uint16(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::uint16_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_uint16Path(),
                    Features::Codec::encode(value));
}

void setF_uint32(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::uint32_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_uint32Path(),
                    Features::Codec::encode(value));
}

void setF_uint64(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::uint64_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_uint64Path(),
                    Features::Codec::encode(value));
}

void setF_int8(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::int8_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_int8Path(),
                    Features::Codec::encode(value));
}

void setF_int16(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::int16_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_int16Path(),
                    Features::Codec::encode(value));
}

void setF_int32(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::int32_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_int32Path(),
                    Features::Codec::encode(value));
}

void setF_int64(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::int64_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_int64Path(),
                    Features::Codec::encode(value));
}

void setF_float(Viper::AttachmentMutating & mutating, ConceptAKey const & key, float value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_floatPath(),
                    Features::Codec::encode(value));
}

void setF_double(Viper::AttachmentMutating & mutating, ConceptAKey const & key, double value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_doublePath(),
                    Features::Codec::encode(value));
}

void setF_uuid(Viper::AttachmentMutating & mutating, ConceptAKey const & key, Viper::UUId const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_uuidPath(),
                    Features::Codec::encode(value));
}

void setF_string(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::string const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_stringPath(),
                    Features::Codec::encode(value));
}

void setF_vec(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::array<std::uint8_t, 2> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_vecPath(),
                    Features::Codec::encode(value));
}

void setF_mat(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::array<std::array<std::uint8_t, 3>, 2> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_matPath(),
                    Features::Codec::encode(value));
}

void setF_tuple(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::tuple<std::uint8_t, std::string> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_tuplePath(),
                    Features::Codec::encode(value));
}

void setF_optional(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::optional<std::uint8_t> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_optionalPath(),
                    Features::Codec::encode(value));
}

void setF_vector(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::vector<std::uint8_t> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_vectorPath(),
                    Features::Codec::encode(value));
}

void setF_set(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::set<std::uint8_t> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_setPath(),
                    Features::Codec::encode(value));
}

void setF_map(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::map<std::uint8_t, std::string> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_mapPath(),
                    Features::Codec::encode(value));
}

void setF_E(Viper::AttachmentMutating & mutating, ConceptAKey const & key, EnumerationE value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_EPath(),
                    Features::Codec::encode(value));
}

void setF_S(Viper::AttachmentMutating & mutating, ConceptAKey const & key, StructureS const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_SPath(),
                    Features::Codec::encode(value));
}

void setF_T(Viper::AttachmentMutating & mutating, ConceptAKey const & key, StructureT const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_TPath(),
                    Features::Codec::encode(value));
}

} // namespace Test::Attachments::ConceptA::properties

namespace Test::Attachments::ConceptA::propertiesInt8 {

Viper::UUId const runtimeId{Viper::UUId::parse("58ce283d-b8eb-1f01-3841-854fccd54fd7")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptAKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptAKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptAKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptAKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptAKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::int8_t> get(Viper::AttachmentGetting const & getting, ConceptAKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::int8_t>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::int8_t const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::int8_t const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptA::propertiesInt8

namespace Test::Attachments::ConceptA::propertiesMapInt8String {

Viper::UUId const runtimeId{Viper::UUId::parse("0eb140e3-5247-d7ad-649f-5fa124359ee2")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptAKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptAKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptAKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptAKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptAKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::map<std::int8_t, std::string>> get(Viper::AttachmentGetting const & getting, ConceptAKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::map<std::int8_t, std::string>>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::map<std::int8_t, std::string> const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::map<std::int8_t, std::string> const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptA::propertiesMapInt8String

namespace Test::Attachments::ConceptA::propertiesSeInt8 {

Viper::UUId const runtimeId{Viper::UUId::parse("ad45f798-b25a-0421-c523-713ff624383e")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptAKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptAKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptAKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptAKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptAKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::set<std::int8_t>> get(Viper::AttachmentGetting const & getting, ConceptAKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::set<std::int8_t>>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::set<std::int8_t> const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::set<std::int8_t> const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptA::propertiesSeInt8

namespace Test::Attachments::ConceptA::propertiesXArray {

Viper::UUId const runtimeId{Viper::UUId::parse("ff9d7eda-5ad0-d217-d910-7d2adfad208f")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptAKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptAKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptAKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptAKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptAKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<Viper::XArray<std::int8_t>> get(Viper::AttachmentGetting const & getting, ConceptAKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<Viper::XArray<std::int8_t>>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptAKey const & key, Viper::XArray<std::int8_t> const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptAKey const & key, Viper::XArray<std::int8_t> const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptA::propertiesXArray

namespace Test::Attachments::ConceptB::propertiesB {

Viper::UUId const runtimeId{Viper::UUId::parse("c117fd64-7b82-f4ab-164c-efb528a408bc")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptBKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptBKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptBKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptBKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptBKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<StructureT> get(Viper::AttachmentGetting const & getting, ConceptBKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<StructureT>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptBKey const & key, StructureT const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptBKey const & key, StructureT const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

void setField_string(Viper::AttachmentMutating & mutating, ConceptBKey const & key, std::string const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureT::field_stringPath(),
                    Features::Codec::encode(value));
}

void setField_structure_s(Viper::AttachmentMutating & mutating, ConceptBKey const & key, StructureS const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureT::field_structure_sPath(),
                    Features::Codec::encode(value));
}

} // namespace Test::Attachments::ConceptB::propertiesB

namespace Test::Attachments::ConceptC::propertiesC {

Viper::UUId const runtimeId{Viper::UUId::parse("7f6d8d89-d32a-3214-ed11-3f23b7faaf1e")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<StructureU> get(Viper::AttachmentGetting const & getting, ConceptCKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<StructureU>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCKey const & key, StructureU const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCKey const & key, StructureU const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

void setF_bool(Viper::AttachmentMutating & mutating, ConceptCKey const & key, bool value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_boolPath(),
                    Features::Codec::encode(value));
}

void setF_uint8(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::uint8_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_uint8Path(),
                    Features::Codec::encode(value));
}

void setF_uint16(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::uint16_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_uint16Path(),
                    Features::Codec::encode(value));
}

void setF_uint32(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::uint32_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_uint32Path(),
                    Features::Codec::encode(value));
}

void setF_uint64(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::uint64_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_uint64Path(),
                    Features::Codec::encode(value));
}

void setF_int8(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::int8_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_int8Path(),
                    Features::Codec::encode(value));
}

void setF_int16(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::int16_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_int16Path(),
                    Features::Codec::encode(value));
}

void setF_int32(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::int32_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_int32Path(),
                    Features::Codec::encode(value));
}

void setF_int64(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::int64_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_int64Path(),
                    Features::Codec::encode(value));
}

void setF_float(Viper::AttachmentMutating & mutating, ConceptCKey const & key, float value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_floatPath(),
                    Features::Codec::encode(value));
}

void setF_double(Viper::AttachmentMutating & mutating, ConceptCKey const & key, double value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_doublePath(),
                    Features::Codec::encode(value));
}

void setF_blob_id(Viper::AttachmentMutating & mutating, ConceptCKey const & key, Viper::BlobId const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_blob_idPath(),
                    Features::Codec::encode(value));
}

void setF_commit_id(Viper::AttachmentMutating & mutating, ConceptCKey const & key, Viper::CommitId const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_commit_idPath(),
                    Features::Codec::encode(value));
}

void setF_uuid(Viper::AttachmentMutating & mutating, ConceptCKey const & key, Viper::UUId const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_uuidPath(),
                    Features::Codec::encode(value));
}

void setF_string(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::string const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_stringPath(),
                    Features::Codec::encode(value));
}

void setF_blob(Viper::AttachmentMutating & mutating, ConceptCKey const & key, Viper::Blob const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_blobPath(),
                    Features::Codec::encode(value));
}

void setF_vec(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::array<std::uint8_t, 2> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_vecPath(),
                    Features::Codec::encode(value));
}

void setF_mat(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::array<std::array<std::uint8_t, 2>, 2> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_matPath(),
                    Features::Codec::encode(value));
}

void setF_tuple(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::tuple<std::uint8_t, std::string> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_tuplePath(),
                    Features::Codec::encode(value));
}

void setF_optional(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::optional<std::uint8_t> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_optionalPath(),
                    Features::Codec::encode(value));
}

void setF_vector(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::vector<std::uint8_t> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_vectorPath(),
                    Features::Codec::encode(value));
}

void setF_set(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::set<std::uint8_t> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_setPath(),
                    Features::Codec::encode(value));
}

void setF_set_s(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::set<StructureS> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_set_sPath(),
                    Features::Codec::encode(value));
}

void setF_map_s1(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::map<StructureS, std::string> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_map_s1Path(),
                    Features::Codec::encode(value));
}

void setF_map_s2(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::map<std::string, StructureS> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_map_s2Path(),
                    Features::Codec::encode(value));
}

void setF_xarray(Viper::AttachmentMutating & mutating, ConceptCKey const & key, Viper::XArray<std::uint8_t> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_xarrayPath(),
                    Features::Codec::encode(value));
}

void setF_xarray_s(Viper::AttachmentMutating & mutating, ConceptCKey const & key, Viper::XArray<StructureS> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_xarray_sPath(),
                    Features::Codec::encode(value));
}

void setF_map_vs(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::map<std::vector<StructureS>, std::string> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_map_vsPath(),
                    Features::Codec::encode(value));
}

void setF_variant(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::variant<std::string, std::uint8_t, StructureS> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_variantPath(),
                    Features::Codec::encode(value));
}

void setF_any(Viper::AttachmentMutating & mutating, ConceptCKey const & key, Viper::Any const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_anyPath(),
                    Features::Codec::encode(value));
}

void setF_E(Viper::AttachmentMutating & mutating, ConceptCKey const & key, EnumerationE value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_EPath(),
                    Features::Codec::encode(value));
}

void setF_S(Viper::AttachmentMutating & mutating, ConceptCKey const & key, StructureS const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_SPath(),
                    Features::Codec::encode(value));
}

void setF_T(Viper::AttachmentMutating & mutating, ConceptCKey const & key, StructureT const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_TPath(),
                    Features::Codec::encode(value));
}

void setF_A(Viper::AttachmentMutating & mutating, ConceptCKey const & key, ConceptAKey const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_APath(),
                    Features::Codec::encode(value));
}

void setF_B(Viper::AttachmentMutating & mutating, ConceptCKey const & key, ConceptBKey const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_BPath(),
                    Features::Codec::encode(value));
}

void setF_C(Viper::AttachmentMutating & mutating, ConceptCKey const & key, ConceptCKey const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_CPath(),
                    Features::Codec::encode(value));
}

void setF_D(Viper::AttachmentMutating & mutating, ConceptCKey const & key, ConceptDKey const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_DPath(),
                    Features::Codec::encode(value));
}

void setF_Klub(Viper::AttachmentMutating & mutating, ConceptCKey const & key, KlubKey const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_KlubPath(),
                    Features::Codec::encode(value));
}

void setF_any_concept(Viper::AttachmentMutating & mutating, ConceptCKey const & key, ::Features::AnyConceptKey const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureU::f_any_conceptPath(),
                    Features::Codec::encode(value));
}

} // namespace Test::Attachments::ConceptC::propertiesC

namespace Test::Attachments::ConceptCoverage::docAny {

Viper::UUId const runtimeId{Viper::UUId::parse("20a71745-30fb-4f1b-2245-d331c323bbba")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<Viper::Any> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<Viper::Any>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, Viper::Any const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, Viper::Any const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docAny

namespace Test::Attachments::ConceptCoverage::docAnyConceptKey {

Viper::UUId const runtimeId{Viper::UUId::parse("ab54b0a8-596a-40fc-6ef1-f1d2eba54f5c")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<::Features::AnyConceptKey> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<::Features::AnyConceptKey>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, ::Features::AnyConceptKey const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, ::Features::AnyConceptKey const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docAnyConceptKey

namespace Test::Attachments::ConceptCoverage::docBlob {

Viper::UUId const runtimeId{Viper::UUId::parse("e80aaf93-0656-f497-1372-20158ecea8fb")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<Viper::Blob> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<Viper::Blob>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, Viper::Blob const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, Viper::Blob const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docBlob

namespace Test::Attachments::ConceptCoverage::docBlobId {

Viper::UUId const runtimeId{Viper::UUId::parse("8dce567e-111b-bddf-7448-1abc8261ac90")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<Viper::BlobId> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<Viper::BlobId>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, Viper::BlobId const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, Viper::BlobId const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docBlobId

namespace Test::Attachments::ConceptCoverage::docBool {

Viper::UUId const runtimeId{Viper::UUId::parse("de0efd5b-90bb-216f-03f8-cbf32245a423")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<bool> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<bool>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, bool const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, bool const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docBool

namespace Test::Attachments::ConceptCoverage::docClubKey {

Viper::UUId const runtimeId{Viper::UUId::parse("6c8c6c4a-f99b-1737-f3e9-b60da806f18b")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<KlubKey> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<KlubKey>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, KlubKey const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, KlubKey const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docClubKey

namespace Test::Attachments::ConceptCoverage::docCommitId {

Viper::UUId const runtimeId{Viper::UUId::parse("8bc4885f-0e59-2156-6534-f71674e16a62")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<Viper::CommitId> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<Viper::CommitId>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, Viper::CommitId const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, Viper::CommitId const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docCommitId

namespace Test::Attachments::ConceptCoverage::docConceptKey {

Viper::UUId const runtimeId{Viper::UUId::parse("e46092d8-19d2-786f-8ec2-ffe4eb96a2b0")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<ConceptAKey> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<ConceptAKey>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, ConceptAKey const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, ConceptAKey const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docConceptKey

namespace Test::Attachments::ConceptCoverage::docConceptKeyB {

Viper::UUId const runtimeId{Viper::UUId::parse("72eb0057-8f6c-7e05-f68e-36ec9bbdc0e6")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<ConceptBKey> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<ConceptBKey>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, ConceptBKey const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, ConceptBKey const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docConceptKeyB

namespace Test::Attachments::ConceptCoverage::docDouble {

Viper::UUId const runtimeId{Viper::UUId::parse("ddcc4ebf-809b-1186-a81d-e04887a55c28")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<double> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<double>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, double const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, double const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docDouble

namespace Test::Attachments::ConceptCoverage::docEnumeration {

Viper::UUId const runtimeId{Viper::UUId::parse("297e6910-d347-da0c-3dd6-563406dc742f")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<EnumerationE> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<EnumerationE>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, EnumerationE const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, EnumerationE const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docEnumeration

namespace Test::Attachments::ConceptCoverage::docFloat {

Viper::UUId const runtimeId{Viper::UUId::parse("59dc723c-e718-31bd-93e1-fce13b975469")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<float> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<float>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, float const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, float const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docFloat

namespace Test::Attachments::ConceptCoverage::docInt16 {

Viper::UUId const runtimeId{Viper::UUId::parse("138e62f6-c93a-11e6-8cbb-582c7de65a27")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::int16_t> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::int16_t>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::int16_t const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::int16_t const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docInt16

namespace Test::Attachments::ConceptCoverage::docInt32 {

Viper::UUId const runtimeId{Viper::UUId::parse("83d4d1bf-497b-e2ad-4efc-09509903ef47")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::int32_t> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::int32_t>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::int32_t const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::int32_t const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docInt32

namespace Test::Attachments::ConceptCoverage::docInt64 {

Viper::UUId const runtimeId{Viper::UUId::parse("bb3c8bde-0fd6-0535-4a63-361ba70dbe9c")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::int64_t> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::int64_t>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::int64_t const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::int64_t const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docInt64

namespace Test::Attachments::ConceptCoverage::docInt8 {

Viper::UUId const runtimeId{Viper::UUId::parse("0eb18fdd-6c1b-1584-34c8-f8356d4bc05d")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::int8_t> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::int8_t>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::int8_t const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::int8_t const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docInt8

namespace Test::Attachments::ConceptCoverage::docMap {

Viper::UUId const runtimeId{Viper::UUId::parse("d06b8489-8bd1-a8ff-4e64-d95c5771208f")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::map<std::uint8_t, std::string>> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::map<std::uint8_t, std::string>>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::map<std::uint8_t, std::string> const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::map<std::uint8_t, std::string> const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docMap

namespace Test::Attachments::ConceptCoverage::docMat {

Viper::UUId const runtimeId{Viper::UUId::parse("43e79483-eead-0925-cedd-78a45ce47d98")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::array<std::array<std::uint8_t, 2>, 2>> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::array<std::array<std::uint8_t, 2>, 2>>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::array<std::array<std::uint8_t, 2>, 2> const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::array<std::array<std::uint8_t, 2>, 2> const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docMat

namespace Test::Attachments::ConceptCoverage::docOptional {

Viper::UUId const runtimeId{Viper::UUId::parse("92e537a9-7a80-e98f-6e44-8a463cf9a970")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::optional<std::uint8_t>> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::optional<std::uint8_t>>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::optional<std::uint8_t> const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::optional<std::uint8_t> const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docOptional

namespace Test::Attachments::ConceptCoverage::docSet {

Viper::UUId const runtimeId{Viper::UUId::parse("7793f2b3-58ab-a3a3-bd44-04cf41b58cdc")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::set<std::uint8_t>> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::set<std::uint8_t>>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::set<std::uint8_t> const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::set<std::uint8_t> const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docSet

namespace Test::Attachments::ConceptCoverage::docString {

Viper::UUId const runtimeId{Viper::UUId::parse("9403f10d-288e-00cc-1169-f9a544777dbc")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::string> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::string>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::string const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::string const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docString

namespace Test::Attachments::ConceptCoverage::docStructureSingleField {

Viper::UUId const runtimeId{Viper::UUId::parse("19ebae3f-d189-04a2-dea3-deb80ece9ff8")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<StructureW> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<StructureW>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, StructureW const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, StructureW const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

void setF_single(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::uint8_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureW::f_singlePath(),
                    Features::Codec::encode(value));
}

} // namespace Test::Attachments::ConceptCoverage::docStructureSingleField

namespace Test::Attachments::ConceptCoverage::docTuple {

Viper::UUId const runtimeId{Viper::UUId::parse("d51d4c9f-f9cd-fe62-4417-28021df7961c")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::tuple<std::uint8_t, std::string>> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::tuple<std::uint8_t, std::string>>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::tuple<std::uint8_t, std::string> const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::tuple<std::uint8_t, std::string> const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docTuple

namespace Test::Attachments::ConceptCoverage::docUInt16 {

Viper::UUId const runtimeId{Viper::UUId::parse("3ae2904f-b0ed-d9e8-448a-fbd6d80be212")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::uint16_t> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::uint16_t>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::uint16_t const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::uint16_t const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docUInt16

namespace Test::Attachments::ConceptCoverage::docUInt32 {

Viper::UUId const runtimeId{Viper::UUId::parse("85ced0f5-1127-8750-a18e-3ecbfbe4813a")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::uint32_t> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::uint32_t>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::uint32_t const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::uint32_t const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docUInt32

namespace Test::Attachments::ConceptCoverage::docUInt64 {

Viper::UUId const runtimeId{Viper::UUId::parse("00a3fbe9-15b1-8e1f-fc42-c01d845ccc9a")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::uint64_t> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::uint64_t>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::uint64_t const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::uint64_t const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docUInt64

namespace Test::Attachments::ConceptCoverage::docUInt8 {

Viper::UUId const runtimeId{Viper::UUId::parse("5ac282e6-15c4-0a8c-bab9-b14ac6a7f9ed")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::uint8_t> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::uint8_t>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::uint8_t const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::uint8_t const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docUInt8

namespace Test::Attachments::ConceptCoverage::docUUId {

Viper::UUId const runtimeId{Viper::UUId::parse("a79058d8-5ee7-303d-1d19-50f01983a35b")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<Viper::UUId> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<Viper::UUId>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, Viper::UUId const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, Viper::UUId const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docUUId

namespace Test::Attachments::ConceptCoverage::docVariant {

Viper::UUId const runtimeId{Viper::UUId::parse("b7a81faa-fea8-a2cb-760b-edf353f16c63")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::variant<std::string, std::uint8_t>> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::variant<std::string, std::uint8_t>>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::variant<std::string, std::uint8_t> const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::variant<std::string, std::uint8_t> const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docVariant

namespace Test::Attachments::ConceptCoverage::docVec {

Viper::UUId const runtimeId{Viper::UUId::parse("73d224c0-d38f-4b5a-d225-bad481cec150")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::array<std::uint8_t, 2>> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::array<std::uint8_t, 2>>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::array<std::uint8_t, 2> const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::array<std::uint8_t, 2> const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docVec

namespace Test::Attachments::ConceptCoverage::docVector {

Viper::UUId const runtimeId{Viper::UUId::parse("ebb21187-7004-e7fa-23e6-690803352742")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<std::vector<std::uint8_t>> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<std::vector<std::uint8_t>>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::vector<std::uint8_t> const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::vector<std::uint8_t> const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docVector

namespace Test::Attachments::ConceptCoverage::docXArray {

Viper::UUId const runtimeId{Viper::UUId::parse("d45a1e55-9fc4-037e-5ce7-856093a638be")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(ConceptCoverageKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<ConceptCoverageKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<ConceptCoverageKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<Viper::XArray<std::uint8_t>> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<Viper::XArray<std::uint8_t>>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, Viper::XArray<std::uint8_t> const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, Viper::XArray<std::uint8_t> const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}
} // namespace Test::Attachments::ConceptCoverage::docXArray

namespace Test::Attachments::Klub::propertiesD {

Viper::UUId const runtimeId{Viper::UUId::parse("f7a9f794-cedc-a3ff-9530-63f86e932850")};

namespace {

/// L'attachment tel que le runtime le connaît, résolu une fois.
std::shared_ptr<Viper::Attachment> const & attachment() {
    static auto const instance = Features::Codec::definitions()->checkAttachment(runtimeId);
    return instance;
}

/// La clé, encodée. Le cast dit ce que le modèle sait déjà : la clé d'un attachment en est une.
std::shared_ptr<Viper::ValueKey> encodeKey(KlubKey const & key) {
    return Viper::ValueKey::cast(Features::Codec::encode(key));
}

} // namespace

std::set<KlubKey> keys(Viper::AttachmentGetting const & getting) {
    std::set<KlubKey> result;
    for (Viper::ValueSetIter it{getting.keys(attachment())}; it.hasNext(); it.next())
        result.insert(Features::Codec::decode<KlubKey>(it.value()));

    return result;
}

bool has(Viper::AttachmentGetting const & getting, KlubKey const & key) {
    return getting.has(attachment(), encodeKey(key));
}

std::optional<StructureV> get(Viper::AttachmentGetting const & getting, KlubKey const & key) {
    auto const document = getting.get(attachment(), encodeKey(key));
    if (document->isNil())
        return std::nullopt;

    return Features::Codec::decode<StructureV>(document->unwrap());
}

void set(Viper::AttachmentMutating & mutating, KlubKey const & key, StructureV const & value) {
    mutating.set(attachment(), encodeKey(key), Features::Codec::encode(value));
}

void diff(Viper::AttachmentMutating & mutating, KlubKey const & key, StructureV const & value,
          bool recursive) {
    mutating.diff(attachment(), encodeKey(key), Features::Codec::encode(value), recursive);
}

void setF_bool(Viper::AttachmentMutating & mutating, KlubKey const & key, bool value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_boolPath(),
                    Features::Codec::encode(value));
}

void setF_uint8(Viper::AttachmentMutating & mutating, KlubKey const & key, std::uint8_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_uint8Path(),
                    Features::Codec::encode(value));
}

void setF_uint16(Viper::AttachmentMutating & mutating, KlubKey const & key, std::uint16_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_uint16Path(),
                    Features::Codec::encode(value));
}

void setF_uint32(Viper::AttachmentMutating & mutating, KlubKey const & key, std::uint32_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_uint32Path(),
                    Features::Codec::encode(value));
}

void setF_uint64(Viper::AttachmentMutating & mutating, KlubKey const & key, std::uint64_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_uint64Path(),
                    Features::Codec::encode(value));
}

void setF_int8(Viper::AttachmentMutating & mutating, KlubKey const & key, std::int8_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_int8Path(),
                    Features::Codec::encode(value));
}

void setF_int16(Viper::AttachmentMutating & mutating, KlubKey const & key, std::int16_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_int16Path(),
                    Features::Codec::encode(value));
}

void setF_int32(Viper::AttachmentMutating & mutating, KlubKey const & key, std::int32_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_int32Path(),
                    Features::Codec::encode(value));
}

void setF_int64(Viper::AttachmentMutating & mutating, KlubKey const & key, std::int64_t value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_int64Path(),
                    Features::Codec::encode(value));
}

void setF_float(Viper::AttachmentMutating & mutating, KlubKey const & key, float value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_floatPath(),
                    Features::Codec::encode(value));
}

void setF_double(Viper::AttachmentMutating & mutating, KlubKey const & key, double value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_doublePath(),
                    Features::Codec::encode(value));
}

void setF_uuid(Viper::AttachmentMutating & mutating, KlubKey const & key, Viper::UUId const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_uuidPath(),
                    Features::Codec::encode(value));
}

void setF_string(Viper::AttachmentMutating & mutating, KlubKey const & key, std::string const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_stringPath(),
                    Features::Codec::encode(value));
}

void setF_vec(Viper::AttachmentMutating & mutating, KlubKey const & key, std::array<std::uint8_t, 2> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_vecPath(),
                    Features::Codec::encode(value));
}

void setF_mat(Viper::AttachmentMutating & mutating, KlubKey const & key, std::array<std::array<std::uint8_t, 3>, 2> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_matPath(),
                    Features::Codec::encode(value));
}

void setF_tuple(Viper::AttachmentMutating & mutating, KlubKey const & key, std::tuple<std::uint8_t, std::string> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_tuplePath(),
                    Features::Codec::encode(value));
}

void setF_optional(Viper::AttachmentMutating & mutating, KlubKey const & key, std::optional<std::uint8_t> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_optionalPath(),
                    Features::Codec::encode(value));
}

void setF_vector(Viper::AttachmentMutating & mutating, KlubKey const & key, std::vector<std::uint8_t> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_vectorPath(),
                    Features::Codec::encode(value));
}

void setF_set(Viper::AttachmentMutating & mutating, KlubKey const & key, std::set<std::uint8_t> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_setPath(),
                    Features::Codec::encode(value));
}

void setF_map(Viper::AttachmentMutating & mutating, KlubKey const & key, std::map<std::uint8_t, std::string> const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_mapPath(),
                    Features::Codec::encode(value));
}

void setF_E(Viper::AttachmentMutating & mutating, KlubKey const & key, EnumerationE value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_EPath(),
                    Features::Codec::encode(value));
}

void setF_S(Viper::AttachmentMutating & mutating, KlubKey const & key, StructureS const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_SPath(),
                    Features::Codec::encode(value));
}

void setF_T(Viper::AttachmentMutating & mutating, KlubKey const & key, StructureT const & value) {
    mutating.update(attachment(), encodeKey(key),
                    Test::Fields::StructureV::f_TPath(),
                    Features::Codec::encode(value));
}

} // namespace Test::Attachments::Klub::propertiesD