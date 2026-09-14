// The composing unit's attachments, and the spanning container in the open.
//
// Link_Mapping's accessors take std::map<ModelA::MaterialKey, ModelB::MaterialKey>:
// a shape belonging to neither driver unit, written here because this is the unit
// that declares it. Its *type descriptor* is another matter and stays in the base --
// see Topology_ValueType.hpp.

#ifndef Projection_Attachments_hpp
#define Projection_Attachments_hpp

#include "Projection_Data.hpp"
#include "ModelA_Data.hpp"
#include "ModelB_Data.hpp"
#include "ModelC_Data.hpp"          // Link_Marker takes a ModelC::MarkerKey
#include "Viper_AttachmentGetting.hpp"
#include "Viper_AttachmentMutating.hpp"

namespace Projection::Attachments::Link_Mapping {

std::optional<std::map<ModelA::MaterialKey, ModelB::MaterialKey>>
get(std::shared_ptr<Viper::AttachmentGetting> const &, LinkKey const &);
// ... unchanged ...

} // ns

namespace Projection::Attachments::Link_Marker {
std::optional<ModelC::MarkerKey> get(std::shared_ptr<Viper::AttachmentGetting> const &, LinkKey const &);
// ... unchanged ...
} // ns

namespace Projection::Attachments::Link_Pair { /* ... unchanged ... */ }

#endif
