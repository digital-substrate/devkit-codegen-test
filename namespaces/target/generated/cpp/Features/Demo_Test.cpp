// unité Demo — l'épreuve de ses types.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/features/Features.dsm.json by kibo-2.0.0.jar

#include "Demo_Test.hpp"

#include "Demo_Attachments.hpp"
#include "Demo_Codec.hpp"
#include "Demo_Model.hpp"

#include "Features_Test.hpp"

namespace Demo {

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
        db, Attachments::AnyConcept::propertiesAnyConceptAny::descriptor());
    Features::Test::roundTripAttachment<ConceptAKey, StructureV>(
        db, Attachments::ConceptA::properties::descriptor());
    Features::Test::roundTripAttachment<ConceptAKey, std::int8_t>(
        db, Attachments::ConceptA::propertiesInt8::descriptor());
    Features::Test::roundTripAttachment<ConceptAKey, std::map<std::int8_t, std::string>>(
        db, Attachments::ConceptA::propertiesMapInt8String::descriptor());
    Features::Test::roundTripAttachment<ConceptAKey, std::set<std::int8_t>>(
        db, Attachments::ConceptA::propertiesSeInt8::descriptor());
    Features::Test::roundTripAttachment<ConceptAKey, Viper::XArray<std::int8_t>>(
        db, Attachments::ConceptA::propertiesXArray::descriptor());
    Features::Test::roundTripAttachment<ConceptBKey, StructureT>(
        db, Attachments::ConceptB::propertiesB::descriptor());
    Features::Test::roundTripAttachment<ConceptCKey, StructureU>(
        db, Attachments::ConceptC::propertiesC::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, Viper::Any>(
        db, Attachments::ConceptCoverage::docAny::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, ::Features::AnyConceptKey>(
        db, Attachments::ConceptCoverage::docAnyConceptKey::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, Viper::Blob>(
        db, Attachments::ConceptCoverage::docBlob::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, Viper::BlobId>(
        db, Attachments::ConceptCoverage::docBlobId::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, bool>(
        db, Attachments::ConceptCoverage::docBool::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, KlubKey>(
        db, Attachments::ConceptCoverage::docClubKey::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, Viper::CommitId>(
        db, Attachments::ConceptCoverage::docCommitId::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, ConceptAKey>(
        db, Attachments::ConceptCoverage::docConceptKey::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, ConceptBKey>(
        db, Attachments::ConceptCoverage::docConceptKeyB::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, double>(
        db, Attachments::ConceptCoverage::docDouble::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, EnumerationE>(
        db, Attachments::ConceptCoverage::docEnumeration::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, float>(
        db, Attachments::ConceptCoverage::docFloat::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::int16_t>(
        db, Attachments::ConceptCoverage::docInt16::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::int32_t>(
        db, Attachments::ConceptCoverage::docInt32::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::int64_t>(
        db, Attachments::ConceptCoverage::docInt64::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::int8_t>(
        db, Attachments::ConceptCoverage::docInt8::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::map<std::uint8_t, std::string>>(
        db, Attachments::ConceptCoverage::docMap::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::array<std::array<std::uint8_t, 2>, 2>>(
        db, Attachments::ConceptCoverage::docMat::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::optional<std::uint8_t>>(
        db, Attachments::ConceptCoverage::docOptional::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::set<std::uint8_t>>(
        db, Attachments::ConceptCoverage::docSet::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::string>(
        db, Attachments::ConceptCoverage::docString::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, StructureW>(
        db, Attachments::ConceptCoverage::docStructureSingleField::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::tuple<std::uint8_t, std::string>>(
        db, Attachments::ConceptCoverage::docTuple::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::uint16_t>(
        db, Attachments::ConceptCoverage::docUInt16::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::uint32_t>(
        db, Attachments::ConceptCoverage::docUInt32::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::uint64_t>(
        db, Attachments::ConceptCoverage::docUInt64::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::uint8_t>(
        db, Attachments::ConceptCoverage::docUInt8::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, Viper::UUId>(
        db, Attachments::ConceptCoverage::docUUId::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::variant<std::string, std::uint8_t>>(
        db, Attachments::ConceptCoverage::docVariant::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::array<std::uint8_t, 2>>(
        db, Attachments::ConceptCoverage::docVec::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, std::vector<std::uint8_t>>(
        db, Attachments::ConceptCoverage::docVector::descriptor());
    Features::Test::roundTripAttachment<ConceptCoverageKey, Viper::XArray<std::uint8_t>>(
        db, Attachments::ConceptCoverage::docXArray::descriptor());
    Features::Test::roundTripAttachment<KlubKey, StructureV>(
        db, Attachments::Klub::propertiesD::descriptor());
}

void fuzzDatabase(std::shared_ptr<Viper::Database> const & db, std::size_t count) {
    Features::Test::fuzzAttachment<::Features::AnyConceptKey, Viper::Any>(
        db, Attachments::AnyConcept::propertiesAnyConceptAny::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptAKey, StructureV>(
        db, Attachments::ConceptA::properties::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptAKey, std::int8_t>(
        db, Attachments::ConceptA::propertiesInt8::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptAKey, std::map<std::int8_t, std::string>>(
        db, Attachments::ConceptA::propertiesMapInt8String::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptAKey, std::set<std::int8_t>>(
        db, Attachments::ConceptA::propertiesSeInt8::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptAKey, Viper::XArray<std::int8_t>>(
        db, Attachments::ConceptA::propertiesXArray::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptBKey, StructureT>(
        db, Attachments::ConceptB::propertiesB::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCKey, StructureU>(
        db, Attachments::ConceptC::propertiesC::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, Viper::Any>(
        db, Attachments::ConceptCoverage::docAny::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, ::Features::AnyConceptKey>(
        db, Attachments::ConceptCoverage::docAnyConceptKey::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, Viper::Blob>(
        db, Attachments::ConceptCoverage::docBlob::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, Viper::BlobId>(
        db, Attachments::ConceptCoverage::docBlobId::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, bool>(
        db, Attachments::ConceptCoverage::docBool::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, KlubKey>(
        db, Attachments::ConceptCoverage::docClubKey::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, Viper::CommitId>(
        db, Attachments::ConceptCoverage::docCommitId::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, ConceptAKey>(
        db, Attachments::ConceptCoverage::docConceptKey::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, ConceptBKey>(
        db, Attachments::ConceptCoverage::docConceptKeyB::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, double>(
        db, Attachments::ConceptCoverage::docDouble::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, EnumerationE>(
        db, Attachments::ConceptCoverage::docEnumeration::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, float>(
        db, Attachments::ConceptCoverage::docFloat::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, std::int16_t>(
        db, Attachments::ConceptCoverage::docInt16::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, std::int32_t>(
        db, Attachments::ConceptCoverage::docInt32::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, std::int64_t>(
        db, Attachments::ConceptCoverage::docInt64::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, std::int8_t>(
        db, Attachments::ConceptCoverage::docInt8::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, std::map<std::uint8_t, std::string>>(
        db, Attachments::ConceptCoverage::docMap::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, std::array<std::array<std::uint8_t, 2>, 2>>(
        db, Attachments::ConceptCoverage::docMat::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, std::optional<std::uint8_t>>(
        db, Attachments::ConceptCoverage::docOptional::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, std::set<std::uint8_t>>(
        db, Attachments::ConceptCoverage::docSet::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, std::string>(
        db, Attachments::ConceptCoverage::docString::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, StructureW>(
        db, Attachments::ConceptCoverage::docStructureSingleField::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, std::tuple<std::uint8_t, std::string>>(
        db, Attachments::ConceptCoverage::docTuple::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, std::uint16_t>(
        db, Attachments::ConceptCoverage::docUInt16::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, std::uint32_t>(
        db, Attachments::ConceptCoverage::docUInt32::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, std::uint64_t>(
        db, Attachments::ConceptCoverage::docUInt64::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, std::uint8_t>(
        db, Attachments::ConceptCoverage::docUInt8::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, Viper::UUId>(
        db, Attachments::ConceptCoverage::docUUId::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, std::variant<std::string, std::uint8_t>>(
        db, Attachments::ConceptCoverage::docVariant::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, std::array<std::uint8_t, 2>>(
        db, Attachments::ConceptCoverage::docVec::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, std::vector<std::uint8_t>>(
        db, Attachments::ConceptCoverage::docVector::descriptor(), count);
    Features::Test::fuzzAttachment<ConceptCoverageKey, Viper::XArray<std::uint8_t>>(
        db, Attachments::ConceptCoverage::docXArray::descriptor(), count);
    Features::Test::fuzzAttachment<KlubKey, StructureV>(
        db, Attachments::Klub::propertiesD::descriptor(), count);
}

} // namespace Demo