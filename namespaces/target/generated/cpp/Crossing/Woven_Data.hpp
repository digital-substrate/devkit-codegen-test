// unité Woven — les types qu'elle déclare.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

#ifndef Woven_Data_hpp
#define Woven_Data_hpp

#include "Parts_Data.hpp"
#include "Core_Data.hpp"

#include "Crossing_AnyConcept.hpp"

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

namespace Woven {

/** Ce sur quoi les attachments de ce namespace sont accrochés. */
class KnotKey final {
public:
    KnotKey() = default;
    KnotKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept;

    /// Reconstruire une clé depuis l'identifiant d'instance seul : l'identifiant
    /// d'exécution est celui de ce concept-ci.
    ///
    /// EXPLICITE, LÀ OÙ LE PACK LAISSAIT LA CONVERSION IMPLICITE. Toutes les clés du modèle
    /// ont la même forme, donc une conversion implicite depuis `UUId` fait de n'importe quel
    /// identifiant n'importe quelle clé, en silence -- ce que le typage des clés existe
    /// justement pour empêcher. `KnotKey{id}` dit la même chose et la dit exprès.
    explicit KnotKey(Viper::UUId const & instanceId) noexcept;

    static KnotKey create();

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
    Crossing::AnyConceptKey toAny() const noexcept;
    static std::optional<KnotKey> from(Crossing::AnyConceptKey const & key) noexcept;


private:
    Viper::UUId _instanceId{};
    Viper::UUId _runtimeId{};
};

bool operator==(KnotKey const &, KnotKey const &) noexcept;
bool operator!=(KnotKey const &, KnotKey const &) noexcept;
bool operator<(KnotKey const &, KnotKey const &) noexcept;

void hash(Viper::Hash::Accumulator & h, KnotKey const & value) noexcept;

/** Un concept dont le parent vit ailleurs. */
class DerivedKey final {
public:
    DerivedKey() = default;
    DerivedKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept;

    /// Reconstruire une clé depuis l'identifiant d'instance seul : l'identifiant
    /// d'exécution est celui de ce concept-ci.
    ///
    /// EXPLICITE, LÀ OÙ LE PACK LAISSAIT LA CONVERSION IMPLICITE. Toutes les clés du modèle
    /// ont la même forme, donc une conversion implicite depuis `UUId` fait de n'importe quel
    /// identifiant n'importe quelle clé, en silence -- ce que le typage des clés existe
    /// justement pour empêcher. `DerivedKey{id}` dit la même chose et la dit exprès.
    explicit DerivedKey(Viper::UUId const & instanceId) noexcept;

    static DerivedKey create();

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
    /// Élargir vers le parent. Implicite, parce que `is a` n'est pas une demande : partout
    /// où le parent est attendu, le dérivé passe.
    operator Core::ThingKey() const noexcept;

    /// Et la même, nommée. DEUX FORMES DE LA MÊME CHOSE, ET LES DEUX SERVENT : l'implicite
    /// pour l'appelant qui passe la clé, la nommée pour celui qui la range ou l'écrit dans
    /// une expression où la conversion ne se déclencherait pas.
    Core::ThingKey toParentKey() const noexcept;
    Crossing::AnyConceptKey toAny() const noexcept;
    static std::optional<DerivedKey> from(Crossing::AnyConceptKey const & key) noexcept;


private:
    Viper::UUId _instanceId{};
    Viper::UUId _runtimeId{};
};

bool operator==(DerivedKey const &, DerivedKey const &) noexcept;
bool operator!=(DerivedKey const &, DerivedKey const &) noexcept;
bool operator<(DerivedKey const &, DerivedKey const &) noexcept;

void hash(Viper::Hash::Accumulator & h, DerivedKey const & value) noexcept;

/** Un club dont les membres viennent de deux fournisseurs ET PORTENT LE MÊME NOM : le nom
du getter ne peut pas être `asThingKey` des deux côtés, et un nom de fonction ne peut pas
contenir `::`. C'est le cas que Core::Klub ne montre pas, ses membres étant chez lui. */
class WeaveKey final {
public:
    WeaveKey() = default;
    WeaveKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept;

