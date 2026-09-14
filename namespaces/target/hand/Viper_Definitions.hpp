#ifndef Viper_Definitions_hpp
#define Viper_Definitions_hpp
#include "Viper_UUId.hpp"
#include <memory>
namespace Viper {
class Attachment;
class Definitions {
public:
    std::shared_ptr<Attachment> checkAttachment(UUId const & runtimeId) const;
};
}
#endif
