// Projector — l'implémentation du pool, et le pont entre le statique et le dynamique.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "Projector_Pool.hpp"

#include "ModelA_Codec.hpp"
#include "ModelB_Codec.hpp"
#include "ModelA_Model.hpp"
#include "ModelB_Model.hpp"

#include "Topology_Codec.hpp"

#include "Viper_FunctionPool.hpp"
#include "Viper_FunctionPrototype.hpp"
#include "Viper_ServiceRemote.hpp"
#include "Viper_ValueVoid.hpp"
#include "Viper_Function.hpp"

namespace Projector {

namespace {

/// L'identité de ce pool dans le modèle, nommée une fois : les deux bords s'en servent.
Viper::UUId const poolId{Viper::UUId::parse("3f513cf9-c9b9-4c57-8ace-ac9a644be74c")};

/// `link`, vue du dynamique.
class Link final : public Viper::Function {
public:
    static std::shared_ptr<Link> make() {
        return std::make_shared<Link>(Viper::FunctionPrototype::make(
            "link",
            {{"a", type(Viper::Codec::tag<ModelA::MaterialKey>{})},
             {"b", type(Viper::Codec::tag<ModelB::MaterialKey>{})}},
            Viper::TypeVoid::Instance()));
    }

    explicit Link(std::shared_ptr<Viper::FunctionPrototype> prototype)
    : Viper::Function{std::move(prototype)} {}

protected:
    std::shared_ptr<Viper::Value> checkedCall(
            std::vector<std::shared_ptr<Viper::Value>> const & args) const override {
        auto const a{Topology::Codec::decode<ModelA::MaterialKey>(args.at(0))};
        auto const b{Topology::Codec::decode<ModelB::MaterialKey>(args.at(1))};

        link(a, b);
        return Viper::ValueVoid::Instance();
    }
};

} // namespace

std::shared_ptr<Viper::FunctionPool> pool() {
    static auto const instance = [] {
        auto const created = Viper::FunctionPool::make(poolId, "Projector");
        created->add(Link::make());
        return created;
    }();
    return instance;
}

Remote::Remote(std::shared_ptr<Viper::ServiceRemote> service)
: _service{std::move(service)} {}

bool Remote::isAvailable() const {
    return _service->queryFunctionPool(poolId) != nullptr;
}

void Remote::link(ModelA::MaterialKey const & a, ModelB::MaterialKey const & b) const {
    _service->call(poolId, "link", {Topology::Codec::encode(a), Topology::Codec::encode(b)});
}

} // namespace Projector