// Tools — a pool, and a unit in its own right.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#ifndef Tools_Pool_hpp
#define Tools_Pool_hpp


#include "Viper_FunctionPool.hpp"
#include "Viper_ServiceRemote.hpp"

// LE CONTEXTE SUR LEQUEL LA FONCTION AGIT. Un pool ordinaire n'en prend pas ; celui-ci le
// prend en premier argument, donc il en a besoin dans ses signatures.
#include "Viper_AttachmentGetting.hpp"
#include "Viper_AttachmentMutating.hpp"

#include <cstdint>
#include <memory>

namespace Tools {

void reset();
std::int64_t add(std::int64_t a, std::int64_t b);

std::shared_ptr<Viper::FunctionPool> pool();

/// The same pool, seen from a client.
class Remote final {
public:
    explicit Remote(std::shared_ptr<Viper::ServiceRemote> service);
    bool isAvailable() const;

    void reset() const;
    std::int64_t add(std::int64_t a, std::int64_t b) const;

private:
    std::shared_ptr<Viper::ServiceRemote> _service;
};

} // namespace Tools

#endif