#include "topology_model_a_codec.hpp"
#include "topology_model_b_codec.hpp"
#include "topology_projection_codec.hpp"

void use_bridge(Viper::StaticWriter::Writer & w) {
    // the spanning map: no generated function, the template + ADL are enough
    std::map<topology::model_a::MaterialKey, topology::model_b::MaterialKey> m;
    Viper::StaticWriter::write(w, m);

    // a container of a single unit, likewise
    std::set<topology::model_a::Colour> s;
    Viper::StaticWriter::write(w, s);

    // and the composed structure, written by its unit
    topology::projection::Pair p;
    write(w, p);
}
