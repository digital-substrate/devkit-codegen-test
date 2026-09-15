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

#include "Viper_AttachmentGetting.hpp"
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

std::set<LinkKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, LinkKey const & key);

std::optional<std::map<ModelA::MaterialKey, ModelB::MaterialKey>> get(Viper::AttachmentGetting const & getting, LinkKey const & key);

void set(Viper::AttachmentMutating & mutating, LinkKey const & key, std::map<ModelA::MaterialKey, ModelB::MaterialKey> const & value);

void diff(Viper::AttachmentMutating & mutating, LinkKey const & key, std::map<ModelA::MaterialKey, ModelB::MaterialKey> const & value,
          bool recursive = false);

void union_(Viper::AttachmentMutating & mutating, LinkKey const & key, std::map<ModelA::MaterialKey, ModelB::MaterialKey> const & value);
void subtract(Viper::AttachmentMutating & mutating, LinkKey const & key, std::set<ModelA::MaterialKey> const & value);
void update(Viper::AttachmentMutating & mutating, LinkKey const & key, std::map<ModelA::MaterialKey, ModelB::MaterialKey> const & value);

} // namespace Projection::Attachments::Link::mapping

/** The only reference to ModelC anywhere: an attachment document type. */
namespace Projection::Attachments::Link::marker {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

std::set<LinkKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, LinkKey const & key);

std::optional<ModelC::MarkerKey> get(Viper::AttachmentGetting const & getting, LinkKey const & key);

void set(Viper::AttachmentMutating & mutating, LinkKey const & key, ModelC::MarkerKey const & value);

void diff(Viper::AttachmentMutating & mutating, LinkKey const & key, ModelC::MarkerKey const & value,
          bool recursive = false);
} // namespace Projection::Attachments::Link::marker

namespace Projection::Attachments::Link::pair {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

std::set<LinkKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, LinkKey const & key);

std::optional<Pair> get(Viper::AttachmentGetting const & getting, LinkKey const & key);

void set(Viper::AttachmentMutating & mutating, LinkKey const & key, Pair const & value);

void diff(Viper::AttachmentMutating & mutating, LinkKey const & key, Pair const & value,
          bool recursive = false);

void setA(Viper::AttachmentMutating & mutating, LinkKey const & key, ModelA::MaterialKey const & value);

void setB(Viper::AttachmentMutating & mutating, LinkKey const & key, ModelB::MaterialKey const & value);

} // namespace Projection::Attachments::Link::pair

#endif