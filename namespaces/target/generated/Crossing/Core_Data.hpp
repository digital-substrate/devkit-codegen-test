// unité Core — les types qu'elle déclare.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

#ifndef Core_Data_hpp
#define Core_Data_hpp


#include "Crossing_AnyConcept.hpp"

#include "Viper_Hash.hpp"
#include "Viper_Scalars.hpp"
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

namespace Core {

/**  */
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

void hash(Viper::Hash::Accumulator & h, OtherKey const & value) noexcept;

/** Ce sur quoi on accroche des choses. */
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

void hash(Viper::Hash::Accumulator & h, ThingKey const & value) noexcept;

/** Un dérivé, dans le même namespace : le cas facile de l'héritage. */
class SubThingKey final {
public:
    SubThingKey() = default;
    SubThingKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept;

    static SubThingKey create();

    Viper::UUId const & instanceId() const noexcept;
    Viper::UUId const & runtimeId() const noexcept;

    bool isValid() const noexcept;
    /// Widen to the parent concept. Implicit, because `is a` is not a request.
    operator ThingKey() const noexcept;
    Crossing::AnyConceptKey toAny() const noexcept;
    static std::optional<SubThingKey> from(Crossing::AnyConceptKey const & key) noexcept;


private:
    Viper::UUId _instanceId{};
    Viper::UUId _runtimeId{};
};

bool operator==(SubThingKey const &, SubThingKey const &) noexcept;
bool operator!=(SubThingKey const &, SubThingKey const &) noexcept;
bool operator<(SubThingKey const &, SubThingKey const &) noexcept;

void hash(Viper::Hash::Accumulator & h, SubThingKey const & value) noexcept;

/** Un club, dont les membres vivent ici. */
class KlubKey final {
public:
    KlubKey() = default;
    KlubKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept;

    KlubKey(OtherKey const & key) noexcept;
    KlubKey(SubThingKey const & key) noexcept;

    std::optional<OtherKey> asOtherKey() const noexcept;
    std::optional<SubThingKey> asSubThingKey() const noexcept;

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

void hash(Viper::Hash::Accumulator & h, KlubKey const & value) noexcept;

/** Une énumération, que d'autres namespaces vont référencer. */
enum class Grade {
    Low,
    High
};

void hash(Viper::Hash::Accumulator & h, Grade value) noexcept;

/** Le même nom que Parts::Colour, un type différent -- la collision de re-export. */
struct Colour final {
    std::uint8_t r{};
    std::uint8_t g{};
    std::uint8_t b{};
};

bool operator==(Colour const &, Colour const &) noexcept;
bool operator!=(Colour const &, Colour const &) noexcept;
bool operator<(Colour const &, Colour const &) noexcept;

void hash(Viper::Hash::Accumulator & h, Colour const & value) noexcept;

/** Toutes les formes scalaires du langage, dans le namespace qui n'en référence aucun
autre. Ce qui ne peut pas traverser une frontière est couvert ici, une fois. */
struct Scalars final {
    bool f_bool{};
    std::uint8_t f_uint8{};
    std::uint16_t f_uint16{};
    std::uint32_t f_uint32{};
    std::uint64_t f_uint64{};
    std::int8_t f_int8{};
    std::int16_t f_int16{};
    std::int32_t f_int32{};
    std::int64_t f_int64{};
    float f_float{};
    double f_double{};
    Viper::BlobId f_blob_id{};
    Viper::CommitId f_commit_id{};
    Viper::UUId f_uuid{};
    std::string f_string{};
    Viper::Blob f_blob{};
    Viper::Any f_any{};
    std::array<std::uint8_t, 2> f_vec{};
    std::array<std::array<std::uint8_t, 2>, 2> f_mat{};
};

bool operator==(Scalars const &, Scalars const &) noexcept;
bool operator!=(Scalars const &, Scalars const &) noexcept;
bool operator<(Scalars const &, Scalars const &) noexcept;

void hash(Viper::Hash::Accumulator & h, Scalars const & value) noexcept;

/** Une structure à un seul champ : le cas zéro/un que le générateur traite à part. */
struct Single final {
    std::uint8_t f_single{};
};

bool operator==(Single const &, Single const &) noexcept;
bool operator!=(Single const &, Single const &) noexcept;
bool operator<(Single const &, Single const &) noexcept;

void hash(Viper::Hash::Accumulator & h, Single const & value) noexcept;

/** Et un document ordinaire dont un champ est un agrégat : les mêmes opérations, à une
adresse au lieu de la racine. */
struct Bag final {
    std::set<ThingKey> members{};
    std::map<ThingKey, Colour> tints{};
    Viper::XArray<Colour> trail{};
};

bool operator==(Bag const &, Bag const &) noexcept;
bool operator!=(Bag const &, Bag const &) noexcept;
bool operator<(Bag const &, Bag const &) noexcept;

void hash(Viper::Hash::Accumulator & h, Bag const & value) noexcept;

/** Les valeurs par défaut, qui sont un chemin de code à part. */
struct Defaults final {
    std::uint8_t f_uint8{};
    float f_float{};
    std::string f_string{};
    Viper::UUId f_uuid{};
    std::array<std::uint8_t, 2> f_vec{};
    Grade f_grade{};
    Colour f_colour{};
};

bool operator==(Defaults const &, Defaults const &) noexcept;
bool operator!=(Defaults const &, Defaults const &) noexcept;
bool operator<(Defaults const &, Defaults const &) noexcept;

void hash(Viper::Hash::Accumulator & h, Defaults const & value) noexcept;

} // namespace Core

template<> struct std::hash<Core::OtherKey> {
    std::size_t operator()(Core::OtherKey const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Core::ThingKey> {
    std::size_t operator()(Core::ThingKey const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Core::SubThingKey> {
    std::size_t operator()(Core::SubThingKey const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Core::KlubKey> {
    std::size_t operator()(Core::KlubKey const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Core::Colour> {
    std::size_t operator()(Core::Colour const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Core::Scalars> {
    std::size_t operator()(Core::Scalars const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Core::Single> {
    std::size_t operator()(Core::Single const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Core::Bag> {
    std::size_t operator()(Core::Bag const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Core::Defaults> {
    std::size_t operator()(Core::Defaults const & v) const noexcept { return Viper::Hash::of(v); }
};

#endif