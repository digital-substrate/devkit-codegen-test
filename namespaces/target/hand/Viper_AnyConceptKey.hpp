#ifndef Viper_AnyConceptKey_hpp
#define Viper_AnyConceptKey_hpp
#include "Viper_UUId.hpp"
namespace Viper {
class AnyConceptKey final {
public:
    AnyConceptKey() = default;
    AnyConceptKey(UUId const & i, UUId const & r) noexcept : _i{i}, _r{r} {}
    UUId const & instanceId() const noexcept { return _i; }
    UUId const & runtimeId() const noexcept { return _r; }
private:
    UUId _i{}, _r{};
};
}
#endif
