// Les descripteurs de type du runtime. Un Type est un objet enregistré dans les
// Definitions du modèle, pas une propriété du type C++ -- c'est la raison pour laquelle
// l'obtenir demande le modèle entier.
#ifndef Viper_Types_hpp
#define Viper_Types_hpp
#include <memory>
namespace Viper {
class Type { public: virtual ~Type() = default; };
class TypeConcept final : public Type {};
class TypeStructure final : public Type {};
class TypeEnumeration final : public Type {};
class TypeKey final : public Type {
public:
    static std::shared_ptr<TypeKey> make(std::shared_ptr<Type> const & typeConcept);
};
}
#endif
