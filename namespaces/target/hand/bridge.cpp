#include "ModelA_Codec.hpp"
#include "ModelB_Codec.hpp"
#include "Projection_Codec.hpp"

void use_bridge(Viper::Codec::Writer & w) {
    // la map qui enjambe : aucune fonction générée, le template + ADL suffisent
    std::map<ModelA::MaterialKey, ModelB::MaterialKey> m;
    Viper::Codec::write(w, m);

    // un conteneur d'une seule unité, idem
    std::set<ModelA::Colour> s;
    Viper::Codec::write(w, s);

    // et la structure composée, écrite par son unité
    Projection::Pair p;
    write(w, p);
}
