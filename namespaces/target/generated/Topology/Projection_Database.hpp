// Projection — ses attachments, vus depuis une base de données.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#ifndef Projection_Database_hpp
#define Projection_Database_hpp

#include "Projection_Data.hpp"
#include "ModelB_Data.hpp"
#include "ModelC_Data.hpp"
#include "ModelA_Data.hpp"

#include "Viper_Database.hpp"

#include <optional>
#include <set>

/** A container shape spanning two namespaces: one typeSuffix, owned by neither. */
namespace Projection::Database::Link::mapping {

std::set<LinkKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, LinkKey const & key);
std::optional<std::map<ModelA::MaterialKey, ModelB::MaterialKey>> get(std::shared_ptr<Viper::Database const> const & db, LinkKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, LinkKey const & key, std::map<ModelA::MaterialKey, ModelB::MaterialKey> const & document);
bool del(std::shared_ptr<Viper::Database> const & db, LinkKey const & key);

} // namespace Projection::Database::Link::mapping

/** The only reference to ModelC anywhere: an attachment document type. */
namespace Projection::Database::Link::marker {

std::set<LinkKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, LinkKey const & key);
std::optional<ModelC::MarkerKey> get(std::shared_ptr<Viper::Database const> const & db, LinkKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, LinkKey const & key, ModelC::MarkerKey const & document);
bool del(std::shared_ptr<Viper::Database> const & db, LinkKey const & key);

} // namespace Projection::Database::Link::marker

namespace Projection::Database::Link::pair {

std::set<LinkKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, LinkKey const & key);
std::optional<Pair> get(std::shared_ptr<Viper::Database const> const & db, LinkKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, LinkKey const & key, Pair const & document);
bool del(std::shared_ptr<Viper::Database> const & db, LinkKey const & key);

} // namespace Projection::Database::Link::pair

#endif