// A UNIT WITH NOTHING TO EMIT, and a file all the same.
//
// Annotations declares one attachment and no concept, structure or enumeration, so
// it contributes nothing to Data. The header exists anyway: every unit has a file
// for every feature it is rendered for, so a path can be written without first
// asking what the model happens to contain. A build lists
// <unit>/<unit>_<feature>.hpp unconditionally, and the day this namespace gains a
// concept its consumers already include it.
//
// Its own content lands in Annotations_Attachments.hpp, which is not empty.

#ifndef Annotations_Data_hpp
#define Annotations_Data_hpp

#include "Topology_Data.hpp"

namespace Annotations {

} // ns Annotations

#endif
