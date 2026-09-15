// unité ModelC — les types qu'elle déclare.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#ifndef ModelC_Data_hpp
#define ModelC_Data_hpp


#include "Topology_AnyConcept.hpp"

#include "Viper_Hash.hpp"
#include "Viper_Scalars.hpp"
#include "Viper_UUId.hpp"

#include <array>
#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <variant>
#include <vector>
#include <functional>
#include <optional>

namespace ModelC {

/** Something a projection can point at, and nothing else refers to. */
class MarkerKey final {
public:
    MarkerKey() = default;
    MarkerKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept;

    static MarkerKey create();

    Viper::UUId const & instanceId() const noexcept;
    Viper::UUId const & runtimeId() const noexcept;

    bool isValid() const noexcept;
    Topology::AnyConceptKey toAny() const noexcept;
    static std::optional<MarkerKey> from(Topology::AnyConceptKey const & key) noexcept;


private:
    Viper::UUId _instanceId{};
    Viper::UUId _runtimeId{};
};

bool operator==(MarkerKey const &, MarkerKey const &) noexcept;
bool operator!=(MarkerKey const &, MarkerKey const &) noexcept;
bool operator<(MarkerKey const &, MarkerKey const &) noexcept;

void hash(Viper::Hash::Accumulator & h, MarkerKey const & value) noexcept;




} // namespace ModelC

template<> struct std::hash<ModelC::MarkerKey> {
    std::size_t operator()(ModelC::MarkerKey const & v) const noexcept { return Viper::Hash::of(v); }
};

#endif