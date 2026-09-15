// unité Demo — l'épreuve de ses types.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/service/Service.dsm.json by kibo-2.0.0.jar

#include "Demo_Test.hpp"

#include "Demo_Attachments.hpp"
#include "Demo_Codec.hpp"
#include "Demo_Model.hpp"

#include "Service_Test.hpp"

namespace Demo {

void test() {
    Service::Test::roundTrip<PlayerKey>();
    Service::Test::roundTrip<Level>();
    Service::Test::roundTrip<PlayerProperty>();
    Service::Test::roundTrip<Vector3>();
}

void testDatabase(std::shared_ptr<Viper::Database> const & db) {
    Service::Test::roundTripAttachment<PlayerKey, PlayerProperty>(
        db, Attachments::Player::property::descriptor());
}

void fuzzDatabase(std::shared_ptr<Viper::Database> const & db, std::size_t count) {
    Service::Test::fuzzAttachment<PlayerKey, PlayerProperty>(
        db, Attachments::Player::property::descriptor(), count);
}

} // namespace Demo