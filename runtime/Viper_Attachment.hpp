#ifndef Viper_Attachment_hpp
#define Viper_Attachment_hpp
#include "Viper_UUId.hpp"
#include <memory>
#include <string>
namespace Viper {
class Type;
class TypeKey;
class TypeOptional;
class TypeSet;
class Attachment final {
public:
    std::shared_ptr<Type> const keyType;
    std::shared_ptr<Type> const documentType;
    std::shared_ptr<TypeSet> const keysType;
    std::shared_ptr<TypeOptional> const optionalDocumentType;
    UUId const runtimeId;

    /// Son nom qualifié -- le namespace qui le déclare, et le sien.
    std::string identifier() const;
};
}
#endif
