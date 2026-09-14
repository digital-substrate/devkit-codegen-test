// ModelA — the data hung on its concepts.
//
// Layer 4: this is where the runtime appears in the signatures. An attachment is a named
// piece of data on instances of a concept, and the operations on it are the unit's --
// ModelA declares `attachment<Material, Colour> colour`, so ModelA says how to read and
// write it.

#ifndef ModelA_Attachments_hpp
#define ModelA_Attachments_hpp

#include "ModelA_Data.hpp"

#include "Viper_AttachmentGetting.hpp"
#include "Viper_AttachmentMutating.hpp"
#include "Viper_Path.hpp"

#include <optional>
#include <set>

namespace ModelA::Attachments::Material {

/// The colour attached to a Material.
///
/// NAMED `colour`, AS THE MODEL SPELLS IT, AND NOT `Colour`. A scope named `Colour` here
/// would shadow the type `Colour` declared a header away, so every signature below would
/// have to qualify its own namespace's type. The pack avoids the clash by flattening the
/// scope to `Material_Colour`, which is the flat prefix again, in a third place. Using
/// the model's own spelling costs nothing and says what the attachment is called.
namespace colour {

std::set<MaterialKey> keys(Viper::AttachmentGetting const & getting);

bool has(Viper::AttachmentGetting const & getting, MaterialKey const & key);

std::optional<Colour> get(Viper::AttachmentGetting const & getting, MaterialKey const & key);

void set(Viper::AttachmentMutating & mutating, MaterialKey const & key, Colour const & value);

/// Write one field rather than the whole document -- this is what layer 2's paths are for.
void set(Viper::AttachmentMutating & mutating, MaterialKey const & key,
         Viper::Path const & path, std::uint8_t channel);

void remove(Viper::AttachmentMutating & mutating, MaterialKey const & key);

} // namespace colour

} // namespace ModelA::Attachments::Material

#endif
