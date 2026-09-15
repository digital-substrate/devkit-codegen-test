#ifndef Viper_Json_hpp
#define Viper_Json_hpp
#include "Viper_Types.hpp"
#include "Viper_Values.hpp"
#include <memory>
#include <string>
namespace Viper {
class Definitions;
namespace JsonValueEncoder { std::string json_encode(std::shared_ptr<Value const> const & value); }
namespace JsonValueDecoder {
std::shared_ptr<Value> json_decode(std::string const & json,
                                   std::shared_ptr<Type> const & type,
                                   std::shared_ptr<Definitions const> const & definitions);
}
}
#endif
