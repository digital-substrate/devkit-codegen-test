// unité ModelA — l'implémentation du pont.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "ModelA_Codec.hpp"

#include "ModelA_Model.hpp"

#include "Topology_Codec.hpp"

#include "Viper_Definitions.hpp"
#include "Viper_StreamCodecInstancing.hpp"
#include "Viper_ValueDecoder.hpp"
#include "Viper_ValueEncoder.hpp"
#include "Viper_TypeErrors.hpp"
#include "Viper_Types.hpp"

namespace ModelA {


void write(Viper::Codec::Writer & w, MaterialKey const & value) {
    write(w, value.instanceId());
    write(w, value.runtimeId());
}

MaterialKey read(Viper::Codec::Reader & r, Viper::Codec::tag<MaterialKey>) {
    auto const instanceId{read(r, Viper::Codec::tag<Viper::UUId>{})};
    auto const runtimeId{read(r, Viper::Codec::tag<Viper::UUId>{})};

    return {instanceId, runtimeId};
}



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


void write(Viper::Codec::Writer & w, Colour const & value) {
    write(w, value.r);
    write(w, value.g);
    write(w, value.b);
}

Colour read(Viper::Codec::Reader & r, Viper::Codec::tag<Colour>) {
    return {read(r, Viper::Codec::tag<std::uint8_t>{}),
            read(r, Viper::Codec::tag<std::uint8_t>{}),
            read(r, Viper::Codec::tag<std::uint8_t>{})};
}


} // namespace ModelA