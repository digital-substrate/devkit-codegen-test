// Ce que la couche 5 permet, vérifié par le compilateur.
#include "ModelA_Test.hpp"
#include "ModelA_Codec.hpp"
#include "ModelA_Model.hpp"
#include "Topology_Test.hpp"

#include <set>

void use_l5() {
    // l'unité s'éprouve elle-même : une liste, et rien d'autre
    topology::model_a::test();

    // et n'importe quelle forme au-dessus de ses types, sans qu'elle ait rien déclaré --
    // le descripteur du conteneur se compose depuis celui de l'élément
    topology::test::roundTrip<std::set<topology::model_a::Colour>>();
    topology::test::roundTrip<std::map<topology::model_a::MaterialKey, topology::model_a::Colour>>();

    // reproductible quand on le demande
    topology::test::seed(42);
}
