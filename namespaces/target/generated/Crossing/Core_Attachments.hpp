// Core — the data hung on concepts, declared by this namespace.
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

#include "Viper_AttachmentGetting.hpp"
#include "Viper_AttachmentMutating.hpp"
#include "Viper_UUId.hpp"

#include <cstdint>
#include <optional>
#include <set>

namespace Core::Attachments::Thing::colour {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

std::set<ThingKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ThingKey const & key);

std::optional<Colour> get(Viper::AttachmentGetting const & getting, ThingKey const & key);

void set(Viper::AttachmentMutating & mutating, ThingKey const & key, Colour const & value);

void diff(Viper::AttachmentMutating & mutating, ThingKey const & key, Colour const & value,
          bool recursive = false);

void setR(Viper::AttachmentMutating & mutating, ThingKey const & key, std::uint8_t value);
void setG(Viper::AttachmentMutating & mutating, ThingKey const & key, std::uint8_t value);
void setB(Viper::AttachmentMutating & mutating, ThingKey const & key, std::uint8_t value);

} // namespace Core::Attachments::Thing::colour

namespace Core::Attachments::Thing::scalars {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

std::set<ThingKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, ThingKey const & key);

std::optional<Scalars> get(Viper::AttachmentGetting const & getting, ThingKey const & key);

void set(Viper::AttachmentMutating & mutating, ThingKey const & key, Scalars const & value);

void diff(Viper::AttachmentMutating & mutating, ThingKey const & key, Scalars const & value,
          bool recursive = false);

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