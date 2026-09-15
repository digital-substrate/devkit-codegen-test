// Le côté dynamique d'un pool : des fonctions qui prennent et rendent des Value.
// Signatures reprises de Viper_Function.hpp, Viper_FunctionPool.hpp et
// Viper_FunctionPrototype.hpp.
#ifndef Viper_FunctionPool_hpp
#define Viper_FunctionPool_hpp
#include "Viper_Types.hpp"
#include "Viper_UUId.hpp"
#include "Viper_AttachmentMutating.hpp"
#include "Viper_Values.hpp"
#include <memory>
#include <string>
#include <vector>
namespace Viper {

class FunctionPrototype final {
public:
    struct Parameter {
        std::string const name;
        std::shared_ptr<Type> const type;
    };
    static std::shared_ptr<FunctionPrototype> make(std::string name,
                                                   std::vector<Parameter> parameters,
                                                   std::shared_ptr<Type> returnType);
};

/// Le point de passage entre le dynamique et le statique. `checkedCall` reçoit des Value
/// et doit en rendre une : tout le pont tient dans la traduction de ces deux bords.
class Function {
public:
    std::shared_ptr<FunctionPrototype> const prototype;
    std::string const documentation;

    explicit Function(std::shared_ptr<FunctionPrototype> prototype, std::string documentation = {});
    virtual ~Function() = default;

protected:
    virtual std::shared_ptr<Value> checkedCall(std::vector<std::shared_ptr<Value>> const & args) const = 0;
};

/// Une fonction d'un pool d'attachments : elle reçoit en plus l'interface sur laquelle
/// agir, parce qu'elle opère sur des documents et non sur des valeurs seules.
class AttachmentMutatingFunction {
public:
    std::shared_ptr<FunctionPrototype> const prototype;
    std::string const documentation;
    AttachmentMutatingFunction(std::shared_ptr<FunctionPrototype> prototype, std::string documentation = {});
    virtual ~AttachmentMutatingFunction() = default;
    virtual std::string representation() const = 0;
};

class AttachmentGettingFunction {
public:
    std::shared_ptr<FunctionPrototype> const prototype;
    std::string const documentation;
    AttachmentGettingFunction(std::shared_ptr<FunctionPrototype> prototype, std::string documentation = {});
    virtual ~AttachmentGettingFunction() = default;
    virtual std::string representation() const = 0;
};

class AttachmentFunctionPool final {
public:
    static std::shared_ptr<AttachmentFunctionPool> make(UUId const & uuid, std::string name, std::string documentation = {});
    void add(std::shared_ptr<AttachmentMutatingFunction> const & function);
    void add(std::shared_ptr<AttachmentGettingFunction> const & function);
};

class FunctionPool final {
public:
    static std::shared_ptr<FunctionPool> make(UUId const & uuid, std::string name, std::string documentation = {});
    void add(std::shared_ptr<Function> const & function);
};

/// La valeur du néant, que rend une fonction sans retour. Son type est celui du runtime.
class Void { public: static std::shared_ptr<Value> Instance(); };

} // ns
#endif
