// L'autre bord du pont : le même pool, vu d'un client. Les arguments partent en Value et
// le retour revient en Value -- le miroir exact de Viper::Function::checkedCall.
#ifndef Viper_ServiceRemote_hpp
#define Viper_ServiceRemote_hpp
#include "Viper_UUId.hpp"
#include "Viper_Values.hpp"
#include <memory>
#include <string>
#include <vector>
namespace Viper {
class FunctionPool;
class ServiceRemote {
public:
    virtual ~ServiceRemote() = default;
    virtual std::shared_ptr<FunctionPool> queryFunctionPool(UUId const & poolId) const = 0;
    virtual std::shared_ptr<Value> call(UUId const & poolId,
                                        std::string const & functionName,
                                        std::vector<std::shared_ptr<Value>> const & arguments) const = 0;
};
}
#endif
