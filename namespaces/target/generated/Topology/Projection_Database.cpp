// unité Projection — l'implémentation, qui est cinq renvois par attachment.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "Projection_Database.hpp"

#include "Projection_Attachments.hpp"
#include "Projection_Codec.hpp"
#include "ModelB_Codec.hpp"
#include "ModelC_Codec.hpp"
#include "ModelA_Codec.hpp"

#include "Topology_Db.hpp"

namespace Projection::Database::Link::mapping {

namespace {
auto const & attachment() { return Projection::Attachments::Link::mapping::runtimeId; }
}

std::set<LinkKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Topology::Db::keys<LinkKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, LinkKey const & key) {
    return Topology::Db::has(db, attachment(), key);
}

std::optional<std::map<ModelA::MaterialKey, ModelB::MaterialKey>> get(std::shared_ptr<Viper::Database const> const & db, LinkKey const & key) {
    return Topology::Db::get<std::map<ModelA::MaterialKey, ModelB::MaterialKey>>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, LinkKey const & key, std::map<ModelA::MaterialKey, ModelB::MaterialKey> const & document) {
    return Topology::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, LinkKey const & key) {
    return Topology::Db::del(db, attachment(), key);
}

} // namespace Projection::Database::Link::mapping

namespace Projection::Database::Link::marker {

namespace {
auto const & attachment() { return Projection::Attachments::Link::marker::runtimeId; }
}

std::set<LinkKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Topology::Db::keys<LinkKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, LinkKey const & key) {
    return Topology::Db::has(db, attachment(), key);
}

std::optional<ModelC::MarkerKey> get(std::shared_ptr<Viper::Database const> const & db, LinkKey const & key) {
    return Topology::Db::get<ModelC::MarkerKey>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, LinkKey const & key, ModelC::MarkerKey const & document) {
    return Topology::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, LinkKey const & key) {
    return Topology::Db::del(db, attachment(), key);
}

} // namespace Projection::Database::Link::marker

namespace Projection::Database::Link::pair {

namespace {
auto const & attachment() { return Projection::Attachments::Link::pair::runtimeId; }
}

std::set<LinkKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Topology::Db::keys<LinkKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, LinkKey const & key) {
    return Topology::Db::has(db, attachment(), key);
}

std::optional<Pair> get(std::shared_ptr<Viper::Database const> const & db, LinkKey const & key) {
    return Topology::Db::get<Pair>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, LinkKey const & key, Pair const & document) {
    return Topology::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, LinkKey const & key) {
    return Topology::Db::del(db, attachment(), key);
}

} // namespace Projection::Database::Link::pair