// Woven — l'implémentation, qui est cinq renvois par attachment.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

#include "Woven_Database.hpp"

#include "Woven_Attachments.hpp"
#include "Woven_Codec.hpp"
#include "Parts_Codec.hpp"
#include "Core_Codec.hpp"

#include "Crossing_Db.hpp"

namespace Woven::Database::Core_Thing::mark {

namespace {
auto const & attachment() { return Woven::Attachments::Core_Thing::mark::runtimeId; }
}

std::set<Core::ThingKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Crossing::Db::keys<Core::ThingKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, Core::ThingKey const & key) {
    return Crossing::Db::has(db, attachment(), key);
}

std::optional<Parts::Colour> get(std::shared_ptr<Viper::Database const> const & db, Core::ThingKey const & key) {
    return Crossing::Db::get<Parts::Colour>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, Core::ThingKey const & key, Parts::Colour const & document) {
    return Crossing::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, Core::ThingKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

} // namespace Woven::Database::Core_Thing::mark

namespace Woven::Database::Knot::docAnyConceptKey {

namespace {
auto const & attachment() { return Woven::Attachments::Knot::docAnyConceptKey::runtimeId; }
}

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Crossing::Db::keys<KnotKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::has(db, attachment(), key);
}

std::optional<::Crossing::AnyConceptKey> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::get<::Crossing::AnyConceptKey>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, ::Crossing::AnyConceptKey const & document) {
    return Crossing::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

} // namespace Woven::Database::Knot::docAnyConceptKey

namespace Woven::Database::Knot::docColour {

namespace {
auto const & attachment() { return Woven::Attachments::Knot::docColour::runtimeId; }
}

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Crossing::Db::keys<KnotKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::has(db, attachment(), key);
}

std::optional<Core::Colour> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::get<Core::Colour>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, Core::Colour const & document) {
    return Crossing::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

} // namespace Woven::Database::Knot::docColour

namespace Woven::Database::Knot::docComposites {

namespace {
auto const & attachment() { return Woven::Attachments::Knot::docComposites::runtimeId; }
}

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Crossing::Db::keys<KnotKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::has(db, attachment(), key);
}

std::optional<Composites> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::get<Composites>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, Composites const & document) {
    return Crossing::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

} // namespace Woven::Database::Knot::docComposites

namespace Woven::Database::Knot::docGrade {

namespace {
auto const & attachment() { return Woven::Attachments::Knot::docGrade::runtimeId; }
}

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Crossing::Db::keys<KnotKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::has(db, attachment(), key);
}

std::optional<Core::Grade> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::get<Core::Grade>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, Core::Grade const & document) {
    return Crossing::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

} // namespace Woven::Database::Knot::docGrade

namespace Woven::Database::Knot::docKlubKey {

namespace {
auto const & attachment() { return Woven::Attachments::Knot::docKlubKey::runtimeId; }
}

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Crossing::Db::keys<KnotKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::has(db, attachment(), key);
}

std::optional<Core::KlubKey> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::get<Core::KlubKey>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, Core::KlubKey const & document) {
    return Crossing::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

} // namespace Woven::Database::Knot::docKlubKey

namespace Woven::Database::Knot::docMapEnum {

namespace {
auto const & attachment() { return Woven::Attachments::Knot::docMapEnum::runtimeId; }
}

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Crossing::Db::keys<KnotKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::has(db, attachment(), key);
}

std::optional<std::map<Core::Grade, Parts::Colour>> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::get<std::map<Core::Grade, Parts::Colour>>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, std::map<Core::Grade, Parts::Colour> const & document) {
    return Crossing::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

} // namespace Woven::Database::Knot::docMapEnum

namespace Woven::Database::Knot::docMapKeys {

namespace {
auto const & attachment() { return Woven::Attachments::Knot::docMapKeys::runtimeId; }
}

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Crossing::Db::keys<KnotKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::has(db, attachment(), key);
}

std::optional<std::map<Core::ThingKey, Parts::ThingKey>> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::get<std::map<Core::ThingKey, Parts::ThingKey>>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, std::map<Core::ThingKey, Parts::ThingKey> const & document) {
    return Crossing::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

} // namespace Woven::Database::Knot::docMapKeys

namespace Woven::Database::Knot::docOptional {

namespace {
auto const & attachment() { return Woven::Attachments::Knot::docOptional::runtimeId; }
}

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Crossing::Db::keys<KnotKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::has(db, attachment(), key);
}

std::optional<std::optional<Core::ThingKey>> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::get<std::optional<Core::ThingKey>>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, std::optional<Core::ThingKey> const & document) {
    return Crossing::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

} // namespace Woven::Database::Knot::docOptional

