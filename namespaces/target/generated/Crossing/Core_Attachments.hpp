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

std::set<ThingKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ThingKey const & key);

std::optional<Bag> get(Viper::AttachmentGetting const & getting, ThingKey const & key);

void set(Viper::AttachmentMutating & mutating, ThingKey const & key, Bag const & value);

void diff(Viper::AttachmentMutating & mutating, ThingKey const & key, Bag const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ThingKey const & key, Bag const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ThingKey const & key);

void setMembers(Viper::AttachmentMutating & mutating, ThingKey const & key, std::set<ThingKey> const & value);
void unionMembers(Viper::AttachmentMutating & mutating, ThingKey const & key, std::set<ThingKey> const & value);
void subtractMembers(Viper::AttachmentMutating & mutating, ThingKey const & key, std::set<ThingKey> const & value);
void setTints(Viper::AttachmentMutating & mutating, ThingKey const & key, std::map<ThingKey, Colour> const & value);
void unionTints(Viper::AttachmentMutating & mutating, ThingKey const & key, std::map<ThingKey, Colour> const & value);
void subtractTints(Viper::AttachmentMutating & mutating, ThingKey const & key, std::set<Core::ThingKey> const & value);
void updateTints(Viper::AttachmentMutating & mutating, ThingKey const & key, std::map<ThingKey, Colour> const & value);
void setTrail(Viper::AttachmentMutating & mutating, ThingKey const & key, Viper::XArray<Colour> const & value);
void insertTrail(Viper::AttachmentMutating & mutating, ThingKey const & key, Viper::UUId const & beforePosition, Viper::UUId const & newPosition, Core::Colour const & value);
void updateTrail(Viper::AttachmentMutating & mutating, ThingKey const & key, Viper::UUId const & position, Core::Colour const & value);
void removeTrail(Viper::AttachmentMutating & mutating, ThingKey const & key, Viper::UUId const & position);
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

std::set<ThingKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ThingKey const & key);

std::optional<Colour> get(Viper::AttachmentGetting const & getting, ThingKey const & key);

void set(Viper::AttachmentMutating & mutating, ThingKey const & key, Colour const & value);

void diff(Viper::AttachmentMutating & mutating, ThingKey const & key, Colour const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ThingKey const & key, Colour const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ThingKey const & key);

void setR(Viper::AttachmentMutating & mutating, ThingKey const & key, std::uint8_t value);

void setG(Viper::AttachmentMutating & mutating, ThingKey const & key, std::uint8_t value);

void setB(Viper::AttachmentMutating & mutating, ThingKey const & key, std::uint8_t value);

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

std::set<ThingKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ThingKey const & key);

std::optional<Viper::XArray<Colour>> get(Viper::AttachmentGetting const & getting, ThingKey const & key);

void set(Viper::AttachmentMutating & mutating, ThingKey const & key, Viper::XArray<Colour> const & value);

void diff(Viper::AttachmentMutating & mutating, ThingKey const & key, Viper::XArray<Colour> const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ThingKey const & key, Viper::XArray<Colour> const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ThingKey const & key);

void insert(Viper::AttachmentMutating & mutating, ThingKey const & key, Viper::UUId const & beforePosition, Viper::UUId const & newPosition, Core::Colour const & value);
void update(Viper::AttachmentMutating & mutating, ThingKey const & key, Viper::UUId const & position, Core::Colour const & value);
void remove(Viper::AttachmentMutating & mutating, ThingKey const & key, Viper::UUId const & position);

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

std::set<ThingKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ThingKey const & key);

std::optional<std::map<ThingKey, Colour>> get(Viper::AttachmentGetting const & getting, ThingKey const & key);

void set(Viper::AttachmentMutating & mutating, ThingKey const & key, std::map<ThingKey, Colour> const & value);

void diff(Viper::AttachmentMutating & mutating, ThingKey const & key, std::map<ThingKey, Colour> const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ThingKey const & key, std::map<ThingKey, Colour> const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ThingKey const & key);

void union_(Viper::AttachmentMutating & mutating, ThingKey const & key, std::map<ThingKey, Colour> const & value);
void subtract(Viper::AttachmentMutating & mutating, ThingKey const & key, std::set<Core::ThingKey> const & value);
void update(Viper::AttachmentMutating & mutating, ThingKey const & key, std::map<ThingKey, Colour> const & value);

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

std::set<ThingKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ThingKey const & key);

std::optional<std::set<ThingKey>> get(Viper::AttachmentGetting const & getting, ThingKey const & key);

void set(Viper::AttachmentMutating & mutating, ThingKey const & key, std::set<ThingKey> const & value);

void diff(Viper::AttachmentMutating & mutating, ThingKey const & key, std::set<ThingKey> const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ThingKey const & key, std::set<ThingKey> const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ThingKey const & key);

void union_(Viper::AttachmentMutating & mutating, ThingKey const & key, std::set<ThingKey> const & value);
void subtract(Viper::AttachmentMutating & mutating, ThingKey const & key, std::set<ThingKey> const & value);

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

std::set<ThingKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ThingKey const & key);

std::optional<Scalars> get(Viper::AttachmentGetting const & getting, ThingKey const & key);

void set(Viper::AttachmentMutating & mutating, ThingKey const & key, Scalars const & value);

void diff(Viper::AttachmentMutating & mutating, ThingKey const & key, Scalars const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ThingKey const & key, Scalars const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ThingKey const & key);

void setF_bool(Viper::AttachmentMutating & mutating, ThingKey const & key, bool value);

void setF_uint8(Viper::AttachmentMutating & mutating, ThingKey const & key, std::uint8_t value);

void setF_uint16(Viper::AttachmentMutating & mutating, ThingKey const & key, std::uint16_t value);

void setF_uint32(Viper::AttachmentMutating & mutating, ThingKey const & key, std::uint32_t value);

void setF_uint64(Viper::AttachmentMutating & mutating, ThingKey const & key, std::uint64_t value);

void setF_int8(Viper::AttachmentMutating & mutating, ThingKey const & key, std::int8_t value);

void setF_int16(Viper::AttachmentMutating & mutating, ThingKey const & key, std::int16_t value);

void setF_int32(Viper::AttachmentMutating & mutating, ThingKey const & key, std::int32_t value);

void setF_int64(Viper::AttachmentMutating & mutating, ThingKey const & key, std::int64_t value);

void setF_float(Viper::AttachmentMutating & mutating, ThingKey const & key, float value);

void setF_double(Viper::AttachmentMutating & mutating, ThingKey const & key, double value);

void setF_blob_id(Viper::AttachmentMutating & mutating, ThingKey const & key, Viper::BlobId const & value);

void setF_commit_id(Viper::AttachmentMutating & mutating, ThingKey const & key, Viper::CommitId const & value);

void setF_uuid(Viper::AttachmentMutating & mutating, ThingKey const & key, Viper::UUId const & value);

void setF_string(Viper::AttachmentMutating & mutating, ThingKey const & key, std::string const & value);

void setF_blob(Viper::AttachmentMutating & mutating, ThingKey const & key, Viper::Blob const & value);

void setF_any(Viper::AttachmentMutating & mutating, ThingKey const & key, Viper::Any const & value);

void setF_vec(Viper::AttachmentMutating & mutating, ThingKey const & key, std::array<std::uint8_t, 2> const & value);

void setF_mat(Viper::AttachmentMutating & mutating, ThingKey const & key, std::array<std::array<std::uint8_t, 2>, 2> const & value);

} // namespace Core::Attachments::Thing::scalars

#endif