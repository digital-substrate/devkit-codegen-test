// unité Core — l'implémentation du pont.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

#include "Core_Codec.hpp"

#include "Core_Model.hpp"

#include "Crossing_Codec.hpp"

#include "Viper_Definitions.hpp"
#include "Viper_StreamCodecInstancing.hpp"
#include "Viper_ValueDecoder.hpp"
#include "Viper_ValueEncoder.hpp"
#include "Viper_TypeErrors.hpp"
#include "Viper_Types.hpp"

namespace Core {


void write(Viper::Codec::Writer & w, OtherKey const & value) {
    write(w, value.instanceId());
    write(w, value.runtimeId());
}

OtherKey read(Viper::Codec::Reader & r, Viper::Codec::tag<OtherKey>) {
    auto const instanceId{read(r, Viper::Codec::tag<Viper::UUId>{})};
    auto const runtimeId{read(r, Viper::Codec::tag<Viper::UUId>{})};

    return {instanceId, runtimeId};
}


void write(Viper::Codec::Writer & w, ThingKey const & value) {
    write(w, value.instanceId());
    write(w, value.runtimeId());
}

ThingKey read(Viper::Codec::Reader & r, Viper::Codec::tag<ThingKey>) {
    auto const instanceId{read(r, Viper::Codec::tag<Viper::UUId>{})};
    auto const runtimeId{read(r, Viper::Codec::tag<Viper::UUId>{})};

    return {instanceId, runtimeId};
}


void write(Viper::Codec::Writer & w, SubThingKey const & value) {
    write(w, value.instanceId());
    write(w, value.runtimeId());
}

SubThingKey read(Viper::Codec::Reader & r, Viper::Codec::tag<SubThingKey>) {
    auto const instanceId{read(r, Viper::Codec::tag<Viper::UUId>{})};
    auto const runtimeId{read(r, Viper::Codec::tag<Viper::UUId>{})};

    return {instanceId, runtimeId};
}


void write(Viper::Codec::Writer & w, KlubKey const & value) {
    write(w, value.instanceId());
    write(w, value.runtimeId());
}

KlubKey read(Viper::Codec::Reader & r, Viper::Codec::tag<KlubKey>) {
    auto const instanceId{read(r, Viper::Codec::tag<Viper::UUId>{})};
    auto const runtimeId{read(r, Viper::Codec::tag<Viper::UUId>{})};

    return {instanceId, runtimeId};
}


void write(Viper::Codec::Writer & w, Grade value) {
    switch (value) {
        case Grade::Low: w.streamWriting->writeUInt8(0); break;
        case Grade::High: w.streamWriting->writeUInt8(1); break;
        default:
            throw Viper::TypeErrors::invalidEnumerationIndex(
                "Core", "Grade", __FUNCTION__, static_cast<std::uint8_t>(value));
    }
}

Grade read(Viper::Codec::Reader & r, Viper::Codec::tag<Grade>) {
    switch (auto const index{r.streamReading->readUInt8()}) {
        case 0: return Grade::Low;
        case 1: return Grade::High;
        default:
            throw Viper::TypeErrors::invalidEnumerationIndex("Core", "Grade", __FUNCTION__, index);
    }
}


void write(Viper::Codec::Writer & w, Bag const & value) {
    write(w, value.members);
    write(w, value.tints);
    write(w, value.trail);
}

Bag read(Viper::Codec::Reader & r, Viper::Codec::tag<Bag>) {
    return {read(r, Viper::Codec::tag<std::set<ThingKey>>{}),
            read(r, Viper::Codec::tag<std::map<ThingKey, Colour>>{}),
            read(r, Viper::Codec::tag<Viper::XArray<Colour>>{})};
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


void write(Viper::Codec::Writer & w, Defaults const & value) {
    write(w, value.f_uint8);
    write(w, value.f_float);
    write(w, value.f_string);
    write(w, value.f_uuid);
    write(w, value.f_vec);
    write(w, value.f_grade);
    write(w, value.f_colour);
}

Defaults read(Viper::Codec::Reader & r, Viper::Codec::tag<Defaults>) {
    return {read(r, Viper::Codec::tag<std::uint8_t>{}),
            read(r, Viper::Codec::tag<float>{}),
            read(r, Viper::Codec::tag<std::string>{}),
            read(r, Viper::Codec::tag<Viper::UUId>{}),
            read(r, Viper::Codec::tag<std::array<std::uint8_t, 2>>{}),
            read(r, Viper::Codec::tag<Grade>{}),
            read(r, Viper::Codec::tag<Colour>{})};
}


void write(Viper::Codec::Writer & w, Scalars const & value) {
    write(w, value.f_bool);
    write(w, value.f_uint8);
    write(w, value.f_uint16);
    write(w, value.f_uint32);
    write(w, value.f_uint64);
    write(w, value.f_int8);
    write(w, value.f_int16);
    write(w, value.f_int32);
    write(w, value.f_int64);
    write(w, value.f_float);
    write(w, value.f_double);
    write(w, value.f_blob_id);
    write(w, value.f_commit_id);
    write(w, value.f_uuid);
    write(w, value.f_string);
    write(w, value.f_blob);
    write(w, value.f_any);
    write(w, value.f_vec);
    write(w, value.f_mat);
}

Scalars read(Viper::Codec::Reader & r, Viper::Codec::tag<Scalars>) {
    return {read(r, Viper::Codec::tag<bool>{}),
            read(r, Viper::Codec::tag<std::uint8_t>{}),
            read(r, Viper::Codec::tag<std::uint16_t>{}),
            read(r, Viper::Codec::tag<std::uint32_t>{}),
            read(r, Viper::Codec::tag<std::uint64_t>{}),
            read(r, Viper::Codec::tag<std::int8_t>{}),
            read(r, Viper::Codec::tag<std::int16_t>{}),
            read(r, Viper::Codec::tag<std::int32_t>{}),
            read(r, Viper::Codec::tag<std::int64_t>{}),
            read(r, Viper::Codec::tag<float>{}),
            read(r, Viper::Codec::tag<double>{}),
            read(r, Viper::Codec::tag<Viper::BlobId>{}),
            read(r, Viper::Codec::tag<Viper::CommitId>{}),
            read(r, Viper::Codec::tag<Viper::UUId>{}),
            read(r, Viper::Codec::tag<std::string>{}),
            read(r, Viper::Codec::tag<Viper::Blob>{}),
            read(r, Viper::Codec::tag<Viper::Any>{}),
            read(r, Viper::Codec::tag<std::array<std::uint8_t, 2>>{}),
            read(r, Viper::Codec::tag<std::array<std::array<std::uint8_t, 2>, 2>>{})};
}


void write(Viper::Codec::Writer & w, Single const & value) {
    write(w, value.f_single);
}

Single read(Viper::Codec::Reader & r, Viper::Codec::tag<Single>) {
    return {read(r, Viper::Codec::tag<std::uint8_t>{})};
}


} // namespace Core