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
template<class T> void roundTrip(Rng & r) {
    auto const a = fuzz(r, Codec::tag<T>{});           // ADL : ModelA::fuzz
    (void)a;
}
}
#endif
