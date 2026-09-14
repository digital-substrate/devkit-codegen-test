// ModelA — l'implémentation du pont, et c'est le cœur de l'unité.
//
// TROIS FONCTIONS PAR TYPE, ET RIEN D'AUTRE. Le pack émet pour ModelA sept artefacts de
// sérialisation -- Stream, ValueCodec, Json, ValueHasher, Database et le reste -- chacun
// avec une fonction par type. Ici il y a `write`, `read` et `type`, et tout ce que le pack
// émet par ailleurs est une composition générique de ces trois-là, écrite une fois dans le
// module injecté ou dans le runtime.
//
// ET AUCUNE NE NOMME MODELA. `write(w, value.r)` sur un uint8 part chez le runtime,
// `write(w, uneCouleur)` revient ici, et c'est l'argument qui décide dans les deux cas.
// C'est ce qui remplace le suffixe de type : `write_ModelA_Colour` disait dans son nom ce
// que la résolution de surcharge sait déjà.

#include "ModelA_Codec.hpp"

#include "ModelA_Model.hpp"

#include "Topology_Codec.hpp"      // definitions() -- le modèle, que l'unité ne porte pas

#include "Viper_Definitions.hpp"
#include "Viper_Stream.hpp"
#include "Viper_TypeErrors.hpp"
#include "Viper_Types.hpp"

namespace ModelA {


// ── Finish ──
//
// CE QUI TRAVERSE EST L'INDEX DE LA CASE, PAS SA VALEUR. Le modèle ordonne les cases, et
// c'est cet ordre qui est le contrat de sérialisation -- une valeur C++ explicite ferait
// dire au langage ce que le modèle dit déjà, et les deux pourraient diverger.

void write(Viper::Codec::Writer & w, Finish value) {
    switch (value) {
        case Finish::Matte: w.streamWriting->writeUInt8(0); break;
        case Finish::Gloss: w.streamWriting->writeUInt8(1); break;
        default:
            throw Viper::TypeErrors::invalidEnumerationIndex(
                "ModelA", "Finish", __FUNCTION__, static_cast<std::uint8_t>(value));
    }
}

Finish read(Viper::Codec::Reader & r, Viper::Codec::tag<Finish>) {
    switch (auto const index{r.streamReading->readUInt8()}) {
        case 0: return Finish::Matte;
        case 1: return Finish::Gloss;
        default:
            throw Viper::TypeErrors::invalidEnumerationIndex("ModelA", "Finish", __FUNCTION__, index);
    }
}


// ── Colour ──

void write(Viper::Codec::Writer & w, Colour const & value) {
    write(w, value.r);
    write(w, value.g);
    write(w, value.b);
}

// AUCUNE VARIABLE LOCALE PAR CHAMP. Le pack en nomme une d'après chaque champ, ce qui est
// sûr chez lui parce que son lecteur est `this` ; ici le lecteur est un paramètre, et un
// champ nommé `r` donnerait `auto const r{read(r, …)}` -- une variable lue dans sa propre
// initialisation. Une liste entre accolades évalue de gauche à droite, garanti, donc
// l'ordre du modèle tient sans qu'on nomme rien.
Colour read(Viper::Codec::Reader & r, Viper::Codec::tag<Colour>) {
    return {read(r, Viper::Codec::tag<std::uint8_t>{}),
            read(r, Viper::Codec::tag<std::uint8_t>{}),
            read(r, Viper::Codec::tag<std::uint8_t>{})};
}


// ── MaterialKey ──
//
// Une clé, sur le fil, c'est deux uuid : l'instance, et le concept qu'elle est réellement.
// Le second est stocké et non déduit du type, parce qu'une MaterialKey peut nommer une
// instance d'un concept dérivé -- Projection::DerivedMaterial -- et c'est l'identité de
// celui-là qui doit traverser.

void write(Viper::Codec::Writer & w, MaterialKey const & value) {
    write(w, value.instanceId());
    write(w, value.runtimeId());
}

MaterialKey read(Viper::Codec::Reader & r, Viper::Codec::tag<MaterialKey>) {
    auto const instanceId{read(r, Viper::Codec::tag<Viper::UUId>{})};
    auto const runtimeId{read(r, Viper::Codec::tag<Viper::UUId>{})};

    return {instanceId, runtimeId};
}


} // namespace ModelA
