// unité Test — les données accrochées aux concepts qu'elle déclare.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/features/Features.dsm.json by kibo-2.0.0.jar
//
// One scope per attachment, under the concept it is keyed on. The concept's own unit is
// part of the scope name whenever it is not this one: a namespace level cannot hold a
// qualified name, so `ModelA::Material` becomes `ModelA_Material` there -- and always,
// not only when two attachments would otherwise collide, so that adding one never
// renames another.

#ifndef Test_Attachments_hpp
#define Test_Attachments_hpp

#include "Test_Data.hpp"

#include "Viper_Attachment.hpp"
#include "Viper_AttachmentGetting.hpp"
#include "Viper_Database.hpp"
#include "Viper_AttachmentMutating.hpp"
#include "Viper_UUId.hpp"

#include <map>

#include <cstdint>
#include <optional>
#include <set>

namespace Test::Attachments::AnyConcept::propertiesAnyConceptAny {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<::Features::AnyConceptKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ::Features::AnyConceptKey const & key);

std::optional<Viper::Any> get(Viper::AttachmentGetting const & getting, ::Features::AnyConceptKey const & key);

void set(Viper::AttachmentMutating & mutating, ::Features::AnyConceptKey const & key, Viper::Any const & value);

void diff(Viper::AttachmentMutating & mutating, ::Features::AnyConceptKey const & key, Viper::Any const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ::Features::AnyConceptKey const & key, Viper::Any const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ::Features::AnyConceptKey const & key);
} // namespace Test::Attachments::AnyConcept::propertiesAnyConceptAny

namespace Test::Attachments::ConceptA::properties {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptAKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptAKey const & key);

std::optional<StructureV> get(Viper::AttachmentGetting const & getting, ConceptAKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptAKey const & key, StructureV const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptAKey const & key, StructureV const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key, StructureV const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key);

void setF_bool(Viper::AttachmentMutating & mutating, ConceptAKey const & key, bool value);

void setF_uint8(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::uint8_t value);

void setF_uint16(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::uint16_t value);

void setF_uint32(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::uint32_t value);

void setF_uint64(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::uint64_t value);

void setF_int8(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::int8_t value);

void setF_int16(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::int16_t value);

void setF_int32(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::int32_t value);

void setF_int64(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::int64_t value);

void setF_float(Viper::AttachmentMutating & mutating, ConceptAKey const & key, float value);

void setF_double(Viper::AttachmentMutating & mutating, ConceptAKey const & key, double value);

void setF_uuid(Viper::AttachmentMutating & mutating, ConceptAKey const & key, Viper::UUId const & value);

void setF_string(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::string const & value);

void setF_vec(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::array<std::uint8_t, 2> const & value);

void setF_mat(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::array<std::array<std::uint8_t, 3>, 2> const & value);

void setF_tuple(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::tuple<std::uint8_t, std::string> const & value);

void setF_optional(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::optional<std::uint8_t> const & value);

void setF_vector(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::vector<std::uint8_t> const & value);

void setF_set(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::set<std::uint8_t> const & value);
void unionF_set(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::set<std::uint8_t> const & value);
void subtractF_set(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::set<std::uint8_t> const & value);
void setF_map(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::map<std::uint8_t, std::string> const & value);
void unionF_map(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::map<std::uint8_t, std::string> const & value);
void subtractF_map(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::set<std::uint8_t> const & value);
void updateF_map(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::map<std::uint8_t, std::string> const & value);
void setF_E(Viper::AttachmentMutating & mutating, ConceptAKey const & key, EnumerationE value);

void setF_S(Viper::AttachmentMutating & mutating, ConceptAKey const & key, StructureS const & value);

void setF_T(Viper::AttachmentMutating & mutating, ConceptAKey const & key, StructureT const & value);

} // namespace Test::Attachments::ConceptA::properties

namespace Test::Attachments::ConceptA::propertiesInt8 {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptAKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptAKey const & key);

std::optional<std::int8_t> get(Viper::AttachmentGetting const & getting, ConceptAKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::int8_t const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::int8_t const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key, std::int8_t const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key);
} // namespace Test::Attachments::ConceptA::propertiesInt8

