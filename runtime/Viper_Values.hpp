// Stubs des valeurs du runtime. Les signatures sont recopiées de
// com.digitalsubstrate.viper/src/Viper -- si elles divergent, l'exercice ne vaut rien.
#ifndef Viper_Values_hpp
#define Viper_Values_hpp
#include "Viper_UUId.hpp"
#include <cstdint>
#include <memory>
#include <optional>
namespace Viper {

class Type;
class TypeKey;
class TypeOptional;
class TypeSet;

class Value {
public:
    virtual ~Value() = default;
    virtual std::shared_ptr<Type> type() const = 0;
    virtual bool equal(std::shared_ptr<Value const> const & other) const = 0;
};

class ValueKey final : public Value {
public:
    bool equal(std::shared_ptr<Value const> const & other) const override;
    UUId const instanceId{};
    static std::shared_ptr<ValueKey> cast(std::shared_ptr<Value> const & value);
    static std::shared_ptr<ValueKey const> cast(std::shared_ptr<Value const> const & value);
    std::shared_ptr<Type> type() const override;
};

class ValueBool final : public Value {
public:
    static std::shared_ptr<ValueBool> from(bool value);
    std::shared_ptr<Type> type() const override;
    bool equal(std::shared_ptr<Value const> const & other) const override;
};

class ValueVoid final : public Value {
public:
    static std::shared_ptr<Value> Instance();
    std::shared_ptr<Type> type() const override;
    bool equal(std::shared_ptr<Value const> const & other) const override;
};

class ValueOptional final : public Value {
public:
    bool equal(std::shared_ptr<Value const> const & other) const override;
    std::shared_ptr<Type> type() const override;
    bool isNil() const;
    std::shared_ptr<Value> unwrap() const;
};

class ValueSet final : public Value {
public:
    bool equal(std::shared_ptr<Value const> const & other) const override;
    std::shared_ptr<Type> type() const override;
    void add(std::shared_ptr<Value const> const & value);
    std::size_t size() const;
};

/// Itère un ValueSet ; le runtime le fournit dans son propre en-tête.
class ValueSetIter final {
public:
    explicit ValueSetIter(std::shared_ptr<ValueSet> const & set);
    bool hasNext() const;
    void next();
    std::shared_ptr<Value> value() const;
};

} // ns
#endif
