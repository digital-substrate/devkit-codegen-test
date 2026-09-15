// unité ModelB — les données accrochées aux concepts qu'elle déclare.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar
//
// One scope per attachment, under the concept it is keyed on. The concept's own unit is
// part of the scope name whenever it is not this one: a namespace level cannot hold a
// qualified name, so `ModelA::Material` becomes `ModelA_Material` there -- and always,
// not only when two attachments would otherwise collide, so that adding one never
// renames another.

#ifndef ModelB_Attachments_hpp
#define ModelB_Attachments_hpp

#include "ModelB_Data.hpp"

#include "Viper_AttachmentGetting.hpp"
#include "Viper_AttachmentMutating.hpp"
#include "Viper_UUId.hpp"

#include <map>

#include <cstdint>
#include <optional>
#include <set>

namespace ModelB::Attachments::Material::colour {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

std::set<MaterialKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, MaterialKey const & key);

std::optional<Colour> get(Viper::AttachmentGetting const & getting, MaterialKey const & key);

void set(Viper::AttachmentMutating & mutating, MaterialKey const & key, Colour const & value);

void diff(Viper::AttachmentMutating & mutating, MaterialKey const & key, Colour const & value,
          bool recursive = false);

void setR(Viper::AttachmentMutating & mutating, MaterialKey const & key, float value);

void setG(Viper::AttachmentMutating & mutating, MaterialKey const & key, float value);

void setB(Viper::AttachmentMutating & mutating, MaterialKey const & key, float value);

} // namespace ModelB::Attachments::Material::colour

#endif