// Tools — l'implémentation du pool, et le pont entre le statique et le dynamique.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/service/Service.dsm.json by kibo-2.0.0.jar

#include "Tools_Pool.hpp"

#include "Demo_Codec.hpp"
#include "Demo_Model.hpp"

#include "Service_Codec.hpp"

#include "Viper_FunctionPool.hpp"
#include "Viper_FunctionPrototype.hpp"
#include "Viper_ServiceRemote.hpp"
#include "Viper_ValueVoid.hpp"
#include "Viper_Function.hpp"

namespace Tools {

namespace {

/// L'identité de ce pool dans le modèle, nommée une fois : les deux bords s'en servent.
Viper::UUId const poolId{Viper::UUId::parse("7aa5aea2-c9de-4f91-8371-7995aca8c947")};

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
        auto const a{Service::Codec::decode<std::int64_t>(args.at(0))};
        auto const b{Service::Codec::decode<std::int64_t>(args.at(1))};

        return Service::Codec::encode(add(a, b));
    }
};

/// `add_vector`, vue du dynamique.
class AddVector final : public Viper::Function {
public:
    static std::shared_ptr<AddVector> make() {
        return std::make_shared<AddVector>(Viper::FunctionPrototype::make(
            "add_vector",
            {{"a", type(Viper::Codec::tag<Demo::Vector3>{})},
             {"b", type(Viper::Codec::tag<Demo::Vector3>{})}},
            type(Viper::Codec::tag<Demo::Vector3>{})));
    }

    explicit AddVector(std::shared_ptr<Viper::FunctionPrototype> prototype)
    : Viper::Function{std::move(prototype)} {}

protected:
    std::shared_ptr<Viper::Value> checkedCall(
            std::vector<std::shared_ptr<Viper::Value>> const & args) const override {
        auto const a{Service::Codec::decode<Demo::Vector3>(args.at(0))};
        auto const b{Service::Codec::decode<Demo::Vector3>(args.at(1))};

        return Service::Codec::encode(add_vector(a, b));
    }
};

/// `random_string`, vue du dynamique.
class RandomString final : public Viper::Function {
public:
    static std::shared_ptr<RandomString> make() {
        return std::make_shared<RandomString>(Viper::FunctionPrototype::make(
            "random_string",
            {{"size", type(Viper::Codec::tag<std::uint32_t>{})}},
            type(Viper::Codec::tag<std::string>{})));
    }

    explicit RandomString(std::shared_ptr<Viper::FunctionPrototype> prototype)
    : Viper::Function{std::move(prototype)} {}

protected:
    std::shared_ptr<Viper::Value> checkedCall(
            std::vector<std::shared_ptr<Viper::Value>> const & args) const override {
        auto const size{Service::Codec::decode<std::uint32_t>(args.at(0))};

        return Service::Codec::encode(random_string(size));
    }
};

} // namespace

std::shared_ptr<Viper::FunctionPool> pool() {
    static auto const instance = [] {
        auto const created = Viper::FunctionPool::make(poolId, "Tools");
        created->add(Add::make());
        created->add(AddVector::make());
        created->add(RandomString::make());
        return created;
    }();
    return instance;
}

Remote::Remote(std::shared_ptr<Viper::ServiceRemote> service)
: _service{std::move(service)} {}

bool Remote::isAvailable() const {
    return _service->queryFunctionPool(poolId) != nullptr;
}

std::int64_t Remote::add(std::int64_t a, std::int64_t b) const {
    return Service::Codec::decode<std::int64_t>(
        _service->call(poolId, "add", {Service::Codec::encode(a), Service::Codec::encode(b)}));
}

Demo::Vector3 Remote::add_vector(Demo::Vector3 const & a, Demo::Vector3 const & b) const {
    return Service::Codec::decode<Demo::Vector3>(
        _service->call(poolId, "add_vector", {Service::Codec::encode(a), Service::Codec::encode(b)}));
}

std::string Remote::random_string(std::uint32_t size) const {
    return Service::Codec::decode<std::string>(
        _service->call(poolId, "random_string", {Service::Codec::encode(size)}));
}

} // namespace Tools