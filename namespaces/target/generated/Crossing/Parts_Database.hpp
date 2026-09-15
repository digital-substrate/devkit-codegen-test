// Parts — ses attachments, vus depuis une base de données.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

#ifndef Parts_Database_hpp
#define Parts_Database_hpp

#include "Parts_Data.hpp"

#include "Viper_Database.hpp"

#include <optional>
#include <set>

namespace Parts::Database::Thing::colour {

std::set<ThingKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ThingKey const & key);
std::optional<Colour> get(std::shared_ptr<Viper::Database const> const & db, ThingKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ThingKey const & key, Colour const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ThingKey const & key);

} // namespace Parts::Database::Thing::colour

#endif