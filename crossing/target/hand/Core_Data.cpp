// Core — l'implémentation de ses types.
//
// CE FICHIER EXISTE POUR DEUX FONCTIONS : `from` et les getters du club. Tout le reste est
// mécanique -- des accesseurs, des comparaisons, une combinaison de hachages -- et c'est
// justement pour cela qu'il fallait l'écrire : les deux qui ne le sont pas décident où
// s'arrête l'unité.

#include "Core_Data.hpp"

#include "Core_Model.hpp"          // les identités et les descripteurs de cette unité
#include "Crossing_Codec.hpp"      // isMember -- la hiérarchie des concepts, qui est au modèle

namespace Core {

// ── Thing ──

ThingKey::ThingKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept
: _instanceId{instanceId}, _runtimeId{runtimeId} {}

ThingKey ThingKey::create() { return {Viper::UUId::create(), RuntimeIds::Thing}; }

Viper::UUId const & ThingKey::instanceId() const noexcept { return _instanceId; }
Viper::UUId const & ThingKey::runtimeId() const noexcept { return _runtimeId; }
bool ThingKey::isValid() const noexcept { return _instanceId.isValid(); }

Viper::AnyConceptKey ThingKey::toAny() const noexcept { return {_instanceId, _runtimeId}; }

/// LE RÉTRÉCISSEMENT NE PEUT PAS ÊTRE ÉCRIT AVEC CE QUE L'UNITÉ SAIT.
///
/// Le pack énumère ici les identifiants de tous les dérivés connus à la génération. Dans un
/// monde plat cela passe, tout étant dans un fichier. Par unité, cela ne passe pas : un
/// dérivé de Core::Thing peut vivre dans Woven, et Core devrait alors inclure Woven --
/// l'arête à l'envers, puisque c'est Woven qui dépend de Core.
///
/// Et ce n'est pas seulement une question de dépendance : un dérivé peut avoir été déclaré
/// après que Core a été généré. L'énumération à la génération est fausse dès qu'un modèle
/// s'étend, ce que le pack reconnaît lui-même dans un commentaire sur `description`.
///
/// La question « cette instance est-elle un Thing ? » porte sur la hiérarchie des concepts
/// du modèle. Elle se pose donc au modèle, et se répond à l'exécution.
std::optional<ThingKey> ThingKey::from(Viper::AnyConceptKey const & key) noexcept {
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

void hash(Hash::Accumulator & h, ThingKey const & value) noexcept {
    hash(h, value.instanceId());
    hash(h, value.runtimeId());
}

// ── SubThing ──

SubThingKey::SubThingKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept
: _instanceId{instanceId}, _runtimeId{runtimeId} {}

SubThingKey SubThingKey::create() {
    return {Viper::UUId::create(), RuntimeIds::SubThing};
}

Viper::UUId const & SubThingKey::instanceId() const noexcept { return _instanceId; }
Viper::UUId const & SubThingKey::runtimeId() const noexcept { return _runtimeId; }
bool SubThingKey::isValid() const noexcept { return _instanceId.isValid(); }

/// L'élargissement ne perd rien et ne peut pas échouer : l'identifiant d'exécution reste
/// celui du concept réel, et c'est pourquoi le retour vers SubThing est possible ensuite.
SubThingKey::operator ThingKey() const noexcept { return {_instanceId, _runtimeId}; }

Viper::AnyConceptKey SubThingKey::toAny() const noexcept { return {_instanceId, _runtimeId}; }

std::optional<SubThingKey> SubThingKey::from(Viper::AnyConceptKey const & key) noexcept {
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

void hash(Hash::Accumulator & h, SubThingKey const & value) noexcept {
    hash(h, value.instanceId());
    hash(h, value.runtimeId());
}

// ── Other ──

OtherKey::OtherKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept
: _instanceId{instanceId}, _runtimeId{runtimeId} {}

OtherKey OtherKey::create() { return {Viper::UUId::create(), RuntimeIds::Other}; }

Viper::UUId const & OtherKey::instanceId() const noexcept { return _instanceId; }
Viper::UUId const & OtherKey::runtimeId() const noexcept { return _runtimeId; }
bool OtherKey::isValid() const noexcept { return _instanceId.isValid(); }

Viper::AnyConceptKey OtherKey::toAny() const noexcept { return {_instanceId, _runtimeId}; }

std::optional<OtherKey> OtherKey::from(Viper::AnyConceptKey const & key) noexcept {
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

void hash(Hash::Accumulator & h, OtherKey const & value) noexcept {
    hash(h, value.instanceId());
    hash(h, value.runtimeId());
}

// ── Klub ──
//
// UN CLUB EST UN RÉTRÉCISSEMENT DE PLUS, ET RIEN D'AUTRE. Entrer est gratuit : un membre
// est membre, donc le constructeur recopie les deux identifiants. Sortir demande la même
// question que `from`, posée pour un membre à la fois -- et la même réponse : c'est le
// modèle qui connaît la hiérarchie, pas l'unité.

KlubKey::KlubKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept
: _instanceId{instanceId}, _runtimeId{runtimeId} {}

KlubKey::KlubKey(SubThingKey const & key) noexcept
: _instanceId{key.instanceId()}, _runtimeId{key.runtimeId()} {}

KlubKey::KlubKey(OtherKey const & key) noexcept
: _instanceId{key.instanceId()}, _runtimeId{key.runtimeId()} {}

std::optional<SubThingKey> KlubKey::asSubThingKey() const noexcept {
    return SubThingKey::from(toAny());
}

std::optional<OtherKey> KlubKey::asOtherKey() const noexcept {
    return OtherKey::from(toAny());
}

Viper::UUId const & KlubKey::instanceId() const noexcept { return _instanceId; }
Viper::UUId const & KlubKey::runtimeId() const noexcept { return _runtimeId; }
bool KlubKey::isValid() const noexcept { return _instanceId.isValid(); }

Viper::AnyConceptKey KlubKey::toAny() const noexcept { return {_instanceId, _runtimeId}; }

/// Pour un club la question est « ce concept est-il membre ? », et non « dérive-t-il de
/// celui-ci ? » -- une adhésion n'est pas un héritage. C'est la seule différence entre ce
/// corps et celui d'un concept, et elle est portée par le descripteur, pas par le code.
std::optional<KlubKey> KlubKey::from(Viper::AnyConceptKey const & key) noexcept {
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

void hash(Hash::Accumulator & h, KlubKey const & value) noexcept {
    hash(h, value.instanceId());
    hash(h, value.runtimeId());
}

// ── Colour ──

bool operator==(Colour const & l, Colour const & r) noexcept {
    return l.r == r.r && l.g == r.g && l.b == r.b;
}
bool operator!=(Colour const & l, Colour const & r) noexcept { return !(l == r); }
bool operator<(Colour const & l, Colour const & r) noexcept {
    if (l.r != r.r) return l.r < r.r;
    if (l.g != r.g) return l.g < r.g;
    return l.b < r.b;
}

void hash(Hash::Accumulator & h, Colour const & value) noexcept {
    hash(h, value.r);
    hash(h, value.g);
    hash(h, value.b);
}

} // namespace Core
