// Topology — les fonctions que kibo injecte, et qu'aucun namespace ne peut revendiquer.
//
// C'est le troisième module, et il n'est ni ModelA ni ModelB. Il porte deux choses :
//
//   definitions()   le modèle tel que le runtime le connaît, une fois pour tout le modèle
//   encode/decode   le passage entre une valeur C++ et une Viper::Value
//
// ENCODE ET DECODE SONT GÉNÉRIQUES, et c'est ce que la couche 3 affirmait. Le pack écrit
// le même corps de dix lignes une fois par type, dont seul le suffixe change -- et ce qui
// change est exactement ce qu'une unité implémente : `write`/`read` pour la valeur, `type`
// pour son descripteur. Les deux sont trouvés par ADL sur l'argument ou sur le tag. Une
// fonction template ici remplace toute la famille encode_X / decode_X.
//
// POURQUOI CE MODULE EXISTE. encode a besoin de definitions(), qui est le modèle entier :
// aucune unité ne peut le fournir, et le runtime ne le connaît pas. C'est la définition du
// socle -- ce qu'aucun namespace ne peut revendiquer -- et il est petit.

#ifndef Topology_Codec_hpp
#define Topology_Codec_hpp

#include "Viper_Codec.hpp"
#include "Viper_Stream.hpp"
#include "Viper_Values.hpp"

#include <cstdint>
#include <memory>
#include <array>
#include <map>
#include <optional>
#include <tuple>
#include <variant>
#include <set>
#include <string>
#include <vector>

namespace Topology::Codec {

using Viper::Codec::tag;

/// Le modèle, enregistré une fois.
std::shared_ptr<Viper::Definitions const> const & definitions();

/// Le codec de flux par lequel passe l'aller-retour.
std::shared_ptr<Viper::StreamCodecInstancing> const & stream();

// ── les descripteurs que personne d'autre ne peut fournir ──
//
// TROUVÉ EN ÉCRIVANT LE .CPP : `setR` encode un std::uint8_t, donc encode<std::uint8_t>
// appelle type(tag<std::uint8_t>{}) -- et aucune unité ne le déclare, puisqu'un uint8 n'est
// à personne. La recherche par ADL sur tag<unsigned char> ne mène nulle part non plus.
//
// C'est le socle qui les porte, et pour une raison concrète : un Type est un objet
// enregistré dans les Definitions du modèle, donc il faut definitions() pour l'obtenir. La
// même chose vaudra pour les conteneurs -- type(tag<std::set<T>>) -- parce qu'un std::set
// n'appartient à aucun namespace du modèle. C'est exactement la frontière cherchée, et elle
// s'est dessinée toute seule à la première compilation.

std::shared_ptr<Viper::Type> const & type(tag<bool>);
std::shared_ptr<Viper::Type> const & type(tag<std::uint8_t>);
std::shared_ptr<Viper::Type> const & type(tag<std::uint16_t>);
std::shared_ptr<Viper::Type> const & type(tag<std::uint32_t>);
std::shared_ptr<Viper::Type> const & type(tag<std::uint64_t>);
std::shared_ptr<Viper::Type> const & type(tag<std::int8_t>);
std::shared_ptr<Viper::Type> const & type(tag<std::int16_t>);
std::shared_ptr<Viper::Type> const & type(tag<std::int32_t>);
std::shared_ptr<Viper::Type> const & type(tag<std::int64_t>);
std::shared_ptr<Viper::Type> const & type(tag<float>);
std::shared_ptr<Viper::Type> const & type(tag<double>);
std::shared_ptr<Viper::Type> const & type(tag<std::string>);
std::shared_ptr<Viper::Type> const & type(tag<Viper::UUId>);
std::shared_ptr<Viper::Type> const & type(tag<Viper::BlobId>);
std::shared_ptr<Viper::Type> const & type(tag<Viper::CommitId>);
std::shared_ptr<Viper::Type> const & type(tag<Viper::Blob>);
std::shared_ptr<Viper::Type> const & type(tag<Viper::Any>);

// ── et les conteneurs, pour la même raison, une fois de plus ──
//
// TROUVÉ EN COMPILANT Projection_Attachments.cpp. Projection déclare
// `attachment<Link, map<key<ModelA::Material>, key<ModelB::Material>>> mapping` : une forme
// qui enjambe deux namespaces et n'appartient à aucun des deux. `encode` de ce document
// demande son descripteur de type, et il n'y a personne à qui le demander -- ModelA ne peut
// pas revendiquer une map dont la valeur est à ModelB, et réciproquement.
//
// C'est la forme qui a forcé un socle à exister, et elle atterrit ici sans qu'on ait rien
// à décider : vector, set et map sont dans std, donc ce sont des conteneurs de std, donc
// aucune unité du modèle n'en est propriétaire. Une famille de templates, écrite une fois.
template<class T> std::shared_ptr<Viper::Type> const & type(tag<std::vector<T>>);
template<class T> std::shared_ptr<Viper::Type> const & type(tag<std::set<T>>);
template<class K, class V> std::shared_ptr<Viper::Type> const & type(tag<std::map<K,V>>);
template<class T> std::shared_ptr<Viper::Type> const & type(tag<std::optional<T>>);
template<class T> std::shared_ptr<Viper::Type> const & type(tag<Viper::XArray<T>>);
template<class... T> std::shared_ptr<Viper::Type> const & type(tag<std::tuple<T...>>);
template<class... T> std::shared_ptr<Viper::Type> const & type(tag<std::variant<T...>>);
template<class T, std::size_t N> std::shared_ptr<Viper::Type> const & type(tag<std::array<T,N>>);

/// Une valeur C++ vers une Viper::Value.
template<class T>
std::shared_ptr<Viper::Value> encode(T const & value) {
    auto const encoder = stream()->createEncoder();
    Viper::Codec::Writer writer{encoder};
    write(writer, value);                                   // ADL : ModelA::write

    return Viper::ValueDecoder::decode(encoder->endEncoding(), stream(),
                                       type(tag<T>{}),      // ADL : ModelA::type
                                       definitions());
}

/// Et le retour.
template<class T>
T decode(std::shared_ptr<Viper::Value const> const & value) {
    auto const decoder = stream()->createDecoder(Viper::ValueEncoder::encode(value, stream()));
    Viper::Codec::Reader reader{decoder, definitions()};

    return read(reader, tag<T>{});                          // ADL : ModelA::read
}

} // namespace Topology::Codec

#endif
