#ifndef Viper_TypeErrors_hpp
#define Viper_TypeErrors_hpp
#include <cstdint>
#include <stdexcept>
#include <string>
namespace Viper::TypeErrors {
std::runtime_error invalidEnumerationIndex(std::string const & component, std::string const & type,
                                           std::string const & function, std::uint8_t index);
}
#endif
