// Tools — l'implémentation du pool, et le pont entre le statique et le dynamique.
//
// UN POOL EST DEUX CHOSES QUI SE RESSEMBLENT. Du côté statique, des fonctions C++ que le
// développeur écrit lui-même -- le générateur ne produit que leur déclaration. Du côté
// dynamique, des objets `Viper::Function` qui prennent et rendent des `Viper::Value`,
// parce que c'est ainsi qu'un appel arrive d'un script, d'une RPC ou d'un outil.
//
// LE PONT NE CONVERTIT RIEN TYPE À TYPE. Il décode chaque argument depuis sa Value,
// appelle la fonction statique, encode le retour. `decode` et `encode` sont les génériques
// du module injecté, et c'est tout ce qu'il y a.
//
// ET C'EST LÀ QUE LE CONTRAT SE PAIE. `decode<T>(value)` fait passer la Value par un flux
// et relit avec `read(r, tag<T>{})` : il faut donc que ce que `Viper::ValueWriter` pose
// pour cette Value soit exactement ce que `read` attend. Les deux formats sont le même,
// et ils le sont parce que les conteneurs sont des templates du runtime, écrits une fois,
// à côté du ValueWriter qu'ils doivent suivre -- au lieu d'être ré-émis par forme et par
// modèle.

#include "Tools_Pool.hpp"

#include "Topology_Codec.hpp"      // encode, decode -- les deux bords du pont

#include "Viper_Function.hpp"
#include "Viper_ValueVoid.hpp"
#include "Viper_FunctionPool.hpp"
#include "Viper_FunctionPrototype.hpp"
#include "Viper_Types.hpp"

namespace Tools {

namespace {

/// L'identité de ce pool dans le modèle, nommée une fois : les deux bords s'en servent.
Viper::UUId const poolId{Viper::UUId::parse("17e63428-03e1-41d7-ad9d-60c5665bbd66")};

/// `void reset()`, vue du dynamique.
class Reset final : public Viper::Function {
public:
    static std::shared_ptr<Reset> make() {
        return std::make_shared<Reset>(
            Viper::FunctionPrototype::make("reset", {}, Viper::TypeVoid::Instance()));
    }

    explicit Reset(std::shared_ptr<Viper::FunctionPrototype> prototype)
    : Viper::Function{std::move(prototype)} {}

protected:
    std::shared_ptr<Viper::Value> checkedCall(
        std::vector<std::shared_ptr<Viper::Value>> const &) const override {
        reset();
        return Viper::ValueVoid::Instance();
    }
};

/// `std::int64_t add(std::int64_t, std::int64_t)`, vue du dynamique.
///
/// Les arguments sont décodés dans l'ordre du prototype, et c'est le seul endroit où
/// l'ordre compte : la Value ne porte pas le nom du paramètre.
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

/// Le pool, tel que le runtime le reçoit : monté une fois, avec son identité du modèle.
std::shared_ptr<Viper::FunctionPool> pool() {
    static auto const instance = [] {
        auto const p = Viper::FunctionPool::make(poolId, "Tools");
        p->add(Reset::make());
        p->add(Add::make());
        return p;
    }();
    return instance;
}

// ── et le même pool, vu d'un client ──
//
// LE MIROIR EXACT DU PONT CI-DESSUS. Là où `checkedCall` décode ses arguments et encode
// son retour, `Remote` encode ses arguments et décode son retour. Ce sont les deux sens du
// même passage, donc les deux mêmes génériques, et le contrat de format est le même :
// l'appel traverse un processus.

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
