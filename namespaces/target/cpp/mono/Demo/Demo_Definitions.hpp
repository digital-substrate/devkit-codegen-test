// The one driver unit's runtime ids. Demo::RuntimeIds::Player, where today it is
// Service::Demo::RuntimeIds::Player.

#ifndef Demo_Definitions_hpp
#define Demo_Definitions_hpp

#include "Viper_UUId.hpp"

namespace Demo::RuntimeIds {
extern Viper::UUId const Player;
extern Viper::UUId const Vector3;
} // ns Demo::RuntimeIds

namespace Demo::AttachmentRuntimeIds {
extern Viper::UUId const Player_Properties;
} // ns Demo::AttachmentRuntimeIds

#endif
