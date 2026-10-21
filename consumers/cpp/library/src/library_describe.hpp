// The library: what it does with what it reads. It reads through the reading usage only,
// shop::store::reads, so it compiles in an application of either database.
#pragma once

#include "Viper_AttachmentGetting.hpp"

#include <memory>
#include <string>

namespace library {

// Every product and part of a base, one line each, in key order: the same text for the same
// documents, whichever base holds them.
std::string describe(std::shared_ptr<Viper::AttachmentGetting> const & getting);

} // namespace library
