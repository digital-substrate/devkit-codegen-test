// LinkModel — l'implémentation du pool, et le pont entre le statique et le dynamique.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "LinkModel_Pool.hpp"

#include "Projection_Codec.hpp"
#include "Projection_Model.hpp"

#include "Topology_Codec.hpp"

#include "Viper_AttachmentFunctionPool.hpp"
#include "Viper_ServiceRemote.hpp"

namespace LinkModel {

namespace {

Viper::UUId const poolId{Viper::UUId::parse("a51019a2-790e-49ac-a164-6b150e0976d6")};

/// `clear`, vue du dynamique.
class Clear final : public Viper::AttachmentMutatingFunction {
public:
    static std::shared_ptr<Clear> make() {
        return std::make_shared<Clear>(Viper::FunctionPrototype::make(
            "clear",
            {{"linkKey", type(Viper::Codec::tag<Projection::LinkKey>{})}},
            Viper::TypeVoid::Instance()));
    }

    explicit Clear(std::shared_ptr<Viper::FunctionPrototype> prototype)
    : Viper::AttachmentMutatingFunction{std::move(prototype)} {}

    std::string representation() const override { return "clear"; }

protected:
    std::shared_ptr<Viper::Value> checkedCall(
            std::shared_ptr<Viper::AttachmentMutating> const & attachmentMutating,
            std::vector<std::shared_ptr<Viper::Value>> const & args) const {
        auto const linkKey{Topology::Codec::decode<Projection::LinkKey>(args.at(0))};

        clear(attachmentMutating, linkKey);
        return Viper::Void::Instance();
    }
};

} // namespace

std::shared_ptr<Viper::AttachmentFunctionPool> pool() {
    static auto const instance = [] {
        auto const created = Viper::AttachmentFunctionPool::make(poolId, "LinkModel");
        created->add(Clear::make());
        return created;
    }();
    return instance;
}

} // namespace LinkModel