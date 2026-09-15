// Core — l'épreuve de ses types.
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
    Crossing::Test::roundTrip<Colour>();
    Crossing::Test::roundTrip<Defaults>();
    Crossing::Test::roundTrip<Scalars>();
    Crossing::Test::roundTrip<Single>();
}

void testDatabase(std::shared_ptr<Viper::Database> const & db) {
    Crossing::Test::roundTripAttachment<ThingKey, Colour>(
        db, Attachments::Thing::colour::runtimeId);
    Crossing::Test::roundTripAttachment<ThingKey, Scalars>(
        db, Attachments::Thing::scalars::runtimeId);
}

} // namespace Core