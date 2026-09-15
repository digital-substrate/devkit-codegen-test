// unité Projection — les types qu'elle déclare.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#ifndef Projection_Data_hpp
#define Projection_Data_hpp

#include "ModelB_Data.hpp"
#include "ModelA_Data.hpp"

#include "Topology_AnyConcept.hpp"

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

namespace Projection {

/** What one link between two driver materials is. */
class LinkKey final {
public:
    LinkKey() = default;
    LinkKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept;

    static LinkKey create();

    Viper::UUId const & instanceId() const noexcept;
    Viper::UUId const & runtimeId() const noexcept;

    bool isValid() const noexcept;
    Topology::AnyConceptKey toAny() const noexcept;
    static std::optional<LinkKey> from(Topology::AnyConceptKey const & key) noexcept;


private:
    Viper::UUId _instanceId{};
    Viper::UUId _runtimeId{};
};

bool operator==(LinkKey const &, LinkKey const &) noexcept;
bool operator!=(LinkKey const &, LinkKey const &) noexcept;
bool operator<(LinkKey const &, LinkKey const &) noexcept;

void hash(Viper::Hash::Accumulator & h, LinkKey const & value) noexcept;

/** A concept whose parent lives in another namespace. */
class DerivedMaterialKey final {
public:
    DerivedMaterialKey() = default;
    DerivedMaterialKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept;

    static DerivedMaterialKey create();

    Viper::UUId const & instanceId() const noexcept;
    Viper::UUId const & runtimeId() const noexcept;

    bool isValid() const noexcept;
    /// Élargir vers le parent. Implicite, parce que `is a` n'est pas une demande : partout
    /// où le parent est attendu, le dérivé passe.
    operator ModelA::MaterialKey() const noexcept;

    /// Et la même, nommée. DEUX FORMES DE LA MÊME CHOSE, ET LES DEUX SERVENT : l'implicite
    /// pour l'appelant qui passe la clé, la nommée pour celui qui la range ou l'écrit dans
    /// une expression où la conversion ne se déclencherait pas.
    ModelA::MaterialKey toParentKey() const noexcept;
    Topology::AnyConceptKey toAny() const noexcept;
    static std::optional<DerivedMaterialKey> from(Topology::AnyConceptKey const & key) noexcept;


private:
    Viper::UUId _instanceId{};
    Viper::UUId _runtimeId{};
};

bool operator==(DerivedMaterialKey const &, DerivedMaterialKey const &) noexcept;
bool operator!=(DerivedMaterialKey const &, DerivedMaterialKey const &) noexcept;
bool operator<(DerivedMaterialKey const &, DerivedMaterialKey const &) noexcept;

void hash(Viper::Hash::Accumulator & h, DerivedMaterialKey const & value) noexcept;



/** Two keys from two namespaces in one structure -- the key<NS::C> edge. */
struct Pair final {
    ModelA::MaterialKey a{};
    ModelB::MaterialKey b{};
};

bool operator==(Pair const &, Pair const &) noexcept;
bool operator!=(Pair const &, Pair const &) noexcept;
bool operator<(Pair const &, Pair const &) noexcept;

void hash(Viper::Hash::Accumulator & h, Pair const & value) noexcept;

} // namespace Projection

template<> struct std::hash<Projection::LinkKey> {
    std::size_t operator()(Projection::LinkKey const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Projection::DerivedMaterialKey> {
    std::size_t operator()(Projection::DerivedMaterialKey const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Projection::Pair> {
    std::size_t operator()(Projection::Pair const & v) const noexcept { return Viper::Hash::of(v); }
};

#endif