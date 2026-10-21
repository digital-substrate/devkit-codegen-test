// The Commit application: writes the fixture through its usage, commit_attachments, commits it,
// then prints what the library reads from the committed state. It also exposes its two pools.
#include "fixture.hpp"
#include "library_describe.hpp"
#include "shop_catalog_attachment_pool.hpp"
#include "shop_codec.hpp"
#include "shop_store_commit_attachments.hpp"
#include "shop_tools_pool.hpp"

#include "Viper_CommitDatabase.hpp"
#include "Viper_CommitMutableState.hpp"
#include "Viper_CommitState.hpp"
#include "Viper_CommitStateBuilder.hpp"

#include <iostream>

int main() {
    namespace attachments = shop::store::commit_attachments;

    auto const database{Viper::CommitDatabase::createInMemory()};
    database->extendDefinitions(shop::codec::definitions());

    auto const state{Viper::CommitMutableState::make(Viper::CommitStateBuilder::initialState(database))};
    for (auto const & [key, value] : fixture::products())
        attachments::Product::properties::set(state, key, value);
    for (auto const & [key, value] : fixture::parts())
        attachments::Part::properties::set(state, key, value);
    auto const commitId{database->commitMutations("fixture", state)};

    if (!shop::tools::pool() || !shop::catalog::pool())
        return 1;

    std::cout << library::describe(Viper::CommitStateBuilder::state(database, commitId));
    return 0;
}
