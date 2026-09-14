// THE ATTACHMENT-BORNE EDGE, visible in a signature.
//
// This unit declares one attachment, on a concept it does not own. Every accessor
// takes a ModelA::MaterialKey, so the include is not a courtesy -- the unit does not
// compile without it. This is the edge that carried no dependency at all before
// kibo 9328acd, and the one both backbone projections rely on.

#ifndef Annotations_Attachments_hpp
#define Annotations_Attachments_hpp

#include "Annotations_Data.hpp"     // its own, empty -- see the note there
#include "ModelA_Data.hpp"          // computed from the dependency set, not composed
#include "Viper_AttachmentGetting.hpp"
#include "Viper_AttachmentMutating.hpp"

namespace Annotations::Attachments::Material_Note {

std::set<ModelA::MaterialKey> keys(std::shared_ptr<Viper::AttachmentGetting> const &);
std::optional<std::string> get(std::shared_ptr<Viper::AttachmentGetting> const &, ModelA::MaterialKey const &);
void set(std::shared_ptr<Viper::AttachmentMutating> const &, ModelA::MaterialKey const &, std::string const &);
// ... unchanged ...

} // ns

#endif
