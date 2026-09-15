// Woven — l'épreuve de ses types.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

#include "Woven_Test.hpp"

#include "Woven_Attachments.hpp"
#include "Woven_Codec.hpp"
#include "Woven_Database.hpp"
#include "Woven_Model.hpp"
#include "Parts_Codec.hpp"
#include "Core_Codec.hpp"
#include "Parts_Model.hpp"
#include "Core_Model.hpp"

#include "Crossing_Test.hpp"

namespace Woven {

void test() {
    Crossing::Test::roundTrip<KnotKey>();
    Crossing::Test::roundTrip<DerivedKey>();
    Crossing::Test::roundTrip<WeaveKey>();
    Crossing::Test::roundTrip<Composites>();
    Crossing::Test::roundTrip<Entities>();
    Crossing::Test::roundTrip<Nested>();
}

void testDatabase(std::shared_ptr<Viper::Database> const & db) {
    Crossing::Test::roundTripAttachment<Core::ThingKey, Parts::Colour>(
        db, Attachments::Core_Thing::mark::runtimeId);
    Crossing::Test::roundTripAttachment<KnotKey, ::Crossing::AnyConceptKey>(
        db, Attachments::Knot::docAnyConceptKey::runtimeId);
    Crossing::Test::roundTripAttachment<KnotKey, Core::Colour>(
        db, Attachments::Knot::docColour::runtimeId);
    Crossing::Test::roundTripAttachment<KnotKey, Composites>(
        db, Attachments::Knot::docComposites::runtimeId);
    Crossing::Test::roundTripAttachment<KnotKey, Core::Grade>(
        db, Attachments::Knot::docGrade::runtimeId);
    Crossing::Test::roundTripAttachment<KnotKey, Core::KlubKey>(
        db, Attachments::Knot::docKlubKey::runtimeId);
    Crossing::Test::roundTripAttachment<KnotKey, std::map<Core::Grade, Parts::Colour>>(
        db, Attachments::Knot::docMapEnum::runtimeId);
    Crossing::Test::roundTripAttachment<KnotKey, std::map<Core::ThingKey, Parts::ThingKey>>(
        db, Attachments::Knot::docMapKeys::runtimeId);
    Crossing::Test::roundTripAttachment<KnotKey, std::optional<Core::ThingKey>>(
        db, Attachments::Knot::docOptional::runtimeId);
    Crossing::Test::roundTripAttachment<KnotKey, Parts::Colour>(
        db, Attachments::Knot::docOtherColour::runtimeId);
    Crossing::Test::roundTripAttachment<KnotKey, std::set<Core::ThingKey>>(
        db, Attachments::Knot::docSet::runtimeId);
    Crossing::Test::roundTripAttachment<KnotKey, Core::ThingKey>(
        db, Attachments::Knot::docThingKey::runtimeId);
    Crossing::Test::roundTripAttachment<KnotKey, std::tuple<Core::Colour, Parts::Colour>>(
        db, Attachments::Knot::docTuple::runtimeId);
    Crossing::Test::roundTripAttachment<KnotKey, std::variant<Core::Colour, Parts::Colour>>(
        db, Attachments::Knot::docVariant::runtimeId);
    Crossing::Test::roundTripAttachment<KnotKey, std::vector<Parts::Colour>>(
        db, Attachments::Knot::docVector::runtimeId);
    Crossing::Test::roundTripAttachment<KnotKey, Viper::XArray<Core::Colour>>(
        db, Attachments::Knot::docXArray::runtimeId);
    Crossing::Test::roundTripAttachment<Parts::ThingKey, Core::Colour>(
        db, Attachments::Parts_Thing::mark::runtimeId);
}

} // namespace Woven