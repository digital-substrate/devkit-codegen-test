// unité Core — l'épreuve de ses types.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

#include "Core_Test.hpp"

#include "Core_Attachments.hpp"
#include "Core_Codec.hpp"
#include "Core_Database.hpp"
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
        db, Attachments::Thing::bag::runtimeId);
    Crossing::Test::roundTripAttachment<ThingKey, Colour>(
        db, Attachments::Thing::colour::runtimeId);
    Crossing::Test::roundTripAttachment<ThingKey, Viper::XArray<Colour>>(
        db, Attachments::Thing::history::runtimeId);
    Crossing::Test::roundTripAttachment<ThingKey, std::map<ThingKey, Colour>>(
        db, Attachments::Thing::palette::runtimeId);
    Crossing::Test::roundTripAttachment<ThingKey, std::set<ThingKey>>(
        db, Attachments::Thing::related::runtimeId);
    Crossing::Test::roundTripAttachment<ThingKey, Scalars>(
        db, Attachments::Thing::scalars::runtimeId);
}

void fuzzDatabase(std::shared_ptr<Viper::Database> const & db, std::size_t count) {
    Crossing::Test::fuzzAttachment<ThingKey, Bag>(
        db, Attachments::Thing::bag::runtimeId, count);
    Crossing::Test::fuzzAttachment<ThingKey, Colour>(
        db, Attachments::Thing::colour::runtimeId, count);
    Crossing::Test::fuzzAttachment<ThingKey, Viper::XArray<Colour>>(
        db, Attachments::Thing::history::runtimeId, count);
    Crossing::Test::fuzzAttachment<ThingKey, std::map<ThingKey, Colour>>(
        db, Attachments::Thing::palette::runtimeId, count);
    Crossing::Test::fuzzAttachment<ThingKey, std::set<ThingKey>>(
        db, Attachments::Thing::related::runtimeId, count);
    Crossing::Test::fuzzAttachment<ThingKey, Scalars>(
        db, Attachments::Thing::scalars::runtimeId, count);
}

} // namespace Core