namespace Test::Attachments::ConceptA::propertiesMapInt8String {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptAKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptAKey const & key);

std::optional<std::map<std::int8_t, std::string>> get(Viper::AttachmentGetting const & getting, ConceptAKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::map<std::int8_t, std::string> const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::map<std::int8_t, std::string> const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key, std::map<std::int8_t, std::string> const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key);

void union_(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::map<std::int8_t, std::string> const & value);
void subtract(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::set<std::int8_t> const & value);
void update(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::map<std::int8_t, std::string> const & value);

} // namespace Test::Attachments::ConceptA::propertiesMapInt8String

namespace Test::Attachments::ConceptA::propertiesSeInt8 {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptAKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptAKey const & key);

std::optional<std::set<std::int8_t>> get(Viper::AttachmentGetting const & getting, ConceptAKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::set<std::int8_t> const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::set<std::int8_t> const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key, std::set<std::int8_t> const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key);

void union_(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::set<std::int8_t> const & value);
void subtract(Viper::AttachmentMutating & mutating, ConceptAKey const & key, std::set<std::int8_t> const & value);

} // namespace Test::Attachments::ConceptA::propertiesSeInt8

namespace Test::Attachments::ConceptA::propertiesXArray {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptAKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptAKey const & key);

std::optional<Viper::XArray<std::int8_t>> get(Viper::AttachmentGetting const & getting, ConceptAKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptAKey const & key, Viper::XArray<std::int8_t> const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptAKey const & key, Viper::XArray<std::int8_t> const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key, Viper::XArray<std::int8_t> const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptAKey const & key);

void insert(Viper::AttachmentMutating & mutating, ConceptAKey const & key, Viper::UUId const & beforePosition, Viper::UUId const & newPosition, std::int8_t value);
void update(Viper::AttachmentMutating & mutating, ConceptAKey const & key, Viper::UUId const & position, std::int8_t value);
void remove(Viper::AttachmentMutating & mutating, ConceptAKey const & key, Viper::UUId const & position);

} // namespace Test::Attachments::ConceptA::propertiesXArray

namespace Test::Attachments::ConceptB::propertiesB {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptBKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptBKey const & key);

std::optional<StructureT> get(Viper::AttachmentGetting const & getting, ConceptBKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptBKey const & key, StructureT const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptBKey const & key, StructureT const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptBKey const & key, StructureT const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptBKey const & key);

void setField_string(Viper::AttachmentMutating & mutating, ConceptBKey const & key, std::string const & value);

void setField_structure_s(Viper::AttachmentMutating & mutating, ConceptBKey const & key, StructureS const & value);

} // namespace Test::Attachments::ConceptB::propertiesB

namespace Test::Attachments::ConceptC::propertiesC {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCKey const & key);

std::optional<StructureU> get(Viper::AttachmentGetting const & getting, ConceptCKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCKey const & key, StructureU const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCKey const & key, StructureU const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCKey const & key, StructureU const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCKey const & key);

void setF_bool(Viper::AttachmentMutating & mutating, ConceptCKey const & key, bool value);

void setF_uint8(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::uint8_t value);

void setF_uint16(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::uint16_t value);

void setF_uint32(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::uint32_t value);

void setF_uint64(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::uint64_t value);

void setF_int8(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::int8_t value);

void setF_int16(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::int16_t value);

void setF_int32(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::int32_t value);

void setF_int64(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::int64_t value);

void setF_float(Viper::AttachmentMutating & mutating, ConceptCKey const & key, float value);

void setF_double(Viper::AttachmentMutating & mutating, ConceptCKey const & key, double value);

void setF_blob_id(Viper::AttachmentMutating & mutating, ConceptCKey const & key, Viper::BlobId const & value);

void setF_commit_id(Viper::AttachmentMutating & mutating, ConceptCKey const & key, Viper::CommitId const & value);

void setF_uuid(Viper::AttachmentMutating & mutating, ConceptCKey const & key, Viper::UUId const & value);

void setF_string(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::string const & value);

void setF_blob(Viper::AttachmentMutating & mutating, ConceptCKey const & key, Viper::Blob const & value);

void setF_vec(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::array<std::uint8_t, 2> const & value);

