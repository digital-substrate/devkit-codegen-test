#include "ModelA_Data.hpp"
#include "ModelB_Data.hpp"
#include "Projection_Data.hpp"
#include <map>
#include <unordered_map>

void use() {
    // deux Material homonymes, aucun renommage
    ModelA::MaterialKey a;
    ModelB::MaterialKey b;
    ModelA::Colour ca{1, 2, 3};        // agrégat, initialisation par accolades
    ModelB::Colour cb{1.f, 2.f, 3.f};

    // la composition, qualifiée là où elle doit l'être
    Projection::Pair p{a, b};

    // « is a » : le dérivé passe où le parent est attendu, sans être demandé
    Projection::DerivedMaterialKey d;
    ModelA::MaterialKey widened = d;
    [](ModelA::MaterialKey) {}(d);

    // utilisable en conteneur, ordonné et haché
    std::map<ModelA::MaterialKey, ModelB::MaterialKey> ordered;
    std::unordered_map<Projection::Pair, int> hashed;
    (void)ca; (void)cb; (void)p; (void)widened; (void)ordered; (void)hashed;
}

#include "ModelA_Fields.hpp"
#include "Projection_Fields.hpp"

void use_fields() {
    // le nom, utilisable en expression constante
    static_assert(ModelA::Fields::Colour::r == "r");
    constexpr auto n = ModelA::Fields::Colour::g;

    // l'adresse, pour une opération partielle
    auto const & p = ModelA::Fields::Colour::rPath();
    auto const & q = Projection::Fields::Pair::aPath();
    (void)n; (void)p; (void)q;
}
