// THE BASE UNIT, in mono exactly as in multi. No special case: one layout.

#ifndef Service_Data_hpp
#define Service_Data_hpp

#include "Viper_UUId.hpp"

namespace Service {

class AnyConceptKey final { /* ... unchanged ... */ };

} // ns Service

template<> struct std::hash<Service::AnyConceptKey> { /* ... */ };

#endif
