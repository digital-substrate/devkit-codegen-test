// unité Test — les types qu'elle déclare.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/features/Features.dsm.json by kibo-2.0.0.jar

#ifndef Test_Data_hpp
#define Test_Data_hpp


#include "Features_AnyConcept.hpp"

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

namespace Test {

/** This is the documentation for the concept A */
class ConceptAKey final {
public:
    ConceptAKey() = default;
    ConceptAKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept;

    static ConceptAKey create();

    Viper::UUId const & instanceId() const noexcept;
    Viper::UUId const & runtimeId() const noexcept;

    bool isValid() const noexcept;
    Features::AnyConceptKey toAny() const noexcept;
    static std::optional<ConceptAKey> from(Features::AnyConceptKey const & key) noexcept;


private:
    Viper::UUId _instanceId{};
    Viper::UUId _runtimeId{};
};

bool operator==(ConceptAKey const &, ConceptAKey const &) noexcept;
bool operator!=(ConceptAKey const &, ConceptAKey const &) noexcept;
bool operator<(ConceptAKey const &, ConceptAKey const &) noexcept;

void hash(Viper::Hash::Accumulator & h, ConceptAKey const & value) noexcept;

/**  */
class ConceptBKey final {
public:
    ConceptBKey() = default;
    ConceptBKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept;

    static ConceptBKey create();

    Viper::UUId const & instanceId() const noexcept;
    Viper::UUId const & runtimeId() const noexcept;

    bool isValid() const noexcept;
    Features::AnyConceptKey toAny() const noexcept;
    static std::optional<ConceptBKey> from(Features::AnyConceptKey const & key) noexcept;


private:
    Viper::UUId _instanceId{};
    Viper::UUId _runtimeId{};
};

bool operator==(ConceptBKey const &, ConceptBKey const &) noexcept;
bool operator!=(ConceptBKey const &, ConceptBKey const &) noexcept;
bool operator<(ConceptBKey const &, ConceptBKey const &) noexcept;

void hash(Viper::Hash::Accumulator & h, ConceptBKey const & value) noexcept;

/**  */
class ConceptCoverageKey final {
public:
    ConceptCoverageKey() = default;
    ConceptCoverageKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept;

    static ConceptCoverageKey create();

    Viper::UUId const & instanceId() const noexcept;
    Viper::UUId const & runtimeId() const noexcept;

    bool isValid() const noexcept;
    Features::AnyConceptKey toAny() const noexcept;
    static std::optional<ConceptCoverageKey> from(Features::AnyConceptKey const & key) noexcept;


private:
    Viper::UUId _instanceId{};
    Viper::UUId _runtimeId{};
};

bool operator==(ConceptCoverageKey const &, ConceptCoverageKey const &) noexcept;
bool operator!=(ConceptCoverageKey const &, ConceptCoverageKey const &) noexcept;
bool operator<(ConceptCoverageKey const &, ConceptCoverageKey const &) noexcept;

void hash(Viper::Hash::Accumulator & h, ConceptCoverageKey const & value) noexcept;

/**  */
class ConceptDKey final {
public:
    ConceptDKey() = default;
    ConceptDKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept;

    static ConceptDKey create();

    Viper::UUId const & instanceId() const noexcept;
    Viper::UUId const & runtimeId() const noexcept;

    bool isValid() const noexcept;
    Features::AnyConceptKey toAny() const noexcept;
    static std::optional<ConceptDKey> from(Features::AnyConceptKey const & key) noexcept;


private:
    Viper::UUId _instanceId{};
    Viper::UUId _runtimeId{};
};

bool operator==(ConceptDKey const &, ConceptDKey const &) noexcept;
bool operator!=(ConceptDKey const &, ConceptDKey const &) noexcept;
bool operator<(ConceptDKey const &, ConceptDKey const &) noexcept;

void hash(Viper::Hash::Accumulator & h, ConceptDKey const & value) noexcept;

/**  */
class ConceptCKey final {
public:
    ConceptCKey() = default;
    ConceptCKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept;

