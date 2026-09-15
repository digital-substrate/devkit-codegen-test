// unité Woven — les données accrochées aux concepts qu'elle déclare.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar
//
// One scope per attachment, under the concept it is keyed on. The concept's own unit is
// part of the scope name whenever it is not this one: a namespace level cannot hold a
// qualified name, so `ModelA::Material` becomes `ModelA_Material` there -- and always,
// not only when two attachments would otherwise collide, so that adding one never
// renames another.

#ifndef Woven_Attachments_hpp
#define Woven_Attachments_hpp

#include "Woven_Data.hpp"
#include "Parts_Data.hpp"
#include "Core_Data.hpp"

#include "Viper_AttachmentGetting.hpp"
#include "Viper_AttachmentMutating.hpp"
#include "Viper_UUId.hpp"

#include <map>

#include <cstdint>
#include <optional>
#include <set>

namespace Woven::Attachments::Core_Thing::mark {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

std::set<Core::ThingKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, Core::ThingKey const & key);

std::optional<Parts::Colour> get(Viper::AttachmentGetting const & getting, Core::ThingKey const & key);

void set(Viper::AttachmentMutating & mutating, Core::ThingKey const & key, Parts::Colour const & value);

void diff(Viper::AttachmentMutating & mutating, Core::ThingKey const & key, Parts::Colour const & value,
          bool recursive = false);

void setR(Viper::AttachmentMutating & mutating, Core::ThingKey const & key, float value);

void setG(Viper::AttachmentMutating & mutating, Core::ThingKey const & key, float value);

void setB(Viper::AttachmentMutating & mutating, Core::ThingKey const & key, float value);

} // namespace Woven::Attachments::Core_Thing::mark

namespace Woven::Attachments::Knot::docAnyConceptKey {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key);

std::optional<::Crossing::AnyConceptKey> get(Viper::AttachmentGetting const & getting, KnotKey const & key);

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, ::Crossing::AnyConceptKey const & value);

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, ::Crossing::AnyConceptKey const & value,
          bool recursive = false);
} // namespace Woven::Attachments::Knot::docAnyConceptKey

namespace Woven::Attachments::Knot::docColour {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key);

std::optional<Core::Colour> get(Viper::AttachmentGetting const & getting, KnotKey const & key);

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, Core::Colour const & value);

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, Core::Colour const & value,
          bool recursive = false);

void setR(Viper::AttachmentMutating & mutating, KnotKey const & key, std::uint8_t value);

void setG(Viper::AttachmentMutating & mutating, KnotKey const & key, std::uint8_t value);

void setB(Viper::AttachmentMutating & mutating, KnotKey const & key, std::uint8_t value);

} // namespace Woven::Attachments::Knot::docColour

namespace Woven::Attachments::Knot::docComposites {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key);

std::optional<Composites> get(Viper::AttachmentGetting const & getting, KnotKey const & key);

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, Composites const & value);

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, Composites const & value,
          bool recursive = false);

void setF_tuple(Viper::AttachmentMutating & mutating, KnotKey const & key, std::tuple<Core::Colour, Parts::Colour> const & value);

void setF_optional(Viper::AttachmentMutating & mutating, KnotKey const & key, std::optional<Core::ThingKey> const & value);

void setF_vector(Viper::AttachmentMutating & mutating, KnotKey const & key, std::vector<Parts::Colour> const & value);

