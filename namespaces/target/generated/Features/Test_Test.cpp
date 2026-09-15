// unité Test — l'épreuve de ses types.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/features/Features.dsm.json by kibo-2.0.0.jar

#include "Test_Test.hpp"

#include "Test_Attachments.hpp"
#include "Test_Codec.hpp"
#include "Test_Database.hpp"
#include "Test_Model.hpp"

#include "Features_Test.hpp"

namespace Test {

void test() {
    Features::Test::roundTrip<ConceptAKey>();
    Features::Test::roundTrip<ConceptBKey>();
    Features::Test::roundTrip<ConceptCoverageKey>();
    Features::Test::roundTrip<ConceptDKey>();
    Features::Test::roundTrip<ConceptCKey>();
    Features::Test::roundTrip<EmptyKlubKey>();
    Features::Test::roundTrip<KlubKey>();
    Features::Test::roundTrip<EnumerationE>();
    Features::Test::roundTrip<StructureS>();
    Features::Test::roundTrip<StructureT>();
    Features::Test::roundTrip<StructureU>();
    Features::Test::roundTrip<StructureV>();
    Features::Test::roundTrip<StructureW>();
}

void testDatabase(std::shared_ptr<Viper::Database> const & db) {
    Features::Test::roundTripAttachment<::Features::AnyConceptKey, Viper::Any>(
        db, Attachments::AnyConcept::propertiesAnyConceptAny::runtimeId);
    Features::Test::roundTripAttachment<ConceptAKey, StructureV>(
        db, Attachments::ConceptA::properties::runtimeId);
    Features::Test::roundTripAttachment<ConceptAKey, std::int8_t>(
        db, Attachments::ConceptA::propertiesInt8::runtimeId);
    Features::Test::roundTripAttachment<ConceptAKey, std::map<std::int8_t, std::string>>(
        db, Attachments::ConceptA::propertiesMapInt8String::runtimeId);
    Features::Test::roundTripAttachment<ConceptAKey, std::set<std::int8_t>>(
        db, Attachments::ConceptA::propertiesSeInt8::runtimeId);
    Features::Test::roundTripAttachment<ConceptAKey, Viper::XArray<std::int8_t>>(
        db, Attachments::ConceptA::propertiesXArray::runtimeId);
    Features::Test::roundTripAttachment<ConceptBKey, StructureT>(
        db, Attachments::ConceptB::propertiesB::runtimeId);
    Features::Test::roundTripAttachment<ConceptCKey, StructureU>(
        db, Attachments::ConceptC::propertiesC::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, Viper::Any>(
        db, Attachments::ConceptCoverage::docAny::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, ::Features::AnyConceptKey>(
        db, Attachments::ConceptCoverage::docAnyConceptKey::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, Viper::Blob>(
        db, Attachments::ConceptCoverage::docBlob::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, Viper::BlobId>(
        db, Attachments::ConceptCoverage::docBlobId::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, bool>(
        db, Attachments::ConceptCoverage::docBool::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, KlubKey>(
        db, Attachments::ConceptCoverage::docClubKey::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, Viper::CommitId>(
        db, Attachments::ConceptCoverage::docCommitId::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, ConceptAKey>(
        db, Attachments::ConceptCoverage::docConceptKey::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, ConceptBKey>(
        db, Attachments::ConceptCoverage::docConceptKeyB::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, double>(
        db, Attachments::ConceptCoverage::docDouble::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, EnumerationE>(
        db, Attachments::ConceptCoverage::docEnumeration::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, float>(
        db, Attachments::ConceptCoverage::docFloat::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::int16_t>(
        db, Attachments::ConceptCoverage::docInt16::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::int32_t>(
        db, Attachments::ConceptCoverage::docInt32::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::int64_t>(
        db, Attachments::ConceptCoverage::docInt64::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::int8_t>(
        db, Attachments::ConceptCoverage::docInt8::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::map<std::uint8_t, std::string>>(
        db, Attachments::ConceptCoverage::docMap::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::array<std::array<std::uint8_t, 2>, 2>>(
        db, Attachments::ConceptCoverage::docMat::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::optional<std::uint8_t>>(
        db, Attachments::ConceptCoverage::docOptional::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::set<std::uint8_t>>(
        db, Attachments::ConceptCoverage::docSet::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::string>(
        db, Attachments::ConceptCoverage::docString::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, StructureW>(
        db, Attachments::ConceptCoverage::docStructureSingleField::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::tuple<std::uint8_t, std::string>>(
        db, Attachments::ConceptCoverage::docTuple::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::uint16_t>(
        db, Attachments::ConceptCoverage::docUInt16::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::uint32_t>(
        db, Attachments::ConceptCoverage::docUInt32::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::uint64_t>(
        db, Attachments::ConceptCoverage::docUInt64::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::uint8_t>(
        db, Attachments::ConceptCoverage::docUInt8::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, Viper::UUId>(
        db, Attachments::ConceptCoverage::docUUId::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::variant<std::string, std::uint8_t>>(
        db, Attachments::ConceptCoverage::docVariant::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::array<std::uint8_t, 2>>(
        db, Attachments::ConceptCoverage::docVec::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::vector<std::uint8_t>>(
        db, Attachments::ConceptCoverage::docVector::runtimeId);
    Features::Test::roundTripAttachment<ConceptCoverageKey, Viper::XArray<std::uint8_t>>(
        db, Attachments::ConceptCoverage::docXArray::runtimeId);
    Features::Test::roundTripAttachment<KlubKey, StructureV>(
        db, Attachments::Klub::propertiesD::runtimeId);
}

} // namespace Test