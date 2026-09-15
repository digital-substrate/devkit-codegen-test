// Le hachage d'une Value par le runtime : un hacheur, une passe, un hexdigest.
#ifndef Viper_Hasher_hpp
#define Viper_Hasher_hpp
#include "Viper_Values.hpp"
#include <memory>
#include <string>
namespace Viper {
class Hashing {
public:
    virtual ~Hashing() = default;
    virtual std::string hexDigest() const = 0;
};
class HashSHA1 { public: static std::shared_ptr<Hashing> make(); };
namespace ValueHasher { void hash(std::shared_ptr<Value const> const & value, std::shared_ptr<Hashing> const & hashing); }
}
#endif
