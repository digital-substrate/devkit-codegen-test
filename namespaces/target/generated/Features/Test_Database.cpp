// unité Test — l'implémentation, qui est cinq renvois par attachment.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/features/Features.dsm.json by kibo-2.0.0.jar

#include "Test_Database.hpp"

#include "Test_Attachments.hpp"
#include "Test_Codec.hpp"

#include "Features_Db.hpp"

namespace Test::Database::AnyConcept::propertiesAnyConceptAny {

namespace {
auto const & attachment() { return Test::Attachments::AnyConcept::propertiesAnyConceptAny::runtimeId; }
}

std::set<::Features::AnyConceptKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<::Features::AnyConceptKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ::Features::AnyConceptKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<Viper::Any> get(std::shared_ptr<Viper::Database const> const & db, ::Features::AnyConceptKey const & key) {
    return Features::Db::get<Viper::Any>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ::Features::AnyConceptKey const & key, Viper::Any const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ::Features::AnyConceptKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::AnyConcept::propertiesAnyConceptAny

namespace Test::Database::ConceptA::properties {

namespace {
auto const & attachment() { return Test::Attachments::ConceptA::properties::runtimeId; }
}

std::set<ConceptAKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptAKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptAKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<StructureV> get(std::shared_ptr<Viper::Database const> const & db, ConceptAKey const & key) {
    return Features::Db::get<StructureV>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key, StructureV const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptA::properties

namespace Test::Database::ConceptA::propertiesInt8 {

namespace {
auto const & attachment() { return Test::Attachments::ConceptA::propertiesInt8::runtimeId; }
}

std::set<ConceptAKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptAKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptAKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<std::int8_t> get(std::shared_ptr<Viper::Database const> const & db, ConceptAKey const & key) {
    return Features::Db::get<std::int8_t>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key, std::int8_t const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptA::propertiesInt8

namespace Test::Database::ConceptA::propertiesMapInt8String {

namespace {
auto const & attachment() { return Test::Attachments::ConceptA::propertiesMapInt8String::runtimeId; }
}

std::set<ConceptAKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptAKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptAKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<std::map<std::int8_t, std::string>> get(std::shared_ptr<Viper::Database const> const & db, ConceptAKey const & key) {
    return Features::Db::get<std::map<std::int8_t, std::string>>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key, std::map<std::int8_t, std::string> const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptA::propertiesMapInt8String

namespace Test::Database::ConceptA::propertiesSeInt8 {

namespace {
auto const & attachment() { return Test::Attachments::ConceptA::propertiesSeInt8::runtimeId; }
}

std::set<ConceptAKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptAKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptAKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<std::set<std::int8_t>> get(std::shared_ptr<Viper::Database const> const & db, ConceptAKey const & key) {
    return Features::Db::get<std::set<std::int8_t>>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key, std::set<std::int8_t> const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptA::propertiesSeInt8

namespace Test::Database::ConceptA::propertiesXArray {

namespace {
auto const & attachment() { return Test::Attachments::ConceptA::propertiesXArray::runtimeId; }
}

std::set<ConceptAKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptAKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptAKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<Viper::XArray<std::int8_t>> get(std::shared_ptr<Viper::Database const> const & db, ConceptAKey const & key) {
    return Features::Db::get<Viper::XArray<std::int8_t>>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key, Viper::XArray<std::int8_t> const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptA::propertiesXArray

namespace Test::Database::ConceptB::propertiesB {

namespace {
auto const & attachment() { return Test::Attachments::ConceptB::propertiesB::runtimeId; }
}

std::set<ConceptBKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptBKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptBKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<StructureT> get(std::shared_ptr<Viper::Database const> const & db, ConceptBKey const & key) {
    return Features::Db::get<StructureT>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptBKey const & key, StructureT const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptBKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptB::propertiesB

namespace Test::Database::ConceptC::propertiesC {

namespace {
auto const & attachment() { return Test::Attachments::ConceptC::propertiesC::runtimeId; }
}

std::set<ConceptCKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<StructureU> get(std::shared_ptr<Viper::Database const> const & db, ConceptCKey const & key) {
    return Features::Db::get<StructureU>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCKey const & key, StructureU const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptC::propertiesC

namespace Test::Database::ConceptCoverage::docAny {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docAny::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<Viper::Any> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<Viper::Any>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, Viper::Any const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docAny

namespace Test::Database::ConceptCoverage::docAnyConceptKey {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docAnyConceptKey::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<::Features::AnyConceptKey> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<::Features::AnyConceptKey>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, ::Features::AnyConceptKey const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docAnyConceptKey

namespace Test::Database::ConceptCoverage::docBlob {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docBlob::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<Viper::Blob> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<Viper::Blob>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, Viper::Blob const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docBlob

namespace Test::Database::ConceptCoverage::docBlobId {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docBlobId::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<Viper::BlobId> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<Viper::BlobId>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, Viper::BlobId const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docBlobId

namespace Test::Database::ConceptCoverage::docBool {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docBool::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<bool> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<bool>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, bool const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docBool

namespace Test::Database::ConceptCoverage::docClubKey {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docClubKey::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<KlubKey> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<KlubKey>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, KlubKey const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docClubKey

namespace Test::Database::ConceptCoverage::docCommitId {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docCommitId::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<Viper::CommitId> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<Viper::CommitId>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, Viper::CommitId const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docCommitId

namespace Test::Database::ConceptCoverage::docConceptKey {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docConceptKey::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<ConceptAKey> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<ConceptAKey>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, ConceptAKey const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docConceptKey

namespace Test::Database::ConceptCoverage::docConceptKeyB {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docConceptKeyB::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<ConceptBKey> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<ConceptBKey>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, ConceptBKey const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docConceptKeyB

namespace Test::Database::ConceptCoverage::docDouble {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docDouble::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<double> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<double>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, double const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docDouble

namespace Test::Database::ConceptCoverage::docEnumeration {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docEnumeration::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<EnumerationE> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<EnumerationE>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, EnumerationE const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docEnumeration

namespace Test::Database::ConceptCoverage::docFloat {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docFloat::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<float> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<float>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, float const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docFloat

namespace Test::Database::ConceptCoverage::docInt16 {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docInt16::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<std::int16_t> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<std::int16_t>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::int16_t const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docInt16

namespace Test::Database::ConceptCoverage::docInt32 {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docInt32::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<std::int32_t> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<std::int32_t>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::int32_t const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docInt32

namespace Test::Database::ConceptCoverage::docInt64 {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docInt64::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<std::int64_t> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<std::int64_t>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::int64_t const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docInt64

namespace Test::Database::ConceptCoverage::docInt8 {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docInt8::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<std::int8_t> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<std::int8_t>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::int8_t const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docInt8

namespace Test::Database::ConceptCoverage::docMap {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docMap::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<std::map<std::uint8_t, std::string>> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<std::map<std::uint8_t, std::string>>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::map<std::uint8_t, std::string> const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docMap

namespace Test::Database::ConceptCoverage::docMat {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docMat::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<std::array<std::array<std::uint8_t, 2>, 2>> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<std::array<std::array<std::uint8_t, 2>, 2>>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::array<std::array<std::uint8_t, 2>, 2> const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docMat

namespace Test::Database::ConceptCoverage::docOptional {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docOptional::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<std::optional<std::uint8_t>> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<std::optional<std::uint8_t>>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::optional<std::uint8_t> const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docOptional

namespace Test::Database::ConceptCoverage::docSet {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docSet::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<std::set<std::uint8_t>> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<std::set<std::uint8_t>>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::set<std::uint8_t> const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docSet

namespace Test::Database::ConceptCoverage::docString {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docString::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<std::string> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<std::string>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::string const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docString

namespace Test::Database::ConceptCoverage::docStructureSingleField {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docStructureSingleField::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<StructureW> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<StructureW>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, StructureW const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docStructureSingleField

namespace Test::Database::ConceptCoverage::docTuple {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docTuple::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<std::tuple<std::uint8_t, std::string>> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<std::tuple<std::uint8_t, std::string>>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::tuple<std::uint8_t, std::string> const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docTuple

namespace Test::Database::ConceptCoverage::docUInt16 {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docUInt16::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<std::uint16_t> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<std::uint16_t>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::uint16_t const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docUInt16

namespace Test::Database::ConceptCoverage::docUInt32 {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docUInt32::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<std::uint32_t> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<std::uint32_t>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::uint32_t const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docUInt32

namespace Test::Database::ConceptCoverage::docUInt64 {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docUInt64::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<std::uint64_t> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<std::uint64_t>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::uint64_t const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docUInt64

namespace Test::Database::ConceptCoverage::docUInt8 {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docUInt8::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<std::uint8_t> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<std::uint8_t>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::uint8_t const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docUInt8

namespace Test::Database::ConceptCoverage::docUUId {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docUUId::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<Viper::UUId> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<Viper::UUId>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, Viper::UUId const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docUUId

namespace Test::Database::ConceptCoverage::docVariant {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docVariant::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<std::variant<std::string, std::uint8_t>> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<std::variant<std::string, std::uint8_t>>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::variant<std::string, std::uint8_t> const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docVariant

namespace Test::Database::ConceptCoverage::docVec {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docVec::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<std::array<std::uint8_t, 2>> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<std::array<std::uint8_t, 2>>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::array<std::uint8_t, 2> const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docVec

namespace Test::Database::ConceptCoverage::docVector {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docVector::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<std::vector<std::uint8_t>> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<std::vector<std::uint8_t>>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::vector<std::uint8_t> const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docVector

namespace Test::Database::ConceptCoverage::docXArray {

namespace {
auto const & attachment() { return Test::Attachments::ConceptCoverage::docXArray::runtimeId; }
}

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<ConceptCoverageKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<Viper::XArray<std::uint8_t>> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key) {
    return Features::Db::get<Viper::XArray<std::uint8_t>>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, Viper::XArray<std::uint8_t> const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::ConceptCoverage::docXArray

namespace Test::Database::Klub::propertiesD {

namespace {
auto const & attachment() { return Test::Attachments::Klub::propertiesD::runtimeId; }
}

std::set<KlubKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Features::Db::keys<KlubKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, KlubKey const & key) {
    return Features::Db::has(db, attachment(), key);
}

std::optional<StructureV> get(std::shared_ptr<Viper::Database const> const & db, KlubKey const & key) {
    return Features::Db::get<StructureV>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, KlubKey const & key, StructureV const & document) {
    return Features::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, KlubKey const & key) {
    return Features::Db::del(db, attachment(), key);
}

} // namespace Test::Database::Klub::propertiesD