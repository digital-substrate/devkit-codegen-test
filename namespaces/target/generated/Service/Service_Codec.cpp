// Service — ce que la clé non typée ne peut pas porter elle-même.
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

#include "Service_Codec.hpp"

#include "Service_Resources.hpp"      // le modèle, en octets

#include "Viper_Definitions.hpp"
#include "Viper_StreamBinaryCodec.hpp"
#include "Viper_StreamTokenBinaryCodec.hpp"
#include "Viper_TypeClub.hpp"
#include "Viper_TypeConcept.hpp"
#include "Viper_DefinitionsToDSMDefinitions.hpp"
#include "Viper_JsonDSMDefinitionsEncoder.hpp"
#include "Viper_DefinitionsDecoder.hpp"
#include "Viper_HashSHA1.hpp"
#include "Viper_ValueHasher.hpp"
#include "Viper_Types.hpp"

#include <cstring>

namespace Service::Codec {

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

/// LE TYPE DU STATIQUE EST CELUI DU RETOUR, ET NON `auto`. `Instance()` rend un
/// `shared_ptr` sur la classe concrète ; avec `auto`, le retour par référence construit une
/// conversion temporaire et rend une référence dessus, qui meurt à la sortie. Le
/// compilateur le dit -- `returning reference to local temporary` -- et seul le vrai type
/// le fait apparaître.
std::shared_ptr<Viper::StreamCodecInstancing> const & stream() {
    static std::shared_ptr<Viper::StreamCodecInstancing> const instance{
        Viper::StreamBinaryCodec::Instance()};
    return instance;
}

bool isKnown(AnyConceptKey const & key,
             std::shared_ptr<Viper::Definitions const> const & definitions) {
    return definitions->queryConcept(key.runtimeId()) != nullptr;
}

std::string description(AnyConceptKey const & key,
                        std::shared_ptr<Viper::Definitions const> const & definitions) {
    auto const concept_ = definitions->queryConcept(key.runtimeId());
    if (!concept_)
        return key.instanceId().uuidString() + ":?(" + key.runtimeId().uuidString() + ")";

    return key.instanceId().uuidString() + ":" + concept_->representation();
}

/// Rétrécir, et la seule opération dont un rétrécissement a besoin.
///
/// `concept_` est ici le descripteur d'un concept ou celui d'un club, et c'est lui qui
/// porte la différence : dériver n'est pas adhérer. Le code est le même des deux côtés.
bool isMember(AnyConceptKey const & key, std::shared_ptr<Viper::Type> const & concept_,
              std::shared_ptr<Viper::Definitions const> const & definitions) {
    auto const instance = definitions->queryConcept(key.runtimeId());
    if (!instance)
        return false;                                  // un concept que ce modèle ignore

    if (auto const target = std::dynamic_pointer_cast<Viper::TypeConcept>(concept_))
        return instance->isMember(target);

    if (auto const club = std::dynamic_pointer_cast<Viper::TypeClub>(concept_))
        return club->isMemberDescendant(instance);

    return false;
}

/// LA SEULE LIGNE DES 549 QUI FASSE QUELQUE CHOSE. Tout le reste de ValueHasher est cette
/// fonction appelée après un encodage, écrite une fois par type -- et elle n'était même pas
/// déclarée dans l'en-tête, parce que rien hors de ce fichier ne l'appelait. Une unité si.
std::string hexdigestValue(std::shared_ptr<Viper::Value const> const & value) {
    auto const hasher = Viper::HashSHA1::make();
    Viper::ValueHasher::hash(value, hasher);

    return hasher->hexDigest();
}

/// LE JSON DU MODÈLE PASSE PAR SA FORME DSM, et c'est ce que le vrai encodeur prend : les
/// `Definitions` sont ce que le runtime manipule, le `DSMDefinitions` ce qu'un document
/// décrit. Le pack fait la même conversion.
std::string jsonDefinitions() {
    return Viper::JsonDSMDefinitionsEncoder::json_encode(Viper::DefinitionsToDSMDefinitions::convert(definitions()));
}

} // namespace Service::Codec
