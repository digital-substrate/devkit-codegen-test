// Topology — de quoi éprouver n'importe quel type du modèle, sans rien savoir d'aucun.
//
// SEPT ARTEFACTS DU PACK TIENNENT ICI, et ce n'est pas une compression : c'est ce que leur
// propre source dit. `TestFuzz::fuzz_X()` vaut `decode_X(TestValueFuzz::fuzz_X())`,
// `TestValueFuzz::fuzz_X()` vaut `fuzzer()->fuzzType(type_X())`, et chaque `test_X` des
// trois codecs est un aller-retour dont seul le suffixe change. Une fois écrits en
// fonctions template au-dessus de `type(tag<T>{})`, il n'en reste rien par type.
//
// LE FUZZ N'EST PAS CELUI D'UNE UNITÉ, et c'est la correction que ce fichier apporte. Le
// premier jet déclarait `fuzz(Rng&, tag<T>)` dans chaque unité, en supposant qu'elle seule
// sait comment fabriquer un de ses types. Elle ne le sait pas mieux que le runtime : celui-
// ci part du descripteur de type, que l'unité fournit déjà. Une unité n'a donc rien à
// implémenter pour être éprouvée.

#ifndef Topology_Test_hpp
#define Topology_Test_hpp

#include "Topology_Codec.hpp"

#include "Viper_Assert.hpp"
#include "Viper_Fuzzer.hpp"
#include "Viper_Json.hpp"

#include <memory>

namespace Topology::Test {

/// Le fabricant, construit une fois sur le modèle. Une graine le rend reproductible.
std::shared_ptr<Viper::Fuzzer> const & fuzzer();
void seed(std::uint64_t value);

/// Une valeur aléatoire de T, côté dynamique puis côté statique.
template<class T>
std::shared_ptr<Viper::Value> fuzzValue() {
    return fuzzer()->fuzzType(type(Viper::Codec::tag<T>{}));   // ADL : l'unité de T
}

template<class T>
T fuzz() {
    return Codec::decode<T>(fuzzValue<T>());
}

// ── les trois allers-retours, un par codec ──
//
// Chacun est ce que le pack écrit une fois par type et par codec, avec le suffixe pour
// seule variable. Écrits une fois ici, ils ne demandent plus qu'une liste de types.

/// Fabriquer, écrire sur un flux, relire, comparer.
template<class T>
void roundTripStream() {
    auto const value{fuzz<T>()};

    auto const encoder{Codec::stream()->createEncoder()};
    Viper::Codec::Writer writer{encoder};
    write(writer, value);                                      // ADL : l'unité de T

    auto const decoder{Codec::stream()->createDecoder(encoder->endEncoding())};
    Viper::Codec::Reader reader{decoder, Codec::definitions()};

    VIPER_ASSERT("Topology.Test", read(reader, Viper::Codec::tag<T>{}) == value);
}

/// Fabriquer une Value, la décoder, la ré-encoder, comparer.
template<class T>
void roundTripValue() {
    auto const value{fuzzValue<T>()};
    auto const back{Codec::encode(Codec::decode<T>(value))};

    VIPER_ASSERT("Topology.Test", value->equal(back));
}

/// Fabriquer, passer par JSON, comparer.
template<class T>
void roundTripJson() {
    auto const value{fuzzValue<T>()};
    auto const json{Viper::JsonValueEncoder::json_encode(value)};
    auto const back{Viper::JsonValueDecoder::json_decode(json, type(Viper::Codec::tag<T>{}),
                                                         Codec::definitions())};

    VIPER_ASSERT("Topology.Test", value->equal(back));
}

/// Les trois d'un coup, ce qu'une unité appelle une fois par type qu'elle déclare.
template<class T>
void roundTrip() {
    roundTripStream<T>();
    roundTripValue<T>();
    roundTripJson<T>();
}

} // namespace Topology::Test

#endif
