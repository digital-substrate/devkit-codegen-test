#include "ModelA_Data.hpp"
#include "ModelB_Data.hpp"
#include "Projection_Data.hpp"
#include <map>
#include <unordered_map>

void use() {
    // deux Material homonymes, aucun renommage
    model_a::MaterialKey a;
    model_b::MaterialKey b;
    model_a::Colour ca{1, 2, 3};        // agrégat, initialisation par accolades
    model_b::Colour cb{1.f, 2.f, 3.f};

    // la composition, qualifiée là où elle doit l'être
    projection::Pair p{a, b};

    // « is a » : le dérivé passe où le parent est attendu, sans être demandé
    projection::DerivedMaterialKey d;
    model_a::MaterialKey widened = d;
    [](model_a::MaterialKey) {}(d);

    // utilisable en conteneur, ordonné et haché
    std::map<model_a::MaterialKey, model_b::MaterialKey> ordered;
    std::unordered_map<projection::Pair, int> hashed;
    (void)ca; (void)cb; (void)p; (void)widened; (void)ordered; (void)hashed;
}

#include "ModelA_Fields.hpp"
#include "Projection_Fields.hpp"

void use_fields() {
    // le nom, utilisable en expression constante
    static_assert(model_a::fields::Colour::r == "r");
    constexpr auto n = model_a::fields::Colour::g;

    // l'adresse, pour une opération partielle
    auto const & p = model_a::fields::Colour::rPath();
    auto const & q = projection::fields::Pair::aPath();
    (void)n; (void)p; (void)q;
}
