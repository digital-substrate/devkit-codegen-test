// Woven — ses attachments, vus depuis une base de données.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

#ifndef Woven_Database_hpp
#define Woven_Database_hpp

#include "Woven_Data.hpp"
#include "Parts_Data.hpp"
#include "Core_Data.hpp"

#include "Viper_Database.hpp"

#include <optional>
#include <set>

namespace Woven::Database::Core_Thing::mark {

std::set<Core::ThingKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, Core::ThingKey const & key);
std::optional<Parts::Colour> get(std::shared_ptr<Viper::Database const> const & db, Core::ThingKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, Core::ThingKey const & key, Parts::Colour const & document);
bool del(std::shared_ptr<Viper::Database> const & db, Core::ThingKey const & key);

} // namespace Woven::Database::Core_Thing::mark

namespace Woven::Database::Knot::docAnyConceptKey {

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
std::optional<::Crossing::AnyConceptKey> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, ::Crossing::AnyConceptKey const & document);
bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key);

} // namespace Woven::Database::Knot::docAnyConceptKey

namespace Woven::Database::Knot::docColour {

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
std::optional<Core::Colour> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, Core::Colour const & document);
bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key);

} // namespace Woven::Database::Knot::docColour

namespace Woven::Database::Knot::docComposites {

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
std::optional<Composites> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, Composites const & document);
bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key);

} // namespace Woven::Database::Knot::docComposites

namespace Woven::Database::Knot::docGrade {

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
std::optional<Core::Grade> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, Core::Grade const & document);
bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key);

} // namespace Woven::Database::Knot::docGrade

namespace Woven::Database::Knot::docKlubKey {

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
std::optional<Core::KlubKey> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, Core::KlubKey const & document);
bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key);

} // namespace Woven::Database::Knot::docKlubKey

namespace Woven::Database::Knot::docMapEnum {

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
std::optional<std::map<Core::Grade, Parts::Colour>> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, std::map<Core::Grade, Parts::Colour> const & document);
bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key);

} // namespace Woven::Database::Knot::docMapEnum

namespace Woven::Database::Knot::docMapKeys {

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
std::optional<std::map<Core::ThingKey, Parts::ThingKey>> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, std::map<Core::ThingKey, Parts::ThingKey> const & document);
bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key);

} // namespace Woven::Database::Knot::docMapKeys

namespace Woven::Database::Knot::docOptional {

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
std::optional<std::optional<Core::ThingKey>> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, std::optional<Core::ThingKey> const & document);
bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key);

} // namespace Woven::Database::Knot::docOptional

namespace Woven::Database::Knot::docOtherColour {

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
std::optional<Parts::Colour> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, Parts::Colour const & document);
bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key);

} // namespace Woven::Database::Knot::docOtherColour

namespace Woven::Database::Knot::docSet {

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
std::optional<std::set<Core::ThingKey>> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, std::set<Core::ThingKey> const & document);
bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key);

} // namespace Woven::Database::Knot::docSet

namespace Woven::Database::Knot::docThingKey {

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
std::optional<Core::ThingKey> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, Core::ThingKey const & document);
bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key);

} // namespace Woven::Database::Knot::docThingKey

namespace Woven::Database::Knot::docTuple {

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
std::optional<std::tuple<Core::Colour, Parts::Colour>> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, std::tuple<Core::Colour, Parts::Colour> const & document);
bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key);

} // namespace Woven::Database::Knot::docTuple

namespace Woven::Database::Knot::docVariant {

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
std::optional<std::variant<Core::Colour, Parts::Colour>> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, std::variant<Core::Colour, Parts::Colour> const & document);
bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key);

} // namespace Woven::Database::Knot::docVariant

namespace Woven::Database::Knot::docVector {

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
std::optional<std::vector<Parts::Colour>> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, std::vector<Parts::Colour> const & document);
bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key);

} // namespace Woven::Database::Knot::docVector

namespace Woven::Database::Knot::docXArray {

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
std::optional<Viper::XArray<Core::Colour>> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, Viper::XArray<Core::Colour> const & document);
bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key);

} // namespace Woven::Database::Knot::docXArray

namespace Woven::Database::Parts_Thing::mark {

std::set<Parts::ThingKey> keys(std::shared_ptr<Viper::Database const> const & db);
bool has(std::shared_ptr<Viper::Database const> const & db, Parts::ThingKey const & key);
std::optional<Core::Colour> get(std::shared_ptr<Viper::Database const> const & db, Parts::ThingKey const & key);
bool set(std::shared_ptr<Viper::Database> const & db, Parts::ThingKey const & key, Core::Colour const & document);
bool del(std::shared_ptr<Viper::Database> const & db, Parts::ThingKey const & key);

} // namespace Woven::Database::Parts_Thing::mark

#endif