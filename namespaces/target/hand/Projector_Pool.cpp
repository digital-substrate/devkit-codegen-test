// Projector — le pool qui enjambe deux unités.
//
// `void link(ModelA::MaterialKey const &, ModelB::MaterialKey const &)`. Rien de nouveau
// par rapport à Tools, et c'est le résultat : le pont ne sait pas que ses arguments
// viennent de deux unités différentes, parce qu'il ne convertit pas type à type. Il décode
// chaque argument depuis sa Value, et `decode<T>` trouve le `read` de T par ADL.
//
// Le pack écrit ici `ValueDecoder::decode_ModelA_MaterialKey(...)` et
// `ValueDecoder::decode_ModelB_MaterialKey(...)` -- deux noms plats qui existaient parce
// que rien d'autre ne distinguait les deux appels.

#include "Projector_Pool.hpp"

// DE CHAQUE UNITÉ ATTEINTE, TROIS ARTEFACTS ET PAS UN. Les types pour les signatures, le
// codec pour `write`/`read`, l'identité de modèle pour le descripteur que le prototype
// dynamique réclame. L'en-tête du pool n'avait besoin que du premier.
#include "ModelA_Codec.hpp"
#include "ModelA_Model.hpp"
#include "ModelB_Codec.hpp"
#include "ModelB_Model.hpp"
#include "Topology_Codec.hpp"

#include "Viper_Function.hpp"
#include "Viper_ValueVoid.hpp"
#include "Viper_FunctionPool.hpp"
#include "Viper_FunctionPrototype.hpp"

namespace Projector {

namespace {

Viper::UUId const poolId{Viper::UUId::parse("3f513cf9-c9b9-4c57-8ace-ac9a644be74c")};

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
        auto const p = Viper::FunctionPool::make(poolId, "Projector");
        p->add(Link::make());
        return p;
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
