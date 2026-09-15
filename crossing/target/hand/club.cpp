// Ce que le club et la clé non typée permettent, vérifié par le compilateur.
#include "Core_Data.hpp"

#include <map>
#include <unordered_map>

void use_club() {
    auto const sub = Core::SubThingKey::create();
    auto const other = Core::OtherKey::create();

    // élargir vers le parent : implicite, et sans perte
    Core::ThingKey const widened = sub;

    // entrer dans le club : implicite aussi, depuis n'importe quel membre
    Core::KlubKey const fromSub = sub;
    Core::KlubKey const fromOther = other;

    // en sortir : optionnel, et c'est le modèle qui répond
    auto const back = fromSub.asSubThingKey();
    auto const wrong = fromSub.asOtherKey();

    // la clé non typée, et le retour
    Crossing::AnyConceptKey const any = sub.toAny();
    auto const narrowed = Core::SubThingKey::from(any);

    // un dérivé rétrécit aussi vers son parent, parce que l'identifiant réel a survécu
    auto const asParent = Core::ThingKey::from(any);

    // utilisables en conteneur, ordonnés et hachés
    std::map<Core::KlubKey, Core::Colour> ordered;
    std::unordered_map<Core::ThingKey, int> hashed;
    std::unordered_map<Crossing::AnyConceptKey, int> anyHashed;

    (void)widened; (void)fromOther; (void)back; (void)wrong;
    (void)narrowed; (void)asParent; (void)ordered; (void)hashed; (void)anyHashed;
}
