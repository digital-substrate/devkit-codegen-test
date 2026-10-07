#include "topology_model_a_data.hpp"
#include "topology_model_b_data.hpp"
#include "topology_projection_data.hpp"
#include <map>
#include <unordered_map>

void use() {
    // two homonymous Materials, no renaming
    topology::model_a::MaterialKey a;
    topology::model_b::MaterialKey b;
    topology::model_a::Colour ca{1, 2, 3};        // aggregate, brace initialisation
    topology::model_b::Colour cb{1.f, 2.f, 3.f};

    // the composition, qualified where it must be
    topology::projection::Pair p{a, b};

    // "is a": the derived key goes where the parent is expected, implicitly
    topology::projection::DerivedMaterialKey d;
    topology::model_a::MaterialKey widened = d;
    [](topology::model_a::MaterialKey) {}(d);

    // usable in containers, ordered and hashed
    std::map<topology::model_a::MaterialKey, topology::model_b::MaterialKey> ordered;
    std::unordered_map<topology::projection::Pair, int> hashed;
    (void)ca; (void)cb; (void)p; (void)widened; (void)ordered; (void)hashed;
}

#include "topology_model_a_fields.hpp"
#include "topology_projection_fields.hpp"
#include "topology_model_a_paths.hpp"
#include "topology_projection_paths.hpp"

void use_fields() {
    // the name, usable in a constant expression
    static_assert(topology::model_a::fields::Colour::r == "r");
    constexpr auto n = topology::model_a::fields::Colour::g;

    // the path, for a partial operation
    auto const & p = topology::model_a::paths::Colour::r();
    auto const & q = topology::projection::paths::Pair::a();
    // a field named after another field's path: the name and the path live apart
    static_assert(topology::model_a::fields::Asset::packagePath == "packagePath");
    auto const & r = topology::model_a::paths::Asset::package();
    (void)n; (void)p; (void)q; (void)r;
}
