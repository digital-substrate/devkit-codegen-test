// Core — les types que ce namespace déclare.
//
// Écrit à la main depuis le modèle. Ce fichier ne couvre pas toutes les structures de Core
// -- `Scalars`, `Defaults` et `Single` sont la même forme que celles déjà écrites dans
// `namespaces/target/hand/ModelA_Data.hpp` -- il couvre les deux qui n'existaient nulle
// part : un concept dérivé dans la même unité, et un club.

#ifndef Core_Data_hpp
#define Core_Data_hpp

#include "Crossing_AnyConcept.hpp"
#include "Viper_HashAccumulator.hpp"
#include "Viper_UUId.hpp"

#include "Viper_Blob.hpp"

#include <cstdint>
#include <map>
#include <optional>
#include <set>

namespace Core {

/// Ce sur quoi on accroche des choses.
class ThingKey final {
public:
    ThingKey() = default;
    ThingKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept;

    static ThingKey create();

    Viper::UUId const & instanceId() const noexcept;
    Viper::UUId const & runtimeId() const noexcept;
    bool isValid() const noexcept;

    Crossing::AnyConceptKey toAny() const noexcept;
    static std::optional<ThingKey> from(Crossing::AnyConceptKey const & key) noexcept;

private:
    Viper::UUId _instanceId{};
    Viper::UUId _runtimeId{};
};

bool operator==(ThingKey const &, ThingKey const &) noexcept;
bool operator!=(ThingKey const &, ThingKey const &) noexcept;
bool operator<(ThingKey const &, ThingKey const &) noexcept;

namespace Hash = Viper::Hash;
void hash(Hash::Accumulator & h, ThingKey const & value) noexcept;

/// Un dérivé, dans la même unité.
///
/// DÉCLARÉ APRÈS SON PARENT, ET CE N'EST PAS UN CHOIX DE MISE EN PAGE. La conversion
/// élargissante ci-dessous nomme `ThingKey`, donc `ThingKey` doit être déclaré au-dessus.
/// Le générateur triait ses concepts par nom, ce qui plaçait `SubThing` en premier.
class SubThingKey final {
public:
    SubThingKey() = default;
    SubThingKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept;

    static SubThingKey create();

    Viper::UUId const & instanceId() const noexcept;
    Viper::UUId const & runtimeId() const noexcept;
    bool isValid() const noexcept;

    /// Élargir vers le parent. Implicite, parce que `is a` n'est pas une demande.
    operator ThingKey() const noexcept;

    /// Et la même, nommée, pour l'expression où la conversion ne se déclencherait pas.
    ThingKey toParentKey() const noexcept;

    Crossing::AnyConceptKey toAny() const noexcept;
    static std::optional<SubThingKey> from(Crossing::AnyConceptKey const & key) noexcept;

private:
    Viper::UUId _instanceId{};
    Viper::UUId _runtimeId{};
};

bool operator==(SubThingKey const &, SubThingKey const &) noexcept;
bool operator!=(SubThingKey const &, SubThingKey const &) noexcept;
bool operator<(SubThingKey const &, SubThingKey const &) noexcept;

void hash(Hash::Accumulator & h, SubThingKey const & value) noexcept;

class OtherKey final {
public:
    OtherKey() = default;
    OtherKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept;

    static OtherKey create();

    Viper::UUId const & instanceId() const noexcept;
    Viper::UUId const & runtimeId() const noexcept;
    bool isValid() const noexcept;

