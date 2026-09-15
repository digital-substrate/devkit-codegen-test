#include "Crossing_Test.hpp"

#include <optional>

namespace Crossing::Test {

namespace {
std::optional<std::uint64_t> g_seed;
std::shared_ptr<Viper::Fuzzer> g_fuzzer;
}

void seed(std::uint64_t value) {
    g_seed = value;
    g_fuzzer.reset();
}

std::shared_ptr<Viper::Fuzzer> const & fuzzer() {
    if (!g_fuzzer)
        g_fuzzer = g_seed ? Viper::Fuzzer::make(Codec::definitions(), *g_seed)
                          : Viper::Fuzzer::make(Codec::definitions());
    return g_fuzzer;
}

} // namespace Crossing::Test
