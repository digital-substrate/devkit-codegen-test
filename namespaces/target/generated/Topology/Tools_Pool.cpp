// Tools — l'implémentation du pool, et le pont entre le statique et le dynamique.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "Tools_Pool.hpp"


#include "Topology_Codec.hpp"

#include "Viper_FunctionPool.hpp"
#include "Viper_FunctionPrototype.hpp"
#include "Viper_ServiceRemote.hpp"
#include "Viper_ValueVoid.hpp"
#include "Viper_Function.hpp"

namespace Tools {

namespace {

/// L'identité de ce pool dans le modèle, nommée une fois : les deux bords s'en servent.
Viper::UUId const poolId{Viper::UUId::parse("17e63428-03e1-41d7-ad9d-60c5665bbd66")};

/// `reset`, vue du dynamique.
class Reset final : public Viper::Function {
public:
    static std::shared_ptr<Reset> make() {
        return std::make_shared<Reset>(Viper::FunctionPrototype::make(
            "reset",
            {},
            Viper::TypeVoid::Instance()));
    }

    explicit Reset(std::shared_ptr<Viper::FunctionPrototype> prototype)
    : Viper::Function{std::move(prototype)} {}

protected:
    std::shared_ptr<Viper::Value> checkedCall(
            std::vector<std::shared_ptr<Viper::Value>> const & args) const override {
        reset();
        return Viper::ValueVoid::Instance();
    }
};

/// `add`, vue du dynamique.
class Add final : public Viper::Function {
public:
    static std::shared_ptr<Add> make() {
        return std::make_shared<Add>(Viper::FunctionPrototype::make(
            "add",
            {{"a", type(Viper::Codec::tag<std::int64_t>{})},
             {"b", type(Viper::Codec::tag<std::int64_t>{})}},
            type(Viper::Codec::tag<std::int64_t>{})));
    }

    explicit Add(std::shared_ptr<Viper::FunctionPrototype> prototype)
    : Viper::Function{std::move(prototype)} {}

protected:
    std::shared_ptr<Viper::Value> checkedCall(
            std::vector<std::shared_ptr<Viper::Value>> const & args) const override {
        auto const a{Topology::Codec::decode<std::int64_t>(args.at(0))};
        auto const b{Topology::Codec::decode<std::int64_t>(args.at(1))};

        return Topology::Codec::encode(add(a, b));
    }
};

} // namespace

std::shared_ptr<Viper::FunctionPool> pool() {
    static auto const instance = [] {
        auto const created = Viper::FunctionPool::make(poolId, "Tools");
        created->add(Reset::make());
        created->add(Add::make());
        return created;
    }();
    return instance;
}

Remote::Remote(std::shared_ptr<Viper::ServiceRemote> service)
: _service{std::move(service)} {}

bool Remote::isAvailable() const {
    return _service->queryFunctionPool(poolId) != nullptr;
}

void Remote::reset() const {
    _service->call(poolId, "reset", {});
}

std::int64_t Remote::add(std::int64_t a, std::int64_t b) const {
    return Topology::Codec::decode<std::int64_t>(
        _service->call(poolId, "add", {Topology::Codec::encode(a), Topology::Codec::encode(b)}));
}

} // namespace Tools