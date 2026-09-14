// Mono, same shape as multi, no special case.

#ifndef Demo_Path_hpp
#define Demo_Path_hpp

#include "Viper_Path.hpp"
#include <memory>

namespace Demo::Path::Vector3 {
std::shared_ptr<Viper::Path const> const & x();
// ... unchanged ...
} // ns

#endif
