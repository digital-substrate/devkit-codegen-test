// unité Core — l'épreuve de ses types.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

#include "Core_Test.hpp"

#include "Core_Attachments.hpp"
#include "Core_Codec.hpp"
#include "Core_Model.hpp"

#include "Crossing_Test.hpp"

namespace Core {

void test() {
    Crossing::Test::roundTrip<OtherKey>();
    Crossing::Test::roundTrip<ThingKey>();
    Crossing::Test::roundTrip<SubThingKey>();
    Crossing::Test::roundTrip<KlubKey>();
    Crossing::Test::roundTrip<Grade>();
    Crossing::Test::roundTrip<Bag>();
    Crossing::Test::roundTrip<Colour>();
    Crossing::Test::roundTrip<Defaults>();
    Crossing::Test::roundTrip<Scalars>();
    Crossing::Test::roundTrip<Single>();
}

void testDatabase(std::shared_ptr<Viper::Database> const & db) {
    Crossing::Test::roundTripAttachment<ThingKey, Bag>(
        db, Attachments::Thing::bag::descriptor());
    Crossing::Test::roundTripAttachment<ThingKey, Colour>(
        db, Attachments::Thing::colour::descriptor());
    Crossing::Test::roundTripAttachment<ThingKey, Viper::XArray<Colour>>(
        db, Attachments::Thing::history::descriptor());
    Crossing::Test::roundTripAttachment<ThingKey, std::map<ThingKey, Colour>>(
        db, Attachments::Thing::palette::descriptor());
    Crossing::Test::roundTripAttachment<ThingKey, std::set<ThingKey>>(
        db, Attachments::Thing::related::descriptor());
    Crossing::Test::roundTripAttachment<ThingKey, Scalars>(
        db, Attachments::Thing::scalars::descriptor());
}

void fuzzDatabase(std::shared_ptr<Viper::Database> const & db, std::size_t count) {
    Crossing::Test::fuzzAttachment<ThingKey, Bag>(
        db, Attachments::Thing::bag::descriptor(), count);
    Crossing::Test::fuzzAttachment<ThingKey, Colour>(
        db, Attachments::Thing::colour::descriptor(), count);
    Crossing::Test::fuzzAttachment<ThingKey, Viper::XArray<Colour>>(
        db, Attachments::Thing::history::descriptor(), count);
    Crossing::Test::fuzzAttachment<ThingKey, std::map<ThingKey, Colour>>(
        db, Attachments::Thing::palette::descriptor(), count);
    Crossing::Test::fuzzAttachment<ThingKey, std::set<ThingKey>>(
        db, Attachments::Thing::related::descriptor(), count);
    Crossing::Test::fuzzAttachment<ThingKey, Scalars>(
        db, Attachments::Thing::scalars::descriptor(), count);
}

} // namespace Core