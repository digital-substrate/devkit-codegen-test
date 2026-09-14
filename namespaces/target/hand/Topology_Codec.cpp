// Topology — ce que la clé non typée ne peut pas porter elle-même.
//
// LES DEUX SEULS MEMBRES DE L'AnyConceptKey GÉNÉRÉE QUI AVAIENT BESOIN DU MODÈLE, et la
// question qu'ils posent : quelqu'un doit bien fournir l'ensemble des concepts connus.
//
// Quelqu'un le fait déjà. Le modèle enregistre chacun de ses concepts dans ses
// `Definitions` au chargement -- c'est l'artefact d'enregistrement, qui existe de toute
// façon, sans quoi rien du runtime ne fonctionnerait. Demander à cet enregistrement
// revient à ne rien générer de plus.
//
// ET C'EST LA BONNE RÉPONSE, PAS SEULEMENT LA PLUS COURTE. Le pack fige la liste à la
// génération : `isKnown()` compare l'identifiant à un ensemble clos au moment où le code a
// été écrit. Or `Viper::Definitions::extendConcepts` existe -- un modèle apprend des
// concepts en cours d'exécution, d'un pair ou d'un document plus récent. Une liste figée
// répond alors « inconnu » pour un concept que le runtime connaît, et le pack le reconnaît
// lui-même dans un commentaire sur `description`.
//
// Interroger le modèle donne la réponse d'aujourd'hui ; l'énumérer donne celle du jour de
// la génération.

#include "Topology_Codec.hpp"

#include "Viper_Definitions.hpp"
#include "Viper_Types.hpp"

namespace Topology::Codec {

bool isKnown(Viper::AnyConceptKey const & key) {
    return definitions()->queryConcept(key.runtimeId()) != nullptr;
}

std::string description(Viper::AnyConceptKey const & key) {
    auto const concept_ = definitions()->queryConcept(key.runtimeId());
    if (!concept_)
        return key.instanceId().uuidString() + ":?(" + key.runtimeId().uuidString() + ")";

    return key.instanceId().uuidString() + ":" + concept_->representation();
}

/// Rétrécir, et la seule opération dont un rétrécissement a besoin.
///
/// `concept_` est ici le descripteur d'un concept ou celui d'un club, et c'est lui qui
/// porte la différence : dériver n'est pas adhérer. Le code est le même des deux côtés.
bool isMember(Viper::AnyConceptKey const & key, std::shared_ptr<Viper::Type> const & concept_) {
    auto const instance = definitions()->queryConcept(key.runtimeId());
    if (!instance)
        return false;                                  // un concept que ce modèle ignore

    if (auto const target = std::dynamic_pointer_cast<Viper::TypeConcept>(concept_))
        return instance->isMember(target);

    if (auto const club = std::dynamic_pointer_cast<Viper::TypeClub>(concept_))
        return club->hasMember(instance);

    return false;
}

} // namespace Topology::Codec
