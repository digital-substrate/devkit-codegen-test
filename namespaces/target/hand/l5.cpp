#include "ModelA_Test.hpp"

void use_l5(Viper::Test::Rng & rng) {
    // le type de l'unité, fuzzé par l'unité
    auto const c = ModelA::fuzz(rng, Viper::Codec::tag<ModelA::Colour>{});

    // un conteneur de ce type : générique, aucune ligne dans l'unité
    auto const s = Viper::Test::fuzz(rng, Viper::Codec::tag<std::set<ModelA::Colour>>{});

    // et l'aller-retour, générique aussi
    Viper::Test::roundTrip<ModelA::Colour>(rng);
    (void)c; (void)s;
}
