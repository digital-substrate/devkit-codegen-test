#ifndef Viper_AttachmentGetting_hpp
#define Viper_AttachmentGetting_hpp
#include <memory>
namespace Viper {
class Attachment;
class Definitions;
class ValueKey;
class ValueOptional;
class ValueSet;
class AttachmentGetting {
public:
    virtual ~AttachmentGetting() = default;
    virtual std::shared_ptr<Definitions const> definitions() const = 0;
    virtual std::shared_ptr<ValueSet> keys(std::shared_ptr<Attachment> const & attachment) const = 0;
    virtual bool has(std::shared_ptr<Attachment> const & attachment,
                     std::shared_ptr<ValueKey> const & key) const = 0;
    virtual std::shared_ptr<ValueOptional> get(std::shared_ptr<Attachment> const & attachment,
                                               std::shared_ptr<ValueKey> const & key) const = 0;
};
}
#endif
