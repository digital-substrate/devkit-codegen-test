// Projector — a pool, and a unit in its own right.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#ifndef Projector_Pool_hpp
#define Projector_Pool_hpp

#include "ModelA_Data.hpp"
#include "ModelB_Data.hpp"

#include "Viper_FunctionPool.hpp"
#include "Viper_ServiceRemote.hpp"

#include <cstdint>
#include <memory>

namespace Projector {

void link(ModelA::MaterialKey const & a, ModelB::MaterialKey const & b);

std::shared_ptr<Viper::FunctionPool> pool();

/// The same pool, seen from a client.
class Remote final {
public:
    explicit Remote(std::shared_ptr<Viper::ServiceRemote> service);
    bool isAvailable() const;

    void link(ModelA::MaterialKey const & a, ModelB::MaterialKey const & b) const;

private:
    std::shared_ptr<Viper::ServiceRemote> _service;
};

} // namespace Projector

#endif