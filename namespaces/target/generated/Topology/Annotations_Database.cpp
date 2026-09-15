// Annotations — l'implémentation, qui est cinq renvois par attachment.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "Annotations_Database.hpp"

#include "Annotations_Attachments.hpp"
#include "Annotations_Codec.hpp"
#include "ModelB_Codec.hpp"
#include "ModelA_Codec.hpp"

#include "Topology_Db.hpp"

namespace Annotations::Database::ModelA_Material::note {

namespace {
auto const & attachment() { return Annotations::Attachments::ModelA_Material::note::runtimeId; }
}

std::set<ModelA::MaterialKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Topology::Db::keys<ModelA::MaterialKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ModelA::MaterialKey const & key) {
    return Topology::Db::has(db, attachment(), key);
}

std::optional<std::string> get(std::shared_ptr<Viper::Database const> const & db, ModelA::MaterialKey const & key) {
    return Topology::Db::get<std::string>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ModelA::MaterialKey const & key, std::string const & document) {
    return Topology::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ModelA::MaterialKey const & key) {
    return Topology::Db::del(db, attachment(), key);
}

} // namespace Annotations::Database::ModelA_Material::note

namespace Annotations::Database::ModelB_Material::note {

namespace {
auto const & attachment() { return Annotations::Attachments::ModelB_Material::note::runtimeId; }
}

std::set<ModelB::MaterialKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Topology::Db::keys<ModelB::MaterialKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ModelB::MaterialKey const & key) {
    return Topology::Db::has(db, attachment(), key);
}

std::optional<std::string> get(std::shared_ptr<Viper::Database const> const & db, ModelB::MaterialKey const & key) {
    return Topology::Db::get<std::string>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ModelB::MaterialKey const & key, std::string const & document) {
    return Topology::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ModelB::MaterialKey const & key) {
    return Topology::Db::del(db, attachment(), key);
}

} // namespace Annotations::Database::ModelB_Material::note