void setF_set(Viper::AttachmentMutating & mutating, KnotKey const & key, std::set<Core::ThingKey> const & value);
void unionF_set(Viper::AttachmentMutating & mutating, KnotKey const & key, std::set<Core::ThingKey> const & value);
void subtractF_set(Viper::AttachmentMutating & mutating, KnotKey const & key, std::set<Core::ThingKey> const & value);
void setF_map_keys(Viper::AttachmentMutating & mutating, KnotKey const & key, std::map<Core::ThingKey, Parts::ThingKey> const & value);
void unionF_map_keys(Viper::AttachmentMutating & mutating, KnotKey const & key, std::map<Core::ThingKey, Parts::ThingKey> const & value);
void subtractF_map_keys(Viper::AttachmentMutating & mutating, KnotKey const & key, std::set<Core::ThingKey> const & value);
void updateF_map_keys(Viper::AttachmentMutating & mutating, KnotKey const & key, std::map<Core::ThingKey, Parts::ThingKey> const & value);
void setF_map_enum(Viper::AttachmentMutating & mutating, KnotKey const & key, std::map<Core::Grade, Parts::Colour> const & value);
void unionF_map_enum(Viper::AttachmentMutating & mutating, KnotKey const & key, std::map<Core::Grade, Parts::Colour> const & value);
void subtractF_map_enum(Viper::AttachmentMutating & mutating, KnotKey const & key, std::set<Core::Grade> const & value);
void updateF_map_enum(Viper::AttachmentMutating & mutating, KnotKey const & key, std::map<Core::Grade, Parts::Colour> const & value);
void setF_xarray(Viper::AttachmentMutating & mutating, KnotKey const & key, Viper::XArray<Core::Colour> const & value);
void insertF_xarray(Viper::AttachmentMutating & mutating, KnotKey const & key, Viper::UUId const & beforePosition, Viper::UUId const & newPosition, Core::Colour const & value);
void updateF_xarray(Viper::AttachmentMutating & mutating, KnotKey const & key, Viper::UUId const & position, Core::Colour const & value);
void removeF_xarray(Viper::AttachmentMutating & mutating, KnotKey const & key, Viper::UUId const & position);
void setF_variant(Viper::AttachmentMutating & mutating, KnotKey const & key, std::variant<Core::Colour, Parts::Colour, std::string> const & value);

} // namespace Woven::Attachments::Knot::docComposites

namespace Woven::Attachments::Knot::docGrade {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key);

std::optional<Core::Grade> get(Viper::AttachmentGetting const & getting, KnotKey const & key);

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, Core::Grade const & value);

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, Core::Grade const & value,
          bool recursive = false);
} // namespace Woven::Attachments::Knot::docGrade

namespace Woven::Attachments::Knot::docKlubKey {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key);

std::optional<Core::KlubKey> get(Viper::AttachmentGetting const & getting, KnotKey const & key);

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, Core::KlubKey const & value);

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, Core::KlubKey const & value,
          bool recursive = false);
} // namespace Woven::Attachments::Knot::docKlubKey

namespace Woven::Attachments::Knot::docMapEnum {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key);

std::optional<std::map<Core::Grade, Parts::Colour>> get(Viper::AttachmentGetting const & getting, KnotKey const & key);

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, std::map<Core::Grade, Parts::Colour> const & value);

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, std::map<Core::Grade, Parts::Colour> const & value,
          bool recursive = false);

void union_(Viper::AttachmentMutating & mutating, KnotKey const & key, std::map<Core::Grade, Parts::Colour> const & value);
void subtract(Viper::AttachmentMutating & mutating, KnotKey const & key, std::set<Core::Grade> const & value);
void update(Viper::AttachmentMutating & mutating, KnotKey const & key, std::map<Core::Grade, Parts::Colour> const & value);

} // namespace Woven::Attachments::Knot::docMapEnum

namespace Woven::Attachments::Knot::docMapKeys {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key);

std::optional<std::map<Core::ThingKey, Parts::ThingKey>> get(Viper::AttachmentGetting const & getting, KnotKey const & key);

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, std::map<Core::ThingKey, Parts::ThingKey> const & value);

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, std::map<Core::ThingKey, Parts::ThingKey> const & value,
          bool recursive = false);

void union_(Viper::AttachmentMutating & mutating, KnotKey const & key, std::map<Core::ThingKey, Parts::ThingKey> const & value);
void subtract(Viper::AttachmentMutating & mutating, KnotKey const & key, std::set<Core::ThingKey> const & value);
void update(Viper::AttachmentMutating & mutating, KnotKey const & key, std::map<Core::ThingKey, Parts::ThingKey> const & value);

} // namespace Woven::Attachments::Knot::docMapKeys

namespace Woven::Attachments::Knot::docOptional {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key);

std::optional<std::optional<Core::ThingKey>> get(Viper::AttachmentGetting const & getting, KnotKey const & key);

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, std::optional<Core::ThingKey> const & value);

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, std::optional<Core::ThingKey> const & value,
          bool recursive = false);
} // namespace Woven::Attachments::Knot::docOptional

namespace Woven::Attachments::Knot::docOtherColour {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key);

std::optional<Parts::Colour> get(Viper::AttachmentGetting const & getting, KnotKey const & key);

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, Parts::Colour const & value);

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, Parts::Colour const & value,
          bool recursive = false);

void setR(Viper::AttachmentMutating & mutating, KnotKey const & key, float value);

