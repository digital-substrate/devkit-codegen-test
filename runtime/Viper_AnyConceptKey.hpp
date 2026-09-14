// La clé non typée : une instance, et le concept qu'elle est réellement.
//
// ELLE EST DU RUNTIME, ET LE PACK LA GÉNÈRE. C'est la question d'où est parti tout ce
// chantier -- « personne ne peut revendiquer cette implémentation » -- et la réponse tient
// dans le décompte : la classe générée a neuf membres, et sept ne nomment aucun concept.
// Les deux qui restent, `description()` et `isKnown()`, ont besoin du modèle pour dire de
// quel concept il s'agit.
//
// Aucun namespace ne peut la revendiquer parce que ce n'est le type d'aucun namespace.
// C'est un type du runtime, à qui deux opérations avaient été attachées qui n'auraient
// jamais dû être des membres : elles sont maintenant des fonctions libres du module
// injecté, qui lui porte le modèle. Il ne reste rien à générer.
#ifndef Viper_AnyConceptKey_hpp
#define Viper_AnyConceptKey_hpp
#include "Viper_Hash.hpp"
#include "Viper_UUId.hpp"
#include <cstddef>
namespace Viper {

class AnyConceptKey final {
public:
    AnyConceptKey() = default;
    AnyConceptKey(UUId const & instanceId, UUId const & runtimeId) noexcept
    : _instanceId{instanceId}, _runtimeId{runtimeId} {}

    UUId const & instanceId() const noexcept { return _instanceId; }

    /// Le concept dont l'instance relève, et non celui par lequel on l'a obtenue.
    UUId const & runtimeId() const noexcept { return _runtimeId; }

    bool isValid() const noexcept { return _instanceId.isValid(); }

private:
    UUId _instanceId{};
    UUId _runtimeId{};
};

inline bool operator==(AnyConceptKey const & l, AnyConceptKey const & r) noexcept {
    return l.instanceId() == r.instanceId() && l.runtimeId() == r.runtimeId();
}
inline bool operator!=(AnyConceptKey const & l, AnyConceptKey const & r) noexcept { return !(l == r); }
inline bool operator<(AnyConceptKey const & l, AnyConceptKey const & r) noexcept {
    if (l.instanceId() != r.instanceId())
        return l.instanceId() < r.instanceId();
    return l.runtimeId() < r.runtimeId();
}

namespace Hash { void hash(Accumulator & h, AnyConceptKey const & value); }

} // ns

template<>
struct std::hash<Viper::AnyConceptKey> {
    std::size_t operator()(Viper::AnyConceptKey const & v) const noexcept { return Viper::Hash::of(v); }
};

#endif
