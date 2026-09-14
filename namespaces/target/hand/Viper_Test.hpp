#ifndef Viper_Test_hpp
#define Viper_Test_hpp
#include "Viper_Codec.hpp"
#include <cstdint>
#include <random>
#include <set>
namespace Viper::Test {
using Rng = std::mt19937_64;
std::uint8_t fuzz(Rng &, Codec::tag<std::uint8_t>);
float        fuzz(Rng &, Codec::tag<float>);
template<class T> std::set<T> fuzz(Rng & r, Codec::tag<std::set<T>>) {
    return {fuzz(r, Codec::tag<T>{})};                 // ADL sur l'élément
}
// L'aller-retour est générique : fabriquer, écrire, relire. Les trois passent par ADL,
// ce qui est la raison pour laquelle un en-tête de test inclut le codec de son unité :
// l'instanciation a lieu chez l'appelant, et les déclarations doivent y être visibles.
template<class T> void roundTrip(Rng & r, Codec::Writer & w, Codec::Reader & d) {
    auto const a = fuzz(r, Codec::tag<T>{});           // ADL : ModelA::fuzz
    write(w, a);                                       // ADL : ModelA::write
    auto const b = read(d, Codec::tag<T>{});           // ADL : ModelA::read
    (void)a; (void)b;
}
}
#endif
