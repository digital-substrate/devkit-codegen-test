// LinkModel — a pool, and a unit in its own right.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#ifndef LinkModel_Pool_hpp
#define LinkModel_Pool_hpp

#include "Projection_Data.hpp"

#include "Viper_AttachmentFunctionPool.hpp"
#include "Viper_ServiceRemote.hpp"

#include <cstdint>
#include <memory>

namespace LinkModel {

void clear(std::shared_ptr<Viper::AttachmentMutating> const & attachmentMutating, Projection::LinkKey const & linkKey);

std::shared_ptr<Viper::AttachmentFunctionPool> pool();

} // namespace LinkModel

#endif