// Projection — the types this namespace declares.
//
// The composing namespace: it owns Link and DerivedMaterial, and its Pair holds keys
// from two others. Hand-written from the model.

#ifndef Projection_Data_hpp
#define Projection_Data_hpp

#include "ModelA_Data.hpp"          // DerivedMaterial's parent, and Pair's first field
#include "ModelB_Data.hpp"          // Pair's second field

#include "Viper_AnyConceptKey.hpp"
#include "Viper_UUId.hpp"

#include <functional>
#include <optional>

namespace Projection {

/// What one link between two driver materials is.
class LinkKey final {
public:
    LinkKey() = default;
    LinkKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept;

    static LinkKey create();

    Viper::UUId const & instanceId() const noexcept;
    Viper::UUId const & runtimeId() const noexcept;

    bool isValid() const noexcept;

    Viper::AnyConceptKey toAny() const noexcept;
    static std::optional<LinkKey> from(Viper::AnyConceptKey const & key) noexcept;

    std::size_t hash() const noexcept;

private:
    Viper::UUId _instanceId{};
    Viper::UUId _runtimeId{};
};

/// A concept whose parent lives in another namespace.
///
/// `is a` means what it says, so this converts to its parent without being asked. The
/// conversion is lossless: both keys carry the same instance and the same runtime id,
/// and it is the runtime id that still names DerivedMaterial after the widening. That is
/// the whole reason the runtime id is stored rather than being a property of the type --
/// see the note in ModelA_Data.hpp.
class DerivedMaterialKey final {
public:
    DerivedMaterialKey() = default;
    DerivedMaterialKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept;

    static DerivedMaterialKey create();

    Viper::UUId const & instanceId() const noexcept;
    Viper::UUId const & runtimeId() const noexcept;

    bool isValid() const noexcept;

    /// Widen to the parent concept. Implicit, because `is a` is not a request.
    operator ModelA::MaterialKey() const noexcept;

    Viper::AnyConceptKey toAny() const noexcept;
    static std::optional<DerivedMaterialKey> from(Viper::AnyConceptKey const & key) noexcept;

    std::size_t hash() const noexcept;

private:
    Viper::UUId _instanceId{};
    Viper::UUId _runtimeId{};
};

/// Two keys from two namespaces in one structure.
///
/// Nothing here is qualified because it has to be disambiguated -- `a` and `b` are
/// plainly different types. It is qualified because the types are not Projection's, and
/// that is exactly what a reader wants to see at a composition site.
struct Pair final {
    ModelA::MaterialKey a{};
    ModelB::MaterialKey b{};
};

bool operator==(LinkKey const &, LinkKey const &) noexcept;
bool operator!=(LinkKey const &, LinkKey const &) noexcept;
bool operator<(LinkKey const &, LinkKey const &) noexcept;

bool operator==(DerivedMaterialKey const &, DerivedMaterialKey const &) noexcept;
bool operator!=(DerivedMaterialKey const &, DerivedMaterialKey const &) noexcept;
bool operator<(DerivedMaterialKey const &, DerivedMaterialKey const &) noexcept;

bool operator==(Pair const &, Pair const &) noexcept;
bool operator!=(Pair const &, Pair const &) noexcept;
bool operator<(Pair const &, Pair const &) noexcept;

std::size_t hash(Pair const & value) noexcept;

} // namespace Projection

template<> struct std::hash<Projection::LinkKey> {
    std::size_t operator()(Projection::LinkKey const & v) const noexcept { return v.hash(); }
};
template<> struct std::hash<Projection::DerivedMaterialKey> {
    std::size_t operator()(Projection::DerivedMaterialKey const & v) const noexcept { return v.hash(); }
};
template<> struct std::hash<Projection::Pair> {
    std::size_t operator()(Projection::Pair const & v) const noexcept { return Projection::hash(v); }
};

#endif
