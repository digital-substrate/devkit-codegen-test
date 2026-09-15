// unité Core — l'implémentation, et elle est la même huit fois.
//
// UNE LIGNE PAR OPÉRATION, ET LE CHEMIN EST LA SEULE VARIABLE. Chaque corps encode la clé,
// encode la valeur, et appelle l'opération du runtime à une adresse -- la racine quand le
// document est l'agrégat, celle du champ quand il en contient un. C'est ce qui rend les
// deux niveaux identiques à écrire.
//
// LE CAST N'EST PAS UNE FORMALITÉ. Le runtime veut un `ValueSet` là où le générique rend
// une `Value` : c'est la seule chose que le modèle sait et que le type C++ ne dit pas.

#include "Core_Attachments.hpp"

#include "Core_Codec.hpp"
#include "Core_Fields.hpp"
#include "Core_Model.hpp"

#include "Crossing_Codec.hpp"

#include "Viper_Attachment.hpp"
#include "Viper_Definitions.hpp"
#include "Viper_Path.hpp"
#include "Viper_Values.hpp"

namespace Core::Attachments::Thing {

namespace {

std::shared_ptr<Viper::Attachment> attachment(Viper::UUId const & runtimeId) {
    return Crossing::Codec::definitions()->checkAttachment(runtimeId);
}

std::shared_ptr<Viper::ValueKey> encodeKey(ThingKey const & key) {
    return Viper::ValueKey::cast(Crossing::Codec::encode(key));
}

/// La racine : l'adresse du document lui-même.
std::shared_ptr<Viper::Path const> root() { return Viper::Path::make(); }

} // namespace

// ── related : le document est un ensemble ──

Viper::UUId const related::runtimeId{Viper::UUId::parse("00000000-0000-0000-0000-000000000000")};

void related::union_(Viper::AttachmentMutating & mutating, ThingKey const & key,
                     std::set<ThingKey> const & value) {
    mutating.unionInSet(attachment(runtimeId), encodeKey(key), root(),
                        Viper::ValueSet::cast(Crossing::Codec::encode(value)));
}

void related::subtract(Viper::AttachmentMutating & mutating, ThingKey const & key,
                       std::set<ThingKey> const & value) {
    mutating.subtractInSet(attachment(runtimeId), encodeKey(key), root(),
                           Viper::ValueSet::cast(Crossing::Codec::encode(value)));
}

// ── palette : le document est une map ──

Viper::UUId const palette::runtimeId{Viper::UUId::parse("00000000-0000-0000-0000-000000000001")};

void palette::union_(Viper::AttachmentMutating & mutating, ThingKey const & key,
                     std::map<ThingKey, Colour> const & value) {
    mutating.unionInMap(attachment(runtimeId), encodeKey(key), root(),
                        Viper::ValueMap::cast(Crossing::Codec::encode(value)));
}

void palette::subtract(Viper::AttachmentMutating & mutating, ThingKey const & key,
                       std::set<ThingKey> const & value) {
    mutating.subtractInMap(attachment(runtimeId), encodeKey(key), root(),
                           Viper::ValueSet::cast(Crossing::Codec::encode(value)));
}

void palette::update(Viper::AttachmentMutating & mutating, ThingKey const & key,
                     std::map<ThingKey, Colour> const & value) {
    mutating.updateInMap(attachment(runtimeId), encodeKey(key), root(),
                         Viper::ValueMap::cast(Crossing::Codec::encode(value)));
}

// ── history : le document est un xarray ──

Viper::UUId const history::runtimeId{Viper::UUId::parse("00000000-0000-0000-0000-000000000002")};

void history::insert(Viper::AttachmentMutating & mutating, ThingKey const & key,
                     Viper::UUId const & beforePosition, Viper::UUId const & newPosition,
                     Colour const & value) {
    mutating.insertInXArray(attachment(runtimeId), encodeKey(key), root(),
                            beforePosition, newPosition, Crossing::Codec::encode(value));
}

void history::update(Viper::AttachmentMutating & mutating, ThingKey const & key,
                     Viper::UUId const & position, Colour const & value) {
    mutating.updateInXArray(attachment(runtimeId), encodeKey(key), root(),
                            position, Crossing::Codec::encode(value));
}

void history::remove(Viper::AttachmentMutating & mutating, ThingKey const & key,
                     Viper::UUId const & position) {
    mutating.removeInXArray(attachment(runtimeId), encodeKey(key), root(), position);
}

// ── bag : les mêmes, à l'adresse d'un champ ──
//
// Le seul changement est l'adresse. La couche 2 sert ici, et c'est son second usage après
// le setter par champ scalaire.

Viper::UUId const bag::runtimeId{Viper::UUId::parse("00000000-0000-0000-0000-000000000003")};

void bag::unionMembers(Viper::AttachmentMutating & mutating, ThingKey const & key,
                       std::set<ThingKey> const & value) {
    mutating.unionInSet(attachment(runtimeId), encodeKey(key), Fields::Bag::membersPath(),
                        Viper::ValueSet::cast(Crossing::Codec::encode(value)));
}

void bag::subtractMembers(Viper::AttachmentMutating & mutating, ThingKey const & key,
                          std::set<ThingKey> const & value) {
    mutating.subtractInSet(attachment(runtimeId), encodeKey(key), Fields::Bag::membersPath(),
                           Viper::ValueSet::cast(Crossing::Codec::encode(value)));
}

void bag::unionTints(Viper::AttachmentMutating & mutating, ThingKey const & key,
                     std::map<ThingKey, Colour> const & value) {
    mutating.unionInMap(attachment(runtimeId), encodeKey(key), Fields::Bag::tintsPath(),
                        Viper::ValueMap::cast(Crossing::Codec::encode(value)));
}

void bag::subtractTints(Viper::AttachmentMutating & mutating, ThingKey const & key,
                        std::set<ThingKey> const & value) {
    mutating.subtractInMap(attachment(runtimeId), encodeKey(key), Fields::Bag::tintsPath(),
                           Viper::ValueSet::cast(Crossing::Codec::encode(value)));
}

void bag::updateTints(Viper::AttachmentMutating & mutating, ThingKey const & key,
                      std::map<ThingKey, Colour> const & value) {
    mutating.updateInMap(attachment(runtimeId), encodeKey(key), Fields::Bag::tintsPath(),
                         Viper::ValueMap::cast(Crossing::Codec::encode(value)));
}

void bag::insertTrail(Viper::AttachmentMutating & mutating, ThingKey const & key,
                      Viper::UUId const & beforePosition, Viper::UUId const & newPosition,
                      Colour const & value) {
    mutating.insertInXArray(attachment(runtimeId), encodeKey(key), Fields::Bag::trailPath(),
                            beforePosition, newPosition, Crossing::Codec::encode(value));
}

void bag::updateTrail(Viper::AttachmentMutating & mutating, ThingKey const & key,
                      Viper::UUId const & position, Colour const & value) {
    mutating.updateInXArray(attachment(runtimeId), encodeKey(key), Fields::Bag::trailPath(),
                            position, Crossing::Codec::encode(value));
}

void bag::removeTrail(Viper::AttachmentMutating & mutating, ThingKey const & key,
                      Viper::UUId const & position) {
    mutating.removeInXArray(attachment(runtimeId), encodeKey(key), Fields::Bag::trailPath(), position);
}

} // namespace Core::Attachments::Thing
