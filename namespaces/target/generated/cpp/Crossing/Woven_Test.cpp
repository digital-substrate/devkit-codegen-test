// unité Woven — l'épreuve de ses types.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

#include "Woven_Test.hpp"

#include "Woven_Attachments.hpp"
#include "Woven_Codec.hpp"
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
        db, Attachments::Core_Thing::mark::descriptor());
    Crossing::Test::roundTripAttachment<KnotKey, ::Crossing::AnyConceptKey>(
        db, Attachments::Knot::docAnyConceptKey::descriptor());
    Crossing::Test::roundTripAttachment<KnotKey, Core::Colour>(
        db, Attachments::Knot::docColour::descriptor());
    Crossing::Test::roundTripAttachment<KnotKey, Composites>(
        db, Attachments::Knot::docComposites::descriptor());
    Crossing::Test::roundTripAttachment<KnotKey, Core::Grade>(
        db, Attachments::Knot::docGrade::descriptor());
    Crossing::Test::roundTripAttachment<KnotKey, Core::KlubKey>(
        db, Attachments::Knot::docKlubKey::descriptor());
    Crossing::Test::roundTripAttachment<KnotKey, std::map<Core::Grade, Parts::Colour>>(
        db, Attachments::Knot::docMapEnum::descriptor());
    Crossing::Test::roundTripAttachment<KnotKey, std::map<Core::ThingKey, Parts::ThingKey>>(
        db, Attachments::Knot::docMapKeys::descriptor());
    Crossing::Test::roundTripAttachment<KnotKey, std::optional<Core::ThingKey>>(
        db, Attachments::Knot::docOptional::descriptor());
    Crossing::Test::roundTripAttachment<KnotKey, Parts::Colour>(
        db, Attachments::Knot::docOtherColour::descriptor());
    Crossing::Test::roundTripAttachment<KnotKey, std::set<Core::ThingKey>>(
        db, Attachments::Knot::docSet::descriptor());
    Crossing::Test::roundTripAttachment<KnotKey, Core::ThingKey>(
        db, Attachments::Knot::docThingKey::descriptor());
    Crossing::Test::roundTripAttachment<KnotKey, std::tuple<Core::Colour, Parts::Colour>>(
        db, Attachments::Knot::docTuple::descriptor());
    Crossing::Test::roundTripAttachment<KnotKey, std::variant<Core::Colour, Parts::Colour>>(
        db, Attachments::Knot::docVariant::descriptor());
    Crossing::Test::roundTripAttachment<KnotKey, std::vector<Parts::Colour>>(
        db, Attachments::Knot::docVector::descriptor());
    Crossing::Test::roundTripAttachment<KnotKey, Viper::XArray<Core::Colour>>(
        db, Attachments::Knot::docXArray::descriptor());
    Crossing::Test::roundTripAttachment<Parts::ThingKey, Core::Colour>(
        db, Attachments::Parts_Thing::mark::descriptor());
}

void fuzzDatabase(std::shared_ptr<Viper::Database> const & db, std::size_t count) {
    Crossing::Test::fuzzAttachment<Core::ThingKey, Parts::Colour>(
        db, Attachments::Core_Thing::mark::descriptor(), count);
    Crossing::Test::fuzzAttachment<KnotKey, ::Crossing::AnyConceptKey>(
        db, Attachments::Knot::docAnyConceptKey::descriptor(), count);
    Crossing::Test::fuzzAttachment<KnotKey, Core::Colour>(
        db, Attachments::Knot::docColour::descriptor(), count);
    Crossing::Test::fuzzAttachment<KnotKey, Composites>(
        db, Attachments::Knot::docComposites::descriptor(), count);
    Crossing::Test::fuzzAttachment<KnotKey, Core::Grade>(
        db, Attachments::Knot::docGrade::descriptor(), count);
    Crossing::Test::fuzzAttachment<KnotKey, Core::KlubKey>(
        db, Attachments::Knot::docKlubKey::descriptor(), count);
    Crossing::Test::fuzzAttachment<KnotKey, std::map<Core::Grade, Parts::Colour>>(
        db, Attachments::Knot::docMapEnum::descriptor(), count);
    Crossing::Test::fuzzAttachment<KnotKey, std::map<Core::ThingKey, Parts::ThingKey>>(
        db, Attachments::Knot::docMapKeys::descriptor(), count);
    Crossing::Test::fuzzAttachment<KnotKey, std::optional<Core::ThingKey>>(
        db, Attachments::Knot::docOptional::descriptor(), count);
    Crossing::Test::fuzzAttachment<KnotKey, Parts::Colour>(
        db, Attachments::Knot::docOtherColour::descriptor(), count);
    Crossing::Test::fuzzAttachment<KnotKey, std::set<Core::ThingKey>>(
        db, Attachments::Knot::docSet::descriptor(), count);
    Crossing::Test::fuzzAttachment<KnotKey, Core::ThingKey>(
        db, Attachments::Knot::docThingKey::descriptor(), count);
    Crossing::Test::fuzzAttachment<KnotKey, std::tuple<Core::Colour, Parts::Colour>>(
        db, Attachments::Knot::docTuple::descriptor(), count);
    Crossing::Test::fuzzAttachment<KnotKey, std::variant<Core::Colour, Parts::Colour>>(
        db, Attachments::Knot::docVariant::descriptor(), count);
    Crossing::Test::fuzzAttachment<KnotKey, std::vector<Parts::Colour>>(
        db, Attachments::Knot::docVector::descriptor(), count);
    Crossing::Test::fuzzAttachment<KnotKey, Viper::XArray<Core::Colour>>(
        db, Attachments::Knot::docXArray::descriptor(), count);
    Crossing::Test::fuzzAttachment<Parts::ThingKey, Core::Colour>(
        db, Attachments::Parts_Thing::mark::descriptor(), count);
}

} // namespace Woven