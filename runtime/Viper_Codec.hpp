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
#include "Viper_Types.hpp"
#include "Viper_Stream.hpp"
#include "Viper_UUId.hpp"
#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <tuple>
#include <utility>
#include <variant>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>
namespace Viper {
class Definitions;
class Type;
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

// ── les descripteurs de ce qui n'est à aucune unité ──
//
// DÉCLARÉS ICI, DÉFINIS PAR LE MODULE INJECTÉ. Un Type est un objet enregistré dans les
// Definitions du modèle, donc seul le module injecté peut le fournir -- mais il ne peut pas
// le *déclarer* chez lui : `type(tag<std::int64_t>{})` appelé depuis un pool ne trouverait
// rien, un type fondamental n'ayant aucun namespace associé.
//
// `tag<T>`, lui, en a un : celui-ci. Déclarer les descripteurs dans Viper::Codec les rend
// donc trouvables par ADL depuis n'importe quelle portée, et la règle devient unique --
// `type(tag<T>{})` marche pour tout T, que T soit d'une unité, une primitive ou un
// conteneur de std.
// ILS NE CONSULTENT PAS LE MODÈLE, DONC ILS NE SONT PAS GÉNÉRÉS. Le type d'une primitive
// est un singleton du runtime ; celui d'un conteneur se compose à partir de ceux de ses
// éléments, et `type(tag<T>{})` sur l'élément part chez l'unité de T par ADL. Un
// `map<ModelA::MaterialKey, ModelB::MaterialKey>` obtient donc son descripteur d'un
// template du runtime nourri par deux unités, sans qu'une ligne soit générée pour lui.
#define VIPER_PRIMITIVE_TYPE_OF(T, N) \
    inline std::shared_ptr<Type> const & type(tag<T>) { \
        static std::shared_ptr<Type> const instance{Type##N::Instance()}; \
        return instance; \
    }
VIPER_PRIMITIVE_TYPE_OF(bool, Bool)
VIPER_PRIMITIVE_TYPE_OF(std::uint8_t, UInt8)
VIPER_PRIMITIVE_TYPE_OF(std::uint16_t, UInt16)
VIPER_PRIMITIVE_TYPE_OF(std::uint32_t, UInt32)
VIPER_PRIMITIVE_TYPE_OF(std::uint64_t, UInt64)
VIPER_PRIMITIVE_TYPE_OF(std::int8_t, Int8)
VIPER_PRIMITIVE_TYPE_OF(std::int16_t, Int16)
VIPER_PRIMITIVE_TYPE_OF(std::int32_t, Int32)
VIPER_PRIMITIVE_TYPE_OF(std::int64_t, Int64)
VIPER_PRIMITIVE_TYPE_OF(float, Float)
VIPER_PRIMITIVE_TYPE_OF(double, Double)
VIPER_PRIMITIVE_TYPE_OF(std::string, String)
VIPER_PRIMITIVE_TYPE_OF(UUId, UUId)
VIPER_PRIMITIVE_TYPE_OF(BlobId, BlobId)
VIPER_PRIMITIVE_TYPE_OF(CommitId, CommitId)
VIPER_PRIMITIVE_TYPE_OF(Blob, Blob)
VIPER_PRIMITIVE_TYPE_OF(Any, Any)
#undef VIPER_PRIMITIVE_TYPE_OF

template<class T> std::shared_ptr<Type> const & type(tag<std::vector<T>>) {
    static std::shared_ptr<Type> const instance{TypeVector::make(type(tag<T>{}))};
    return instance;
}
template<class T> std::shared_ptr<Type> const & type(tag<std::set<T>>) {
    static std::shared_ptr<Type> const instance{TypeSet::make(type(tag<T>{}))};
    return instance;
}
template<class T> std::shared_ptr<Type> const & type(tag<std::optional<T>>) {
    static std::shared_ptr<Type> const instance{TypeOptional::make(type(tag<T>{}))};
    return instance;
}
template<class T> std::shared_ptr<Type> const & type(tag<XArray<T>>) {
    static std::shared_ptr<Type> const instance{TypeXArray::make(type(tag<T>{}))};
    return instance;
}
template<class K, class V> std::shared_ptr<Type> const & type(tag<std::map<K,V>>) {
    static std::shared_ptr<Type> const instance{TypeMap::make(type(tag<K>{}), type(tag<V>{}))};
    return instance;
}
template<class T, std::size_t N> std::shared_ptr<Type> const & type(tag<std::array<T,N>>) {
    static std::shared_ptr<Type> const instance{TypeVec::make(type(tag<T>{}), N)};
    return instance;
}
template<class... T> std::shared_ptr<Type> const & type(tag<std::tuple<T...>>) {
    static std::shared_ptr<Type> const instance{TypeTuple::make({type(tag<T>{})...})};
    return instance;
}
template<class... T> std::shared_ptr<Type> const & type(tag<std::variant<T...>>) {
    static std::shared_ptr<Type> const instance{TypeVariant::make({type(tag<T>{})...})};
    return instance;
}

// LES CONTENEURS, ET LE CONTRAT QUI REND LE PONT STATIQUE/DYNAMIQUE POSSIBLE.
//
// Ce que ces fonctions posent sur le flux doit être exactement ce que
// `Viper::ValueWriter` pose pour la Value correspondante, et réciproquement pour
// `Viper::ValueReader`. C'est ce qui permet à `encode<T>` de fabriquer une Value en
// écrivant la valeur C++ sur un flux et en la relisant côté dynamique -- et au pont d'un
// pool de traduire dans les deux sens sans jamais convertir type à type.
//
// Le format vient donc de Viper_ValueWriter.cpp, et non d'un choix fait ici :
//
//   optional          writeBool(présent) puis la valeur
//   vector/set/map    writeUInt64(taille) puis les éléments, clé avant valeur
//   variant           writeUInt8(index dans le variant) puis la valeur
//   vec/mat           les éléments, sans taille : elle est dans le type
//   xarray            trois sections, chacune préfixée de sa taille
//   structure         ses champs dans l'ordre du type
//   clé               writeUUId(instance) puis writeUUId(concept réel)
//   énumération       writeUInt8(rang de la case)
//
// UN CONTRAT D'AUTANT PLUS SÛR QU'IL EST ÉCRIT UNE FOIS. Le pack ré-émet ces corps par
// forme et par modèle ; ici ce sont des templates du runtime, au même endroit que le
// ValueWriter qu'ils doivent suivre.
template<class T> void write(Writer & w, std::vector<T> const & v) {
    w.streamWriting->writeUInt64(v.size());
    for (auto const & e : v) write(w, e);
}
template<class T> void write(Writer & w, std::set<T> const & v) {
    w.streamWriting->writeUInt64(v.size());
    for (auto const & e : v) write(w, e);
}
template<class K, class V> void write(Writer & w, std::map<K,V> const & v) {
    w.streamWriting->writeUInt64(v.size());
    for (auto const & [k, e] : v) { write(w, k); write(w, e); }
}
template<class T> void write(Writer & w, std::optional<T> const & v) {
    w.streamWriting->writeBool(v.has_value());
    if (v) write(w, *v);
}
template<class T> void write(Writer & w, XArray<T> const & v) { v.write(w.streamWriting); }
template<class T, std::size_t N> void write(Writer & w, std::array<T,N> const & v) {
    for (auto const & e : v) write(w, e);       // la taille est dans le type
}
template<class... T> void write(Writer & w, std::tuple<T...> const & v) {
    std::apply([&](auto const &... e) { (write(w, e), ...); }, v);
}
template<class... T> void write(Writer & w, std::variant<T...> const & v) {
    w.streamWriting->writeUInt8(static_cast<std::uint8_t>(v.index()));
    std::visit([&](auto const & e) { write(w, e); }, v);
}

template<class T> std::vector<T> read(Reader & r, tag<std::vector<T>>) {
    std::vector<T> result;
    auto const size{r.streamReading->readUInt64()};
    result.reserve(size);
    for (std::uint64_t i{}; i < size; ++i) result.push_back(read(r, tag<T>{}));
    return result;
}
template<class T> std::set<T> read(Reader & r, tag<std::set<T>>) {
    std::set<T> result;
    auto const size{r.streamReading->readUInt64()};
    for (std::uint64_t i{}; i < size; ++i) result.insert(read(r, tag<T>{}));
    return result;
}
template<class T> std::optional<T> read(Reader & r, tag<std::optional<T>>) {
    if (!r.streamReading->readBool()) return std::nullopt;
    return read(r, tag<T>{});
}
template<class T> XArray<T> read(Reader & r, tag<XArray<T>>) { return XArray<T>::read(r.streamReading); }
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
    std::map<K,V> result;
    auto const size{r.streamReading->readUInt64()};
    for (std::uint64_t i{}; i < size; ++i) {
        auto key{read(r, tag<K>{})};                       // la clé avant la valeur,
        result.emplace(std::move(key), read(r, tag<V>{})); // et pas dans un argument
    }
    return result;
}

}} // ns
#endif
