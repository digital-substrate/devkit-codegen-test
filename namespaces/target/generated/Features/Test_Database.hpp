// Test — ses attachments, vus depuis une base de données.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/features/Features.dsm.json by kibo-2.0.0.jar

#ifndef Test_Database_hpp
#define Test_Database_hpp

#include "Test_Data.hpp"

#include "Viper_Database.hpp"

#include <optional>
#include <set>

namespace Test::Database::Any_concept::propertiesAnyConceptAny {

std::set<::Features::AnyConceptKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ::Features::AnyConceptKey const & key);
std::optional<Viper::Any> get(std::shared_ptr<Viper::Database const> const & db, ::Features::AnyConceptKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ::Features::AnyConceptKey const & key, Viper::Any const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ::Features::AnyConceptKey const & key);

} // namespace Test::Database::Any_concept::propertiesAnyConceptAny

namespace Test::Database::ConceptA::properties {

std::set<ConceptAKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptAKey const & key);
std::optional<StructureV> get(std::shared_ptr<Viper::Database const> const & db, ConceptAKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key, StructureV const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key);

} // namespace Test::Database::ConceptA::properties

namespace Test::Database::ConceptA::propertiesInt8 {

std::set<ConceptAKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptAKey const & key);
std::optional<std::int8_t> get(std::shared_ptr<Viper::Database const> const & db, ConceptAKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key, std::int8_t const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key);

} // namespace Test::Database::ConceptA::propertiesInt8

namespace Test::Database::ConceptA::propertiesMapInt8String {

std::set<ConceptAKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptAKey const & key);
std::optional<std::map<std::int8_t, std::string>> get(std::shared_ptr<Viper::Database const> const & db, ConceptAKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key, std::map<std::int8_t, std::string> const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key);

} // namespace Test::Database::ConceptA::propertiesMapInt8String

namespace Test::Database::ConceptA::propertiesSeInt8 {

std::set<ConceptAKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptAKey const & key);
std::optional<std::set<std::int8_t>> get(std::shared_ptr<Viper::Database const> const & db, ConceptAKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key, std::set<std::int8_t> const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key);

} // namespace Test::Database::ConceptA::propertiesSeInt8

namespace Test::Database::ConceptA::propertiesXArray {

std::set<ConceptAKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptAKey const & key);
std::optional<Viper::XArray<std::int8_t>> get(std::shared_ptr<Viper::Database const> const & db, ConceptAKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key, Viper::XArray<std::int8_t> const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key);

} // namespace Test::Database::ConceptA::propertiesXArray

namespace Test::Database::ConceptB::propertiesB {

std::set<ConceptBKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptBKey const & key);
std::optional<StructureT> get(std::shared_ptr<Viper::Database const> const & db, ConceptBKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptBKey const & key, StructureT const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptBKey const & key);

} // namespace Test::Database::ConceptB::propertiesB

namespace Test::Database::ConceptC::propertiesC {

std::set<ConceptCKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCKey const & key);
std::optional<StructureU> get(std::shared_ptr<Viper::Database const> const & db, ConceptCKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCKey const & key, StructureU const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCKey const & key);

} // namespace Test::Database::ConceptC::propertiesC

