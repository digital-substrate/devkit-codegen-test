// The unit that was empty in Data is NOT empty here: it declares one attachment,
// so it has one attachment runtime id and no concept ids at all.
//
// Which is the argument for emitting a file per unit per feature: whether a unit
// has content depends on the feature, and a consumer should not have to know.

#ifndef Annotations_Definitions_hpp
#define Annotations_Definitions_hpp

#include "Viper_UUId.hpp"

namespace Annotations::RuntimeIds {
} // ns Annotations::RuntimeIds

namespace Annotations::AttachmentRuntimeIds {
extern Viper::UUId const Material_note;
} // ns Annotations::AttachmentRuntimeIds

#endif
