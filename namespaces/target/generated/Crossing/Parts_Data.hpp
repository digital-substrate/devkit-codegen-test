// Parts — the types this namespace declares.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

#ifndef Parts_Data_hpp
#define Parts_Data_hpp


#include "Crossing_AnyConcept.hpp"

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

namespace Parts {

/** Le même nom que Core::Thing, et rien de commun. */
class ThingKey final {
public:
    ThingKey() = default;
    ThingKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept;

    static ThingKey create();

    Viper::UUId const & instanceId() const noexcept;
    Viper::UUId const & runtimeId() const noexcept;

    bool isValid() const noexcept;
    Crossing::AnyConceptKey toAny() const noexcept;
    static std::optional<ThingKey> from(Crossing::AnyConceptKey const & key) noexcept;


private:
    Viper::UUId _instanceId{};
    Viper::UUId _runtimeId{};
};

bool operator==(ThingKey const &, ThingKey const &) noexcept;
bool operator!=(ThingKey const &, ThingKey const &) noexcept;
bool operator<(ThingKey const &, ThingKey const &) noexcept;

void hash(Viper::Hash::Accumulator & h, ThingKey const & value) noexcept;


/** Le même nom que Core::Grade, des cases différentes. */
enum class Grade {
    Soft,
    Hard
};

void hash(Viper::Hash::Accumulator & h, Grade value) noexcept;

/** Le même nom que Core::Colour, en virgule flottante. */
struct Colour final {
    float r{};
    float g{};
    float b{};
};

bool operator==(Colour const &, Colour const &) noexcept;
bool operator!=(Colour const &, Colour const &) noexcept;
bool operator<(Colour const &, Colour const &) noexcept;

void hash(Viper::Hash::Accumulator & h, Colour const & value) noexcept;

} // namespace Parts

template<> struct std::hash<Parts::ThingKey> {
    std::size_t operator()(Parts::ThingKey const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Parts::Colour> {
    std::size_t operator()(Parts::Colour const & v) const noexcept { return Viper::Hash::of(v); }
};

#endif