void setF_mat(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::array<std::array<std::uint8_t, 2>, 2> const & value);

void setF_tuple(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::tuple<std::uint8_t, std::string> const & value);

void setF_optional(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::optional<std::uint8_t> const & value);

void setF_vector(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::vector<std::uint8_t> const & value);

void setF_set(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::set<std::uint8_t> const & value);
void unionF_set(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::set<std::uint8_t> const & value);
void subtractF_set(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::set<std::uint8_t> const & value);
void setF_set_s(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::set<StructureS> const & value);
void unionF_set_s(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::set<StructureS> const & value);
void subtractF_set_s(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::set<StructureS> const & value);
void setF_map_s1(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::map<StructureS, std::string> const & value);
void unionF_map_s1(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::map<StructureS, std::string> const & value);
void subtractF_map_s1(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::set<Test::StructureS> const & value);
void updateF_map_s1(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::map<StructureS, std::string> const & value);
void setF_map_s2(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::map<std::string, StructureS> const & value);
void unionF_map_s2(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::map<std::string, StructureS> const & value);
void subtractF_map_s2(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::set<std::string> const & value);
void updateF_map_s2(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::map<std::string, StructureS> const & value);
void setF_xarray(Viper::AttachmentMutating & mutating, ConceptCKey const & key, Viper::XArray<std::uint8_t> const & value);
void insertF_xarray(Viper::AttachmentMutating & mutating, ConceptCKey const & key, Viper::UUId const & beforePosition, Viper::UUId const & newPosition, std::uint8_t value);
void updateF_xarray(Viper::AttachmentMutating & mutating, ConceptCKey const & key, Viper::UUId const & position, std::uint8_t value);
void removeF_xarray(Viper::AttachmentMutating & mutating, ConceptCKey const & key, Viper::UUId const & position);
void setF_xarray_s(Viper::AttachmentMutating & mutating, ConceptCKey const & key, Viper::XArray<StructureS> const & value);
void insertF_xarray_s(Viper::AttachmentMutating & mutating, ConceptCKey const & key, Viper::UUId const & beforePosition, Viper::UUId const & newPosition, Test::StructureS const & value);
void updateF_xarray_s(Viper::AttachmentMutating & mutating, ConceptCKey const & key, Viper::UUId const & position, Test::StructureS const & value);
void removeF_xarray_s(Viper::AttachmentMutating & mutating, ConceptCKey const & key, Viper::UUId const & position);
void setF_map_vs(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::map<std::vector<StructureS>, std::string> const & value);
void unionF_map_vs(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::map<std::vector<StructureS>, std::string> const & value);
void subtractF_map_vs(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::set<std::vector<Test::StructureS>> const & value);
void updateF_map_vs(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::map<std::vector<StructureS>, std::string> const & value);
void setF_variant(Viper::AttachmentMutating & mutating, ConceptCKey const & key, std::variant<std::string, std::uint8_t, StructureS> const & value);

void setF_any(Viper::AttachmentMutating & mutating, ConceptCKey const & key, Viper::Any const & value);

void setF_E(Viper::AttachmentMutating & mutating, ConceptCKey const & key, EnumerationE value);

void setF_S(Viper::AttachmentMutating & mutating, ConceptCKey const & key, StructureS const & value);

void setF_T(Viper::AttachmentMutating & mutating, ConceptCKey const & key, StructureT const & value);

void setF_A(Viper::AttachmentMutating & mutating, ConceptCKey const & key, ConceptAKey const & value);

void setF_B(Viper::AttachmentMutating & mutating, ConceptCKey const & key, ConceptBKey const & value);

void setF_C(Viper::AttachmentMutating & mutating, ConceptCKey const & key, ConceptCKey const & value);

void setF_D(Viper::AttachmentMutating & mutating, ConceptCKey const & key, ConceptDKey const & value);

void setF_Klub(Viper::AttachmentMutating & mutating, ConceptCKey const & key, KlubKey const & value);

void setF_any_concept(Viper::AttachmentMutating & mutating, ConceptCKey const & key, ::Features::AnyConceptKey const & value);

} // namespace Test::Attachments::ConceptC::propertiesC

