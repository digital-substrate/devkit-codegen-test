// LinkModel — a pool, and a unit in its own right.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#ifndef LinkModel_Pool_hpp
#define LinkModel_Pool_hpp

#include "Projection_Data.hpp"

#include "Viper_AttachmentFunctionPool.hpp"
#include "Viper_ServiceRemote.hpp"

// LE CONTEXTE SUR LEQUEL LA FONCTION AGIT. Un pool ordinaire n'en prend pas ; celui-ci le
// prend en premier argument, donc il en a besoin dans ses signatures.
#include "Viper_AttachmentGetting.hpp"
#include "Viper_AttachmentMutating.hpp"

#include <cstdint>
#include <memory>

namespace LinkModel {

void clear(std::shared_ptr<Viper::AttachmentMutating> const & attachmentMutating, Projection::LinkKey const & linkKey);

std::shared_ptr<Viper::AttachmentFunctionPool> pool();

/// The same pool, seen from a client.
class Remote final {
public:
    explicit Remote(std::shared_ptr<Viper::ServiceRemote> service);
    bool isAvailable() const;

    void clear(std::shared_ptr<Viper::AttachmentMutating> const & attachmentMutating, Projection::LinkKey const & linkKey) const;

private:
    std::shared_ptr<Viper::ServiceRemote> _service;
};

} // namespace LinkModel

#endif