// Topology — le programme qui éprouve le modèle.
//
// LE SEUL ARTEFACT QUI ÉNUMÈRE LES UNITÉS, et c'est sa raison d'être. Tout le reste de la
// génération produit du code par unité, qui ne connaît que lui-même ; quelqu'un doit bien
// dire qu'un modèle est fait de celles-ci. C'est un assemblage, et c'est du socle.
//
// LE PACK EN ÉCRIT QUATRE -- codec, base, base en fuzz, base distante -- qui ne diffèrent
// que par les options acceptées et les appels lancés. Ici il y en a un, parce que ce qu'ils
// lancent est devenu une liste et non sept familles de fonctions.

#include "Topology_Test.hpp"

#include "Annotations_Test.hpp"
#include "ModelA_Test.hpp"
#include "ModelB_Test.hpp"
#include "ModelC_Test.hpp"
#include "Projection_Test.hpp"

#include "Viper_Database.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

namespace {

/// Les unités du modèle, dans l'ordre où il les déclare. La seule liste que la génération
/// produise à ce niveau -- et la seule chose qu'une unité ne peut pas dire d'elle-même.
void testTypes() {
    ModelA::test();
    ModelB::test();
    ModelC::test();
    Projection::test();
    Annotations::test();
}

void testDatabase(std::shared_ptr<Viper::Database> const & db) {
    ModelA::testDatabase(db);
    ModelB::testDatabase(db);
    ModelC::testDatabase(db);
    Projection::testDatabase(db);
    Annotations::testDatabase(db);
}

} // namespace

int main(int argc, char * argv[]) {
    // Une graine explicite rend la séquence reproductible ; sans elle, chaque exécution
    // éprouve autre chose, ce qui est le but.
    if (argc > 2 && std::string{argv[1]} == "--seed")
        Topology::Test::seed(std::strtoull(argv[2], nullptr, 10));

    try {
        testTypes();

        auto const db = Viper::Database::createInMemory();
        testDatabase(db);
        db->close();
    } catch (std::exception const & e) {
        std::cerr << "échec : " << e.what() << std::endl;
        return 1;
    }

    std::cout << "ok" << std::endl;
    return 0;
}
