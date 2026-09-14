// Le Writer, le Reader et le tag.
//
// LE PACK LES GÉNÈRE, ET C'EST LE NOM QUI LES Y RETIENT. `Topology::Writer` a une
// méthode par type -- `write_ModelA_Colour` -- donc la classe dépend du modèle. Rendues
// libres et trouvées par ADL, ces fonctions sortent de la classe, et il ne reste dans le
// Writer rien qui connaisse un modèle : un encodeur de flux, et des primitives. Sa place
// est alors dans le runtime, où ce stub le met.
#ifndef Viper_Codec_hpp
#define Viper_Codec_hpp
#include "Viper_Stream.hpp"
#include "Viper_UUId.hpp"
#include <cstdint>
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
    explicit Writer(std::shared_ptr<StreamEncoder> encoder);
    std::shared_ptr<StreamEncoder> const & encoder() const;
};

class Reader final {
public:
    Reader(std::shared_ptr<StreamDecoder> decoder, std::shared_ptr<Definitions const> definitions);
};

// Les primitives : identiques dans tout modèle jamais généré.
void write(Writer &, std::uint8_t);
void write(Writer &, float);
void write(Writer &, std::string const &);
void write(Writer &, UUId const &);
std::uint8_t read(Reader &, tag<std::uint8_t>);
float        read(Reader &, tag<float>);
std::string  read(Reader &, tag<std::string>);
UUId         read(Reader &, tag<UUId>);

// Les conteneurs : std::set n'appartient à aucun namespace du modèle, donc à aucune unité.
template<class T> void write(Writer & w, std::vector<T> const & v) { for (auto const & e : v) write(w, e); }
template<class T> void write(Writer & w, std::set<T> const & v)    { for (auto const & e : v) write(w, e); }
template<class K, class V> void write(Writer & w, std::map<K,V> const & v) {
    for (auto const & [k, e] : v) { write(w, k); write(w, e); }
}
template<class T> std::vector<T> read(Reader & r, tag<std::vector<T>>) { return {read(r, tag<T>{})}; }
template<class T> std::set<T>    read(Reader & r, tag<std::set<T>>)    { return {read(r, tag<T>{})}; }
template<class K, class V> std::map<K,V> read(Reader & r, tag<std::map<K,V>>) {
    return {{read(r, tag<K>{}), read(r, tag<V>{})}};
}

}} // ns
#endif