    Crossing::AnyConceptKey toAny() const noexcept;
    static std::optional<OtherKey> from(Crossing::AnyConceptKey const & key) noexcept;

private:
    Viper::UUId _instanceId{};
    Viper::UUId _runtimeId{};
};

bool operator==(OtherKey const &, OtherKey const &) noexcept;
bool operator!=(OtherKey const &, OtherKey const &) noexcept;
bool operator<(OtherKey const &, OtherKey const &) noexcept;

void hash(Hash::Accumulator & h, OtherKey const & value) noexcept;

/// Un club : un ensemble nommé de concepts, et une clé qui peut désigner une instance de
/// n'importe lequel d'entre eux.
///
/// LES CONVERSIONS SONT DU CÔTÉ DU CLUB, PAS DU MEMBRE. Un club connaît ses membres ; un
/// membre n'a pas à connaître ses clubs, et souvent il ne le peut pas -- `Woven::Weave` a
/// pour membres `Core::Thing` et `Parts::Thing`, deux unités qui ignorent Woven et dont
/// Woven dépend. Poser la conversion chez le membre inverserait l'arête du graphe.
class KlubKey final {
public:
    KlubKey() = default;
    KlubKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept;

    /// Depuis un membre. Implicite : appartenir au club n'est pas une demande non plus.
    KlubKey(SubThingKey const & key) noexcept;
    KlubKey(OtherKey const & key) noexcept;

    /// Vers un membre. Optionnel, parce que l'instance peut relever d'un autre membre --
    /// c'est toute la différence avec l'élargissement, qui lui ne peut pas échouer.
    std::optional<SubThingKey> asSubThingKey() const noexcept;
    std::optional<OtherKey> asOtherKey() const noexcept;

    Viper::UUId const & instanceId() const noexcept;
    Viper::UUId const & runtimeId() const noexcept;
    bool isValid() const noexcept;

    Crossing::AnyConceptKey toAny() const noexcept;
    static std::optional<KlubKey> from(Crossing::AnyConceptKey const & key) noexcept;

private:
    Viper::UUId _instanceId{};
    Viper::UUId _runtimeId{};
};

bool operator==(KlubKey const &, KlubKey const &) noexcept;
bool operator!=(KlubKey const &, KlubKey const &) noexcept;
bool operator<(KlubKey const &, KlubKey const &) noexcept;

void hash(Hash::Accumulator & h, KlubKey const & value) noexcept;

/// Une énumération, que d'autres namespaces référencent.
enum class Grade {
    Low,
    High
};

/// Le même nom que Parts::Colour, un type différent.
struct Colour final {
    std::uint8_t r{};
    std::uint8_t g{};
    std::uint8_t b{};
};

bool operator==(Colour const &, Colour const &) noexcept;
bool operator!=(Colour const &, Colour const &) noexcept;
bool operator<(Colour const &, Colour const &) noexcept;

void hash(Hash::Accumulator & h, Colour const & value) noexcept;

/// Un document ordinaire dont les champs sont des agrégats.
///
/// DÉCLARÉ APRÈS `Colour`, ET C'EST LA TROISIÈME FOIS QUE L'ORDRE COMPTE. Il en contient
/// une, et une unité émet dans un seul fichier -- après le parent d'un concept et les
/// membres d'un club, les champs d'une structure.
struct Bag final {
    std::set<ThingKey> members{};
    std::map<ThingKey, Colour> tints{};
    Viper::XArray<Colour> trail{};
};

bool operator==(Bag const &, Bag const &) noexcept;
bool operator!=(Bag const &, Bag const &) noexcept;
bool operator<(Bag const &, Bag const &) noexcept;

void hash(Hash::Accumulator & h, Bag const & value) noexcept;

} // namespace Core

// UNE SEULE FORME DE SPÉCIALISATION, POUR TOUS LES TYPES. La couche 1 en avait deux -- une
// clé se hachait par sa méthode, une structure par une fonction libre -- et cette
// distinction n'avait pas de raison d'être. `hash(h, x)` est trouvé par ADL pour les deux,
// et pour les conteneurs du runtime par la même écriture.
template<> struct std::hash<Core::ThingKey> {
    std::size_t operator()(Core::ThingKey const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Core::SubThingKey> {
    std::size_t operator()(Core::SubThingKey const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Core::OtherKey> {
    std::size_t operator()(Core::OtherKey const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Core::KlubKey> {
    std::size_t operator()(Core::KlubKey const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Core::Colour> {
    std::size_t operator()(Core::Colour const & v) const noexcept { return Viper::Hash::of(v); }
};

#endif
