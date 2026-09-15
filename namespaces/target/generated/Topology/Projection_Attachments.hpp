// unité Projection — les données accrochées aux concepts qu'elle déclare.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar
//
// One scope per attachment, under the concept it is keyed on. The concept's own unit is
// part of the scope name whenever it is not this one: a namespace level cannot hold a
// qualified name, so `ModelA::Material` becomes `ModelA_Material` there -- and always,
// not only when two attachments would otherwise collide, so that adding one never
// renames another.

#ifndef Projection_Attachments_hpp
#define Projection_Attachments_hpp

#include "Projection_Data.hpp"
#include "ModelB_Data.hpp"
#include "ModelC_Data.hpp"
#include "ModelA_Data.hpp"

#include "Viper_Attachment.hpp"
#include "Viper_AttachmentGetting.hpp"
#include "Viper_Database.hpp"
#include "Viper_AttachmentMutating.hpp"
#include "Viper_UUId.hpp"

#include <map>

#include <cstdint>
#include <optional>
#include <set>

/** A container shape spanning two namespaces: one typeSuffix, owned by neither. */
namespace Projection::Attachments::Link::mapping {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<LinkKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting);

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, LinkKey const & key);

std::optional<std::map<ModelA::MaterialKey, ModelB::MaterialKey>> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, LinkKey const & key);

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, LinkKey const & key, std::map<ModelA::MaterialKey, ModelB::MaterialKey> const & value);

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, LinkKey const & key, std::map<ModelA::MaterialKey, ModelB::MaterialKey> const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, LinkKey const & key, std::map<ModelA::MaterialKey, ModelB::MaterialKey> const & value);
bool del(std::shared_ptr<Viper::Database> const & db, LinkKey const & key);

void union_(std::shared_ptr<Viper::AttachmentMutating> const & mutating, LinkKey const & key, std::map<ModelA::MaterialKey, ModelB::MaterialKey> const & value);
void subtract(std::shared_ptr<Viper::AttachmentMutating> const & mutating, LinkKey const & key, std::set<ModelA::MaterialKey> const & value);
void update(std::shared_ptr<Viper::AttachmentMutating> const & mutating, LinkKey const & key, std::map<ModelA::MaterialKey, ModelB::MaterialKey> const & value);

} // namespace Projection::Attachments::Link::mapping

/** The only reference to ModelC anywhere: an attachment document type. */
namespace Projection::Attachments::Link::marker {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<LinkKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting);

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, LinkKey const & key);

std::optional<ModelC::MarkerKey> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, LinkKey const & key);

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, LinkKey const & key, ModelC::MarkerKey const & value);

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, LinkKey const & key, ModelC::MarkerKey const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, LinkKey const & key, ModelC::MarkerKey const & value);
bool del(std::shared_ptr<Viper::Database> const & db, LinkKey const & key);
} // namespace Projection::Attachments::Link::marker

namespace Projection::Attachments::Link::pair {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<LinkKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting);

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, LinkKey const & key);

std::optional<Pair> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, LinkKey const & key);

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, LinkKey const & key, Pair const & value);

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, LinkKey const & key, Pair const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, LinkKey const & key, Pair const & value);
bool del(std::shared_ptr<Viper::Database> const & db, LinkKey const & key);

void setA(std::shared_ptr<Viper::AttachmentMutating> const & mutating, LinkKey const & key, ModelA::MaterialKey const & value);

void setB(std::shared_ptr<Viper::AttachmentMutating> const & mutating, LinkKey const & key, ModelB::MaterialKey const & value);

} // namespace Projection::Attachments::Link::pair

#endif