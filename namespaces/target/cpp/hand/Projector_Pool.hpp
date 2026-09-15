// Projector — the pool that makes the composing layer necessary.
//
// `void link(key<ModelA::Material>, key<ModelB::Material>)`. Its signature names two
// namespaces, so it belongs to neither, and asking which one owns it is the wrong
// question: a pool is not owned by the namespaces whose types it mentions. It is the
// operations an application chooses to expose, and another application over the same
// models would expose others.

#ifndef Projector_Pool_hpp
#define Projector_Pool_hpp

#include "ModelA_Data.hpp"
#include "ModelB_Data.hpp"

#include "Viper_FunctionPool.hpp"
#include "Viper_ServiceRemote.hpp"

#include <memory>

namespace Projector {

void link(ModelA::MaterialKey const & a, ModelB::MaterialKey const & b);

std::shared_ptr<Viper::FunctionPool> pool();

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
