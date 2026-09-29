#include "Tools_Pool.hpp"
#include "Viper_ValueAny.hpp"
#include <random>

// MARK: - Tools
namespace tools {

std::int64_t add(std::int64_t a, std::int64_t b) {
  return a + b;
}

demo::Vector3 add_vector(demo::Vector3 const & a, demo::Vector3 const & b) {
  return {a.x + b.x, a.y + b.y, a.z + b.z};
}

std::string random_string(std::uint32_t size) {
  static std::string const alphabet{"abcdefghijklmnopqrstuvwxyz"};
  std::random_device rd;
  std::default_random_engine e(rd());
  std::uniform_int_distribution<size_t> d(0, 25);
  std::string result;
  result.reserve(size);
  for (std::size_t i{}; i < size; i++)
    result.push_back(alphabet.at(d(e)));
  return result;
}

bool is_greater(Viper::Any const & a, Viper::Any const & b) {
  return Viper::isGreater(a.value()->compare(b.value()));
}

} // namespace tools

// namespace SV::FunctionPoolBridges
