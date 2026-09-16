// L'accumulateur, et les primitives qu'il sait hacher.
//
// TOUT PASSE PAR `Hash::combine_acc`, QUE LE RUNTIME A DÉJÀ. Ce fichier n'invente pas une
// fonction de hachage : il donne une forme -- un accumulateur en premier argument -- à ce
// qui existe, pour que la recherche par argument fonctionne aussi sur les types
// fondamentaux, qui n'ont aucun namespace associé.

#include "Viper_HashAccumulator.hpp"

#include "Viper_Hash.hpp"

#include <functional>

namespace Viper::Hash {

void Accumulator::combine(std::size_t value) noexcept { combine_acc(_seed, value); }
std::size_t Accumulator::value() const noexcept { return _seed; }

namespace {
template<class T> void of(Accumulator & h, T const & value) { h.combine(std::hash<T>{}(value)); }
}

void hash(Accumulator & h, bool value) { of(h, value); }
void hash(Accumulator & h, std::uint8_t value) { of(h, value); }
void hash(Accumulator & h, std::uint16_t value) { of(h, value); }
void hash(Accumulator & h, std::uint32_t value) { of(h, value); }
void hash(Accumulator & h, std::uint64_t value) { of(h, value); }
void hash(Accumulator & h, std::int8_t value) { of(h, value); }
void hash(Accumulator & h, std::int16_t value) { of(h, value); }
void hash(Accumulator & h, std::int32_t value) { of(h, value); }
void hash(Accumulator & h, std::int64_t value) { of(h, value); }
void hash(Accumulator & h, float value) { of(h, value); }
void hash(Accumulator & h, double value) { of(h, value); }
void hash(Accumulator & h, std::string const & value) { of(h, value); }

// Ces quatre-là ont déjà leur propre hachage dans le runtime : on l'accumule.
void hash(Accumulator & h, UUId const & value) { h.combine(value.hash()); }
void hash(Accumulator & h, BlobId const & value) { h.combine(value.hash()); }
void hash(Accumulator & h, CommitId const & value) { h.combine(value.hash()); }
void hash(Accumulator & h, Blob const & value) { h.combine(value.hash()); }
void hash(Accumulator & h, Any const & value) { h.combine(value.hash()); }

} // namespace Viper::Hash
