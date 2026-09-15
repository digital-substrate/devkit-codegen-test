// unité Core — ses attachments, vus depuis une base de données.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

#ifndef Core_Database_hpp
#define Core_Database_hpp

#include "Core_Data.hpp"

#include "Viper_Database.hpp"

#include <optional>
#include <set>

namespace Core::Database::Thing::bag {

std::set<ThingKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ThingKey const & key);
std::optional<Bag> get(std::shared_ptr<Viper::Database const> const & db, ThingKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ThingKey const & key, Bag const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ThingKey const & key);

} // namespace Core::Database::Thing::bag

namespace Core::Database::Thing::colour {

std::set<ThingKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ThingKey const & key);
std::optional<Colour> get(std::shared_ptr<Viper::Database const> const & db, ThingKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ThingKey const & key, Colour const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ThingKey const & key);

} // namespace Core::Database::Thing::colour

namespace Core::Database::Thing::history {

std::set<ThingKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ThingKey const & key);
std::optional<Viper::XArray<Colour>> get(std::shared_ptr<Viper::Database const> const & db, ThingKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ThingKey const & key, Viper::XArray<Colour> const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ThingKey const & key);

} // namespace Core::Database::Thing::history

namespace Core::Database::Thing::palette {

std::set<ThingKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ThingKey const & key);
std::optional<std::map<ThingKey, Colour>> get(std::shared_ptr<Viper::Database const> const & db, ThingKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ThingKey const & key, std::map<ThingKey, Colour> const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ThingKey const & key);

} // namespace Core::Database::Thing::palette

/** Un document qui EST un agrégat : ses opérations ne sont pas celles d'un document
ordinaire, puisqu'on peut y ajouter et en retirer sans l'écraser. */
namespace Core::Database::Thing::related {

std::set<ThingKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ThingKey const & key);
std::optional<std::set<ThingKey>> get(std::shared_ptr<Viper::Database const> const & db, ThingKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ThingKey const & key, std::set<ThingKey> const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ThingKey const & key);

} // namespace Core::Database::Thing::related

namespace Core::Database::Thing::scalars {

std::set<ThingKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, ThingKey const & key);
std::optional<Scalars> get(std::shared_ptr<Viper::Database const> const & db, ThingKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, ThingKey const & key, Scalars const & document);
bool del(std::shared_ptr<Viper::Database> const & db, ThingKey const & key);

} // namespace Core::Database::Thing::scalars

#endif