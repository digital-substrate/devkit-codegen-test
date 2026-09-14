// Tools — a pool, which is a unit in its own right.
//
// A pool holds only functions, nothing depends on it, and its name is already a scope.
// This one names no type from any namespace -- `void reset()`, `int64 add(int64, int64)`
// -- so it includes nothing and depends on nothing. The degenerate unit, and proof that
// a unit need not be a namespace of the model.

#ifndef Tools_Pool_hpp
#define Tools_Pool_hpp

#include "Viper_FunctionPool.hpp"
#include "Viper_ServiceRemote.hpp"

#include <cstdint>
#include <memory>

namespace Tools {

// ── implemented by the application, called by the runtime ──

/// Utilities whose signatures name no namespaced type at all.
void reset();
std::int64_t add(std::int64_t a, std::int64_t b);

/// The pool as the runtime sees it, with the two above registered in it.
std::shared_ptr<Viper::FunctionPool> pool();

// ── and the same pool seen from a client ──

/// `Tools::Remote`, not `FunctionPoolRemotes::Tools`: the pool's name is the unit's, and
/// `FunctionPoolRemotes` was a template's name that had become a namespace level. The
/// local and the remote side of one pool sit together, which is where a reader looks.
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
