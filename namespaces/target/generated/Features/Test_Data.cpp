// unité Test — l'implémentation de ses types.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/features/Features.dsm.json by kibo-2.0.0.jar

#include "Test_Data.hpp"

#include "Test_Model.hpp"
#include "Features_Codec.hpp"

namespace Test {

// ── ConceptA ──

ConceptAKey::ConceptAKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept
: _instanceId{instanceId}, _runtimeId{runtimeId} {}

ConceptAKey::ConceptAKey(Viper::UUId const & instanceId) noexcept
: _instanceId{instanceId}, _runtimeId{RuntimeIds::ConceptA} {}

ConceptAKey ConceptAKey::create() { return {Viper::UUId::create(), RuntimeIds::ConceptA}; }

Viper::UUId const & ConceptAKey::instanceId() const noexcept { return _instanceId; }
Viper::UUId const & ConceptAKey::runtimeId() const noexcept { return _runtimeId; }
bool ConceptAKey::isValid() const noexcept { return _instanceId.isValid(); }

std::string ConceptAKey::description() const { return Features::Codec::description(toAny()); }
bool ConceptAKey::isKnown() const { return Features::Codec::isKnown(toAny()); }
Features::AnyConceptKey ConceptAKey::toAny() const noexcept { return {_instanceId, _runtimeId}; }

/// Rétrécir depuis la clé non typée : le modèle répond, parce que lui seul connaît la
/// hiérarchie -- y compris ce qui a été déclaré après cette unité.
std::optional<ConceptAKey> ConceptAKey::from(Features::AnyConceptKey const & key) noexcept {
    if (!Features::Codec::isMember(key, conceptType(Viper::Codec::tag<ConceptAKey>{})))
        return std::nullopt;

    return ConceptAKey{key.instanceId(), key.runtimeId()};
}

bool operator==(ConceptAKey const & l, ConceptAKey const & r) noexcept {
    return l.instanceId() == r.instanceId() && l.runtimeId() == r.runtimeId();
}
bool operator!=(ConceptAKey const & l, ConceptAKey const & r) noexcept { return !(l == r); }
bool operator<(ConceptAKey const & l, ConceptAKey const & r) noexcept {
    if (l.instanceId() != r.instanceId())
        return l.instanceId() < r.instanceId();
    return l.runtimeId() < r.runtimeId();
}

void hash(Viper::Hash::Accumulator & h, ConceptAKey const & value) noexcept {
    hash(h, value.instanceId());
    hash(h, value.runtimeId());
}

// ── ConceptB ──

ConceptBKey::ConceptBKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept
: _instanceId{instanceId}, _runtimeId{runtimeId} {}

ConceptBKey::ConceptBKey(Viper::UUId const & instanceId) noexcept
: _instanceId{instanceId}, _runtimeId{RuntimeIds::ConceptB} {}

ConceptBKey ConceptBKey::create() { return {Viper::UUId::create(), RuntimeIds::ConceptB}; }

Viper::UUId const & ConceptBKey::instanceId() const noexcept { return _instanceId; }
Viper::UUId const & ConceptBKey::runtimeId() const noexcept { return _runtimeId; }
bool ConceptBKey::isValid() const noexcept { return _instanceId.isValid(); }

std::string ConceptBKey::description() const { return Features::Codec::description(toAny()); }
bool ConceptBKey::isKnown() const { return Features::Codec::isKnown(toAny()); }
Features::AnyConceptKey ConceptBKey::toAny() const noexcept { return {_instanceId, _runtimeId}; }

/// Rétrécir depuis la clé non typée : le modèle répond, parce que lui seul connaît la
/// hiérarchie -- y compris ce qui a été déclaré après cette unité.
std::optional<ConceptBKey> ConceptBKey::from(Features::AnyConceptKey const & key) noexcept {
    if (!Features::Codec::isMember(key, conceptType(Viper::Codec::tag<ConceptBKey>{})))
        return std::nullopt;

    return ConceptBKey{key.instanceId(), key.runtimeId()};
}

bool operator==(ConceptBKey const & l, ConceptBKey const & r) noexcept {
    return l.instanceId() == r.instanceId() && l.runtimeId() == r.runtimeId();
}
bool operator!=(ConceptBKey const & l, ConceptBKey const & r) noexcept { return !(l == r); }
bool operator<(ConceptBKey const & l, ConceptBKey const & r) noexcept {
    if (l.instanceId() != r.instanceId())
        return l.instanceId() < r.instanceId();
    return l.runtimeId() < r.runtimeId();
}

void hash(Viper::Hash::Accumulator & h, ConceptBKey const & value) noexcept {
    hash(h, value.instanceId());
    hash(h, value.runtimeId());
}

// ── ConceptCoverage ──

ConceptCoverageKey::ConceptCoverageKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept
: _instanceId{instanceId}, _runtimeId{runtimeId} {}

ConceptCoverageKey::ConceptCoverageKey(Viper::UUId const & instanceId) noexcept
: _instanceId{instanceId}, _runtimeId{RuntimeIds::ConceptCoverage} {}

ConceptCoverageKey ConceptCoverageKey::create() { return {Viper::UUId::create(), RuntimeIds::ConceptCoverage}; }

Viper::UUId const & ConceptCoverageKey::instanceId() const noexcept { return _instanceId; }
Viper::UUId const & ConceptCoverageKey::runtimeId() const noexcept { return _runtimeId; }
bool ConceptCoverageKey::isValid() const noexcept { return _instanceId.isValid(); }

std::string ConceptCoverageKey::description() const { return Features::Codec::description(toAny()); }
bool ConceptCoverageKey::isKnown() const { return Features::Codec::isKnown(toAny()); }
Features::AnyConceptKey ConceptCoverageKey::toAny() const noexcept { return {_instanceId, _runtimeId}; }

/// Rétrécir depuis la clé non typée : le modèle répond, parce que lui seul connaît la
/// hiérarchie -- y compris ce qui a été déclaré après cette unité.
std::optional<ConceptCoverageKey> ConceptCoverageKey::from(Features::AnyConceptKey const & key) noexcept {
    if (!Features::Codec::isMember(key, conceptType(Viper::Codec::tag<ConceptCoverageKey>{})))
        return std::nullopt;

    return ConceptCoverageKey{key.instanceId(), key.runtimeId()};
}

bool operator==(ConceptCoverageKey const & l, ConceptCoverageKey const & r) noexcept {
    return l.instanceId() == r.instanceId() && l.runtimeId() == r.runtimeId();
}
bool operator!=(ConceptCoverageKey const & l, ConceptCoverageKey const & r) noexcept { return !(l == r); }
bool operator<(ConceptCoverageKey const & l, ConceptCoverageKey const & r) noexcept {
    if (l.instanceId() != r.instanceId())
        return l.instanceId() < r.instanceId();
    return l.runtimeId() < r.runtimeId();
}

void hash(Viper::Hash::Accumulator & h, ConceptCoverageKey const & value) noexcept {
    hash(h, value.instanceId());
    hash(h, value.runtimeId());
}

// ── ConceptD ──

ConceptDKey::ConceptDKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept
: _instanceId{instanceId}, _runtimeId{runtimeId} {}

ConceptDKey::ConceptDKey(Viper::UUId const & instanceId) noexcept
: _instanceId{instanceId}, _runtimeId{RuntimeIds::ConceptD} {}

ConceptDKey ConceptDKey::create() { return {Viper::UUId::create(), RuntimeIds::ConceptD}; }

Viper::UUId const & ConceptDKey::instanceId() const noexcept { return _instanceId; }
Viper::UUId const & ConceptDKey::runtimeId() const noexcept { return _runtimeId; }
bool ConceptDKey::isValid() const noexcept { return _instanceId.isValid(); }

std::string ConceptDKey::description() const { return Features::Codec::description(toAny()); }
bool ConceptDKey::isKnown() const { return Features::Codec::isKnown(toAny()); }
Features::AnyConceptKey ConceptDKey::toAny() const noexcept { return {_instanceId, _runtimeId}; }

/// Rétrécir depuis la clé non typée : le modèle répond, parce que lui seul connaît la
/// hiérarchie -- y compris ce qui a été déclaré après cette unité.
std::optional<ConceptDKey> ConceptDKey::from(Features::AnyConceptKey const & key) noexcept {
    if (!Features::Codec::isMember(key, conceptType(Viper::Codec::tag<ConceptDKey>{})))
        return std::nullopt;

    return ConceptDKey{key.instanceId(), key.runtimeId()};
}

bool operator==(ConceptDKey const & l, ConceptDKey const & r) noexcept {
    return l.instanceId() == r.instanceId() && l.runtimeId() == r.runtimeId();
}
bool operator!=(ConceptDKey const & l, ConceptDKey const & r) noexcept { return !(l == r); }
bool operator<(ConceptDKey const & l, ConceptDKey const & r) noexcept {
    if (l.instanceId() != r.instanceId())
        return l.instanceId() < r.instanceId();
    return l.runtimeId() < r.runtimeId();
}

void hash(Viper::Hash::Accumulator & h, ConceptDKey const & value) noexcept {
    hash(h, value.instanceId());
    hash(h, value.runtimeId());
}

// ── ConceptC ──

ConceptCKey::ConceptCKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept
: _instanceId{instanceId}, _runtimeId{runtimeId} {}

ConceptCKey::ConceptCKey(Viper::UUId const & instanceId) noexcept
: _instanceId{instanceId}, _runtimeId{RuntimeIds::ConceptC} {}

ConceptCKey ConceptCKey::create() { return {Viper::UUId::create(), RuntimeIds::ConceptC}; }

Viper::UUId const & ConceptCKey::instanceId() const noexcept { return _instanceId; }
Viper::UUId const & ConceptCKey::runtimeId() const noexcept { return _runtimeId; }
bool ConceptCKey::isValid() const noexcept { return _instanceId.isValid(); }

std::string ConceptCKey::description() const { return Features::Codec::description(toAny()); }
bool ConceptCKey::isKnown() const { return Features::Codec::isKnown(toAny()); }

/// L'élargissement ne perd rien et ne peut pas échouer : l'identifiant d'exécution reste
/// celui du concept réel, et c'est pourquoi le retour est possible ensuite.
ConceptCKey::operator ConceptBKey() const noexcept { return {_instanceId, _runtimeId}; }

ConceptBKey ConceptCKey::toParentKey() const noexcept { return {_instanceId, _runtimeId}; }

Features::AnyConceptKey ConceptCKey::toAny() const noexcept { return {_instanceId, _runtimeId}; }

/// Rétrécir depuis la clé non typée : le modèle répond, parce que lui seul connaît la
/// hiérarchie -- y compris ce qui a été déclaré après cette unité.
std::optional<ConceptCKey> ConceptCKey::from(Features::AnyConceptKey const & key) noexcept {
    if (!Features::Codec::isMember(key, conceptType(Viper::Codec::tag<ConceptCKey>{})))
        return std::nullopt;

    return ConceptCKey{key.instanceId(), key.runtimeId()};
}

bool operator==(ConceptCKey const & l, ConceptCKey const & r) noexcept {
    return l.instanceId() == r.instanceId() && l.runtimeId() == r.runtimeId();
}
bool operator!=(ConceptCKey const & l, ConceptCKey const & r) noexcept { return !(l == r); }
bool operator<(ConceptCKey const & l, ConceptCKey const & r) noexcept {
    if (l.instanceId() != r.instanceId())
        return l.instanceId() < r.instanceId();
    return l.runtimeId() < r.runtimeId();
}

void hash(Viper::Hash::Accumulator & h, ConceptCKey const & value) noexcept {
    hash(h, value.instanceId());
    hash(h, value.runtimeId());
}

// ── EmptyKlub ──

EmptyKlubKey::EmptyKlubKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept
: _instanceId{instanceId}, _runtimeId{runtimeId} {}

EmptyKlubKey::EmptyKlubKey(Viper::UUId const & instanceId) noexcept
: _instanceId{instanceId}, _runtimeId{RuntimeIds::EmptyKlub} {}



Viper::UUId const & EmptyKlubKey::instanceId() const noexcept { return _instanceId; }
Viper::UUId const & EmptyKlubKey::runtimeId() const noexcept { return _runtimeId; }
bool EmptyKlubKey::isValid() const noexcept { return _instanceId.isValid(); }

std::string EmptyKlubKey::description() const { return Features::Codec::description(toAny()); }
bool EmptyKlubKey::isKnown() const { return Features::Codec::isKnown(toAny()); }

Features::AnyConceptKey EmptyKlubKey::toAny() const noexcept { return {_instanceId, _runtimeId}; }

/// Rétrécir depuis la clé non typée : le modèle répond, parce que lui seul connaît la
/// hiérarchie -- y compris ce qui a été déclaré après cette unité.
std::optional<EmptyKlubKey> EmptyKlubKey::from(Features::AnyConceptKey const & key) noexcept {
    if (!Features::Codec::isMember(key, clubType(Viper::Codec::tag<EmptyKlubKey>{})))
        return std::nullopt;

    return EmptyKlubKey{key.instanceId(), key.runtimeId()};
}

bool operator==(EmptyKlubKey const & l, EmptyKlubKey const & r) noexcept {
    return l.instanceId() == r.instanceId() && l.runtimeId() == r.runtimeId();
}
bool operator!=(EmptyKlubKey const & l, EmptyKlubKey const & r) noexcept { return !(l == r); }
bool operator<(EmptyKlubKey const & l, EmptyKlubKey const & r) noexcept {
    if (l.instanceId() != r.instanceId())
        return l.instanceId() < r.instanceId();
    return l.runtimeId() < r.runtimeId();
}

void hash(Viper::Hash::Accumulator & h, EmptyKlubKey const & value) noexcept {
    hash(h, value.instanceId());
    hash(h, value.runtimeId());
}

// ── Klub ──

KlubKey::KlubKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept
: _instanceId{instanceId}, _runtimeId{runtimeId} {}

KlubKey::KlubKey(Viper::UUId const & instanceId) noexcept
: _instanceId{instanceId}, _runtimeId{RuntimeIds::Klub} {}

KlubKey::KlubKey(ConceptCKey const & key) noexcept
: _instanceId{key.instanceId()}, _runtimeId{key.runtimeId()} {}

KlubKey::KlubKey(ConceptDKey const & key) noexcept
: _instanceId{key.instanceId()}, _runtimeId{key.runtimeId()} {}

std::optional<ConceptCKey> KlubKey::asConceptCKey() const noexcept {
    return ConceptCKey::from(toAny());
}

std::optional<ConceptDKey> KlubKey::asConceptDKey() const noexcept {
    return ConceptDKey::from(toAny());
}

Viper::UUId const & KlubKey::instanceId() const noexcept { return _instanceId; }
Viper::UUId const & KlubKey::runtimeId() const noexcept { return _runtimeId; }
bool KlubKey::isValid() const noexcept { return _instanceId.isValid(); }

std::string KlubKey::description() const { return Features::Codec::description(toAny()); }
bool KlubKey::isKnown() const { return Features::Codec::isKnown(toAny()); }

Features::AnyConceptKey KlubKey::toAny() const noexcept { return {_instanceId, _runtimeId}; }

/// Rétrécir depuis la clé non typée : le modèle répond, parce que lui seul connaît la
/// hiérarchie -- y compris ce qui a été déclaré après cette unité.
std::optional<KlubKey> KlubKey::from(Features::AnyConceptKey const & key) noexcept {
    if (!Features::Codec::isMember(key, clubType(Viper::Codec::tag<KlubKey>{})))
        return std::nullopt;

    return KlubKey{key.instanceId(), key.runtimeId()};
}

bool operator==(KlubKey const & l, KlubKey const & r) noexcept {
    return l.instanceId() == r.instanceId() && l.runtimeId() == r.runtimeId();
}
bool operator!=(KlubKey const & l, KlubKey const & r) noexcept { return !(l == r); }
bool operator<(KlubKey const & l, KlubKey const & r) noexcept {
    if (l.instanceId() != r.instanceId())
        return l.instanceId() < r.instanceId();
    return l.runtimeId() < r.runtimeId();
}

void hash(Viper::Hash::Accumulator & h, KlubKey const & value) noexcept {
    hash(h, value.instanceId());
    hash(h, value.runtimeId());
}

// ── EnumerationE ──

void hash(Viper::Hash::Accumulator & h, EnumerationE value) noexcept {
    hash(h, static_cast<std::uint8_t>(value));
}

// ── StructureS ──

bool operator==(StructureS const & l, StructureS const & r) noexcept {
    return l.f_float == r.f_float
        && l.f_string == r.f_string;
}
bool operator!=(StructureS const & l, StructureS const & r) noexcept { return !(l == r); }
bool operator<(StructureS const & l, StructureS const & r) noexcept {
    if (l.f_float < r.f_float) return true;
    if (r.f_float < l.f_float) return false;
    return l.f_string < r.f_string;
}

void hash(Viper::Hash::Accumulator & h, StructureS const & value) noexcept {
    hash(h, value.f_float);
    hash(h, value.f_string);
}

// ── StructureT ──

bool operator==(StructureT const & l, StructureT const & r) noexcept {
    return l.field_string == r.field_string
        && l.field_structure_s == r.field_structure_s;
}
bool operator!=(StructureT const & l, StructureT const & r) noexcept { return !(l == r); }
bool operator<(StructureT const & l, StructureT const & r) noexcept {
    if (l.field_string < r.field_string) return true;
    if (r.field_string < l.field_string) return false;
    return l.field_structure_s < r.field_structure_s;
}

void hash(Viper::Hash::Accumulator & h, StructureT const & value) noexcept {
    hash(h, value.field_string);
    hash(h, value.field_structure_s);
}

// ── StructureU ──

bool operator==(StructureU const & l, StructureU const & r) noexcept {
    return l.f_bool == r.f_bool
        && l.f_uint8 == r.f_uint8
        && l.f_uint16 == r.f_uint16
        && l.f_uint32 == r.f_uint32
        && l.f_uint64 == r.f_uint64
        && l.f_int8 == r.f_int8
        && l.f_int16 == r.f_int16
        && l.f_int32 == r.f_int32
        && l.f_int64 == r.f_int64
        && l.f_float == r.f_float
        && l.f_double == r.f_double
        && l.f_blob_id == r.f_blob_id
        && l.f_commit_id == r.f_commit_id
        && l.f_uuid == r.f_uuid
        && l.f_string == r.f_string
        && l.f_blob == r.f_blob
        && l.f_vec == r.f_vec
        && l.f_mat == r.f_mat
        && l.f_tuple == r.f_tuple
        && l.f_optional == r.f_optional
        && l.f_vector == r.f_vector
        && l.f_set == r.f_set
        && l.f_set_s == r.f_set_s
        && l.f_map_s1 == r.f_map_s1
        && l.f_map_s2 == r.f_map_s2
        && l.f_xarray == r.f_xarray
        && l.f_xarray_s == r.f_xarray_s
        && l.f_map_vs == r.f_map_vs
        && l.f_variant == r.f_variant
        && l.f_any == r.f_any
        && l.f_E == r.f_E
        && l.f_S == r.f_S
        && l.f_T == r.f_T
        && l.f_A == r.f_A
        && l.f_B == r.f_B
        && l.f_C == r.f_C
        && l.f_D == r.f_D
        && l.f_Klub == r.f_Klub
        && l.f_any_concept == r.f_any_concept;
}
bool operator!=(StructureU const & l, StructureU const & r) noexcept { return !(l == r); }
bool operator<(StructureU const & l, StructureU const & r) noexcept {
    if (l.f_bool < r.f_bool) return true;
    if (r.f_bool < l.f_bool) return false;
    if (l.f_uint8 < r.f_uint8) return true;
    if (r.f_uint8 < l.f_uint8) return false;
    if (l.f_uint16 < r.f_uint16) return true;
    if (r.f_uint16 < l.f_uint16) return false;
    if (l.f_uint32 < r.f_uint32) return true;
    if (r.f_uint32 < l.f_uint32) return false;
    if (l.f_uint64 < r.f_uint64) return true;
    if (r.f_uint64 < l.f_uint64) return false;
    if (l.f_int8 < r.f_int8) return true;
    if (r.f_int8 < l.f_int8) return false;
    if (l.f_int16 < r.f_int16) return true;
    if (r.f_int16 < l.f_int16) return false;
    if (l.f_int32 < r.f_int32) return true;
    if (r.f_int32 < l.f_int32) return false;
    if (l.f_int64 < r.f_int64) return true;
    if (r.f_int64 < l.f_int64) return false;
    if (l.f_float < r.f_float) return true;
    if (r.f_float < l.f_float) return false;
    if (l.f_double < r.f_double) return true;
    if (r.f_double < l.f_double) return false;
    if (l.f_blob_id < r.f_blob_id) return true;
    if (r.f_blob_id < l.f_blob_id) return false;
    if (l.f_commit_id < r.f_commit_id) return true;
    if (r.f_commit_id < l.f_commit_id) return false;
    if (l.f_uuid < r.f_uuid) return true;
    if (r.f_uuid < l.f_uuid) return false;
    if (l.f_string < r.f_string) return true;
    if (r.f_string < l.f_string) return false;
    if (l.f_blob < r.f_blob) return true;
    if (r.f_blob < l.f_blob) return false;
    if (l.f_vec < r.f_vec) return true;
    if (r.f_vec < l.f_vec) return false;
    if (l.f_mat < r.f_mat) return true;
    if (r.f_mat < l.f_mat) return false;
    if (l.f_tuple < r.f_tuple) return true;
    if (r.f_tuple < l.f_tuple) return false;
    if (l.f_optional < r.f_optional) return true;
    if (r.f_optional < l.f_optional) return false;
    if (l.f_vector < r.f_vector) return true;
    if (r.f_vector < l.f_vector) return false;
    if (l.f_set < r.f_set) return true;
    if (r.f_set < l.f_set) return false;
    if (l.f_set_s < r.f_set_s) return true;
    if (r.f_set_s < l.f_set_s) return false;
    if (l.f_map_s1 < r.f_map_s1) return true;
    if (r.f_map_s1 < l.f_map_s1) return false;
    if (l.f_map_s2 < r.f_map_s2) return true;
    if (r.f_map_s2 < l.f_map_s2) return false;
    if (l.f_xarray < r.f_xarray) return true;
    if (r.f_xarray < l.f_xarray) return false;
    if (l.f_xarray_s < r.f_xarray_s) return true;
    if (r.f_xarray_s < l.f_xarray_s) return false;
    if (l.f_map_vs < r.f_map_vs) return true;
    if (r.f_map_vs < l.f_map_vs) return false;
    if (l.f_variant < r.f_variant) return true;
    if (r.f_variant < l.f_variant) return false;
    if (l.f_any < r.f_any) return true;
    if (r.f_any < l.f_any) return false;
    if (l.f_E < r.f_E) return true;
    if (r.f_E < l.f_E) return false;
    if (l.f_S < r.f_S) return true;
    if (r.f_S < l.f_S) return false;
    if (l.f_T < r.f_T) return true;
    if (r.f_T < l.f_T) return false;
    if (l.f_A < r.f_A) return true;
    if (r.f_A < l.f_A) return false;
    if (l.f_B < r.f_B) return true;
    if (r.f_B < l.f_B) return false;
    if (l.f_C < r.f_C) return true;
    if (r.f_C < l.f_C) return false;
    if (l.f_D < r.f_D) return true;
    if (r.f_D < l.f_D) return false;
    if (l.f_Klub < r.f_Klub) return true;
    if (r.f_Klub < l.f_Klub) return false;
    return l.f_any_concept < r.f_any_concept;
}

void hash(Viper::Hash::Accumulator & h, StructureU const & value) noexcept {
    hash(h, value.f_bool);
    hash(h, value.f_uint8);
    hash(h, value.f_uint16);
    hash(h, value.f_uint32);
    hash(h, value.f_uint64);
    hash(h, value.f_int8);
    hash(h, value.f_int16);
    hash(h, value.f_int32);
    hash(h, value.f_int64);
    hash(h, value.f_float);
    hash(h, value.f_double);
    hash(h, value.f_blob_id);
    hash(h, value.f_commit_id);
    hash(h, value.f_uuid);
    hash(h, value.f_string);
    hash(h, value.f_blob);
    hash(h, value.f_vec);
    hash(h, value.f_mat);
    hash(h, value.f_tuple);
    hash(h, value.f_optional);
    hash(h, value.f_vector);
    hash(h, value.f_set);
    hash(h, value.f_set_s);
    hash(h, value.f_map_s1);
    hash(h, value.f_map_s2);
    hash(h, value.f_xarray);
    hash(h, value.f_xarray_s);
    hash(h, value.f_map_vs);
    hash(h, value.f_variant);
    hash(h, value.f_any);
    hash(h, value.f_E);
    hash(h, value.f_S);
    hash(h, value.f_T);
    hash(h, value.f_A);
    hash(h, value.f_B);
    hash(h, value.f_C);
    hash(h, value.f_D);
    hash(h, value.f_Klub);
    hash(h, value.f_any_concept);
}

// ── StructureV ──

bool operator==(StructureV const & l, StructureV const & r) noexcept {
    return l.f_bool == r.f_bool
        && l.f_uint8 == r.f_uint8
        && l.f_uint16 == r.f_uint16
        && l.f_uint32 == r.f_uint32
        && l.f_uint64 == r.f_uint64
        && l.f_int8 == r.f_int8
        && l.f_int16 == r.f_int16
        && l.f_int32 == r.f_int32
        && l.f_int64 == r.f_int64
        && l.f_float == r.f_float
        && l.f_double == r.f_double
        && l.f_uuid == r.f_uuid
        && l.f_string == r.f_string
        && l.f_vec == r.f_vec
        && l.f_mat == r.f_mat
        && l.f_tuple == r.f_tuple
        && l.f_optional == r.f_optional
        && l.f_vector == r.f_vector
        && l.f_set == r.f_set
        && l.f_map == r.f_map
        && l.f_E == r.f_E
        && l.f_S == r.f_S
        && l.f_T == r.f_T;
}
bool operator!=(StructureV const & l, StructureV const & r) noexcept { return !(l == r); }
bool operator<(StructureV const & l, StructureV const & r) noexcept {
    if (l.f_bool < r.f_bool) return true;
    if (r.f_bool < l.f_bool) return false;
    if (l.f_uint8 < r.f_uint8) return true;
    if (r.f_uint8 < l.f_uint8) return false;
    if (l.f_uint16 < r.f_uint16) return true;
    if (r.f_uint16 < l.f_uint16) return false;
    if (l.f_uint32 < r.f_uint32) return true;
    if (r.f_uint32 < l.f_uint32) return false;
    if (l.f_uint64 < r.f_uint64) return true;
    if (r.f_uint64 < l.f_uint64) return false;
    if (l.f_int8 < r.f_int8) return true;
    if (r.f_int8 < l.f_int8) return false;
    if (l.f_int16 < r.f_int16) return true;
    if (r.f_int16 < l.f_int16) return false;
    if (l.f_int32 < r.f_int32) return true;
    if (r.f_int32 < l.f_int32) return false;
    if (l.f_int64 < r.f_int64) return true;
    if (r.f_int64 < l.f_int64) return false;
    if (l.f_float < r.f_float) return true;
    if (r.f_float < l.f_float) return false;
    if (l.f_double < r.f_double) return true;
    if (r.f_double < l.f_double) return false;
    if (l.f_uuid < r.f_uuid) return true;
    if (r.f_uuid < l.f_uuid) return false;
    if (l.f_string < r.f_string) return true;
    if (r.f_string < l.f_string) return false;
    if (l.f_vec < r.f_vec) return true;
    if (r.f_vec < l.f_vec) return false;
    if (l.f_mat < r.f_mat) return true;
    if (r.f_mat < l.f_mat) return false;
    if (l.f_tuple < r.f_tuple) return true;
    if (r.f_tuple < l.f_tuple) return false;
    if (l.f_optional < r.f_optional) return true;
    if (r.f_optional < l.f_optional) return false;
    if (l.f_vector < r.f_vector) return true;
    if (r.f_vector < l.f_vector) return false;
    if (l.f_set < r.f_set) return true;
    if (r.f_set < l.f_set) return false;
    if (l.f_map < r.f_map) return true;
    if (r.f_map < l.f_map) return false;
    if (l.f_E < r.f_E) return true;
    if (r.f_E < l.f_E) return false;
    if (l.f_S < r.f_S) return true;
    if (r.f_S < l.f_S) return false;
    return l.f_T < r.f_T;
}

void hash(Viper::Hash::Accumulator & h, StructureV const & value) noexcept {
    hash(h, value.f_bool);
    hash(h, value.f_uint8);
    hash(h, value.f_uint16);
    hash(h, value.f_uint32);
    hash(h, value.f_uint64);
    hash(h, value.f_int8);
    hash(h, value.f_int16);
    hash(h, value.f_int32);
    hash(h, value.f_int64);
    hash(h, value.f_float);
    hash(h, value.f_double);
    hash(h, value.f_uuid);
    hash(h, value.f_string);
    hash(h, value.f_vec);
    hash(h, value.f_mat);
    hash(h, value.f_tuple);
    hash(h, value.f_optional);
    hash(h, value.f_vector);
    hash(h, value.f_set);
    hash(h, value.f_map);
    hash(h, value.f_E);
    hash(h, value.f_S);
    hash(h, value.f_T);
}

// ── StructureW ──

bool operator==(StructureW const & l, StructureW const & r) noexcept {
    return l.f_single == r.f_single;
}
bool operator!=(StructureW const & l, StructureW const & r) noexcept { return !(l == r); }
bool operator<(StructureW const & l, StructureW const & r) noexcept {
    return l.f_single < r.f_single;
}

void hash(Viper::Hash::Accumulator & h, StructureW const & value) noexcept {
    hash(h, value.f_single);
}

} // namespace Test