namespace Test::Attachments::ConceptCoverage::docAny {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<Viper::Any> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, Viper::Any const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, Viper::Any const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, Viper::Any const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);
} // namespace Test::Attachments::ConceptCoverage::docAny

namespace Test::Attachments::ConceptCoverage::docAnyConceptKey {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<::Features::AnyConceptKey> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, ::Features::AnyConceptKey const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, ::Features::AnyConceptKey const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, ::Features::AnyConceptKey const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);
} // namespace Test::Attachments::ConceptCoverage::docAnyConceptKey

namespace Test::Attachments::ConceptCoverage::docBlob {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<Viper::Blob> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, Viper::Blob const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, Viper::Blob const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, Viper::Blob const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);
} // namespace Test::Attachments::ConceptCoverage::docBlob

namespace Test::Attachments::ConceptCoverage::docBlobId {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<Viper::BlobId> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, Viper::BlobId const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, Viper::BlobId const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, Viper::BlobId const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);
} // namespace Test::Attachments::ConceptCoverage::docBlobId

namespace Test::Attachments::ConceptCoverage::docBool {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<bool> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, bool const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, bool const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, bool const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);
} // namespace Test::Attachments::ConceptCoverage::docBool

namespace Test::Attachments::ConceptCoverage::docClubKey {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<KlubKey> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, KlubKey const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, KlubKey const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, KlubKey const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);
} // namespace Test::Attachments::ConceptCoverage::docClubKey

namespace Test::Attachments::ConceptCoverage::docCommitId {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<Viper::CommitId> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, Viper::CommitId const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, Viper::CommitId const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, Viper::CommitId const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);
} // namespace Test::Attachments::ConceptCoverage::docCommitId

namespace Test::Attachments::ConceptCoverage::docConceptKey {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<ConceptAKey> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, ConceptAKey const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, ConceptAKey const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, ConceptAKey const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);
} // namespace Test::Attachments::ConceptCoverage::docConceptKey

namespace Test::Attachments::ConceptCoverage::docConceptKeyB {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<ConceptBKey> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, ConceptBKey const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, ConceptBKey const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, ConceptBKey const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);
} // namespace Test::Attachments::ConceptCoverage::docConceptKeyB

namespace Test::Attachments::ConceptCoverage::docDouble {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<double> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, double const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, double const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, double const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);
} // namespace Test::Attachments::ConceptCoverage::docDouble

namespace Test::Attachments::ConceptCoverage::docEnumeration {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<EnumerationE> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, EnumerationE const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, EnumerationE const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, EnumerationE const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);
} // namespace Test::Attachments::ConceptCoverage::docEnumeration

namespace Test::Attachments::ConceptCoverage::docFloat {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<float> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, float const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, float const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, float const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);
} // namespace Test::Attachments::ConceptCoverage::docFloat

namespace Test::Attachments::ConceptCoverage::docInt16 {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<std::int16_t> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::int16_t const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::int16_t const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::int16_t const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);
} // namespace Test::Attachments::ConceptCoverage::docInt16

namespace Test::Attachments::ConceptCoverage::docInt32 {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<std::int32_t> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::int32_t const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::int32_t const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::int32_t const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);
} // namespace Test::Attachments::ConceptCoverage::docInt32

namespace Test::Attachments::ConceptCoverage::docInt64 {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<std::int64_t> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::int64_t const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::int64_t const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::int64_t const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);
} // namespace Test::Attachments::ConceptCoverage::docInt64

namespace Test::Attachments::ConceptCoverage::docInt8 {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<std::int8_t> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::int8_t const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::int8_t const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::int8_t const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);
} // namespace Test::Attachments::ConceptCoverage::docInt8

namespace Test::Attachments::ConceptCoverage::docMap {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<std::map<std::uint8_t, std::string>> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::map<std::uint8_t, std::string> const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::map<std::uint8_t, std::string> const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::map<std::uint8_t, std::string> const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

void union_(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::map<std::uint8_t, std::string> const & value);
void subtract(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::set<std::uint8_t> const & value);
void update(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::map<std::uint8_t, std::string> const & value);

} // namespace Test::Attachments::ConceptCoverage::docMap

