#include "library_describe.hpp"
#include "shop_store_reads.hpp"

#include <sstream>

namespace library {

namespace attachments = shop::store::reads;

std::string describe(std::shared_ptr<Viper::AttachmentGetting> const & getting) {
    std::ostringstream out;
    for (auto const & key : attachments::Product::properties::keys(getting)) {
        auto const p{attachments::Product::properties::get(getting, key)};
        out << "product " << key.instanceId().uuidString() << " has=" << attachments::Product::properties::has(getting, key);
        if (p) {
            out << " name=" << p->name << " price=" << p->price << " tags=";
            for (auto const & tag : p->tags)
                out << tag << ',';
        }
        out << '\n';
    }
    for (auto const & key : attachments::Part::properties::keys(getting)) {
        auto const p{attachments::Part::properties::get(getting, key)};
        out << "part " << key.instanceId().uuidString();
        if (p)
            out << " reference=" << p->reference << " quantity=" << p->quantity;
        out << '\n';
    }
    return out.str();
}

} // namespace library
