#include "ModelB_Data.hpp"
#include "ModelA_Attachments.hpp"
#include "Tools_Pool.hpp"
#include "Projector_Pool.hpp"
#include "ModelA_Fields.hpp"

void use_l4(std::shared_ptr<Viper::AttachmentGetting> const & g,
            std::shared_ptr<Viper::AttachmentMutating> const & m,
            std::shared_ptr<Viper::ServiceRemote> svc) {
    model_a::MaterialKey k;

    // l'attachment, nommé comme le modèle l'écrit
    auto const c = model_a::attachments::Material::colour::get(g, k);
    model_a::attachments::Material::colour::set(m, k, model_a::Colour{1, 2, 3});

    // écriture partielle : un setter par champ, et c'est là que la couche 2 sert
    model_a::attachments::Material::colour::setR(m, k, 9);

    // et l'écriture différentielle, que le runtime offre au même titre que set
    model_a::attachments::Material::colour::diff(m, k, model_a::Colour{1, 2, 3});

    // le pool local, et le même pool vu du client
    auto const n = tools::add(2, 3);
    tools::Remote remote{svc};
    auto const n2 = remote.add(2, 3);

    // le pool qui enjambe
    projector::Remote p{svc};
    p.link(k, model_b::MaterialKey{});
    (void)c; (void)n; (void)n2;
}
