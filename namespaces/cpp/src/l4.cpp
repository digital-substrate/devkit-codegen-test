#include "topology_model_b_data.hpp"
#include "topology_model_a_attachments.hpp"
#include "topology_tools_pool.hpp"
#include "topology_projector_pool.hpp"
#include "topology_model_a_fields.hpp"

void use_l4(std::shared_ptr<Viper::AttachmentGetting> const & g,
            std::shared_ptr<Viper::AttachmentMutating> const & m,
            std::shared_ptr<Viper::ServiceRemote> svc) {
    topology::model_a::MaterialKey k;

    // l'attachment, nommé comme le modèle l'écrit
    auto const c = topology::model_a::attachments::Material::colour::get(g, k);
    topology::model_a::attachments::Material::colour::set(m, k, topology::model_a::Colour{1, 2, 3});

    // écriture partielle : un setter par champ, et c'est là que la couche 2 sert
    topology::model_a::attachments::Material::colour::setR(m, k, 9);

    // et l'écriture différentielle, que le runtime offre au même titre que set
    topology::model_a::attachments::Material::colour::diff(m, k, topology::model_a::Colour{1, 2, 3});

    // le pool local, et le même pool vu du client
    auto const n = topology::tools::add(2, 3);
    topology::tools::Remote remote{svc};
    auto const n2 = remote.add(2, 3);

    // le pool qui enjambe
    topology::projector::Remote p{svc};
    p.link(k, topology::model_b::MaterialKey{});
    (void)c; (void)n; (void)n2;
}
