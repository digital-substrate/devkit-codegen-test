// A unit's half of Definitions: the runtime ids of what this namespace declares.
//
// RuntimeIds stays a scope, unlike ValueType: it is not a feature name but a real
// distinction -- ModelA::RuntimeIds::Material is the UUID, ModelA::MaterialKey is
// the type, and both are ModelA's.

#ifndef ModelA_Definitions_hpp
#define ModelA_Definitions_hpp

#include "Viper_UUId.hpp"

namespace ModelA::RuntimeIds {
extern Viper::UUId const Material;
extern Viper::UUId const Colour;
} // ns ModelA::RuntimeIds

namespace ModelA::AttachmentRuntimeIds {
extern Viper::UUId const Material_Colour;
} // ns ModelA::AttachmentRuntimeIds

#endif
