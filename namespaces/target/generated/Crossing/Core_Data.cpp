// unité Core — l'implémentation de ses types.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

#include "Core_Data.hpp"

#include "Core_Model.hpp"
#include "Crossing_Codec.hpp"

namespace Core {

// ── Other ──

OtherKey::OtherKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept
: _instanceId{instanceId}, _runtimeId{runtimeId} {}

OtherKey OtherKey::create() { return {Viper::UUId::create(), RuntimeIds::Other}; }

Viper::UUId const & OtherKey::instanceId() const noexcept { return _instanceId; }
Viper::UUId const & OtherKey::runtimeId() const noexcept { return _runtimeId; }
bool OtherKey::isValid() const noexcept { return _instanceId.isValid(); }
Crossing::AnyConceptKey OtherKey::toAny() const noexcept { return {_instanceId, _runtimeId}; }

/// Rétrécir depuis la clé non typée : le modèle répond, parce que lui seul connaît la
/// hiérarchie -- y compris ce qui a été déclaré après cette unité.
std::optional<OtherKey> OtherKey::from(Crossing::AnyConceptKey const & key) noexcept {
    if (!Crossing::Codec::isMember(key, conceptType(Viper::Codec::tag<OtherKey>{})))
        return std::nullopt;

    return OtherKey{key.instanceId(), key.runtimeId()};
}

bool operator==(OtherKey const & l, OtherKey const & r) noexcept {
    return l.instanceId() == r.instanceId() && l.runtimeId() == r.runtimeId();
}
bool operator!=(OtherKey const & l, OtherKey const & r) noexcept { return !(l == r); }
bool operator<(OtherKey const & l, OtherKey const & r) noexcept {
    if (l.instanceId() != r.instanceId())
        return l.instanceId() < r.instanceId();
    return l.runtimeId() < r.runtimeId();
}

void hash(Viper::Hash::Accumulator & h, OtherKey const & value) noexcept {
    hash(h, value.instanceId());
    hash(h, value.runtimeId());
}

// ── Thing ──

ThingKey::ThingKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept
: _instanceId{instanceId}, _runtimeId{runtimeId} {}

ThingKey ThingKey::create() { return {Viper::UUId::create(), RuntimeIds::Thing}; }

Viper::UUId const & ThingKey::instanceId() const noexcept { return _instanceId; }
Viper::UUId const & ThingKey::runtimeId() const noexcept { return _runtimeId; }
bool ThingKey::isValid() const noexcept { return _instanceId.isValid(); }
Crossing::AnyConceptKey ThingKey::toAny() const noexcept { return {_instanceId, _runtimeId}; }

/// Rétrécir depuis la clé non typée : le modèle répond, parce que lui seul connaît la
/// hiérarchie -- y compris ce qui a été déclaré après cette unité.
std::optional<ThingKey> ThingKey::from(Crossing::AnyConceptKey const & key) noexcept {
    if (!Crossing::Codec::isMember(key, conceptType(Viper::Codec::tag<ThingKey>{})))
        return std::nullopt;

    return ThingKey{key.instanceId(), key.runtimeId()};
}

bool operator==(ThingKey const & l, ThingKey const & r) noexcept {
    return l.instanceId() == r.instanceId() && l.runtimeId() == r.runtimeId();
}
bool operator!=(ThingKey const & l, ThingKey const & r) noexcept { return !(l == r); }
bool operator<(ThingKey const & l, ThingKey const & r) noexcept {
    if (l.instanceId() != r.instanceId())
        return l.instanceId() < r.instanceId();
    return l.runtimeId() < r.runtimeId();
}

void hash(Viper::Hash::Accumulator & h, ThingKey const & value) noexcept {
    hash(h, value.instanceId());
    hash(h, value.runtimeId());
}

// ── SubThing ──

SubThingKey::SubThingKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept
: _instanceId{instanceId}, _runtimeId{runtimeId} {}

SubThingKey SubThingKey::create() { return {Viper::UUId::create(), RuntimeIds::SubThing}; }

Viper::UUId const & SubThingKey::instanceId() const noexcept { return _instanceId; }
Viper::UUId const & SubThingKey::runtimeId() const noexcept { return _runtimeId; }
bool SubThingKey::isValid() const noexcept { return _instanceId.isValid(); }

/// L'élargissement ne perd rien et ne peut pas échouer : l'identifiant d'exécution reste
/// celui du concept réel, et c'est pourquoi le retour est possible ensuite.
SubThingKey::operator ThingKey() const noexcept { return {_instanceId, _runtimeId}; }

Crossing::AnyConceptKey SubThingKey::toAny() const noexcept { return {_instanceId, _runtimeId}; }

/// Rétrécir depuis la clé non typée : le modèle répond, parce que lui seul connaît la
/// hiérarchie -- y compris ce qui a été déclaré après cette unité.
std::optional<SubThingKey> SubThingKey::from(Crossing::AnyConceptKey const & key) noexcept {
    if (!Crossing::Codec::isMember(key, conceptType(Viper::Codec::tag<SubThingKey>{})))
        return std::nullopt;

    return SubThingKey{key.instanceId(), key.runtimeId()};
}

bool operator==(SubThingKey const & l, SubThingKey const & r) noexcept {
    return l.instanceId() == r.instanceId() && l.runtimeId() == r.runtimeId();
}
bool operator!=(SubThingKey const & l, SubThingKey const & r) noexcept { return !(l == r); }
bool operator<(SubThingKey const & l, SubThingKey const & r) noexcept {
    if (l.instanceId() != r.instanceId())
        return l.instanceId() < r.instanceId();
    return l.runtimeId() < r.runtimeId();
}

void hash(Viper::Hash::Accumulator & h, SubThingKey const & value) noexcept {
    hash(h, value.instanceId());
    hash(h, value.runtimeId());
}

// ── Klub ──

KlubKey::KlubKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept
: _instanceId{instanceId}, _runtimeId{runtimeId} {}

KlubKey::KlubKey(OtherKey const & key) noexcept
: _instanceId{key.instanceId()}, _runtimeId{key.runtimeId()} {}

KlubKey::KlubKey(SubThingKey const & key) noexcept
: _instanceId{key.instanceId()}, _runtimeId{key.runtimeId()} {}

std::optional<OtherKey> KlubKey::asOtherKey() const noexcept {
    return OtherKey::from(toAny());
}

std::optional<SubThingKey> KlubKey::asSubThingKey() const noexcept {
    return SubThingKey::from(toAny());
}

Viper::UUId const & KlubKey::instanceId() const noexcept { return _instanceId; }
Viper::UUId const & KlubKey::runtimeId() const noexcept { return _runtimeId; }
bool KlubKey::isValid() const noexcept { return _instanceId.isValid(); }

Crossing::AnyConceptKey KlubKey::toAny() const noexcept { return {_instanceId, _runtimeId}; }

/// Rétrécir depuis la clé non typée : le modèle répond, parce que lui seul connaît la
/// hiérarchie -- y compris ce qui a été déclaré après cette unité.
std::optional<KlubKey> KlubKey::from(Crossing::AnyConceptKey const & key) noexcept {
    if (!Crossing::Codec::isMember(key, clubType(Viper::Codec::tag<KlubKey>{})))
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

// ── Grade ──

void hash(Viper::Hash::Accumulator & h, Grade value) noexcept {
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
    if (l.r != r.r) return l.r < r.r;
    if (l.g != r.g) return l.g < r.g;
    return l.b < r.b;
}

void hash(Viper::Hash::Accumulator & h, Colour const & value) noexcept {
    hash(h, value.r);
    hash(h, value.g);
    hash(h, value.b);
}

// ── Defaults ──

bool operator==(Defaults const & l, Defaults const & r) noexcept {
    return l.f_uint8 == r.f_uint8
        && l.f_float == r.f_float
        && l.f_string == r.f_string
        && l.f_uuid == r.f_uuid
        && l.f_vec == r.f_vec
        && l.f_grade == r.f_grade
        && l.f_colour == r.f_colour;
}
bool operator!=(Defaults const & l, Defaults const & r) noexcept { return !(l == r); }
bool operator<(Defaults const & l, Defaults const & r) noexcept {
    if (l.f_uint8 != r.f_uint8) return l.f_uint8 < r.f_uint8;
    if (l.f_float != r.f_float) return l.f_float < r.f_float;
    if (l.f_string != r.f_string) return l.f_string < r.f_string;
    if (l.f_uuid != r.f_uuid) return l.f_uuid < r.f_uuid;
    if (l.f_vec != r.f_vec) return l.f_vec < r.f_vec;
    if (l.f_grade != r.f_grade) return l.f_grade < r.f_grade;
    return l.f_colour < r.f_colour;
}

void hash(Viper::Hash::Accumulator & h, Defaults const & value) noexcept {
    hash(h, value.f_uint8);
    hash(h, value.f_float);
    hash(h, value.f_string);
    hash(h, value.f_uuid);
    hash(h, value.f_vec);
    hash(h, value.f_grade);
    hash(h, value.f_colour);
}

// ── Scalars ──

bool operator==(Scalars const & l, Scalars const & r) noexcept {
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
        && l.f_any == r.f_any
        && l.f_vec == r.f_vec
        && l.f_mat == r.f_mat;
}
bool operator!=(Scalars const & l, Scalars const & r) noexcept { return !(l == r); }
bool operator<(Scalars const & l, Scalars const & r) noexcept {
    if (l.f_bool != r.f_bool) return l.f_bool < r.f_bool;
    if (l.f_uint8 != r.f_uint8) return l.f_uint8 < r.f_uint8;
    if (l.f_uint16 != r.f_uint16) return l.f_uint16 < r.f_uint16;
    if (l.f_uint32 != r.f_uint32) return l.f_uint32 < r.f_uint32;
    if (l.f_uint64 != r.f_uint64) return l.f_uint64 < r.f_uint64;
    if (l.f_int8 != r.f_int8) return l.f_int8 < r.f_int8;
    if (l.f_int16 != r.f_int16) return l.f_int16 < r.f_int16;
    if (l.f_int32 != r.f_int32) return l.f_int32 < r.f_int32;
    if (l.f_int64 != r.f_int64) return l.f_int64 < r.f_int64;
    if (l.f_float != r.f_float) return l.f_float < r.f_float;
    if (l.f_double != r.f_double) return l.f_double < r.f_double;
    if (l.f_blob_id != r.f_blob_id) return l.f_blob_id < r.f_blob_id;
    if (l.f_commit_id != r.f_commit_id) return l.f_commit_id < r.f_commit_id;
    if (l.f_uuid != r.f_uuid) return l.f_uuid < r.f_uuid;
    if (l.f_string != r.f_string) return l.f_string < r.f_string;
    if (l.f_blob != r.f_blob) return l.f_blob < r.f_blob;
    if (l.f_any != r.f_any) return l.f_any < r.f_any;
    if (l.f_vec != r.f_vec) return l.f_vec < r.f_vec;
    return l.f_mat < r.f_mat;
}

void hash(Viper::Hash::Accumulator & h, Scalars const & value) noexcept {
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
    hash(h, value.f_any);
    hash(h, value.f_vec);
    hash(h, value.f_mat);
}

// ── Single ──

bool operator==(Single const & l, Single const & r) noexcept {
    return l.f_single == r.f_single;
}
bool operator!=(Single const & l, Single const & r) noexcept { return !(l == r); }
bool operator<(Single const & l, Single const & r) noexcept {
    return l.f_single < r.f_single;
}

void hash(Viper::Hash::Accumulator & h, Single const & value) noexcept {
    hash(h, value.f_single);
}

} // namespace Core