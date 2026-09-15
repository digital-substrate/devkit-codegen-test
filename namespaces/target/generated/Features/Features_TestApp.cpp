// modèle Features — le programme qui éprouve le modèle.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/features/Features.dsm.json by kibo-2.0.0.jar

#include "Features_Test.hpp"

#include "Test_Test.hpp"

#include "Viper_Database.hpp"

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

} // namespace

int main(int argc, char * argv[]) {
    // Une graine explicite rend la séquence reproductible ; sans elle, chaque exécution
    // éprouve autre chose, ce qui est le but.
    if (argc > 2 && std::string{argv[1]} == "--seed")
        Features::Test::seed(std::strtoull(argv[2], nullptr, 10));

    try {
        testTypes();

        auto const db = Viper::Database::createInMemory(Features::Codec::definitions());
        testDatabase(db);
        db->close();
    } catch (std::exception const & e) {
        std::cerr << "échec : " << e.what() << std::endl;
        return 1;
    }

    std::cout << "ok" << std::endl;
    return 0;
}