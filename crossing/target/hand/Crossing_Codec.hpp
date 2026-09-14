// Crossing — les fonctions que kibo injecte, et qu'aucun namespace ne peut revendiquer.
//
// Copié du module injecté de `namespaces/target/hand/Topology_Codec.hpp` -- le nom du
// modèle change, le contenu non -- et augmenté de ce que ce modèle-ci a fait apparaître.

#ifndef Crossing_Codec_hpp
#define Crossing_Codec_hpp

#include "Viper_AnyConceptKey.hpp"
#include "Viper_Codec.hpp"
#include "Viper_Stream.hpp"
#include "Viper_Values.hpp"

#include <memory>
#include <optional>
#include <string>

namespace Crossing::Codec {

using Viper::Codec::tag;

/// Le modèle, enregistré une fois.
std::shared_ptr<Viper::Definitions const> const & definitions();

/// Le codec de flux par lequel passe l'aller-retour.
std::shared_ptr<Viper::StreamCodecInstancing> const & stream();

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

template<class T>
std::shared_ptr<Viper::Value> encode(T const & value);

template<class T>
T decode(std::shared_ptr<Viper::Value const> const & value);

} // namespace Crossing::Codec

#endif
