#include "Service_FunctionPoolBridges.hpp"
#include <random>

// MARK: - Tools
namespace Service::FunctionPoolBridges::Tools {

std::int64_t add(std::int64_t a, std::int64_t b) {
  return a + b;
}

Demo::Vector3 add_vector(Demo::Vector3 const & a, Demo::Vector3 const & b) {
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

} // namespace Service::FunctionPoolBridges::Tools

// namespace SV::FunctionPoolBridges
