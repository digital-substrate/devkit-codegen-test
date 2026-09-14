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

#include "Viper_AnyConceptKey.hpp"
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
// DÉCLARÉS DANS Viper::Codec, DÉFINIS ICI. Ils ont besoin de definitions(), donc seul ce
// module peut les écrire -- mais les déclarer ici les rendrait introuvables depuis un pool
// ou une unité : un type fondamental n'a aucun namespace associé. `tag<T>` en a un, celui
// du runtime, et c'est là qu'ils se déclarent pour que `type(tag<T>{})` marche partout.
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



// ── ce que la clé non typée ne peut pas porter elle-même ──
//
// LES DEUX SEULS MEMBRES DE L'AnyConceptKey GÉNÉRÉE QUI AVAIENT BESOIN DU MODÈLE. Les sept
// autres sont deux uuid, leurs comparaisons et leur hachage : rien qu'un namespace ou un
// générateur ait à fournir. Dire de quel concept relève une instance, en revanche, demande
// le modèle, et le modèle est ici.
//
// Fonctions libres, et non membres, parce que c'est la seule forme qui laisse le type
// au runtime. Un membre aurait obligé la classe entière à être générée -- ce qu'elle est
// aujourd'hui, pour ces deux lignes.

/// Le nom du concept, tel que le modèle le connaît, ou une forme brute s'il l'ignore.
std::string description(Viper::AnyConceptKey const & key);

/// Si ce modèle sait de quel concept il s'agit. Faux pour une instance venue d'un modèle
/// plus récent, ce qui est un cas normal et non une erreur.
bool isKnown(Viper::AnyConceptKey const & key);

/// Si l'instance relève de ce concept, ou d'un de ses dérivés.
///
/// C'est l'unique opération dont un rétrécissement a besoin, et elle est ici plutôt que
/// dans chaque unité pour une raison de sens : la réponse dépend de la hiérarchie des
/// concepts du modèle, pas de l'unité qui pose la question. Un dérivé peut avoir été
/// déclaré dans un namespace qui n'existait pas quand l'unité a été écrite.
bool isMember(Viper::AnyConceptKey const & key, std::shared_ptr<Viper::Type> const & concept_);

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
