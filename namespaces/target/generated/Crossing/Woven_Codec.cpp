// unité Woven — l'implémentation du pont.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/crossing/Crossing.dsm.json by kibo-2.0.0.jar

#include "Woven_Codec.hpp"

#include "Woven_Model.hpp"

#include "Crossing_Codec.hpp"

#include "Viper_Definitions.hpp"
#include "Viper_Stream.hpp"
#include "Viper_TypeErrors.hpp"
#include "Viper_Types.hpp"

namespace Woven {


void write(Viper::Codec::Writer & w, KnotKey const & value) {
    write(w, value.instanceId());
    write(w, value.runtimeId());
}

KnotKey read(Viper::Codec::Reader & r, Viper::Codec::tag<KnotKey>) {
    auto const instanceId{read(r, Viper::Codec::tag<Viper::UUId>{})};
    auto const runtimeId{read(r, Viper::Codec::tag<Viper::UUId>{})};

    return {instanceId, runtimeId};
}


void write(Viper::Codec::Writer & w, DerivedKey const & value) {
    write(w, value.instanceId());
    write(w, value.runtimeId());
}

DerivedKey read(Viper::Codec::Reader & r, Viper::Codec::tag<DerivedKey>) {
    auto const instanceId{read(r, Viper::Codec::tag<Viper::UUId>{})};
    auto const runtimeId{read(r, Viper::Codec::tag<Viper::UUId>{})};

    return {instanceId, runtimeId};
}


void write(Viper::Codec::Writer & w, WeaveKey const & value) {
    write(w, value.instanceId());
    write(w, value.runtimeId());
}

WeaveKey read(Viper::Codec::Reader & r, Viper::Codec::tag<WeaveKey>) {
    auto const instanceId{read(r, Viper::Codec::tag<Viper::UUId>{})};
    auto const runtimeId{read(r, Viper::Codec::tag<Viper::UUId>{})};

    return {instanceId, runtimeId};
}



void write(Viper::Codec::Writer & w, Composites const & value) {
    write(w, value.f_tuple);
    write(w, value.f_optional);
    write(w, value.f_vector);
    write(w, value.f_set);
    write(w, value.f_map_keys);
    write(w, value.f_map_enum);
    write(w, value.f_xarray);
    write(w, value.f_variant);
}

Composites read(Viper::Codec::Reader & r, Viper::Codec::tag<Composites>) {
    return {read(r, Viper::Codec::tag<std::tuple<Core::Colour, Parts::Colour>>{}),
            read(r, Viper::Codec::tag<std::optional<Core::ThingKey>>{}),
            read(r, Viper::Codec::tag<std::vector<Parts::Colour>>{}),
            read(r, Viper::Codec::tag<std::set<Core::ThingKey>>{}),
            read(r, Viper::Codec::tag<std::map<Core::ThingKey, Parts::ThingKey>>{}),
            read(r, Viper::Codec::tag<std::map<Core::Grade, Parts::Colour>>{}),
            read(r, Viper::Codec::tag<Viper::XArray<Core::Colour>>{}),
            read(r, Viper::Codec::tag<std::variant<Core::Colour, Parts::Colour, std::string>>{})};
}


void write(Viper::Codec::Writer & w, Entities const & value) {
    write(w, value.f_core_grade);
    write(w, value.f_parts_grade);
    write(w, value.f_core_colour);
    write(w, value.f_parts_colour);
    write(w, value.f_single);
    write(w, value.f_thing);
    write(w, value.f_sub_thing);
    write(w, value.f_other_thing);
    write(w, value.f_klub);
    write(w, value.f_any_concept);
}

Entities read(Viper::Codec::Reader & r, Viper::Codec::tag<Entities>) {
    return {read(r, Viper::Codec::tag<Core::Grade>{}),
            read(r, Viper::Codec::tag<Parts::Grade>{}),
            read(r, Viper::Codec::tag<Core::Colour>{}),
            read(r, Viper::Codec::tag<Parts::Colour>{}),
            read(r, Viper::Codec::tag<Core::Single>{}),
            read(r, Viper::Codec::tag<Core::ThingKey>{}),
            read(r, Viper::Codec::tag<Core::SubThingKey>{}),
            read(r, Viper::Codec::tag<Parts::ThingKey>{}),
            read(r, Viper::Codec::tag<Core::KlubKey>{}),
            read(r, Viper::Codec::tag<::Crossing::AnyConceptKey>{})};
}


void write(Viper::Codec::Writer & w, Nested const & value) {
    write(w, value.f_composites);
    write(w, value.f_entities);
}

Nested read(Viper::Codec::Reader & r, Viper::Codec::tag<Nested>) {
    return {read(r, Viper::Codec::tag<Composites>{}),
            read(r, Viper::Codec::tag<Entities>{})};
}


} // namespace Woven