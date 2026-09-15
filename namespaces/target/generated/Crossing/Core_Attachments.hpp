// unité Core — les données accrochées aux concepts qu'elle déclare.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar
//
// One scope per attachment, under the concept it is keyed on. The concept's own unit is
// part of the scope name whenever it is not this one: a namespace level cannot hold a
// qualified name, so `ModelA::Material` becomes `ModelA_Material` there -- and always,
// not only when two attachments would otherwise collide, so that adding one never
// renames another.

#ifndef Core_Attachments_hpp
#define Core_Attachments_hpp

#include "Core_Data.hpp"

#include "Viper_Attachment.hpp"
#include "Viper_AttachmentGetting.hpp"
#include "Viper_Database.hpp"
#include "Viper_AttachmentMutating.hpp"
#include "Viper_UUId.hpp"

#include <map>

#include <cstdint>
#include <optional>
#include <set>

namespace Core::Attachments::Thing::bag {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ThingKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting);

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ThingKey const & key);

std::optional<Bag> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ThingKey const & key);

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Bag const & value);

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Bag const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ThingKey const & key, Bag const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ThingKey const & key);

void setMembers(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::set<ThingKey> const & value);
void unionMembers(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::set<ThingKey> const & value);
void subtractMembers(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::set<ThingKey> const & value);
void setTints(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::map<ThingKey, Colour> const & value);
void unionTints(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::map<ThingKey, Colour> const & value);
void subtractTints(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::set<Core::ThingKey> const & value);
void updateTints(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::map<ThingKey, Colour> const & value);
void setTrail(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Viper::XArray<Colour> const & value);
void insertTrail(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Viper::UUId const & beforePosition, Viper::UUId const & newPosition, Core::Colour const & value);
void updateTrail(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Viper::UUId const & position, Core::Colour const & value);
void removeTrail(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Viper::UUId const & position);
} // namespace Core::Attachments::Thing::bag

namespace Core::Attachments::Thing::colour {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ThingKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting);

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ThingKey const & key);

std::optional<Colour> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ThingKey const & key);

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Colour const & value);

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Colour const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ThingKey const & key, Colour const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ThingKey const & key);

void setR(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::uint8_t value);

void setG(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::uint8_t value);

void setB(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::uint8_t value);

} // namespace Core::Attachments::Thing::colour

namespace Core::Attachments::Thing::history {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ThingKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting);

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ThingKey const & key);

std::optional<Viper::XArray<Colour>> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ThingKey const & key);

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Viper::XArray<Colour> const & value);

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Viper::XArray<Colour> const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ThingKey const & key, Viper::XArray<Colour> const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ThingKey const & key);

void insert(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Viper::UUId const & beforePosition, Viper::UUId const & newPosition, Core::Colour const & value);
void update(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Viper::UUId const & position, Core::Colour const & value);
void remove(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Viper::UUId const & position);

} // namespace Core::Attachments::Thing::history

namespace Core::Attachments::Thing::palette {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ThingKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting);

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ThingKey const & key);

std::optional<std::map<ThingKey, Colour>> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ThingKey const & key);

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::map<ThingKey, Colour> const & value);

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::map<ThingKey, Colour> const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ThingKey const & key, std::map<ThingKey, Colour> const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ThingKey const & key);

void union_(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::map<ThingKey, Colour> const & value);
void subtract(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::set<Core::ThingKey> const & value);
void update(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::map<ThingKey, Colour> const & value);

} // namespace Core::Attachments::Thing::palette

/** Un document qui EST un agrégat : ses opérations ne sont pas celles d'un document
ordinaire, puisqu'on peut y ajouter et en retirer sans l'écraser. */
namespace Core::Attachments::Thing::related {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ThingKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting);

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ThingKey const & key);

std::optional<std::set<ThingKey>> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ThingKey const & key);

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::set<ThingKey> const & value);

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::set<ThingKey> const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ThingKey const & key, std::set<ThingKey> const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ThingKey const & key);

void union_(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::set<ThingKey> const & value);
void subtract(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::set<ThingKey> const & value);

} // namespace Core::Attachments::Thing::related

namespace Core::Attachments::Thing::scalars {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ThingKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting);

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ThingKey const & key);

std::optional<Scalars> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ThingKey const & key);

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Scalars const & value);

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Scalars const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ThingKey const & key, Scalars const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ThingKey const & key);

void setF_bool(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, bool value);

void setF_uint8(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::uint8_t value);

void setF_uint16(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::uint16_t value);

void setF_uint32(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::uint32_t value);

void setF_uint64(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::uint64_t value);

void setF_int8(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::int8_t value);

void setF_int16(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::int16_t value);

void setF_int32(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::int32_t value);

void setF_int64(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::int64_t value);

void setF_float(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, float value);

void setF_double(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, double value);

void setF_blob_id(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Viper::BlobId const & value);

void setF_commit_id(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Viper::CommitId const & value);

void setF_uuid(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Viper::UUId const & value);

void setF_string(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::string const & value);

void setF_blob(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Viper::Blob const & value);

void setF_any(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, Viper::Any const & value);

void setF_vec(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::array<std::uint8_t, 2> const & value);

void setF_mat(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ThingKey const & key, std::array<std::array<std::uint8_t, 2>, 2> const & value);

} // namespace Core::Attachments::Thing::scalars

#endif