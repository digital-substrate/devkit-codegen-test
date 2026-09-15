#ifndef Viper_Definitions_hpp
#define Viper_Definitions_hpp
#include "Viper_UUId.hpp"
#include <memory>
#include <set>
#include <vector>
namespace Viper {
class Attachment;
class TypeConcept;
class TypeStructure;
class TypeEnumeration;
class TypeClub;
class Definitions {
public:
    std::shared_ptr<Attachment> checkAttachment(UUId const & runtimeId) const;

    /// Tous les attachments du modèle. C'est par là qu'on construit sans rien générer.
    std::vector<std::shared_ptr<Attachment>> attachments() const;
    std::shared_ptr<TypeConcept> checkConcept(UUId const & runtimeId) const;

    /// Le concept d'un identifiant, ou rien s'il vient d'un modèle que celui-ci ne
    /// connaît pas -- ce qui arrive, et c'est pourquoi la réponse est nullable.
    std::shared_ptr<TypeConcept> queryConcept(UUId const & runtimeId) const;
    std::shared_ptr<TypeStructure> checkStructure(UUId const & runtimeId) const;
    std::shared_ptr<TypeEnumeration> checkEnumeration(UUId const & runtimeId) const;
    std::shared_ptr<TypeClub> checkClub(UUId const & runtimeId) const;
    std::shared_ptr<TypeClub> queryClub(UUId const & runtimeId) const;

    /// Le modèle peut apprendre des concepts qu'il ne connaissait pas au chargement --
    /// et c'est la raison pour laquelle l'ensemble des concepts connus ne peut pas être
    /// figé à la génération.
    std::set<UUId> extendConcepts(std::shared_ptr<Definitions const> const & other);
};
}
#endif
