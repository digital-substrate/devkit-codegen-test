// unité Projection — l'implémentation du pont.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "Projection_Codec.hpp"

#include "Projection_Model.hpp"

#include "Topology_Codec.hpp"

#include "Viper_Definitions.hpp"
#include "Viper_StreamCodecInstancing.hpp"
#include "Viper_ValueDecoder.hpp"
#include "Viper_ValueEncoder.hpp"
#include "Viper_TypeErrors.hpp"
#include "Viper_Types.hpp"

namespace Projection {


void write(Viper::Codec::Writer & w, LinkKey const & value) {
    write(w, value.instanceId());
    write(w, value.runtimeId());
}

LinkKey read(Viper::Codec::Reader & r, Viper::Codec::tag<LinkKey>) {
    auto const instanceId{read(r, Viper::Codec::tag<Viper::UUId>{})};
    auto const runtimeId{read(r, Viper::Codec::tag<Viper::UUId>{})};

    return {instanceId, runtimeId};
}


void write(Viper::Codec::Writer & w, DerivedMaterialKey const & value) {
    write(w, value.instanceId());
    write(w, value.runtimeId());
}

DerivedMaterialKey read(Viper::Codec::Reader & r, Viper::Codec::tag<DerivedMaterialKey>) {
    auto const instanceId{read(r, Viper::Codec::tag<Viper::UUId>{})};
    auto const runtimeId{read(r, Viper::Codec::tag<Viper::UUId>{})};

    return {instanceId, runtimeId};
}




void write(Viper::Codec::Writer & w, Pair const & value) {
    write(w, value.a);
    write(w, value.b);
}

Pair read(Viper::Codec::Reader & r, Viper::Codec::tag<Pair>) {
    return {read(r, Viper::Codec::tag<ModelA::MaterialKey>{}),
            read(r, Viper::Codec::tag<ModelB::MaterialKey>{})};
}


} // namespace Projection