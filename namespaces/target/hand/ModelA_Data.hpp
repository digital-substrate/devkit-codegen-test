// ModelA — the types this namespace declares.
//
// Hand-written, from the model, without looking at what the generator currently emits.
// This is the reference the templated feature must reproduce, not the other way round.

#ifndef ModelA_Data_hpp
#define ModelA_Data_hpp

#include "Viper_AnyConceptKey.hpp"
#include "Viper_UUId.hpp"

#include <cstdint>
#include <functional>
#include <optional>

namespace ModelA {

/// A material, as ModelA understands one.
///
/// A handle, not the thing: it names an instance, and the instance lives in a database.
/// Value semantics throughout — copy it, compare it, use it as a key in a container.
class MaterialKey final {
public:
    MaterialKey() = default;
    MaterialKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept;

    /// A key on a new instance. The instance does not exist until something writes it.
    static MaterialKey create();

    /// Identifies the instance.
    Viper::UUId const & instanceId() const noexcept;

    /// Identifies the concept the instance actually is.
    ///
    /// Stored, not a property of the type, and the reason is inheritance: a MaterialKey
    /// may name an instance of any concept derived from Material, and its runtime id is
    /// that concept's. Making it static would be smaller and would make toAny() lie
    /// after every widening. ModelA alone cannot show this -- Projection's
    /// DerivedMaterial does.
    Viper::UUId const & runtimeId() const noexcept;

    bool isValid() const noexcept;

    /// Widen to the untyped key, which keeps the runtime id alongside the instance id.
    Viper::AnyConceptKey toAny() const noexcept;

    /// Narrow back. Empty when the key names an instance of another concept — which is
    /// why this returns an optional and the widening above does not.
    static std::optional<MaterialKey> from(Viper::AnyConceptKey const & key) noexcept;

    std::size_t hash() const noexcept;

private:
    Viper::UUId _instanceId{};
    Viper::UUId _runtimeId{};
};

bool operator==(MaterialKey const & lhs, MaterialKey const & rhs) noexcept;
bool operator!=(MaterialKey const & lhs, MaterialKey const & rhs) noexcept;
bool operator<(MaterialKey const & lhs, MaterialKey const & rhs) noexcept;

/// Colour in 8-bit channels.
///
/// Plain data: the model says three fields, so it is an aggregate and brace-initialises.
/// ModelB declares a Colour too, in floating point; the two are different types with the
/// same name, and neither is renamed.
struct Colour final {
    std::uint8_t r{};
    std::uint8_t g{};
    std::uint8_t b{};
};

bool operator==(Colour const & lhs, Colour const & rhs) noexcept;
bool operator!=(Colour const & lhs, Colour const & rhs) noexcept;
bool operator<(Colour const & lhs, Colour const & rhs) noexcept;

std::size_t hash(Colour const & value) noexcept;

} // namespace ModelA

template<>
struct std::hash<ModelA::MaterialKey> {
    std::size_t operator()(ModelA::MaterialKey const & v) const noexcept { return v.hash(); }
};

template<>
struct std::hash<ModelA::Colour> {
    std::size_t operator()(ModelA::Colour const & v) const noexcept { return ModelA::hash(v); }
};

#endif
