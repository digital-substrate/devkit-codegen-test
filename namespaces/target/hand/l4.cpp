#include "ModelB_Data.hpp"
#include "ModelA_Attachments.hpp"
#include "Tools_Pool.hpp"
#include "Projector_Pool.hpp"
#include "ModelA_Fields.hpp"

void use_l4(Viper::AttachmentGetting & g, Viper::AttachmentMutating & m,
            std::shared_ptr<Viper::ServiceRemote> svc) {
    ModelA::MaterialKey k;

    // l'attachment, nommé comme le modèle l'écrit
    auto const c = ModelA::Attachments::Material::colour::get(g, k);
    ModelA::Attachments::Material::colour::set(m, k, ModelA::Colour{1, 2, 3});

    // écriture partielle : la couche 2 fournit l'adresse
    ModelA::Attachments::Material::colour::set(m, k, *ModelA::Fields::Colour::rPath(), 9);

    // le pool local, et le même pool vu du client
    auto const n = Tools::add(2, 3);
    Tools::Remote remote{svc};
    auto const n2 = remote.add(2, 3);

    // le pool qui enjambe
    Projector::Remote p{svc};
    p.link(k, ModelB::MaterialKey{});
    (void)c; (void)n; (void)n2;
}
