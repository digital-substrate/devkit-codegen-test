// modèle Topology — le programme qui éprouve le modèle.
//
// Generated from /Volumes/DigitalSubstrate/devkit-codegen-test/namespaces/Topology.dsm.json by kibo-2.0.0.jar

#include "Topology_Test.hpp"

#include "ModelA_Test.hpp"
#include "ModelC_Test.hpp"
#include "ModelB_Test.hpp"
#include "Projection_Test.hpp"
#include "Annotations_Test.hpp"
#include "Projector_Pool.hpp"
#include "Tools_Pool.hpp"
#include "LinkModel_Pool.hpp"

#include "Viper_Database.hpp"
#include "Viper_DatabaseTransactionMode.hpp"

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>

namespace {

/// Les unités du modèle, dans l'ordre où il les déclare. La seule liste produite à ce
/// niveau -- et la seule chose qu'une unité ne peut pas dire d'elle-même.
void testTypes() {
    ModelA::test();
    ModelC::test();
    ModelB::test();
    Projection::test();
    Annotations::test();
}

void testDatabase(std::shared_ptr<Viper::Database> const & db) {
    ModelA::testDatabase(db);
    ModelC::testDatabase(db);
    ModelB::testDatabase(db);
    Projection::testDatabase(db);
    Annotations::testDatabase(db);
}

void fuzzDatabase(std::shared_ptr<Viper::Database> const & db, std::size_t count) {
    ModelA::fuzzDatabase(db, count);
    ModelC::fuzzDatabase(db, count);
    ModelB::fuzzDatabase(db, count);
    Projection::fuzzDatabase(db, count);
    Annotations::fuzzDatabase(db, count);
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

        // LE MODÈLE EST DONNÉ À LA BASE, ET C'EST TOUT CE QUE LA CLASSE GÉNÉRÉE FAISAIT DE
        // PLUS. `Database::create` du pack étendait les définitions du fichier avec celles
        // du modèle, et `open` vérifiait qu'elles s'y trouvaient. Rien d'autre dans ses
        // 1 638 lignes ne nommait le modèle -- et une fois cet appel écrit ici, la classe
        // par modèle n'a plus de raison d'être.
        db->extendDefinitions(Topology::Codec::definitions());

        // UNE TRANSACTION AUTOUR DE TOUT, parce que la base refuse d'écrire sans. Le pack
        // l'ouvre au même endroit, et c'est le genre de chose qu'aucune lecture ne dit :
        // elle se découvre en exécutant.
        db->beginTransaction(Viper::DatabaseTransactionMode::Exclusive);

        // Ce que la base offre hors du modèle : elle ne nomme aucun type, donc elle
        // s'éprouve sans rien demander aux unités.
        Topology::Test::testMetadata(db);
        Topology::Test::testBlobCreate(db);
        Topology::Test::testBlobStream(db);
        Topology::Test::testBlobIO(db);

        // Un blob existe pendant l'épreuve des attachments : un document peut en tenir
        // l'identifiant, et le modèle refuse une référence vers un blob absent.
        Topology::Test::withBlob(db);
        testDatabase(db);
        fuzzDatabase(db, 32);
        Topology::Test::withoutBlob(db);

        // LE PONT, APPELÉ. Chaque fonction de chaque pool, avec des arguments fuzzés depuis
        // son prototype : la valeur dynamique traverse, la fonction statique s'exécute, le
        // retour revient encodé. C'est la seule épreuve qui franchit la frontière.
        Topology::Test::testPool(Projector::pool());
        Topology::Test::testPool(Tools::pool());
        Topology::Test::testPool(LinkModel::pool(), db);

        db->commit();
        db->close();
    } catch (std::exception const & e) {
        std::cerr << "échec : " << e.what() << std::endl;
        return 1;
    }

    std::cout << "ok" << std::endl;
    return 0;
}