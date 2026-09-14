#ifndef Viper_AttachmentMutating_hpp
#define Viper_AttachmentMutating_hpp
#include "Viper_AttachmentGetting.hpp"
namespace Viper {
class Path;
class Value;
class AttachmentMutating : public AttachmentGetting {
public:
    virtual void set(std::shared_ptr<Attachment> const & attachment,
                     std::shared_ptr<ValueKey> const & key,
                     std::shared_ptr<Value const> const & value) = 0;
    virtual void diff(std::shared_ptr<Attachment> const & attachment,
                      std::shared_ptr<ValueKey> const & key,
                      std::shared_ptr<Value const> const & value,
                      bool recursive) = 0;
    virtual void update(std::shared_ptr<Attachment> const & attachment,
                        std::shared_ptr<ValueKey> const & key,
                        std::shared_ptr<Path const> const & path,
                        std::shared_ptr<Value const> const & value) = 0;
};
}
#endif
