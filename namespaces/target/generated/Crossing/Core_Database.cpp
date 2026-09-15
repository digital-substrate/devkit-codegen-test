// Core — l'implémentation, qui est cinq renvois par attachment.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

#include "Core_Database.hpp"

#include "Core_Attachments.hpp"
#include "Core_Codec.hpp"

#include "Crossing_Db.hpp"

namespace Core::Database::Thing::colour {

namespace {
auto const & attachment() { return Core::Attachments::Thing::colour::runtimeId; }
}

std::set<ThingKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Crossing::Db::keys<ThingKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ThingKey const & key) {
    return Crossing::Db::has(db, attachment(), key);
}

std::optional<Colour> get(std::shared_ptr<Viper::Database const> const & db, ThingKey const & key) {
    return Crossing::Db::get<Colour>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ThingKey const & key, Colour const & document) {
    return Crossing::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ThingKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

} // namespace Core::Database::Thing::colour

namespace Core::Database::Thing::scalars {

namespace {
auto const & attachment() { return Core::Attachments::Thing::scalars::runtimeId; }
}

std::set<ThingKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Crossing::Db::keys<ThingKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, ThingKey const & key) {
    return Crossing::Db::has(db, attachment(), key);
}

std::optional<Scalars> get(std::shared_ptr<Viper::Database const> const & db, ThingKey const & key) {
    return Crossing::Db::get<Scalars>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, ThingKey const & key, Scalars const & document) {
    return Crossing::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, ThingKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

} // namespace Core::Database::Thing::scalars