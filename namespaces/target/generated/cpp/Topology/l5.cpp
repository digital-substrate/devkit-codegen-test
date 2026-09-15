// Ce que la couche 5 permet, vérifié par le compilateur.
#include "ModelA_Test.hpp"
#include "ModelA_Codec.hpp"
#include "ModelA_Model.hpp"
#include "Topology_Test.hpp"

#include <set>

void use_l5() {
    // l'unité s'éprouve elle-même : une liste, et rien d'autre
    ModelA::test();

    // et n'importe quelle forme au-dessus de ses types, sans qu'elle ait rien déclaré --
    // le descripteur du conteneur se compose depuis celui de l'élément
    Topology::Test::roundTrip<std::set<ModelA::Colour>>();
    Topology::Test::roundTrip<std::map<ModelA::MaterialKey, ModelA::Colour>>();

    // reproductible quand on le demande
    Topology::Test::seed(42);
}
