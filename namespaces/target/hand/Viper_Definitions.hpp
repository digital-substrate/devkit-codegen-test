#ifndef Viper_Definitions_hpp
#define Viper_Definitions_hpp
#include "Viper_UUId.hpp"
#include <memory>
namespace Viper {
class Attachment;
class TypeConcept;
class TypeStructure;
class TypeEnumeration;
class TypeClub;
class Definitions {
public:
    std::shared_ptr<Attachment> checkAttachment(UUId const & runtimeId) const;
    std::shared_ptr<TypeConcept> checkConcept(UUId const & runtimeId) const;
    std::shared_ptr<TypeStructure> checkStructure(UUId const & runtimeId) const;
    std::shared_ptr<TypeEnumeration> checkEnumeration(UUId const & runtimeId) const;
    std::shared_ptr<TypeClub> checkClub(UUId const & runtimeId) const;
};
}
#endif
