// Parts — l'épreuve de ses types.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

#include "Parts_Test.hpp"

#include "Parts_Attachments.hpp"
#include "Parts_Codec.hpp"
#include "Parts_Database.hpp"
#include "Parts_Model.hpp"

#include "Crossing_Test.hpp"

namespace Parts {

void test() {
    Crossing::Test::roundTrip<ThingKey>();
    Crossing::Test::roundTrip<Grade>();
    Crossing::Test::roundTrip<Colour>();
}

void testDatabase(std::shared_ptr<Viper::Database> const & db) {
    Crossing::Test::roundTripAttachment<ThingKey, Colour>(
        db, Attachments::Thing::colour::runtimeId);
}

} // namespace Parts