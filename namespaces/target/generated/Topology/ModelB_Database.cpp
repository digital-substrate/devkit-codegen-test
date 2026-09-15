// unité ModelB — l'implémentation, qui est cinq renvois par attachment.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "ModelB_Database.hpp"

#include "ModelB_Attachments.hpp"
#include "ModelB_Codec.hpp"

#include "Topology_Db.hpp"

namespace ModelB::Database::Material::colour {

namespace {
auto const & attachment() { return ModelB::Attachments::Material::colour::runtimeId; }
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

} // namespace ModelB::Database::Material::colour