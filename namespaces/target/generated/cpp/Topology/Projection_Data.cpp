// unité Projection — l'implémentation de ses types.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "Projection_Data.hpp"

#include "Projection_Model.hpp"
#include "Topology_Codec.hpp"

namespace Projection {

// ── Link ──

LinkKey::LinkKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept
: _instanceId{instanceId}, _runtimeId{runtimeId} {}

LinkKey::LinkKey(Viper::UUId const & instanceId) noexcept
: _instanceId{instanceId}, _runtimeId{RuntimeIds::Link} {}

LinkKey LinkKey::create() { return {Viper::UUId::create(), RuntimeIds::Link}; }

Viper::UUId const & LinkKey::instanceId() const noexcept { return _instanceId; }
Viper::UUId const & LinkKey::runtimeId() const noexcept { return _runtimeId; }
bool LinkKey::isValid() const noexcept { return _instanceId.isValid(); }

std::string LinkKey::description() const { return Topology::Codec::description(toAny()); }
bool LinkKey::isKnown() const { return Topology::Codec::isKnown(toAny()); }
Topology::AnyConceptKey LinkKey::toAny() const noexcept { return {_instanceId, _runtimeId}; }

/// Rétrécir depuis la clé non typée : le modèle répond, parce que lui seul connaît la
/// hiérarchie -- y compris ce qui a été déclaré après cette unité.
std::optional<LinkKey> LinkKey::from(Topology::AnyConceptKey const & key) noexcept {
    if (!Topology::Codec::isMember(key, conceptType(Viper::Codec::tag<LinkKey>{})))
        return std::nullopt;

    return LinkKey{key.instanceId(), key.runtimeId()};
}

bool operator==(LinkKey const & l, LinkKey const & r) noexcept {
    return l.instanceId() == r.instanceId() && l.runtimeId() == r.runtimeId();
}
bool operator!=(LinkKey const & l, LinkKey const & r) noexcept { return !(l == r); }
bool operator<(LinkKey const & l, LinkKey const & r) noexcept {
    if (l.instanceId() != r.instanceId())
        return l.instanceId() < r.instanceId();
    return l.runtimeId() < r.runtimeId();
}

void hash(Viper::Hash::Accumulator & h, LinkKey const & value) noexcept {
    hash(h, value.instanceId());
    hash(h, value.runtimeId());
}

// ── DerivedMaterial ──

DerivedMaterialKey::DerivedMaterialKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept
: _instanceId{instanceId}, _runtimeId{runtimeId} {}

DerivedMaterialKey::DerivedMaterialKey(Viper::UUId const & instanceId) noexcept
: _instanceId{instanceId}, _runtimeId{RuntimeIds::DerivedMaterial} {}

DerivedMaterialKey DerivedMaterialKey::create() { return {Viper::UUId::create(), RuntimeIds::DerivedMaterial}; }

Viper::UUId const & DerivedMaterialKey::instanceId() const noexcept { return _instanceId; }
Viper::UUId const & DerivedMaterialKey::runtimeId() const noexcept { return _runtimeId; }
bool DerivedMaterialKey::isValid() const noexcept { return _instanceId.isValid(); }

std::string DerivedMaterialKey::description() const { return Topology::Codec::description(toAny()); }
bool DerivedMaterialKey::isKnown() const { return Topology::Codec::isKnown(toAny()); }

/// L'élargissement ne perd rien et ne peut pas échouer : l'identifiant d'exécution reste
/// celui du concept réel, et c'est pourquoi le retour est possible ensuite.
DerivedMaterialKey::operator ModelA::MaterialKey() const noexcept { return {_instanceId, _runtimeId}; }

ModelA::MaterialKey DerivedMaterialKey::toParentKey() const noexcept { return {_instanceId, _runtimeId}; }

Topology::AnyConceptKey DerivedMaterialKey::toAny() const noexcept { return {_instanceId, _runtimeId}; }

/// Rétrécir depuis la clé non typée : le modèle répond, parce que lui seul connaît la
/// hiérarchie -- y compris ce qui a été déclaré après cette unité.
std::optional<DerivedMaterialKey> DerivedMaterialKey::from(Topology::AnyConceptKey const & key) noexcept {
    if (!Topology::Codec::isMember(key, conceptType(Viper::Codec::tag<DerivedMaterialKey>{})))
        return std::nullopt;

    return DerivedMaterialKey{key.instanceId(), key.runtimeId()};
}

bool operator==(DerivedMaterialKey const & l, DerivedMaterialKey const & r) noexcept {
    return l.instanceId() == r.instanceId() && l.runtimeId() == r.runtimeId();
}
bool operator!=(DerivedMaterialKey const & l, DerivedMaterialKey const & r) noexcept { return !(l == r); }
bool operator<(DerivedMaterialKey const & l, DerivedMaterialKey const & r) noexcept {
    if (l.instanceId() != r.instanceId())
        return l.instanceId() < r.instanceId();
    return l.runtimeId() < r.runtimeId();
}

void hash(Viper::Hash::Accumulator & h, DerivedMaterialKey const & value) noexcept {
    hash(h, value.instanceId());
    hash(h, value.runtimeId());
}



// ── Pair ──

bool operator==(Pair const & l, Pair const & r) noexcept {
    return l.a == r.a
        && l.b == r.b;
}
bool operator!=(Pair const & l, Pair const & r) noexcept { return !(l == r); }
bool operator<(Pair const & l, Pair const & r) noexcept {
    if (l.a < r.a) return true;
    if (r.a < l.a) return false;
    return l.b < r.b;
}

void hash(Viper::Hash::Accumulator & h, Pair const & value) noexcept {
    hash(h, value.a);
    hash(h, value.b);
}

} // namespace Projection