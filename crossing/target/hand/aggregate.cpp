// Ce que les mutations d'agrégat permettent, vérifié par le compilateur.
#include "Core_Attachments.hpp"

#include <map>
#include <set>

void use_aggregate(Viper::AttachmentMutating & m) {
    auto const k = Core::ThingKey::create();
    Core::Colour const c{1, 2, 3};

    // le document EST l'ensemble : ajouter, retirer -- et non remplacer
    Core::Attachments::Thing::related::union_(m, k, {k});
    Core::Attachments::Thing::related::subtract(m, k, {k});

    // le document est une map : retirer prend des clés, pas des paires
    Core::Attachments::Thing::palette::union_(m, k, {{k, c}});
    Core::Attachments::Thing::palette::subtract(m, k, {k});
    Core::Attachments::Thing::palette::update(m, k, {{k, c}});

    // le document est un xarray : des positions, jamais un index
    auto const before = Viper::UUId::create();
    auto const at = Viper::UUId::create();
    Core::Attachments::Thing::history::insert(m, k, before, at, c);
    Core::Attachments::Thing::history::update(m, k, at, c);
    Core::Attachments::Thing::history::remove(m, k, at);

    // et les mêmes à l'adresse d'un champ, ce qui est le second usage de la couche 2
    Core::Attachments::Thing::bag::unionMembers(m, k, {k});
    Core::Attachments::Thing::bag::subtractTints(m, k, {k});
    Core::Attachments::Thing::bag::insertTrail(m, k, before, at, c);
}
