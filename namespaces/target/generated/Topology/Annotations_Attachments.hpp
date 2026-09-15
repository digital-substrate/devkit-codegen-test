// unité Annotations — les données accrochées aux concepts qu'elle déclare.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar
//
// One scope per attachment, under the concept it is keyed on. The concept's own unit is
// part of the scope name whenever it is not this one: a namespace level cannot hold a
// qualified name, so `ModelA::Material` becomes `ModelA_Material` there -- and always,
// not only when two attachments would otherwise collide, so that adding one never
// renames another.

#ifndef Annotations_Attachments_hpp
#define Annotations_Attachments_hpp

#include "Annotations_Data.hpp"
#include "ModelB_Data.hpp"
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

/** A note carried by a material this namespace does not own. */
namespace Annotations::Attachments::ModelA_Material::note {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ModelA::MaterialKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting);

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ModelA::MaterialKey const & key);

std::optional<std::string> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ModelA::MaterialKey const & key);

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ModelA::MaterialKey const & key, std::string const & value);

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ModelA::MaterialKey const & key, std::string const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ModelA::MaterialKey const & key, std::string const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ModelA::MaterialKey const & key);
} // namespace Annotations::Attachments::ModelA_Material::note

/** The same attachment name, on the same-named concept of another namespace. The
generator qualifies both scopes rather than colliding -- but only once this second
one exists, so adding it renames the first. */
namespace Annotations::Attachments::ModelB_Material::note {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

/// Et le descripteur que le runtime en tire, résolu une fois.
///
/// PUBLIC PARCE QUE TOUT LE MONDE LE DEMANDE. L'épreuve sur base et le pont dynamique le
/// veulent autant que les cinq opérations, et chacun le re-résoudrait depuis l'identifiant.
/// Une identité, un endroit.
std::shared_ptr<Viper::Attachment> const & descriptor();

std::set<ModelB::MaterialKey> keys(std::shared_ptr<Viper::AttachmentGetting> const & getting);

bool has(std::shared_ptr<Viper::AttachmentGetting> const & getting, ModelB::MaterialKey const & key);

std::optional<std::string> get(std::shared_ptr<Viper::AttachmentGetting> const & getting, ModelB::MaterialKey const & key);

void set(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ModelB::MaterialKey const & key, std::string const & value);

void diff(std::shared_ptr<Viper::AttachmentMutating> const & mutating, ModelB::MaterialKey const & key, std::string const & value,
          bool recursive = false);

// ── et les mêmes, sur une base de données ──
//
// DEUX OPÉRATIONS, ET NON CINQ. `Viper::Database` hérite d'`AttachmentGetting`, donc les
// `keys`, `has` et `get` ci-dessus marchent déjà sur une base : ce sont les mêmes fonctions
// virtuelles. Ce qu'une base ajoute est d'écrire en rendant un statut, parce qu'un
// enregistrement peut échouer là où un changement en mémoire ne le peut pas.

bool set(std::shared_ptr<Viper::Database> const & db, ModelB::MaterialKey const & key, std::string const & value);
bool del(std::shared_ptr<Viper::Database> const & db, ModelB::MaterialKey const & key);
} // namespace Annotations::Attachments::ModelB_Material::note

#endif