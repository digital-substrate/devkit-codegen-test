// unité ModelC — les types qu'elle déclare.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#ifndef ModelC_Data_hpp
#define ModelC_Data_hpp


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

namespace ModelC {

/** Something a projection can point at, and nothing else refers to. */
class MarkerKey final {
public:
    MarkerKey() = default;
    MarkerKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept;

    /// Reconstruire une clé depuis l'identifiant d'instance seul : l'identifiant
    /// d'exécution est celui de ce concept-ci.
    ///
    /// EXPLICITE, LÀ OÙ LE PACK LAISSAIT LA CONVERSION IMPLICITE. Toutes les clés du modèle
    /// ont la même forme, donc une conversion implicite depuis `UUId` fait de n'importe quel
    /// identifiant n'importe quelle clé, en silence -- ce que le typage des clés existe
    /// justement pour empêcher. `MarkerKey{id}` dit la même chose et la dit exprès.
    explicit MarkerKey(Viper::UUId const & instanceId) noexcept;

    static MarkerKey create();

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