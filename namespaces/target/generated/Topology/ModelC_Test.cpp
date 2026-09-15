// unité ModelC — l'épreuve de ses types.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "ModelC_Test.hpp"

#include "ModelC_Attachments.hpp"
#include "ModelC_Codec.hpp"
#include "ModelC_Database.hpp"
#include "ModelC_Model.hpp"

#include "Topology_Test.hpp"

namespace ModelC {

void test() {
    Topology::Test::roundTrip<MarkerKey>();
}

void testDatabase(std::shared_ptr<Viper::Database> const & db) {
}

void fuzzDatabase(std::shared_ptr<Viper::Database> const & db, std::size_t count) {
}

} // namespace ModelC