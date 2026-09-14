// A driver unit's own attachment: no cross-unit include at all. Both the concept
// and the document type are ModelA's.

#ifndef ModelA_Attachments_hpp
#define ModelA_Attachments_hpp

#include "ModelA_Data.hpp"
#include "Viper_AttachmentGetting.hpp"
#include "Viper_AttachmentMutating.hpp"

namespace ModelA::Attachments::Material_Colour {
std::optional<Colour> get(std::shared_ptr<Viper::AttachmentGetting> const &, MaterialKey const &);
// ... unchanged; MaterialKey and Colour unqualified, they are this unit's ...
} // ns

#endif
