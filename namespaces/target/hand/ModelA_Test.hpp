// ModelA — what it must provide for its types to be exercised.
//
// Layer 5, and it mirrors layer 3 exactly, which is the check on layers 1 to 4: if the
// decomposition is right, the tests need no new idea.
//
// A round-trip test is generic -- make a value, encode it, decode it, compare -- and the
// only part that is not is making one. ModelA knows Colour has three channels, so ModelA
// fuzzes a Colour, and nothing else here belongs to it.

#ifndef ModelA_Test_hpp
#define ModelA_Test_hpp

#include "ModelA_Data.hpp"
#include "ModelA_Codec.hpp"

#include "Viper_Codec.hpp"
#include "Viper_Test.hpp"          // roundTrip<T>, the generic fuzz for containers

namespace ModelA {

// ── the only thing ModelA implements, again ──

Colour      fuzz(Viper::Test::Rng & rng, Viper::Codec::tag<Colour>);
MaterialKey fuzz(Viper::Test::Rng & rng, Viper::Codec::tag<MaterialKey>);

// ── and the entry the driver calls ──

/// Round-trip every type this namespace declares, through every codec.
///
/// Its body is a list of `roundTrip<T>(rng)`, one per declared type, and `roundTrip` is
/// the runtime's. A container of ModelA's types needs no line here: the generic fuzz
/// builds one by calling `fuzz(rng, tag<Colour>{})`, and ADL brings it back.
void test(Viper::Test::Rng & rng);

} // namespace ModelA

// What is NOT here:
//
//   roundTrip<T>                generic, over encode / decode / operator==
//   fuzz(tag<std::set<T>>)      generic, and std::set is not ModelA's
//   fuzz(tag<std::int64_t>)     the runtime's
//   the driver that calls every unit's test()   -- model-wide, it enumerates the model
//
// The pack emits seven test artefacts -- TestFuzz, TestValueFuzz, TestCodecJson,
// TestCodecStream, TestCodecValue, TestDatabase, TestDatabaseFuzz -- each with a function
// per type per codec. Written this way there is one line per type, once.

#endif
