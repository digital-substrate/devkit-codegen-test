// modèle Service — l'implémentation de la clé non typée.
//
// QUATRE FONCTIONS, ET CE SONT CELLES D'UNE CLÉ. Sur le fil elle est deux uuid, comme
// n'importe quelle clé ; son descripteur est celui que le runtime tient pour « n'importe
// quel concept » ; son hachage combine les deux identifiants. Rien de cela ne dépend du
// modèle, ce qui est toute la raison pour laquelle ce fichier pourra disparaître.

#include "Service_AnyConcept.hpp"

#include "Viper_StreamReading.hpp"
#include "Viper_StreamWriting.hpp"
#include "Viper_TypeAnyConcept.hpp"

namespace Service {

void hash(Viper::Hash::Accumulator & h, AnyConceptKey const & value) noexcept {
    hash(h, value.instanceId());
    hash(h, value.runtimeId());
}

void write(Viper::Codec::Writer & w, AnyConceptKey const & value) {
    write(w, value.instanceId());
    write(w, value.runtimeId());
}

AnyConceptKey read(Viper::Codec::Reader & r, Viper::Codec::tag<AnyConceptKey>) {
    auto const instanceId{read(r, Viper::Codec::tag<Viper::UUId>{})};
    auto const runtimeId{read(r, Viper::Codec::tag<Viper::UUId>{})};

    return {instanceId, runtimeId};
}

std::shared_ptr<Viper::Type> const & type(Viper::Codec::tag<AnyConceptKey>) {
    static std::shared_ptr<Viper::Type> const instance{Viper::TypeAnyConcept::InstanceTypeKey()};
    return instance;
}

} // namespace Service
