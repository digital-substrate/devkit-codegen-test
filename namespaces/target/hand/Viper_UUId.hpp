#ifndef Viper_UUId_hpp
#define Viper_UUId_hpp
#include "Viper_Ordered.hpp"
#include <cstddef>
#include <cstdint>
#include <string>
namespace Viper {
struct UUId {
    std::uint64_t hi{}, lo{};

    static UUId create();
    static UUId const & Invalid();
    static UUId parse(std::string const & text);

    bool isValid() const noexcept { return hi != 0 || lo != 0; }
    std::string uuidString() const;
    std::size_t hash() const noexcept;
    Ordered compare(UUId const & o) const noexcept;

    bool operator==(UUId const & o) const noexcept { return hi == o.hi && lo == o.lo; }
    bool operator!=(UUId const & o) const noexcept { return !(*this == o); }
    bool operator<(UUId const & o) const noexcept { return hi != o.hi ? hi < o.hi : lo < o.lo; }
};
}
#endif
