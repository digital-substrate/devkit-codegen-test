// modèle Features — les fonctions injectées, qu'aucune unité ne peut revendiquer.
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

#ifndef Features_Codec_hpp
#define Features_Codec_hpp

#include "Features_AnyConcept.hpp"
#include "Viper_Codec.hpp"
#include "Viper_Hasher.hpp"
#include "Viper_Json.hpp"
#include "Viper_Definitions.hpp"
#include "Viper_Stream.hpp"
#include "Viper_Values.hpp"

#include <memory>
#include <string>

namespace Features::Codec {

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

// L'ENSEMBLE DES CONCEPTS CONNUS EST UN ARGUMENT, ET C'EST TOUT L'INTÉRÊT DE CES TROIS
// FONCTIONS. Les poser sur `definitions()` -- les définitions du modèle, embarquées quand
// kibo a tourné -- reviendrait exactement à l'énumération que le pack écrit : le même
// ensemble, clos au même instant, interrogé autrement. Remplacer une liste par une requête
// sur cette liste ne gagne rien.
//
// L'ensemble s'ouvre ailleurs. `Database::open` charge les définitions du fichier et vérifie
// seulement qu'elles *contiennent* celles du modèle : ce que la base rend peut être
// strictement plus large -- écrit par une version plus récente, ou par un autre modèle
// partageant le fichier. Un pair en RPC est dans le même cas, et `extendConcepts` existe
// pour cela.
//
// Une clé qui vient de là peut nommer un concept que le modèle embarqué ignore, et la seule
// réponse utile est celle des définitions qu'on a en main.

/// Le nom du concept selon ces définitions, ou une forme brute si elles l'ignorent.
std::string description(AnyConceptKey const & key,
                        std::shared_ptr<Viper::Definitions const> const & definitions);

/// Si ces définitions savent de quel concept il s'agit.
bool isKnown(AnyConceptKey const & key,
             std::shared_ptr<Viper::Definitions const> const & definitions);

/// Si l'instance relève de ce concept -- ou de ce club. Le descripteur porte la différence
/// entre dériver et adhérer.
bool isMember(AnyConceptKey const & key, std::shared_ptr<Viper::Type> const & concept_,
              std::shared_ptr<Viper::Definitions const> const & definitions);

// Les mêmes contre le modèle embarqué, pour l'appelant qui n'a rien d'autre en main. Ce sont
// les réponses du jour de la génération, et c'est ce qu'elles valent.

inline std::string description(AnyConceptKey const & key) { return description(key, definitions()); }
inline bool isKnown(AnyConceptKey const & key) { return isKnown(key, definitions()); }
inline bool isMember(AnyConceptKey const & key, std::shared_ptr<Viper::Type> const & concept_) {
    return isMember(key, concept_, definitions());
}

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

// ── ce que le pack écrit encore une fois par type, et qui n'en demande pas ──
//
// DEUX FAMILLES, ET LEUR PROPRE SOURCE DIT CE QU'ELLES SONT :
//
//   json encode_X(v)     = json_encode(ValueEncoder::encode_X(v))
//   hexdigest_X(v)       = hexdigestValue(ValueEncoder::encode_X(v))
//
// 549 lignes de template pour deux compositions au-dessus de l'`encode` générique. Rien
// n'y varie que le type, et le type est déjà un paramètre.

/// Le JSON d'une valeur, et le retour.
template<class T>
std::string jsonEncode(T const & value) {
    return Viper::JsonValueEncoder::json_encode(encode(value));
}

template<class T>
T jsonDecode(std::string const & json) {
    return decode<T>(Viper::JsonValueDecoder::json_decode(json, type(tag<T>{}), definitions()));
}

/// L'empreinte d'une Value -- ce que les deux familles avaient en commun sans le dire.
///
/// DEUX NOMS, ET LE PACK AVAIT RAISON DE LE FAIRE. Appeler les deux `hexdigest` ne marche
/// pas : depuis `hexdigest(T const &)`, l'appel `hexdigest(encode(value))` reprend le
/// template -- qui correspond exactement -- plutôt que la surcharge sur `Value`, qui
/// demanderait une conversion. La fonction s'appelle elle-même. Le nom distinct n'est pas
/// une commodité de lecture, c'est ce qui départage.
std::string hexdigestValue(std::shared_ptr<Viper::Value const> const & value);

/// Et celle d'une valeur C++, qui n'est que la précédente après encodage.
template<class T>
std::string hexdigest(T const & value) {
    return hexdigestValue(encode(value));
}

} // namespace Features::Codec

#endif
