// Ce que la couche 5 permet, vérifié par le compilateur.
#include "topology_model_a_test.hpp"
#include "topology_model_a_codec.hpp"
#include "topology_model_a_model.hpp"
#include "topology_test.hpp"

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
