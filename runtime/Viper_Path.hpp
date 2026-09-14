// L'adresse d'une position dans un document. Signatures reprises de
// com.digitalsubstrate.viper/src/Viper/Viper_Path.hpp, réduites à ce que les références
// touchent.
#ifndef Viper_Path_hpp
#define Viper_Path_hpp
#include <cstddef>
#include <memory>
#include <string>
namespace Viper {
class Path final {
public:
    static std::shared_ptr<Path> make();
    static std::shared_ptr<Path> makeField(std::string const & fieldName);
    static std::shared_ptr<Path> makeIndex(std::size_t value);
};
}
#endif
