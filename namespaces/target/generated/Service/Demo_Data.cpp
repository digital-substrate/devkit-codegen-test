// unité Demo — l'implémentation de ses types.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/service/Service.dsm.json by kibo-2.0.0.jar

#include "Demo_Data.hpp"

#include "Demo_Model.hpp"
#include "Service_Codec.hpp"

namespace Demo {

// ── Player ──

PlayerKey::PlayerKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept
: _instanceId{instanceId}, _runtimeId{runtimeId} {}

PlayerKey PlayerKey::create() { return {Viper::UUId::create(), RuntimeIds::Player}; }

Viper::UUId const & PlayerKey::instanceId() const noexcept { return _instanceId; }
Viper::UUId const & PlayerKey::runtimeId() const noexcept { return _runtimeId; }
bool PlayerKey::isValid() const noexcept { return _instanceId.isValid(); }
Service::AnyConceptKey PlayerKey::toAny() const noexcept { return {_instanceId, _runtimeId}; }

/// Rétrécir depuis la clé non typée : le modèle répond, parce que lui seul connaît la
/// hiérarchie -- y compris ce qui a été déclaré après cette unité.
std::optional<PlayerKey> PlayerKey::from(Service::AnyConceptKey const & key) noexcept {
    if (!Service::Codec::isMember(key, conceptType(Viper::Codec::tag<PlayerKey>{})))
        return std::nullopt;

    return PlayerKey{key.instanceId(), key.runtimeId()};
}

bool operator==(PlayerKey const & l, PlayerKey const & r) noexcept {
    return l.instanceId() == r.instanceId() && l.runtimeId() == r.runtimeId();
}
bool operator!=(PlayerKey const & l, PlayerKey const & r) noexcept { return !(l == r); }
bool operator<(PlayerKey const & l, PlayerKey const & r) noexcept {
    if (l.instanceId() != r.instanceId())
        return l.instanceId() < r.instanceId();
    return l.runtimeId() < r.runtimeId();
}

void hash(Viper::Hash::Accumulator & h, PlayerKey const & value) noexcept {
    hash(h, value.instanceId());
    hash(h, value.runtimeId());
}


// ── Level ──

void hash(Viper::Hash::Accumulator & h, Level value) noexcept {
    hash(h, static_cast<std::uint8_t>(value));
}

// ── PlayerProperty ──

bool operator==(PlayerProperty const & l, PlayerProperty const & r) noexcept {
    return l.nickname == r.nickname
        && l.level == r.level;
}
bool operator!=(PlayerProperty const & l, PlayerProperty const & r) noexcept { return !(l == r); }
bool operator<(PlayerProperty const & l, PlayerProperty const & r) noexcept {
    if (l.nickname < r.nickname) return true;
    if (r.nickname < l.nickname) return false;
    return l.level < r.level;
}

void hash(Viper::Hash::Accumulator & h, PlayerProperty const & value) noexcept {
    hash(h, value.nickname);
    hash(h, value.level);
}

// ── Vector3 ──

bool operator==(Vector3 const & l, Vector3 const & r) noexcept {
    return l.x == r.x
        && l.y == r.y
        && l.z == r.z;
}
bool operator!=(Vector3 const & l, Vector3 const & r) noexcept { return !(l == r); }
bool operator<(Vector3 const & l, Vector3 const & r) noexcept {
    if (l.x < r.x) return true;
    if (r.x < l.x) return false;
    if (l.y < r.y) return true;
    if (r.y < l.y) return false;
    return l.z < r.z;
}

void hash(Viper::Hash::Accumulator & h, Vector3 const & value) noexcept {
    hash(h, value.x);
    hash(h, value.y);
    hash(h, value.z);
}

} // namespace Demo