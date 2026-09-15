// unité ModelB — l'implémentation du pont.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "ModelB_Codec.hpp"

#include "ModelB_Model.hpp"

#include "Topology_Codec.hpp"

#include "Viper_Definitions.hpp"
#include "Viper_Stream.hpp"
#include "Viper_TypeErrors.hpp"
#include "Viper_Types.hpp"

namespace ModelB {


void write(Viper::Codec::Writer & w, MaterialKey const & value) {
    write(w, value.instanceId());
    write(w, value.runtimeId());
}

MaterialKey read(Viper::Codec::Reader & r, Viper::Codec::tag<MaterialKey>) {
    auto const instanceId{read(r, Viper::Codec::tag<Viper::UUId>{})};
    auto const runtimeId{read(r, Viper::Codec::tag<Viper::UUId>{})};

    return {instanceId, runtimeId};
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


} // namespace ModelB