    /// Reconstruire une clé depuis l'identifiant d'instance seul : l'identifiant
    /// d'exécution est celui de ce concept-ci.
    ///
    /// EXPLICITE, LÀ OÙ LE PACK LAISSAIT LA CONVERSION IMPLICITE. Toutes les clés du modèle
    /// ont la même forme, donc une conversion implicite depuis `UUId` fait de n'importe quel
    /// identifiant n'importe quelle clé, en silence -- ce que le typage des clés existe
    /// justement pour empêcher. `WeaveKey{id}` dit la même chose et la dit exprès.
    explicit WeaveKey(Viper::UUId const & instanceId) noexcept;

    WeaveKey(Core::ThingKey const & key) noexcept;
    WeaveKey(Parts::ThingKey const & key) noexcept;

    std::optional<Core::ThingKey> asCoreThingKey() const noexcept;
    std::optional<Parts::ThingKey> asPartsThingKey() const noexcept;

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

    Crossing::AnyConceptKey toAny() const noexcept;
    static std::optional<WeaveKey> from(Crossing::AnyConceptKey const & key) noexcept;

private:
    Viper::UUId _instanceId{};
    Viper::UUId _runtimeId{};
};

bool operator==(WeaveKey const &, WeaveKey const &) noexcept;
bool operator!=(WeaveKey const &, WeaveKey const &) noexcept;
bool operator<(WeaveKey const &, WeaveKey const &) noexcept;

void hash(Viper::Hash::Accumulator & h, WeaveKey const & value) noexcept;


/** Les entités des deux fournisseurs, nues, comme champs. */
struct Entities final {
    Core::Grade f_core_grade{};
    Parts::Grade f_parts_grade{};
    Core::Colour f_core_colour{};
    Parts::Colour f_parts_colour{};
    Core::Single f_single{};
    Core::ThingKey f_thing{};
    Core::SubThingKey f_sub_thing{};
    Parts::ThingKey f_other_thing{};
    Core::KlubKey f_klub{};
    ::Crossing::AnyConceptKey f_any_concept{};
};

bool operator==(Entities const &, Entities const &) noexcept;
bool operator!=(Entities const &, Entities const &) noexcept;
bool operator<(Entities const &, Entities const &) noexcept;

void hash(Viper::Hash::Accumulator & h, Entities const & value) noexcept;

/** Chaque conteneur, avec des éléments des deux fournisseurs. */
struct Composites final {
    std::tuple<Core::Colour, Parts::Colour> f_tuple{};
    std::optional<Core::ThingKey> f_optional{};
    std::vector<Parts::Colour> f_vector{};
    std::set<Core::ThingKey> f_set{};
    std::map<Core::ThingKey, Parts::ThingKey> f_map_keys{};
    std::map<Core::Grade, Parts::Colour> f_map_enum{};
    Viper::XArray<Core::Colour> f_xarray{};
    std::variant<Core::Colour, Parts::Colour, std::string> f_variant{};
};

bool operator==(Composites const &, Composites const &) noexcept;
bool operator!=(Composites const &, Composites const &) noexcept;
bool operator<(Composites const &, Composites const &) noexcept;

void hash(Viper::Hash::Accumulator & h, Composites const & value) noexcept;

/** Une structure d'ici qui contient une structure d'ici : la profondeur reste locale. */
struct Nested final {
    Composites f_composites{};
    Entities f_entities{};
};

bool operator==(Nested const &, Nested const &) noexcept;
bool operator!=(Nested const &, Nested const &) noexcept;
bool operator<(Nested const &, Nested const &) noexcept;

void hash(Viper::Hash::Accumulator & h, Nested const & value) noexcept;

} // namespace Woven

template<> struct std::hash<Woven::KnotKey> {
    std::size_t operator()(Woven::KnotKey const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Woven::DerivedKey> {
    std::size_t operator()(Woven::DerivedKey const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Woven::WeaveKey> {
    std::size_t operator()(Woven::WeaveKey const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Woven::Entities> {
    std::size_t operator()(Woven::Entities const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Woven::Composites> {
    std::size_t operator()(Woven::Composites const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Woven::Nested> {
    std::size_t operator()(Woven::Nested const & v) const noexcept { return Viper::Hash::of(v); }
};

#endif