    static ConceptCKey create();

    Viper::UUId const & instanceId() const noexcept;
    Viper::UUId const & runtimeId() const noexcept;

    bool isValid() const noexcept;
    /// Widen to the parent concept. Implicit, because `is a` is not a request.
    operator ConceptBKey() const noexcept;
    Features::AnyConceptKey toAny() const noexcept;
    static std::optional<ConceptCKey> from(Features::AnyConceptKey const & key) noexcept;


private:
    Viper::UUId _instanceId{};
    Viper::UUId _runtimeId{};
};

bool operator==(ConceptCKey const &, ConceptCKey const &) noexcept;
bool operator!=(ConceptCKey const &, ConceptCKey const &) noexcept;
bool operator<(ConceptCKey const &, ConceptCKey const &) noexcept;

void hash(Viper::Hash::Accumulator & h, ConceptCKey const & value) noexcept;

/**  */
class EmptyKlubKey final {
public:
    EmptyKlubKey() = default;
    EmptyKlubKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept;



    Viper::UUId const & instanceId() const noexcept;
    Viper::UUId const & runtimeId() const noexcept;
    bool isValid() const noexcept;

    Features::AnyConceptKey toAny() const noexcept;
    static std::optional<EmptyKlubKey> from(Features::AnyConceptKey const & key) noexcept;

private:
    Viper::UUId _instanceId{};
    Viper::UUId _runtimeId{};
};

bool operator==(EmptyKlubKey const &, EmptyKlubKey const &) noexcept;
bool operator!=(EmptyKlubKey const &, EmptyKlubKey const &) noexcept;
bool operator<(EmptyKlubKey const &, EmptyKlubKey const &) noexcept;

void hash(Viper::Hash::Accumulator & h, EmptyKlubKey const & value) noexcept;

/** This is the documentation for the concept D */
class KlubKey final {
public:
    KlubKey() = default;
    KlubKey(Viper::UUId const & instanceId, Viper::UUId const & runtimeId) noexcept;

    KlubKey(ConceptCKey const & key) noexcept;
    KlubKey(ConceptDKey const & key) noexcept;

    std::optional<ConceptCKey> asConceptCKey() const noexcept;
    std::optional<ConceptDKey> asConceptDKey() const noexcept;

    Viper::UUId const & instanceId() const noexcept;
    Viper::UUId const & runtimeId() const noexcept;
    bool isValid() const noexcept;

