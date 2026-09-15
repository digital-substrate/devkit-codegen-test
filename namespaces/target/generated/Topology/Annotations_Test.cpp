// unité Annotations — l'épreuve de ses types.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "Annotations_Test.hpp"

#include "Annotations_Attachments.hpp"
#include "Annotations_Codec.hpp"
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
        db, Attachments::ModelA_Material::note::descriptor());
    Topology::Test::roundTripAttachment<ModelB::MaterialKey, std::string>(
        db, Attachments::ModelB_Material::note::descriptor());
}

void fuzzDatabase(std::shared_ptr<Viper::Database> const & db, std::size_t count) {
    Topology::Test::fuzzAttachment<ModelA::MaterialKey, std::string>(
        db, Attachments::ModelA_Material::note::descriptor(), count);
    Topology::Test::fuzzAttachment<ModelB::MaterialKey, std::string>(
        db, Attachments::ModelB_Material::note::descriptor(), count);
}

} // namespace Annotations