namespace Woven::Database::Knot::docOtherColour {

namespace {
auto const & attachment() { return Woven::Attachments::Knot::docOtherColour::runtimeId; }
}

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Crossing::Db::keys<KnotKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::has(db, attachment(), key);
}

std::optional<Parts::Colour> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::get<Parts::Colour>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, Parts::Colour const & document) {
    return Crossing::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

} // namespace Woven::Database::Knot::docOtherColour

namespace Woven::Database::Knot::docSet {

namespace {
auto const & attachment() { return Woven::Attachments::Knot::docSet::runtimeId; }
}

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Crossing::Db::keys<KnotKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::has(db, attachment(), key);
}

std::optional<std::set<Core::ThingKey>> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::get<std::set<Core::ThingKey>>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, std::set<Core::ThingKey> const & document) {
    return Crossing::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

} // namespace Woven::Database::Knot::docSet

namespace Woven::Database::Knot::docThingKey {

namespace {
auto const & attachment() { return Woven::Attachments::Knot::docThingKey::runtimeId; }
}

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Crossing::Db::keys<KnotKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::has(db, attachment(), key);
}

std::optional<Core::ThingKey> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::get<Core::ThingKey>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, Core::ThingKey const & document) {
    return Crossing::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

} // namespace Woven::Database::Knot::docThingKey

namespace Woven::Database::Knot::docTuple {

namespace {
auto const & attachment() { return Woven::Attachments::Knot::docTuple::runtimeId; }
}

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Crossing::Db::keys<KnotKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::has(db, attachment(), key);
}

std::optional<std::tuple<Core::Colour, Parts::Colour>> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::get<std::tuple<Core::Colour, Parts::Colour>>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, std::tuple<Core::Colour, Parts::Colour> const & document) {
    return Crossing::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

} // namespace Woven::Database::Knot::docTuple

namespace Woven::Database::Knot::docVariant {

namespace {
auto const & attachment() { return Woven::Attachments::Knot::docVariant::runtimeId; }
}

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Crossing::Db::keys<KnotKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::has(db, attachment(), key);
}

std::optional<std::variant<Core::Colour, Parts::Colour>> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::get<std::variant<Core::Colour, Parts::Colour>>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, std::variant<Core::Colour, Parts::Colour> const & document) {
    return Crossing::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

} // namespace Woven::Database::Knot::docVariant

namespace Woven::Database::Knot::docVector {

namespace {
auto const & attachment() { return Woven::Attachments::Knot::docVector::runtimeId; }
}

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Crossing::Db::keys<KnotKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::has(db, attachment(), key);
}

std::optional<std::vector<Parts::Colour>> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::get<std::vector<Parts::Colour>>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, std::vector<Parts::Colour> const & document) {
    return Crossing::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

} // namespace Woven::Database::Knot::docVector

namespace Woven::Database::Knot::docXArray {

namespace {
auto const & attachment() { return Woven::Attachments::Knot::docXArray::runtimeId; }
}

std::set<KnotKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Crossing::Db::keys<KnotKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::has(db, attachment(), key);
}

std::optional<Viper::XArray<Core::Colour>> get(std::shared_ptr<Viper::Database const> const & db, KnotKey const & key) {
    return Crossing::Db::get<Viper::XArray<Core::Colour>>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, KnotKey const & key, Viper::XArray<Core::Colour> const & document) {
    return Crossing::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, KnotKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

} // namespace Woven::Database::Knot::docXArray

namespace Woven::Database::Parts_Thing::mark {

namespace {
auto const & attachment() { return Woven::Attachments::Parts_Thing::mark::runtimeId; }
}

std::set<Parts::ThingKey> keys(std::shared_ptr<Viper::Database const> const & db) {
    return Crossing::Db::keys<Parts::ThingKey>(db, attachment());
}

bool has(std::shared_ptr<Viper::Database const> const & db, Parts::ThingKey const & key) {
    return Crossing::Db::has(db, attachment(), key);
}

std::optional<Core::Colour> get(std::shared_ptr<Viper::Database const> const & db, Parts::ThingKey const & key) {
    return Crossing::Db::get<Core::Colour>(db, attachment(), key);
}

bool set(std::shared_ptr<Viper::Database> const & db, Parts::ThingKey const & key, Core::Colour const & document) {
    return Crossing::Db::set(db, attachment(), key, document);
}

bool del(std::shared_ptr<Viper::Database> const & db, Parts::ThingKey const & key) {
    return Crossing::Db::del(db, attachment(), key);
}

} // namespace Woven::Database::Parts_Thing::mark