    Features::AnyConceptKey toAny() const noexcept;
    static std::optional<KlubKey> from(Features::AnyConceptKey const & key) noexcept;

private:
    Viper::UUId _instanceId{};
    Viper::UUId _runtimeId{};
};

bool operator==(KlubKey const &, KlubKey const &) noexcept;
bool operator!=(KlubKey const &, KlubKey const &) noexcept;
bool operator<(KlubKey const &, KlubKey const &) noexcept;

void hash(Viper::Hash::Accumulator & h, KlubKey const & value) noexcept;

/** This is the documentation for enumeration E */
enum class EnumerationE {
    A,
    B,
    C
};

void hash(Viper::Hash::Accumulator & h, EnumerationE value) noexcept;

/** This is the documentation for the struct S */
struct StructureS final {
    float f_float{};
    std::string f_string{};
};

bool operator==(StructureS const &, StructureS const &) noexcept;
bool operator!=(StructureS const &, StructureS const &) noexcept;
bool operator<(StructureS const &, StructureS const &) noexcept;

void hash(Viper::Hash::Accumulator & h, StructureS const & value) noexcept;

/**  */
struct StructureW final {
    std::uint8_t f_single{};
};

bool operator==(StructureW const &, StructureW const &) noexcept;
bool operator!=(StructureW const &, StructureW const &) noexcept;
bool operator<(StructureW const &, StructureW const &) noexcept;

void hash(Viper::Hash::Accumulator & h, StructureW const & value) noexcept;

/**  */
struct StructureT final {
    std::string field_string{};
    StructureS field_structure_s{};
};

bool operator==(StructureT const &, StructureT const &) noexcept;
bool operator!=(StructureT const &, StructureT const &) noexcept;
bool operator<(StructureT const &, StructureT const &) noexcept;

void hash(Viper::Hash::Accumulator & h, StructureT const & value) noexcept;

/**  */
struct StructureV final {
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
    Viper::UUId f_uuid{};
    std::string f_string{};
    std::array<std::uint8_t, 2> f_vec{};
    std::array<std::array<std::uint8_t, 3>, 2> f_mat{};
    std::tuple<std::uint8_t, std::string> f_tuple{};
    std::optional<std::uint8_t> f_optional{};
    std::vector<std::uint8_t> f_vector{};
    std::set<std::uint8_t> f_set{};
    std::map<std::uint8_t, std::string> f_map{};
    EnumerationE f_E{};
    StructureS f_S{};
    StructureT f_T{};
};

bool operator==(StructureV const &, StructureV const &) noexcept;
bool operator!=(StructureV const &, StructureV const &) noexcept;
bool operator<(StructureV const &, StructureV const &) noexcept;

void hash(Viper::Hash::Accumulator & h, StructureV const & value) noexcept;

/**  */
struct StructureU final {
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
    std::array<std::uint8_t, 2> f_vec{};
    std::array<std::array<std::uint8_t, 2>, 2> f_mat{};
    std::tuple<std::uint8_t, std::string> f_tuple{};
    std::optional<std::uint8_t> f_optional{};
    std::vector<std::uint8_t> f_vector{};
    std::set<std::uint8_t> f_set{};
    std::set<StructureS> f_set_s{};
    std::map<StructureS, std::string> f_map_s1{};
    std::map<std::string, StructureS> f_map_s2{};
    Viper::XArray<std::uint8_t> f_xarray{};
    Viper::XArray<StructureS> f_xarray_s{};
    std::map<std::vector<StructureS>, std::string> f_map_vs{};
    std::variant<std::string, std::uint8_t, StructureS> f_variant{};
    Viper::Any f_any{};
    EnumerationE f_E{};
    StructureS f_S{};
    StructureT f_T{};
    ConceptAKey f_A{};
    ConceptBKey f_B{};
    ConceptCKey f_C{};
    ConceptDKey f_D{};
    KlubKey f_Klub{};
    ::Features::AnyConceptKey f_any_concept{};
};

bool operator==(StructureU const &, StructureU const &) noexcept;
bool operator!=(StructureU const &, StructureU const &) noexcept;
bool operator<(StructureU const &, StructureU const &) noexcept;

void hash(Viper::Hash::Accumulator & h, StructureU const & value) noexcept;

} // namespace Test

template<> struct std::hash<Test::ConceptAKey> {
    std::size_t operator()(Test::ConceptAKey const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Test::ConceptBKey> {
    std::size_t operator()(Test::ConceptBKey const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Test::ConceptCoverageKey> {
    std::size_t operator()(Test::ConceptCoverageKey const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Test::ConceptDKey> {
    std::size_t operator()(Test::ConceptDKey const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Test::ConceptCKey> {
    std::size_t operator()(Test::ConceptCKey const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Test::EmptyKlubKey> {
    std::size_t operator()(Test::EmptyKlubKey const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Test::KlubKey> {
    std::size_t operator()(Test::KlubKey const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Test::StructureS> {
    std::size_t operator()(Test::StructureS const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Test::StructureW> {
    std::size_t operator()(Test::StructureW const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Test::StructureT> {
    std::size_t operator()(Test::StructureT const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Test::StructureV> {
    std::size_t operator()(Test::StructureV const & v) const noexcept { return Viper::Hash::of(v); }
};
template<> struct std::hash<Test::StructureU> {
    std::size_t operator()(Test::StructureU const & v) const noexcept { return Viper::Hash::of(v); }
};

#endif