// unité ModelB — l'épreuve de ses types.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "ModelB_Test.hpp"

#include "ModelB_Attachments.hpp"
#include "ModelB_Codec.hpp"
#include "ModelB_Database.hpp"
#include "ModelB_Model.hpp"

#include "Topology_Test.hpp"

namespace ModelB {

void test() {
    Topology::Test::roundTrip<MaterialKey>();
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

} // namespace ModelB