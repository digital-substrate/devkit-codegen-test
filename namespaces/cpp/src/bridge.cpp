#include "ModelA_Codec.hpp"
#include "ModelB_Codec.hpp"
#include "Projection_Codec.hpp"

void use_bridge(Viper::StaticWriter::Writer & w) {
    // la map qui enjambe : aucune fonction générée, le template + ADL suffisent
    std::map<topology::model_a::MaterialKey, topology::model_b::MaterialKey> m;
    Viper::StaticWriter::write(w, m);

    // un conteneur d'une seule unité, idem
    std::set<topology::model_a::Colour> s;
    Viper::StaticWriter::write(w, s);

    // et la structure composée, écrite par son unité
    topology::projection::Pair p;
    write(w, p);
}
