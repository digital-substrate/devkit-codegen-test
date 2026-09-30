// What the bridge promises the developer, tested from outside the generated code.
//
// The generated test program round-trips every type; this one checks what a round trip does
// not show: the type `encode` returns, and `decode` refusing a value that is not of the
// requested type -- first a key of another concept, which has the same shape as the right
// one and would pass without this check.
#include "features_codec.hpp"
#include "features_attachment_pool.hpp"

#include "Viper_AttachmentFunction.hpp"
#include "Viper_FunctionPrototype.hpp"
#include "Viper_TypeSet.hpp"

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
    // The attachment pool builds, and its prototypes speak of keys, not concepts: a `key`
    // parameter is a key, `keys` returns a set of keys. An application registers it at startup;
    // if it does not build, nothing opens.
    auto const pool{features::attachment_pool()};
    for (auto const & f : pool->functions()) {
        auto const & prototype{f->prototype};
        for (auto const & parameter : prototype->parameters)
            if (parameter.name == "key" && parameter.type->typeCode != Viper::TypeCode::Key) {
                std::cout << prototype->name << ": the key parameter is not a key\n";
                ++failures;
            }
        auto const isKeys{prototype->name.size() > 5 && prototype->name.substr(prototype->name.size() - 5) == "_keys"};
        if (isKeys && (prototype->returnType->typeCode != Viper::TypeCode::Set
                       || Viper::TypeSet::cast(prototype->returnType)->elementType->typeCode != Viper::TypeCode::Key)) {
            std::cout << prototype->name << ": does not return a set of keys\n";
            ++failures;
        }
    }

    return failures ? 1 : 0;
}
