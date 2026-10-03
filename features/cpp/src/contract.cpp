// What the bridge promises the developer, tested from outside the generated code.
//
// The generated test program round-trips every type; this one checks what a round trip does
// not show: the type `encode` returns, and `decode` refusing a value that is not of the
// requested type -- first a key of another concept, which has the same shape as the right
// one and would pass without this check.
#include "features_codec.hpp"

#include <iostream>
#include <type_traits>

using namespace features;

// encode returns the Value class the type becomes -- checked at compile time.
static_assert(std::is_same_v<decltype(codec::encode(std::declval<demo::ConceptAKey>())), std::shared_ptr<Viper::ValueKey>>);
static_assert(std::is_same_v<decltype(codec::encode(std::declval<demo::StructureS>())), std::shared_ptr<Viper::ValueStructure>>);
static_assert(std::is_same_v<decltype(codec::encode(std::declval<demo::EnumerationE>())), std::shared_ptr<Viper::ValueEnumeration>>);
static_assert(std::is_same_v<decltype(codec::encode(std::declval<std::vector<demo::StructureS>>())), std::shared_ptr<Viper::ValueVector>>);
static_assert(std::is_same_v<decltype(codec::encode(std::declval<AnyConceptKey>())), std::shared_ptr<Viper::ValueKey>>);

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

} // namespace

int main() {
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
