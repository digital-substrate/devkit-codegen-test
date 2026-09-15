// unité ModelA — l'implémentation de ses types.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "ModelA_Data.hpp"

#include "ModelA_Model.hpp"
#include "Topology_Codec.hpp"

namespace ModelA {

// ── Material ──

MaterialKey::MaterialKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept
: _instanceId{instanceId}, _runtimeId{runtimeId} {}

MaterialKey::MaterialKey(Viper::UUId const & instanceId) noexcept
: _instanceId{instanceId}, _runtimeId{RuntimeIds::Material} {}

MaterialKey MaterialKey::create() { return {Viper::UUId::create(), RuntimeIds::Material}; }

Viper::UUId const & MaterialKey::instanceId() const noexcept { return _instanceId; }
Viper::UUId const & MaterialKey::runtimeId() const noexcept { return _runtimeId; }
bool MaterialKey::isValid() const noexcept { return _instanceId.isValid(); }

std::string MaterialKey::description() const { return Topology::Codec::description(toAny()); }
bool MaterialKey::isKnown() const { return Topology::Codec::isKnown(toAny()); }
Topology::AnyConceptKey MaterialKey::toAny() const noexcept { return {_instanceId, _runtimeId}; }

/// Rétrécir depuis la clé non typée : le modèle répond, parce que lui seul connaît la
/// hiérarchie -- y compris ce qui a été déclaré après cette unité.
std::optional<MaterialKey> MaterialKey::from(Topology::AnyConceptKey const & key) noexcept {
    if (!Topology::Codec::isMember(key, conceptType(Viper::Codec::tag<MaterialKey>{})))
        return std::nullopt;

    return MaterialKey{key.instanceId(), key.runtimeId()};
}

bool operator==(MaterialKey const & l, MaterialKey const & r) noexcept {
    return l.instanceId() == r.instanceId() && l.runtimeId() == r.runtimeId();
}
bool operator!=(MaterialKey const & l, MaterialKey const & r) noexcept { return !(l == r); }
bool operator<(MaterialKey const & l, MaterialKey const & r) noexcept {
    if (l.instanceId() != r.instanceId())
        return l.instanceId() < r.instanceId();
    return l.runtimeId() < r.runtimeId();
}

void hash(Viper::Hash::Accumulator & h, MaterialKey const & value) noexcept {
    hash(h, value.instanceId());
    hash(h, value.runtimeId());
}


// ── Finish ──

void hash(Viper::Hash::Accumulator & h, Finish value) noexcept {
    hash(h, static_cast<std::uint8_t>(value));
}

// ── Colour ──

bool operator==(Colour const & l, Colour const & r) noexcept {
    return l.r == r.r
        && l.g == r.g
        && l.b == r.b;
}
bool operator!=(Colour const & l, Colour const & r) noexcept { return !(l == r); }
bool operator<(Colour const & l, Colour const & r) noexcept {
    if (l.r < r.r) return true;
    if (r.r < l.r) return false;
    if (l.g < r.g) return true;
    if (r.g < l.g) return false;
    return l.b < r.b;
}

void hash(Viper::Hash::Accumulator & h, Colour const & value) noexcept {
    hash(h, value.r);
    hash(h, value.g);
    hash(h, value.b);
}

} // namespace ModelA