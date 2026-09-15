// ModelA — l'implémentation, qui est cinq renvois par attachment.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "ModelA_Database.hpp"

#include "ModelA_Attachments.hpp"
#include "ModelA_Codec.hpp"

#include "Topology_Db.hpp"

namespace ModelA::Database::Material::colour {

namespace {
auto const & attachment() { return ModelA::Attachments::Material::colour::runtimeId; }
}

std::set<MaterialKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Topology::Db::keys<MaterialKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, MaterialKey const & key) {
    return Topology::Db::has(db, attachment(), key);
}

std::optional<Colour> get(std::shared_ptr<Viper::Database const> const & db, MaterialKey const & key) {
    return Topology::Db::get<Colour>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, MaterialKey const & key, Colour const & document) {
    return Topology::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, MaterialKey const & key) {
    return Topology::Db::del(db, attachment(), key);
}

} // namespace ModelA::Database::Material::colour