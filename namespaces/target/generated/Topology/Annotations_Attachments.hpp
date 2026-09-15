// Annotations — the data hung on concepts, declared by this namespace.
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

#include "Viper_AttachmentGetting.hpp"
#include "Viper_AttachmentMutating.hpp"
#include "Viper_UUId.hpp"

#include <cstdint>
#include <optional>
#include <set>

/** A note carried by a material this namespace does not own. */
namespace Annotations::Attachments::ModelA_Material::note {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

std::set<ModelA::MaterialKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ModelA::MaterialKey const & key);

std::optional<std::string> get(Viper::AttachmentGetting const & getting, ModelA::MaterialKey const & key);

void set(Viper::AttachmentMutating & mutating, ModelA::MaterialKey const & key, std::string const & value);

void diff(Viper::AttachmentMutating & mutating, ModelA::MaterialKey const & key, std::string const & value,
          bool recursive = false);
} // namespace Annotations::Attachments::ModelA_Material::note

/** The same attachment name, on the same-named concept of another namespace. The
generator qualifies both scopes rather than colliding -- but only once this second
one exists, so adding it renames the first. */
namespace Annotations::Attachments::ModelB_Material::note {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

std::set<ModelB::MaterialKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ModelB::MaterialKey const & key);

std::optional<std::string> get(Viper::AttachmentGetting const & getting, ModelB::MaterialKey const & key);

void set(Viper::AttachmentMutating & mutating, ModelB::MaterialKey const & key, std::string const & value);

void diff(Viper::AttachmentMutating & mutating, ModelB::MaterialKey const & key, std::string const & value,
          bool recursive = false);
} // namespace Annotations::Attachments::ModelB_Material::note

#endif