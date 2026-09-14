// ModelB — the types this namespace declares.
//
// The symmetry with ModelA is the point, not a coincidence: it declares a Material and a
// Colour of its own, both named exactly as ModelA's, and nothing anywhere is renamed to
// keep them apart. That is what a namespace is for, and it is what the flat prefix was
// imitating.

#ifndef ModelB_Data_hpp
#define ModelB_Data_hpp

#include "Viper_AnyConceptKey.hpp"
#include "Viper_UUId.hpp"

#include <functional>
#include <optional>

namespace ModelB {

/// A material, as ModelB understands one.
class MaterialKey final {
public:
    MaterialKey() = default;
    MaterialKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept;

    static MaterialKey create();

    Viper::UUId const & instanceId() const noexcept;
    Viper::UUId const & runtimeId() const noexcept;

    bool isValid() const noexcept;

    Viper::AnyConceptKey toAny() const noexcept;
    static std::optional<MaterialKey> from(Viper::AnyConceptKey const & key) noexcept;

    std::size_t hash() const noexcept;

private:
    Viper::UUId _instanceId{};
    Viper::UUId _runtimeId{};
};

bool operator==(MaterialKey const &, MaterialKey const &) noexcept;
bool operator!=(MaterialKey const &, MaterialKey const &) noexcept;
bool operator<(MaterialKey const &, MaterialKey const &) noexcept;

/// Colour in floating point -- the same name as ModelA::Colour, a different type.
struct Colour final {
    float r{};
    float g{};
    float b{};
};

bool operator==(Colour const &, Colour const &) noexcept;
bool operator!=(Colour const &, Colour const &) noexcept;
bool operator<(Colour const &, Colour const &) noexcept;

std::size_t hash(Colour const & value) noexcept;

} // namespace ModelB

template<> struct std::hash<ModelB::MaterialKey> {
    std::size_t operator()(ModelB::MaterialKey const & v) const noexcept { return v.hash(); }
};
template<> struct std::hash<ModelB::Colour> {
    std::size_t operator()(ModelB::Colour const & v) const noexcept { return ModelB::hash(v); }
};

#endif
