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

#include "Topology_Resources.hpp"      // le modèle, en octets

#include "Viper_Definitions.hpp"
#include "Viper_DefinitionsDecoder.hpp"
#include "Viper_Types.hpp"

#include <cstring>

namespace Topology::Codec {

/// LE MODÈLE EST UNE DONNÉE, PAS DU CODE. Rien n'enregistre les types un par un : le `.dsm`
/// est embarqué tel quel et décodé au premier appel. C'est ce qui rend le socle petit --
/// il n'y a pas d'artefact d'enregistrement à générer par unité -- et c'est aussi ce qui
/// répond à « qui tient la liste des concepts connus » : cette liste-là.
std::shared_ptr<Viper::Definitions const> const & definitions() {
    static std::shared_ptr<Viper::Definitions const> instance;
    if (!instance) {
        Viper::Blob blob(sizeof(Resources::definitions));
        std::memcpy(blob.storage.data(), Resources::definitions, blob.size());
        instance = Viper::DefinitionsDecoder::decode(blob, Viper::StreamTokenBinaryCodec::Instance());
    }
    return instance;
}

std::shared_ptr<Viper::StreamCodecInstancing> const & stream() {
    static auto const instance = Viper::StreamBinaryCodec::Instance();
    return instance;
}

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
