// Tools — a pool, and a unit in its own right.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/service/Service.dsm.json by kibo-2.0.0.jar

#ifndef Tools_Pool_hpp
#define Tools_Pool_hpp

#include "Demo_Data.hpp"

#include "Viper_FunctionPool.hpp"
#include "Viper_ServiceRemote.hpp"

// LE CONTEXTE SUR LEQUEL AGIT UNE FONCTION D'ATTACHMENT. Un pool ordinaire n'en prend pas ;
// celui-ci le prend en premier argument, donc il en a besoin dans ses signatures.
#include "Viper_AttachmentGetting.hpp"
#include "Viper_AttachmentMutating.hpp"

#include <cstdint>
#include <memory>

namespace Tools {

std::int64_t add(std::int64_t a, std::int64_t b);
Demo::Vector3 add_vector(Demo::Vector3 const & a, Demo::Vector3 const & b);
std::string random_string(std::uint32_t size);

std::shared_ptr<Viper::FunctionPool> pool();

/// The same pool, seen from a client.
class Remote final {
public:
    explicit Remote(std::shared_ptr<Viper::ServiceRemote> service);
    bool isAvailable() const;

    std::int64_t add(std::int64_t a, std::int64_t b) const;
    Demo::Vector3 add_vector(Demo::Vector3 const & a, Demo::Vector3 const & b) const;
    std::string random_string(std::uint32_t size) const;

private:
    std::shared_ptr<Viper::ServiceRemote> _service;
};

} // namespace Tools

#endif