// unité ModelB — les types qu'elle déclare.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#ifndef ModelB_Data_hpp
#define ModelB_Data_hpp


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

namespace ModelB {

/** A material, as ModelB understands one. */
class MaterialKey final {
public:
    MaterialKey() = default;
    MaterialKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept;

    /// Reconstruire une clé depuis l'identifiant d'instance seul : l'identifiant
    /// d'exécution est celui de ce concept-ci.
    ///
    /// EXPLICITE, LÀ OÙ LE PACK LAISSAIT LA CONVERSION IMPLICITE. Toutes les clés du modèle
    /// ont la même forme, donc une conversion implicite depuis `UUId` fait de n'importe quel
    /// identifiant n'importe quelle clé, en silence -- ce que le typage des clés existe
    /// justement pour empêcher. `MaterialKey{id}` dit la même chose et la dit exprès.
    explicit MaterialKey(Viper::UUId const & instanceId) noexcept;

    static MaterialKey create();

    Viper::UUId const & instanceId() const noexcept;
    Viper::UUId const & runtimeId() const noexcept;

    /// Ce que la clé désigne, dit en clair, et si le modèle le connaît.
    ///
    /// LA RÉPONSE VIENT DES DÉFINITIONS, PAS DE LA GÉNÉRATION. Un identifiant d'exécution
    /// peut être celui d'un descendant qui n'existait pas quand ce fichier a été écrit ;
    /// les définitions embarquées, elles, sont lues à l'exécution et savent le nommer.
    std::string description() const;
    bool isKnown() const;

    bool isValid() const noexcept;
    Topology::AnyConceptKey toAny() const noexcept;
    static std::optional<MaterialKey> from(Topology::AnyConceptKey const & key) noexcept;


private:
    Viper::UUId _instanceId{};
    Viper::UUId _runtimeId{};
};

bool operator==(MaterialKey const &, MaterialKey const &) noexcept;
bool operator!=(MaterialKey const &, MaterialKey const &) noexcept;
bool operator<(MaterialKey const &, MaterialKey const &) noexcept;

void hash(Viper::Hash::Accumulator & h, MaterialKey const & value) noexcept;



/** Colour in floating point -- the same name as ModelA::Colour, a different type. */
struct Colour final {
    float r{};
    float g{};
    float b{};
};

bool operator==(Colour const &, Colour const &) noexcept;
bool operator!=(Colour const &, Colour const &) noexcept;
bool operator<(Colour const &, Colour const &) noexcept;

void hash(Viper::Hash::Accumulator & h, Colour const & value) noexcept;

} // namespace ModelB

template<> struct std::hash<ModelB::MaterialKey> {
    std::size_t operator()(ModelB::MaterialKey const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<ModelB::Colour> {
    std::size_t operator()(ModelB::Colour const & v) const noexcept { return Viper::Hash::of(v); }
};

#endif