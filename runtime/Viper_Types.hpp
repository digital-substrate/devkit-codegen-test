// Les descripteurs de type du runtime. Un Type est un objet enregistré dans les
// Definitions du modèle, pas une propriété du type C++ -- c'est la raison pour laquelle
// l'obtenir demande le modèle entier.
#ifndef Viper_Types_hpp
#define Viper_Types_hpp
#include <cstddef>
#include <memory>
#include <vector>
#include <string>
namespace Viper {
class Type { public: virtual ~Type() = default; };
class TypeConcept final : public Type {
public:
    std::shared_ptr<TypeConcept> const parent;
    std::string representation() const;
    /// Vrai si ce concept est celui-là, ou en dérive.
    bool isMember(std::shared_ptr<TypeConcept> const & typeConcept) const;
};
class TypeStructureField final {
public:
    std::string const name;
    std::shared_ptr<Type> const type;
};

class TypeStructure final : public Type {
public:
    static std::shared_ptr<TypeStructure> cast(std::shared_ptr<Type> const & type);
    std::vector<std::shared_ptr<TypeStructureField>> const & fields() const;
};
class TypeEnumeration final : public Type {};
class TypeClub final : public Type {
public:
    std::string representation() const;
    /// Vrai si ce concept est membre du club, directement ou par un de ses parents.
    bool hasMember(std::shared_ptr<TypeConcept> const & typeConcept) const;
};
class TypeKey final : public Type {
public:
    static std::shared_ptr<TypeKey> make(std::shared_ptr<Type> const & typeConcept);
};

// Les types des primitives sont des singletons du runtime, et ceux des conteneurs se
// composent à partir de leurs éléments. Ni les uns ni les autres ne consultent le modèle.
#define VIPER_PRIMITIVE_TYPE(N) class Type##N final : public Type { public: static std::shared_ptr<Type##N> Instance(); };
VIPER_PRIMITIVE_TYPE(Bool)
VIPER_PRIMITIVE_TYPE(UInt8)
VIPER_PRIMITIVE_TYPE(UInt16)
VIPER_PRIMITIVE_TYPE(UInt32)
VIPER_PRIMITIVE_TYPE(UInt64)
VIPER_PRIMITIVE_TYPE(Int8)
VIPER_PRIMITIVE_TYPE(Int16)
VIPER_PRIMITIVE_TYPE(Int32)
VIPER_PRIMITIVE_TYPE(Int64)
VIPER_PRIMITIVE_TYPE(Float)
VIPER_PRIMITIVE_TYPE(Double)
VIPER_PRIMITIVE_TYPE(String)
VIPER_PRIMITIVE_TYPE(UUId)
VIPER_PRIMITIVE_TYPE(BlobId)
VIPER_PRIMITIVE_TYPE(CommitId)
VIPER_PRIMITIVE_TYPE(Blob)
VIPER_PRIMITIVE_TYPE(Any)
VIPER_PRIMITIVE_TYPE(Void)
#undef VIPER_PRIMITIVE_TYPE

class TypeAnyConcept final : public Type {
public:
    static std::shared_ptr<TypeAnyConcept> Instance();
    static std::shared_ptr<TypeKey> InstanceTypeKey();
};

class TypeVector final : public Type { public: static std::shared_ptr<TypeVector> make(std::shared_ptr<Type> elementType); };
class TypeSet final : public Type { public: static std::shared_ptr<TypeSet> make(std::shared_ptr<Type> elementType); };
class TypeOptional final : public Type { public: static std::shared_ptr<TypeOptional> make(std::shared_ptr<Type> elementType); };
class TypeXArray final : public Type { public: static std::shared_ptr<TypeXArray> make(std::shared_ptr<Type> elementType); };
class TypeMap final : public Type { public: static std::shared_ptr<TypeMap> make(std::shared_ptr<Type> keyType, std::shared_ptr<Type> elementType); };
class TypeVec final : public Type { public: static std::shared_ptr<TypeVec> make(std::shared_ptr<Type> elementType, std::size_t size); };
class TypeTuple final : public Type { public: static std::shared_ptr<TypeTuple> make(std::vector<std::shared_ptr<Type>> types); };
class TypeVariant final : public Type { public: static std::shared_ptr<TypeVariant> make(std::vector<std::shared_ptr<Type>> types); };
}
#endif
