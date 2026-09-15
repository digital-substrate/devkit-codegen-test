#ifndef Viper_Assert_hpp
#define Viper_Assert_hpp
#include <stdexcept>
#include <string>
#define VIPER_ASSERT(component, condition) \
    do { if (!(condition)) throw std::runtime_error(std::string(component) + ": " #condition); } while (false)
#endif
