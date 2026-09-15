// Annotations — l'épreuve de ses types.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "Annotations_Test.hpp"

#include "Annotations_Attachments.hpp"
#include "Annotations_Codec.hpp"
#include "Annotations_Database.hpp"
#include "Annotations_Model.hpp"
#include "ModelB_Codec.hpp"
#include "ModelA_Codec.hpp"
#include "ModelB_Model.hpp"
#include "ModelA_Model.hpp"

#include "Topology_Test.hpp"

namespace Annotations {

void test() {
}

void testDatabase(std::shared_ptr<Viper::Database> const & db) {
    Topology::Test::roundTripAttachment<ModelA::MaterialKey, std::string>(
        db, Attachments::ModelA_Material::note::runtimeId);
    Topology::Test::roundTripAttachment<ModelB::MaterialKey, std::string>(
        db, Attachments::ModelB_Material::note::runtimeId);
}

} // namespace Annotations