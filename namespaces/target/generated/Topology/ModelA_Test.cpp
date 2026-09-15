// unité ModelA — l'épreuve de ses types.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "ModelA_Test.hpp"

#include "ModelA_Attachments.hpp"
#include "ModelA_Codec.hpp"
#include "ModelA_Database.hpp"
#include "ModelA_Model.hpp"

#include "Topology_Test.hpp"

namespace ModelA {

void test() {
    Topology::Test::roundTrip<MaterialKey>();
    Topology::Test::roundTrip<Finish>();
    Topology::Test::roundTrip<Colour>();
}

void testDatabase(std::shared_ptr<Viper::Database> const & db) {
    Topology::Test::roundTripAttachment<MaterialKey, Colour>(
        db, Attachments::Material::colour::runtimeId);
}

void fuzzDatabase(std::shared_ptr<Viper::Database> const & db, std::size_t count) {
    Topology::Test::fuzzAttachment<MaterialKey, Colour>(
        db, Attachments::Material::colour::runtimeId, count);
}

} // namespace ModelA