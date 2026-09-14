// THE ONE DRIVER UNIT. `Demo::PlayerKey`, not `Service::Demo::PlayerKey`: the
// namespace is stated once, where it belongs. This is what the 99% gain.
//
// What they pay is one more header than today -- the base unit -- reached
// transitively, so a consumer still writes a single include.

#ifndef Demo_Data_hpp
#define Demo_Data_hpp

#include "Service_Data.hpp"         // the base unit
#include "Viper_UUId.hpp"

namespace Demo {

class PlayerKey final { /* ... unchanged ... */ };
class Vector3 final { /* ... unchanged ... */ };

} // ns Demo

template<> struct std::hash<Demo::PlayerKey> { /* ... */ };

#endif
