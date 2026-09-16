// Ce que JSON et l'empreinte permettent, vérifié par le compilateur.
#include "ModelA_Codec.hpp"
#include "ModelA_Model.hpp"
#include "Topology_Codec.hpp"

#include <map>
#include <set>

void use_json() {
    ModelA::Colour const c{1, 2, 3};

    // un type d'unité
    auto const j = Topology::Codec::jsonEncode(c);
    auto const back = Topology::Codec::jsonDecode<ModelA::Colour>(j);
    auto const h = Topology::Codec::hexdigest(c);

    // et n'importe quelle forme au-dessus, sans qu'aucune unité ait rien déclaré
    std::map<ModelA::MaterialKey, ModelA::Colour> m;
    auto const jm = Topology::Codec::jsonEncode(m);
    auto const hm = Topology::Codec::hexdigest(m);

    (void)back; (void)h; (void)jm; (void)hm;
}
