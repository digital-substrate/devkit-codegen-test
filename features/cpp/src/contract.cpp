// What the bridge promises the developer, tested from outside the generated code.
//
// The generated test program round-trips every type; this one checks what a round trip does
// not show: the type `encode` returns, and `decode` refusing a value that is not of the
// requested type -- first a key of another concept, which has the same shape as the right
// one and would pass without this check.
#include "features_codec.hpp"
#include "features_demo_fields.hpp"
#include "features_demo_paths.hpp"
#include "Viper_HashSHA1.hpp"
#include "Viper_StreamEncoding.hpp"
#include "Viper_ValueEncoder.hpp"
#include "Viper_ValueFloat.hpp"
#include "Viper_ValueHasher.hpp"
#include "Viper_ValueStructure.hpp"

#include <cmath>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <limits>
#include <type_traits>
#include <vector>

using namespace features;

// encode returns the Value class the type becomes -- checked at compile time.
static_assert(std::is_same_v<decltype(codec::encode(std::declval<demo::ConceptAKey>())), std::shared_ptr<Viper::ValueKey>>);
static_assert(std::is_same_v<decltype(codec::encode(std::declval<demo::StructureS>())), std::shared_ptr<Viper::ValueStructure>>);
static_assert(std::is_same_v<decltype(codec::encode(std::declval<demo::EnumerationE>())), std::shared_ptr<Viper::ValueEnumeration>>);
static_assert(std::is_same_v<decltype(codec::encode(std::declval<std::vector<demo::StructureS>>())), std::shared_ptr<Viper::ValueVector>>);
static_assert(std::is_same_v<decltype(codec::encode(std::declval<AnyConceptKey>())), std::shared_ptr<Viper::ValueKey>>);

// A field's name is the model's, usable in a constant expression.
static_assert(demo::fields::StructureS::f_float == "f_float");

// A key widens implicitly to every ancestor, as the 1.2 surface did -- not to its parent alone.
static_assert(std::is_convertible_v<demo::ConceptEKey, demo::ConceptCKey>);
static_assert(std::is_convertible_v<demo::ConceptEKey, demo::ConceptBKey>);

namespace {

int failures{};

template<class T, class F>
void refused(char const * name, F make) {
    try {
        (void)codec::decode<T>(make());
        std::cout << "ACCEPTED " << name << "\n";
        ++failures;
    } catch (std::exception const &) {
    }
}

// A structure holding the same number in every field shape: NaN, the infinities and the two
// zeros among them.
demo::StructureNumbers numbers(double n, Viper::UUId const & position) {
    demo::StructureNumbers result{};
    result.f_double = n;
    result.f_float = static_cast<float>(n);
    result.f_vec = {n, 1.0, 2.0};
    result.f_mat = {{{static_cast<float>(n), 0.0f}, {0.0f, 1.0f}}};
    result.f_optional = n;
    result.f_vector = {n};
    result.f_tuple = {n, 3};
    result.f_variant = n;
    result.f_map = {{"a", n}};
    result.f_xarray.insert(Viper::UUId::Invalid(), n, position);
    result.f_S.f_float = static_cast<float>(n);
    result.f_set = {n, 1.0};
    result.f_map_by_vec = {{{static_cast<float>(n), 1.0f}, 7}};
    return result;
}

// == is an equivalence, < a strict weak order whose incomparability is ==, and the hash
// follows ==, NaN and the two zeros included.
void rigour() {
    std::uint64_t const bits{0xFFF8000000000001ull};
    double otherNaN;
    std::memcpy(&otherNaN, &bits, sizeof otherNaN);
    double const inf{std::numeric_limits<double>::infinity()};
    auto const position{Viper::UUId::create()};
    std::vector<demo::StructureNumbers> values;
    for (double const n : {std::numeric_limits<double>::quiet_NaN(), otherNaN, -inf, -1.0, -0.0, 0.0, 1.0, inf})
        values.push_back(numbers(n, position));

    auto const hashOf{[](demo::StructureNumbers const & v) { return Viper::StaticHash::of(v); }};
    int broken{};
    for (auto const & a : values) {
        if (!(a == a) || a < a)
            ++broken;
        for (auto const & b : values) {
            bool const equal{a == b};
            if (equal != (b == a) || equal != (!(a < b) && !(b < a)) || (a < b && b < a))
                ++broken;
            if (equal && hashOf(a) != hashOf(b))
                ++broken;
            for (auto const & c : values)
                if (a < b && b < c && !(a < c))
                    ++broken;
        }
    }
    if (!(values.at(0) == values.at(1)) || !(values.at(4) == values.at(5)) || !(values.at(0) < values.at(2))) {
        std::cout << "every NaN is not one datum, or the two zeros not one, or NaN not below -inf\n";
        ++failures;
    }
    // A set or a map keyed by a floating-point value finds NaN, and holds one NaN and one zero.
    decltype(demo::StructureNumbers::f_set) keyed{std::numeric_limits<double>::quiet_NaN(), otherNaN, -0.0, 0.0, 1.0};
    if (keyed.size() != 3 || keyed.count(otherNaN) != 1 || !std::isnan(*keyed.begin())) {
        std::cout << "a set of double does not hold NaN as one datum below every number\n";
        ++failures;
    }
    if (broken) {
        std::cout << "a structure holding NaN, an infinity or a zero breaks ==, < or its hash (" << broken << " cases)\n";
        ++failures;
    }
}

// The bytes the static writer writes are the bytes the runtime writes for the same value, so
// equal data have one BlobId; and equal values have one digest. NaN of any bits and the two
// zeros included.
void contentAddressing() {
    std::uint64_t const bits{0xFFF8000000000001ull};
    double otherNaN;
    std::memcpy(&otherNaN, &bits, sizeof otherNaN);
    double const inf{std::numeric_limits<double>::infinity()};
    auto const position{Viper::UUId::create()};
    std::vector<demo::StructureNumbers> values;
    for (double const n : {std::numeric_limits<double>::quiet_NaN(), otherNaN, -inf, -1.0, -0.0, 0.0, 1.0, inf})
        values.push_back(numbers(n, position));

    auto const staticBytes{[](demo::StructureNumbers const & v) {
        auto const encoder{codec::stream()->createEncoder()};
        Viper::StaticWriter::Writer w{encoder};
        write(w, v);
        return encoder->endEncoding();
    }};
    auto const digest{[](demo::StructureNumbers const & v) {
        auto const hashing{Viper::HashSHA1::make()};
        Viper::ValueHasher::hash(codec::encode(v), hashing);
        return hashing->hexDigest();
    }};

    int broken{};
    for (auto const & a : values) {
        if (!(staticBytes(a) == Viper::ValueEncoder::encode(codec::encode(a), codec::stream())))
            ++broken;
        for (auto const & b : values)
            if (a == b && digest(a) != digest(b))
                ++broken;
    }
    if (!(staticBytes(values.at(0)) == staticBytes(values.at(1)))) {
        std::cout << "a NaN of other bits is not written as the canonical NaN\n";
        ++failures;
    }
    if (broken) {
        std::cout << "a structure holding NaN or a zero is written apart from the runtime, or equal values digest apart (" << broken << " cases)\n";
        ++failures;
    }
}

} // namespace

