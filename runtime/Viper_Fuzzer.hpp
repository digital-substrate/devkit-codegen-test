// Le fabricant de valeurs aléatoires du runtime : il part d'un descripteur de type et rend
// une Value. C'est lui qui rend tout le fuzz générique -- une unité n'a rien à fabriquer,
// elle fournit déjà son descripteur.
#ifndef Viper_Fuzzer_hpp
#define Viper_Fuzzer_hpp
#include "Viper_Types.hpp"
#include "Viper_Values.hpp"
#include <cstdint>
#include <memory>
namespace Viper {
class Definitions;
class Fuzzer final {
public:
    static std::shared_ptr<Fuzzer> make(std::shared_ptr<Definitions const> const & definitions);
    static std::shared_ptr<Fuzzer> make(std::shared_ptr<Definitions const> const & definitions, std::uint64_t seed);
    std::shared_ptr<Value> fuzzType(std::shared_ptr<Type> const & type);
};
}
#endif
