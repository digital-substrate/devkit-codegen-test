// Le hachage, sous la même forme que l'écriture : un accumulateur en premier argument.
//
// ET CE PREMIER ARGUMENT N'EST PAS UN ORNEMENT. `hash(x)` sur un std::uint8_t ne peut pas
// marcher : un type fondamental n'a aucun namespace associé, donc la recherche par ADL ne
// mène nulle part, et la recherche ordinaire depuis ModelA s'arrête sur les surcharges de
// ModelA. Un argument porté par le runtime rétablit l'ADL pour tous les types, fondamentaux
// compris -- exactement ce que `write(w, x)` obtient du Writer.
#ifndef Viper_Hash_hpp
#define Viper_Hash_hpp
#include "Viper_UUId.hpp"
#include <cstddef>
#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>
namespace Viper::Hash {

class Accumulator final {
public:
    void combine(std::size_t value) noexcept;
    std::size_t value() const noexcept;
private:
    std::size_t _seed{};
};

// Les primitives.
void hash(Accumulator & h, bool value);
void hash(Accumulator & h, std::uint8_t value);
void hash(Accumulator & h, float value);
void hash(Accumulator & h, std::string const & value);
void hash(Accumulator & h, UUId const & value);

// Les conteneurs : ils ne sont à aucune unité, donc leur hachage non plus.
template<class T> void hash(Accumulator & h, std::vector<T> const & v) { for (auto const & e : v) hash(h, e); }
template<class T> void hash(Accumulator & h, std::set<T> const & v)    { for (auto const & e : v) hash(h, e); }
template<class K, class V> void hash(Accumulator & h, std::map<K,V> const & v) {
    for (auto const & [k, e] : v) { hash(h, k); hash(h, e); }
}

/// Ce que `std::hash<T>` appelle : une passe complète sur une valeur.
template<class T> std::size_t of(T const & value) {
    Accumulator h;
    hash(h, value);                                    // ADL : l'unité de `value`
    return h.value();
}

}
#endif