int main() {
    rigour();
    contentAddressing();

    refused<demo::ConceptAKey>("ConceptB key read as ConceptAKey", [] { return codec::encode(demo::ConceptBKey::create()); });
    refused<demo::StructureS>("StructureT read as StructureS", [] { return codec::encode(demo::StructureT{}); });
    refused<std::uint16_t>("uint8 read as uint16", [] { return codec::encode(std::uint8_t{7}); });
    refused<std::vector<demo::StructureS>>("vector<StructureT> read as vector<StructureS>",
                                           [] { return codec::encode(std::vector<demo::StructureT>{{}}); });

    auto const key{demo::ConceptAKey::create()};
    if (!(codec::decode<demo::ConceptAKey>(codec::encode(key)) == key)) {
        std::cout << "a key does not survive a round trip\n";
        ++failures;
    }

    // A parent key narrows to a local descendant by name, as the 1.2 surface did.
    auto const c{demo::ConceptCKey::create()};
    demo::ConceptBKey const b{c};
    if (!(b.asConceptCKey() == c) || demo::ConceptBKey::create().asConceptCKey().has_value()) {
        std::cout << "a parent key does not narrow to its descendant\n";
        ++failures;
    }
    // A field's path addresses that field: it reads it in a value it was not built from.
    demo::StructureS pathed{};
    pathed.f_float = 1.5f;
    if (!demo::paths::StructureS::f_float()->at(codec::encode(pathed))->equal(Viper::ValueFloat::make(1.5f))) {
        std::cout << "a field's path does not read its field\n";
        ++failures;
    }

    auto const e{demo::ConceptEKey::create()};
    demo::ConceptBKey const grand{e};
    if (!(grand.toAny() == e.toAny())) {
        std::cout << "a key widened to its grandparent does not designate the same instance\n";
        ++failures;
    }
    if (!(b.toAnyConceptKey() == c.toAny())) {
        std::cout << "toAnyConceptKey() differs from toAny()\n";
        ++failures;
    }

    // A structure is built from its fields in declaration order, in C++17, as the 1.2
    // structures were: a double literal narrows to a float field, and a one-field structure
    // converts from its field.
    demo::StructureS const s(0.5, "x");
    demo::StructureW const w = std::uint8_t{7};
    if (!(s.f_float == 0.5f && s.f_string == "x" && w.f_single == 7 && demo::StructureS{} == demo::StructureS(0, ""))) {
        std::cout << "a structure is not built from its fields\n";
        ++failures;
    }

    return failures ? 1 : 0;
}
