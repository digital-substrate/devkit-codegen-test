// modèle Features — le programme qui éprouve le modèle.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/features/Features.dsm.json by kibo-2.0.0.jar

#include "Features_Test.hpp"

#include "Test_Test.hpp"

#include "Viper_Database.hpp"

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>

namespace {

/// Les unités du modèle, dans l'ordre où il les déclare. La seule liste produite à ce
/// niveau -- et la seule chose qu'une unité ne peut pas dire d'elle-même.
void testTypes() {
    Test::test();
}

void testDatabase(std::shared_ptr<Viper::Database> const & db) {
    Test::testDatabase(db);
}

void fuzzDatabase(std::shared_ptr<Viper::Database> const & db, std::size_t count) {
    Test::fuzzDatabase(db, count);
}

} // namespace

int main(int argc, char * argv[]) {
    // Une graine explicite rend la séquence reproductible ; sans elle, chaque exécution
    // éprouve autre chose, ce qui est le but.
    if (argc > 2 && std::string{argv[1]} == "--seed")
        Features::Test::seed(std::strtoull(argv[2], nullptr, 10));

    try {
        testTypes();

        auto const db = Viper::Database::createInMemory(Features::Codec::definitions());

        // Ce que la base offre hors du modèle : elle ne nomme aucun type, donc elle
        // s'éprouve sans rien demander aux unités.
        Features::Test::testMetadata(db);
        Features::Test::testBlobCreate(db);
        Features::Test::testBlobStream(db);
        Features::Test::testBlobIO(db);

        // Un blob existe pendant l'épreuve des attachments : un document peut en tenir
        // l'identifiant, et le modèle refuse une référence vers un blob absent.
        Features::Test::withBlob(db);
        testDatabase(db);
        fuzzDatabase(db, 32);
        Features::Test::withoutBlob(db);

        db->close();
    } catch (std::exception const & e) {
        std::cerr << "échec : " << e.what() << std::endl;
        return 1;
    }

    std::cout << "ok" << std::endl;
    return 0;
}