namespace Test::Attachments::ConceptCoverage::docMat {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<std::array<std::array<std::uint8_t, 2>, 2>> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::array<std::array<std::uint8_t, 2>, 2> const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::array<std::array<std::uint8_t, 2>, 2> const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::array<std::array<std::uint8_t, 2>, 2> const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);
} // namespace Test::Attachments::ConceptCoverage::docMat

namespace Test::Attachments::ConceptCoverage::docOptional {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<std::optional<std::uint8_t>> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::optional<std::uint8_t> const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::optional<std::uint8_t> const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::optional<std::uint8_t> const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);
} // namespace Test::Attachments::ConceptCoverage::docOptional

namespace Test::Attachments::ConceptCoverage::docSet {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<std::set<std::uint8_t>> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::set<std::uint8_t> const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::set<std::uint8_t> const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::set<std::uint8_t> const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

void union_(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::set<std::uint8_t> const & value);
void subtract(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::set<std::uint8_t> const & value);

} // namespace Test::Attachments::ConceptCoverage::docSet

namespace Test::Attachments::ConceptCoverage::docString {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<std::string> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::string const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::string const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::string const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);
} // namespace Test::Attachments::ConceptCoverage::docString

namespace Test::Attachments::ConceptCoverage::docStructureSingleField {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<StructureW> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, StructureW const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, StructureW const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, StructureW const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

void setF_single(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::uint8_t value);

} // namespace Test::Attachments::ConceptCoverage::docStructureSingleField

namespace Test::Attachments::ConceptCoverage::docTuple {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<std::tuple<std::uint8_t, std::string>> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::tuple<std::uint8_t, std::string> const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::tuple<std::uint8_t, std::string> const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::tuple<std::uint8_t, std::string> const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);
} // namespace Test::Attachments::ConceptCoverage::docTuple

namespace Test::Attachments::ConceptCoverage::docUInt16 {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<std::uint16_t> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::uint16_t const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::uint16_t const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::uint16_t const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);
} // namespace Test::Attachments::ConceptCoverage::docUInt16

namespace Test::Attachments::ConceptCoverage::docUInt32 {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<std::uint32_t> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::uint32_t const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::uint32_t const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::uint32_t const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);
} // namespace Test::Attachments::ConceptCoverage::docUInt32

namespace Test::Attachments::ConceptCoverage::docUInt64 {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<std::uint64_t> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::uint64_t const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::uint64_t const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::uint64_t const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);
} // namespace Test::Attachments::ConceptCoverage::docUInt64

namespace Test::Attachments::ConceptCoverage::docUInt8 {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<std::uint8_t> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::uint8_t const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::uint8_t const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::uint8_t const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);
} // namespace Test::Attachments::ConceptCoverage::docUInt8

namespace Test::Attachments::ConceptCoverage::docUUId {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<Viper::UUId> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, Viper::UUId const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, Viper::UUId const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, Viper::UUId const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);
} // namespace Test::Attachments::ConceptCoverage::docUUId

namespace Test::Attachments::ConceptCoverage::docVariant {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<std::variant<std::string, std::uint8_t>> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::variant<std::string, std::uint8_t> const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::variant<std::string, std::uint8_t> const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::variant<std::string, std::uint8_t> const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);
} // namespace Test::Attachments::ConceptCoverage::docVariant

namespace Test::Attachments::ConceptCoverage::docVec {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<std::array<std::uint8_t, 2>> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::array<std::uint8_t, 2> const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::array<std::uint8_t, 2> const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::array<std::uint8_t, 2> const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);
} // namespace Test::Attachments::ConceptCoverage::docVec

namespace Test::Attachments::ConceptCoverage::docVector {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<std::vector<std::uint8_t>> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::vector<std::uint8_t> const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, std::vector<std::uint8_t> const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, std::vector<std::uint8_t> const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);
} // namespace Test::Attachments::ConceptCoverage::docVector

namespace Test::Attachments::ConceptCoverage::docXArray {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ConceptCoverageKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

std::optional<Viper::XArray<std::uint8_t>> get(Viper::AttachmentGetting const & getting, ConceptCoverageKey const & key);

void set(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, Viper::XArray<std::uint8_t> const & value);

void diff(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, Viper::XArray<std::uint8_t> const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key, Viper::XArray<std::uint8_t> const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ConceptCoverageKey const & key);

void insert(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, Viper::UUId const & beforePosition, Viper::UUId const & newPosition, std::uint8_t value);
void update(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, Viper::UUId const & position, std::uint8_t value);
void remove(Viper::AttachmentMutating & mutating, ConceptCoverageKey const & key, Viper::UUId const & position);

} // namespace Test::Attachments::ConceptCoverage::docXArray

