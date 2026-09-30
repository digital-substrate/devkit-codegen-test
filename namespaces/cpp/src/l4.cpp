#include "topology_model_b_data.hpp"
#include "topology_model_a_attachments.hpp"
#include "topology_tools_pool.hpp"
#include "topology_tools_remote.hpp"
#include "topology_projector_pool.hpp"
#include "topology_projector_remote.hpp"
#include "topology_model_a_fields.hpp"

void use_l4(std::shared_ptr<Viper::AttachmentGetting> const & g,
            std::shared_ptr<Viper::AttachmentMutating> const & m,
            std::shared_ptr<Viper::ServiceRemote> svc) {
    topology::model_a::MaterialKey k;

    // the attachment, named as the model writes it
    auto const c = topology::model_a::attachments::Material::colour::get(g, k);
    topology::model_a::attachments::Material::colour::set(m, k, topology::model_a::Colour{1, 2, 3});

    // partial write: one setter per field, which is where layer 2 is used
    topology::model_a::attachments::Material::colour::setR(m, k, 9);

    // and the differential write, which the runtime offers just like set
    topology::model_a::attachments::Material::colour::diff(m, k, topology::model_a::Colour{1, 2, 3});

    // the local pool, and the same pool seen from the client
    auto const n = topology::tools::add(2, 3);
    topology::tools::Remote remote{svc};
    auto const n2 = remote.add(2, 3);

    // the spanning pool
    topology::projector::Remote p{svc};
    p.link(k, topology::model_b::MaterialKey{});
    (void)c; (void)n; (void)n2;
}