namespace Test::Database::ConceptCoverage::docAny {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<Viper::Any> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, Viper::Any const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docAny

namespace Test::Database::ConceptCoverage::docAnyConceptKey {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<::Features::AnyConceptKey> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, ::Features::AnyConceptKey const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docAnyConceptKey

namespace Test::Database::ConceptCoverage::docBlob {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<Viper::Blob> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, Viper::Blob const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docBlob

namespace Test::Database::ConceptCoverage::docBlobId {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<Viper::BlobId> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, Viper::BlobId const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docBlobId

namespace Test::Database::ConceptCoverage::docBool {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<bool> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, bool const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docBool

namespace Test::Database::ConceptCoverage::docClubKey {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<KlubKey> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, KlubKey const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docClubKey

namespace Test::Database::ConceptCoverage::docCommitId {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<Viper::CommitId> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, Viper::CommitId const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docCommitId

namespace Test::Database::ConceptCoverage::docConceptKey {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<ConceptAKey> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, ConceptAKey const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docConceptKey

namespace Test::Database::ConceptCoverage::docConceptKeyB {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<ConceptBKey> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, ConceptBKey const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docConceptKeyB

namespace Test::Database::ConceptCoverage::docDouble {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<double> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, double const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docDouble

namespace Test::Database::ConceptCoverage::docEnumeration {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<EnumerationE> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, EnumerationE const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docEnumeration

namespace Test::Database::ConceptCoverage::docFloat {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<float> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, float const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docFloat

namespace Test::Database::ConceptCoverage::docInt16 {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<std::int16_t> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::int16_t const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docInt16

namespace Test::Database::ConceptCoverage::docInt32 {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<std::int32_t> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::int32_t const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docInt32

namespace Test::Database::ConceptCoverage::docInt64 {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<std::int64_t> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::int64_t const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docInt64

namespace Test::Database::ConceptCoverage::docInt8 {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<std::int8_t> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::int8_t const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docInt8

namespace Test::Database::ConceptCoverage::docMap {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<std::map<std::uint8_t, std::string>> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::map<std::uint8_t, std::string> const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docMap

namespace Test::Database::ConceptCoverage::docMat {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<std::array<std::array<std::uint8_t, 2>, 2>> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::array<std::array<std::uint8_t, 2>, 2> const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docMat

namespace Test::Database::ConceptCoverage::docOptional {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<std::optional<std::uint8_t>> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::optional<std::uint8_t> const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docOptional

namespace Test::Database::ConceptCoverage::docSet {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<std::set<std::uint8_t>> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::set<std::uint8_t> const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docSet

namespace Test::Database::ConceptCoverage::docString {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<std::string> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::string const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docString

namespace Test::Database::ConceptCoverage::docStructureSingleField {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<StructureW> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, StructureW const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docStructureSingleField

namespace Test::Database::ConceptCoverage::docTuple {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<std::tuple<std::uint8_t, std::string>> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::tuple<std::uint8_t, std::string> const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docTuple

namespace Test::Database::ConceptCoverage::docUInt16 {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<std::uint16_t> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::uint16_t const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docUInt16

namespace Test::Database::ConceptCoverage::docUInt32 {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<std::uint32_t> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::uint32_t const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docUInt32

namespace Test::Database::ConceptCoverage::docUInt64 {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<std::uint64_t> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::uint64_t const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docUInt64

namespace Test::Database::ConceptCoverage::docUInt8 {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<std::uint8_t> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::uint8_t const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docUInt8

namespace Test::Database::ConceptCoverage::docUUId {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<Viper::UUId> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, Viper::UUId const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docUUId

namespace Test::Database::ConceptCoverage::docVariant {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<std::variant<std::string, std::uint8_t>> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::variant<std::string, std::uint8_t> const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docVariant

namespace Test::Database::ConceptCoverage::docVec {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<std::array<std::uint8_t, 2>> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::array<std::uint8_t, 2> const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docVec

namespace Test::Database::ConceptCoverage::docVector {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<std::vector<std::uint8_t>> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::vector<std::uint8_t> const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docVector

namespace Test::Database::ConceptCoverage::docXArray {

std::set<ConceptCoverageKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
std::optional<Viper::XArray<std::uint8_t>> get(std::shared_ptr<Viper::Database const> const & db, ConceptCoverageKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, Viper::XArray<std::uint8_t> const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

} // namespace Test::Database::ConceptCoverage::docXArray

namespace Test::Database::Klub::propertiesD {

std::set<KlubKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, KlubKey const & key);
std::optional<StructureV> get(std::shared_ptr<Viper::Database const> const & db, KlubKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, KlubKey const & key, StructureV const & document);
bool del(std::shared_ptr<Viper::Database> const & db, KlubKey const & key);

} // namespace Test::Database::Klub::propertiesD

#endif