void setG(Viper::AttachmentMutating & mutating, KnotKey const & key, float value);

void setB(Viper::AttachmentMutating & mutating, KnotKey const & key, float value);

} // namespace Woven::Attachments::Knot::docOtherColour

namespace Woven::Attachments::Knot::docSet {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key);

std::optional<std::set<Core::ThingKey>> get(Viper::AttachmentGetting const & getting, KnotKey const & key);

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, std::set<Core::ThingKey> const & value);

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, std::set<Core::ThingKey> const & value,
          bool recursive = false);

void union_(Viper::AttachmentMutating & mutating, KnotKey const & key, std::set<Core::ThingKey> const & value);
void subtract(Viper::AttachmentMutating & mutating, KnotKey const & key, std::set<Core::ThingKey> const & value);

} // namespace Woven::Attachments::Knot::docSet

namespace Woven::Attachments::Knot::docThingKey {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key);

std::optional<Core::ThingKey> get(Viper::AttachmentGetting const & getting, KnotKey const & key);

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, Core::ThingKey const & value);

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, Core::ThingKey const & value,
          bool recursive = false);
} // namespace Woven::Attachments::Knot::docThingKey

namespace Woven::Attachments::Knot::docTuple {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key);

std::optional<std::tuple<Core::Colour, Parts::Colour>> get(Viper::AttachmentGetting const & getting, KnotKey const & key);

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, std::tuple<Core::Colour, Parts::Colour> const & value);

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, std::tuple<Core::Colour, Parts::Colour> const & value,
          bool recursive = false);
} // namespace Woven::Attachments::Knot::docTuple

namespace Woven::Attachments::Knot::docVariant {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key);

std::optional<std::variant<Core::Colour, Parts::Colour>> get(Viper::AttachmentGetting const & getting, KnotKey const & key);

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, std::variant<Core::Colour, Parts::Colour> const & value);

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, std::variant<Core::Colour, Parts::Colour> const & value,
          bool recursive = false);
} // namespace Woven::Attachments::Knot::docVariant

namespace Woven::Attachments::Knot::docVector {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key);

std::optional<std::vector<Parts::Colour>> get(Viper::AttachmentGetting const & getting, KnotKey const & key);

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, std::vector<Parts::Colour> const & value);

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, std::vector<Parts::Colour> const & value,
          bool recursive = false);
} // namespace Woven::Attachments::Knot::docVector

namespace Woven::Attachments::Knot::docXArray {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

std::set<KnotKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, KnotKey const & key);

std::optional<Viper::XArray<Core::Colour>> get(Viper::AttachmentGetting const & getting, KnotKey const & key);

void set(Viper::AttachmentMutating & mutating, KnotKey const & key, Viper::XArray<Core::Colour> const & value);

void diff(Viper::AttachmentMutating & mutating, KnotKey const & key, Viper::XArray<Core::Colour> const & value,
          bool recursive = false);

void insert(Viper::AttachmentMutating & mutating, KnotKey const & key, Viper::UUId const & beforePosition, Viper::UUId const & newPosition, Core::Colour const & value);
void update(Viper::AttachmentMutating & mutating, KnotKey const & key, Viper::UUId const & position, Core::Colour const & value);
void remove(Viper::AttachmentMutating & mutating, KnotKey const & key, Viper::UUId const & position);

} // namespace Woven::Attachments::Knot::docXArray

namespace Woven::Attachments::Parts_Thing::mark {

/// L'identité de cet attachment dans le modèle. La portée nomme déjà l'attachment, donc
/// il ne reste que le nom.
extern Viper::UUId const runtimeId;

std::set<Parts::ThingKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, Parts::ThingKey const & key);

std::optional<Core::Colour> get(Viper::AttachmentGetting const & getting, Parts::ThingKey const & key);

void set(Viper::AttachmentMutating & mutating, Parts::ThingKey const & key, Core::Colour const & value);

void diff(Viper::AttachmentMutating & mutating, Parts::ThingKey const & key, Core::Colour const & value,
          bool recursive = false);

void setR(Viper::AttachmentMutating & mutating, Parts::ThingKey const & key, std::uint8_t value);

void setG(Viper::AttachmentMutating & mutating, Parts::ThingKey const & key, std::uint8_t value);

void setB(Viper::AttachmentMutating & mutating, Parts::ThingKey const & key, std::uint8_t value);

} // namespace Woven::Attachments::Parts_Thing::mark

#endif