// The pools' functions, which the Commit application implements.
#include "shop_catalog_attachment_pool.hpp"
#include "shop_store_commit_attachments.hpp"
#include "shop_tools_pool.hpp"

namespace shop::tools {

std::int64_t add(std::int64_t a, std::int64_t b) {
    return a + b;
}

} // namespace shop::tools

namespace shop::catalog {

store::ProductKey create(std::shared_ptr<Viper::AttachmentMutating> const & attachmentMutating, std::string const & name,
                         float price) {
    auto const key{store::ProductKey::create()};
    store::commit_attachments::Product::properties::set(attachmentMutating, key, store::ProductProperties{name, price, {}});
    return key;
}

} // namespace shop::catalog
