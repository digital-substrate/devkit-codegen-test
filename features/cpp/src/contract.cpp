// Ce que le pont promet au développeur, éprouvé depuis l'extérieur du code généré.
//
// Le programme d'épreuve généré fait l'aller-retour de chaque type ; celui-ci fixe ce qu'un
// aller-retour ne montre pas : le type que rend `encode`, et le refus de `decode` quand une
// valeur n'est pas du type demandé -- une clé d'un autre concept d'abord, qui a la même forme
// que la bonne et passerait sans lui.
#include "features_codec.hpp"
#include "features_attachment_pool.hpp"

#include "Viper_AttachmentFunction.hpp"
#include "Viper_FunctionPrototype.hpp"
#include "Viper_TypeSet.hpp"

#include <iostream>
#include <type_traits>

using namespace features;

// encode rend la classe de Value que le type devient -- vérifié à la compilation.
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
        std::cout << "ACCEPTÉ " << name << "\n";
        ++failures;
    } catch (std::exception const &) {
    }
}

} // namespace

int main() {
    refused<demo::ConceptAKey>("clé de ConceptB lue comme ConceptAKey", [] { return codec::encode(demo::ConceptBKey::create()); });
    refused<demo::StructureS>("StructureT lue comme StructureS", [] { return codec::encode(demo::StructureT{}); });
    refused<std::uint16_t>("uint8 lu comme uint16", [] { return codec::encode(std::uint8_t{7}); });
    refused<std::vector<demo::StructureS>>("vector<StructureT> lu comme vector<StructureS>",
                                           [] { return codec::encode(std::vector<demo::StructureT>{{}}); });

    auto const key{demo::ConceptAKey::create()};
    if (!(codec::decode<demo::ConceptAKey>(codec::encode(key)) == key)) {
        std::cout << "une clé ne revient pas d'un aller-retour\n";
        ++failures;
    }
    // Le pool des attachments se construit, et ses prototypes parlent de clés, pas de concepts :
    // un paramètre `key` est une clé, `keys` rend un ensemble de clés. Une application l'enregistre
    // au démarrage ; s'il ne se construit pas, rien ne s'ouvre.
    auto const pool{features::attachment_pool()};
    for (auto const & f : pool->functions()) {
        auto const & prototype{f->prototype};
        for (auto const & parameter : prototype->parameters)
            if (parameter.name == "key" && parameter.type->typeCode != Viper::TypeCode::Key) {
                std::cout << prototype->name << " : le paramètre key n'est pas une clé\n";
                ++failures;
            }
        auto const isKeys{prototype->name.size() > 5 && prototype->name.substr(prototype->name.size() - 5) == "_keys"};
        if (isKeys && (prototype->returnType->typeCode != Viper::TypeCode::Set
                       || Viper::TypeSet::cast(prototype->returnType)->elementType->typeCode != Viper::TypeCode::Key)) {
            std::cout << prototype->name << " : ne rend pas un ensemble de clés\n";
            ++failures;
        }
    }

    return failures ? 1 : 0;
}
