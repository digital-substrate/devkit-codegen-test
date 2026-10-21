// The Database application: writes the fixture through its usage, database_attachments, then
// prints what the library reads from the database as it is. It compiles nothing of Commit.
#include "fixture.hpp"
#include "library_describe.hpp"
#include "shop_codec.hpp"
#include "shop_store_database_attachments.hpp"

#include "Viper_Database.hpp"

#include <iostream>

int main() {
    namespace attachments = shop::store::database_attachments;

    auto const database{Viper::Database::createInMemory()};
    database->extendDefinitions(shop::codec::definitions());

    database->beginTransaction(Viper::DatabaseTransactionMode::Deferred);
    for (auto const & [key, value] : fixture::products())
        attachments::Product::properties::set(database, key, value);
    for (auto const & [key, value] : fixture::parts())
        attachments::Part::properties::set(database, key, value);
    database->commit();

    std::cout << library::describe(database);
    return 0;
}
