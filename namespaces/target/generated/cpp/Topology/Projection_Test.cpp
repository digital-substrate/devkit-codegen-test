// unité Projection — l'épreuve de ses types.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "Projection_Test.hpp"

#include "Projection_Attachments.hpp"
#include "Projection_Codec.hpp"
#include "Projection_Model.hpp"
#include "ModelB_Codec.hpp"
#include "ModelC_Codec.hpp"
#include "ModelA_Codec.hpp"
#include "ModelB_Model.hpp"
#include "ModelC_Model.hpp"
#include "ModelA_Model.hpp"

#include "Topology_Test.hpp"

namespace Projection {

void test() {
    Topology::Test::roundTrip<LinkKey>();
    Topology::Test::roundTrip<DerivedMaterialKey>();
    Topology::Test::roundTrip<Pair>();
}

void testDatabase(std::shared_ptr<Viper::Database> const & db) {
    Topology::Test::roundTripAttachment<LinkKey, std::map<ModelA::MaterialKey, ModelB::MaterialKey>>(
        db, Attachments::Link::mapping::descriptor());
    Topology::Test::roundTripAttachment<LinkKey, ModelC::MarkerKey>(
        db, Attachments::Link::marker::descriptor());
    Topology::Test::roundTripAttachment<LinkKey, Pair>(
        db, Attachments::Link::pair::descriptor());
}

void fuzzDatabase(std::shared_ptr<Viper::Database> const & db, std::size_t count) {
    Topology::Test::fuzzAttachment<LinkKey, std::map<ModelA::MaterialKey, ModelB::MaterialKey>>(
        db, Attachments::Link::mapping::descriptor(), count);
    Topology::Test::fuzzAttachment<LinkKey, ModelC::MarkerKey>(
        db, Attachments::Link::marker::descriptor(), count);
    Topology::Test::fuzzAttachment<LinkKey, Pair>(
        db, Attachments::Link::pair::descriptor(), count);
}

} // namespace Projection