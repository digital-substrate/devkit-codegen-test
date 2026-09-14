// Le Writer, le Reader et le tag.
//
// LE PACK LES GÉNÈRE, ET C'EST LE NOM QUI LES Y RETIENT. `Topology::Writer` a une
// méthode par type -- `write_ModelA_Colour` -- donc la classe dépend du modèle. Rendues
// libres et trouvées par ADL, ces fonctions sortent de la classe, et il ne reste dans le
// Writer rien qui connaisse un modèle : un encodeur de flux, et des primitives. Sa place
// est alors dans le runtime, où ce stub le met.
#ifndef Viper_Codec_hpp
#define Viper_Codec_hpp
#include "Viper_Scalars.hpp"
#include "Viper_Stream.hpp"
#include "Viper_UUId.hpp"
#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <tuple>
#include <variant>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>
namespace Viper {
class Definitions;
namespace Codec {

template<class T> struct tag {};

class Writer final {
public:
    std::shared_ptr<StreamWriting> const streamWriting;
    explicit Writer(std::shared_ptr<StreamWriting> streamWriting);
};

class Reader final {
public:
    std::shared_ptr<StreamReading> const streamReading;
    Reader(std::shared_ptr<StreamReading> streamReading, std::shared_ptr<Definitions const> definitions);
};

// Les primitives : identiques dans tout modèle jamais généré, et toutes présentes --
// une seule qui manque rend l'appel ambigu entre ses voisines plutôt qu'introuvable.
void write(Writer &, bool);
void write(Writer &, std::uint8_t);
void write(Writer &, std::uint16_t);
void write(Writer &, std::uint32_t);
void write(Writer &, std::uint64_t);
void write(Writer &, std::int8_t);
void write(Writer &, std::int16_t);
void write(Writer &, std::int32_t);
void write(Writer &, std::int64_t);
void write(Writer &, float);
void write(Writer &, double);
void write(Writer &, std::string const &);
void write(Writer &, UUId const &);
void write(Writer &, BlobId const &);
void write(Writer &, CommitId const &);
void write(Writer &, Blob const &);
void write(Writer &, Any const &);

bool          read(Reader &, tag<bool>);
std::uint8_t  read(Reader &, tag<std::uint8_t>);
std::uint16_t read(Reader &, tag<std::uint16_t>);
std::uint32_t read(Reader &, tag<std::uint32_t>);
std::uint64_t read(Reader &, tag<std::uint64_t>);
std::int8_t   read(Reader &, tag<std::int8_t>);
std::int16_t  read(Reader &, tag<std::int16_t>);
std::int32_t  read(Reader &, tag<std::int32_t>);
std::int64_t  read(Reader &, tag<std::int64_t>);
float         read(Reader &, tag<float>);
double        read(Reader &, tag<double>);
std::string   read(Reader &, tag<std::string>);
UUId          read(Reader &, tag<UUId>);
BlobId        read(Reader &, tag<BlobId>);
CommitId      read(Reader &, tag<CommitId>);
Blob          read(Reader &, tag<Blob>);
Any           read(Reader &, tag<Any>);

// Les conteneurs : std::set n'appartient à aucun namespace du modèle, donc à aucune unité.
template<class T> void write(Writer & w, std::vector<T> const & v) { for (auto const & e : v) write(w, e); }
template<class T> void write(Writer & w, std::set<T> const & v)    { for (auto const & e : v) write(w, e); }
template<class K, class V> void write(Writer & w, std::map<K,V> const & v) {
    for (auto const & [k, e] : v) { write(w, k); write(w, e); }
}
template<class T> void write(Writer & w, std::optional<T> const & v) { if (v) write(w, *v); }
template<class T> void write(Writer & w, XArray<T> const &) {}
template<class T, std::size_t N> void write(Writer & w, std::array<T,N> const & v) { for (auto const & e : v) write(w, e); }
template<class... T> void write(Writer & w, std::tuple<T...> const & v) {
    std::apply([&](auto const &... e) { (write(w, e), ...); }, v);
}
template<class... T> void write(Writer & w, std::variant<T...> const & v) {
    std::visit([&](auto const & e) { write(w, e); }, v);
}

template<class T> std::vector<T> read(Reader & r, tag<std::vector<T>>) { return {read(r, tag<T>{})}; }
template<class T> std::set<T>    read(Reader & r, tag<std::set<T>>)    { return {read(r, tag<T>{})}; }
template<class T> std::optional<T> read(Reader & r, tag<std::optional<T>>) { return read(r, tag<T>{}); }
template<class T> XArray<T> read(Reader &, tag<XArray<T>>) { return {}; }
template<class T, std::size_t N> std::array<T,N> read(Reader & r, tag<std::array<T,N>>) {
    std::array<T,N> result{};
    for (auto & e : result) e = read(r, tag<T>{});
    return result;
}
template<class... T> std::tuple<T...> read(Reader & r, tag<std::tuple<T...>>) {
    return std::tuple<T...>{read(r, tag<T>{})...};
}
template<class First, class... Rest> std::variant<First, Rest...> read(Reader & r, tag<std::variant<First, Rest...>>) {
    return read(r, tag<First>{});
}
template<class K, class V> std::map<K,V> read(Reader & r, tag<std::map<K,V>>) {
    return {{read(r, tag<K>{}), read(r, tag<V>{})}};
}

}} // ns
#endif
