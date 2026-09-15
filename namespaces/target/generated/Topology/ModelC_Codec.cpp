// unité ModelC — l'implémentation du pont.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "ModelC_Codec.hpp"

#include "ModelC_Model.hpp"

#include "Topology_Codec.hpp"

#include "Viper_Definitions.hpp"
#include "Viper_StreamCodecInstancing.hpp"
#include "Viper_ValueDecoder.hpp"
#include "Viper_ValueEncoder.hpp"
#include "Viper_TypeErrors.hpp"
#include "Viper_Types.hpp"

namespace ModelC {


void write(Viper::Codec::Writer & w, MarkerKey const & value) {
    write(w, value.instanceId());
    write(w, value.runtimeId());
}

MarkerKey read(Viper::Codec::Reader & r, Viper::Codec::tag<MarkerKey>) {
    auto const instanceId{read(r, Viper::Codec::tag<Viper::UUId>{})};
    auto const runtimeId{read(r, Viper::Codec::tag<Viper::UUId>{})};

    return {instanceId, runtimeId};
}





} // namespace ModelC