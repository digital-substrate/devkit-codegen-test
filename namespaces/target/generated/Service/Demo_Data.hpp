// unité Demo — les types qu'elle déclare.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/service/Service.dsm.json by kibo-2.0.0.jar

#ifndef Demo_Data_hpp
#define Demo_Data_hpp


#include "Service_AnyConcept.hpp"

#include "Viper_HashAccumulator.hpp"
#include "Viper_Blob.hpp"
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

namespace Demo {

/**  */
class PlayerKey final {
public:
    PlayerKey() = default;
    PlayerKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept;

    static PlayerKey create();

    Viper::UUId const & instanceId() const noexcept;
    Viper::UUId const & runtimeId() const noexcept;

    bool isValid() const noexcept;
    Service::AnyConceptKey toAny() const noexcept;
    static std::optional<PlayerKey> from(Service::AnyConceptKey const & key) noexcept;


private:
    Viper::UUId _instanceId{};
    Viper::UUId _runtimeId{};
};

bool operator==(PlayerKey const &, PlayerKey const &) noexcept;
bool operator!=(PlayerKey const &, PlayerKey const &) noexcept;
bool operator<(PlayerKey const &, PlayerKey const &) noexcept;

void hash(Viper::Hash::Accumulator & h, PlayerKey const & value) noexcept;


/**  */
enum class Level {
    Beginner,
    Intermediate,
    Expert
};

void hash(Viper::Hash::Accumulator & h, Level value) noexcept;

/**  */
struct PlayerProperty final {
    std::string nickname{};
    Level level{};
};

bool operator==(PlayerProperty const &, PlayerProperty const &) noexcept;
bool operator!=(PlayerProperty const &, PlayerProperty const &) noexcept;
bool operator<(PlayerProperty const &, PlayerProperty const &) noexcept;

void hash(Viper::Hash::Accumulator & h, PlayerProperty const & value) noexcept;

/**  */
struct Vector3 final {
    float x{};
    float y{};
    float z{};
};

bool operator==(Vector3 const &, Vector3 const &) noexcept;
bool operator!=(Vector3 const &, Vector3 const &) noexcept;
bool operator<(Vector3 const &, Vector3 const &) noexcept;

void hash(Viper::Hash::Accumulator & h, Vector3 const & value) noexcept;

} // namespace Demo

template<> struct std::hash<Demo::PlayerKey> {
    std::size_t operator()(Demo::PlayerKey const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Demo::PlayerProperty> {
    std::size_t operator()(Demo::PlayerProperty const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Demo::Vector3> {
    std::size_t operator()(Demo::Vector3 const & v) const noexcept { return Viper::Hash::of(v); }
};

#endif