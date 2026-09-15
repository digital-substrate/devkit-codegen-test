// unité ModelC — l'implémentation de ses types.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "ModelC_Data.hpp"

#include "ModelC_Model.hpp"
#include "Topology_Codec.hpp"

namespace ModelC {

// ── Marker ──

MarkerKey::MarkerKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept
: _instanceId{instanceId}, _runtimeId{runtimeId} {}

MarkerKey MarkerKey::create() { return {Viper::UUId::create(), RuntimeIds::Marker}; }

Viper::UUId const & MarkerKey::instanceId() const noexcept { return _instanceId; }
Viper::UUId const & MarkerKey::runtimeId() const noexcept { return _runtimeId; }
bool MarkerKey::isValid() const noexcept { return _instanceId.isValid(); }
Topology::AnyConceptKey MarkerKey::toAny() const noexcept { return {_instanceId, _runtimeId}; }

/// Rétrécir depuis la clé non typée : le modèle répond, parce que lui seul connaît la
/// hiérarchie -- y compris ce qui a été déclaré après cette unité.
std::optional<MarkerKey> MarkerKey::from(Topology::AnyConceptKey const & key) noexcept {
    if (!Topology::Codec::isMember(key, conceptType(Viper::Codec::tag<MarkerKey>{})))
        return std::nullopt;

    return MarkerKey{key.instanceId(), key.runtimeId()};
}

bool operator==(MarkerKey const & l, MarkerKey const & r) noexcept {
    return l.instanceId() == r.instanceId() && l.runtimeId() == r.runtimeId();
}
bool operator!=(MarkerKey const & l, MarkerKey const & r) noexcept { return !(l == r); }
bool operator<(MarkerKey const & l, MarkerKey const & r) noexcept {
    if (l.instanceId() != r.instanceId())
        return l.instanceId() < r.instanceId();
    return l.runtimeId() < r.runtimeId();
}

void hash(Viper::Hash::Accumulator & h, MarkerKey const & value) noexcept {
    hash(h, value.instanceId());
    hash(h, value.runtimeId());
}




} // namespace ModelC