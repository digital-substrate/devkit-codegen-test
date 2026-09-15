// Parts — l'implémentation du pont.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

#include "Parts_Codec.hpp"

#include "Parts_Model.hpp"

#include "Crossing_Codec.hpp"

#include "Viper_Definitions.hpp"
#include "Viper_Stream.hpp"
#include "Viper_TypeErrors.hpp"
#include "Viper_Types.hpp"

namespace Parts {


void write(Viper::Codec::Writer & w, ThingKey const & value) {
    write(w, value.instanceId());
    write(w, value.runtimeId());
}

ThingKey read(Viper::Codec::Reader & r, Viper::Codec::tag<ThingKey>) {
    auto const instanceId{read(r, Viper::Codec::tag<Viper::UUId>{})};
    auto const runtimeId{read(r, Viper::Codec::tag<Viper::UUId>{})};

    return {instanceId, runtimeId};
}



void write(Viper::Codec::Writer & w, Grade value) {
    switch (value) {
        case Grade::Soft: w.streamWriting->writeUInt8(0); break;
        case Grade::Hard: w.streamWriting->writeUInt8(1); break;
        default:
            throw Viper::TypeErrors::invalidEnumerationIndex(
                "Parts", "Grade", __FUNCTION__, static_cast<std::uint8_t>(value));
    }
}

Grade read(Viper::Codec::Reader & r, Viper::Codec::tag<Grade>) {
    switch (auto const index{r.streamReading->readUInt8()}) {
        case 0: return Grade::Soft;
        case 1: return Grade::Hard;
        default:
            throw Viper::TypeErrors::invalidEnumerationIndex("Parts", "Grade", __FUNCTION__, index);
    }
}


void write(Viper::Codec::Writer & w, Colour const & value) {
    write(w, value.r);
    write(w, value.g);
    write(w, value.b);
}

Colour read(Viper::Codec::Reader & r, Viper::Codec::tag<Colour>) {
    return {read(r, Viper::Codec::tag<float>{}),
            read(r, Viper::Codec::tag<float>{}),
            read(r, Viper::Codec::tag<float>{})};
}


} // namespace Parts