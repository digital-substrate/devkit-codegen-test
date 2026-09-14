// Les descripteurs de type du runtime. Un Type est un objet enregistré dans les
// Definitions du modèle, pas une propriété du type C++ -- c'est la raison pour laquelle
// l'obtenir demande le modèle entier.
#ifndef Viper_Types_hpp
#define Viper_Types_hpp
#include <memory>
#include <string>
namespace Viper {
class Type { public: virtual ~Type() = default; };
class TypeConcept final : public Type {
public:
    std::string const name;
    /// Vrai si ce concept est celui-là, ou en dérive.
    bool isMember(std::shared_ptr<TypeConcept> const & typeConcept) const;
};
class TypeStructure final : public Type {};
class TypeEnumeration final : public Type {};
class TypeClub final : public Type {
public:
    std::string const name;
    /// Vrai si ce concept est membre du club, directement ou par un de ses parents.
    bool hasMember(std::shared_ptr<TypeConcept> const & typeConcept) const;
};
class TypeKey final : public Type {
public:
    static std::shared_ptr<TypeKey> make(std::shared_ptr<Type> const & typeConcept);
};
}
#endif
