#ifndef Viper_Codec_hpp
#define Viper_Codec_hpp
#include <cstdint>
#include <map>
#include <memory>
#include <set>
#include <vector>
namespace Viper {
class Type;
namespace Codec {
class Writer; class Reader;
template<class T> struct tag {};

// la couche générique : neuf templates, indépendants du modèle
template<class T> void write(Writer & w, std::vector<T> const & v) { for (auto const & e : v) write(w, e); }
template<class T> void write(Writer & w, std::set<T> const & v)    { for (auto const & e : v) write(w, e); }
template<class K, class V> void write(Writer & w, std::map<K,V> const & v) {
    for (auto const & [k, e] : v) { write(w, k); write(w, e); }
}
void write(Writer &, std::uint8_t);
void write(Writer &, float);
template<class T> T decode(Reader & r) { return read(r, tag<T>{}); }
}}
#endif
