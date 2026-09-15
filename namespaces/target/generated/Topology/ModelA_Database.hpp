// unité ModelA — ses attachments, vus depuis une base de données.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#ifndef ModelA_Database_hpp
#define ModelA_Database_hpp

#include "ModelA_Data.hpp"

#include "Viper_Database.hpp"

#include <optional>
#include <set>

namespace ModelA::Database::Material::colour {

std::set<MaterialKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, MaterialKey const & key);
std::optional<Colour> get(std::shared_ptr<Viper::Database const> const & db, MaterialKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, MaterialKey const & key, Colour const & document);
bool del(std::shared_ptr<Viper::Database> const & db, MaterialKey const & key);

} // namespace ModelA::Database::Material::colour

#endif