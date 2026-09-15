// Topology — les fonctions que kibo injecte, et qu'aucun namespace ne peut revendiquer.
//
// LE SOCLE, ET IL TIENT EN QUATRE DÉCLARATIONS. Chacune a besoin du modèle entier, ce qui
// est le seul critère : ce dont aucun namespace ne peut répondre.
//
//   definitions()   le modèle tel que le runtime le connaît
//   stream()        le codec de flux par lequel passe l'aller-retour
//   encode/decode   le passage entre une valeur C++ et une Viper::Value
//   la clé non typée -- description, isKnown, isMember
//
// ENCODE ET DECODE SONT GÉNÉRIQUES. Le pack écrit le même corps de dix lignes une fois par
// type, dont seul le suffixe change -- et ce qui change est exactement ce qu'une unité
// implémente : `write`/`read` pour la valeur, `type` pour son descripteur, trouvés par ADL
// sur l'argument ou sur le tag. Un template remplace toute la famille encode_X / decode_X.
//
// CE QUI N'EST PAS ICI, ET Y ÉTAIT IL Y A UNE HEURE. Les descripteurs des primitives et des
// conteneurs. Ils semblaient avoir besoin du modèle ; ils n'en ont pas besoin : le type
// d'une primitive est un singleton du runtime, celui d'un conteneur se compose à partir de
// ceux de ses éléments. Ils sont donc entièrement du runtime, et le socle rétrécit d'autant.

#ifndef Topology_Codec_hpp
#define Topology_Codec_hpp

#include "Viper_AnyConceptKey.hpp"
#include "Viper_Codec.hpp"
#include "Viper_Stream.hpp"
#include "Viper_Values.hpp"

#include <memory>
#include <string>

namespace Topology::Codec {

using Viper::Codec::tag;

/// Le modèle, décodé une fois depuis la ressource qui le porte.
std::shared_ptr<Viper::Definitions const> const & definitions();

/// Le codec de flux par lequel passe l'aller-retour.
std::shared_ptr<Viper::StreamCodecInstancing> const & stream();

// ── ce que la clé non typée ne peut pas porter elle-même ──
//
// LES DEUX SEULS MEMBRES DE L'AnyConceptKey GÉNÉRÉE QUI AVAIENT BESOIN DU MODÈLE. Les sept
// autres sont deux uuid, leurs comparaisons et leur hachage. Fonctions libres, et non
// membres : un seul membre aurait obligé la classe entière à être générée -- ce qu'elle
// est aujourd'hui, pour ces deux lignes.

/// Le nom du concept, tel que le modèle le connaît, ou une forme brute s'il l'ignore.
std::string description(Viper::AnyConceptKey const & key);

/// Si ce modèle sait de quel concept il s'agit. Faux pour une instance venue d'un modèle
/// plus récent, ce qui est un cas normal et non une erreur.
bool isKnown(Viper::AnyConceptKey const & key);

/// Si l'instance relève de ce concept -- ou de ce club. Le descripteur porte la différence
/// entre dériver et adhérer ; c'est l'unique opération dont un rétrécissement a besoin, et
/// elle est ici parce que la réponse dépend de la hiérarchie du modèle, pas de l'unité qui
/// pose la question.
bool isMember(Viper::AnyConceptKey const & key, std::shared_ptr<Viper::Type> const & concept_);

// ── le passage entre les deux mondes ──

/// Une valeur C++ vers une Viper::Value.
template<class T>
std::shared_ptr<Viper::Value> encode(T const & value) {
    auto const encoder = stream()->createEncoder();
    Viper::Codec::Writer writer{encoder};
    write(writer, value);                                   // ADL : l'unité de value

    return Viper::ValueDecoder::decode(encoder->endEncoding(), stream(),
                                       type(tag<T>{}),      // ADL : l'unité, ou le runtime
                                       definitions());
}

/// Et le retour.
template<class T>
T decode(std::shared_ptr<Viper::Value const> const & value) {
    auto const decoder = stream()->createDecoder(Viper::ValueEncoder::encode(value, stream()));
    Viper::Codec::Reader reader{decoder, definitions()};

    return read(reader, tag<T>{});                          // ADL : l'unité de T
}

} // namespace Topology::Codec

#endif
