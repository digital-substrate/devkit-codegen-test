// What layer 5 allows, checked by the compiler.
#include "topology_model_a_test.hpp"
#include "topology_model_a_codec.hpp"
#include "topology_model_a_model.hpp"
#include "topology_test.hpp"

#include <set>

void use_l5() {
    // the unit tests itself: one list, and nothing else
    topology::model_a::test();

    // and any shape built on its types, without it declaring anything --
    // the container's descriptor is composed from the element's
    topology::test::roundTrip<std::set<topology::model_a::Colour>>();
    topology::test::roundTrip<std::map<topology::model_a::MaterialKey, topology::model_a::Colour>>();

    // reproducible on request
    topology::test::seed(42);
}