namespace Test::Attachments::Klub::propertiesD {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<KlubKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, KlubKey const & key);

std::optional<StructureV> get(Viper::AttachmentGetting const & getting, KlubKey const & key);

void set(Viper::AttachmentMutating & mutating, KlubKey const & key, StructureV const & value);

void diff(Viper::AttachmentMutating & mutating, KlubKey const & key, StructureV const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, KlubKey const & key, StructureV const & value);
bool del(std::shared_ptr<Viper::Database> const & db, KlubKey const & key);

void setF_bool(Viper::AttachmentMutating & mutating, KlubKey const & key, bool value);

void setF_uint8(Viper::AttachmentMutating & mutating, KlubKey const & key, std::uint8_t value);

void setF_uint16(Viper::AttachmentMutating & mutating, KlubKey const & key, std::uint16_t value);

void setF_uint32(Viper::AttachmentMutating & mutating, KlubKey const & key, std::uint32_t value);

void setF_uint64(Viper::AttachmentMutating & mutating, KlubKey const & key, std::uint64_t value);

void setF_int8(Viper::AttachmentMutating & mutating, KlubKey const & key, std::int8_t value);

void setF_int16(Viper::AttachmentMutating & mutating, KlubKey const & key, std::int16_t value);

void setF_int32(Viper::AttachmentMutating & mutating, KlubKey const & key, std::int32_t value);

void setF_int64(Viper::AttachmentMutating & mutating, KlubKey const & key, std::int64_t value);

void setF_float(Viper::AttachmentMutating & mutating, KlubKey const & key, float value);

void setF_double(Viper::AttachmentMutating & mutating, KlubKey const & key, double value);

void setF_uuid(Viper::AttachmentMutating & mutating, KlubKey const & key, Viper::UUId const & value);

void setF_string(Viper::AttachmentMutating & mutating, KlubKey const & key, std::string const & value);

void setF_vec(Viper::AttachmentMutating & mutating, KlubKey const & key, std::array<std::uint8_t, 2> const & value);

void setF_mat(Viper::AttachmentMutating & mutating, KlubKey const & key, std::array<std::array<std::uint8_t, 3>, 2> const & value);

void setF_tuple(Viper::AttachmentMutating & mutating, KlubKey const & key, std::tuple<std::uint8_t, std::string> const & value);

void setF_optional(Viper::AttachmentMutating & mutating, KlubKey const & key, std::optional<std::uint8_t> const & value);

void setF_vector(Viper::AttachmentMutating & mutating, KlubKey const & key, std::vector<std::uint8_t> const & value);

void setF_set(Viper::AttachmentMutating & mutating, KlubKey const & key, std::set<std::uint8_t> const & value);
void unionF_set(Viper::AttachmentMutating & mutating, KlubKey const & key, std::set<std::uint8_t> const & value);
void subtractF_set(Viper::AttachmentMutating & mutating, KlubKey const & key, std::set<std::uint8_t> const & value);
void setF_map(Viper::AttachmentMutating & mutating, KlubKey const & key, std::map<std::uint8_t, std::string> const & value);
void unionF_map(Viper::AttachmentMutating & mutating, KlubKey const & key, std::map<std::uint8_t, std::string> const & value);
void subtractF_map(Viper::AttachmentMutating & mutating, KlubKey const & key, std::set<std::uint8_t> const & value);
void updateF_map(Viper::AttachmentMutating & mutating, KlubKey const & key, std::map<std::uint8_t, std::string> const & value);
void setF_E(Viper::AttachmentMutating & mutating, KlubKey const & key, EnumerationE value);

void setF_S(Viper::AttachmentMutating & mutating, KlubKey const & key, StructureS const & value);

void setF_T(Viper::AttachmentMutating & mutating, KlubKey const & key, StructureT const & value);

} // namespace Test::Attachments::Klub::propertiesD

#endif