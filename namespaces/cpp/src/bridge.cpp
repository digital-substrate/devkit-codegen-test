#include "ModelA_Codec.hpp"
#include "ModelB_Codec.hpp"
#include "Projection_Codec.hpp"

void use_bridge(Viper::StaticWriter::Writer & w) {
    // la map qui enjambe : aucune fonction générée, le template + ADL suffisent
    std::map<model_a::MaterialKey, model_b::MaterialKey> m;
    Viper::StaticWriter::write(w, m);

    // un conteneur d'une seule unité, idem
    std::set<model_a::Colour> s;
    Viper::StaticWriter::write(w, s);

    // et la structure composée, écrite par son unité
    projection::Pair p;
    write(w, p);
}
