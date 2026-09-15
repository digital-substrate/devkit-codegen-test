// Annotations — ses attachments, vus depuis une base de données.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#ifndef Annotations_Database_hpp
#define Annotations_Database_hpp

#include "Annotations_Data.hpp"
#include "ModelB_Data.hpp"
#include "ModelA_Data.hpp"

#include "Viper_Database.hpp"

#include <optional>
#include <set>

/** A note carried by a material this namespace does not own. */
namespace Annotations::Database::ModelA_Material::note {

std::set<ModelA::MaterialKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ModelA::MaterialKey const & key);
std::optional<std::string> get(std::shared_ptr<Viper::Database const> const & db, ModelA::MaterialKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ModelA::MaterialKey const & key, std::string const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ModelA::MaterialKey const & key);

} // namespace Annotations::Database::ModelA_Material::note

/** The same attachment name, on the same-named concept of another namespace. The
generator qualifies both scopes rather than colliding -- but only once this second
one exists, so adding it renames the first. */
namespace Annotations::Database::ModelB_Material::note {

std::set<ModelB::MaterialKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ModelB::MaterialKey const & key);
std::optional<std::string> get(std::shared_ptr<Viper::Database const> const & db, ModelB::MaterialKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ModelB::MaterialKey const & key, std::string const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ModelB::MaterialKey const & key);

} // namespace Annotations::Database::ModelB_Material::note

#endif