#ifndef Viper_UUId_hpp
#define Viper_UUId_hpp
#include <cstdint>
#include <cstddef>
namespace Viper {
struct UUId {
    std::uint64_t hi{}, lo{};
    bool operator==(UUId const & o) const noexcept { return hi == o.hi && lo == o.lo; }
    bool operator<(UUId const & o) const noexcept { return hi != o.hi ? hi < o.hi : lo < o.lo; }
};
}
#endif
